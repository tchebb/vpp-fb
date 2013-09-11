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

#define _FE_DEINT_C_

#include "thinvpp_common.h"
#include "thinvpp_api.h"
#include "thinvpp_module.h"
#include "thinvpp_bcmbuf.h"

#include "maddr.h"
#include "vpp.h"

#include "vpp_fe_deint.h"
#include "vpp_fe_deintprv.h"
#include "vpp_fe_deintcfg.h"

/**********************************************************************
 * FUNCTION: This API sets the Vp Read/Write client pixel/DMA size
 *
 * PARAMS: pVpClientSize - Pointer to VP client pixel/DMA size
 * RETURN: 1 - succeed
 *         others - failed to load lookup table to BCM buffer
 **********************************************************************/
int FE_DEINT_SetVpDeintClientSize(THINVPP_OBJ* vpp_obj, PVPP_VP_CLIENT_SIZE pVpClientSize, int training)
{
    unsigned int TotalInpPix, TotalOutPix;
    unsigned int TotPixForWriteClient, TotPixForReadClient;

    TotalInpPix = pVpClientSize->ivRes * pVpClientSize->ihRes;

    if (!pVpClientSize->IsProgressive)
        TotalOutPix = 2 * pVpClientSize->ivRes * pVpClientSize->ihRes;
    else
        TotalOutPix = pVpClientSize->ivRes * pVpClientSize->ihRes;

    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr+RA_Vpp_vpIn_pix, TotalInpPix);
    if (training)
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr+RA_Vpp_vpOut_pix, 100);
    else
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr+RA_Vpp_vpOut_pix, TotalOutPix);

    TotPixForWriteClient = (pVpClientSize->ivRes + 1) * pVpClientSize->ihRes;

    TotPixForReadClient = (TotPixForWriteClient * 26 + 63) / 64;

    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr+RA_Vpp_diW_pix, TotPixForWriteClient);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr+RA_Vpp_diR_word, TotPixForReadClient);

    return MV_THINVPP_OK;
}
