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

#define _VPP_BE_HDMITX_C_

#include "maddr.h"
#include "vpp.h"

#include "thinvpp_api.h"
#include "thinvpp_module.h"
#include "thinvpp_common.h"
#include "thinvpp_bcmbuf.h"
#include "thinvpp_cfg.h"
#include "galois_io.h"

#include "hdmi_cmn.h"
#include "vpp_be_hdmitx.h"
#include "vpp_be_hdmitx_prv.h"
#include "vpp_be_hdmitx_cfg.h"

#if (BERLIN_CHIP_VERSION == BERLIN_BG2CD_A0)
#define VPP_HDTX_OUT_MUX_SEL0_VAL           1
#define VPP_HDTX_OUT_MUX_SEL1_VAL           0x23

#define VPP_HDMI_PHY_PD_IREF_VAL            0
#define VPP_HDMI_PHY_POLSWAP_TX_VAL         0xC
#define VPP_HDMI_PHY_INV_CK20T_VAL          0xF

//only one setting for BG2CD now
#define VPP_HDMI_PHY_DAMP_VAL_HI_FREQ       0xDB6
#define VPP_HDMI_PHY_EAMP_VAL_HI_FREQ       0x049
#define VPP_HDMI_PHY_IDRV_VAL_HI_FREQ       0x1122
#define VPP_HDMI_PHY_TXDRVX2_VAL_HI_FREQ    0x0
#define VPP_HDMI_PHY_TXDRVX2_VAL_HI_FREQ_ENABLED

#define VPP_HDMI_PHY_DAMP_VAL_LO_FREQ       VPP_HDMI_PHY_DAMP_VAL_HI_FREQ
#define VPP_HDMI_PHY_EAMP_VAL_LO_FREQ       VPP_HDMI_PHY_EAMP_VAL_HI_FREQ
#define VPP_HDMI_PHY_EAMP_VAL_LO_FREQ_INIT	VPP_HDMI_PHY_EAMP_VAL_HI_FREQ
#define VPP_HDMI_PHY_IDRV_VAL_LO_FREQ       VPP_HDMI_PHY_IDRV_VAL_HI_FREQ
#define VPP_HDMI_PHY_TXDRVX2_VAL_LO_FREQ    VPP_HDMI_PHY_TXDRVX2_VAL_HI_FREQ

#define VPP_HDMI_PHY_SVTX_VAL               0x6DB
#define VPP_HDMI_PHY_CP_VAL                 0xAA

#define VPP_HDMI_PHY_ODT_ENABLE             0
#define VPP_HDMI_PHY_AUX_VAL                (0x6 | VPP_HDMI_PHY_ODT_ENABLE)

#else /* !(BERLIN_CHIP_VERSION == BERLIN_BG2CD_A0) */
#define VPP_HDMI_PHY_AUX_VAL                0x3

#if (BERLIN_CHIP_VERSION < BERLIN_BG2)
#define VPP_HDMI_PHY_POLSWAP_TX_VAL         0x5
#define VPP_HDMI_PHY_INV_CK20T_VAL          0x1
#else
#define VPP_HDMI_PHY_POLSWAP_TX_VAL         0x0
#define VPP_HDMI_PHY_INV_CK20T_VAL          0x0
#endif

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
#define VPP_HDMI_PHY_DAMP_VAL_HI_FREQ       0xB6D
#define VPP_HDMI_PHY_EAMP_VAL_HI_FREQ       0x492
#define VPP_HDMI_PHY_IDRV_VAL_HI_FREQ       0xEEEE
#elif (BERLIN_CHIP_VERSION >= BERLIN_C_1)
#define VPP_HDMI_PHY_DAMP_VAL_HI_FREQ       0xB6D
#define VPP_HDMI_PHY_EAMP_VAL_HI_FREQ       0x249
#define VPP_HDMI_PHY_IDRV_VAL_HI_FREQ       0xDDDD
#elif (BERLIN_CHIP_VERSION == BERLIN_C_0)
#define VPP_HDMI_PHY_DAMP_VAL_HI_FREQ       0xDB6
#define VPP_HDMI_PHY_EAMP_VAL_HI_FREQ       0x6DB
#define VPP_HDMI_PHY_IDRV_VAL_HI_FREQ       0xCCCC
#else
#define VPP_HDMI_PHY_DAMP_VAL_HI_FREQ       0xB6D
#define VPP_HDMI_PHY_EAMP_VAL_HI_FREQ       0x492
#define VPP_HDMI_PHY_IDRV_VAL_HI_FREQ_UNUSED
#endif

#define VPP_HDMI_PHY_DAMP_VAL_LO_FREQ       0x924
#define VPP_HDMI_PHY_EAMP_VAL_LO_FREQ       0x249
#define VPP_HDMI_PHY_EAMP_VAL_LO_FREQ_INIT	0x0
#define VPP_HDMI_PHY_TXDRVX2_VAL_LO_FREQ    0x0

#if (BERLIN_CHIP_VERSION < BERLIN_BG2)
#define VPP_HDMI_PHY_IDRV_VAL_LO_FREQ		0xEEEE /* Old value - 0xFFFF */
#else
#define VPP_HDMI_PHY_IDRV_VAL_LO_FREQ		0xCCCC /* Old value - 0xCCCC */
#endif

#define VPP_HDMI_PHY_SVTX_VAL               0x249 /* Old value - 0x00 */
#define VPP_HDMI_PHY_CP_VAL                 0xFF
#endif

int BE_HDMITX_SetHDCPFixColor(THINVPP_OBJ *vpp_obj, int color);

