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

#define _VPP_FE_DLR_C_

#include "memmap.h"

#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_fe_dlr.h"
#include "vpp_fe_dlr_prv.h"

#include "vpp.h"
//#include "MTR.h"

/***************************************************************************************
 * FUNCTION: load default values of data loader to BCM buffer
 * PARAMS:  Channel - indicate the channel
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int Channel)
{
    unsigned int RegAddr;
    int Count;
    int RetVal = MV_THINVPP_OK;

    if((Channel < VPP_FE_DLR_CHANNEL_BG) || (Channel > VPP_FE_DLR_CHANNEL_OFFLINE))
        return MV_THINVPP_EBADPARAM;;

    if (Channel != VPP_FE_DLR_CHANNEL_OFFLINE) {

        RegAddr = vpp_obj->base_addr + RA_Vpp_LDR + VppFeDlrRegOff[Channel] + RA_PLANE_SIZE;

        /*write default register values for the plane to BCM buffer*/
        for(Count=0; Count<5; Count++){
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (RegAddr + (Count << 2)), VppFeDlr[Count + Channel * 5])))
                return RetVal;
        }
    }

    if(Channel == VPP_FE_DLR_CHANNEL_MAIN){
        /*load main channel dummy TG default values*/
        RegAddr = vpp_obj->base_addr + RA_Vpp_VP_TG + RA_TG_SIZE;
        for(Count=0; Count<4; Count++){
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (Count << 2), VppFeDlr[Count + VPP_FE_DLR_TG_OFFSET])))
                return RetVal;
        }
        RegAddr = vpp_obj->base_addr + RA_Vpp_VP_TG + RA_TG_VB0;
        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, VppFeDlr[VPP_FE_DLR_TG_VB0_OFFSET])))
            return RetVal;

        /*load de-interlacer clock setting*/
        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_VP_CLKEN_CTRL, VppFeDlr[VPP_FE_DLR_VP_CLKEN_OFFSET])))
            return RetVal;
    }

    if(Channel == VPP_FE_DLR_CHANNEL_OFFLINE){
        /*load off-line channel data loader default values*/
        RegAddr = vpp_obj->base_addr + RA_Vpp_mainW;
        for(Count=0; Count<6; Count++){
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (Count << 2), VppFeDlr[Count + VPP_FE_DLR_MAINW_OFFSET ])))
                    return RetVal;
        }
        /*load off-line channel total pixel number*/
        RegAddr = vpp_obj->base_addr + RA_Vpp_mainW_pix;
        for(Count=0; Count<6; Count++){
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (Count << 2), VppFeDlr[Count + VPP_FE_DLR_MAINW_PIX_OFFSET])))
                return RetVal;
        }
    }

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: clear all the FIFOs and pipline data inside the channel.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_ClearChannel(THINVPP_OBJ *vpp_obj, int Channel)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    if((Channel < VPP_FE_DLR_CHANNEL_BG) || (Channel > VPP_FE_DLR_CHANNEL_MOSD))
        return MV_THINVPP_EBADPARAM;

    RegAddr = vpp_obj->base_addr + RA_Vpp_LDR + VppFeDlrRegOff[Channel] + RA_PLANE_CLEAR;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, 1))) // clear
        return RetVal;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, 0))) // unclear
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: Clear the asynchronous FIFO between the client and dHub, clear the start bit at the same time.
 * PARAMS: Channel - id of a front-end dataloader channel.
 *               Clear - 1:Clear the asynchronous FIFO, 0:don't clear, normal stare.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_ClearOffLineChannel(THINVPP_OBJ *vpp_obj, int Channel, int Clear)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)

    /*only off-line channel for B0*/
    if((Channel < VPP_FE_DLR_OFFLINE_MAIN_W) || (Channel > VPP_FE_DLR_OFFLINE_AUX_R))
        return MV_THINVPP_EBADPARAM;
    RegAddr = vpp_obj->base_addr  + RA_Vpp_mainW + (Channel << 2);

#else

    /*BG channel or off-line channel*/
    if((Channel < VPP_FE_DLR_BG_R) || (Channel > VPP_FE_DLR_OFFLINE_AUX_R))
        return MV_THINVPP_EBADPARAM;
    RegAddr = vpp_obj->base_addr + RA_Vpp_bgR + (Channel << 2);

