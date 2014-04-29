#include "com_type.h"
#include "memmap.h"
#include "galois_io.h"
#include "global.h"
#include "avpll.h"

#ifdef BERLIN

#define BFM_HOST_Bus_Write32 	GA_REG_WORD32_WRITE
#define BFM_HOST_Bus_Read32	GA_REG_WORD32_READ

static char dbg_buf[256];

enum PRINT_LEVEL {
	PRN_NONE=0,
	PRN_ERR,
	PRN_RES,
	PRN_INFO,
	PRN_DBG
};
static void dbg_printf(SIGN32 logLevel,const char* szFormat, ...)
{
#if 0
	va_list args;
	va_start(args, szFormat);
	vsnprintf(dbg_buf, 255, szFormat, args);
	printf("%s\n", dbg_buf);
	va_end(args);
#endif
}

typedef struct {
	unsigned int vco_freq_index;
	unsigned int av_freq_index;
	int freq_offset; //signed number
	unsigned int p_sync2;
	unsigned int p_sync1;
	unsigned int divAV1;
	unsigned int divAV2;
	unsigned int divAV3;
} CLK_FREQ;

enum {
	HDMI_8BIT_MODE=0,
	HDMI_10BIT_MODE,
	HDMI_12BIT_MODE
};

enum {
	FRAME_RATE_59P94=0,
	FRAME_RATE_60
};

#define	OVERSAMPLE_HDMI			0
#define OVERSAMPLE_1X			1
#define OVERSAMPLE_2X			2
#define OVERSAMPLE_4X			4
#define OVERSAMPLE_8X			8

uint64_t  diag_videoFreqs[] = {
	//video frequencies, pixel freq
	25174825ull,
	27000000ull,
	54000000ull,
	74175824ull,
	108000000ull,
	148351648ull
};

//all the VCO freq reqired for video and audio in MHz
uint64_t diag_vcoFreqs[]= {
	1080000000ull, 	//8 bit HDMI
	1260000000ull,	//10 bit HDMI
	1350000000ull,	//10 bit HDMI
	1485000000ull,	//8 bit HDMI
	1512000000ull, 	//8 bit HDMI	and 12 bit HDMI
	1620000000ull,	//12 bit HDMI
	1856250000ull,//10 bit HDMI
	2227500000ull,	//12 bit HDMI
};

//from Section 7 table
static unsigned char diag_avpllRegFBDIV[]=
{
	43,	//VCO_FREQ_1_080G,
	50, //VCO_FREQ_1_260G,
	54, //VCO_FREQ_1_350G,
	59, //VCO_FREQ_1_485G,
	60, //VCO_FREQ_1_512G,
	65, //VCO_FREQ_1_620G,
	74, //VCO_FREQ_1_856G,
	89, //VCO_FREQ_2_227G
};

//from Section 7 table, bit18 is signe bit
unsigned int diag_avpllRegFREQ_OFFSET_C8[]=
{
		 (19508),	//VCO_FREQ_1_080G,
		 (33554), 	//VCO_FREQ_1_260G,
		 (00000), 	//VCO_FREQ_1_350G,
		 (28435), 	//VCO_FREQ_1_485G,
		 (33554), 	//VCO_FREQ_1_512G,
	((1<<18)|(12905)), 	//VCO_FREQ_1_620G,
		 (14169), 	//VCO_FREQ_1_856G,
		 (4712), 	//VCO_FREQ_2_227G
};

unsigned int diag_avpllRegSPEED[]=
{
        0x0,    //1.08G<F<= 1.21G, for 1.08G
        0x2,    //1.21G<F<=1.4G    for 1.26G
        0x2,    //1.21G<F<=1.4G    for 1.35G
        0x3,    //1.4G<F<=1.61G    for 1.48G
        0x3,    //1.4G<F<=1.61G    for 1.51G
        0x4,    //1.61G<F<= 1.86G  for 1.62G
        0x5,    //1.61G<F<= 1.86G  for 1.85G
        0x6,    //F> 2.22G         for 2.22G
};

unsigned int diag_avpllRegINTPI[]=
{
        0x3,    //1G~1.4                for 1.08G
        0x3,    //1G~1.4                for 1.26G
        0x3,    //1G~1.4                for 1.35G
        0x4,    //1.4G~1.8G             for 1.48G
        0x4,    //1.4G~1.8G             for 1.51G
        0x4,    //1.4G~1.8G             for 1.62G
        0x5,    //1.8G~2.25G    for 1.85G
        0x5,    //1.8G~2.25G    for 2.22G
};


//vco is determined by video frequence and HDMI mode
static int vcoSelectionTable[3][6] =
{
	{AVPLL_VCO_FREQ_1_512G, AVPLL_VCO_FREQ_1_080G, AVPLL_VCO_FREQ_1_080G, AVPLL_VCO_FREQ_1_485G, AVPLL_VCO_FREQ_1_080G, AVPLL_VCO_FREQ_1_485G},
	{AVPLL_VCO_FREQ_1_260G, AVPLL_VCO_FREQ_1_350G, AVPLL_VCO_FREQ_1_350G, AVPLL_VCO_FREQ_1_856G, AVPLL_VCO_FREQ_1_350G, AVPLL_VCO_FREQ_1_856G},
	{AVPLL_VCO_FREQ_1_512G, AVPLL_VCO_FREQ_1_620G, AVPLL_VCO_FREQ_1_620G, AVPLL_VCO_FREQ_2_227G, AVPLL_VCO_FREQ_1_620G, AVPLL_VCO_FREQ_2_227G},
};

//1KPPM is determined by video frequence and 59Hz/60Hz mode
static int ppm1kSelectionTable[2][6] =
{
	{-1, 0, 0, -1, 0, -1}, //59.94Hz 1KPPM flag
	{ 0, 1, 1,  0, 1,  0}, //60Hz 1KPPM flag
};