/*-----------------------------------------------------------------------------
 * Description  : This function sets the default configuration values to the
 *              : hardware registers
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_LoadDefaultVal(THINVPP_OBJ *vpp_obj)
{
    unsigned int  reg;
    unsigned int  addr;
    int     i;

    // Set host packet base addresses
    vpp_obj->be.hdmiTxDrv.hostPktCfg[0] = HDTX_PKT0_BYTE0;
    vpp_obj->be.hdmiTxDrv.hostPktCfg[1] = HDTX_PKT1_BYTE0;
    vpp_obj->be.hdmiTxDrv.hostPktCfg[2] = HDTX_PKT2_BYTE0;
    vpp_obj->be.hdmiTxDrv.hostPktCfg[3] = HDTX_PKT3_BYTE0;
    vpp_obj->be.hdmiTxDrv.hostPktCfg[4] = HDTX_PKT4_BYTE0;
    vpp_obj->be.hdmiTxDrv.hostPktCfg[5] = HDTX_PKT5_BYTE0;

    // Set MemSize
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_MEMSIZE_L, (unsigned char*)&HdmiTxMemSize, 2, REG_DATA_ACCESS_VBI_BCMBUF));

    // Disable audio FIFO reset (H/W bug)
    reg = 0x00;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_FIFO_CTRL, (unsigned char*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // Set deep color fifo read and write pointers
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_DC_FIFO_WR_PTR, (unsigned char*)&HdmiTxWritePtr, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_DC_FIFO_RD_PTR, (unsigned char*)&HdmiTxReadPtr, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // Set BCH Rotate Flag
    HwiHdmiTxEnableBCHRotate(vpp_obj,HdmiTxEnBchRot);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HDMI_CTRL, &vpp_obj->be.hdmiTxDrv.hdmiCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // Set Swap Control
    reg = (HdmiTxEnTmdsBitSwap) | (HdmiTxEnTmdsChnSwap << 1);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_SWAP_CTRL, (unsigned char*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // Set Tmds Clock
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_TDATA3_0, (unsigned char*)&HdmiTxTmdsClkCfg, 3, REG_DATA_ACCESS_VBI_BCMBUF));

    // Disable audio transmission
    HDMITX_RETCODE_CHK(BE_HDMITX_EnableAudioPkt(vpp_obj, 0));

    // Mute audio and video
    HDMITX_RETCODE_CHK(BE_HDMITX_SetMute(vpp_obj, 1, 1));

    // Clear all packet transmission
    for (i = 0; i < VPP_BE_HDMITX_MAX_PKT_INDEX; i++)
    {
        HDMITX_RETCODE_CHK(BE_HDMITX_ClearHostPktTxData(vpp_obj,i,REG_DATA_ACCESS_VBI_BCMBUF));
    }
    HDMITX_RETCODE_CHK(BE_HDMITX_DisableHostPkt(
        vpp_obj, VPP_BE_HDMITX_MAX_PKT_INDEX, VPP_BE_HDMITX_HOST_PKT_TX_EVERY_VSYNC));

    // Reset all other registers
    vpp_obj->be.hdmiTxDrv.gcpCfg0   = 0x00;
    vpp_obj->be.hdmiTxDrv.gcpCfg1   = 0x00;
    vpp_obj->be.hdmiTxDrv.hdmiCtrl  = 0x00;
    vpp_obj->be.hdmiTxDrv.videoCtrl = 0x00;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    // ACR given more priority than audio sample packets
    HwiHdmiTxSetACRPriority(vpp_obj,1);
#endif

    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_GCP_CFG0, &vpp_obj->be.hdmiTxDrv.gcpCfg0, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_GCP_CFG0, &vpp_obj->be.hdmiTxDrv.gcpCfg1, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_VIDEO_CTRL, &vpp_obj->be.hdmiTxDrv.videoCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HDMI_CTRL, &vpp_obj->be.hdmiTxDrv.hdmiCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    reg = 0x00;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HTOT_L, (unsigned char*)&reg, 2, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HBLANK_L, (unsigned char*)&reg, 2, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_VTOT_L, (unsigned char*)&reg, 2, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_VRES_L, (unsigned char*)&reg, 2, REG_DATA_ACCESS_VBI_BCMBUF));

    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_VSTART_L, (unsigned char*)&reg, 2, REG_DATA_ACCESS_VBI_BCMBUF));

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    reg = 0x00;

    // Reset HBR Control
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_HBR_PKT, (unsigned char*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // Clear Audio channel select
    addr = HDTX_AUD_CH1_SEL;
    for (i = 0; i < 8; i++)
    {
        HDMITX_RETCODE_CHK (HDMITX_RegWrite (
            vpp_obj, addr, (unsigned char*)&i, 1, REG_DATA_ACCESS_VBI_BCMBUF));
        addr++;
    }

    // HPD Select
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, TX_HDCP_HPD_SEL, (unsigned char*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
    reg = 0x00; // Deep color control for pixel packing phase
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_DC_PP_CTRL, (unsigned char*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));
#endif

    // Host packet control 2
    // Indicates VSync selected edge is used for host packets and vsync rise edge is selected in C0
    reg = 0x00;
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_HST_PKT_CTRL2, (unsigned char*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // Enable PHY FIFO
    BE_HDMITX_EnablePhyFifo (vpp_obj, 0, 1);
#endif // (BERLIN_CHIP_VERSION >= BERLIN_B_0)

    // Set HDCP Color
    BE_HDMITX_SetHDCPFixColor(vpp_obj, 0x801080);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
    reg = 0x01;
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, TX_HDCP_DB_EN, (UINT8*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));
#endif

    /*
     * set up HDTX MUX and HDMI mode if required
     */
#if (BERLIN_CHIP_VERSION == BERLIN_BG2CD_A0)
    reg = VPP_HDTX_OUT_MUX_SEL0_VAL;
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_OUT_MUX_SEL0, (UINT8*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    reg = VPP_HDTX_OUT_MUX_SEL1_VAL;
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_OUT_MUX_SEL1, (UINT8*)&reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));
#endif

    return (MV_THINVPP_OK);
}

