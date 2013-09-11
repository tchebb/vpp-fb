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

#ifndef __VPP_BE_HDMITX_H__
#define __VPP_BE_HDMITX_H__

int BE_HDMIPHY_SetDAMP (THINVPP_OBJ *vpp_obj, int value);
int BE_HDMIPHY_SetEAMP(THINVPP_OBJ *vpp_obj, int value);

#define NEW_HDMI_TX_IP

/*-----------------------------------------------------------------------------
 * Macros
 *-----------------------------------------------------------------------------
 */
#define VPP_BE_HDMITX_MAX_PKT_INDEX     6

/*-----------------------------------------------------------------------------
 * Enums, Structures and Unions
 *-----------------------------------------------------------------------------
 */
typedef enum tagVPP_BE_HDMITX_OUT_MODE
{
    VPP_BE_HDMITX_OUT_UNDEF = 0x00,
    VPP_BE_HDMITX_OUT_DVI,
    VPP_BE_HDMITX_OUT_HDMI,
}VPP_BE_HDMITX_OUT_MODE;

typedef enum tagVPP_BE_HDMITX_AUDIO_BUS
{
    VPP_BE_HDMITX_AUDIO_I2S,
    VPP_BE_HDMITX_AUDIO_SPDIF,
    VPP_BE_HDMITX_AUDIO_BUS_MAX
}VPP_BE_HDMITX_AUDIO_BUS, *PVPP_BE_HDMITX_AUDIO_BUS;

// Audio Input clock sampling freq types
typedef enum tagVPP_BE_HDMITX_AUDIO_INP_CLK_SEL
{
    VPP_BE_HDMITX_AUD_INP_CLK_128fs = 0,
    VPP_BE_HDMITX_AUD_INP_CLK_256fs,
    VPP_BE_HDMITX_AUD_INP_CLK_384fs,
    VPP_BE_HDMITX_AUD_INP_CLK_512fs,
    VPP_BE_HDMITX_AUD_INP_CLK_MAX
}VPP_BE_HDMITX_AUDIO_INP_CLK_SEL;

// Color Depth
typedef enum tagVPP_BE_HDMITX_BIT_DEPTH
{
    VPP_BE_HDMITX_BIT_DEPTH_8 = 4,
    VPP_BE_HDMITX_BIT_DEPTH_10,
    VPP_BE_HDMITX_BIT_DEPTH_12,
}VPP_BE_HDMITX_BIT_DEPTH;

// Pixel repetition types
typedef enum tagVPP_BE_HDMITX_PIXEL_RPT_TYPE
{
    VPP_BE_HDMITX_PIXEL_RPT_NONE = 0,
    VPP_BE_HDMITX_PIXEL_RPT_BY_2 = 1,
    VPP_BE_HDMITX_PIXEL_RPT_BY_3,
    VPP_BE_HDMITX_PIXEL_RPT_BY_4,
    VPP_BE_HDMITX_PIXEL_RPT_BY_5,
    VPP_BE_HDMITX_PIXEL_RPT_BY_6,
    VPP_BE_HDMITX_PIXEL_RPT_BY_7,
    VPP_BE_HDMITX_PIXEL_RPT_BY_8,
    VPP_BE_HDMITX_PIXEL_RPT_BY_9,
    VPP_BE_HDMITX_PIXEL_RPT_BY_10,
    VPP_BE_HDMITX_PIXEL_RPT_MAX
}VPP_BE_HDMITX_PIXEL_RPT_TYPE;