// Just for Audio channel configuration. Video channel configuration uses other tables.
static CLK_FREQ clk_freqs[] =
{
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_90P3168_MHZ,	-56508,	12544, 12375, 6, 0x5},	// 44.1KHz
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_65P536_MHZ, 	-121161,114688,111375,6, 0x7},	// 32KHz
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_98P304_MHZ,	-62130,	188416,185625,4, 0x17},	// 48KHz

	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_90P3168_MHZ,	-14712,	3136,	3125, 5, 0x9},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_65P536_MHZ,	-47104,	2048,	2025, 6, 0x5},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_98P304_MHZ,	125696,	16384,	16875,5, 0x8},

	{AVPLL_VCO_FREQ_1_512G,	AUDIO_FREQ_90P3168_MHZ,	-63883, 1904,	1875, 4, 0x11},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_65P536_MHZ,	13000,	23552,	23625,4, 0x17},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_98P304_MHZ,	106496, 1536,	1575, 4, 0xF},

	{AVPLL_VCO_FREQ_1_350G,	AUDIO_FREQ_90P3168_MHZ,	-14712,	3136,	3125, 4, 0xF},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_65P536_MHZ,	-80018,	28672,	28125,4, 0x15},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_98P304_MHZ,	-80018,	28672,	28125,5, 0x7},

	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_90P3168_MHZ,	-89347,	175616,	171875,4,0x15},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_65P536_MHZ,	48553,	917504,	928125,5,0xE},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_98P304_MHZ,	-25882,	311296,	309375,4,0x13},

	{AVPLL_VCO_FREQ_1_260G,	AUDIO_FREQ_90P3168_MHZ,	-14712,	3136,	3125,  5,0x7},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_65P536_MHZ,	49906,	38912,	39375, 4,0x13},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_98P304_MHZ,	-58919,	13312,	13125, 4,0xD},

	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_90P3168_MHZ,	-14712,	3136,	3125,  5,0x6},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_65P536_MHZ,	125696,	16384,	16875, 5,0x8},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_98P304_MHZ, 	-5213,	5632,	5625,  4,0xB},

	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_90P3168_MHZ,	115900,	100352,	103125,5,0x8},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_65P536_MHZ, 	-62130,	188416,	185625,4,0x17},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_98P304_MHZ, 	29696,	4096,	4125,  4,0xF},

	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_22P5792_MHZ, -56508, 12544, 12375, 6, 0x14},	// 44.1KHz
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_16P384_MHZ,  29696,  4096,  4125,  6, 0x1B},	// 32KHz
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_24P576_MHZ,  29696,  4096,  4125,  6, 0x12},  // 48KHz

	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_22P5792_MHZ, 104704, 5488,  5625,  6, 0xE},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_16P384_MHZ,  -47104, 2048,  2025,  6, 0x14},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_24P576_MHZ,  59234,  3328,  3375,  6, 0xD},

	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_22P5792_MHZ, 126750, 1456,  1500,  6, 0xD},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_16P384_MHZ,  106496, 1536,  1575,  6, 0x12},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_24P576_MHZ,  106496, 1536,  1575,  6, 0xC},

	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_22P5792_MHZ, -14712, 3136,  3125,  6, 0xC},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_16P384_MHZ,  125696, 16384, 16875, 6, 0x10},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_24P576_MHZ,  -5213,  5632,  5625,  6, 0xB},

	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_22P5792_MHZ, 115900, 100352,103125,6, 0x10},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_16P384_MHZ,  125696, 16384, 16875, 4, 0x6E},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_24P576_MHZ,  29696,  4096,  4125,  6, 0xF},

	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_22P5792_MHZ, 61280,  1232,	 1250,  6, 0xB},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_16P384_MHZ,  106496, 1024,	 1050,	6, 0xF},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_24P576_MHZ,  106496, 1024,	 1050,	6, 0xA},

	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_22P5792_MHZ, -181895,1176,	 1125,  6, 0xA},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_16P384_MHZ,  59234,  3328,	 3375,	6, 0xD},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_24P576_MHZ,  -98304, 1152,	 1125,	6, 0x9},

	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_22P5792_MHZ, 49589,  20384, 20625,	6, 0xD},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_16P384_MHZ,  29696,  4096,	 4125,	6, 0x12},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_24P576_MHZ,  29696,  4096,	 4125,  6, 0xC},

	// new entries for APLL deviation
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_22P636_MHZ,  -66890,  22636,  22275,  6, 0x14},	//
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_16P424_MHZ,  19408,  4106,  4125,  6, 0x1B},
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_24P636_MHZ,  19408,  4106,  4125,  6, 0x12},

	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_22P636_MHZ,  93917,  39613,  40500,  6, 0xE}, //
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_16P424_MHZ,  -57204,  2053,  2025,  6, 0x14},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_24P636_MHZ,  48875,  26689,  27000,  6, 0xD},

	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_22P636_MHZ,  115908, 73567,  75600,  6, 0xD},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_16P424_MHZ,  96021, 2053,  2100,  6, 0x12},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_24P636_MHZ,  96021, 2053,  2100,  6, 0xC},

	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_22P636_MHZ,  -25199,  5659,  5625,  6, 0xC},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_16P424_MHZ,  115174,  16424,  16875,  6, 0x10},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_24P636_MHZ,  -15415,  22583,  22500,  6, 0xB},

	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_22P636_MHZ,  105084, 181088,  185625,  6, 0x10},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_16P424_MHZ,  -72193, 188876,  185625,  6, 0x17},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_24P636_MHZ,  19408,  4106,  4125,  6, 0xF},

	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_22P636_MHZ,  50601, 62249,	 63000,	6, 0xB},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_16P424_MHZ,  96021, 2053,	 2100,	6, 0xF},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_24P636_MHZ,  96021, 2053,	 2100,	6, 0xA},

	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_22P636_MHZ,  -191964, 5659,	 5400,	6, 0xA},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_16P424_MHZ,  48875, 26689,	 27000,	6, 0xD},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_24P636_MHZ,  -108279, 2053,	 2000,	6, 0x9},

	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_22P636_MHZ,  38940,  73567,	 74250,  6, 0xD},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_16P424_MHZ,  19408,  4106,	 4125,  6, 0x12},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_24P636_MHZ,  19408,  4106,	 4125,  6, 0xC},

	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_90P544_MHZ,  -66890,  22636, 22275, 6, 0x5},
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_65P696_MHZ,  -131081, 114968 , 111375, 6, 0x7},
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_98P544_MHZ,  115174, 16424, 16875, 5, 0xB},

	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_90P544_MHZ,  -25199,  5659, 5625, 5, 0x9},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_65P696_MHZ,  -57204,  2053, 2025, 6, 0x5},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_98P544_MHZ,  115174, 16424, 16875, 5, 0x8},

	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_90P544_MHZ,  -74248,  96203, 94500, 4, 0x11},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_65P696_MHZ,  2753,  47219, 47250, 4, 0x17},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_98P544_MHZ,  -172123, 8212, 7875, 5, 0x8},

	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_90P544_MHZ,  -25199,  5659, 5625, 4, 0xF},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_65P696_MHZ,  -90038,  28742, 28125, 4, 0x15},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_98P544_MHZ,  -90038,  28742, 28125, 5, 0x7},

	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_90P544_MHZ,  105084,  181088, 185625, 6, 0x4},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_65P696_MHZ,  -243948,  65696, 61875, 6, 0x6},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_98P544_MHZ,  194979,  32848, 34375, 5, 0x9},

	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_90P544_MHZ,  -25199,  5659, 5625, 5, 0x7},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_65P696_MHZ,  -172123,  8212,	7875, 6, 0x4},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_98P544_MHZ,  -68990,  26689, 26250, 4, 0xD},

	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_90P544_MHZ,  -25199,  5659, 5625, 5, 0x6},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_65P696_MHZ,  115174,  16424,	 16875,  5, 0x8},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_98P544_MHZ,  -15415,  22583, 22500,  4, 0xB},

	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_90P544_MHZ,  105084,  181088, 185625, 5, 0x8},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_65P696_MHZ,  115174,  16424,	 16875,  5, 0xB},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_98P544_MHZ,  -243948,  65686, 61875,  5, 0x8},

	//
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_22P522_MHZ,  -45999,  22522,  22275,  6, 0x14},	//
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_16P342_MHZ,  40551,  8171,  8250,  6, 0x1B},
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_24P514_MHZ,  40375,  12257,  12375,  6, 0x12},

	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_22P522_MHZ,  115623,  78827,  81000,  6, 0xE}, //
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_16P342_MHZ,  -36445,  8171,  8100,  6, 0x14},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_24P514_MHZ,  5381,  134827,  135000,  5, 0x21},

	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_22P522_MHZ,  137725, 146393,  151200,  6, 0xD},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_16P342_MHZ,  -109390, 155249,  151200,  6, 0x13},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_24P514_MHZ,  -21712, 54281,  54000,  5, 0x1F},

	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_22P522_MHZ,  -4097,  11261,  11250,  6, 0xC},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_16P342_MHZ,  -117972,  138907,  135000,  6, 0x11},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_24P514_MHZ,  5381,  134827,  135000,  6, 0xB},

	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_22P522_MHZ,  126846, 180176,  185625,  6, 0x10},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_16P342_MHZ,  -51510, 187933,  185625,  6, 0x17},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_24P514_MHZ,  40379,  12257,  12375,  6, 0xF},

	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_22P522_MHZ,  72088, 123871,	 126000,6, 0xB},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_16P342_MHZ,  117549, 8171,	 8400,	6, 0xF},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_24P514_MHZ,  117373, 1751,	 1800,	6, 0xA},

	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_22P522_MHZ,  -171705, 11261,	 10800,	6, 0xA},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_16P342_MHZ,  70166,   106223, 108000,6, 0xD},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_24P514_MHZ,  -87944, 12257,	 12000,	6, 0x9},

	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_22P522_MHZ,  60367,  146393,	 148500,  6, 0xD},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_16P342_MHZ,  40551,  8171,	 8250,  6, 0x12},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_24P514_MHZ,  40379,  12257,	 12375,  6, 0xC},

	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_90P088_MHZ,  -45999,  22522, 22275, 6, 0x5},
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_65P368_MHZ,  -110692, 114394 , 111375, 6, 0x7},
	{AVPLL_VCO_FREQ_2_227G, AUDIO_FREQ_98P056_MHZ,  136622, 49028, 50625, 5, 0xB},

	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_90P088_MHZ,  -4097,  11261, 11250, 5, 0x9},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_65P368_MHZ,  -36445,  8171, 8100, 6, 0x5},
	{AVPLL_VCO_FREQ_1_620G, AUDIO_FREQ_98P056_MHZ,  136622, 49028, 50625, 5, 0x8},

	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_90P088_MHZ,  -53393,  191437, 189000, 4, 0x11},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_65P368_MHZ,  23813,  187933, 189000, 4, 0x17},
	{AVPLL_VCO_FREQ_1_512G, AUDIO_FREQ_98P056_MHZ,  -152106, 3502, 3375, 5, 0x8},

	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_90P088_MHZ,  -4097,  11261, 11250, 4, 0xF},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_65P368_MHZ,  -69444,  57197, 56250, 4, 0x15},
	{AVPLL_VCO_FREQ_1_350G, AUDIO_FREQ_98P056_MHZ,  -69612,  85799, 84375, 5, 0x7},

	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_90P088_MHZ,  126846,  180176, 185625, 6, 0x4},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_65P368_MHZ,  -224126,  65368, 61875, 6, 0x6},
	{AVPLL_VCO_FREQ_1_856G, AUDIO_FREQ_98P056_MHZ,  216824,  98056, 103125, 5, 0x9},

	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_90P088_MHZ,  -4097,  11261, 11250, 5, 0x7},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_65P368_MHZ,  -151941,  8171,	7875, 6, 0x4},
	{AVPLL_VCO_FREQ_1_260G, AUDIO_FREQ_98P056_MHZ,  -48460,  22763, 22500, 4, 0xD},

	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_90P088_MHZ,  -4097,  11261, 11250, 5, 0x6},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_65P368_MHZ,  136798,  16342,	 16875,  5, 0x8},
	{AVPLL_VCO_FREQ_1_080G, AUDIO_FREQ_98P056_MHZ,  5381,  134827, 135000,  4, 0xB},

	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_90P088_MHZ,  126846,  180176, 185625, 5, 0x8},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_65P368_MHZ,  136798,  16342,	 16875,  5, 0xB},
	{AVPLL_VCO_FREQ_1_485G, AUDIO_FREQ_98P056_MHZ,  -224288,  196112, 185625,  5, 0x8},
};