int BE_HDMITX_SetHDCPFixColor(THINVPP_OBJ *vpp_obj, int color)
{
    /* note: FIX_CLR_0/1/2 (with VideoMute in AVMUTE_CTRL) are not used in BG2 HDMI TX */
    /* instead, FIX_CLR_CH0/1/2 (with FIX_CLR_SEL) are used to select register solid color output */
#if (BERLIN_CHIP_VERSION < BERLIN_BG2)
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, TX_HDCP_FIX_CLR_0, (UINT8*)&color, 3, REG_DATA_ACCESS_VBI_BCMBUF));
#else
    INT regVal;

    regVal = (color & 0x0ff);
    regVal <<= 4; // FIX_CLR_CH0/1/2 are 12-bit registers which provides 12-bit input to HDMI TX
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_IN_FIX_CLR_CH0_L, (UINT8*)&regVal, 2, REG_DATA_ACCESS_VBI_BCMBUF));
    regVal = ((color>>8) & 0x0ff);
    regVal <<= 4; // FIX_CLR_CH0/1/2 are 12-bit registers which provides 12-bit input to HDMI TX
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_IN_FIX_CLR_CH1_L, (UINT8*)&regVal, 2, REG_DATA_ACCESS_VBI_BCMBUF));
    regVal = ((color>>16) & 0x0ff);
    regVal <<= 4; // FIX_CLR_CH0/1/2 are 12-bit registers which provides 12-bit input to HDMI TX
    HDMITX_RETCODE_CHK (HDMITX_RegWrite (
        vpp_obj, HDTX_IN_FIX_CLR_CH2_L, (UINT8*)&regVal, 2, REG_DATA_ACCESS_VBI_BCMBUF));
