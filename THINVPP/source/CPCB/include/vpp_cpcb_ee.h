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

#ifndef _VPP_CPCB_EE_H_
#define _VPP_CPCB_EE_H_

#include "thinvpp_api.h"
#include "thinvpp_module.h"

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/**********************************************************************
*Type definition for FE detail EE                                                                             *
***********************************************************************/
/*enum for motion adaptive LPF's(Low Pass Filter) mode. (LPF_CTRL)*/
typedef enum VPP_FE_DET_LPF_MODE
{
    VPP_FE_DET_LPF_OUTPUT_DISABLED               = 0x00,   // LPF output disabled
    VPP_FE_DET_MOTION_ADAPTIVE_LPF_FILM_MODE     = 0x01,   // Film mode status is high
    VPP_FE_DET_MOTION_ADAPTIVE_LPF_NON_FILM_MODE = 0x02,   // Film mode status is ignored
    VPP_FE_DET_LPF_OUTPUT_ENABLED                = 0x03,   // Enables LPF output.
    VPP_FE_DET_LPF_OUTPUT_END
}VPP_FE_DET_LPF_MODE, *PVPP_FE_DET_LPF_MODE;

/*enum for EE pre-set level*/
typedef enum VPP_DET_PRESET_LEVEL
{
    VPP_FE_DET_TH_LOW = 0,
    VPP_FE_DET_TH_MEDIUM,
    VPP_FE_DET_TH_HIGH,
    VPP_FE_DET_TH_NONE
}VPP_DET_PRESET_LEVEL,*PVPP_DET_PRESET_LEVEL;
#endif

/**********************************************************************
*Type definition for CPCB EE                                                                               *
***********************************************************************/
/*struct for CPCB EE control parameters*/
typedef struct VPP_CPCB_EE_CTRL_PARAMS
{
    unsigned char LtiGain;
    unsigned char CtiGain;
}VPP_CPCB_EE_CTRL_PARAMS, *PVPP_CPCB_EE_CTRL_PARAMS;

/**********************************************************************
*Function definition for CPCB EE block driver                                                           *
***********************************************************************/

/***************************************************************************************
 * FUNCTION: load the default register values of FE detail EE and CPCB EE block
 * PARAMS: None.
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_EE_LoadDefaultVal(THINVPP_OBJ *vpp_obj);

#endif/*_VPP_CPCB_EE_H_*/