int diag_pll_A_VCO_Setting = AVPLL_VCO_FREQ_2_227G;
int diag_pll_B_VCO_Setting = AVPLL_VCO_FREQ_1_620G;

unsigned int gAVPLLA_Channel_OutputClock[8] = {0};
unsigned int gAVPLLB_Channel_OutputClock[8] = {0};

void diag_setDPll_A(int enable, int p_sync1, int p_sync2, int chId)
{
	T32Gbl_avPllCtl30 regData30;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), &regData30.u32);


	//disable DPll first
	regData30.uavPllCtl_avPllEnDpllC_A &= ~(1<<(chId-1));
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), regData30.u32);

	switch(chId)
	{
		//set values
		case 1:
		{
			T32Gbl_avPllCtl15 regData15;
			T32Gbl_avPllCtl23 regData23;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl15), &regData15.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl23), &regData23.u32);
			regData15.uavPllCtl_avPllPSync1C1_A = p_sync1;
			regData23.uavPllCtl_avPllPSync2C1_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl15), regData15.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl23), regData23.u32);
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl16 regData16;
			T32Gbl_avPllCtl24 regData24;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl16), &regData16.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl24), &regData24.u32);
			regData16.uavPllCtl_avPllPSync1C2_A = p_sync1;
			regData24.uavPllCtl_avPllPSync2C2_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl16), regData16.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl24), regData24.u32);
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl17 regData17;
			T32Gbl_avPllCtl25 regData25;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl17), &regData17.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl25), &regData25.u32);
			regData17.uavPllCtl_avPllPSync1C3_A = p_sync1;
			regData25.uavPllCtl_avPllPSync2C3_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl17), regData17.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl25), regData25.u32);
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl18 regData18;
			T32Gbl_avPllCtl26 regData26;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl18), &regData18.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl26), &regData26.u32);
			regData18.uavPllCtl_avPllPSync1C4_A = p_sync1;
			regData26.uavPllCtl_avPllPSync2C4_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl18), regData18.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl26), regData26.u32);
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl19 regData19;
			T32Gbl_avPllCtl27 regData27;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl19), &regData19.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl27), &regData27.u32);
			regData19.uavPllCtl_avPllPSync1C5_A = p_sync1;
			regData27.uavPllCtl_avPllPSync2C5_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl19), regData19.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl27), regData27.u32);
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl20 regData20;
			T32Gbl_avPllCtl28 regData28;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl20), &regData20.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl28), &regData28.u32);
			regData20.uavPllCtl_avPllPSync1C6_A = p_sync1;
			regData28.uavPllCtl_avPllPSync2C6_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl20), regData20.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl28), regData28.u32);
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl21 regData21;
			T32Gbl_avPllCtl29 regData29;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl21), &regData21.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl29), &regData29.u32);
			regData21.uavPllCtl_avPllPSync1C7_A = p_sync1;
			regData29.uavPllCtl_avPllPSync2C7_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl21), regData21.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl29), regData29.u32);
		}
		break;
		case 8:
		{
			T32Gbl_avPllCtl22 regData22;
			T32Gbl_avPllCtl30 regData30;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl22), &regData22.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), &regData30.u32);
			regData22.uavPllCtl_avPllPSync1C8_A = p_sync1;
			regData30.uavPllCtl_avPllPSync2C8_A = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl22), regData22.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), regData30.u32);
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid channel\n");
		break;
	}

	if(enable)
	{
		//enable DPLL
		regData30.uavPllCtl_avPllEnDpllC_A |= (1<<(chId-1));

		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), regData30.u32);
	}

}

void diag_setDPll_B(int enable, int p_sync1, int p_sync2, int chId)
{
	T32Gbl_avPllCtl61 regData61;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), &regData61.u32);

	//disable DPLL first
	regData61.uavPllCtl_avPllEnDpllC_B &= ~(1<<(chId-1));
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), regData61.u32);

	switch(chId)
	{
		//set values
		case 1:
		{
			T32Gbl_avPllCtl46 regData46;
			T32Gbl_avPllCtl54 regData54;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl46), &regData46.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl54), &regData54.u32);
			regData46.uavPllCtl_avPllPSync1C1_B = p_sync1;
			regData54.uavPllCtl_avPllPSync2C1_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl46), regData46.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl54), regData54.u32);
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl47 regData47;
			T32Gbl_avPllCtl55 regData55;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl47), &regData47.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl55), &regData55.u32);
			regData47.uavPllCtl_avPllPSync1C2_B = p_sync1;
			regData55.uavPllCtl_avPllPSync2C2_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl47), regData47.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl55), regData55.u32);
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl48 regData48;
			T32Gbl_avPllCtl56 regData56;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl48), &regData48.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl56), &regData56.u32);
			regData48.uavPllCtl_avPllPSync1C3_B = p_sync1;
			regData56.uavPllCtl_avPllPSync2C3_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl48), regData48.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl56), regData56.u32);
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl49 regData49;
			T32Gbl_avPllCtl57 regData57;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl49), &regData49.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl57), &regData57.u32);
			regData49.uavPllCtl_avPllPSync1C4_B = p_sync1;
			regData57.uavPllCtl_avPllPSync2C4_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl49), regData49.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl57), regData57.u32);
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl50 regData50;
			T32Gbl_avPllCtl58 regData58;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl50), &regData50.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl58), &regData58.u32);
			regData50.uavPllCtl_avPllPSync1C5_B = p_sync1;
			regData58.uavPllCtl_avPllPSync2C5_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl50), regData50.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl58), regData58.u32);
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl51 regData51;
			T32Gbl_avPllCtl59 regData59;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl51), &regData51.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl59), &regData59.u32);
			regData51.uavPllCtl_avPllPSync1C6_B = p_sync1;
			regData59.uavPllCtl_avPllPSync2C6_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl51), regData51.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl59), regData59.u32);
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl52 regData52;
			T32Gbl_avPllCtl60 regData60;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl52), &regData52.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl60), &regData60.u32);
			regData52.uavPllCtl_avPllPSync1C7_B = p_sync1;
			regData60.uavPllCtl_avPllPSync2C7_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl52), regData52.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl60), regData60.u32);
		}
		break;
		case 8:
		{
			T32Gbl_avPllCtl53 regData53;
			T32Gbl_avPllCtl61 regData61;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl53), &regData53.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), &regData61.u32);
			regData53.uavPllCtl_avPllPSync1C8_B = p_sync1;
			regData61.uavPllCtl_avPllPSync2C8_B = p_sync2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl53), regData53.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), regData61.u32);
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid channel\n");
		break;
	}

	if(enable)
	{
		//re-enable DPLL
		regData61.uavPllCtl_avPllEnDpllC_B |= (1<<(chId-1));
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), regData61.u32);
	}

}

//Yongchun Move from lower here to handle the resolution change could change the VCO.
static int avpll_inited[2] = {0, 0};

void diag_assertReset_A(void);
void diag_deassertReset_A(void);

void diag_setVCO_A(int vco_freq_index)
{
	T32Gbl_avPllCtl reg;
	T32Gbl_avPllCtl1 regData1;
	T32Gbl_avPllCtl9 regData9;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl), &reg.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl1), &regData1.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), &regData9.u32);

	//following three settings are done under reset to improve long term reliability
	diag_assertReset_A();
	regData1.uavPllCtl_avPllFbDiv_A = diag_avpllRegFBDIV[vco_freq_index];
	reg.uavPllCtl_avPllSpeed_A = diag_avpllRegSPEED[vco_freq_index];
	reg.uavPllCtl_avPllIntpi_A = diag_avpllRegINTPI[vco_freq_index];
	diag_deassertReset_A();

	regData9.uavPllCtl_avPllFreqOffsetC8_A = diag_avpllRegFREQ_OFFSET_C8[vco_freq_index];

	diag_pll_A_VCO_Setting = vco_freq_index;

    avpll_inited[0] = 1;

	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl), reg.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl1), regData1.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), regData9.u32);

	//toggle the offset_rdy bit
	{
		volatile int i;

		T32Gbl_avPllCtl9 regData;
		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_A = (1<<7);
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), regData.u32);

		//add some delay because need to be asserted by 30ns
		for(i=0; i<10000; i++);

		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_A = 0;
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), regData.u32);
	}
}

void diag_assertReset_B(void);
void diag_deassertReset_B(void);

