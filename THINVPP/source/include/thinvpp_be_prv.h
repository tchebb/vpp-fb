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

#ifndef _VPP_BE_PRV_H_
#define _VPP_BE_PRV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thinvpp_api.h"
#include "vpp_be_hdmitx.h"

#define MAX_RES_INFO            64
#define HDMITX_MAX_FIFO_SIZE    10
#define HDMITX_TIMER_CONFIG     100 // in milliseconds

#define HDMITX_AUDIO_CBIT       0x0
#define HDMITX_AUDIO_UBIT       0x1
#define HDMITX_AUDIO_VBIT       0x2

#define HDMITX_INC_TIMER_CMD_CNTR(max,cur) (((cur)==((max)+1))?((max)+1):((cur)+1))


typedef struct BE_HDMITX_DATA_T {
    // Video Settings
    VPP_BE_HDMITX_VIDEO_FMT_PARAMS videoParams;

    // Rx Connected State
    volatile int           rxConnected;

    // Current output mode
    int                    curOutHdmiMode;

    int                     frameCntr;
} BE_HDMITX_DATA, *PBE_HDMITX_DATA;

/*******************************************************************
 * FUNCTION: config Hdmi HPD pin
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
static void HdmiHpdConfig();

/*******************************************************************
 * FUNCTION: Reset Hdmi Tx components
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxReset(THINVPP_OBJ *vpp_obj);

/*******************************************************************
 * FUNCTION: Initialize Hdmi Tx - allocate memory for data storage
 *         : and create required OS components
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxInit (THINVPP_OBJ *vpp_obj);

/*******************************************************************
 * FUNCTION: Handle hot plug event
 * PARAMS:   *vpp_obj - pointer to VPP object
 *       :   rxConnected - Indicates if receiver is connected/
 *       :                 disconnected
 * RETURN:   MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxHandleHotPlug (THINVPP_OBJ *vpp_obj, int rxConnected);

/*******************************************************************
 * FUNCTION: Construct AVI info frame packet
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN:   MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxConfigAVIInfoFrame (THINVPP_OBJ *vpp_obj,
                                     int aspRatio, int scanInfo,
                                     int extCalorimetry, int newFrame);

#ifdef __cplusplus
}
#endif

#endif // _VPP_BE_PRV_H_