#endif

    return (MV_THINVPP_OK);
}
/*-----------------------------------------------------------------------------
 * Description  : This function enables audio packet transfer
 * Arguments    : EnAudio - Flag to enable/disable audio packet transmission
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_EnableAudioPkt (THINVPP_OBJ *vpp_obj, int EnAudio)
{
    unsigned char   reg = 0;

    if (EnAudio)
    {
        HwiHdmiTxSetInputAudioFmt (vpp_obj, VPP_BE_HDMITX_AUDIO_I2S);
        HwiHdmiTxEnableAudPktTrans(vpp_obj, 1);
        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_AUD_CTRL, &vpp_obj->be.hdmiTxDrv.audCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));
    }
    else
    {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        HwiHdmiTxEnableAudPktTrans(vpp_obj, 0);
#else
        //Workaround for disabling audio currently in Ax
        HwiHdmiTxSetInputAudioFmt (vpp_obj, VPP_BE_HDMITX_AUDIO_SPDIF);
#endif
        HwiHdmiTxEnableAcrPktTrans(vpp_obj, 0);
        HwiHdmiTxSetLayout(vpp_obj, 0);
        HwiHdmiTxEnableSWCts(vpp_obj, 1);
        HwiHdmiTxSetMClkFreq(vpp_obj, 0);

        reg = 0;
        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_AUD_CTRL, &vpp_obj->be.hdmiTxDrv.audCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_ACR_CTRL, &vpp_obj->be.hdmiTxDrv.acrCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_ACR_N0, &reg, 3, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_HDMI_CTRL, &vpp_obj->be.hdmiTxDrv.hdmiCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_I2S_DLEN, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_CHSTS_0, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_CHSTS_1, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_CHSTS_2, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_CHSTS_3, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_CHSTS_4, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));
    }
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets video format parameters
 * Arguments    : pVideoParams - Pointer to video format parameters (Input)
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetVideoFmtParams(THINVPP_OBJ *vpp_obj,
                                VPP_BE_HDMITX_OUT_MODE OutMode,
                                PVPP_BE_HDMITX_VIDEO_FMT_PARAMS pVideoParams)
{
    int                    SWTimingPars;
    RESOLUTION_INFO         *pDisplayModeParam;
    unsigned int                  Temp;
    VPP_BE_HDMITX_BIT_DEPTH BitDepth;

    if (!(OutMode == VPP_BE_HDMITX_OUT_DVI ||
          OutMode == VPP_BE_HDMITX_OUT_HDMI))
    {
        return MV_THINVPP_EBADPARAM;
    }

    // Video format
    HwiHdmiTxSetInVideoYC(vpp_obj,pVideoParams->VideoFmt == OUTPUT_COLOR_FMT_YCBCR422);

    switch (pVideoParams->ColorDepth)
    {
        case OUTPUT_BIT_DEPTH_12BIT:    BitDepth = VPP_BE_HDMITX_BIT_DEPTH_12; break;
        case OUTPUT_BIT_DEPTH_10BIT:    BitDepth = VPP_BE_HDMITX_BIT_DEPTH_10; break;
        case OUTPUT_BIT_DEPTH_8BIT:     BitDepth = VPP_BE_HDMITX_BIT_DEPTH_8;  break;
        default:
            return MV_THINVPP_EBADPARAM;
    }
    SWTimingPars = ((BitDepth == VPP_BE_HDMITX_BIT_DEPTH_10) ||
                    (BitDepth == VPP_BE_HDMITX_BIT_DEPTH_12));

    // Set Timing Parameters
    SWTimingPars = 1; // Force software parameters
    if (SWTimingPars)
    {
        pDisplayModeParam = (RESOLUTION_INFO *)&m_resinfo_table[pVideoParams->DispRes];

        // Update PHY settings
        HDMITX_UpdatePHYSettings(vpp_obj, pVideoParams->DispRes, pVideoParams->ColorDepth);

        // Updated HBlank programming based on inputs from design team
        Temp = ((pDisplayModeParam->width - pDisplayModeParam->active_width) *
                (pVideoParams->PixelRpt + 1)) - 1;
        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_HBLANK_L, (unsigned char*)&Temp, 2, REG_DATA_ACCESS_VBI_BCMBUF));

        // Configure VStart
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        if (pDisplayModeParam->scan == SCAN_INTERLACED)
            Temp = (unsigned int)((pDisplayModeParam->height - pDisplayModeParam->active_height)/2);
        else
            Temp = pDisplayModeParam->height - pDisplayModeParam->active_height;
        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_VSTART_L, (unsigned char*)&Temp, 2, REG_DATA_ACCESS_VBI_BCMBUF));
#endif
    }

    // Set SW/HW timing parameters
    HwiHdmiTxEnableDetectVidFmtInHW(vpp_obj,!SWTimingPars);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_VIDEO_CTRL, &vpp_obj->be.hdmiTxDrv.videoCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    // GCP Fields
    // GCP is valid only for HDMI and not DVI
//    if (OutMode == VPP_BE_HDMITX_OUT_HDMI)
    {
        HwiHdmiTxEnableGCPTrans(vpp_obj,0);
        HwiHdmiTxSetSWPPVal(vpp_obj,0);
        if (BitDepth == VPP_BE_HDMITX_BIT_DEPTH_8) {
            // HDMI CTS requires CD fields to be 0 for 8 bit
            HwiHdmiTxSetColorDepth(vpp_obj,0);
        } else {
            HwiHdmiTxSetColorDepth(vpp_obj,BitDepth);
        }
        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_GCP_CFG1, &vpp_obj->be.hdmiTxDrv.gcpCfg1, 1, REG_DATA_ACCESS_VBI_BCMBUF));
    }

    // Pixel Replication
    HwiHdmiTxEnablePixelRepeat(vpp_obj,pVideoParams->PixelRpt);
    if (OutMode == VPP_BE_HDMITX_OUT_HDMI)
    {
        HwiHdmiTxSetHdmiMode(vpp_obj,1);
    }
    else
    {
        HwiHdmiTxSetHdmiMode(vpp_obj,0);
    }
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HDMI_CTRL, &vpp_obj->be.hdmiTxDrv.hdmiCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets HDMI/DVI output mode
 * Arguments    : OutMode - HDMI/DVI Mode
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetMode(THINVPP_OBJ *vpp_obj,VPP_BE_HDMITX_OUT_MODE OutMode)
{
    if (OutMode == VPP_BE_HDMITX_OUT_HDMI)
    {
        HwiHdmiTxSetHdmiMode(vpp_obj,1);
    }
    else
    {
        HwiHdmiTxSetHdmiMode(vpp_obj,0);
    }
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HDMI_CTRL, &vpp_obj->be.hdmiTxDrv.hdmiCtrl, 1, REG_DATA_ACCESS_VBI_BCMBUF));
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function enables GCP packet transfer
 * Arguments    : EnableGCP - Flag to indicate GCP enable/disable
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_EnableGCP(THINVPP_OBJ *vpp_obj,int EnableGCP)
{
    if (HwiHdmiTxIsVideoMuted(vpp_obj))
    {
        HwiHdmiTxSetAVMute(vpp_obj,1);
    }
    else
    {
        HwiHdmiTxSetAVMute(vpp_obj,0);
    }
    HwiHdmiTxEnableGCPTrans(vpp_obj,EnableGCP);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_GCP_CFG0, &vpp_obj->be.hdmiTxDrv.gcpCfg0, 1, REG_DATA_ACCESS_VBI_BCMBUF));
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function fills the given data in the buffer of the
 *              : specified index and enables transfer
 * Arguments    : PktIndex   - Packet Index
 *              : PktTxMode - Packet transfer mode
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SendHostPkt(THINVPP_OBJ *vpp_obj, unsigned char PktIndex,
                          VPP_BE_HDMITX_HOST_PKT_TX_MODE PktTxMode)
{
    unsigned char   PktCfg;

    // Check packet index
    if (PktIndex >= VPP_BE_HDMITX_MAX_PKT_INDEX)
    {
        return MV_THINVPP_EBADPARAM;
    }

    // Set packet data
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, vpp_obj->be.hdmiTxDrv.hostPktCfg[PktIndex],
        vpp_obj->be.hdmiTxDrv.hostPktData[PktIndex], 31,
        REG_DATA_ACCESS_VDE_BCMBUF));

    if (PktTxMode == VPP_BE_HDMITX_HOST_PKT_TX_EVERY_VSYNC)
    {
        // Configure host packet control 1
        PktCfg = HwiHdmiTxGetPktTxMode(vpp_obj);
        PktCfg |= (1 << PktIndex);

        HwiHdmiTxSetPktTxMode(vpp_obj,PktCfg);
        HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_HST_PKT_CTRL1, &vpp_obj->be.hdmiTxDrv.hostPktCtrl1, 1,
            REG_DATA_ACCESS_VDE_BCMBUF));
    }

    // Configure host packet control 0
    // For repeat transfer also, this register has to be configured
    PktCfg = HwiHdmiTxGetPktEnableConfig(vpp_obj);
    PktCfg |= (1 << PktIndex);

    HwiHdmiTxSetPktEnableConfig(vpp_obj,PktCfg);

    HDMITX_WriteReg32(vpp_obj, RA_Vpp_regIfCtrl, 0x0000010f, REG_DATA_ACCESS_VDE_BCMBUF);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HST_PKT_CTRL0, &vpp_obj->be.hdmiTxDrv.hostPktCtrl0, 1,
        REG_DATA_ACCESS_VDE_BCMBUF));
#if (BERLIN_CHIP_VERSION < BERLIN_BG2_A0)
    // Write 0 to host packet control 0 (HW bug)
    PktCfg &=  ~(1 << PktIndex);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HST_PKT_CTRL0, &PktCfg, 1, REG_DATA_ACCESS_VDE_BCMBUF));
#else
#if !defined( NEW_HDMI_TX_IP)
    // Write 0 to host packet control 0 (HW bug)
    PktCfg &=  ~(1 << PktIndex);
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_HST_PKT_CTRL0, &PktCfg, 1, REG_DATA_ACCESS_VDE_BCMBUF));
#endif
#endif
    HDMITX_WriteReg32(vpp_obj, RA_Vpp_regIfCtrl, 0x00000101, REG_DATA_ACCESS_VDE_BCMBUF);

    // Clear sticky status for this packet to indicate that HW is updated
    HwiHdmiTxSetHostPktData(vpp_obj,PktIndex,31,0);
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function disables the packet transfer in the given
 *              : index
 * Arguments    : PktIndex   - Packet Index
 *              : PktTxMode  - Mode of transfer
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_DisableHostPkt(THINVPP_OBJ *vpp_obj, unsigned char PktIndex,
                             VPP_BE_HDMITX_HOST_PKT_TX_MODE PktTxMode)
{
    int     retCode = MV_THINVPP_OK;
    unsigned char   pktCfg;

    if (PktTxMode == VPP_BE_HDMITX_HOST_PKT_TX_EVERY_VSYNC)
    {
        if (PktIndex < VPP_BE_HDMITX_MAX_PKT_INDEX)
        {
            // Clear host packet control 1
            pktCfg = HwiHdmiTxGetPktTxMode(vpp_obj);
            pktCfg &= ~(1 << PktIndex);

            HwiHdmiTxSetPktTxMode(vpp_obj,pktCfg);
            HDMITX_RETCODE_CHK(HDMITX_RegWrite (
                vpp_obj, HDTX_HST_PKT_CTRL1, &vpp_obj->be.hdmiTxDrv.hostPktCtrl1, 1, REG_DATA_ACCESS_VDE_BCMBUF));

            // Configure host packet control 0
            // For repeat transfer also, this register has to be configured
            pktCfg = HwiHdmiTxGetPktEnableConfig(vpp_obj);
            pktCfg &= ~(1 << PktIndex);

            HwiHdmiTxSetPktEnableConfig(vpp_obj,pktCfg);

            HDMITX_WriteReg32(vpp_obj, RA_Vpp_regIfCtrl, 0x0000010f, REG_DATA_ACCESS_VDE_BCMBUF);
            retCode = HDMITX_RegWrite (
                vpp_obj, HDTX_HST_PKT_CTRL0, &vpp_obj->be.hdmiTxDrv.hostPktCtrl0, 1, REG_DATA_ACCESS_VDE_BCMBUF);
            HDMITX_WriteReg32(vpp_obj, RA_Vpp_regIfCtrl, 0x00000101, REG_DATA_ACCESS_VDE_BCMBUF);
            HDMITX_RETCODE_CHK(retCode);
        }
        else
        {
            // Disable all
            pktCfg = 0x00;
            HwiHdmiTxSetPktTxMode(vpp_obj,pktCfg);
            HDMITX_RETCODE_CHK(HDMITX_RegWrite (
                vpp_obj, HDTX_HST_PKT_CTRL1, &vpp_obj->be.hdmiTxDrv.hostPktCtrl1, 1, REG_DATA_ACCESS_VDE_BCMBUF));

            HwiHdmiTxSetPktEnableConfig(vpp_obj,pktCfg);
            HDMITX_WriteReg32(vpp_obj, RA_Vpp_regIfCtrl, 0x0000010f, REG_DATA_ACCESS_VDE_BCMBUF);
            retCode = HDMITX_RegWrite (
                vpp_obj, HDTX_HST_PKT_CTRL0, &vpp_obj->be.hdmiTxDrv.hostPktCtrl0, 1, REG_DATA_ACCESS_VDE_BCMBUF);
            HDMITX_WriteReg32(vpp_obj, RA_Vpp_regIfCtrl, 0x00000101, REG_DATA_ACCESS_VDE_BCMBUF);
            HDMITX_RETCODE_CHK(retCode);
        }

    }
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function stores host packet data at the given index
 * Arguments    : pktIndex   - Packet Index
 *              : pPktData   - Pointer to return packet data
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetHostPktTxData(THINVPP_OBJ *vpp_obj, unsigned char pktIndex, unsigned char *pPktData)
{
    unsigned char   i;

    // Check packet index
    if (pktIndex >= VPP_BE_HDMITX_MAX_PKT_INDEX)
    {
        return (MV_THINVPP_EBADPARAM);
    }
    // Set packet data
    for (i = 0; i < 31; i++)
    {
        HwiHdmiTxSetHostPktData(vpp_obj,pktIndex,i,pPktData[i]);
    }
    HwiHdmiTxSetHostPktData(vpp_obj,pktIndex,31,1);
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function clears host packet data at the given index
 * Arguments    : pktIndex   - Packet Index
 *              : bcmType - bcm buffer register programming goes to
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_ClearHostPktTxData(THINVPP_OBJ *vpp_obj, unsigned char pktIndex, unsigned char bcmType)
{
    int     retCode = MV_THINVPP_OK;
    unsigned char   i;

    // Check packet index
    if (pktIndex >= VPP_BE_HDMITX_MAX_PKT_INDEX)
    {
        return MV_THINVPP_EBADPARAM;
    }

    // Set packet data
    for (i = 0; i < 31; i++)
    {
        HwiHdmiTxSetHostPktData(vpp_obj,pktIndex,i,0);
    }
    retCode = HDMITX_RegWrite (vpp_obj, vpp_obj->be.hdmiTxDrv.hostPktCfg[pktIndex],
                                           vpp_obj->be.hdmiTxDrv.hostPktData[pktIndex], 31,
                                           /*REG_DATA_ACCESS_VDE_BCMBUF*/bcmType);
    // Clear local status
    HwiHdmiTxSetHostPktData(vpp_obj,pktIndex,31,0);
    return (retCode);
}