void diag_setVCO_B(int vco_freq_index)
{
	T32Gbl_avPllCtl31 regData31;
	T32Gbl_avPllCtl32 regData32;
	T32Gbl_avPllCtl40 regData40;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl31), &regData31.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl32), &regData32.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), &regData40.u32);

	//following three settings are done under reset to improve long term reliability
	diag_assertReset_B();
	regData32.uavPllCtl_avPllFbDiv_B = diag_avpllRegFBDIV[vco_freq_index];
	regData31.uavPllCtl_avPllSpeed_B = diag_avpllRegSPEED[vco_freq_index];
	regData31.uavPllCtl_avPllIntpi_B = diag_avpllRegINTPI[vco_freq_index];
	diag_deassertReset_B();

	regData40.uavPllCtl_avPllFreqOffsetC8_B = diag_avpllRegFREQ_OFFSET_C8[vco_freq_index];

	diag_pll_B_VCO_Setting = vco_freq_index;

    avpll_inited[1] = 1;

	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), regData40.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl32), regData32.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl31), regData31.u32);

	//toggle the offset_rdy bit
	{
		volatile int i;

		T32Gbl_avPllCtl40 regData;
		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_B = (1<<7);
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), regData.u32);

		//add some delay because need to be asserted by 30ns
		for(i=0; i<10000; i++);

		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_B = 0;
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), regData.u32);
	}
}

void diag_setChanOffset_A(int offset, int chId)
{
	unsigned int reg_offset;

	if(offset<0)
	{
		reg_offset = (1<<18) | (-offset) ;
	}
	else
	{
		reg_offset = offset;
	}

	dbg_printf(PRN_INFO, "set A%d offset to 0x%x\n", chId, reg_offset);

	//set offset register
	switch(chId)
	{
		case 1:
		{
			T32Gbl_avPllCtl2 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl2), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC1_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl2), regData.u32);
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl3 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl3), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC2_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl3), regData.u32);
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl4 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl4), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC3_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl4), regData.u32);
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl5 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl5), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC4_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl5), regData.u32);
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl6 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl6), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC5_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl6), regData.u32);
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl7 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl7), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC6_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl7), regData.u32);
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl8 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl8), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC7_A = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl8), regData.u32);
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invlid Channel ID (1 to 7 only)\n");
		break;
	}

	//toggle the offset_rdy bit
	{
		volatile int i;

		T32Gbl_avPllCtl9 regData;
		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_A = (1<<(chId-1));
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), regData.u32);

		//add some delay because need to be asserted by 30ns
		for(i=0; i<10000; i++);

		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_A = 0;
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), regData.u32);
	}

}

void diag_setChanOffset_B(int offset, int chId)
{
	unsigned int reg_offset;

	if(offset<0)
	{
		reg_offset = (1<<18) | (-offset) ;
	}
	else
	{
		reg_offset = offset;
	}

	dbg_printf(PRN_INFO, "set A%d offset to 0x%x\n", chId, reg_offset);

	//set offset register
	switch(chId)
	{
		case 1:
		{
			T32Gbl_avPllCtl33 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl33), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC1_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl33), regData.u32);
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl34 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl34), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC2_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl34), regData.u32);
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl35 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl35), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC3_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl35), regData.u32);
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl36 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl36), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC4_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl36), regData.u32);
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl37 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl37), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC5_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl37), regData.u32);
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl38 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl38), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC6_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl38), regData.u32);
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl39 regData;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl39), &regData.u32);
			regData.uavPllCtl_avPllFreqOffsetC7_B = reg_offset;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl39), regData.u32);
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invlid Channel ID (1 to 7 only)\n");
		break;
	}

	//toggle the offset_rdy bit
	{
		volatile int i;

		T32Gbl_avPllCtl40 regData;
		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_B = (1<<(chId-1));
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), regData.u32);

		//add some delay because need to be asserted by 30ns
		for(i=0; i<10000; i++);

		BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), &regData.u32);

		regData.uavPllCtl_avPllFreqOffsetReadyC_B = 0;
		BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), regData.u32);
	}

}

void diag_setHDMI_Div_A(int divHDMI, int chId)
{
	unsigned int div_reg;
	T32Gbl_avPllCtl11 regData;

	switch(divHDMI)
	{
		case 0:
			div_reg = 0; //disable DIV_HDMI
			break;
		case 1:
			div_reg = 4; //div by 1, by pass
			break;
		case 2:
			div_reg = 5; //div by 2
			break;
		case 4:
			div_reg = 6; //div by 4
			break;
		case 6:
			div_reg = 7; //div by 6
			break;
		default:
			{
				dbg_printf(PRN_RES, "Invalid divider for HDMI\n");
				return ;
			}
	}

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl11), &regData.u32);

	switch(chId)
	{
		case 1:
			regData.uavPllCtl_avPllDivHdmiC1_A = div_reg;
		break;
		case 2:
			regData.uavPllCtl_avPllDivHdmiC2_A = div_reg;
		break;
		case 3:
			regData.uavPllCtl_avPllDivHdmiC3_A = div_reg;
		break;
		case 4:
			regData.uavPllCtl_avPllDivHdmiC4_A = div_reg;
		break;
		case 5:
			regData.uavPllCtl_avPllDivHdmiC5_A = div_reg;
		break;
		case 6:
			regData.uavPllCtl_avPllDivHdmiC6_A = div_reg;
		break;
		case 7:
			regData.uavPllCtl_avPllDivHdmiC7_A = div_reg;
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel Id\n");
		break;
	}

	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl11), regData.u32);
}

void diag_setHDMI_Div_B(int divHDMI, int chId)
{
	unsigned int div_reg;
	T32Gbl_avPllCtl42 regData;

	switch(divHDMI)
	{
		case 0:
			div_reg = 0; //disable DIV_HDMI
			break;
		case 1:
			div_reg = 4; //div by 1, by pass
			break;
		case 2:
			div_reg = 5; //div by 2
			break;
		case 4:
			div_reg = 6; //div by 4
			break;
		case 6:
			div_reg = 7; //div by 6
			break;
		default:
			{
				dbg_printf(PRN_RES, "Invalid divider for HDMI\n");
				return ;
			}
	}

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl42), &regData.u32);

	switch(chId)
	{
		case 1:
			regData.uavPllCtl_avPllDivHdmiC1_B = div_reg;
		break;
		case 2:
			regData.uavPllCtl_avPllDivHdmiC2_B = div_reg;
		break;
		case 3:
			regData.uavPllCtl_avPllDivHdmiC3_B = div_reg;
		break;
		case 4:
			regData.uavPllCtl_avPllDivHdmiC4_B = div_reg;
		break;
		case 5:
			regData.uavPllCtl_avPllDivHdmiC5_B = div_reg;
		break;
		case 6:
			regData.uavPllCtl_avPllDivHdmiC6_B = div_reg;
		break;
		case 7:
			regData.uavPllCtl_avPllDivHdmiC7_B = div_reg;
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel Id\n");
		break;
	}

	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl42), regData.u32);
}

//divAV1 is the register value, not the actual divider
//mapping is (binary):
//000 = bypass, the whole divAV channel will be bypassed
//100 = div by 1
//101 = div by 2
//110 = div by 5
//111 = div by 5
void diag_setAV_Div_A(int divAV1, int divAV2, int chId)
{
	if(divAV2 !=0 && (divAV2<4 || divAV2>127))
	{
		dbg_printf(PRN_RES, "Invalid divider for AV1\n");
			return ;
	}


	//program DIV_AV1 and DIV_AV2
	switch(chId)
	{
		case 1:
		{
			T32Gbl_avPllCtl11 regData11;
			T32Gbl_avPllCtl12 regData12;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl11), &regData11.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			regData11.uavPllCtl_avPllDivAv1C1_A = divAV1;
			regData12.uavPllCtl_avPllDivAv2C1_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl11), regData11.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl12 regData12;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			regData12.uavPllCtl_avPllDivAv1C2_A = divAV1;
			regData12.uavPllCtl_avPllDivAv2C2_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl12 regData12;
			T32Gbl_avPllCtl13 regData13;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), &regData13.u32);
			regData12.uavPllCtl_avPllDivAv1C3_A = divAV1;
			regData13.uavPllCtl_avPllDivAv2C3_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), regData13.u32);
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl12 regData12;
			T32Gbl_avPllCtl13 regData13;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), &regData13.u32);
			regData12.uavPllCtl_avPllDivAv1C4_A = divAV1;
			regData13.uavPllCtl_avPllDivAv2C4_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), regData13.u32);
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl12 regData12;
			T32Gbl_avPllCtl13 regData13;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), &regData13.u32);
			regData12.uavPllCtl_avPllDivAv1C5_A = divAV1;
			regData13.uavPllCtl_avPllDivAv2C5_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), regData13.u32);
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl12 regData12;
			T32Gbl_avPllCtl13 regData13;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), &regData13.u32);
			regData12.uavPllCtl_avPllDivAv1C6_A = divAV1;
			regData13.uavPllCtl_avPllDivAv2C6_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), regData13.u32);
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl12 regData12;
			T32Gbl_avPllCtl14 regData14;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl14), &regData14.u32);
			regData12.uavPllCtl_avPllDivAv1C7_A = divAV1;
			regData14.uavPllCtl_avPllDivAv2C7_A = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl14), regData14.u32);
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel Id\n");
		break;
	}
}

