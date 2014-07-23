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
* MARVELL intERNATIONAL LTD. (MIL), MARVELL TECHNOLOGY, INC. (MTI), MARVELL    *
* SEMICONDUCTOR, INC. (MSI), MARVELL ASIA PTE LTD. (MAPL), MARVELL JAPAN K.K.  *
* (MJKK), MARVELL ISRAEL LTD. (MSIL).                                          *
*******************************************************************************/

#ifndef _VPP_BE_VOP_H_
#define _VPP_BE_VOP_H_

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/*Data alignment in 30-bit format after rounding.*/
typedef enum VPP_VOP_DATA_ALIGNMENT_T
{
    VPP_VOP_8_10_LSB_ALIGN = 0,
    VPP_VOP_8_10_MSB_ALIGN,
    VPP_VOP_24_30_LSB_ALIGN,
    VPP_VOP_24_30_MSB_ALIGN,
    VPP_VOP_ALIGN_MAX

}VPP_VOP_DATA_ALIGNMENT,*PVPP_VOP_DATA_ALIGNMENT;

/*Data rounding selection control*/
typedef enum tagVPP_VOP_DATA_ROUNDING
{
    VPP_VOP_12_TO_8_BITS_ROUND 	= 1,
    VPP_VOP_12_TO_10_BITS_ROUND,
    VPP_VOP_DATA_BYPASS         = 4,
    VPP_VOP_DATA_ZERO           = 7,
    VPP_VOP_DATA_ROUND_MAX

}VPP_VOP_DATA_ROUNDING,*PVPP_VOP_DATA_ROUNDING;

/*DNS mode selection control*/
typedef enum tagVPP_VOP_DNS_MODE
{
    VPP_VOP_DNS_MODE_BYPASS 	= 0,
    VPP_VOP_DNS_MODE_ENABLE,
    VPP_VOP_DNS_MODE_MAX

}VPP_VOP_DNS_MODE,*PVPP_VOP_DNS_MODE;

/*Enums for CSC mode.*/
typedef enum VPP_VOP_CSC_MODES
{
    VPP_VOP_CSC_BYPASS_MODE = 0,
    VPP_VOP_CSC_601_TO_709,
    VPP_VOP_CSC_709_TO_601,
    VPP_VOP_CSC_RGB_TO_YUV_709,
    VPP_VOP_CSC_YUV_709_TO_RGB,
    VPP_VOP_CSC_RGB_TO_YUV_601,
    VPP_VOP_CSC_YUV_601_TO_RGB,
    VPP_VOP_CSC_sRGB_TO_YUV_709,
    VPP_VOP_CSC_YUV_709_TO_sRGB,
    VPP_VOP_CSC_sRGB_TO_YUV_601,
    VPP_VOP_CSC_YUV_601_TO_sRGB,
    VPP_VOP_CSC_UV_SWAP,
    VPP_VOP_CSC_MODES_NO_CHANGE,
    VPP_VOP_CSC_MAX_MODES = VPP_VOP_CSC_MODES_NO_CHANGE

} VPP_VOP_CSC_MODES;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)

/*VOP clock polarity for TTL24 and TTL30*/
typedef enum VPP_VOP_DV_CLK_POL{
    VPP_VOP_DV_CLK_POL_NORMAL = 0,
    VPP_VOP_DV_CLK_POL_INVERT

} VPP_VOP_DV_CLK_POL;

/*output data range contral for BT656/SMPTE encoders*/
typedef enum VPP_VOP_DV_SATURATE_CTRL{
    VPP_VOP_DV_SATURATE_NO_CHANGE = 0,
    VPP_VOP_DV_SATURATE_1_255,
    VPP_VOP_DV_SATURATE_16_235,

} VPP_VOP_DV_SATURATE_CTRL;

/*HS/HDE select on DV0/1_HS pad for TTL24 and TTL30*/
typedef enum VPP_VOP_DV_HS_PAD_SEL{
    VPP_VOP_DV_HS_PAD_HDE = 0,
    VPP_VOP_DV_HS_PAD_HS,

} VPP_VOP_DV_HS_PAD_SEL;

/*VS/VDE select on DV0/1_VS pad for TTL24 and TTL30*/
typedef enum VPP_VOP_DV_VS_PAD_SEL{
    VPP_VOP_DV_VS_PAD_VDE = 0,
    VPP_VOP_DV_VS_PAD_VS,

} VPP_VOP_DV_VS_PAD_SEL;