/*-----------------------------------------------------------------------------
 * Description  : This function mutes audio and/or video
 * Arguments    : audio - Enable/Disable audio mute
 *              : video - Enable/Disable vidio mute
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetMute(THINVPP_OBJ *vpp_obj, int audio, int video)
{
    int retCode;

    HwiHdmiTxMuteAudio(vpp_obj,audio);
    HwiHdmiTxMuteVideo(vpp_obj,video);

    retCode = HDMITX_RegWrite (
        vpp_obj, HDTX_AVMUTE_CTRL, &vpp_obj->be.hdmiTxDrv.avMuteCtrl, 1,
        REG_DATA_ACCESS_VBI_BCMBUF);
    HDMITX_RETCODE_CHK(retCode);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    /* note: VideoMute in AVMUTE_CTRL is not used any more in BG2 HDMI TX */
    /* instead, FIX_CLR_SEL is used to select register solid color output or inline video output */
    int regVal;

    if (video)
        regVal = 1;
    else
        regVal = 0;
    retCode = HDMITX_RegWrite (
        vpp_obj, HDTX_IN_FIX_CLR_SEL, (unsigned char *)&regVal, 1,
        REG_DATA_ACCESS_VBI_BCMBUF);
    HDMITX_RETCODE_CHK(retCode);
