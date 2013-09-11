/*******************************************************************************
*                Copyright 2007, MARVELL SEMICONDUCTOR, LTD.                   *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL.                      *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*                                                                              *
* MARVELL COMPRISES MARVELL TECHNOLOGY GROUP LTD. (MTGL) AND ITS SUBSIDIARIES, *
* MARVELL INTERNATIONAL LTD. (MIL), MARVELL TECHNOLOGY, INC. (MTI), MARVELL    *
* SEMICONDUCTOR, INC. (MSI), MARVELL ASIA PTE LTD. (MAPL), MARVELL JAPAN K.K.  *
* (MJKK), MARVELL ISRAEL LTD. (MSIL).                                          *
*******************************************************************************/

#ifndef _VPP_FRC_SCL_PRV_H_
#define _VPP_FRC_SCL_PRV_H_

/**********************************************************************
*macro definitions for FRC scaler                                                                           *
***********************************************************************/

/*register number in a FRC_SCL unit, neglect those useless*/
#define FRC_SCL_REG_NUM 73//register number in local buffer

/*maximum address in the line buffer*/
#define VPP_SCL_LINE_BUF_ADDR_MAX 1279

/*scaler tap number restrictions*/
#define VPP_SCL_HTAP_NUM_MIN 1
#define VPP_SCL_HTAP_NUM_MAX 12
#define VPP_SCL_VTAP_NUM_MIN 1
#define VPP_SCL_VTAP_NUM_MAX_16BIT 8
#define VPP_SCL_VTAP_NUM_MAX_24BIT 5

/*max allowable expension ratio in non linear*/
#define VPP_SCL_MAX_EXP 4
/*max allowable reduction ratio in non linear*/
#define VPP_SCL_MAX_RED 3

/*CSC coefficient and offset number*/
#define VPP_SCL_MAX_COL_COEFF_INDEX   9
#define VPP_SCL_MAX_COL_OFFSET_INDEX  3

/*CPCB FRC_SCL unit number validation*/
#define CHECK_FRC_SCL_NUM(UnitNum)\
do{\
    if((UnitNum < VPP_FRC_SCL_MAIN) ||(UnitNum >= VPP_FRC_SCL_MAX))\
        return MV_THINVPP_EBADPARAM;\
}while(0)

/*load register default value by name*/
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)

#define WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, RegName, DefValues)\
do{\
    if (UnitNum >= VPP_FRC_SCL_BE) \
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + ((FRC5_OFFSET + (UnitNum-VPP_FRC_SCL_BE)*0x100 + RegName) << 2), DefValues.VPP_##RegName);\
    else \
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + ((FRC0_OFFSET + UnitNum * 0x100 + RegName) << 2), DefValues.VPP_##RegName);\
}while(0)

#else

#define WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, RegName, DefValues)\
do{\
    if (UnitNum == VPP_FRC_SCL_BE) \
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + ((FRC5_OFFSET + RegName) << 2), DefValues.VPP_##RegName);\
    else \
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + ((FRC0_OFFSET + UnitNum * 0x100 + RegName) << 2), DefValues.VPP_##RegName);\
}while(0)

#endif

#define WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RegName, DefValues)\
do{\
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RegName, DefValues.VPP_##RegName);\
}while(0)

/**********************************************************************
*bit field definition for FRC SCL                                                                              *
***********************************************************************/
#if (BERLIN_CHIP_VERSION >= BERLIN_C_2)
typedef union VPP_REG_SCL_ALPH_CTRL_T
{
    struct {
        unsigned int alpha_osd_fmt	: 4;
        unsigned int reserved		: 3;
        unsigned int alpha_div_en	: 1;
        unsigned int reserved2	:24;
    } field;
    unsigned int data;
} VPP_REG_SCL_ALPH_CTRL;
#endif

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/*RA_Vpp_CPCBx_PL_EN Register Bit Fields */
typedef union CPCB_PL_EN_T
{
    struct {
        unsigned int main               : 1;
        unsigned int pip                : 1;
        unsigned int ig                 : 1;
        unsigned int pg                 : 1;
        unsigned int cursor             : 1;
        unsigned int mosd               : 1;
        unsigned int bg                 : 1;
        unsigned int reserved           :25;
    } field;

    unsigned int data;
} CPCB_PL_EN;

