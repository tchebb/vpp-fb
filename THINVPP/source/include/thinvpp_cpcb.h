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

#ifndef _VPP_CPCB_H_
#define _VPP_CPCB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************/
/********************** CPCB APIs ******************/
/*************************************************/

/*******************************************************************
 * FUNCTION: Reset all VPP CPCB blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_Reset(THINVPP_OBJ *vpp_obj);

/**********************************************************************
 * FUNCTION: initialize all VPP CPCB blocks according to configuration
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 *********************************************************************/
int THINVPP_CPCB_Config(THINVPP_OBJ *vpp_obj);

/******************************************************************
 * FUNCTION: set CPCB plane blending factor and background color
 * PARAMS: *vpp_obj - pointer to VPP obj
 *          dvID - CPCB ID
 *          layerID - CPCB layer ID
 *          alpha - alpha of CPCB layer
 *          bgcolor - background color of CPCB layer
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_SetPlaneAttribute(THINVPP_OBJ *vpp_obj, int dvID, int layerID, int alpha, int bgcolor);

/******************************************************************
 * FUNCTION: set CPCB plane background window
 * PARAMS: *vpp_obj - pointer to VPP obj
 *          dvID - CPCB ID
 *          layerID - CPCB layer ID
 *          x - x of layer background window
 *          y - y of layer background window
 *          width - width of layer background window
 *          height - height of layer background window
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_SetPlaneBGWindow(THINVPP_OBJ *vpp_obj, int dvID, int layerID, int x, int y, int width, int height);

/******************************************************************
 * FUNCTION: set CPCB plane source window
 * PARAMS: *vpp_obj - pointer to VPP obj
 *          dvID - CPCB ID
 *          layerID - CPCB layer ID
 *          x - x of layer source window
 *          y - y of layer source window
 *          width - width of layer source window
 *          height - height of layer source window
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_SetPlaneSourceWindow(THINVPP_OBJ *vpp_obj, int dvID, int layerID, int x, int y, int width, int height);

#endif

/*******************************************************************
 * FUNCTION: set VPP CPCB output resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *         dvID - CPCB ID
 *         resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_SetOutputResolution(THINVPP_OBJ *vpp_obj, int dvID, int resID);

#ifdef __cplusplus
}

#endif