#endif

    if (HwiHdmiTxGetHdmiMode(vpp_obj))
    {
        retCode = BE_HDMITX_EnableGCP(vpp_obj,1);
    }
    return (retCode);
}

/*-----------------------------------------------------------------------------
 * Description  : This function returns audio and video mute status
 * Arguments    : pAudio - Pointer to return audio mute status (Output)
 *              : pVideo - Pointer to return video mute status (Output)
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_GetMuteSts(THINVPP_OBJ *vpp_obj, int *pAudio, int *pVideo)
{
    *pAudio = HwiHdmiTxIsAudioMuted(vpp_obj);
    *pVideo = HwiHdmiTxIsVideoMuted(vpp_obj);
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function resets the FIFO between Hdmi Tx and PHY
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 * Notes        : Register TDATA_0 is used for doing this reset in Berlin
 *              : Ax platforms
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_ResetFifo(THINVPP_OBJ *vpp_obj)
{
    unsigned char   reg;
    int     retCode = MV_THINVPP_OK;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    reg = 0x00;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_PHY_FIFO_SOFT_RST, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    reg = 0x01;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_PHY_FIFO_SOFT_RST, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    reg = 0x00;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_PHY_FIFO_SOFT_RST, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));
#else
    reg = 0x40;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_TDATA0_0, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    reg = 0x41;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_TDATA0_0, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));

    reg = 0x40;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
        vpp_obj, HDTX_TDATA0_0, &reg, 1, REG_DATA_ACCESS_VBI_BCMBUF));
#endif
    return (retCode);
}

/*-----------------------------------------------------------------------------
 * Description  : This function enables/disables PHY FIFO
 * Arguments    : enable   - 1/0 to control PHY FIFO
 *              : bufWrite - True to use bcm buffer, False to write directly
 * Returns      : MV_THINVPP_OK on success
 * Notes        : Register TDATA_0 is used for doing this reset in Berlin
 *              : Ax platforms
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_EnablePhyFifo(THINVPP_OBJ *vpp_obj, int enable, int bufWrite)
{
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    enable = !enable;
    HDMITX_RETCODE_CHK(HDMITX_RegWrite (
            vpp_obj, HDTX_PHY_FIFO_SOFT_RST, (unsigned char *)&enable, 1,
            bufWrite?REG_DATA_ACCESS_VBI_BCMBUF:REG_DATA_ACCESS_DIRECT));
#endif

    return (MV_THINVPP_OK);
}

/*****************************************************************************/
/* HDMI PHY Setting                                                          */
/*****************************************************************************/

/*-----------------------------------------------------------------------------
 * Description  : This function sets the default configuration values to the
 *              : PHY registers
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMIPHY_LoadDefaultVal (THINVPP_OBJ *vpp_obj)
{
#if !defined(FPGA)
    unsigned int regData;

#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    // D1 register
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), &regData);
    SET32HDMI_ctrl_POLSWAP_TX(regData, 5);
    SET32HDMI_ctrl_PD_TX(regData,0);
    SET32HDMI_ctrl_SYNC(regData, 1);
    SET32HDMI_ctrl_INV_CK20T (regData, 1);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), regData, REG_DATA_ACCESS_DIRECT);

    // Set Aux
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x14), &regData);
    SET32HDMI_ctrl_AUX(regData, 3);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x14), regData, REG_DATA_ACCESS_DIRECT);

#if 0
    // Set Damp
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x08), &regData);
    SET32HDMI_ctrl_DAMP(regData, 0x924);
    SET32HDMI_ctrl_EAMP(regData, 0x249);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x08), regData, REG_DATA_ACCESS_DIRECT);
#endif

    // Set SVTX and IDRV
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x0C), &regData);
    SET32HDMI_ctrl_SVTX(regData, 0x249); /* Old value - 0x00 */
    SET32HDMI_ctrl_TXDRVX2(regData,0);
    SET32HDMI_ctrl_IDRV(regData, 0xEEEE); /* Old value - 0xFFFF */
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x0C), regData, REG_DATA_ACCESS_DIRECT);

#else // (BERLIN_CHIP_VERSION < BERLIN_B_0)

    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x00), &regData);
    if (GET32HDMI_ctrl_PD_TX(regData) == 0) {
        // TMDS already enabled - don't re-init PHY
        return (MV_THINVPP_OK);
    }

#if (BERLIN_CHIP_VERSION == BERLIN_BG2CD_A0)
    SET32HDMI_ctrl_PD_IREF(regData, VPP_HDMI_PHY_PD_IREF_VAL);
#endif

    SET32HDMI_ctrl_POLSWAP_TX(regData, VPP_HDMI_PHY_POLSWAP_TX_VAL);

    //SET32HDMI_ctrl_PD_TX(regData,0);
    SET32HDMI_ctrl_SYNC(regData, 1);

    SET32HDMI_ctrl_INV_CK20T(regData, VPP_HDMI_PHY_INV_CK20T_VAL);

#if (BERLIN_CHIP_VERSION == BERLIN_BG2CD_A0)
    SET32HDMI_ctrl_DAMP(regData, VPP_HDMI_PHY_DAMP_VAL_LO_FREQ);
#endif
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x00), regData, REG_DATA_ACCESS_DIRECT);

    // Set Aux
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x0C), &regData);
    SET32HDMI_ctrl_AUX(regData, VPP_HDMI_PHY_AUX_VAL);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x0C), regData, REG_DATA_ACCESS_DIRECT);

