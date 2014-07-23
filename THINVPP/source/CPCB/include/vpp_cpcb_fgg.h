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

#ifndef _VPP_CPCB_FGG_H_
#define _VPP_CPCB_FGG_H_

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/**********************************************************************
*data structure definition for CPCB FGG block driver                                                *
***********************************************************************/
typedef struct VPP_CPCB_FGG_CTRL_T
{
    unsigned char	MainEnable;
    unsigned char	PipEnable;
    unsigned char	AdaptiveMode;
}VPP_CPCB_FGG_CTRL, *PVPP_CPCB_FGG_CTRL;

typedef struct VPP_CPCB_FGG_CTRL_PARAMS_T
{
    unsigned int	FggGain;
    unsigned int	FggTemp;
    unsigned int	FggLth;
    unsigned int	FggHth;
}VPP_CPCB_FGG_CTRL_PARAMS, *PVPP_CPCB_FGG_CTRL_PARAMS;

typedef enum VPP_CPCB_FEEDBACK_MODE_T
{
    VPP_CPCB_OVL_TO_FE = 0,
    VPP_CPCB_CMU_TO_FE,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    VPP_CPCB_MAIN_EE_OUT_TO_FE,
#endif
    VPP_CPCB_PRG_OUT_TO_FE,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    VPP_CPCB_PIP_EE_OUT_TO_FE,
#endif
    VPP_CPCB_FEEDBACK_MODE_MAX
}VPP_CPCB_FEEDBACK_MODE;

/**********************************************************************
*Function definition for CPCB FGG block driver                                                        *
***********************************************************************/

/***************************************************************************************
 * FUNCTION: set Feedback mode of CPCB0
 * PARAMS: FeedbackPath - CPCB0 feedback mode
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_SetFeedbackPath(THINVPP_OBJ *vpp_obj, int FeedbackPath);

#endif /*_VPP_CPCB_FGG_H_*/