//divAV1 is the register value, not the actual divider
//mapping is (binary):
//000 = bypass
//100 = div by 1
//101 = div by 2
//110 = div by 5
//111 = div by 5
void diag_setAV_Div_B(int divAV1, int divAV2, int chId)
{

	if(divAV2 !=0 && (divAV2<4 || divAV2>127))
	{
		dbg_printf(PRN_RES, "Invalid divider for AV1\n");
			return ;
	}


	//program DIV_AV1 and DIV_AV2
	switch(chId)
	{
		case 1:
		{
			T32Gbl_avPllCtl42 regData42;
			T32Gbl_avPllCtl43 regData43;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl42), &regData42.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			regData42.uavPllCtl_avPllDivAv1C1_B = divAV1;
			regData43.uavPllCtl_avPllDivAv2C1_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl42), regData42.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl43 regData43;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			regData43.uavPllCtl_avPllDivAv1C2_B = divAV1;
			regData43.uavPllCtl_avPllDivAv2C2_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl43 regData43;
			T32Gbl_avPllCtl44 regData44;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), &regData44.u32);
			regData43.uavPllCtl_avPllDivAv1C3_B = divAV1;
			regData44.uavPllCtl_avPllDivAv2C3_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), regData44.u32);
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl43 regData43;
			T32Gbl_avPllCtl44 regData44;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), &regData44.u32);
			regData43.uavPllCtl_avPllDivAv1C4_B = divAV1;
			regData44.uavPllCtl_avPllDivAv2C4_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), regData44.u32);
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl43 regData43;
			T32Gbl_avPllCtl44 regData44;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), &regData44.u32);
			regData43.uavPllCtl_avPllDivAv1C5_B = divAV1;
			regData44.uavPllCtl_avPllDivAv2C5_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), regData44.u32);
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl43 regData43;
			T32Gbl_avPllCtl44 regData44;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), &regData44.u32);
			regData43.uavPllCtl_avPllDivAv1C6_B = divAV1;
			regData44.uavPllCtl_avPllDivAv2C6_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), regData44.u32);
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl43 regData43;
			T32Gbl_avPllCtl45 regData45;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl45), &regData45.u32);
			regData43.uavPllCtl_avPllDivAv1C7_B = divAV1;
			regData45.uavPllCtl_avPllDivAv2C7_B = divAV2;
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
			BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl45), regData45.u32);
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel Id\n");
		break;
	}
}

//Input is the hex code for AV2 and AV3, see table III
void diag_setAV3_Div_A(int divAV2, int divAV3, int chId)
{
	T32Gbl_avPllCtl12 regData12;
	T32Gbl_avPllCtl13 regData13;
	T32Gbl_avPllCtl14 regData14;
	T32Gbl_avPllCtl15 regData15;
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), &regData13.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl14), &regData14.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl15), &regData15.u32);


	//program DIV_AV1 and DIV_AV2
	switch(chId)
	{
		case 1:
		{
			regData12.uavPllCtl_avPllDivAv2C1_A = divAV2;
			regData14.uavPllCtl_avPllDivAv3C1_A = divAV3;
		}
		break;
		case 2:
		{
			regData12.uavPllCtl_avPllDivAv2C2_A = divAV2;
			regData14.uavPllCtl_avPllDivAv3C2_A = divAV3;
		}
		break;
		case 3:
		{
			regData13.uavPllCtl_avPllDivAv2C3_A = divAV2;
			regData14.uavPllCtl_avPllDivAv3C3_A = divAV3;
		}
		break;
		case 4:
		{
			regData13.uavPllCtl_avPllDivAv2C4_A = divAV2;
			regData14.uavPllCtl_avPllDivAv3C4_A = divAV3;
		}
		break;
		case 5:
		{
			regData13.uavPllCtl_avPllDivAv2C5_A = divAV2;
			regData14.uavPllCtl_avPllDivAv3C5_A = divAV3;			}
		break;
		case 6:
		{
			regData13.uavPllCtl_avPllDivAv2C6_A = divAV2;
			regData14.uavPllCtl_avPllDivAv3C6_A = divAV3;			}
		break;
		case 7:
		{
			regData14.uavPllCtl_avPllDivAv2C7_A = divAV2;
			regData15.uavPllCtl_avPllDivAv3C7_A = divAV3;			}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel Id\n");
		break;
	}

	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), regData12.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), regData13.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl14), regData14.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl15), regData15.u32);

}

void diag_setAV3_Div_B(int divAV2, int divAV3, int chId)
{
	T32Gbl_avPllCtl43 regData43;
	T32Gbl_avPllCtl44 regData44;
	T32Gbl_avPllCtl45 regData45;
	T32Gbl_avPllCtl46 regData46;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), &regData44.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl45), &regData45.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl46), &regData46.u32);

	switch(chId)
	{
		case 1:
		{
			regData43.uavPllCtl_avPllDivAv2C1_B = divAV2;
			regData45.uavPllCtl_avPllDivAv3C1_B = divAV3;
		}
		break;
		case 2:
		{
			regData43.uavPllCtl_avPllDivAv2C2_B = divAV2;
			regData45.uavPllCtl_avPllDivAv3C2_B = divAV3;
		}
		break;
		case 3:
		{
			regData44.uavPllCtl_avPllDivAv2C3_B = divAV2;
			regData45.uavPllCtl_avPllDivAv3C3_B = divAV3;
		}
		break;
		case 4:
		{
			regData44.uavPllCtl_avPllDivAv2C4_B = divAV2;
			regData45.uavPllCtl_avPllDivAv3C4_B = divAV3;
		}
		break;
		case 5:
		{
			regData44.uavPllCtl_avPllDivAv2C5_B = divAV2;
			regData45.uavPllCtl_avPllDivAv3C5_B = divAV3;
		}
		break;
		case 6:
		{
			regData44.uavPllCtl_avPllDivAv2C6_B = divAV2;
			regData45.uavPllCtl_avPllDivAv3C6_B = divAV3;
		}
		break;
		case 7:
		{
			regData45.uavPllCtl_avPllDivAv2C7_B = divAV2;
			regData46.uavPllCtl_avPllDivAv3C7_B = divAV3;
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel Id\n");
		break;
	}

	//write divAV2, divAV3 back
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), regData43.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), regData44.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl45), regData45.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl46), regData46.u32);
}


#define OFFSET_1KPPM_INC	(-4194)
#define OFFSET_1KPPM_DEC	(4194)

//this is done by using offset and dpll
//inc=1 means increase freq to 1001/1000
//inc=0 means disable 1KPPM (by setting offset to 0 and disable DPLL)
//inc=-1 means decrease freq to 1000/1001
void diag_set1KPPM_A(int inc, int chId)
{
	if(inc)
	{
		if(inc>0)
		{
			//increase by 1KPPM
			diag_setChanOffset_A(OFFSET_1KPPM_INC, chId);
			diag_setDPll_A(1, 1000, 1001, chId);
		}
		else
		{
			//decrease by 1KPPM
			diag_setChanOffset_A(OFFSET_1KPPM_DEC, chId);
			diag_setDPll_A(1, 1001, 1000, chId);
		}
	}
	else
	{
		//set offset to 0 and disable DPLL
		diag_setChanOffset_A(0, chId);
		diag_setDPll_A(0, 0, 0, chId);
	}
}

void diag_set1KPPM_B(int inc, int chId)
{
	if(inc)
	{
		if(inc>0)
		{
			//increase by 1KPPM
			diag_setChanOffset_B(OFFSET_1KPPM_INC, chId);
			diag_setDPll_B(1, 1000, 1001, chId);
		}
		else
		{
			//decrease by 1KPPM
			diag_setChanOffset_B(OFFSET_1KPPM_DEC, chId);
			diag_setDPll_B(1, 1001, 1000, chId);
		}
	}
	else
	{
		//set offset to 0 and disable DPLL
		diag_setChanOffset_B(0, chId);
		diag_setDPll_B(0, 0, 0, chId);
	}
}

/* new reference in MHz, chan : chan_A 0, Chan_B 1 */
void diag_changeRefFreq(int vco_freq_index, int grp)
{
	if(grp ==0)
	{
		diag_setVCO_A(vco_freq_index);
	}
	else
	{
		diag_setVCO_B(vco_freq_index);
	}
}

