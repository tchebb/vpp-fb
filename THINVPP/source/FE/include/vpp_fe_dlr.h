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

#ifndef _VPP_FE_DLR_H_
#define _VPP_FE_DLR_H_

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/**********************************************************************
*Data structure definitions for FE DLR  block driver                                                 *
***********************************************************************/

#define PIXEL_PER_BEAT_YUV_422   4
#define PIXEL_PER_BEAT_ARGB_8888 2
#define PIXEL_PER_BEAT_LUT8      8

/*Enum for CSC mode*/
typedef enum VPP_FE_DLR_CSC_MODES
{
    VPP_FE_DLR_CSC_BYPASS_MODE = 0,
    VPP_FE_DLR_CSC_601_TO_709,
    VPP_FE_DLR_CSC_709_TO_601,
    VPP_FE_DLR_CSC_RGB_TO_YUV_709,
    VPP_FE_DLR_CSC_YUV_709_TO_RGB,
    VPP_FE_DLR_CSC_RGB_TO_YUV_601,
    VPP_FE_DLR_CSC_YUV_601_TO_RGB,
    VPP_FE_DLR_CSC_sRGB_TO_YUV_709,
    VPP_FE_DLR_CSC_YUV_709_TO_sRGB,
    VPP_FE_DLR_CSC_sRGB_TO_YUV_601,
    VPP_FE_DLR_CSC_YUV_601_TO_sRGB,
    VPP_FE_DLR_CSC_MAX_MODES
} VPP_FE_DLR_CSC_MODES;

/*Enum for dataloader in-line channel*/
typedef enum VPP_FE_DLR_CHANNEL
{
    VPP_FE_DLR_CHANNEL_BG = 0,
    VPP_FE_DLR_CHANNEL_MAIN,
    VPP_FE_DLR_CHANNEL_PIP,
    VPP_FE_DLR_CHANNEL_PG,
    VPP_FE_DLR_CHANNEL_IG,
    VPP_FE_DLR_CHANNEL_CURSOR,
    VPP_FE_DLR_CHANNEL_MOSD,
    VPP_FE_DLR_CHANNEL_OFFLINE, //used in loading defult value for BG and off-line scaling data loader
    VPP_FE_DLR_CHANNEL_MAX = VPP_FE_DLR_CHANNEL_OFFLINE

}VPP_FE_DLR_CHANNEL;

/*Enum for dataloader off-line channel*/
typedef enum VPP_FE_DLR_OFFLINE_CHANNEL
{
    VPP_FE_DLR_OFFLINE_MAIN_W = 0,
    VPP_FE_DLR_OFFLINE_MAIN_R,
    VPP_FE_DLR_OFFLINE_PIP_W,
    VPP_FE_DLR_OFFLINE_PIP_R,
    VPP_FE_DLR_OFFLINE_AUX_W,
    VPP_FE_DLR_OFFLINE_AUX_R,
    VPP_FE_DLR_SEL_MAX

}VPP_FE_DLR_OFFLINE_CHANNEL;

/*input data format*/
typedef enum VPP_FE_DLR_FMT_SRC_FMT
{
    VPP_FE_DLR_SRC_FMT_YUV422 = 0,
    VPP_FE_DLR_SRC_FMT_ARGB32 = 0,
    VPP_FE_DLR_SRC_FMT_ARGB24,
    VPP_FE_DLR_SRC_FMT_ARGB4444,
    VPP_FE_DLR_SRC_FMT_RGB565,
    VPP_FE_DLR_SRC_FMT_ARGB1555,
    VPP_FE_DLR_SRC_FMT_LUT8,
    VPP_FE_DLR_SRC_FMT_MAX

}VPP_FE_DLR_FMT_SRC_FMT;

/*input data components order in OSD or PG graphic planes. In B0, for graphic planes*/
typedef enum VPP_FE_DLR_FMT_ORDER_OSD_PG
{
    VPP_FE_DLR_ORDER_OSD_PG_ARGB = 0,
    VPP_FE_DLR_ORDER_OSD_PG_ABGR,
    VPP_FE_DLR_ORDER_OSD_PG_RGBA,
    VPP_FE_DLR_ORDER_OSD_PG_BGRA,
    VPP_FE_DLR_ORDER_OSD_PG_MAX

}VPP_FE_DLR_FMT_ORDER_OSD_PG;

/*input data components order in PG graphic plane. In B0, for graphic planes*/
typedef enum VPP_FE_DLR_FMT_ORDER_PG
{
    VPP_FE_DLR_ORDER_PG_AVYU = 0,
    VPP_FE_DLR_ORDER_PG_AUYV,
    VPP_FE_DLR_ORDER_PG_VYUA,
    VPP_FE_DLR_ORDER_PG_UYVA,
    VPP_FE_DLR_ORDER_PG_MAX

}VPP_FE_DLR_FMT_ORDER_PG;