// HDMI Packet Types
typedef enum tagVPP_BE_HDMITX_HOST_PKT_TYPE
{
    VPP_BE_HDMITX_PKT_NONE  = 0x00,
    VPP_BE_HDMITX_NULL_PKT,
    VPP_BE_HDMITX_ACR_PKT,
    VPP_BE_HDMITX_AUD_SAMP_PKT,
    VPP_BE_HDMITX_GC_PKT,
    VPP_BE_HDMITX_ACP_PKT,
    VPP_BE_HDMITX_ISRC1_PKT,
    VPP_BE_HDMITX_ISRC2_PKT,
    VPP_BE_HDMITX_1BIT_AUD_SAMP_PKT,
    VPP_BE_HDMITX_DST_AUD_PKT,
    VPP_BE_HDMITX_HBR_AUD_PKT,
    VPP_BE_HDMITX_GAMUT_METADATA_PKT,
    VPP_BE_HDMITX_VENDOR_INFOFRM_PKT = 0x81,
    VPP_BE_HDMITX_AVI_INFOFRM_PKT,
    VPP_BE_HDMITX_SPD_INFOFRM_PKT,
    VPP_BE_HDMITX_AUD_INFOFRM_PKT,
    VPP_BE_HDMITX_MPEG_INFOFRM_PKT,
    VPP_BE_HDMITX_MAX_PKT,
}VPP_BE_HDMITX_HOST_PKT_TYPE, *PVPP_BE_HDMITX_HOST_PKT_TYPE;

// Host packet transfer mode
typedef enum tagVPP_BE_HDMITX_HOST_PKT_TX_MODE
{
    VPP_BE_HDMITX_HOST_PKT_TX_ONCE = 0,
    VPP_BE_HDMITX_HOST_PKT_TX_EVERY_VSYNC,
    VPP_BE_HDMITX_HOST_PKT_TX_MAX_MODE
}VPP_BE_HDMITX_HOST_PKT_TX_MODE,*PVPP_BE_HDMITX_HOST_PKT_TX_MODE;

typedef union tagVPP_BE_HDMITX_AUDIO_BUS_PARAMS
{
    struct
    {
        int        ClkDelay;
        int        DataShift;
        int        DataJustification;
        int        LeftChnWordSelEdge;
        int        DataLatchingEdge;
        unsigned char       PortCfg; // Flag
    }I2SParams;
}VPP_BE_HDMITX_AUDIO_BUS_PARAMS, *PVPP_BE_HDMITX_AUDIO_BUS_PARAMS;

typedef struct tagVPP_BE_HDMITX_AUDIO_FMT_PARAMS
{
    int                                Layout;
    unsigned char                               WordLength;
    VPP_BE_HDMITX_AUDIO_INP_CLK_SEL     InputClk;
    unsigned int                              AcrN;
    unsigned int                              AcrCts;
    unsigned char                               HbrAudio;
    unsigned char                               AudioFmt;
}VPP_BE_HDMITX_AUDIO_FMT_PARAMS, *PVPP_BE_HDMITX_AUDIO_FMT_PARAMS;

typedef struct tagVPP_BE_HDMITX_VIDEO_FMT_PARAMS
{
    // RGB/YCbCr
    int  VideoFmt;
    // Display Resolution
    int  DispRes;
    // Color Depth
    int ColorDepth;
    // Pixel Repetition
    VPP_BE_HDMITX_PIXEL_RPT_TYPE PixelRpt;
}VPP_BE_HDMITX_VIDEO_FMT_PARAMS, *PVPP_BE_HDMITX_VIDEO_FMT_PARAMS;

typedef struct tagVPP_BE_HDMITX_AUDIO_CHN_STS
{
    unsigned char       CpBit;
    unsigned char       PreEmphasisInfo;
    unsigned char       CategoryCode;
    unsigned char       SrcNum;
    unsigned char       ChnNum;
    unsigned char       SampFreq;
    unsigned char       ClkAccuracy;
    unsigned char       MaxAudSampLen;
    unsigned char       WordLength; //Based on MaxAudSampLen
    unsigned char       OrigSampFreq;
}VPP_BE_HDMITX_AUDIO_CHN_STS, *PVPP_BE_HDMITX_AUDIO_CHN_STS;

/*-----------------------------------------------------------------------------
 * Function Prototypes
 *-----------------------------------------------------------------------------
 */
