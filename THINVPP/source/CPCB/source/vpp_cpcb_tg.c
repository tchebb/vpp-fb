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

#define _VPP_CPCB_TG_C_

#include "maddr.h"
#include "vpp.h"

#include "thinvpp_module.h"
#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_cpcb_tg.h"
#include "vpp_cpcb_tg_prv.h"

/***************************************************************************************
 * FUNCTION: load the default register values for CPCB TG block
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int CpcbUnit)
{
    int RetVal = MV_THINVPP_OK;

    CHECK_CPCB_NUM(CpcbUnit);

    /*load all the default registers*/
    if(VPP_CPCB0 == CpcbUnit){
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
        WRITE_REG_DEFAULT_VAL(CPCB0_DB_CTRL, gCpcb0TgDefValues);
#endif
        WRITE_REG_DEFAULT_VAL(CPCB0_MODE, gCpcb0TgDefValues);
        WRITE_REG_DEFAULT_VAL_32BITS(RA_Vpp_cpcb0Clk, gCpcb0TgDefValues);

    }else{

#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
        WRITE_REG_DEFAULT_VAL(CPCB2_DB_CTRL, gCpcb2TgDefValues);
#endif
        WRITE_REG_DEFAULT_VAL(CPCB2_MODE, gCpcb2TgDefValues);
        WRITE_REG_DEFAULT_VAL_32BITS(RA_Vpp_cpcb2Clk, gCpcb2TgDefValues);
    }

    return RetVal;
}