#if 0
    // Set Damp
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x00), &regData);
    SET32HDMI_ctrl_DAMP(regData, 0x924);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x00), regData, REG_DATA_ACCESS_DIRECT);
#endif
    // Set Eamp
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), &regData);
    SET32HDMI_ctrl_EAMP(regData, VPP_HDMI_PHY_EAMP_VAL_LO_FREQ_INIT);
    SET32HDMI_ctrl_TXDRVX2(regData, VPP_HDMI_PHY_TXDRVX2_VAL_LO_FREQ);
    SET32HDMI_ctrl_IDRV(regData, VPP_HDMI_PHY_IDRV_VAL_LO_FREQ);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), regData, REG_DATA_ACCESS_DIRECT);

    // Set SVTX and IDRV
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x08), &regData);
    SET32HDMI_ctrl_SVTX(regData, VPP_HDMI_PHY_SVTX_VAL);
    SET32HDMI_ctrl_CP(regData, VPP_HDMI_PHY_CP_VAL);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x08), regData, REG_DATA_ACCESS_DIRECT);

    BE_HDMIPHY_EnableTmds (vpp_obj,1);
#endif
#endif

    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function enables/disables HDMI TMDS
 * Arguments    : Enable - True/False to control TMDS
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMIPHY_EnableTmds (THINVPP_OBJ *vpp_obj,int Enable)
{
#if !defined(FPGA)
    unsigned int regData;

#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), &regData);
    if (Enable)
    {
        SET32HDMI_ctrl_PD_TX(regData,0);
    }
    else
    {
        SET32HDMI_ctrl_PD_TX(regData,0x0f);
    }
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), regData, REG_DATA_ACCESS_DIRECT);

    // Toggle reset when powering up
    if (Enable)
    {
        HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), &regData);

        SET32HDMI_ctrl_RESET_TX(regData,1);
        HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), regData, REG_DATA_ACCESS_DIRECT);

        SET32HDMI_ctrl_RESET_TX(regData,0);
        HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), regData, REG_DATA_ACCESS_DIRECT);
    }
#else
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0), &regData);
    if (Enable)
    {
        SET32HDMI_ctrl_PD_TX(regData,0);
    }
    else
    {
        SET32HDMI_ctrl_PD_TX(regData, 0x0f);
    }
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0), regData, REG_DATA_ACCESS_DIRECT);

    // Toggle reset when powering up
    if (Enable)
    {
        HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), &regData);

        SET32HDMI_ctrl_RESET_TX(regData,1);
        HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), regData, REG_DATA_ACCESS_DIRECT);

        SET32HDMI_ctrl_RESET_TX(regData,0);
        HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), regData, REG_DATA_ACCESS_DIRECT);
    }
#endif
#endif
    return (MV_THINVPP_OK);
}

int BE_HDMIPHY_SetDAMP(THINVPP_OBJ *vpp_obj, int value)
{
#if !defined(FPGA)
    unsigned int regData;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0), &regData);
    SET32HDMI_ctrl_DAMP(regData, value);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0), regData, REG_DATA_ACCESS_DIRECT);
#endif
#endif
    return (MV_THINVPP_OK);
}

int BE_HDMIPHY_SetEAMP(THINVPP_OBJ *vpp_obj, int value)
{
#if !defined(FPGA)
    unsigned int regData;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), &regData);
    SET32HDMI_ctrl_EAMP(regData, value);
    HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), regData, REG_DATA_ACCESS_DIRECT);
#endif
#endif
    return (MV_THINVPP_OK);
}

/*****************************************************************************/
/* STATIC FUNCTIONS                                                          */
/*****************************************************************************/