#else
/*FRC_BE_SW1_L Register Bit Fields */
typedef union VPP_FRC_FRC_BE_SW1_L_T
{
    struct {
        unsigned int OsdSwitch                 : 4;
        unsigned int BgSwitch                   : 4;
        unsigned int reserved                   :24;
    } field;

    unsigned int data;
} VPP_FRC_FRC_BE_SW1_L;
#endif

/*CSC coefficients and offsets*/
const unsigned short VppSclCscCoeff[VPP_SCL_CSC_MAX_MODES][VPP_SCL_MAX_COL_COEFF_INDEX] = {
    /*  C0       C1      C2      C3      C4      C5      C6      C7      C8   */
    {   0x200,  0,      0,      0,      0x200,  0,      0,      0,      0x200 }, //Bypass Mode
    {   0x106,  0x20CA, 0x203C, 0x25,   0x16E,  0x6D,   0x2018, 0x20EE, 0x106 }, //RGB->YUV(709)
//    { 0xE1,  0x20AD, 0x2034, 0x20,   0x13A,  0x5E,   0x2014, 0x20CC, 0xE1 },
    {   0x106,  0x20AE, 0x2058, 0x3A,   0x12D,  0x99,   0x202A, 0x20DB, 0x106 }, //RGB->YUV(601)
    {   0x0E1,  0x20AD, 0x2034, 0x20,   0x13A,  0x5D,   0x2015, 0x20CC, 0x0E1 }, //sRGB->YUV(709)
    {   0x0E1,  0x2095, 0x204C, 0x32,   0x102,  0x84,   0x2025, 0x20BC, 0x0E1 }, //sRGB->YUV(601)
};

const unsigned short VppSclCscOff[VPP_SCL_CSC_MAX_MODES][VPP_SCL_MAX_COL_OFFSET_INDEX] = {
    /* A0       A1          A2      */
    { 0,        0,          0       }, //Bypass Mode
    { 0x800,    0,          0x800   }, //RGB->YUV(709)//
//    { 0x800,    0x100,    0x800},
    { 0x800,    0,          0x800   }, //RGB->YUV(601)
    { 0x800,    0x100,      0x800   }, //sRGB->YUV(709)
    { 0x800,    0x100,      0x800   }, //sRGB->YUV(601)
};

/**********************************************************************
*default register values of VPP FRC scaler                                                              *
***********************************************************************/

typedef struct VPP_FRC_SCL_BE_SW_T{
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned int VPP_RA_Vpp_CPCB0_PL_EN;
    unsigned int VPP_RA_Vpp_CPCB1_PL_EN;
#else
    unsigned int VPP_FRC_BE_SW_L;
    unsigned int VPP_FRC_BE_SW_H;
    unsigned int VPP_FRC_BE_SW1_L;
    unsigned int VPP_FRC_BE_SW1_H;
    unsigned int VPP_FRC_BE_SW2;
#endif
}VPP_FRC_SCL_BE_SW, *PVPP_FRC_SCL_BE_SW;

