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

#define _VPP_CPCB_C_

#include "thinvpp_api.h"
#include "thinvpp_cfg.h"
#include "thinvpp_module.h"
#include "thinvpp_cpcb.h"
#include "vpp_cpcb_ee.h"
#include "vpp_cpcb_fgg.h"
#include "vpp_cpcb_ovl.h"
#include "vpp_cpcb_tg.h"
#include "vpp_cpcb_int.h"


              ///////////////////////////////////////////
              //                                       //
              //    CPCB functions for Berlin          //
              //                                       //
              ///////////////////////////////////////////

/*******************************************************************
 * FUNCTION: initialize all VPP CPCB blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_Reset(THINVPP_OBJ *vpp_obj)
{
    /* reset CPCB EE */
    CPCB_EE_LoadDefaultVal(vpp_obj);

    /* reset CPCB video-overlay */
    VPP_OVL_LoadDefaultVal(vpp_obj, VPP_CPCB_OVL0);
    VPP_OVL_LoadDefaultVal(vpp_obj, VPP_CPCB_OVL2);

    /* reset CPCB TG */
    CPCB_TG_LoadDefaultVal(vpp_obj, VPP_CPCB0);
    CPCB_TG_LoadDefaultVal(vpp_obj, VPP_CPCB2);

    /* reset CPCB interlacer */
    CPCB_INT_LoadDefaultVal(vpp_obj, VPP_CPCB_INT0);
    CPCB_INT_LoadDefaultVal(vpp_obj, VPP_CPCB_INT2);

    return (MV_THINVPP_OK);
}

/**********************************************************************
 * FUNCTION: Initialize all VPP CPCB blocks according to configuration
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 *********************************************************************/
int THINVPP_CPCB_Config(THINVPP_OBJ *vpp_obj)
{
    VPP_OVL_OSD_CTRL ovl_ctrl;
    int i, cpcbID, chanID;
    int order[7];

    /* set aux input selection */
    CPCB_SetFeedbackPath(vpp_obj, VPP_CPCB_PRG_OUT_TO_FE);

    /* set OSD overlay mode & domain for CPCBs */
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    for (cpcbID=CPCB_1; cpcbID<=CPCB_2; cpcbID++){
        ovl_ctrl.OSdDomain = VPP_OVL_OSD_YUV_DMN; // overlay happen in YUV domain
#if (BERLIN_CHIP_VERSION >= BERLIN_C_2)
#if !defined(BERLIN_C2_HACK)
        ovl_ctrl.OsdMode = VPP_OVL_OSD_MODE_NORMAL; //  in normal format
#else
        ovl_ctrl.OsdMode = VPP_OVL_OSD_MODE_MATTE; //  in matte format
#endif
#else
        ovl_ctrl.OsdMode = VPP_OVL_OSD_MODE_MATTE; //  in matte format
#endif
        VPP_OVL_SetCtrl(vpp_obj, cpcbID, &ovl_ctrl);
        VPP_OVL_SetPlaneAlpha(vpp_obj, cpcbID, Vpp_OVL_PLANE1, 0xff);
        VPP_OVL_SetPlaneAlpha(vpp_obj, cpcbID, Vpp_OVL_PLANE2, 0xff);
    }

#else
    for (cpcbID=CPCB_1; cpcbID<=CPCB_3; cpcbID++){
        ovl_ctrl.OSdDomain = VPP_OVL_OSD_YUV_DMN; // overlay happen in YUV domain
        if (vpp_obj->chan[CHAN_OSD].dvID == cpcbID) {
            ovl_ctrl.OsdMode = VPP_OVL_OSD_MODE_MATTE; // VOP mixer output matte format OSD data
            VPP_OVL_SetPlaneAlpha(vpp_obj, cpcbID, Vpp_OVL_PLANE1, 0xff);
        } else {
            ovl_ctrl.OsdMode = VPP_OVL_OSD_MODE_NORMAL; // normal format GFX data
            VPP_OVL_SetPlaneAlpha(vpp_obj, cpcbID, Vpp_OVL_PLANE1, 0x00);
        }
        VPP_OVL_SetCtrl(vpp_obj, cpcbID, &ovl_ctrl);
    }
#endif

    /* set z-order of CPCB layers */
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    for (cpcbID=CPCB_1; cpcbID<=CPCB_2; cpcbID++){
        order[0] = order[1] = order[2] = order[3] = order[4] = order[5] = order[6] = 0;
        for (i=0; i<vpp_obj->dv[cpcbID].num_of_chans; i++){
            chanID = vpp_obj->dv[cpcbID].chanID[i];
            if((vpp_obj->chan[chanID].zorder>=0) && (vpp_obj->chan[chanID].zorder<=6))
                order[vpp_obj->chan[chanID].zorder] = vpp_obj->chan[chanID].dvlayerID+1; // index from 1
        }
        VPP_OVL_SetChannelOrder(vpp_obj, cpcbID, order);
    }
#else
    for (cpcbID=CPCB_1; cpcbID<=CPCB_3; cpcbID++){
        order[0] = order[1] = order[2] = order[3] = 0;
        for (i=0; i<vpp_obj->dv[cpcbID].num_of_chans; i++){
            chanID = vpp_obj->dv[cpcbID].chanID[i];
            if((vpp_obj->chan[chanID].zorder>=0) && (vpp_obj->chan[chanID].zorder<=3))
                order[vpp_obj->chan[chanID].zorder] = vpp_obj->chan[chanID].dvlayerID+1; // index from 1
        }
        VPP_OVL_SetChannelOrder(vpp_obj, cpcbID, order);
    }
#endif

    return (MV_THINVPP_OK);
}