/*DV output selection for TTL24 and TTL30*/
typedef enum VPP_VOP_DV_OUTPUT_SEL{
    VPP_VOP_DV_OUTPUT_BT656 = 0,
    VPP_VOP_DV_OUTPUT_SMPTE_DDR,
    VPP_VOP_DV_OUTPUT_INVALID,
    VPP_VOP_DV_OUTPUT_SMPTE_SDR//the output of TTL24 is ingored, if TTL30 is in this mode

} VPP_VOP_DV_OUTPUT_SEL;

/*DV Luma and Chroma selection in SMPTE DDR mode for TTL24 and TTL30*/
typedef enum VPP_VOP_DV_YC_POS_SEL{
    VPP_VOP_DV_YC_POS_C_HIGH = 0,
    VPP_VOP_DV_YC_POS_Y_HIGH,

} VPP_VOP_DV_YC_POS_SEL;

/*DV Luma and Chroma sequence selection in SMPTE SDR mode for TTL30*/
typedef enum VPP_VOP_DV_YC_SEQ_SEL{
    VPP_VOP_DV_YC_SEQ_Y_15_8 = 0,
    VPP_VOP_DV_YC_SEQ_Y_7_0,

} VPP_VOP_DV_YC_SEQ_SEL;

/*Enum for VOP clock select*/
typedef enum VPP_VOP_CLK_SEL
{
    VPP_VOP_CLK_DISABLE = -1,
    VPP_VOP_CLK_D1,
    VPP_VOP_CLK_D2,
    VPP_VOP_CLK_D4,
    VPP_VOP_CLK_D6,
    VPP_VOP_CLK_D8,
    VPP_VOP_CLK_D12,
    VPP_VOP_CLK_D3,
    VPP_VOP_CLK_MAX

}VPP_VOP_CLK_SEL;

#else

/*DV0 output components order*/
typedef enum VPP_VOP_DV0_COMP_ORDER{
    VPP_VOP_DV0_OUTPUT_CY = 0,
    VPP_VOP_DV0_OUTPUT_YC

} VPP_VOP_DV0_COMP_ORDER;

#endif

/*Type of output*/
typedef enum VPP_VOP_OUTPUT
{
    VPP_VOP_AHD = 0,
    VPP_VOP_ASD,
    VPP_VOP_HDMI,
    VPP_VOP_TTL24,
    VPP_VOP_TTL30,
    VPP_VOP_OUTPUT_MAX

}VPP_VOP_OUTPUT,*PVPP_VOP_OUTPUT;

/*HDMI control data structure*/
typedef struct VPP_VOP_HDMI_CTRL_T
{
    unsigned int CBlank;
    unsigned char InputSel;
    unsigned char OutputAlign;
}VPP_VOP_HDMI_CTRL,*PVPP_VOP_HDMI_CTRL;

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_Z2)
/*LVDS control data structure*/
typedef struct VPP_VOP_LVDS_CTRL_T
{
    unsigned char InputSel;
    unsigned char OutputAlign;
}VPP_VOP_LVDS_CTRL,*PVPP_VOP_LVDS_CTRL;
#endif

/*AHD and ASD control data structure*/
typedef struct VPP_VOP_AHD_ASD_CTRL_T
{
    unsigned char InputSel;
    unsigned char OutputAlign;
}VPP_VOP_AHD_ASD_CTRL,*PVPP_VOP_AHD_ASD_CTRL;

/*TTL30 control data structure*/
typedef struct VPP_VOP_TTL30_CTRL_T
{
    unsigned int CBlank;
    unsigned char InputSel;
    unsigned char CscMode;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned char ClkPol;
    unsigned char Saturate;
    unsigned char HsHdeSel;
    unsigned char VsVdeSel;
    unsigned char OutputSel;
    unsigned char YCPosSel;
#endif
}VPP_VOP_TTL30_CTRL,*PVPP_VOP_TTL30_CTRL;

/*Dither Algorithm selection.*/
typedef enum VPP_VOP_TTL24_DITHER_ALG
{
    VPP_VOP_DIT_BYPASS_MODE = 0,
    VPP_VOP_PRBS_HPF_ALGORITHM,
    VPP_VOP_ORDERED_DIT_ALGORITHM,
    VPP_VOP_ROUND_AND_TRUNC,
    VPP_VOP_DIT_END

}VPP_VOP_TTL24_DITHER_ALG,*PVPP_VOP_TTL24_DITHER_ALG;

/*TTL24 output mode selection when DNS enable*/
typedef enum VPP_VOP_TTL24_18_24_DNS_ENB
{
    VPP_VOP_YC_16BIT_SEL_TTL24_OP = 0,  // YC 16 bit is selected
    VPP_VOP_YC_20BIT_SEL_TTL24_OP,        // YC 20-bit is selected
    VPP_VOP_YC_24BIT_SEL_TTL24_OP,	       // YC 24-bit is selected
    VPP_VOP_YC_TTL24_MAX

}VPP_VOP_TTL24_18_24_DNS_ENB, *PVPP_VOP_TTL24_18_24_DNS_ENB;

