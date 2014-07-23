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

#ifndef _VPP_FE_DLR_PRV_H_
#define _VPP_FE_DLR_PRV_H_

#include "vpp.h"

/****************************************************************************************
*macro for FE dummy TG, only set offset plus input res dynamically, others are set in loading defult values*
*****************************************************************************************/
/*the offset plus with input resolution to set dummy TG size*/
#if (defined(BERLIN_A0_HACK) && (BERLIN_CHIP_VERSION < BERLIN_B_0))
#define VPP_FE_DUMMY_TG_SIZE_H_OFF_P 10
#else
#define VPP_FE_DUMMY_TG_SIZE_H_OFF_P 20
#endif
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
#define VPP_FE_DUMMY_TG_SIZE_V_OFF_P 10
#else
#define VPP_FE_DUMMY_TG_SIZE_V_OFF_P 6
#endif
#define VPP_FE_DUMMY_TG_SIZE_H_OFF_I 22
#define VPP_FE_DUMMY_TG_SIZE_V_OFF_I 10

#define VPP_FE_DUMMY_TG_SENSIO_H_OFF_P 100
#define VPP_FE_DUMMY_TG_SENSIO_V_OFF_P 12
#define VPP_FE_DUMMY_TG_SENSIO_H_OFF_I 102
#define VPP_FE_DUMMY_TG_SENSIO_V_OFF_I 12

/*dummy TG HSync*/
#define VPP_FE_DUMMY_TG_HS_FE 1
#define VPP_FE_DUMMY_TG_HS_BE 3

/*dummy TG HBlank*/
#if (defined(BERLIN_A0_HACK) && (BERLIN_CHIP_VERSION < BERLIN_B_0))
#define VPP_FE_DUMMY_TG_HB_FE_OFF 5 //VPP_FE_DUMMY_TG_HB_BE + 1
#define VPP_FE_DUMMY_TG_HB_BE     4 //VPP_FE_DUMMY_TG_HS_BE + 4
#else
#define VPP_FE_DUMMY_TG_HB_FE_OFF 8 //VPP_FE_DUMMY_TG_HB_BE + 1
#define VPP_FE_DUMMY_TG_HB_BE     7 //VPP_FE_DUMMY_TG_HS_BE + 4
#endif

#define VPP_FE_DUMMY_TG_SENSIO_HB_FE_OFF 50 //VPP_FE_DUMMY_TG_HB_BE + 1
#define VPP_FE_DUMMY_TG_SENSIO_HB_BE     49 //VPP_FE_DUMMY_TG_HS_BE + 4
/*dummy TG VSync0*/
#define VPP_FE_DUMMY_TG_VS0_FE 1
#define VPP_FE_DUMMY_TG_VS0_BE 2

/*dummy TG VBlank*/
#define VPP_FE_DUMMY_TG_VB0_FE_OFF 3//VPP_FE_DUMMY_TG_VS0_BE + 1
#define VPP_FE_DUMMY_TG_VB0_BE     2 //VPP_FE_DUMMY_TG_VS0_BE

#define VPP_FE_DLR_OSD_CLUT_NUM_MAX 256

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/**********************************************************************
*register offset definitions in local block buffer                                                        *
***********************************************************************/
#define VPP_FE_DLR_CSC_OFFSET 35
#define VPP_FE_DLR_TG_OFFSET 35 + 24
#define VPP_FE_DLR_TG_VB0_OFFSET 35 + 24 + 4
#define VPP_FE_DLR_MAINW_OFFSET 35 + 24 + 5
#define VPP_FE_DLR_MAINW_PIX_OFFSET 35 + 24 + 5 +6
#define VPP_FE_DLR_VP_CLKEN_OFFSET 35 + 24 + 5 + 12

/*macro definitions for CSC*/
#define VPP_FE_DLR_MAX_COEFF_INDEX 9
#define VPP_FE_DLR_MAX_OFFSET_INDEX 3

/*array to store register offset for each channel*/
const unsigned int VppFeDlrRegOff[] = {
           RA_LDR_BG,
           RA_LDR_MAIN,
           RA_LDR_PIP,
           RA_LDR_PG,
           RA_LDR_IG,
           RA_LDR_CURSOR,
           RA_LDR_MOSD
};

/*******************************************************************************
*default register values of VPP FE data loader block,                          *
********************************************************************************/
/*default register values for B0*/
const unsigned int VppFeDlr[] = {
                       /*BG channel dataloader*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*MAIN channel dataloader*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*PIP channel dataloader*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*PG channel dataloader*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*IG channel dataloader*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*CURSOR channel dataloader plane register*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*MOSD channel dataloader*/
                       0x07800438,//RA_PLANE_SIZE         H:1920   V:1080
                       0x00200000,//RA_PLANE_CROP
                       0x00000000,//RA_PLANE_FORMAT
                       0x00000000,//RA_PLANE_START
                       0x00000000,//RA_PLANE_CLEAR

                       /*CURSOR channel dataloader CSC register*/
                       0x00000200,//RA_CSC_const_C0
                       0x00000000,//RA_CSC_const_C1
                       0x00000000,//RA_CSC_const_C2
                       0x00000000,//RA_CSC_const_C3
                       0x00000200,//RA_CSC_const_C4
                       0x00000000,//RA_CSC_const_C5
                       0x00000000,//RA_CSC_const_C6
                       0x00000000,//RA_CSC_const_C7
                       0x00000200,//RA_CSC_const_C8

                       0x00000000,//RA_CSC_off_A0
                       0x00000000,//RA_CSC_off_A1
                       0x00000000,//RA_CSC_off_A2

                       /*MOSD channel dataloader CSC register*/
                       0x00000200,//RA_CSC_const_C0
                       0x00000000,//RA_CSC_const_C1
                       0x00000000,//RA_CSC_const_C2
                       0x00000000,//RA_CSC_const_C3
                       0x00000200,//RA_CSC_const_C4
                       0x00000000,//RA_CSC_const_C5
                       0x00000000,//RA_CSC_const_C6
                       0x00000000,//RA_CSC_const_C7
                       0x00000200,//RA_CSC_const_C8

                       0x00000000,//RA_CSC_off_A0
                       0x00000000,//RA_CSC_off_A1
                       0x00000000,//RA_CSC_off_A2

                       /*dummy TG*/
                       0x08AC046B,//RA_TG_SIZE   H:2200+20   V:1125+6
                       0x00030001,//RA_TG_HS     BE:3 	     FE:1
                       0x000708A0,//RA_TG_HB     BE:7 	     FE:2200+8
                       0x00020001,//RA_TG_VS0    BE:2        EF:1
                       0x00020468,//RA_TG_VB0   BE:2        FE:1125+3//values with 2200 or 1125 need be set dynamically

                       /*new registers for start offline dataloader channel*/
                       0x00000000,//RA_Vpp_mainW
                       0x00000000,//RA_Vpp_mainR
                       0x00000000,//RA_Vpp_pipW
                       0x00000000,//RA_Vpp_pipR
                       0x00000000,//RA_Vpp_auxW
                       0x00000000,//RA_Vpp_auxR

                       0x00000064,//RA_Vpp_mainW_pix
                       0x00000064,//RA_Vpp_mainR_word
                       0x00000064,//RA_Vpp_pipW_pix
                       0x00000064,//RA_Vpp_pipR_word
                       0x00000064,//RA_Vpp_auxW_pix
                       0x00000064,//RA_Vpp_auxR_word

                       0x00000000};//RA_Vpp_VP_CLKEN_CTRL
#endif//#if defined(BERLIN)
#endif//#ifndef _VPP_FE_DLR_PRV_H_
