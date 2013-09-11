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

#ifndef __VPP_BE_HDMITX_PRV_H__
#define __VPP_BE_HDMITX_PRV_H__

/**********************************************************************
* Private Definitions and Prototypes                                  *
***********************************************************************/
#define HDMITX_RETCODE_CHK(RetCode) \
    if (RetCode != MV_THINVPP_OK) \
        return (RetCode);


/**********************************************************************
* Static Function Prototypes                                          *
***********************************************************************/
static int HDMITX_RegWrite (THINVPP_OBJ *vpp_obj,
                            unsigned int startAddr, unsigned char *pDataBuf,
                            unsigned int length,
                            REG_DATA_ACCESS dataAccess);

static int HDMITX_ReadReg32 (THINVPP_OBJ *vpp_obj, unsigned int addr, unsigned int *pData);

static int HDMITX_WriteReg32 (THINVPP_OBJ *vpp_obj, unsigned int addr, unsigned int data,
                              REG_DATA_ACCESS dataAccess);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
static int HDMITX_UpdatePHYSettings (THINVPP_OBJ *vpp_obj, int resID, int colorDepth);
#endif // (BERLIN_CHIP_VERSION >= BERLIN_B_0)

/**********************************************************************
* Register access typedefs and macros                                 *
***********************************************************************/
/* ACR Control Register */
typedef struct tagHDMITX_ACR_CTRL
{
    unsigned char ACREnable     : 1;
    unsigned char CTSSelect     : 1;
    unsigned char MClkSelect    : 2;
    unsigned char Res           : 4;
} HDMITX_ACR_CTRL;

/* Audio Control Register */
typedef struct tagHDMITX_AUD_CTRL
{
    unsigned char AudEnable     : 1;
    unsigned char I2SChnEnable  : 4;
    unsigned char I2SMode       : 1;
    unsigned char I2SDbgEnable  : 1;
    unsigned char ValidityBit   : 1;
} HDMITX_AUD_CTRL;

/* I2S Control Register */
typedef struct tagHDMITX_I2S_CTRL
{
    unsigned char ClkDelayMode      : 1;
    unsigned char ByteShift         : 1;
    unsigned char DataJustification : 1;
    unsigned char LeftChannelWs     : 1;
    unsigned char DataLatchingEdge  : 1;
} HDMITX_I2S_CTRL;

/* GCP Config Register 0 */
typedef struct tagHDMITX_GCP_CFG0
{
    unsigned char GCPEnable         : 1;
    unsigned char AVMute            : 1;
    unsigned char DefaultPhaseBit   : 1;
    unsigned char PPSWVal           : 1;
} HDMITX_GCP_CFG0;

/* GCP Config Register 1 */
typedef struct tagHDMITX_GCP_CFG1
{
    unsigned char PPBits            : 4;
    unsigned char ColorDepth        : 4;
} HDMITX_GCP_CFG1;

/* Video Control Register */
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)

typedef struct tagHDMITX_VIDEO_CTRL
{
    unsigned char InYC              : 1;
    unsigned char FldPol            : 1;
    unsigned char DebugCtrl         : 1;
    unsigned char ACRPriority       : 1;
    unsigned char UVCLoadCtrl       : 1;
    unsigned char Reserved1         : 1;
    unsigned char DetectVidFmtInHW  : 1;
    unsigned char Reserved2         : 1;
}HDMITX_VIDEO_CTRL;

#elif (BERLIN_CHIP_VERSION >= BERLIN_B_0)

typedef struct tagHDMITX_VIDEO_CTRL
{
    unsigned char InYC              : 1;
    unsigned char FldPol            : 1;
    unsigned char DebugCtrl         : 1;
    unsigned char ACRPriority       : 1;
    unsigned char Reserved1         : 2;
    unsigned char DetectVidFmtInHW  : 1;
    unsigned char Reserved2         : 1;
}HDMITX_VIDEO_CTRL;

#else // BERLIN_Ax

typedef struct tagHDMITX_VIDEO_CTRL
{
    unsigned char InYC              : 1;
    unsigned char Reserved1         : 5;
    unsigned char DetectVidFmtInHW  : 1;
    unsigned char Reserved2         : 1;
}HDMITX_VIDEO_CTRL;