/*-----------------------------------------------------------------------------
 * Description  : This function writes block of data starting at specified
 *              : register address
 * Arguments    : startAddr - start address to write to
 *              : pDataBuf - Pointer to data buffer (input)
 *              : length   - Length of data to be written
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
static int HDMITX_RegWrite (THINVPP_OBJ *vpp_obj,
                            unsigned int startAddr, unsigned char *pDataBuf,
                            unsigned int length,
                            REG_DATA_ACCESS dataAccess)
{
    unsigned int  i;
    unsigned int  wrAddr;
    int     retCode = MV_THINVPP_OK;
#if defined(BERLIN_SINGLE_CPU)
    int     cpcbID = vpp_obj->vout[VOUT_HDMI].dvID;
#endif

    wrAddr = vpp_obj->base_addr + (startAddr << 2);
    if (dataAccess == REG_DATA_ACCESS_VBI_BCMBUF)
    {
        for (i = 0; i < length; i++)
        {
            if(MV_THINVPP_OK != (retCode = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, wrAddr + (4*i), *pDataBuf)))
                return retCode;
            pDataBuf++;
        }
    }
    else if (dataAccess == REG_DATA_ACCESS_VDE_BCMBUF)
    {
        for (i = 0; i < length; i++)
        {
#if defined(BERLIN_SINGLE_CPU)
            if (cpcbID >= FIRST_CPCB && cpcbID < MAX_NUM_CPCBS)
                if(MV_THINVPP_OK != (retCode = THINVPP_BCMBUF_Write(vpp_obj->pVdeBcmBuf[cpcbID], wrAddr + (4*i), *pDataBuf)))
                    return retCode;
#else
#if 0//(BERLIN_CHIP_VERSION >= BERLIN_B_0)
            if(MV_THINVPP_OK != (retCode = THINVPP_BCMBUF_Write(vpp_obj->vde_bcm_buf, wrAddr + (4*i), *pDataBuf)))
                return retCode;
#else
            if(MV_THINVPP_OK != (retCode = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, wrAddr + (4*i), *pDataBuf)))
                return retCode;
#endif
#endif
            pDataBuf++;
        }
    }
    else // Direct Write
    {
        for (i = 0; i < length; i++)
        {
            GLB_REG_WRITE32((wrAddr + 4*i),*pDataBuf);
            pDataBuf++;
        }
    }
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function reads block of data starting at specified
 *              : register address
 * Arguments    : Addr - start address to read from
 *              : pDataBuf - Pointer to data buffer (Output)
 *              : Length   - Length of data to be read
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
static int HDMITX_ReadReg32 (THINVPP_OBJ *vpp_obj, unsigned int addr, unsigned int *pData)
{
    *pData = VPP_REG_READ32_RAW(addr);
    return (MV_THINVPP_OK);
}

/*-----------------------------------------------------------------------------
 * Description  : This function writes block of data starting at specified
 *              : register address
 * Arguments    : Addr - start address to write to
 *              : pDataBuf - Pointer to data buffer (input)
 *              : Length   - Length of data to be written
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
static int HDMITX_WriteReg32 (THINVPP_OBJ *vpp_obj, unsigned int addr, unsigned int data,
                              REG_DATA_ACCESS dataAccess)
{
    int retCode = MV_THINVPP_OK;
#if defined(BERLIN_SINGLE_CPU)
    int cpcbID = vpp_obj->vout[VOUT_HDMI].dvID;
#endif

    if (dataAccess == REG_DATA_ACCESS_VBI_BCMBUF)
    {
        retCode = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf,vpp_obj->base_addr + addr, data);
    }
    else if (dataAccess == REG_DATA_ACCESS_VDE_BCMBUF)
    {
#if defined(BERLIN_SINGLE_CPU)
        if (cpcbID >= FIRST_CPCB && cpcbID < MAX_NUM_CPCBS)
            retCode = THINVPP_BCMBUF_Write(vpp_obj->pVdeBcmBuf[cpcbID], vpp_obj->base_addr + addr, data);
#else
#if 0 //(BERLIN_CHIP_VERSION >= BERLIN_B_0)
        retCode = THINVPP_BCMBUF_Write(vpp_obj->vde_bcm_buf, vpp_obj->base_addr + addr, data);
#else
        retCode = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + addr, data);
#endif
#endif
    }
    else
    {
        GA_REG_WORD32_WRITE (vpp_obj->base_addr + addr, data);
    }
    return (retCode);
}

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/*-----------------------------------------------------------------------------
 * Description  : This function updates specific PHY settings based on the
 *              : video configuration
 * Arguments    : pResInfo - Pointer to resolution info
 *              : colorDepth - Color Depth
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
static int HDMITX_UpdatePHYSettings (THINVPP_OBJ *vpp_obj, int resID, int colorDepth)
{
    unsigned int regData;

    if ((m_resinfo_table[resID].freq >= 148000) && (colorDepth != OUTPUT_BIT_DEPTH_8BIT))
    {
        HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), &regData);
        SET32HDMI_ctrl_DAMP(regData, VPP_HDMI_PHY_DAMP_VAL_HI_FREQ);
        HDMITX_WriteReg32(vpp_obj, RA_Vpp_HDMI_ctrl, regData, REG_DATA_ACCESS_VBI_BCMBUF);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        /* toggle reset */
        SET32HDMI_ctrl_RESET_TX(regData,1);
        HDMITX_WriteReg32(vpp_obj, RA_Vpp_HDMI_ctrl, regData, REG_DATA_ACCESS_VBI_BCMBUF);

        SET32HDMI_ctrl_RESET_TX(regData,0);
        HDMITX_WriteReg32(vpp_obj, RA_Vpp_HDMI_ctrl, regData, REG_DATA_ACCESS_VBI_BCMBUF);
#endif

        HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), &regData);
        SET32HDMI_ctrl_EAMP   (regData, VPP_HDMI_PHY_EAMP_VAL_HI_FREQ);
#ifndef VPP_HDMI_PHY_IDRV_VAL_HI_FREQ_UNUSED
        SET32HDMI_ctrl_IDRV   (regData, VPP_HDMI_PHY_IDRV_VAL_HI_FREQ);
#endif
#if defined(VPP_HDMI_PHY_TXDRVX2_VAL_HI_FREQ_ENABLED)
        SET32HDMI_ctrl_TXDRVX2(regData, VPP_HDMI_PHY_TXDRVX2_VAL_HI_FREQ);
#endif
        HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), regData, REG_DATA_ACCESS_VBI_BCMBUF);

    }
    else
    {
        HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl), &regData);
        SET32HDMI_ctrl_DAMP(regData, VPP_HDMI_PHY_DAMP_VAL_LO_FREQ);
        HDMITX_WriteReg32(vpp_obj, RA_Vpp_HDMI_ctrl, regData, REG_DATA_ACCESS_VBI_BCMBUF);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        /* toggle reset */
        SET32HDMI_ctrl_RESET_TX(regData,1);
        HDMITX_WriteReg32(vpp_obj, RA_Vpp_HDMI_ctrl, regData, REG_DATA_ACCESS_VBI_BCMBUF);

        SET32HDMI_ctrl_RESET_TX(regData,0);
        HDMITX_WriteReg32(vpp_obj, RA_Vpp_HDMI_ctrl, regData, REG_DATA_ACCESS_VBI_BCMBUF);
#endif

        HDMITX_ReadReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), &regData);
        SET32HDMI_ctrl_EAMP   (regData, VPP_HDMI_PHY_EAMP_VAL_LO_FREQ);
#if (BERLIN_CHIP_VERSION == BERLIN_BG2CD_A0)
        SET32HDMI_ctrl_IDRV   (regData, VPP_HDMI_PHY_IDRV_VAL_LO_FREQ);
        SET32HDMI_ctrl_TXDRVX2(regData, VPP_HDMI_PHY_TXDRVX2_VAL_LO_FREQ);
#else
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
#if (BERLIN_CHIP_VERSION < BERLIN_BG2)
        SET32HDMI_ctrl_IDRV(regData, 0xEEEE);
#else
        SET32HDMI_ctrl_IDRV(regData, 0xCCCC);
#endif
#endif
#endif
        HDMITX_WriteReg32(vpp_obj, (RA_Vpp_HDMI_ctrl + 0x04), regData, REG_DATA_ACCESS_VBI_BCMBUF);
    }
    return (MV_THINVPP_OK);
}

#endif
