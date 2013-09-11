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

#define _VPP_BE_VOP_C_

#include "maddr.h"
#include "vpp.h"
#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_be_vop.h"
#include "vpp_be_vop_prv.h"

/***************************************************************************************
 * FUNCTION: set HDMI DNS mode
 * PARAMS: DnsMode - HDMI DNS mode
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP HDMI DNS mode values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetHdmiDnsMode(THINVPP_OBJ *vpp_obj, int DnsMode)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    /*get register address of VOP HDMI MODE*/
    RegAddr = vpp_obj->base_addr + (VOP_HDMI_MODE << 2);

    /*set HDMI mode to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, DnsMode)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set HDMI parameters
 * PARAMS: pHdmiCtrl - pointer to HDMI control parameters
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP HDMI control values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetHdmiParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_HDMI_CTRL pHdmiCtrl)
{
    unsigned int LowBits, HighBits;

    /*set chroma blank low byte to BCM buffer*/
    LowBits = GET_LOWEST_BYTE(pHdmiCtrl->CBlank);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_HDMI_CBLANK_L << 2), LowBits);

    /*set chroma blank high bits to BCM buffer*/
    HighBits = pHdmiCtrl->CBlank >> 8;
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_HDMI_CBLANK_H << 2), HighBits);

    /* set HDMI alignment */
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_HDMI_ALIGN << 2), pHdmiCtrl->OutputAlign);

    /*set HDMI input select to BCM buffer*/
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_HDMI_SEL << 2), pHdmiCtrl->InputSel);

    return MV_THINVPP_OK;
}

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_Z2)
/***************************************************************************************
 *  * FUNCTION: set LVDS parameters
 *   * PARAMS: pLvdsCtrl - pointer to LVDS control parameters
 *    * RETURN:  1 - succeed
 *     *                others - failed to load BE VOP LVDS control values to BCM buffer
 *      ***************************************************************************************/
int BE_VOP_SetLvdsParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_LVDS_CTRL pLvdsCtrl)
{

#if defined(LVDS_DEBUG_MODE) &&(LVDS_DEBUG_MODE==5)
    printf("---------- In SetLvdsParams ----------\n");
    printf("Input=0x%x, OutputAlign=0x%x\n", pLvdsCtrl->InputSel, pLvdsCtrl->OutputAlign);
#endif
    /*set HDMI input select to BCM buffer*/
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + ((VOP_TTL_BASE + VOP_LVDS_SEL) << 2), pLvdsCtrl->InputSel);

    /* set HDMI alignment */
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + ((VOP_TTL_BASE + VDOP_TTL_FRMT_0) << 2), pLvdsCtrl->OutputAlign);

    return MV_THINVPP_OK;
}
#endif


/***************************************************************************************
 * FUNCTION: set AHD parameters
 * PARAMS: pAhdCtrl - pointer to AHD control parameters
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP AHD control values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetAhdParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_AHD_ASD_CTRL pAhdCtrl)
{
    /* set AHD alignment */
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_AHD_ALIGN << 2), pAhdCtrl->OutputAlign);

    /*set AHD input select to BCM buffer*/
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_AHD_SEL << 2), pAhdCtrl->InputSel);

    return MV_THINVPP_OK;
}

/***************************************************************************************
 * FUNCTION: set ASD parameters
 * PARAMS: pAsdCtrl - pointer to ASD control parameters
 * RETURN:  1 - succeed
 *                others - failed to load BE VOP ASD control values to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetAsdParams(THINVPP_OBJ *vpp_obj, PVPP_VOP_AHD_ASD_CTRL pAsdCtrl)
{
    /* set ASD alignment */
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_ASD_ALIGN << 2), pAsdCtrl->OutputAlign);

    /*set ASD input select to BCM buffer*/
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (VOP_ASD_SEL << 2), pAsdCtrl->InputSel);

    return MV_THINVPP_OK;
}

/***************************************************************************************
 * FUNCTION: sets output round mode
 * PARAMS: OutputSel - indicates which VOP unit to be loaded(HDMI, AHD, ASD). TTL24 and TTL30 have no round
 *               RndMode - round mode
 * RETURN:  1 - succeed
 *                others - failed to load round register value to BCM buffer or invalid parameters
 ***************************************************************************************/
int BE_VOP_SetRoundMode(THINVPP_OBJ *vpp_obj, int OutputSel, int RndMode)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    /*get register address of VOP ROUND*/
    switch(OutputSel){
        case VPP_VOP_HDMI:
            RegAddr = vpp_obj->base_addr + (VOP_HDMI_RND << 2);
            break;
        case VPP_VOP_AHD:
            RegAddr = vpp_obj->base_addr + (VOP_AHD_RND << 2);
            break;
        case VPP_VOP_ASD:
            RegAddr = vpp_obj->base_addr + (VOP_ASD_RND << 2);
            break;
        default:
            /*TTL always outputs 8-bit data*/
            return MV_THINVPP_EBADPARAM;
    }

    /*set round register value to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, RndMode)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: load CSC coeffs and offsets to VOP
 * PARAMS: OutputSel - indicates which VOP unit to be loaded(HDMI, AHD, ASD, TTL24, TTL30)
 *               CscMode - CSC mode
 * RETURN:  1 - succeed
 *                others - failed to load CSC coeffs and offsets to BCM buffer
 ***************************************************************************************/
