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

#define _VPP_CPCB_FGG_C_

#include "maddr.h"

#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_cpcb_fgg.h"
#include "vpp_cpcb_fgg_prv.h"


#if 0
/***************************************************************************************
 * FUNCTION: load the default register values of CPCB0 FGG block
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_FGG_LoadDefaultVal(THINVPP_OBJ *vpp_obj)
{
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_CTRL, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_GAIN, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_TEMP, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_LTH_L, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_LTH_H, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_HTH_L, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_FGG_HTH_H, gCpcb0FggDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_MISC_CTRL, gCpcb0FggDefValues);

    return MV_THINVPP_OK;
}
#endif

/***************************************************************************************
 * FUNCTION: set Feedback mode of CPCB0
 * PARAMS: FeedbackPath - CPCB0 feedback mode
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_SetFeedbackPath(THINVPP_OBJ *vpp_obj, int FeedbackPath)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    RegAddr = vpp_obj->base_addr + (CPCB0_MISC_CTRL << 2);

    /*write data to BCM bufer */
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, FeedbackPath)))
        return RetVal;

    return RetVal;
}