/*TTL24 output mode selection when DNS disable*/
typedef enum VPP_VOP_TTL24_18_24_DNS_DISB
{
    VPP_VOP_RGB_YCBCR_24BIT_SEL   = 0,
    VPP_VOP_RGB_YCBCR_18BIT_SEL   = 1,
    VPP_VOP_RGB_BIT_DISB_MAX

}VPP_VOP_TTL24_18_24_DNS_DISB, *PVPP_VOP_TTL24_18_24_DNS_DISB;

/*Dither selection*/
typedef struct VPP_VOP_TTL24_DITHER_SEL_T
{
    unsigned int Dither;        //Dither algorithm selection
    unsigned int DitMirror;
    unsigned int DitInpRes; 	// Input data width
    unsigned int DitOutRes; 	// Output data width

}VPP_VOP_TTL24_DITHER_SEL,*PVPP_VOP_TTL24_DITHER_SEL;

/*TTL 24 control data structure*/
typedef struct VPP_VOP_TTL24_CTRL_T
{
    unsigned int CBlank;
    unsigned char InputSel;
    unsigned char CscMode;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned char ClkPol;
    unsigned char Saturate;
    unsigned char HsHdeSel;
    unsigned char VsVdeSel;
    unsigned char OutputSel;
    unsigned char YCPosSel;
#else
    VPP_VOP_TTL24_DITHER_SEL  DitherSel;
#endif
}VPP_VOP_TTL24_CTRL,*PVPP_VOP_TTL24_CTRL;

/***************************************************************************************
 * FUNCTION: set HDMI DNS mode
 * PARAMS: DnsMode - HDMI DNS mode
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP HDMI DNS mode values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetHdmiDnsMode(THINVPP_OBJ *vpp_obj, int DnsMode);

/***************************************************************************************
 * FUNCTION: set HDMI parameters
 * PARAMS: pHdmiCtrl - pointer to HDMI control parameters
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP HDMI control values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetHdmiParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_HDMI_CTRL pHdmiCtrl);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_Z2)
/***************************************************************************************
 *  * FUNCTION: set LVDS parameters
 *   * PARAMS: pLvdsCtrl - pointer to LVDS control parameters
 *    * RETURN:  1 - succeed
 *     *                others - failed to load BE VOP LVDS control values to BCM buffer
 *      ***************************************************************************************/
int BE_VOP_SetLvdsParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_LVDS_CTRL pLvdsCtrl);
#endif

/***************************************************************************************
 * FUNCTION: set AHD parameters
 * PARAMS: pAhdCtrl - pointer to AHD control parameters
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP AHD control values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetAhdParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_AHD_ASD_CTRL pAhdCtrl);

/***************************************************************************************
 * FUNCTION: set ASD parameters
 * PARAMS: pAsdCtrl - pointer to ASD control parameters
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP ASD control values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetAsdParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_AHD_ASD_CTRL pAsdCtrl);

/***************************************************************************************
 * FUNCTION: sets output round mode
 * PARAMS: OutputSel - indicates which VOP unit to be loaded(HDMI, AHD, ASD). TTL24 and TTL30 have no round
 *               RndMode - round mode
 * RETURN:  1 - succeed
 *                others - failed to load round register value to BCM buffer or invalid parameters
 ***************************************************************************************/
int BE_VOP_SetRoundMode(THINVPP_OBJ *vpp_obj, int OutputSel, int RndMode);

/***************************************************************************************
 * FUNCTION: load CSC coeffs and offsets to VOP
 * PARAMS: OutputSel - indicates which VOP unit to be loaded(HDMI, AHD, ASD, TTL24, TTL30)
 *               CscMode - CSC mode
 * RETURN:  1 - succeed
 *                others - failed to load CSC coeffs and offsets to BCM buffer
 ***************************************************************************************/
int BE_VOP_LoadCscCoeff(THINVPP_OBJ *vpp_obj, int OutputSel, int CscMode);

/**************************************************************************************
 * FUNCTION: set HDMI/HD/SD encoder clock dividor
 * PARAMS: OutputSel - VOP output ID(VPP_VOP_HDMI, VPP_VOP_AHD, VPP_VOP_ASD)
 *         ClkSel - clock selector
 * RETURN:  1 - succeed
 *          others - failed
 ***************************************************************************************/
int BE_VOP_ClkSelect(THINVPP_OBJ *vpp_obj, int OutputSel, int ClkSel);

#endif