/*-----------------------------------------------------------------------------
 * Description  : This function sets the default configuration values to the
 *              : hardware registers
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_LoadDefaultVal(THINVPP_OBJ *vpp_obj);

/*-----------------------------------------------------------------------------
 * Description  : This function enables audio packet transfer
 * Arguments    : EnAudio - Flag to enable/disable audio packet transmission
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_EnableAudioPkt(THINVPP_OBJ *vpp_obj,int EnAudio);

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
                                PVPP_BE_HDMITX_VIDEO_FMT_PARAMS pVideoParams);

/*-----------------------------------------------------------------------------
 * Description  : This function enables GCP packet transfer
 * Arguments    : EnableGCP - Flag to indicate GCP enable/disable
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_EnableGCP(THINVPP_OBJ *vpp_obj,int EnableGCP);

/*-----------------------------------------------------------------------------
 * Description  : This function mutes audio and/or video
 * Arguments    : audio - Enable/Disable audio mute
 *              : video - Enable/Disable vidio mute
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetMute(THINVPP_OBJ *vpp_obj,int Audio, int Video);

/*-----------------------------------------------------------------------------
 * Description  : This function returns audio and video mute status
 * Arguments    : pAudio - Pointer to return audio mute status (Output)
 *              : pVideo - Pointer to return video mute status (Output)
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_GetMuteSts(THINVPP_OBJ *vpp_obj,int *pAudio, int *pVideo);

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
                          VPP_BE_HDMITX_HOST_PKT_TX_MODE PktTxMode);

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
                             VPP_BE_HDMITX_HOST_PKT_TX_MODE PktTxMode);

/*-----------------------------------------------------------------------------
 * Description  : This function stores host packet data at the given index
 * Arguments    : pktIndex   - Packet Index
 *              : pPktData   - Pointer to return packet data
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetHostPktTxData(THINVPP_OBJ *vpp_obj, unsigned char pktIndex, unsigned char *pPktData);

/*-----------------------------------------------------------------------------
 * Description  : This function clears host packet data at the given index
 * Arguments    : pktIndex   - Packet Index
 *              : bcmType - bcm buffer register programming goes to
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_ClearHostPktTxData(THINVPP_OBJ *vpp_obj, unsigned char pktIndex, unsigned char bcmType);

/*-----------------------------------------------------------------------------
 * Description  : This function synchronizes internal software status
 *              : of host packet control in case of transmit once packets
 * Arguments    : pPktTxOnceStatus - Pointer to return transmit once status
 *              :                  - of each packet (Output)
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SyncHostPktTxOnceStatus(THINVPP_OBJ *vpp_obj, unsigned char *pPktTxOnceStatus);

/*-----------------------------------------------------------------------------
 * Description  : This function resets the FIFO between Hdmi Tx and PHY
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 * Notes        : Register TDATA_0 is used for doing this reset in Berlin
 *              : Ax platforms
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_ResetFifo(THINVPP_OBJ *vpp_obj);

/*-----------------------------------------------------------------------------
 * Description  : This function enables/disables PHY FIFO
 * Arguments    : enable   - TRUE/FALSE to control PHY FIFO
 *              : bufWrite - True to use bcm buffer, False to write directly
 * Returns      : MV_THINVPP_OK on success
 * Notes        : Register TDATA_0 is used for doing this reset in Berlin
 *              : Ax platforms
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_EnablePhyFifo(THINVPP_OBJ *vpp_obj, int enable, int bufWrite);

/*-----------------------------------------------------------------------------
 * Description  : This function sets HDMI/DVI output mode
 * Arguments    : OutMode - HDMI/DVI Mode
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMITX_SetMode(THINVPP_OBJ *vpp_obj,VPP_BE_HDMITX_OUT_MODE OutMode);

/* HDMI PHY APIs */
/*-----------------------------------------------------------------------------
 * Description  : This function sets the default configuration values to the
 *              : PHY registers
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMIPHY_LoadDefaultVal (THINVPP_OBJ *vpp_obj);

/*-----------------------------------------------------------------------------
 * Description  : This function enables/disables HDMI TMDS
 * Arguments    : Enable - True/False to control TMDS
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_HDMIPHY_EnableTmds (THINVPP_OBJ *vpp_obj,int Enable);

#endif // __VPP_BE_HDMITX_H__