#endif

/* HDMI Control Register */
typedef struct tagHDMITX_HDMI_CTRL
{
    unsigned char HdmiMode          : 1;
    unsigned char Layout            : 1;
    unsigned char BCHRotate         : 1;
    unsigned char PixelRepeat       : 4;
} HDMITX_HDMI_CTRL;

/* AV Mute Control Register */
typedef struct tagHDMITX_AVMUTE_CTRL
{
    unsigned char MuteAudio         : 1;
    unsigned char MuteVideo         : 1;
} HDMITX_AVMUTE_CTRL;

/*
 * Set/Get Macros for Acr Control Register
 */

/* ACR Packet Transmission */
#define HwiHdmiTxEnableAcrPktTrans(handle,Val) \
{ \
    ((HDMITX_ACR_CTRL *)(&handle->be.hdmiTxDrv.acrCtrl))->ACREnable = (Val); \
}

#define HwiHdmiTxIsAcrPktTransEnabled(handle) \
    (((HDMITX_ACR_CTRL *)(&handle->be.hdmiTxDrv.acrCtrl))->ACREnable)

/* Select SW/HW CTS */
#define HwiHdmiTxEnableSWCts(handle,Val) \
{ \
    ((HDMITX_ACR_CTRL *)(&handle->be.hdmiTxDrv.acrCtrl))->CTSSelect = (Val); \
}

#define HwiHdmiTxIsSWCtsEnabled(handle) \
    (((HDMITX_ACR_CTRL *)(&handle->be.hdmiTxDrv.acrCtrl))->CTSSelect)

/* MCLK Frequency */
#define HwiHdmiTxSetMClkFreq(handle,Val) \
{ \
    ((HDMITX_ACR_CTRL *)(&handle->be.hdmiTxDrv.acrCtrl))->MClkSelect = (Val); \
}

#define HwiHdmiTxGetMClkFreq(handle) \
    (((HDMITX_ACR_CTRL *)(&handle->be.hdmiTxDrv.acrCtrl))->MClkSelect)

/*
 * Set/Get Macros for Audio Control Register
 */