int BE_VOP_LoadCscCoeff(THINVPP_OBJ *vpp_obj, int OutputSel, int CscMode)
{
    unsigned int RegAddr;
    unsigned int LowBits, HighBits;
    int Count;
    int RetVal = MV_THINVPP_OK;

    if((OutputSel < VPP_VOP_AHD) || (OutputSel >= VPP_VOP_OUTPUT_MAX))
        return MV_THINVPP_EBADPARAM;

    if((CscMode < VPP_VOP_CSC_BYPASS_MODE) || (CscMode > VPP_VOP_CSC_MAX_MODES))
        return MV_THINVPP_EBADPARAM;

    /*no need to change CSC coeffs and offsets*/
    if(CscMode == VPP_VOP_CSC_MODES_NO_CHANGE)
        return MV_THINVPP_OK;

    /*get register address of VOP CSC coefficient 0 register*/
    RegAddr = vpp_obj->base_addr  + ((VOP_AHD_C0_L + VPP_VOP_CSC_REG_NUM * OutputSel) << 2);

    /*put all CSC coeffs into local buffer and BCM buffer*/
    for(Count=0; Count<VPP_VOP_CSC_MAX_COEFF_INDEX; Count++){
        /*get low 8 bits*/
        LowBits = GET_LOWEST_BYTE(VppVopCscCoeff[CscMode][Count]);

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, LowBits)))
             return RetVal;

        /*get high 4 bits*/
        HighBits = VppVopCscCoeff[CscMode][Count] >> 8;

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, HighBits)))
         return RetVal;

        /*update address*/
        RegAddr += 8;
    }

    /*put all CSC coeffs into local buffer and BCM buffer*/
    for(Count=0; Count<VPP_VOP_CSC_MAX_OFFSET_INDEX; Count++){
        /*get low 8 bits*/
        LowBits = GET_LOWEST_BYTE(VppVopCscOffset[CscMode][Count]);

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, LowBits)))
             return RetVal;

        /*get high 8 bits*/
        HighBits = VppVopCscOffset[CscMode][Count] >> 8;

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, HighBits)))
         return RetVal;

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
        /*get msb 2 bits*/
        HighBits = VppVopCscOffset[CscMode][Count] >> 16;

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8, HighBits)))
         return RetVal;

        /*update address*/
        RegAddr += 12;
#else
        /*update address*/
        RegAddr += 8;
#endif
    }

    return RetVal;
}

#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
/***************************************************************************************
 * FUNCTION: set DV0 control
 * PARAMS: SignalSel - 1 for HVSync, 0 for HVDE
 *               Order - components order
 * RETURN:  1 - succeed
 *                others - failed to load DV0 control to BCM buffer
 ***************************************************************************************/
int BE_VOP_SetDv0Ctrl(THINVPP_OBJ *vpp_obj, int SignalSel, int Order)
{
    unsigned int RegVal;
    int RetVal = MV_THINVPP_OK;

    RegVal = SignalSel + (SignalSel << 1) + (Order << 2);

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_DV0_CTRL, RegVal)))
         return RetVal;

    return RetVal;
}

#else

/**************************************************************************************
 * FUNCTION: set HDMI/HD/SD encoder clock dividor
 * PARAMS: OutputSel - VOP output ID(VPP_VOP_HDMI, VPP_VOP_AHD, VPP_VOP_ASD)
 *         ClkSel - clock selector
 * RETURN:  1 - succeed
 *          others - failed
 ***************************************************************************************/
int BE_VOP_ClkSelect(THINVPP_OBJ *vpp_obj, int OutputSel, int ClkSel)
{
    unsigned int RegAddr;
    int RegValue;

    if((ClkSel < VPP_VOP_CLK_DISABLE) ||(ClkSel >= VPP_VOP_CLK_MAX))
        return MV_THINVPP_EBADPARAM;

    /*get register address of VOP clock dividor */
    switch(OutputSel){
        case VPP_VOP_HDMI:
            RegAddr = vpp_obj->base_addr + (VOP_HDMI_CLKX_CTRL << 2);
            break;
        case VPP_VOP_AHD:
            RegAddr = vpp_obj->base_addr + (VOP_AHD_CLKX_CTRL << 2);
            break;
        case VPP_VOP_ASD:
            RegAddr = vpp_obj->base_addr + (VOP_ASD_CLKX_CTRL << 2);
            break;
        default:
            return MV_THINVPP_EBADPARAM;
    }

    if(VPP_VOP_CLK_DISABLE == ClkSel){
        RegValue = 0x00;
    }else if(VPP_VOP_CLK_D3 == ClkSel){
        RegValue = 0x07;
    }else if(VPP_VOP_CLK_D1 == ClkSel){
        RegValue = 0x04;
    }else{ //x2, x4, x6, x8, x12
        RegValue = (ClkSel << 3) | 0x05;
    }

    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, RegValue);

    return MV_THINVPP_OK;
}

#endif
