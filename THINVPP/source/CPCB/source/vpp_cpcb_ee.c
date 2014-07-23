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

#define VPP_CPCB_EE_C

#include "maddr.h"

#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_cpcb_ee.h"
#include "vpp_cpcb_ee_prv.h"

/***************************************************************************************
 * FUNCTION: load the default register values of FE detail EE and CPCB EE block
 * PARAMS: None.
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_EE_LoadDefaultVal(THINVPP_OBJ *vpp_obj)
{
    int RetVal = MV_THINVPP_OK;

    /*load CPCB0 EE default vaules*/
    WRITE_REG_DEFAULT_VAL(CPCB0_EE0_CTRL, gCpcb0EeDefValues);
    WRITE_REG_DEFAULT_VAL(CPCB0_EE1_CTRL, gCpcb0EeDefValues);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    /*load FE detail EE default vaules*/
    WRITE_REG_DEFAULT_VAL(DET_CTRL, gFeDetDefValues);
#endif

    return RetVal;
}