#endif

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, (Clear << 1))))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set the size of the plane.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 *                pPlaneSize - pointer to the struct of horizontal and vertial size.
 *                CropWpl - beat per line and crop
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetPlaneSize(THINVPP_OBJ *vpp_obj, int Channel, PVPP_FE_DLR_INPUT_RES pPlaneSize, unsigned int CropWpl)
{
    unsigned int RegAddr;
    unsigned int RegSizeVal;
    int RetVal = MV_THINVPP_OK;

    if((Channel < VPP_FE_DLR_CHANNEL_BG) || (Channel > VPP_FE_DLR_CHANNEL_MOSD))
        return MV_THINVPP_EBADPARAM;

    RegAddr = vpp_obj->base_addr + RA_Vpp_LDR + VppFeDlrRegOff[Channel];

    /*get plane size register value*/
    RegSizeVal = pPlaneSize->VRes + (pPlaneSize->HRes << 16);

    /*write plane size to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (RegAddr + RA_PLANE_SIZE), RegSizeVal)))
        return RetVal;

    /*write crop WPL to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (RegAddr + RA_PLANE_CROP), CropWpl)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set input data format and order.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 *                pDataFmt - pointer to the struct of data format and order.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetPlaneDataFmt(THINVPP_OBJ *vpp_obj, int Channel, PVPP_FE_DLR_PLANE_DATA_FMT pDataFmt)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;
    unsigned int RegFmtVal;

    if((Channel < VPP_FE_DLR_CHANNEL_BG) || (Channel > VPP_FE_DLR_CHANNEL_MOSD))
        return MV_THINVPP_EBADPARAM;

    RegAddr = vpp_obj->base_addr + RA_Vpp_LDR + VppFeDlrRegOff[Channel] + RA_PLANE_FORMAT;

    RegFmtVal = pDataFmt->SrcFmt + (pDataFmt->FmtOrder << 3);

    /*write input data fromat to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, RegFmtVal)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: enable the channel.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 *                Enable - 1:enable, 0:no effect.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_EnableChannel(THINVPP_OBJ *vpp_obj, int Channel, int Enable)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    if((Channel < VPP_FE_DLR_CHANNEL_BG) || (Channel > VPP_FE_DLR_CHANNEL_MOSD))
        return MV_THINVPP_EBADPARAM;

    RegAddr = vpp_obj->base_addr + RA_Vpp_LDR + VppFeDlrRegOff[Channel] + RA_PLANE_START;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Enable)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: start data loader for BG(only in A0/A1) or off-line channel(main PIP AUX).
 * PARAMS: Channel - id of a front-end dataloader channel.
 *               Enable - 1:kick the hardware, 0:no effect on hardware.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_EnableOffLineChannel(THINVPP_OBJ *vpp_obj, int Channel, int Enable)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)

    /*only off-line channel for B0*/
    if((Channel < VPP_FE_DLR_OFFLINE_MAIN_W) || (Channel > VPP_FE_DLR_OFFLINE_AUX_R))
        return MV_THINVPP_EBADPARAM;
    RegAddr = vpp_obj->base_addr  + RA_Vpp_mainW + (Channel << 2);

#else

    /*BG channel or off-line channel*/
    if((Channel < VPP_FE_DLR_BG_R) || (Channel > VPP_FE_DLR_OFFLINE_AUX_R))
        return MV_THINVPP_EBADPARAM;
    RegAddr = vpp_obj->base_addr + RA_Vpp_bgR + (Channel << 2);

#endif

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Enable)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set total number of pixel for BG or off-line scaling channel(main PIP BE).
 * PARAMS: Channel - id of a front-end dataloader channel.
 *               pRes - pointer to struct of scaler output resolution
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetOffLineChannel(THINVPP_OBJ *vpp_obj, int Channel, PVPP_FE_DLR_INPUT_RES pRes)
{
    unsigned int RegVal;
    int RetVal = MV_THINVPP_OK;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    /*only off-line channel for B0*/
    if((Channel < VPP_FE_DLR_OFFLINE_MAIN_W) || (Channel > VPP_FE_DLR_OFFLINE_AUX_R))
        return MV_THINVPP_EBADPARAM;
#else
    /*BG channel or off-line channel*/
    if((Channel < VPP_FE_DLR_BG_R) || (Channel > VPP_FE_DLR_OFFLINE_AUX_R))
        return MV_THINVPP_EBADPARAM;
#endif

    switch(Channel){

#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
        case VPP_FE_DLR_BG_R:
            RegVal = (((pRes->HRes * pRes->VRes) << 4) + 63) >> 6;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_bgR_word, RegVal)))
                return RetVal;
            break;
