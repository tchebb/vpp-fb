#ifndef _AVPLL_H_
#define _AVPLL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BERLIN

// audio channel frequency
typedef enum
{
	AUDIO_FREQ_8P4672_MHZ=0,
	AUDIO_FREQ_11P2896_MHZ,
	AUDIO_FREQ_16P9344_MHZ,
	AUDIO_FREQ_22P5792_MHZ,
	AUDIO_FREQ_12P288_MHZ,
	AUDIO_FREQ_24P576_MHZ,
	AUDIO_FREQ_16P384_MHZ,
	AUDIO_FREQ_65P536_MHZ,
	AUDIO_FREQ_90P3168_MHZ,
	AUDIO_FREQ_98P304_MHZ,

	AUDIO_FREQ_22P636_MHZ,
	AUDIO_FREQ_24P636_MHZ,
	AUDIO_FREQ_16P424_MHZ,
	AUDIO_FREQ_90P544_MHZ,
	AUDIO_FREQ_98P544_MHZ,
	AUDIO_FREQ_65P696_MHZ,

	AUDIO_FREQ_22P522_MHZ,
	AUDIO_FREQ_24P514_MHZ,
	AUDIO_FREQ_16P342_MHZ,
	AUDIO_FREQ_90P088_MHZ,
	AUDIO_FREQ_98P056_MHZ,
	AUDIO_FREQ_65P368_MHZ,
} AUDIO_CLK_FREQ;

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
typedef enum
{
        AVPLL_VCO_FREQ_1_080G=0,
        AVPLL_VCO_FREQ_1_260G,
        AVPLL_VCO_FREQ_1_350G,
        AVPLL_VCO_FREQ_1_485G,
        AVPLL_VCO_FREQ_1_512G,
        AVPLL_VCO_FREQ_1_620G,
        AVPLL_VCO_FREQ_1_856G,
        AVPLL_VCO_FREQ_2_227G
}AVPLL_VCO_FREQ;
#else
typedef enum
{
        AVPLL_VCO_FREQ_1_258G=0,
        AVPLL_VCO_FREQ_1_350G,
        AVPLL_VCO_FREQ_1_510G,
        AVPLL_VCO_FREQ_1_620G,
        AVPLL_VCO_FREQ_1_854G,
        AVPLL_VCO_FREQ_2_225G,
}AVPLL_VCO_FREQ;
#endif

void AVPLL_EnableChannel(int avpll, int id, int on);
void AVPLL_Enable(void);
void AVPLL_EnableMicClk(int en);
int AVPLL_SetWithPPM1K(int groupId, int chanId, int refFreqIndex, float avFreq, int ppm1k_en);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
int AVPLL_Set(int groupId, int chanId, int avFreqIndex);
int diag_getVCOFreq(int hdmiMode, int freqIndex);
int diag_getChannelOutputFreq(int AVPLLIndex, int chID);
void diag_videoFreq_A(int freqIndex, int hdmiMode, int frameRate, int overSampleRate, int chId);
void diag_videoFreq_B(int freqIndex, int hdmiMode, int frameRate, int overSampleRate, int chId);
#else
int AVPLL_Set(int groupId, int chanId, int refFreqIndex, float avFreq);
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif

