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

#ifndef _THINVPP_BE_H_
#define _THINVPP_BE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thinvpp_module.h"

#define VPP_BE_SET_BIT(data,index) \
   ((data) |= (1 << (index)))
#define VPP_BE_GET_BIT(data,index) \
   ((data) >> (index))
#define VPP_BE_CLR_BIT(data,index) \
   ((data) &= ~(1 << (index)))

#define VPP_BE_HDMI_HPD_INTR            0
#define VPP_BE_HDMI_HDCP_INTR           1
#define VPP_BE_HDMI_CEC_INTR            2

#define VPP_BE_HDMI_HDCP_FRMTRIG        0
#define VPP_BE_HDMI_HOST_PKT_FRMTRIG    1
#define VPP_BE_HDMI_SIG_FIFO_FRMTRIG    2

#define VPP_BE_CPCB0_INTR				3

/* Mux control for the selection of input data.*/
typedef enum VPP_VOP_SELECT_INPUT_T
{
    VPP_VOP_CPCB0_PROG = 0,
    VPP_VOP_CPCB0_INTER,
    VPP_VOP_CPCB1_PROG,
    VPP_VOP_CPCB1_INTER,//not used in B0
    VPP_VOP_CPCB2_PROG,
    VPP_VOP_CPCB2_INTER, // not used in A0
    VPP_VOP_NO_INPUT,
    VPP_VOP_INP_MAX

}VPP_VOP_SELECT_INPUT,*PVPP_VOP_SELECT_INPUT;


/*************************************************/
/********************** BE APIs ******************/
/*************************************************/

/*******************************************************************
 * FUNCTION: Reset all VPP BE blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_Reset(THINVPP_OBJ *vpp_obj);

/*********************************************************************
 * FUNCTION: initialize all VPP BE blocks according to configuration
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ********************************************************************/
int THINVPP_BE_Config(THINVPP_OBJ *vpp_obj);

/*******************************************************************
 * FUNCTION: select input for VOUTs in VPP BE blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           voutID - Vout
 *           cpcbout - CPCB output ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetVoutInput(THINVPP_OBJ *vpp_obj, int voutID, int cpcbout);

/*******************************************************************
 * FUNCTION: select input for VOUTs in VPP BE blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           voutID - Vout
 *           color_fmt - CPCB output color format
 *           bit_depth - CPCB output bit depth
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetVoutFormat(THINVPP_OBJ *vpp_obj, int voutID, int color_fmt, int bit_depth);

/*******************************************************************
 * FUNCTION: set HDMI resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHdmiResolution(THINVPP_OBJ *vpp_obj, int resID);

/*******************************************************************
 * FUNCTION: set HD DAC oversampling rate
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - HD resolution ID
 *           ovsmpl - oversampling rate
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHDacOversampling(THINVPP_OBJ *vpp_obj, int resID, int ovsmpl);


/*******************************************************************
 * FUNCTION: set SD DAC oversampling rate
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           ovsmpl - oversampling rate
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetSDacOversampling(THINVPP_OBJ *vpp_obj, int ovsmpl);

/*******************************************************************
 * FUNCTION: set HD DAC resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHDacResolution(THINVPP_OBJ *vpp_obj, int resID);

/*******************************************************************
 * FUNCTION: set SD DAC resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetSDacResolution(THINVPP_OBJ *vpp_obj, int resID);

/*******************************************************************
 * FUNCTION: set TTL24 resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetTtl24Resolution(THINVPP_OBJ *vpp_obj, int resID);

/*******************************************************************
 * FUNCTION: set TTL30 resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetTtl30Resolution(THINVPP_OBJ *vpp_obj, int resID);

/*******************************************************************
 * FUNCTION: mute AHD/ASD output
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           mute - 1: mute 0:un-mute
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetDacMute(THINVPP_OBJ *vpp_obj, int mute, int vout);

/********************************************************************************
 * FUNCTION: Set Hdmi Video format
 * INPUT: *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_SetHdmiVideoFmt(THINVPP_OBJ *vpp_obj);

/*******************************************************************
 * FUNCTION: set HDMI audio format
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           sampFreq - Sampling frequency
 *           sampSize - Word Size
 *           mClkFactor - 128/256/384/512 times frequency
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHdmiAudioFmt(THINVPP_OBJ *vpp_obj, int enable);

/*******************************************************************
 * FUNCTION: Configure Audio VUC data
 * PARAMS:   *vpp_obj       - pointer to VPP object
 *           pVUCCfg        - pointer to VUC config structure
 *           loadOnAudioCfg - 1 for loading these data when audio
 *                          - is configured subsequently
 *                          - 0 for loading it on the next VBI
 *           pVUCUpdateReqd - pointer to indicate if update is
 *                          - required on the next VBI interrupt
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_ConfigHdmiAudioVUCBits(THINVPP_OBJ *vpp_obj,
                                  VPP_HDMI_AUDIO_VUC_CFG *pVUCCfg,
                                  int loadOnAudioCfg, int *pVUCUpdateReqd);

/*******************************************************************
 * FUNCTION: Set Audio VUC data
 * PARAMS:   *vpp_obj         - pointer to VPP object
 *           vucUpdateSetting - audio VUC bit update setting
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHdmiAudioVUCBits(THINVPP_OBJ *vpp_obj, int vucUpdateSetting);

/*******************************************************************
 * FUNCTION: Set/Clear Hdmi audio fifo reset
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           bSet     - TRUE/FALSE to set/clear the audio fifo reset
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHdmiAudioFifoReset(THINVPP_OBJ *vpp_obj, int bSet);

/*******************************************************************
 * FUNCTION: mute Hdmi video/audio
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           video - video/audio to be muted
 *           mute - 1: mute 0:un-mute
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHdmiMute (THINVPP_OBJ *vpp_obj, int video, int muteEn);

/********************************************************************************
 * FUNCTION: Set Hdmi output mode (Hdmi/Dvi)
 * INPUT: hdmiMode - 0:DVI, 1:HDMI
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_SetHdmiMode(THINVPP_OBJ *vpp_obj, int hdmiMode);

/********************************************************************************
 * FUNCTION: Configure Hdmi Video format
 * INPUT: color_fmt - color format (RGB, YCbCr 444, 422)
 *      : bit_depth - 8/10/12 bit color
 *      : pixel_rept - 1/2/4 repetitions of pixel
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_ConfigHdmiVideoFmt(THINVPP_OBJ *vpp_obj, int color_fmt,
                              int bit_depth, int pixel_rept);

/*******************************************************************
 * FUNCTION: set HDMI audio format
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           sampFreq - Sampling frequency
 *           sampSize - Word Size
 *           mClkFactor - 128/256/384/512 times frequency
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_ConfigHdmiAudioFmt(THINVPP_OBJ *vpp_obj, int enable,
                              VPP_HDMI_AUDIO_CFG *pAudioCfg);

/********************************************************************************
 * FUNCTION: Set HDMI Video Information
 * INPUT: aspect ratio
 *      : scan info
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_SetHdmiVideoInfo(THINVPP_OBJ *vpp_obj, int aspRatio, int scanInfo);

/********************************************************************************
 * FUNCTION: Set HDMI Audio Information
 * INPUT: Speaker Mapping
 *      : Level Shift Value
 *      : Down Mix Inhibit Flag
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_SetHdmiAudioInfo(THINVPP_OBJ *vpp_obj, int spkrAlloc,
                            int lvlShiftVal, int downMixInhFlag);

/********************************************************************************
 * FUNCTION: Register for HDMI event notifications
 * INPUT: eventCode - Event code for which notifications has to be raised
 *      : cbFnAddr - Address of callback function
 *      : contextParam - Context parameter for the registering application
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_HdmiRegisterCB(THINVPP_OBJ *vpp_obj, unsigned int eventCode,
                          unsigned int cbFnAddr, unsigned int contextParam);

/********************************************************************************
 * FUNCTION: Unregister for HDMI event notifications
 * INPUT: eventCode - Event code for which notifications has to be raised
 *      : cbFnAddr - Address of callback function
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_HdmiUnregisterCB(THINVPP_OBJ *vpp_obj);

/********************************************************************************
 * FUNCTION: Format HDMI Auxillary Packet
 * INPUT: enable    - To handle packet enable/disable
 *      : pktType   - Packet type
 *      : pAuxPkt   - Pointer to aux packet data (Input)
 *      : pPktIndex - Packet index
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_HdmiFormatAuxPkt(THINVPP_OBJ *vpp_obj, int enable, VPP_HDMI_PKT_ID pktType,
                            VPP_HDMI_PKT *pAuxPkt, unsigned char *pPktIndex);

/********************************************************************************
 * FUNCTION: Send HDMI Auxillary Packet
 * INPUT: pktType    - Packet type
 *      : pktIndex   - Packet index
 *      : repeatPkt  - Transmit packet once/repeat every VSync
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_HdmiSendAuxPkt(THINVPP_OBJ *vpp_obj, VPP_HDMI_PKT_ID pktType,
                          unsigned char pktIndex, int repeatPkt);

/********************************************************************************
 * FUNCTION: Stop HDMI Auxillary Packet
 * INPUT: pktType   - Packet type
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_HdmiStopAuxPkt(THINVPP_OBJ *vpp_obj, VPP_HDMI_PKT_ID pktType);

#ifdef __cplusplus
}
#endif

#endif
