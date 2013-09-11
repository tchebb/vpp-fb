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

#ifndef _VPP_SCL_H_
#define _VPP_SCL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************/
/********************** SCL structure***************/
/*************************************************/
/*CPCB0 output resolution*/
typedef struct VPP_CPCB0_OUTPUT_RES_T
{
    unsigned int  HRes;
    unsigned int  VRes;
} VPP_CPCB0_OUTPUT_RES, *PVPP_CPCB0_OUTPUT_RES;

/*************************************************/
/********************** SCL APIs ******************/
/*************************************************/

/*******************************************************************
 * FUNCTION: Reset all VPP SCL blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_SCL_Reset(THINVPP_OBJ *vpp_obj);

/*********************************************************************
 * FUNCTION: initialize all VPP SCL blocks according to configuration
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ********************************************************************/
int THINVPP_SCL_Config(THINVPP_OBJ *vpp_obj);

/***************************************************************************************
 * FUNCTION: set BE FIFO for loopback
 * PARAMS: pCpcb0Tot - CPCB0 output total resolution
 *               pCpcb0Res - CPCB0 active resolution
 * RETURN:  1 - succeed
 *                others - failed to load CPCB BE FIFO values to BCM buffer
 ***************************************************************************************/
int THINVPP_SCL_SetBeFifo(THINVPP_OBJ *vpp_obj, PVPP_CPCB0_OUTPUT_RES pCpcb0Tot, PVPP_CPCB0_OUTPUT_RES pCpcb0Res);

#ifdef __cplusplus
}
#endif

#endif
