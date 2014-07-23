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

#ifndef VPP_FRS_SCL_H
#define VPP_FRS_SCL_H

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/**********************************************************************
*data structure definition for FRC SCL block driver                                                  *
***********************************************************************/
/*Enum for horizontal scaler position*/
typedef enum VPP_SCL_HSCALER_POS
{
    VPP_SCL_HSCALE_ABSENT = 0,
    VPP_SCL_HSCALE_BEFORE = 2,
    VPP_SCL_HSCALE_AFTER,
    VPP_SCL_HSCALE_AUTO
}VPP_SCL_HSCALER_POS;

/*Enum for input and  output bit mode*/
typedef enum VPP_SCL_IO_BITMODE
{
    VPP_SCL_16IN_16OUT = 0,
    VPP_SCL_24IN_16OUT,
    VPP_SCL_16IN_24OUT,
    VPP_SCL_24IN_24OUT
}VPP_SCL_IO_BITMODE;

/*Enum for CSC mode in OSD formatter*/
typedef enum VPP_SCL_CSC_MODES
{
    VPP_SCL_CSC_BYPASS_MODE = 0,
    VPP_SCL_CSC_RGB_TO_YUV_709,
    VPP_SCL_CSC_RGB_TO_YUV_601,
    VPP_SCL_CSC_sRGB_TO_YUV_709,
    VPP_SCL_CSC_sRGB_TO_YUV_601,
    VPP_SCL_CSC_MAX_MODES
} VPP_SCL_CSC_MODES;

/*Enum for input data format of OSD formatter*/
typedef enum VPP_SCL_OSD_CTRL
{
    VPP_SCL_32BIT_8888_OSD = 2,
    VPP_SCL_24BIT_888_OSD = 8,
    VPP_SCL_OSD_CTRL_MAX
}VPP_SCL_OSD_CTRL;

/*Enum for scaler to CPCB switch*/
typedef enum VPP_SCL_BE_SWITCH
{
    VPP_SCL_BE_CPCB0_PATH0 = 0,
    VPP_SCL_BE_CPCB0_PATH1,
    VPP_SCL_BE_CPCB0_PATH2,
    VPP_SCL_BE_CPCB0_PATH3,
    VPP_SCL_BE_CPCB1_PATH0,
    VPP_SCL_BE_CPCB1_PATH1,
    VPP_SCL_BE_CPCB1_PATH2,
    VPP_SCL_BE_CPCB1_PATH3,
    VPP_SCL_BE_CPCB2_PATH0,
    VPP_SCL_BE_CPCB2_PATH1,
    VPP_SCL_BE_SWITCH_MAX
}VPP_SCL_BE_SWITCH;

/*sacler coefficient mode*/
typedef enum VPP_FRC_SCL_COEFF_MODE_T
{

//Hred
	COEFF_H_PSHARP,
	COEFF_H_BYPASS,
	COEFF_HRED_BY_1_5,
	COEFF_HRED_BY_2_7,
//Vred
	COEFF_V_PSHARP,
	COEFF_V_BYPASS,
	COEFF_VRED_BY_1_5,
	COEFF_VRED_BY_1_5_5taps,
	COEFF_VRED_BY_1_5_3taps,
	COEFF_VRED_BY_2_25,
	COEFF_MAX
}VPP_FRC_SCL_COEFF_MODE, *PVPP_FRC_SCL_COEFF_MODE;

/*FRC input resolution*/
typedef struct VPP_FRC_RES_T
{
    unsigned int  HRes;
    unsigned int  VRes;
} VPP_FRC_RES, *PVPP_FRC_RES;

/**********************************************************************
*Function definition for CPCB FRC SCL block driver                                                 *
***********************************************************************/

/***************************************************************************************
 * FUNCTION: load the default register values to FRC SCL the unit
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int UnitNum);

/***************************************************************************************
 * FUNCTION: set HV resolution to FRC unit.
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4)
 *               pFrcRes - pointer to the resolution data stucture
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetFrcParams(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_FRC_RES pFrcRes);

/***************************************************************************************
 * FUNCTION: set delay between DE  to line reset.
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4)
 *               DeLrstDelay -delay value
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetDeLrstDelay(THINVPP_OBJ *vpp_obj, int UnitNum, unsigned int DeLrstDelay);

/***************************************************************************************
 * FUNCTION: set control information and I&O resolution to scaler
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4)
 *               pIORes -pointer to I&O resolution
 *               pSclCtrl - pointer to scaler control information
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetSclCtrlParams(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_SCL_RES pIORes, PVPP_SCL_CTRL pSclCtrl);

/***************************************************************************************
 * FUNCTION: set non linear scaler parameters
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4)
 *               pIORes -pointer to I&O resolution
 *               CenterFrac - central undistorted franction of output frame
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetNLParams(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_SCL_RES pIORes, unsigned char CenterFrac);

int FRC_SCL_SetSclCoeff(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_SCL_RES pIORes, PVPP_SCL_CTRL pSclCtrl);

/***************************************************************************************
 * FUNCTION: load the default register values to SCL back end switch
 * PARAMS: void
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_LoadSwDefault(THINVPP_OBJ *vpp_obj);

/***************************************************************************************
 * FUNCTION: set scaler to CPCB path route
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4)
 *               BESwitch - CPCB unit and path selection
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetBeSwitch(THINVPP_OBJ *vpp_obj, int UnitNum, int BESwitch);

/***************************************************************************************
 * FUNCTION: set BE FIFO for loopback
 * PARAMS: pCpcb0Tot - CPCB0 output total resolution
 *               pCpcb0Res - CPCB0 active resolution
 * RETURN:  1 - succeed
 *                others - failed to load CPCB BE FIFO values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetBeFifo(THINVPP_OBJ *vpp_obj, PVPP_FRC_RES pCpcb0Tot, PVPP_FRC_RES pCpcb0Res);

/***************************************************************************************
 * FUNCTION: set main or PIP scaler working mode
 * PARAMS: UnitNum - unit number(0, 1)
 *               WorkMode -1: off-line mode 0: in-line mode
 * RETURN:  1 - succeed
 *                others - failed to load register to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetWorkMode(THINVPP_OBJ *vpp_obj, int UnitNum, int WorkMode);

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
/***************************************************************************************
 * FUNCTION: control Hscaler chopping
 * PARAMS: UnitNum - unit number(0, 1)
 *         Value - 0, 1, 2, 3
 * RETURN:  1 - succeed
 *                others - failed to load register to BCM buffer
 ***************************************************************************************/
int FRC_SCL_ChopCtrl(THINVPP_OBJ *vpp_obj, int UnitNum, int Value);
#endif

#endif