/******************************************************************
 * FUNCTION: set CPCB plane blending factor and background color
 * PARAMS: *vpp_obj - pointer to VPP obj
 *          cpcbID - CPCB ID
 *          layerID - CPCB layer ID
 *          alpha - alpha of CPCB layer
 *          bgcolor - background color of CPCB layer
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_SetPlaneAttribute(THINVPP_OBJ *vpp_obj, int cpcbID, int layerID, int alpha, int bgcolor)
{
    VPP_OVL_SetPlaneColor(vpp_obj, cpcbID, layerID+1, bgcolor);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    // set plane source global alpha
    if (layerID == CPCB1_PLANE_1){ /* global alpha only available for CPCB plane-1 */
        VPP_OVL_SetPlaneAlpha(vpp_obj, cpcbID, Vpp_OVL_PLANE1, alpha);
    } else if (layerID == CPCB1_PLANE_2){ /* global alpha only available for CPCB plane-2 */
        /* plane-2 alpha (weight) range: 0 - 128 */
        if (vpp_obj->chan[CHAN_MAIN].zorder < vpp_obj->chan[CHAN_PIP].zorder)
            VPP_OVL_SetVideoBlendingFactor(vpp_obj, cpcbID, (alpha+1)/2);
        else
            VPP_OVL_SetVideoBlendingFactor(vpp_obj, cpcbID, (256-alpha)/2);

        VPP_OVL_SetPlaneAlpha(vpp_obj, cpcbID, Vpp_OVL_PLANE2, alpha);
    }

    // set plane border global alpha
    VPP_OVL_SetBorderAlpha(vpp_obj, cpcbID, layerID+1, alpha);

#else
    if (layerID == CPCB1_PLANE_2){ /* global alpha only available for CPCB plane-2 */
        alpha = (alpha + 1) / 2; /* plane-2 alpha (weight) range: 0 - 128 */

#if !(BERLIN_CHIP_VERSION == BERLIN_A_2)
        if (!alpha)
            alpha = 1; /* there is a bug if alpha is 0 for plane-2 */
#endif

        VPP_OVL_SetVideoBlendingFactor(vpp_obj, cpcbID, alpha);

    }
#endif

    return (MV_THINVPP_OK);
}

/******************************************************************
 * FUNCTION: set CPCB plane background window
 * PARAMS: *vpp_obj - pointer to VPP obj
 *          cpcbID - CPCB ID
 *          layerID - CPCB layer ID
 *          x - x of layer display window
 *          y - y of layer display window
 *          width - width of layer display window
 *          height - height of layer display window
 * RETURN: MV_THINVPP_OK
 * NOTE: cropping need to be done before set background window.
 ******************************************************************/
int THINVPP_CPCB_SetPlaneBGWindow(THINVPP_OBJ *vpp_obj, int cpcbID, int layerID, int x, int y, int width, int height)
{
    VPP_WINDOW bgwin;

    bgwin.TopLeft.X = x;
    bgwin.TopLeft.Y = y;
    bgwin.BottomRight.X = x + width;
    bgwin.BottomRight.Y = y + height;

    switch (cpcbID){
        case CPCB_1:
        case CPCB_2:
            switch (layerID){
                case CPCB1_PLANE_1: /* CPCB plane 1 */
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE5_MAIN_BORDER, &bgwin);
                    break;
                case CPCB1_PLANE_2: /* CPCB plane 2 */
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE6_PIP_BORDER, &bgwin);
                    break;
                case CPCB1_PLANE_3: /* CPCB plane 3 = IG/G0 */
                    printk(KERN_INFO "pl3 setbg\n");
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE7_BORDER, &bgwin);
                    printk(KERN_INFO "pl3a setbg\n");
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE7A_BORDER, &bgwin);
                    break;
            }
            break;
        case CPCB_3:
            switch (layerID){
                case CPCB1_PLANE_1: /* CPCB plane 1 */
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE5_MAIN_BORDER, &bgwin);
                    break;
            }
            break;
    }

    return (MV_THINVPP_OK);
}

/*************************************************************************
 * FUNCTION: set CPCB plane source window
 * PARAMS: *vpp_obj - pointer to VPP obj
 *          cpcbID - CPCB ID
 *          layerID - CPCB layer ID
 *          x - x of layer source window
 *          y - y of layer source window
 *          width - width of layer source window
 *          height - height of layer source window
 * RETURN: MV_THINVPP_OK
 * NOTE: for CPCB source window, we do chopping in upper layer function
 *       because DataLoader and SCL also need source window chopping
 *       information.
 ************************************************************************/
int THINVPP_CPCB_SetPlaneSourceWindow(THINVPP_OBJ *vpp_obj, int cpcbID, int layerID, int x, int y, int width, int height)
{
    VPP_WINDOW window;

    window.TopLeft.X = x;
    window.TopLeft.Y = y;
    window.BottomRight.X = x + width;
    window.BottomRight.Y = y + height;

    switch (cpcbID){
        case CPCB_1:
        case CPCB_2:
            switch (layerID){
                case CPCB1_PLANE_1: /* CPCB plane 1 = MAIN */
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE1_MAIN, &window);
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE1_MAIN_CROP1, &window);
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE1_MAIN_CROP2, &window);
                    break;
                case CPCB1_PLANE_2: /* CPCB plane 2 = PIP */
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE2_PIP, &window);
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE2_PIP_CROP1, &window);
                    break;
                case CPCB1_PLANE_3: /* CPCB plane 3 = IG/G0 */
                    printk(KERN_INFO "pl3 wnd\n");
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE3, &window);
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE3_CROP, &window);
                    printk(KERN_INFO "pl3a wnd\n");
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE3A, &window);
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE3A_CROP, &window);
                    break;
            }
            break;
        case CPCB_3:
            switch (layerID){
                case CPCB1_PLANE_1: /* CPCB plane 1 */
                    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE1_MAIN, &window);
                    break;
            }
            break;
    }

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: set VPP CPCB output resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *         cpcbID - CPCB ID
 *         resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_CPCB_SetOutputResolution(THINVPP_OBJ *vpp_obj, int cpcbID, int resID)
{
    RESOLUTION_INFO *resinfo = (RESOLUTION_INFO *)&m_resinfo_table[resID];
    RESOLUTION_INFO *prog_resinfo = resinfo;
    RESOLUTION_INFO *intlr_resinfo = resinfo;
    VPP_CPCB_TG_HVTOTAL hvtot;
    VPP_CPCB_TG_PARAMS tg_params;
    VPP_CPCB_INT_PARAMS intlrtg_params;
    VPP_WINDOW window;
    int clk_ctrl;

    /* TODO: set TG clock according to CPCB resolution */
if (resID != RES_RESET) {
#if !defined(FPGA)
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
    if (m_resinfo_table[resID].freq <= 27027)
        clk_ctrl = VPP_CPCB_CLK_D4;
    else if (m_resinfo_table[resID].freq >= 148000)
        clk_ctrl = VPP_CPCB_CLK_D1;
    else
        clk_ctrl = VPP_CPCB_CLK_D2;
#else
    if (m_resinfo_table[resID].freq <= 27027)
        clk_ctrl = VPP_CPCB_CLK_D8;
    else if (m_resinfo_table[resID].freq >= 148000)
        clk_ctrl = VPP_CPCB_CLK_D2;
    else
        clk_ctrl = VPP_CPCB_CLK_D4;
#endif
#else
    clk_ctrl = VPP_CPCB_CLK_D1;
#endif
#else
    clk_ctrl = VPP_CPCB_CLK_D4;
#endif
    CPCB_TG_ClkSelect(vpp_obj, cpcbID, clk_ctrl);
}
    /* set CPCB end display resolution */
    hvtot.HTotal = resinfo->width-1;
    hvtot.VTotal = resinfo->height-1;
    CPCB_TG_SetHVTotal(vpp_obj, cpcbID, &hvtot);

    /* set CPCB TG timing parameters */
    if (resinfo->scan == SCAN_INTERLACED) {
        if ((resID == RES_1080I60) || (resID == RES_1080I5994))
            prog_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_1080P60];
        else if (resID == RES_1080I50)
            prog_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_1080P50];
        else if ((resID == RES_PAL_BGH) || (resID == RES_625I50))
            prog_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_625P50];
        else if ((resID == RES_NTSC_M) || (resID == RES_NTSC_J) || (resID == RES_PAL_M) || (resID == RES_525I60) || (resID == RES_525I5994))
            prog_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_525P60];
    } else {
        if ((resID == RES_1080P60) || (resID == RES_1080P5994))
            intlr_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_1080I60];
        else if (resID == RES_1080P50)
            intlr_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_1080I50];
        else if (resID == RES_625P50)
            intlr_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_625I50];
        else if ((resID == RES_525P60) || (resID == RES_525P5994))
            intlr_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[RES_525I60];
        else
            intlr_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[resID]; // for 720P30/25/60/50, 1080P30/25/24
    }