#define HwiHdmiTxEnableAudPktTrans(handle,Val) \
{ \
    ((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->AudEnable = (Val); \
}

#define HwiHdmiTxIsAudPktTransEnabled(handle) \
    (((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->AudEnable)

/* I2S Channel */
#define HwiHdmiSetI2SChnConfig(handle,Val) \
{ \
    ((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->I2SChnEnable = (Val); \
}

#define HwiHdmiTxGetI2SChnConfig(handle) \
    (((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->I2SChnEnable)

/* I2S Mode */
#define HwiHdmiTxSetInputAudioFmt(handle,Val) \
{ \
    ((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->I2SMode = (Val); \
}

#define HwiHdmiTxGetInputAudioFmt(handle) \
    (((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->I2SMode)

/* I2S Debug */
#define HwiHdmiTxEnableI2SDbg(handle,Val) \
{ \
    ((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->I2SDbgEnable = (Val); \
}

#define HwiHdmiTxIsI2SDbgEnabled(handle) \
    (((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->I2SDbgEnable)

/* Validity Bit */
#define HwiHdmiTxSetValidityBit(handle,Val) \
{ \
    ((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->ValidityBit = (Val); \
}

#define HwiHdmiTxGetValidityBit(handle) \
    (((HDMITX_AUD_CTRL *)(&handle->be.hdmiTxDrv.audCtrl))->ValidityBit)

/*
 * Set/Get Macros for I2S Control Register
 */

/* Clock Delay Mode */
#define HwiHdmiTxEnableClockDelay(handle,Val) \
{ \
    ((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->ClkDelayMode = (Val); \
}

#define HwiHdmiTxIsClockDelayEnabled(handle) \
    (((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->ClkDelayMode)

/* MSB/LSB shifted first */
#define HwiHdmiTxSetByteShiftMode(handle,Val) \
{ \
    ((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->ByteShift = (Val); \
}

#define HwiHdmiTxGetByteShiftMode(handle) \
    (((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->ByteShift)

/* Left/Right justified data */
#define HwiHdmiTxSetDataJustification(handle,Val) \
{ \
    ((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->DataJustification = (Val); \
}

#define HwiHdmiTxGetDataJustification(handle) \
    (((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->DataJustification)

/* Word Select */
#define HwiHdmiTxSetLeftChannelWs(handle,Val) \
{ \
    ((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->LeftChannelWs = (Val); \
}

#define HwiHdmiTxGetLeftChannelWs(handle) \
    (((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->LeftChannelWs)

/* Data latching on postive/negative edge of sck */
#define HwiHdmiTxSetDataLatchingEdge(handle,Val) \
{ \
    ((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->DataLatchingEdge = (Val); \
}

#define HwiHdmiTxGetDataLatchingEdge(handle) \
    (((HDMITX_I2S_CTRL *)(&handle->be.hdmiTxDrv.i2sCtrl))->DataLatchingEdge)

/*
 * Set/Get Macros for GCP Configuration Registers
 */
/* GCP transmission enable/disable */
#define HwiHdmiTxEnableGCPTrans(handle,Val) \
{ \
    ((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->GCPEnable = (Val); \
}

#define HwiHdmiTxIsGCPTransEnabled(handle) \
    (((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->GCPEnable)

/* Set AVMute */
#define HwiHdmiTxSetAVMute(handle,Val) \
{ \
    ((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->AVMute = (Val); \
}

#define HwiHdmiTxIsAVMuteSet(handle) \
    (((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->AVMute)

/* Default Phase Bit */
#define HwiHdmiTxSetDefPhaseBit(handle,Val) \
{ \
    ((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->DefaultPhaseBit = (Val); \
}

#define HwiHdmiTxGetDefPhaseBit(handle) \
    (((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->DefaultPhaseBit)

/* Enable SW/HW pixel packing phase */
#define HwiHdmiTxSetSWPPVal(handle,Val) \
{ \
    ((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->PPSWVal = (Val); \
}

#define HwiHdmiTxIsSWPPValEnabled(handle) \
    (((HDMITX_GCP_CFG0 *)(&handle->be.hdmiTxDrv.gcpCfg0))->PPSWVal)

/* Pixel Packing Field Bits */
#define HwiHdmiTxSetPPBits(handle,Val) \
{ \
    ((HDMITX_GCP_CFG1 *)(&handle->be.hdmiTxDrv.gcpCfg1))->PPBits = (Val); \
}

#define HwiHdmiTxGetPPBits(handle) \
    (((HDMITX_GCP_CFG1 *)(&handle->be.hdmiTxDrv.gcpCfg1))->PPBits)

/* Color Depth Value */
#define HwiHdmiTxSetColorDepth(handle,Val) \
{ \
    ((HDMITX_GCP_CFG1 *)(&handle->be.hdmiTxDrv.gcpCfg1))->ColorDepth = (Val); \
}

#define HwiHdmiTxGetColorDepth(handle) \
    (((HDMITX_GCP_CFG1 *)(&handle->be.hdmiTxDrv.gcpCfg1))->ColorDepth)

/*
 * Set/Get Macros for Video Control Register Bits
 */

/* Input Video format */
#define HwiHdmiTxSetInVideoYC(handle,Val) \
{ \
    ((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->InYC = (Val); \
}

#define HwiHdmiTxGetInVideoYC(handle) \
    (((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->InYC)

/* Detect video format in hardware */
#define HwiHdmiTxEnableDetectVidFmtInHW(handle,Val) \
{ \
    ((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->DetectVidFmtInHW = (Val); \
}

#define HwiHdmiTxIsVidFmtDetectInHWEnabled(handle) \
    (((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->DetectVidFmtInHW)

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/* Field Polarity */
#define HwiHdmiTxSetFldPolarity(handle,Val) \
{ \
    ((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->FldPol = (Val); \
}

#define HwiHdmiTxGetFldPolarity(handle) \
    (((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->FldPol)

/* Debug Control */
#define HwiHdmiTxSetDebugCtrl(handle,Val) \
{ \
    ((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->DebugCtrl = (Val); \
}

#define HwiHdmiTxGetDebugCtrl(handle) \
    (((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->DebugCtrl)

/* ACR Priority */
#define HwiHdmiTxSetACRPriority(handle,Val) \
{ \
    ((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->ACRPriority = (Val); \
}

#define HwiHdmiTxGetACRPriority(handle) \
    (((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->ACRPriority)

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
/* UVC Load Control */
#define HwiHdmiTxSetUVCLoadCtrl(handle,Val) \
{ \
    ((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->UVCLoadCtrl = (Val); \
}

#define HwiHdmiTxGetUVCLoadCtrl(handle) \
    (((HDMITX_VIDEO_CTRL *)(&handle->be.hdmiTxDrv.videoCtrl))->UVCLoadCtrl)
#endif
#endif
/*
 * Set/Get Macros for HDMI Control Register Bits
 */

/* HDMI/DVI Mode */
#define HwiHdmiTxSetHdmiMode(handle,Val) \
{ \
    ((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->HdmiMode = (Val); \
}

#define HwiHdmiTxGetHdmiMode(handle) \
    (((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->HdmiMode)

/* Layout - audio packetisation control */
#define HwiHdmiTxSetLayout(handle,Val) \
{ \
    ((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->Layout = (Val); \
}

#define HwiHdmiTxGetLayout(handle) \
    (((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->Layout)

/* BCH Rotate */
#define HwiHdmiTxEnableBCHRotate(handle,Val) \
{ \
    ((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->BCHRotate = (Val); \
}

#define HwiHdmiTxIsBCHRotateEnabled(handle) \
    (((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->BCHRotate)

/* Pixel Repeat */
#define HwiHdmiTxEnablePixelRepeat(handle,Val) \
{ \
    ((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->PixelRepeat = (Val); \
}

#define HwiHdmiTxIsPixelRepeatEnabled(handle) \
    (((HDMITX_HDMI_CTRL *)(&handle->be.hdmiTxDrv.hdmiCtrl))->PixelRepeat)

/*
 * Set/Get Macros for AVMute Control
 */
#define HwiHdmiTxMuteAudio(handle,Val) \
{ \
    ((HDMITX_AVMUTE_CTRL *)(&handle->be.hdmiTxDrv.avMuteCtrl))->MuteAudio = (Val); \
}

#define HwiHdmiTxIsAudioMuted(handle) \
    (((HDMITX_AVMUTE_CTRL *)(&handle->be.hdmiTxDrv.avMuteCtrl))->MuteAudio)

#define HwiHdmiTxMuteVideo(handle,Val) \
{ \
    ((HDMITX_AVMUTE_CTRL *)(&handle->be.hdmiTxDrv.avMuteCtrl))->MuteVideo = (Val); \
}

#define HwiHdmiTxIsVideoMuted(handle) \
    (((HDMITX_AVMUTE_CTRL *)(&handle->be.hdmiTxDrv.avMuteCtrl))->MuteVideo)

/*
 * Set/Get Macros for Host Packet Control 0 Register
 */
#define HwiHdmiTxSetPktEnableConfig(handle,Val) \
{ \
    handle->be.hdmiTxDrv.hostPktCtrl0 = (Val); \
}

#define HwiHdmiTxGetPktEnableConfig(handle) \
    (handle->be.hdmiTxDrv.hostPktCtrl0)

/*
 * Set/Get Macros for Host Packet Control 1 Register
 */
#define HwiHdmiTxSetPktTxMode(handle,Val) \
{ \
    handle->be.hdmiTxDrv.hostPktCtrl1 = (Val); \
}

#define HwiHdmiTxGetPktTxMode(handle) \
    (handle->be.hdmiTxDrv.hostPktCtrl1)

/*
 * Set/Get Macros for Packet 0 data Registers
 */
#define HwiHdmiTxSetHostPktData(handle,PktId,Index,Val) \
{ \
    handle->be.hdmiTxDrv.hostPktData[PktId][Index] = (Val); \
}

#define HwiHdmiTxGetHostPktData(handle,PktId,Index) \
  (handle->be.hdmiTxDrv.hostPktData[PktId][Index])

#endif // __VPP_BE_HDMITX_PRV_H__