void diag_setMasterSlaveB(int MasterSlaveB_A, int MasterSlaveB_B)
{
	T32Gbl_avPllCtl30 regData30;
	T32Gbl_avPllCtl61 regData61;
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), &regData30.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), &regData61.u32);

	regData30.uavPllCtl_avPllMasterSlaveB_A = MasterSlaveB_A;
	regData61.uavPllCtl_avPllMasterSlaveB_B = MasterSlaveB_B;

	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), regData30.u32);
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), regData61.u32);
}

void diag_assertReset_A()
{
	T32Gbl_avPllCtl reg;

	//assert reset
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl), &reg.u32);
	reg.uavPllCtl_avPllResetPll_A=1;
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl), reg.u32);
}

void diag_deassertReset_A()
{
	volatile int i;

	T32Gbl_avPllCtl reg;

	for(i=0; i<10000; i++);

	//deassert reset
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl), &reg.u32);
	reg.uavPllCtl_avPllResetPll_A=0;
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl), reg.u32);
}

void diag_assertReset_B()
{
	T32Gbl_avPllCtl31 reg;

	//assert reset
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl31), &reg.u32);
	reg.uavPllCtl_avPllResetPll_B=1;
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl31), reg.u32);
}

void diag_deassertReset_B()
{
	volatile int i;

	T32Gbl_avPllCtl31 reg;

	for(i=0; i<10000; i++);

	//deassert reset
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl31), &reg.u32);
	reg.uavPllCtl_avPllResetPll_B=0;
	BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl31), reg.u32);

}

int divHDMICode[] = {
	1, 2, 4, 6
};

int divAV1Code[] = {
	1, 2, 5, 5
};

void diag_avpllFreq_A(int chId)
{
	int offset, sync1, sync2, divHDMI, divAV1, divAV2, divAV3;
	int enDPLL;

	T32Gbl_avPllCtl11 regData11;
	T32Gbl_avPllCtl12 regData12;
	T32Gbl_avPllCtl13 regData13;
	T32Gbl_avPllCtl14 regData14;
	T32Gbl_avPllCtl15 regData15;
	T32Gbl_avPllCtl30 regData30;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl11), &regData11.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl12), &regData12.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl13), &regData13.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl14), &regData14.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl15), &regData15.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl30), &regData30.u32);

	enDPLL = regData30.uavPllCtl_avPllEnDpllC_A & (1<<(chId-1));

	//find offset, sync1, sync2, divHDMI, divAV1, divAV2, divAV3
	switch(chId)
	{
		case 1:
		{
			T32Gbl_avPllCtl2 regData2;
			T32Gbl_avPllCtl23 regData23;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl2), &regData2.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl23), &regData23.u32);

			offset = regData2.uavPllCtl_avPllFreqOffsetC1_A;
			sync1 =  regData15.uavPllCtl_avPllPSync1C1_A;
			sync2 =  regData23.uavPllCtl_avPllPSync2C1_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC1_A;
			divAV1 = regData11.uavPllCtl_avPllDivAv1C1_A;
			divAV2 = regData12.uavPllCtl_avPllDivAv2C1_A;
			divAV3 = regData14.uavPllCtl_avPllDivAv3C1_A;
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl3 regData3;
			T32Gbl_avPllCtl16 regData16;
			T32Gbl_avPllCtl24 regData24;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl3), &regData3.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl16), &regData16.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl24), &regData24.u32);

			offset = regData3.uavPllCtl_avPllFreqOffsetC2_A;
			sync1 =  regData16.uavPllCtl_avPllPSync1C2_A;
			sync2 =  regData24.uavPllCtl_avPllPSync2C2_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC2_A;
			divAV1 = regData12.uavPllCtl_avPllDivAv1C2_A;
			divAV2 = regData12.uavPllCtl_avPllDivAv2C2_A;
			divAV3 = regData14.uavPllCtl_avPllDivAv3C2_A;
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl4 regData4;
			T32Gbl_avPllCtl17 regData17;
			T32Gbl_avPllCtl25 regData25;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl4), &regData4.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl17), &regData17.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl25), &regData25.u32);
			offset = regData4.uavPllCtl_avPllFreqOffsetC3_A;
			sync1 =  regData17.uavPllCtl_avPllPSync1C3_A;
			sync2 =  regData25.uavPllCtl_avPllPSync2C3_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC3_A;
			divAV1 = regData12.uavPllCtl_avPllDivAv1C3_A;
			divAV2 = regData13.uavPllCtl_avPllDivAv2C3_A;
			divAV3 = regData14.uavPllCtl_avPllDivAv3C3_A;
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl5 regData5;
			T32Gbl_avPllCtl18 regData18;
			T32Gbl_avPllCtl26 regData26;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl5), &regData5.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl18), &regData18.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl26), &regData26.u32);
			offset = regData5.uavPllCtl_avPllFreqOffsetC4_A;
			sync1 =  regData18.uavPllCtl_avPllPSync1C4_A;
			sync2 =  regData26.uavPllCtl_avPllPSync2C4_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC4_A;
			divAV1 = regData12.uavPllCtl_avPllDivAv1C4_A;
			divAV2 = regData13.uavPllCtl_avPllDivAv2C4_A;
			divAV3 = regData14.uavPllCtl_avPllDivAv3C4_A;
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl6 regData6;
			T32Gbl_avPllCtl19 regData19;
			T32Gbl_avPllCtl27 regData27;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl6), &regData6.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl19), &regData19.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl27), &regData27.u32);
			offset = regData6.uavPllCtl_avPllFreqOffsetC5_A;
			sync1 =  regData19.uavPllCtl_avPllPSync1C5_A;
			sync2 =  regData27.uavPllCtl_avPllPSync2C5_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC5_A;
			divAV1 = regData12.uavPllCtl_avPllDivAv1C5_A;
			divAV2 = regData13.uavPllCtl_avPllDivAv2C5_A;
			divAV3 = regData14.uavPllCtl_avPllDivAv3C5_A;
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl7 regData7;
			T32Gbl_avPllCtl20 regData20;
			T32Gbl_avPllCtl28 regData28;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl7), &regData7.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl20), &regData20.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl28), &regData28.u32);
			offset = regData7.uavPllCtl_avPllFreqOffsetC6_A;
			sync1 =  regData20.uavPllCtl_avPllPSync1C6_A;
			sync2 =  regData28.uavPllCtl_avPllPSync2C6_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC6_A;
			divAV1 = regData12.uavPllCtl_avPllDivAv1C6_A;
			divAV2 = regData13.uavPllCtl_avPllDivAv2C6_A;
			divAV3 = regData14.uavPllCtl_avPllDivAv3C6_A;
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl8 regData8;
			T32Gbl_avPllCtl21 regData21;
			T32Gbl_avPllCtl29 regData29;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl8), &regData8.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl21), &regData21.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl29), &regData29.u32);
			offset = regData8.uavPllCtl_avPllFreqOffsetC7_A;
			sync1 =  regData21.uavPllCtl_avPllPSync1C7_A;
			sync2 =  regData29.uavPllCtl_avPllPSync2C7_A;
			divHDMI= regData11.uavPllCtl_avPllDivHdmiC7_A;
			divAV1 = regData12.uavPllCtl_avPllDivAv1C7_A;
			divAV2 = regData14.uavPllCtl_avPllDivAv2C7_A;
			divAV3 = regData15.uavPllCtl_avPllDivAv3C7_A;
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel\n");
			return;

	}

	if(offset& (1<<18))
	{
		offset = - (offset & ((1<<18)-1));
	}

	//figure out which divider used
	if(divHDMI != 0)
	{
		divHDMI &= 0x3;
		dbg_printf(PRN_RES, "divHDMI on: %d\n", divHDMI);
	}

	if(divAV1 != 0)
	{
		divAV1 &= 0x3;
		dbg_printf(PRN_RES, "divAV1 on: %d\n", divAV1);
	}

	if(divAV2 != 0)
	{
		if(divAV3 == 0)
		{
			dbg_printf(PRN_RES, "divAV2 on: %d\n", divAV2);
		}
		else
		{
			dbg_printf(PRN_RES, "divAV2 on: %d\n", divAV2);
			dbg_printf(PRN_RES, "divAV3 on: %d\n", divAV3);
		}
	}
}