#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    if (resinfo->active_height == 1080)
        tg_params.FrameReset = prog_resinfo->active_height+6 +2;
    else
#endif
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        tg_params.FrameReset = prog_resinfo->active_height+7;
#else
#if defined(BERLIN_SINGLE_CPU)
        tg_params.FrameReset = prog_resinfo->active_height+4;
#else
        tg_params.FrameReset = prog_resinfo->active_height+3;
#endif
#endif

#if (BERLIN_CHIP_VERSION < BERLIN_B_0) && defined(INTERNAL_VDAC)
    tg_params.HSyncStartPos = 0;
    tg_params.HSyncEndPos = prog_resinfo->active_width;
    tg_params.VSyncStartPos = 0;
    tg_params.VSyncEndPos = prog_resinfo->active_height;
    tg_params.Vsampx = tg_params.HSyncStartPos/*0 for HDE/VDE */;
#else
    if (resinfo->type == TYPE_SD)
    {
        tg_params.HSyncEndPos = prog_resinfo->active_width + prog_resinfo->hfrontporch;
        tg_params.HSyncStartPos = tg_params.HSyncEndPos + prog_resinfo->hsyncwidth;
        tg_params.VSyncEndPos = prog_resinfo->active_height + prog_resinfo->vfrontporch;
        tg_params.VSyncStartPos = tg_params.VSyncEndPos + prog_resinfo->vsyncwidth;
        tg_params.Vsampx = tg_params.HSyncEndPos/*0 for HDE/VDE */;
    }
    else
    {
        tg_params.HSyncStartPos = prog_resinfo->active_width + prog_resinfo->hfrontporch;
        tg_params.HSyncEndPos = tg_params.HSyncStartPos + prog_resinfo->hsyncwidth;
        tg_params.VSyncStartPos = prog_resinfo->active_height + prog_resinfo->vfrontporch/* -1 */;
        tg_params.VSyncEndPos = tg_params.VSyncStartPos + prog_resinfo->vsyncwidth;
        tg_params.Vsampx = tg_params.HSyncStartPos/*0 for HDE/VDE */;
    }