/*CPCB FRC SCL register structure*/
typedef struct VPP_FRC_SCL_T{
    unsigned int VPP_FRC_CTRL0;
    unsigned int VPP_FRC_DLY_FRST_DE;
    unsigned int VPP_FRC_DLY_DE_LRST;
    unsigned int VPP_FRC_DLY_LRST_DE;
    unsigned int VPP_FRC_BEHRES_L;
    unsigned int VPP_FRC_BEHRES_H;
    unsigned int VPP_FRC_BEVRES_L;
    unsigned int VPP_FRC_BEVRES_H;
    unsigned int VPP_FRC_FEVRES_L;
    unsigned int VPP_FRC_FEVRES_H;
    unsigned int VPP_FRC_SCLCLK_CTRL;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned int VPP_FRC_SCLCLK_CTRL1;
#endif

    unsigned int VPP_SCL_IVRES_0;
    unsigned int VPP_SCL_IVRES_1;
    unsigned int VPP_SCL_IHRES_0;
    unsigned int VPP_SCL_IHRES_1;
    unsigned int VPP_SCL_OVRES_0;
    unsigned int VPP_SCL_OVRES_1;
    unsigned int VPP_SCL_OHRES_0;
    unsigned int VPP_SCL_OHRES_1;
    unsigned int VPP_SCL_MEMSIZE_0;
    unsigned int VPP_SCL_MEMSIZE_1;
    unsigned int VPP_SCL_VRATIO_0;
    unsigned int VPP_SCL_VRATIO_1;
    unsigned int VPP_SCL_VRATIO_2;
    unsigned int VPP_SCL_HRATIO_0;
    unsigned int VPP_SCL_HRATIO_1;
    unsigned int VPP_SCL_HRATIO_2;
    unsigned int VPP_SCL_VWRAP_0;
    unsigned int VPP_SCL_VWRAP_1;
    unsigned int VPP_SCL_VINITPH_EVEN;
    unsigned int VPP_SCL_VINITPH_ODD;
    unsigned int VPP_SCL_HINITPH;
    unsigned int VPP_SCL_VCTRL_0;
    unsigned int VPP_SCL_HCTRL_0;
    unsigned int VPP_SCL_CTRL_0;
    unsigned int VPP_SCL_NUMTAPS;
    unsigned int VPP_SCL_HTAP_OFFSET;
    unsigned int VPP_SCL_VTAP_OFFSET;
    unsigned int VPP_SCL_STALL;
    unsigned int VPP_SCL_INIT_RATIO_0;
    unsigned int VPP_SCL_INIT_RATIO_1;
    unsigned int VPP_SCL_INIT_RATIO_2;
    unsigned int VPP_SCL_INC_RATIO_0;
    unsigned int VPP_SCL_INC_RATIO_1;
    unsigned int VPP_SCL_INC_RATIO_2;
    unsigned int VPP_SCL_NLCRES_0;
    unsigned int VPP_SCL_NLCRES_1;

    unsigned int VPP_SCL_MEMCTRL;
    unsigned int VPP_SCL_ALPH_CTRL;
}VPP_FRC_SCL, *PVPP_FRC_SCL;

typedef struct VPP_FRC_SCL_NEW_T{
    unsigned int VPP_RA_Vpp_MAIN_LSIZE;
    unsigned int VPP_RA_Vpp_PIP_LSIZE;
    unsigned int VPP_RA_Vpp_OSD_LSIZE;
    unsigned int VPP_RA_Vpp_PG_LSIZE;
    unsigned int VPP_RA_Vpp_AUX_LSIZE;
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    unsigned int VPP_RA_Vpp_MOSD_LSIZE;
#endif

    unsigned int VPP_RA_FE_BE_FIFO_CTRL;
    unsigned int VPP_RA_FE_BE_LRST;
    unsigned int VPP_RA_FE_BE_FRST;
    unsigned int VPP_RA_FE_BE_SYNC_CTRL;

    unsigned int VPP_RA_Vpp_pip_pix;
    unsigned int VPP_RA_Vpp_osd_pix;
    unsigned int VPP_RA_Vpp_pg_pix;
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    unsigned int VPP_RA_Vpp_mosd_pix;
    unsigned int VPP_RA_Vpp_FE_MOSD_CTRL;
#endif
    unsigned int VPP_RA_Vpp_main_ols;
    unsigned int VPP_RA_Vpp_pip_ols;
#if (BERLIN_CHIP_VERSION >= BERLIN_C_2)
    unsigned int VPP_RA_Vpp_PIP_AL_IN;
    unsigned int VPP_RA_Vpp_PIP_AL_OUT;
#endif
}VPP_FRC_SCL_NEW, *PVPP_FRC_SCL_NEW;