void diag_avpllFreq_B(int chId)
{
	int offset, sync1, sync2, divHDMI, divAV1, divAV2, divAV3;
	int enDPLL;

	T32Gbl_avPllCtl42 regData42;
	T32Gbl_avPllCtl43 regData43;
	T32Gbl_avPllCtl44 regData44;
	T32Gbl_avPllCtl45 regData45;
	T32Gbl_avPllCtl46 regData46;
	T32Gbl_avPllCtl61 regData61;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl42), &regData42.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl43), &regData43.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl44), &regData44.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl45), &regData45.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl46), &regData46.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl61), &regData61.u32);

	enDPLL = regData61.uavPllCtl_avPllEnDpllC_B & (1<<(chId-1));

	//find offset, sync1, sync2, divHDMI, divAV1, divAV2, divAV3
	switch(chId)
	{
		case 1:
		{
			T32Gbl_avPllCtl33 regData33;
			T32Gbl_avPllCtl46 regData46;
			T32Gbl_avPllCtl54 regData54;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl33), &regData33.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl46), &regData46.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl54), &regData54.u32);

			offset = regData33.uavPllCtl_avPllFreqOffsetC1_B;
			sync1 =  regData46.uavPllCtl_avPllPSync1C1_B;
			sync2 =  regData54.uavPllCtl_avPllPSync2C1_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC1_B;
			divAV1 = regData42.uavPllCtl_avPllDivAv1C1_B;
			divAV2 = regData43.uavPllCtl_avPllDivAv2C1_B;
			divAV3 = regData45.uavPllCtl_avPllDivAv3C1_B;
		}
		break;
		case 2:
		{
			T32Gbl_avPllCtl34 regData34;
			T32Gbl_avPllCtl47 regData47;
			T32Gbl_avPllCtl55 regData55;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl34), &regData34.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl47), &regData47.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl55), &regData55.u32);

			offset = regData34.uavPllCtl_avPllFreqOffsetC2_B;
			sync1 =  regData47.uavPllCtl_avPllPSync1C2_B;
			sync2 =  regData55.uavPllCtl_avPllPSync2C2_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC2_B;
			divAV1 = regData43.uavPllCtl_avPllDivAv1C2_B;
			divAV2 = regData43.uavPllCtl_avPllDivAv2C2_B;
			divAV3 = regData45.uavPllCtl_avPllDivAv3C2_B;
		}
		break;
		case 3:
		{
			T32Gbl_avPllCtl35 regData35;
			T32Gbl_avPllCtl48 regData48;
			T32Gbl_avPllCtl56 regData56;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl35), &regData35.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl48), &regData48.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl56), &regData56.u32);
			offset = regData35.uavPllCtl_avPllFreqOffsetC3_B;
			sync1 =  regData48.uavPllCtl_avPllPSync1C3_B;
			sync2 =  regData56.uavPllCtl_avPllPSync2C3_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC3_B;
			divAV1 = regData43.uavPllCtl_avPllDivAv1C3_B;
			divAV2 = regData44.uavPllCtl_avPllDivAv2C3_B;
			divAV3 = regData45.uavPllCtl_avPllDivAv3C3_B;
		}
		break;
		case 4:
		{
			T32Gbl_avPllCtl36 regData36;
			T32Gbl_avPllCtl49 regData49;
			T32Gbl_avPllCtl57 regData57;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl36), &regData36.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl49), &regData49.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl57), &regData57.u32);
			offset = regData36.uavPllCtl_avPllFreqOffsetC4_B;
			sync1 =  regData49.uavPllCtl_avPllPSync1C4_B;
			sync2 =  regData57.uavPllCtl_avPllPSync2C4_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC4_B;
			divAV1 = regData43.uavPllCtl_avPllDivAv1C4_B;
			divAV2 = regData44.uavPllCtl_avPllDivAv2C4_B;
			divAV3 = regData45.uavPllCtl_avPllDivAv3C4_B;
		}
		break;
		case 5:
		{
			T32Gbl_avPllCtl37 regData37;
			T32Gbl_avPllCtl50 regData50;
			T32Gbl_avPllCtl58 regData58;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl37), &regData37.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl50), &regData50.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl58), &regData58.u32);
			offset = regData37.uavPllCtl_avPllFreqOffsetC5_B;
			sync1 =  regData50.uavPllCtl_avPllPSync1C5_B;
			sync2 =  regData58.uavPllCtl_avPllPSync2C5_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC5_B;
			divAV1 = regData43.uavPllCtl_avPllDivAv1C5_B;
			divAV2 = regData44.uavPllCtl_avPllDivAv2C5_B;
			divAV3 = regData45.uavPllCtl_avPllDivAv3C5_B;
		}
		break;
		case 6:
		{
			T32Gbl_avPllCtl38 regData38;
			T32Gbl_avPllCtl51 regData51;
			T32Gbl_avPllCtl59 regData59;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl38), &regData38.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl51), &regData51.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl59), &regData59.u32);
			offset = regData38.uavPllCtl_avPllFreqOffsetC6_B;
			sync1 =  regData51.uavPllCtl_avPllPSync1C6_B;
			sync2 =  regData59.uavPllCtl_avPllPSync2C6_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC6_B;
			divAV1 = regData43.uavPllCtl_avPllDivAv1C6_B;
			divAV2 = regData44.uavPllCtl_avPllDivAv2C6_B;
			divAV3 = regData45.uavPllCtl_avPllDivAv3C6_B;
		}
		break;
		case 7:
		{
			T32Gbl_avPllCtl39 regData39;
			T32Gbl_avPllCtl52 regData52;
			T32Gbl_avPllCtl60 regData60;
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl39), &regData39.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl52), &regData52.u32);
			BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl60), &regData60.u32);
			offset = regData39.uavPllCtl_avPllFreqOffsetC7_B;
			sync1 =  regData52.uavPllCtl_avPllPSync1C7_B;
			sync2 =  regData60.uavPllCtl_avPllPSync2C7_B;
			divHDMI= regData42.uavPllCtl_avPllDivHdmiC7_B;
			divAV1 = regData43.uavPllCtl_avPllDivAv1C7_B;
			divAV2 = regData45.uavPllCtl_avPllDivAv2C7_B;
			divAV3 = regData46.uavPllCtl_avPllDivAv3C7_B;
		}
		break;
		default:
			dbg_printf(PRN_RES, "Invalid Channel\n");
			return;

	}

	if(offset& (1<<18))
	{
		offset = - (offset & ((1<<18)-1));
	}

	//figure out which divider used
	if(divHDMI != 0)
	{
		divHDMI &= 0x3;
		dbg_printf(PRN_RES, "divHDMI on: %d\n", divHDMI);
	}

	if(divAV1 != 0)
	{
		divAV1 &= 0x3;
		dbg_printf(PRN_RES, "divAV1 on: %d\n", divAV1);
	}

	if(divAV2 != 0)
	{
		if(divAV3 == 0)
		{
			dbg_printf(PRN_RES, "divAV2 on: %d\n", divAV2);
		}
		else
		{
			dbg_printf(PRN_RES, "divAV2 on: %d\n", divAV2);
			dbg_printf(PRN_RES, "divAV3 on: %d\n", divAV3);
		}
	}
}

void diag_vcoFreq_A(void)
{
	int offset, fbDiv;

	T32Gbl_avPllCtl1 regData1;
	T32Gbl_avPllCtl9 regData9;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl1), &regData1.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl9), &regData9.u32);

	//find offset, fbDiv
	offset = regData9.uavPllCtl_avPllFreqOffsetC8_A;
	fbDiv =  regData1.uavPllCtl_avPllFbDiv_A;

	if(offset& (1<<18))
	{
		offset = - (offset & ((1<<18)-1));
	}
}

void diag_vcoFreq_B(void)
{
	int offset, fbDiv;

	T32Gbl_avPllCtl32 regData32;
	T32Gbl_avPllCtl40 regData40;

	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl32), &regData32.u32);
	BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_avPllCtl40), &regData40.u32);

	//find offset, fbDiv
	offset = regData40.uavPllCtl_avPllFreqOffsetC8_B;
	fbDiv =  regData32.uavPllCtl_avPllFbDiv_B;

	if(offset& (1<<18))
	{
		offset = - (offset & ((1<<18)-1));
	}
}

int diag_getVCOFreq(int hdmiMode, int freqIndex)
{
    return (vcoSelectionTable[hdmiMode][freqIndex]);
}

int diag_getChannelOutputFreq(int AVPLLIndex,int chID)
{
    if (chID<0 || chID>7)
        return 0;

    if (AVPLLIndex == 0) //AVPLL-A
        return (gAVPLLA_Channel_OutputClock[chID]);
    else
        return (gAVPLLB_Channel_OutputClock[chID]);
}

uint64_t do_div_quot(uint64_t n, uint64_t base) {
    do_div(n, base);
    return n;
}

uint64_t get_divider(uint64_t vcoFreq, uint64_t videoFreq, int overSampleRate) {
    uint64_t scaled_vcoFreq = vcoFreq * 1000000;
    do_div(scaled_vcoFreq, videoFreq);
    do_div(scaled_vcoFreq, overSampleRate);
    return scaled_vcoFreq;
}

uint64_t round_divider(uint64_t divider) {
    uint64_t rounded = divider + 500000;
    do_div(rounded, 1000000);
    return rounded;
}