#endif

        case VPP_FE_DLR_OFFLINE_MAIN_W:
            RegVal = pRes->HRes * pRes->VRes;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_mainW_pix, RegVal)))
                return RetVal;
            break;

        case VPP_FE_DLR_OFFLINE_MAIN_R:
            RegVal = (((pRes->HRes * pRes->VRes) << 4) + 63) >> 6;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_mainR_word, RegVal)))
                return RetVal;
            break;

        case VPP_FE_DLR_OFFLINE_PIP_W:
            RegVal = pRes->HRes * pRes->VRes;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_pipW_pix, RegVal)))
                return RetVal;
            break;

        case VPP_FE_DLR_OFFLINE_PIP_R:
            RegVal = (((pRes->HRes * pRes->VRes) << 4) + 63) >> 6;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_pipR_word, RegVal)))
                return RetVal;
            break;

        case VPP_FE_DLR_OFFLINE_AUX_W:
            RegVal = pRes->HRes * pRes->VRes;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_auxW_pix, RegVal)))
                return RetVal;
            break;

        case VPP_FE_DLR_OFFLINE_AUX_R:
            RegVal = (((pRes->HRes * pRes->VRes) << 4) + 63) >> 6;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_auxR_word, RegVal)))
                return RetVal;
            break;
    }

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set dummy TG for main video channel.
 * PARAMS: TotRes - input total resolution.
 *                progressive - 1: prgressive, 0: interlaced.
 *                sensio - 1: sensio mode, 0: non-sensio mode.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetDummyTG(THINVPP_OBJ *vpp_obj, PVPP_FE_DLR_INPUT_RES pTotRes, int progressive, int sensio)
{
    unsigned int RegAddr;
    unsigned int RegVal;
    int RetVal = MV_THINVPP_OK;

    RegAddr = vpp_obj->base_addr + RA_Vpp_VP_TG;

    if (progressive) {
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        if (sensio)
            RegVal = (pTotRes->VRes + VPP_FE_DUMMY_TG_SENSIO_V_OFF_P) + ((pTotRes->HRes + VPP_FE_DUMMY_TG_SENSIO_H_OFF_P) << 16);
        else
#endif
            RegVal = (pTotRes->VRes + VPP_FE_DUMMY_TG_SIZE_V_OFF_P) + ((pTotRes->HRes + VPP_FE_DUMMY_TG_SIZE_H_OFF_P) << 16);
    } else {
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        if (sensio)
            RegVal = (pTotRes->VRes + VPP_FE_DUMMY_TG_SENSIO_V_OFF_I) + ((pTotRes->HRes + VPP_FE_DUMMY_TG_SENSIO_H_OFF_I) << 16);
        else
#endif
            RegVal = (pTotRes->VRes + VPP_FE_DUMMY_TG_SIZE_V_OFF_I) + ((pTotRes->HRes + VPP_FE_DUMMY_TG_SIZE_H_OFF_I) << 16);
    }

    /*write TG size to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (RegAddr + RA_TG_SIZE), RegVal)))
        return RetVal;

    /*calculate the H blank front edge value*/
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
    if (sensio)
        RegVal = pTotRes->HRes + VPP_FE_DUMMY_TG_SENSIO_HB_FE_OFF + (VPP_FE_DUMMY_TG_SENSIO_HB_BE << 16);
    else
#endif
        RegVal = pTotRes->HRes + VPP_FE_DUMMY_TG_HB_FE_OFF + (VPP_FE_DUMMY_TG_HB_BE << 16);

    /*write the data to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (RegAddr + RA_TG_HB), RegVal)))
        return RetVal;

    /*calculate the V blank front edge value*/
    RegVal = pTotRes->VRes + VPP_FE_DUMMY_TG_VB0_FE_OFF + (VPP_FE_DUMMY_TG_VB0_BE << 16);

    /*writer the data to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (RegAddr + RA_TG_VB0), RegVal)))
        return RetVal;

    return RetVal;
}

int FE_DLR_SetVPDMX(THINVPP_OBJ *vpp_obj, PVPP_FE_DLR_INPUT_RES pTotRes, int progressive, int sensio)
{
    int RetVal = MV_THINVPP_OK;

    if (progressive) {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_HRES), pTotRes->HRes-1);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_VRES), (pTotRes->VRes/2)-1);
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        if (sensio) {
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_HT), pTotRes->HRes + VPP_FE_DUMMY_TG_SENSIO_H_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_IVT), pTotRes->VRes + VPP_FE_DUMMY_TG_SENSIO_V_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_VT), pTotRes->VRes + VPP_FE_DUMMY_TG_SENSIO_V_OFF_I - 1);
        } else
#endif
        {
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_HT), pTotRes->HRes + VPP_FE_DUMMY_TG_SIZE_H_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_IVT), pTotRes->VRes + VPP_FE_DUMMY_TG_SIZE_V_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_VT), pTotRes->VRes + VPP_FE_DUMMY_TG_SIZE_V_OFF_I - 1);
        }
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_CTRL), 1); // ignore hardware calibration
#endif
    } else {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_HRES), pTotRes->HRes-1);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_VRES), pTotRes->VRes-1);
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        if (sensio) {
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_HT), pTotRes->HRes + VPP_FE_DUMMY_TG_SENSIO_H_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_IVT), pTotRes->VRes + VPP_FE_DUMMY_TG_SENSIO_V_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_VT), 2 * (pTotRes->VRes + VPP_FE_DUMMY_TG_SENSIO_V_OFF_I) - 1);
        } else
#endif
        {
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_HT), pTotRes->HRes + VPP_FE_DUMMY_TG_SIZE_H_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_IVT), pTotRes->VRes + VPP_FE_DUMMY_TG_SIZE_V_OFF_I - 1);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_VT), 2 * (pTotRes->VRes + VPP_FE_DUMMY_TG_SIZE_V_OFF_I) - 1);
        }
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, (vpp_obj->base_addr + RA_Vpp_VP_DMX_CTRL), 1); // ignore hardware calibration
#endif
    }

    return RetVal;
}