/*FRC SCL register default values*/
#if LOGO_ENABLE_MAIN
const VPP_FRC_SCL gFrcScl0DefValues = {
    .VPP_FRC_CTRL0  			   = 0x00000000,
    .VPP_FRC_DLY_FRST_DE     = 0x00000014,
    .VPP_FRC_DLY_DE_LRST     = 0x00000014,
    .VPP_FRC_DLY_LRST_DE     = 0x00000014,
    .VPP_FRC_BEHRES_L  	     = 0x00000000,
    .VPP_FRC_BEHRES_H  	     = 0x00000000,
    .VPP_FRC_BEVRES_L  	     = 0x00000000,
    .VPP_FRC_BEVRES_H  	     = 0x00000000,
    .VPP_FRC_FEVRES_L  	     = 0x00000000,
    .VPP_FRC_FEVRES_H  	     = 0x00000000,
    .VPP_FRC_SCLCLK_CTRL     = 0x00000080,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    .VPP_FRC_SCLCLK_CTRL1     = 0x00000080,
#endif

    .VPP_SCL_IVRES_0         = 0x000000E0,
    .VPP_SCL_IVRES_1         = 0x00000001,
    .VPP_SCL_IHRES_0         = 0x000000D0,
    .VPP_SCL_IHRES_1         = 0x00000002,
    .VPP_SCL_OVRES_0         = 0x000000E0,
    .VPP_SCL_OVRES_1         = 0x00000001,
    .VPP_SCL_OHRES_0         = 0x000000D0,
    .VPP_SCL_OHRES_1         = 0x00000002,
    .VPP_SCL_MEMSIZE_0       = 0x000000FF,//1279
    .VPP_SCL_MEMSIZE_1       = 0x00000004,
    .VPP_SCL_VRATIO_0        = 0x00000000,
    .VPP_SCL_VRATIO_1        = 0x00000000,
    .VPP_SCL_VRATIO_2        = 0x00000010,
    .VPP_SCL_HRATIO_0        = 0x00000000,
    .VPP_SCL_HRATIO_1        = 0x00000000,
    .VPP_SCL_HRATIO_2        = 0x00000010,
    .VPP_SCL_VWRAP_0         = 0x00000000,
    .VPP_SCL_VWRAP_1         = 0x00000000,
    .VPP_SCL_VINITPH_EVEN    = 0x00000080,
    .VPP_SCL_VINITPH_ODD     = 0x00000080,
    .VPP_SCL_HINITPH         = 0x00000080,
    .VPP_SCL_VCTRL_0         = 0x0000001A,//signed 10bit coefficients
    .VPP_SCL_HCTRL_0         = 0x0000001A,
    .VPP_SCL_CTRL_0          = 0x00000004,
    .VPP_SCL_NUMTAPS         = 0x00000055,
    .VPP_SCL_HTAP_OFFSET     = 0x00000000,
    .VPP_SCL_VTAP_OFFSET     = 0x00000000,
    .VPP_SCL_STALL           = 0x00000000,
    .VPP_SCL_INIT_RATIO_0    = 0x00000000,
    .VPP_SCL_INIT_RATIO_1    = 0x00000000,
    .VPP_SCL_INIT_RATIO_2    = 0x00000010,
    .VPP_SCL_INC_RATIO_0     = 0x00000000,
    .VPP_SCL_INC_RATIO_1     = 0x00000000,
    .VPP_SCL_INC_RATIO_2     = 0x00000000,
    .VPP_SCL_NLCRES_0        = 0x00000000,
    .VPP_SCL_NLCRES_1        = 0x00000000,

    .VPP_SCL_MEMCTRL         = 0x00000000,
    .VPP_SCL_ALPH_CTRL       = 0x00000002,//32 bit 8888 osd: Formatter Bypass for 32 bit OSD
};
#endif
#if LOGO_ENABLE_PIP
const VPP_FRC_SCL gFrcScl1DefValues = {
    .VPP_FRC_CTRL0  			   = 0x00000000,
    .VPP_FRC_DLY_FRST_DE     = 0x00000014,
    .VPP_FRC_DLY_DE_LRST     = 0x00000014,
    .VPP_FRC_DLY_LRST_DE     = 0x00000014,
    .VPP_FRC_BEHRES_L  	     = 0x00000000,
    .VPP_FRC_BEHRES_H  	     = 0x00000000,
    .VPP_FRC_BEVRES_L  	     = 0x00000000,
    .VPP_FRC_BEVRES_H  	     = 0x00000000,
    .VPP_FRC_FEVRES_L  	     = 0x00000000,
    .VPP_FRC_FEVRES_H  	     = 0x00000000,
    .VPP_FRC_SCLCLK_CTRL     = 0x00000080,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    .VPP_FRC_SCLCLK_CTRL1     = 0x00000080,
#endif

    .VPP_SCL_IVRES_0         = 0x000000E0,
    .VPP_SCL_IVRES_1         = 0x00000001,
    .VPP_SCL_IHRES_0         = 0x000000D0,
    .VPP_SCL_IHRES_1         = 0x00000002,
    .VPP_SCL_OVRES_0         = 0x000000E0,
    .VPP_SCL_OVRES_1         = 0x00000001,
    .VPP_SCL_OHRES_0         = 0x000000D0,
    .VPP_SCL_OHRES_1         = 0x00000002,
    .VPP_SCL_MEMSIZE_0       = 0x000000FF,//1279
    .VPP_SCL_MEMSIZE_1       = 0x00000004,
    .VPP_SCL_VRATIO_0        = 0x00000000,
    .VPP_SCL_VRATIO_1        = 0x00000000,
    .VPP_SCL_VRATIO_2        = 0x00000010,
    .VPP_SCL_HRATIO_0        = 0x00000000,
    .VPP_SCL_HRATIO_1        = 0x00000000,
    .VPP_SCL_HRATIO_2        = 0x00000010,
    .VPP_SCL_VWRAP_0         = 0x00000000,
    .VPP_SCL_VWRAP_1         = 0x00000000,
    .VPP_SCL_VINITPH_EVEN    = 0x00000080,
    .VPP_SCL_VINITPH_ODD     = 0x00000080,
    .VPP_SCL_HINITPH         = 0x00000080,
    .VPP_SCL_VCTRL_0         = 0x0000001A,//signed 10bit coefficients
    .VPP_SCL_HCTRL_0         = 0x0000001A,
    .VPP_SCL_CTRL_0          = 0x00000004,
    .VPP_SCL_NUMTAPS         = 0x00000055,
    .VPP_SCL_HTAP_OFFSET     = 0x00000000,
    .VPP_SCL_VTAP_OFFSET     = 0x00000000,
    .VPP_SCL_STALL           = 0x00000000,
    .VPP_SCL_INIT_RATIO_0    = 0x00000000,
    .VPP_SCL_INIT_RATIO_1    = 0x00000000,
    .VPP_SCL_INIT_RATIO_2    = 0x00000010,
    .VPP_SCL_INC_RATIO_0     = 0x00000000,
    .VPP_SCL_INC_RATIO_1     = 0x00000000,
    .VPP_SCL_INC_RATIO_2     = 0x00000000,
    .VPP_SCL_NLCRES_0        = 0x00000000,
    .VPP_SCL_NLCRES_1        = 0x00000000,

    .VPP_SCL_MEMCTRL         = 0x00000000,
    .VPP_SCL_ALPH_CTRL       = 0x00000002,//32 bit 8888 osd: Formatter Bypass for 32 bit OSD
};
#endif