#endif

    CPCB_TG_SetParams(vpp_obj, cpcbID, &tg_params);

    /* always enable interlacer for Berlin B0 */
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    if (resinfo->scan == SCAN_INTERLACED) {
#else
    if(!resinfo->flag_3d){
#endif
        /* set CPCB interlacer TG timing parameters */
        if (resinfo->type == TYPE_HD)
            intlrtg_params.MemSize = 1919; /* for 1920x1080I*/
        else
            intlrtg_params.MemSize = 719; /* for 720x480I or 720x576I */

#if (BERLIN_CHIP_VERSION < BERLIN_B_0) && defined(INTERNAL_VDAC)
        intlrtg_params.HsyncS = 0;
        intlrtg_params.HsyncE = intlr_resinfo->active_width;
        intlrtg_params.VsyncS = 0;
        intlrtg_params.VsyncE = intlr_resinfo->active_height/2;
        intlrtg_params.VsampEven = 0;
        intlrtg_params.VsampOdd = 0;
        intlrtg_params.FsampX = intlrtg_params.HsyncS;
        intlrtg_params.FsampY = intlrtg_params.VsyncS;
#else
        if (resID == RES_RESET) {
                intlrtg_params.HsyncE = 0;
                intlrtg_params.HsyncS = 0;
                intlrtg_params.VsyncE = 0;
                intlrtg_params.VsyncS = 0;
                intlrtg_params.VsampEven = 0;
                intlrtg_params.VsampOdd = 0;
                intlrtg_params.FsampX = 0;
                intlrtg_params.FsampY = 0;
        } else {
            if (resinfo->type == TYPE_SD)
            {
                intlrtg_params.HsyncE = intlr_resinfo->active_width + intlr_resinfo->hfrontporch;
                intlrtg_params.HsyncS = intlrtg_params.HsyncE + intlr_resinfo->hsyncwidth;
                if ((resID == RES_VGA_480P5994) || (resID == RES_VGA_480P60)) {
                    intlrtg_params.VsyncS = (intlr_resinfo->active_height >> 1) + (intlr_resinfo->vfrontporch >> 1) - 1;
                    intlrtg_params.VsyncE = intlrtg_params.VsyncS + (intlr_resinfo->vsyncwidth >> 1);
                } else {
                    intlrtg_params.VsyncE = (intlr_resinfo->active_height >> 1) + intlr_resinfo->vfrontporch - 1;
                    intlrtg_params.VsyncS = intlrtg_params.VsyncE + intlr_resinfo->vsyncwidth;
                }
                intlrtg_params.VsampEven = intlrtg_params.HsyncE;
                intlrtg_params.VsampOdd = intlrtg_params.HsyncE - (intlr_resinfo->width >> 1);
                intlrtg_params.FsampX = intlrtg_params.HsyncE;
                intlrtg_params.FsampY = intlrtg_params.VsyncE;
            }
            else
            {
                intlrtg_params.HsyncS = intlr_resinfo->active_width + intlr_resinfo->hfrontporch;
                intlrtg_params.HsyncE = intlrtg_params.HsyncS + intlr_resinfo->hsyncwidth;
                if (((resID <= RES_720P50) && (resID >= RES_720P30)) || ((resID <= RES_1080P2398) && (resID >= RES_1080P30))) {
                    intlrtg_params.VsyncS = (intlr_resinfo->active_height >> 1) + (intlr_resinfo->vfrontporch >> 1) - 1;
                    intlrtg_params.VsyncE = intlrtg_params.VsyncS + (intlr_resinfo->vsyncwidth >> 1);
                } else {
                    intlrtg_params.VsyncS = (intlr_resinfo->active_height >> 1) + intlr_resinfo->vfrontporch - 1;
                    intlrtg_params.VsyncE = intlrtg_params.VsyncS + intlr_resinfo->vsyncwidth;
                }
                intlrtg_params.VsampEven = intlrtg_params.HsyncS;
                intlrtg_params.VsampOdd = intlrtg_params.HsyncS - (intlr_resinfo->width >> 1);
                intlrtg_params.FsampX = intlrtg_params.HsyncS;
                intlrtg_params.FsampY = intlrtg_params.VsyncS;
            }
        }
#endif
        intlrtg_params.YBlankVal = 0;
        intlrtg_params.CBlankVal = 0x200; /* for 10-bit */
        CPCB_INT_SetParams(vpp_obj, cpcbID, &intlrtg_params);

        /* enable interlacer */
        CPCB_INT_Enable(vpp_obj, cpcbID, 1);
    }
    else {
        /* disable interlacer for 3D resolutions*/
        CPCB_INT_Enable(vpp_obj, cpcbID, 0);
    }

    /* set CPCB base plane */
    window.TopLeft.X = 0;
    window.TopLeft.Y = 0;
    window.BottomRight.X = prog_resinfo->active_width;
    window.BottomRight.Y = prog_resinfo->active_height;
    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE0_BASE, &window);
    CPCB_TG_SetPlaneWindow(vpp_obj, cpcbID, TG_PLANE4_BASE_BORDER, &window);

    return (MV_THINVPP_OK);
}