/**************************************************************************************
 * FUNCTION: start the timing generator by set horizontal and vertical total
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *                HVtotal - horizontal and vertical total values
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_SetHVTotal(THINVPP_OBJ *vpp_obj, int CpcbUnit, PVPP_CPCB_TG_HVTOTAL pHVtotal)
{
    unsigned int TotalLow, TotalHigh;
    unsigned int HVTotalAddr;

    CHECK_CPCB_NUM(CpcbUnit);

    /*get VT total register start address*/
    if(VPP_CPCB0 == CpcbUnit)
        HVTotalAddr = vpp_obj->base_addr + (CPCB0_VT_L << 2);
    else if(VPP_CPCB1 == CpcbUnit)
        HVTotalAddr =  vpp_obj->base_addr + (CPCB1_VT_L << 2);
    else
        HVTotalAddr = vpp_obj->base_addr + (CPCB2_VT_L << 2);

    /*set vertical total value field to BCM buffer*/
    TotalLow = GET_LOWEST_BYTE(pHVtotal->VTotal);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, HVTotalAddr, TotalLow);

    TotalHigh = pHVtotal->VTotal >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, HVTotalAddr + 4, TotalHigh);

    /*set horizontal total value field to BCM buffer*/
    TotalLow = GET_LOWEST_BYTE(pHVtotal->HTotal);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, HVTotalAddr + 8, TotalLow);

    TotalHigh = pHVtotal->HTotal >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, HVTotalAddr + 12, TotalHigh);

    return MV_THINVPP_OK;
}

  /**************************************************************************************
 * FUNCTION: set the CPCB TG params
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *                CpcbTgParams - TG params
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_SetParams(THINVPP_OBJ *vpp_obj, int CpcbUnit, PVPP_CPCB_TG_PARAMS pTgParams)
{
    unsigned int Low8bits, High4bits;
    unsigned int VXAddr;

    CHECK_CPCB_NUM(CpcbUnit);

    /*get VX register start adress*/
    if(VPP_CPCB0 == CpcbUnit)
        VXAddr = vpp_obj->base_addr + (CPCB0_VX_L << 2);
    else if(VPP_CPCB1 == CpcbUnit)
        VXAddr =  vpp_obj->base_addr + (CPCB1_VX_L << 2);
    else
        VXAddr = vpp_obj->base_addr + (CPCB2_VX_L << 2);

    /*set horizontal position at which Vertical active data begins field to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pTgParams->Vsampx);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr, Low8bits);

    High4bits = pTgParams->Vsampx >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 4, High4bits);

    /*set frame reset position field  to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pTgParams->FrameReset);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 8, Low8bits);

    High4bits = pTgParams->FrameReset >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 12, High4bits);

    /*set Hsync start position field  to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pTgParams->HSyncStartPos);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 16, Low8bits);

    High4bits = pTgParams->HSyncStartPos >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 20, High4bits);

    /*set Hsync end position field to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pTgParams->HSyncEndPos);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 24, Low8bits);

    High4bits = pTgParams->HSyncEndPos >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 28, High4bits);

    /*set Vsync start position field to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pTgParams->VSyncStartPos);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 32, Low8bits);

    High4bits = pTgParams->VSyncStartPos >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 36, High4bits);

    /*set Vsync end position to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pTgParams->VSyncEndPos);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 40, Low8bits);

    High4bits = pTgParams->VSyncEndPos >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, VXAddr + 44, High4bits);

    return MV_THINVPP_OK;
}

  /**************************************************************************************
 * FUNCTION: set the the window position for one plane in the backend. can be used to disable a plane by setting the window to 0
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *               CpCbPlane - CPCB plane number
 *               WindowPos - plane window position
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_SetPlaneWindow(THINVPP_OBJ *vpp_obj, int CpcbUnit, int CpCbPlane, PVPP_WINDOW pWindowPos)
{
    unsigned int Low8bits, High4bits;
    unsigned int PlaneAddr;

    CHECK_CPCB_NUM(CpcbUnit);

    switch (CpCbPlane) {
        case TG_PLANE0_BASE:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P0_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P0_SX_L << 2);
            else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P0_SX_L << 2);
            break;
        case TG_PLANE1_MAIN:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P1_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P1_SX_L << 2);
            else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P1_SX_L << 2);
            break;
        case TG_PLANE1_MAIN_CROP1:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P1_CR1_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P1_CR1_SX_L << 2);
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM); // B0 CPCB2 has no MAIN CR-1
#else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P1_CR1_SX_L << 2);
#endif
            break;
        case TG_PLANE1_MAIN_CROP2:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P1_CR2_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM); // B0 CPCB1 has no MAIN CR-2
#else
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P1_CR2_SX_L << 2);
#endif
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM); // B0 CPCB2 has no MAIN CR-2
#else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P1_CR2_SX_L << 2);
#endif
            break;
        case TG_PLANE2_PIP:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P2_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P2_SX_L << 2);
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM); // B0 CPCB2 has no PIP
#else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P2_SX_L << 2);
#endif
            break;
        case TG_PLANE2_PIP_CROP1:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P2_CR1_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P2_CR1_SX_L << 2);
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM); // B0 CPCB2 has no PIP CR-1
#else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P2_CR1_SX_L << 2);
#endif
            break;

        // NEW FOR GFX0 PLANE //
        case TG_PLANE3:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P3_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
            {
                printk(KERN_INFO "actually setting pl-3 window\n");
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P3_SX_L << 2);
            }
            else
                return (MV_THINVPP_EBADPARAM); // CPCB2 has no IG/G0 plane
            break;
        case TG_PLANE3_CROP:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P3_CR_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
            {
                printk(KERN_INFO "actually setting pl-3 crop\n");
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P3_CR_SX_L << 2);
            }
            else
                return (MV_THINVPP_EBADPARAM); // CPCB2 has no IG/G0 CR
        // NEW FOR PG PLANE //
        case TG_PLANE3A:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P3A_CR_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
            {
                printk(KERN_INFO "actually setting pla-3 window\n");
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P3A_SX_L << 2);
            }
            else
                return (MV_THINVPP_EBADPARAM); // CPCB2 has no IG/G0 plane
            break;
        case TG_PLANE3A_CROP:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P3A_CR_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
            {
                printk(KERN_INFO "actually setting pla-3 crop\n");
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P3A_CR_SX_L << 2);
            }
            else
                return (MV_THINVPP_EBADPARAM); // CPCB2 has no IG/G0 CR
            break;

        case TG_PLANE4_BASE_BORDER:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P4_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P4_SX_L << 2);
            else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P4_SX_L << 2);
            break;
        case TG_PLANE5_MAIN_BORDER:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P5_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P5_SX_L << 2);
            else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P5_SX_L << 2);
            break;
        case TG_PLANE6_PIP_BORDER:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P6_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P6_SX_L << 2);
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM); // B0 CPCB2 has no PLANE-6
#else
                PlaneAddr = vpp_obj->base_addr + (CPCB2_P6_SX_L << 2);
#endif
            break;
        // NEW for PG and IG/G0 plane border
        case TG_PLANE7_BORDER:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P7_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P7_SX_L << 2);
            else
                return (MV_THINVPP_EBADPARAM); // CPCB2 has no PLANE-7
            break;
        case TG_PLANE7A_BORDER:
            if (VPP_CPCB0 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB0_P7A_SX_L << 2);
            else if (VPP_CPCB1 == CpcbUnit)
                PlaneAddr = vpp_obj->base_addr + (CPCB1_P7A_SX_L << 2);
            else
                return (MV_THINVPP_EBADPARAM); // CPCB2 has no PLANE-7a
            break;

        default:
            return (MV_THINVPP_EBADPARAM);
    }

    /*get horizontal start address low byte*/
    Low8bits = GET_LOWEST_BYTE(pWindowPos->TopLeft.X);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr, Low8bits);

    /*get horizontal start address high byte*/
    High4bits = pWindowPos->TopLeft.X >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 4, High4bits);

    /*set horizontal end address for the plane to BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pWindowPos->BottomRight.X);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 8, Low8bits);

    High4bits = pWindowPos->BottomRight.X >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 12, High4bits);

    if((VPP_CPCB2 == CpcbUnit) && (TG_PLANE5_MAIN_BORDER == CpCbPlane))
        PlaneAddr += 16;

    /*set vertical start address for the planeto BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pWindowPos->TopLeft.Y);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 16, Low8bits);

    High4bits = pWindowPos->TopLeft.Y >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 20, High4bits);

    /*set vertical end address for the planeto BCM buffer*/
    Low8bits = GET_LOWEST_BYTE(pWindowPos->BottomRight.Y);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 24, Low8bits);

    High4bits = pWindowPos->BottomRight.Y >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, PlaneAddr + 28, High4bits);

    return MV_THINVPP_OK;
}

  /**************************************************************************************
 * FUNCTION: set CPCB TG actual clock
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *               ClkSel - CPCB clock selector
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG clock selection to BCM buffer
 ***************************************************************************************/
int CPCB_TG_ClkSelect(THINVPP_OBJ *vpp_obj, int CpcbUnit, int ClkSel)
{
    unsigned int RegAddr;
    int RegValue;

    CHECK_CPCB_NUM(CpcbUnit);

    if((ClkSel < VPP_CPCB_CLK_DISABLE) ||(ClkSel >= VPP_CPCB_CLK_MAX))
        return MV_THINVPP_EBADPARAM;

    RegAddr = vpp_obj->base_addr + RA_Vpp_cpcb0Clk + (CpcbUnit << 2);

    if(VPP_CPCB_CLK_DISABLE == ClkSel){
        RegValue = 0x00;
    }else if(VPP_CPCB_CLK_D3 == ClkSel){
        RegValue = 0x07;
    }else if(VPP_CPCB_CLK_D1 == ClkSel){
        RegValue = 0x04;
    }else{ //x2, x4, x6, x8, x12
        RegValue = (ClkSel << 3) | 0x05;
    }

    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, RegValue);

    return MV_THINVPP_OK;
}