const VPP_FRC_SCL gFrcScl5DefValues = {
    .VPP_FRC_CTRL0           = 0x00000002,
    .VPP_FRC_DLY_FRST_DE     = 0x00000014,
    .VPP_FRC_DLY_DE_LRST     = 0x00000014,
    .VPP_FRC_DLY_LRST_DE     = 0x00000014,
    .VPP_FRC_BEHRES_L  	     = 0x00000000,
    .VPP_FRC_BEHRES_H  	     = 0x00000000,
    .VPP_FRC_BEVRES_L  	     = 0x00000000,
    .VPP_FRC_BEVRES_H  	     = 0x00000000,
    .VPP_FRC_FEVRES_L  	     = 0x00000000,
    .VPP_FRC_FEVRES_H  	     = 0x00000000,
    .VPP_FRC_SCLCLK_CTRL     = 0x00000080,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    .VPP_FRC_SCLCLK_CTRL1     = 0x00000080,
#endif

    .VPP_SCL_IVRES_0         = 0x000000E0,
    .VPP_SCL_IVRES_1         = 0x00000001,
    .VPP_SCL_IHRES_0         = 0x000000D0,
    .VPP_SCL_IHRES_1         = 0x00000002,
    .VPP_SCL_OVRES_0         = 0x000000E0,
    .VPP_SCL_OVRES_1         = 0x00000001,
    .VPP_SCL_OHRES_0         = 0x000000D0,
    .VPP_SCL_OHRES_1         = 0x00000002,
    .VPP_SCL_MEMSIZE_0       = 0x000000FF,//1279
    .VPP_SCL_MEMSIZE_1       = 0x00000004,
    .VPP_SCL_VRATIO_0        = 0x00000000,
    .VPP_SCL_VRATIO_1        = 0x00000000,
    .VPP_SCL_VRATIO_2        = 0x00000010,
    .VPP_SCL_HRATIO_0        = 0x00000000,
    .VPP_SCL_HRATIO_1        = 0x00000000,
    .VPP_SCL_HRATIO_2        = 0x00000010,
    .VPP_SCL_VWRAP_0         = 0x00000000,
    .VPP_SCL_VWRAP_1         = 0x00000000,
    .VPP_SCL_VINITPH_EVEN    = 0x00000080,
    .VPP_SCL_VINITPH_ODD     = 0x00000080,
    .VPP_SCL_HINITPH         = 0x00000080,
    .VPP_SCL_VCTRL_0         = 0x0000001A,//signed 10bit coefficients
    .VPP_SCL_HCTRL_0         = 0x0000001A,
    .VPP_SCL_CTRL_0          = 0x00000022,
    .VPP_SCL_NUMTAPS         = 0x00000055,
    .VPP_SCL_HTAP_OFFSET     = 0x00000000,
    .VPP_SCL_VTAP_OFFSET     = 0x00000000,
    .VPP_SCL_STALL           = 0x00000080,
    .VPP_SCL_INIT_RATIO_0    = 0x00000000,
    .VPP_SCL_INIT_RATIO_1    = 0x00000000,
    .VPP_SCL_INIT_RATIO_2    = 0x00000010,
    .VPP_SCL_INC_RATIO_0     = 0x00000000,
    .VPP_SCL_INC_RATIO_1     = 0x00000000,
    .VPP_SCL_INC_RATIO_2     = 0x00000000,
    .VPP_SCL_NLCRES_0        = 0x00000000,
    .VPP_SCL_NLCRES_1        = 0x00000000,

    .VPP_SCL_MEMCTRL         = 0x00000000,
    .VPP_SCL_ALPH_CTRL       = 0x00000002,//32 bit 8888 osd: Formatter Bypass for 32 bit OSD
};

