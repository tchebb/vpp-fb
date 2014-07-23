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

#ifndef _VPP_CPCB_INT_H_
#define _VPP_CPCB_INT_H_

/**********************************************************************
*Type definition for CPCB INT block driver                                                                *
***********************************************************************/

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/*Enum for INT unit number*/
 typedef enum VPP_CPCB_INT_UNIT_NUM
 {
     VPP_CPCB_INT0	= 0,
     VPP_CPCB_INT1,
     VPP_CPCB_INT2,
     VPP_CPCB_INT_MAX
 }VPP_CPCB_INT_UNIT_NUM;

/*weight for common usage*/
typedef enum VPP_CPCB_INT_WEIGHT
{
    VPP_CPCB_INT_BOTTOM_LINE_DROPING = 0,
    VPP_CPCB_INT_AVERAGING = 128,
    VPP_CPCB_INT_TOP_LINE_DROPING = 256,
}VPP_CPCB_INT_WEIGHT;

/*interlacer sync mode*/
typedef enum VPP_CPCB_INT_SYNC_MODE
{
    VPP_CPCB_INT_FREE_RUN = 0,
    VPP_CPCB_INT_SYNC_WITH_FE,
    VPP_CPCB_INT_SYNC_WITH_FE_INVERT,
}VPP_CPCB_INT_SYNC_MODE;

/*interlacer control data structure*/
typedef struct VPP_CPCB_INT_CTRL_T
{
    unsigned int	SyncMode;
    unsigned int	FieldPol;
    unsigned int	BitMode;
}VPP_CPCB_INT_CTRL, *PVPP_CPCB_INT_CTRL;

/*interlacer parameters data structure*/
typedef struct VPP_CPCB_INT_PARAMS_T
{
    unsigned int	MemSize;
    unsigned int	FsampX;
    unsigned int	FsampY;
    unsigned int	VsyncS;
    unsigned int	VsyncE;
    unsigned int	HsyncS;
    unsigned int	HsyncE;
    unsigned int	VsampEven;
    unsigned int	VsampOdd;
    unsigned int	YBlankVal;
    unsigned int	CBlankVal;
}VPP_CPCB_INT_PARAMS, *PVPP_CPCB_INT_PARAMS;

/**********************************************************************
*Function definition for CPCB FGG block driver                                                        *
***********************************************************************/

/***************************************************************************************
 * FUNCTION: load the default register values of CPCB interlacer block
 * PARAMS: IntUnit - INT unit number(INT0, INT1)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_INT_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int IntUnit);

/***************************************************************************************
 * FUNCTION: enable or disable interlacer in CPCB0 or CPCB1
 * PARAMS: IntUnit - INT unit number(INT0, INT1)
 *               Enable - 1: enable, 0: disable
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_INT_Enable(THINVPP_OBJ *vpp_obj, int IntUnit, unsigned int Enable);

/***************************************************************************************
 * FUNCTION: set interlacer parameters, include HVsync positions, VsampX and YC blank values
 * PARAMS: IntUnit - INT unit number(INT0, INT1)
 *               pParams - pointer to interlacer parameters structure
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int CPCB_INT_SetParams(THINVPP_OBJ *vpp_obj, int IntUnit, PVPP_CPCB_INT_PARAMS pParams);

#endif