/*input data components order in video or PIP planes. In B0, for video planes*/
typedef enum VPP_FE_DLR_FMT_ORDER_VIDEO
{
    VPP_FE_DLR_ORDER_VIDEO_AVYU = 0,
    VPP_FE_DLR_ORDER_VIDEO_AUYV,
    VPP_FE_DLR_ORDER_VIDEO_VYUA,
    VPP_FE_DLR_ORDER_VIDEO_UYVA,
    VPP_FE_DLR_ORDER_VIDEO_MAX

}VPP_FE_DLR_FMT_ORDER_VIDEO;

/*input data format for main video*/
typedef enum VPP_FE_DLR_MAIN_INPUT_FMT
{
    VPP_FE_DLR_MAIN_INTERLACED = 0,
    VPP_FE_DLR_MAIN_PROGRESSIVE

}VPP_FE_DLR_MAIN_INPUT_FMT;

/*data loader input resolution*/
typedef struct VPP_FE_DLR_INPUT_RES_T
{
    unsigned int HRes;
    unsigned int VRes;

}VPP_FE_DLR_INPUT_RES, *PVPP_FE_DLR_INPUT_RES;

/*data loader plane start location*/
typedef struct VPP_FE_DLR_PLANE_START_LOC_T
{
    unsigned int HLoc;
    unsigned int VLoc;

}VPP_FE_DLR_PLANE_START_LOC, *PVPP_FE_DLR_PLANE_START_LOC;

/*data loader plane input format*/
typedef struct VPP_FE_DLR_PLANE_DATA_FMT_T
{
    unsigned char SrcFmt;
    unsigned char FmtOrder;

}VPP_FE_DLR_PLANE_DATA_FMT, *PVPP_FE_DLR_PLANE_DATA_FMT;

/**********************************************************************
*Function definition for FE DLR block driver                                                             *
***********************************************************************/
/***************************************************************************************
 * FUNCTION: load default values of data loader to BCM buffer
 * PARAMS:  Channel - indicate the channel
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int Channel);

/***************************************************************************************
 * FUNCTION: clear all the FIFOs and pipline data inside the channel.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_ClearChannel(THINVPP_OBJ *vpp_obj, int Channel);

/***************************************************************************************
 * FUNCTION: Clear the asynchronous FIFO between the client and dHub, clear the start bit at the same time.
 * PARAMS: Channel - id of a front-end dataloader channel.
 *               Clear - 1:Clear the asynchronous FIFO, 0:don't clear, normal stare.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_ClearOffLineChannel(THINVPP_OBJ *vpp_obj, int Channel, int Clear);

/***************************************************************************************
 * FUNCTION: set the size of the plane.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 *                pPlaneSize - pointer to the struct of horizontal and vertial size.
 *                CropWpl - beat per line and crop
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetPlaneSize(THINVPP_OBJ *vpp_obj, int Channel, PVPP_FE_DLR_INPUT_RES pPlaneSize, unsigned int CropWpl);

/***************************************************************************************
 * FUNCTION: set input data format and order.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 *                pDataFmt - pointer to the struct of data format and order.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetPlaneDataFmt(THINVPP_OBJ *vpp_obj, int Channel, PVPP_FE_DLR_PLANE_DATA_FMT pDataFmt);

/***************************************************************************************
 * FUNCTION: enable the channel.
 * PARAMS:  Channel - id of a front-end dataloader channel.
 *                Enable - 1:enable, 0:no effect.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_EnableChannel(THINVPP_OBJ *vpp_obj, int Channel, int Enable);

/***************************************************************************************
 * FUNCTION: start data loader for BG(only in A0/A1) or off-line channel(main PIP AUX).
 * PARAMS: Channel - id of a front-end dataloader channel.
 *               Enable - 1:kick the hardware, 0:no effect on hardware.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBADPARAM - bad input parameters.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_EnableOffLineChannel(THINVPP_OBJ *vpp_obj, int Channel, int Enable);

/***************************************************************************************
 * FUNCTION: set total number of pixel for BG or off-line scaling channel(main PIP BE).
 * PARAMS: Channel - id of a front-end dataloader channel.
 *               pRes - pointer to struct of scaler output resolution
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetOffLineChannel(THINVPP_OBJ *vpp_obj, int Channel, PVPP_FE_DLR_INPUT_RES pRes);

/***************************************************************************************
 * FUNCTION: set dummy TG for main video channel.
 * PARAMS: TotRes - input total resolution.
 *                progressive - 1: prgressive, 0: interlaced.
 *                sensio - 1: sensio mode, 0: non-sensio mode.
 * RETURN:  MV_THINVPP_OK - succeed.
 *                MV_THINVPP_EBCMBUFFULL -BCM buffer is full.
 ***************************************************************************************/
int FE_DLR_SetDummyTG(THINVPP_OBJ *vpp_obj, PVPP_FE_DLR_INPUT_RES pTotRes, int progressive, int sensio);

int FE_DLR_SetVPDMX(THINVPP_OBJ *vpp_obj, PVPP_FE_DLR_INPUT_RES pTotRes, int progressive, int sensio);

#endif