const VPP_FRC_SCL_NEW gFrcSclNewDefValues = {
    .VPP_RA_Vpp_MAIN_LSIZE   = 0x00000001,
    .VPP_RA_Vpp_PIP_LSIZE    = 0x00000001,
    .VPP_RA_Vpp_OSD_LSIZE    = 0x00000001,
    .VPP_RA_Vpp_PG_LSIZE     = 0x00000001,
    .VPP_RA_Vpp_AUX_LSIZE    = 0x00000001,
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    .VPP_RA_Vpp_MOSD_LSIZE    = 0x00000001,
#endif

    .VPP_RA_FE_BE_FIFO_CTRL  = 0x00000020,//set to 0x20
    .VPP_RA_FE_BE_LRST       = 0x00000000,
    .VPP_RA_FE_BE_FRST       = 0x00000000,
    .VPP_RA_FE_BE_SYNC_CTRL  = 0x00000000,

    .VPP_RA_Vpp_pip_pix      = 0x00000064,
    .VPP_RA_Vpp_osd_pix      = 0x00000064,
    .VPP_RA_Vpp_pg_pix       = 0x00000064,
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    .VPP_RA_Vpp_mosd_pix      = 0x00000064,
    .VPP_RA_Vpp_FE_MOSD_CTRL  = 0x00000000,
#endif
    .VPP_RA_Vpp_main_ols     = 0x00000000,
    .VPP_RA_Vpp_pip_ols      = 0x00000000,
#if (BERLIN_CHIP_VERSION >= BERLIN_C_2)
    .VPP_RA_Vpp_PIP_AL_IN    = 0x0000FF00,
    .VPP_RA_Vpp_PIP_AL_OUT   = 0x000000FF,
#endif
};

const VPP_FRC_SCL_BE_SW gFrcSclBeSwDefValues = {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    .VPP_RA_Vpp_CPCB0_PL_EN  = 0x00000000,
    .VPP_RA_Vpp_CPCB1_PL_EN  = 0x00000000,
#else
    .VPP_FRC_BE_SW_L         = 0x000000ff,
    .VPP_FRC_BE_SW_H         = 0x000000ff,
    .VPP_FRC_BE_SW1_L        = 0x000000ff,
    .VPP_FRC_BE_SW1_H        = 0x000000ff,
    .VPP_FRC_BE_SW2          = 0x000000ff
#endif
};

#endif
