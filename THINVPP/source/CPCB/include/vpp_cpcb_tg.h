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

#ifndef _VPP_CPCB_TG_H_
#define _VPP_CPCB_TG_H_

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/**********************************************************************
*Data structure definitions for CPCB TG block driver                                                *
***********************************************************************/

//temporarily put here
typedef struct VPP_POINT
{
    unsigned int X;
    unsigned int Y;

}VPP_POINT, *PVPP_POINT;

typedef struct VPP_WINDOW_T
{
    VPP_POINT TopLeft;
    VPP_POINT BottomRight;

}VPP_WINDOW, *PVPP_WINDOW;

/*Enum for CPCB0 and CPCB1 TG plane*/
 typedef enum VPP_CPCB_TG_PLANE
{
    TG_PLANE0_BASE = 0,
    TG_PLANE1_MAIN,
    TG_PLANE1_MAIN_CROP1,
    TG_PLANE1_MAIN_CROP2,
    TG_PLANE2_PIP,
    TG_PLANE2_PIP_CROP1,
    TG_PLANE2_PIP_CROP2,
    TG_PLANE3,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    TG_PLANE3_CROP,
#endif
    TG_PLANE3A,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    TG_PLANE3A_CROP,
    TG_PLANE3B,
    TG_PLANE3C,
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    TG_PLANE3C_CROP,
#endif
    TG_PLANE3D,
#endif
    TG_PLANE4_BASE_BORDER,
    TG_PLANE5_MAIN_BORDER,
    TG_PLANE6_PIP_BORDER,
    TG_PLANE7_BORDER,
    TG_PLANE7A_BORDER,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    TG_PLANE7B_BORDER,
    TG_PLANE7C_BORDER,
    TG_PLANE7D_BORDER,
#endif
    TG_PLANE_MAX

}VPP_CPCB_TG_PLANE,*PVPP_CPCB_TG_PLANE;

/*Enum for CPCB clock select*/
typedef enum VPP_CPCB_CLK_SEL
{
    VPP_CPCB_CLK_DISABLE = -1,
    VPP_CPCB_CLK_D1,
    VPP_CPCB_CLK_D2,
    VPP_CPCB_CLK_D4,
    VPP_CPCB_CLK_D6,
    VPP_CPCB_CLK_D8,
    VPP_CPCB_CLK_D12,
    VPP_CPCB_CLK_D3,
    VPP_CPCB_CLK_MAX

}VPP_CPCB_CLK_SEL;

 /*structure of horizontal and vertical total pixels*/
 typedef struct VPP_CPCB_TG_HVTOTAL_T
{
    unsigned int  HTotal;	  // H Total Active and Inactive Pixels
    unsigned int  VTotal;		  // V Total Active and Inactive Pixels

} VPP_CPCB_TG_HVTOTAL, *PVPP_CPCB_TG_HVTOTAL;

/*timing generator parameters*/
 typedef struct VPP_CPCB_TG_PARAMS_T
{
    unsigned int  Vsampx;            // Horizontal Pos at which Vertical active data begins
    unsigned int  FrameReset;      // Pos in the blank interval when frame reset is generated.
    unsigned int  HSyncStartPos;  // H Sync Start Position
    unsigned int  HSyncEndPos;    // H Sync End Position
    unsigned int  VSyncStartPos;  // V Sync Start Position
    unsigned int  VSyncEndPos;    // V Sync End Position

} VPP_CPCB_TG_PARAMS, *PVPP_CPCB_TG_PARAMS;

/**********************************************************************
*Function definitions for CPCB TG block driver                                                           *
***********************************************************************/

/***************************************************************************************
 * FUNCTION: load the default register values for CPCB TG block
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int CpcbUnit);

/**************************************************************************************
 * FUNCTION: start the timing generator by set horizontal and vertical total
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *                HVtotal - horizontal and vertical total values
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_SetHVTotal(THINVPP_OBJ *vpp_obj, int CpcbUnit, PVPP_CPCB_TG_HVTOTAL pHVtotal);

  /**************************************************************************************
 * FUNCTION: set the CPCB TG params
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *                CpcbTgParams - TG params
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_SetParams(THINVPP_OBJ *vpp_obj, int CpcbUnit, PVPP_CPCB_TG_PARAMS pCpcbTgParams);

  /**************************************************************************************
 * FUNCTION: set the the window position for one plane in the backend. can be used to disable a plane by setting the window to 0
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *               CpCbPlane - CPCB plane number
 *               WindowPos - plane window position
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG default values to BCM buffer
 ***************************************************************************************/
int CPCB_TG_SetPlaneWindow(THINVPP_OBJ *vpp_obj, int CpcbUnit, int CpCbPlane, PVPP_WINDOW pWindowPos);

  /**************************************************************************************
 * FUNCTION: set CPCB TG actual clock
 * PARAMS: CpcbUnit - CPCB unit number(CPCB0, CPCB1, CPCB2)
 *               ClkSel - CPCB clock selector
 * RETURN:  1 - succeed
 *                others - failed to load CPCB TG clock selection to BCM buffer
 ***************************************************************************************/
int CPCB_TG_ClkSelect(THINVPP_OBJ *vpp_obj, int CpcbUnit, int ClkSel);

#endif