//freq_index, 0 to 5, the 6 VCLKs
//hdmiMode, HDMI_8BIT_MODE, HDMI_10BIT_MODE, HDMI_12BIT_MODE
//frameRate, FRAME_RATE_59P94 FRAME_RATE_60
//overSampleRate, 1, 2, 4, 8, 10, 12.5, 15
void diag_videoFreq_A(int freqIndex, int hdmiMode, int frameRate, int overSampleRate, int chId)
{
            int vcoFreqIndex=vcoSelectionTable[hdmiMode][freqIndex]; // AVPLL_VCO_FREQ_1_485G
            uint64_t vcoFreq, videoFreq;
            int ppm1K=ppm1kSelectionTable[frameRate][freqIndex]; // 0
            uint64_t divider;

            if (chId<0 || chId>7)
                return;

            dbg_printf(PRN_RES, "Set PLLA C%d:\n", chId);

            //set VCO freq here
            diag_setVCO_A(vcoFreqIndex);

            //check to see if ppm1K is need
            vcoFreq = diag_vcoFreqs[vcoFreqIndex];
            if(ppm1K<0)
            {
                        vcoFreq = vcoFreq - do_div_quot(vcoFreq, 1001);
            }

            if(ppm1K>0)
            {
                        vcoFreq = vcoFreq + do_div_quot(vcoFreq, 1000);
            }

            diag_set1KPPM_A(ppm1K, chId);

            //get the video freq
            videoFreq = diag_videoFreqs[freqIndex];
            if(frameRate)
            {
                        //60Hz vclk is 1001/1000 times 59.94Hz vclk
                        videoFreq = videoFreq + do_div_quot(videoFreq, 1000);
            }

            //disable all dividers
            diag_setHDMI_Div_A(0, chId);
            diag_setAV_Div_A(0, 0, chId); //divAV1 is for divide by 1, 0 will disable the whole divAV chain
            diag_setAV3_Div_A(0, 0, chId);

            //set the divider
            if(overSampleRate>=10)
            {
                        //use HDMI divider
                        divider = get_divider(vcoFreq, videoFreq, overSampleRate);
                        dbg_printf(PRN_RES, "HDMI divider is %d\n", round_divider(divider));
                        printk(KERN_INFO "vcoFreq and videoFreq are %llu %llu\n", vcoFreq, videoFreq);
                        printk(KERN_INFO "Raw divider is %llu\n", divider);
                        printk(KERN_INFO "HDMI divider is %llu\n", round_divider(divider));

                        diag_setHDMI_Div_A(round_divider(divider), chId);
            }
            else
            {
                        divider = get_divider(vcoFreq * 2, videoFreq, overSampleRate);
                        dbg_printf(PRN_RES, "AV divider is %d\n", round_divider(divider)>>1);

                        if(round_divider(divider)&1)
                        {
                                    //fractional divider, use AV2 and AV3
                                    //figure out AV3, AV3 = round(AV2/4)-1
                                    int divAV3 = round_divider(divider>>2)-1;

                                    //this enables divAV channel
                                    diag_setAV_Div_A(4, 0, chId);

                                    //add enable bit
                                    divAV3 |= (1<<3);
                                    diag_setAV3_Div_A(round_divider(divider), divAV3, chId);
                        }
                        else
                        {
                                    //integer divider, use AV2 only
                                    diag_setAV_Div_A(4, round_divider(divider)>>1, chId);
                        }
            }

            gAVPLLA_Channel_OutputClock[chId] = (unsigned int)(videoFreq*overSampleRate);

}

//freq_index, 0 to 5, the 6 VCLKs
//hdmiMode, HDMI_8BIT_MODE, HDMI_10BIT_MODE, HDMI_12BIT_MODE
//frameRate, FRAME_RATE_59P94 FRAME_RATE_60
//overSampleRate, 1, 2, 4, 8, 10, 12.5, 15
void diag_videoFreq_B(int freqIndex, int hdmiMode, int frameRate, int overSampleRate, int chId)
{
            int vcoFreqIndex=vcoSelectionTable[hdmiMode][freqIndex];
            uint64_t vcoFreq, videoFreq;
            int ppm1K=ppm1kSelectionTable[frameRate][freqIndex];
            uint64_t divider;

            if (chId<0 || chId>7)
                return;

            dbg_printf(PRN_RES, "Set PLLB C%d:\n", chId);

            //set VCO freq here
            diag_setVCO_B(vcoFreqIndex);

            //check to see if ppm1K is need
            vcoFreq = diag_vcoFreqs[vcoFreqIndex];
            if(ppm1K<0)
            {
                        vcoFreq = vcoFreq - do_div_quot(vcoFreq, 1001);
            }

            if(ppm1K>0)
            {
                        vcoFreq = vcoFreq + do_div_quot(vcoFreq, 1000);
            }

            diag_set1KPPM_B(ppm1K, chId);

            //get the video freq
            videoFreq = diag_videoFreqs[freqIndex];
            if(frameRate)
            {
                        //60Hz vclk is 1001/1000 times 59.94Hz vclk
                        videoFreq = videoFreq + do_div_quot(videoFreq, 1000);
            }

            //disable all dividers
            diag_setHDMI_Div_B(0, chId);
            diag_setAV_Div_B(0, 0, chId);
            diag_setAV3_Div_B(0, 0, chId);

            //set the divider
            if(overSampleRate>=10)
            {
                        //use HDMI divider
                        divider = get_divider(vcoFreq, videoFreq, overSampleRate);
                        dbg_printf(PRN_RES, "HDMI divider is %d\n", round_divider(divider));

                        diag_setHDMI_Div_B(round_divider(divider), chId);
            }
            else
            {
                        divider = get_divider(vcoFreq * 2, videoFreq, overSampleRate);
                        dbg_printf(PRN_RES, "AV divider is %d\n", round_divider(divider)>>1);

                        if(round_divider(divider)&1)
                        {
                                    //fractional divider, use AV2 and AV3
                                    //figure out AV3, AV3 = round(AV2/4)-1
                                    int divAV3 = round_divider(divider>>2)-1;

                                    //this enables divAV channel
                                    diag_setAV_Div_B(4, 0, chId);

                                    //add enable bit
                                    divAV3 |= (1<<3);
                                    diag_setAV3_Div_B(round_divider(divider), divAV3, chId);
                        }
                        else
                        {
                                    //integer divider, use AV2 only
                                    diag_setAV_Div_B(4, round_divider(divider)>>1, chId);
                        }
            }

            gAVPLLB_Channel_OutputClock[chId] = (unsigned int)(videoFreq*overSampleRate);

}

int get_freqTabIndex(int vco_freq_index, int av_freq_index)
{
	int i, tab_index=-1;

	for(i=0; i<(sizeof(clk_freqs) / sizeof(CLK_FREQ)); i++)
	{
		if(clk_freqs[i].vco_freq_index == vco_freq_index && clk_freqs[i].av_freq_index == av_freq_index)
		{
			tab_index = i; break;
		}
	}
	return tab_index;
}

// secondary MCLK keeps 4x, other MCLK div4 to 1x
int AVPLL_SetDiv4()
{
	T32Gbl_ClkSwitch1  ClkSwitch1;
	T32Gbl_clkSelect2 ClkSelect2;
#ifdef INTERNAL_ADAC_DISABLE
	T32Gbl_clkSelect3 ClkSelect3;
#endif

        GA_REG_WORD32_READ((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_ClkSwitch1), &ClkSwitch1.u32);
        ClkSwitch1.uClkSwitch_audio0ClkSwitch = 1; // primary
        ClkSwitch1.uClkSwitch_audio2ClkSwitch = 1; // mic
        ClkSwitch1.uClkSwitch_audio3ClkSwitch = 1; // spdif
#ifdef INTERNAL_ADAC_DISABLE
	ClkSwitch1.uClkSwitch_audio1ClkSwitch = 1; // stereo
#endif
        GA_REG_WORD32_WRITE((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_ClkSwitch1), (ClkSwitch1.u32));

	GA_REG_WORD32_READ((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_clkSelect2), &ClkSelect2.u32);
	ClkSelect2.uclkSelect_audio0ClkSel = Gbl_clkSelect_audio0ClkSel_d4;
	ClkSelect2.uclkSelect_audio2ClkSel = Gbl_clkSelect_audio2ClkSel_d4;
	ClkSelect2.uclkSelect_audio3ClkSel = Gbl_clkSelect_audio3ClkSel_d4;
	GA_REG_WORD32_WRITE((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_clkSelect2), (ClkSelect2.u32));

#ifdef INTERNAL_ADAC_DISABLE
	GA_REG_WORD32_READ((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_clkSelect3), &ClkSelect3.u32);
	ClkSelect3.uclkSelect_audio1ClkSel = Gbl_clkSelect_audio1ClkSel_d4;
	GA_REG_WORD32_WRITE((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_clkSelect3), (ClkSelect3.u32));
#endif
}


// S/W workaround is not required at BG2.
void AVPLL_EnableMicClk(int en)
{
        T32Gbl_clkEnable  regClkEnable;
        BFM_HOST_Bus_Read32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_clkEnable), &regClkEnable.u32);
	if (en) {
		en = 1;
	}
        regClkEnable.uclkEnable_audio2ClkEn = en;
        BFM_HOST_Bus_Write32((MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_clkEnable), regClkEnable.u32);
}
#endif // <- #if defined(BERLIN)

