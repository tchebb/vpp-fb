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

#define _VPP_SCL_C_

#include "thinvpp_module.h"
#include "vpp_frc_scl.h"
#include "vpp_fe_dlr.h"

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
#include "vpp.h"
#endif

/*******************************************************************
 * FUNCTION: Reset all VPP SCL blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_SCL_Reset(THINVPP_OBJ *vpp_obj)
{
    /* reset FRC-SCLs */
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    VPP_REG_WRITE32(RA_Vpp_SCL_CLKEN_CTRL, 0x3F); // disable data enable signal checking for SCL fifo reading
#else
    VPP_REG_WRITE32(RA_Vpp_SCL_CLKEN_CTRL, 0x1F); // disable data enable signal checking for SCL fifo reading
#endif
#endif

#if VPPFB_ENABLE_MAIN
    FE_DLR_LoadDefaultVal(vpp_obj, VPP_FE_DLR_CHANNEL_MAIN);
    FRC_SCL_LoadDefaultVal(vpp_obj, VPP_FRC_SCL_MAIN);
#else
    FE_DLR_LoadDefaultVal(vpp_obj, VPP_FE_DLR_CHANNEL_PIP);
    FRC_SCL_LoadDefaultVal(vpp_obj, VPP_FRC_SCL_PIP);
#endif
    FE_DLR_LoadDefaultVal(vpp_obj, VPP_FE_DLR_CHANNEL_IG);
    FRC_SCL_LoadDefaultVal(vpp_obj, VPP_FRC_SCL_OSD);

    FE_DLR_LoadDefaultVal(vpp_obj, VPP_FE_DLR_CHANNEL_OFFLINE);
    FRC_SCL_LoadDefaultVal(vpp_obj, VPP_FRC_SCL_BE);



    /* reset SW BE switch */
    FRC_SCL_LoadSwDefault(vpp_obj);

    return (MV_THINVPP_OK);
}


/**********************************************************************
 * FUNCTION: initialize all VPP SCL blocks according to configuration
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 *********************************************************************/
int THINVPP_SCL_Config(THINVPP_OBJ *vpp_obj)
{
#if VPPFB_ENABLE_MAIN
    if (vpp_obj->chan[CHAN_MAIN].dvID != DV_INVALID){
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_MAIN_R, 1);
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_MAIN_W, 0);
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_MAIN_R, 0);

        FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_MAIN);

        /* config FRC-SCLs */
        vpp_obj->chan[CHAN_MAIN].scl_in_out_mode = 0; /* 16-bit input & 16-bit output */
        FRC_SCL_SetBeSwitch(vpp_obj, CHAN_MAIN, vpp_obj->chan[CHAN_MAIN].dvID);
    }
#else
    if (vpp_obj->chan[CHAN_PIP].dvID != DV_INVALID){
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_PIP_R, 1);
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_PIP_W, 0);
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_PIP_R, 0);

        FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_PIP);

        /* config FRC-SCLs */
        vpp_obj->chan[CHAN_PIP].scl_in_out_mode = 0; /* 16-bit input & 16-bit output */
        FRC_SCL_SetBeSwitch(vpp_obj, CHAN_PIP, vpp_obj->chan[CHAN_PIP].dvID);
    }
#endif
    if (vpp_obj->chan[CHAN_AUX].dvID != DV_INVALID){
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_AUX_R, 1);
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_AUX_W, 0);
        FE_DLR_ClearOffLineChannel(vpp_obj, VPP_FE_DLR_OFFLINE_AUX_R, 0);

        vpp_obj->chan[CHAN_AUX].scl_in_out_mode = 1; /* 24-bit input & 16-bit output */
        /* no switch setting needed for AUX channel in B0 */
        /* because it is hard-wired to CPCB-3 */
    }

    if (vpp_obj->chan[CHAN_GFX0].dvID != DV_INVALID) {
        FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_IG);
        vpp_obj->chan[CHAN_GFX0].scl_in_out_mode = 1;
        FRC_SCL_SetBeSwitch(vpp_obj, CHAN_GFX0, vpp_obj->chan[CHAN_GFX0].dvID);
    }
/*
    FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_PG);
    FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_CURSOR);
    FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_MOSD);
    FE_DLR_ClearChannel(vpp_obj, VPP_FE_DLR_CHANNEL_BG);
*/
    return (MV_THINVPP_OK);
}

/***************************************************************************************
 * FUNCTION: set BE FIFO for loopback
 * PARAMS: pCpcb0Tot - CPCB0 output total resolution
 *               pCpcb0Res - CPCB0 active resolution
 * RETURN:  1 - succeed
 *                others - failed to load CPCB BE FIFO values to BCM buffer
 ***************************************************************************************/
int THINVPP_SCL_SetBeFifo(THINVPP_OBJ *vpp_obj, PVPP_FRC_RES pCpcb0Tot, PVPP_FRC_RES pCpcb0Res)
{
    FRC_SCL_SetBeFifo(vpp_obj, pCpcb0Tot, pCpcb0Res);

    return (MV_THINVPP_OK);
}
