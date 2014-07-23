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

#ifndef _VPP_CPCB_OVL_H_
#define _VPP_CPCB_OVL_H_

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/**********************************************************************
*Type definition for CPCB OVL block driver                                                             *
***********************************************************************/

/*Enum for OVL unit number*/
 typedef enum VPP_CPCB_OVL_UNIT_NUM_T
 {
     VPP_CPCB_OVL0	= 0,
     VPP_CPCB_OVL1,
     VPP_CPCB_OVL2,
     VPP_CPCB_OVL_MAX
 }VPP_CPCB_OVL_UNIT_NUM, *PVPP_CPCB_OVL_UNIT_NUM;

 typedef enum VPP_CPCB_OVL_CHANNEL_T
 {
     VPP_CPCB_OVL_CHANNEL_MAIN = 0,
     VPP_CPCB_OVL_CHANNEL_PIP,
     VPP_CPCB_OVL_CHANNEL_OSD0,
     VPP_CPCB_OVL_CHANNEL_OSD1,
     VPP_CPCB_OVL_CHANNEL_MAX

 }VPP_CPCB_OVL_ZORDER;

typedef enum VPP_OVL_PLANE_UNIT_NUM_T
{
    Vpp_OVL_PLANE0 = 0,
    Vpp_OVL_PLANE1,
    Vpp_OVL_PLANE2,
    Vpp_OVL_PLANE3,
    Vpp_OVL_PLANE3A,
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    Vpp_OVL_PLANE3B,
    Vpp_OVL_PLANE3C,
    Vpp_OVL_PLANE3D,
#endif
}VPP_OVL_PLANE_UNIT_NUM;

typedef enum VPP_OVL_OSD_MODE
{
    VPP_OVL_OSD_MODE_NORMAL = 0 ,
    VPP_OVL_OSD_MODE_MATTE
}VPP_OVL_OSD_MODE;

typedef enum VPP_OVL_OSD_DOMAIN
{
    VPP_OVL_OSD_YUV_DMN = 0,
    VPP_OVL_OSD_RGB_DMN,
}VPP_OVL_OSD_DOMAIN;

typedef struct VPP_OVL_OSD_CTRL
{
    int	OSdDomain;
    int	OsdMode;
}VPP_OVL_OSD_CTRL, *PVPP_OVL_OSD_CTRL;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
typedef union VPP_OVL_AL_POL_T {
    struct {
        unsigned int p1:  1;
        unsigned int p2:  1;
        unsigned int p3:  1;
        unsigned int p3a:  1;
        unsigned int p3b:  1;
        unsigned int p3c:  1;
        unsigned int p3d:  1;
    } field;

    unsigned int data;
} VPP_OVL_AL_POL, *PVPP_OVL_AL_POL;

typedef struct VPP_OVL_LUMAKEY_CTRL
{
    unsigned int enable;
    unsigned int v_key_min;
    unsigned int y_key_min;
    unsigned int u_key_min;
    unsigned int v_key_max;
    unsigned int y_key_max;
    unsigned int u_key_max;
}VPP_OVL_LUMAKEY_CTRL, *PVPP_OVL_LUMAKEY_CTRL;
#endif

/**********************************************************************
*Function definition for CPCB OVL block driver                                                        *
***********************************************************************/

/***************************************************************************************
 * FUNCTION: load the default register values of CPCB OVL block
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL default values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int OvlUnit);

/***************************************************************************************
 * FUNCTION: set the OSD Overlay mode and domain
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               pZOrder - *pZOrder for layer1 channel selection, *(pZOrder+1) for layer2 channel selection.....
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetChannelOrder(THINVPP_OBJ *vpp_obj, int OvlUnit, int *pZOrder);

/***************************************************************************************
 * FUNCTION: set the OSD Overlay mode and domain
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               OsdCtrl - structure of mode and domain
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetCtrl(THINVPP_OBJ *vpp_obj, int OvlUnit, PVPP_OVL_OSD_CTRL pOsdCtrl);

/***************************************************************************************
 * FUNCTION: set the OSD Overlay mode and domain
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               plane - plane1 or plane2
 *               PlaneAlpha - alpha value
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetPlaneAlpha(THINVPP_OBJ *vpp_obj, int OvlUnit, int plane, unsigned int PlaneAlpha);

/***************************************************************************************
 * FUNCTION: set weighting factor for blending Main and Pip
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               BlendFactor - weighting factor for blending Main and Pip
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetVideoBlendingFactor(THINVPP_OBJ *vpp_obj, int OvlUnit, unsigned int BlendFactor);

/***************************************************************************************
 * FUNCTION: set the fixed color associated with each backend plane
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *         plane - plane number
 *         Color - plane fix color value
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetPlaneColor(THINVPP_OBJ *vpp_obj, int OvlUnit, int Plane, unsigned int Color);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/***************************************************************************************
 * FUNCTION: set plane's border alpha
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *         plane - plane number
 *         alpha - alpha value
 * RETURN:  1 - succeed
 *          others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetBorderAlpha(THINVPP_OBJ *vpp_obj, int OvlUnit, int plane, int alpha);
#endif

#endif/*_VPP_CPCB_OVL_H_*/
