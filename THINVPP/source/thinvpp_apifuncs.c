/*******************************************************************************
* Copyright (C) Marvell International Ltd. and its affiliates
*
* Marvell GPL License Option
*
* If you received this File from Marvell, you may opt to use, redistribute and/or
* modify this File in accordance with the terms and conditions of the General
* Public License Version 2, June 1991 (the "GPL License"), a copy of which is
* available along with the File in the license.txt file or by writing to the Free
* Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 or
* on the worldwide web at http://www.gnu.org/licenses/gpl.txt.
*
* THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE IMPLIED
* WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY
* DISCLAIMED.  The GPL License provides additional details about this warranty
* disclaimer.
********************************************************************************/



#define _VPP_APIFUNCS_C_

#include "thinvpp_module.h"
#include "thinvpp_cfg.h"
#include "vpp_fe_dlr.h"
#include "vpp_fe_deint.h"
#include "thinvpp_scl.h"
#include "vpp_frc_scl.h"
#include "thinvpp_cpcb.h"
#include "thinvpp_be.h"
#include "vpp_be_enc.h"
#include "thinvpp_apifuncs.h"
#include "vpp_cpcb_ovl.h"
#include "vpp_cpcb_fgg.h"

#if (BERLIN_CHIP_VERSION < BERLIN_C_2)
#define LUMA_KEY_HACK
#endif

/*******************************************************************
 * FUNCTION: set CPCB(for Berlin) or DV(for Galois) output resolution
 * INPUT: cpcbID - CPCB(for Berlin) or DV(for Galois) id
 *        resID - id of DV output resolution
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured or plane not active
 *         MV_EFRAMEQFULL - frame queue is full
 * Note: this function has to be called before enabling a plane
 *       which belongs to that DV.
 *******************************************************************/
int VPP_SetCPCBOutputResolution(THINVPP_OBJ *vpp_obj, int *in_params)
{
    int cpcbID = in_params[0];
    int resID = in_params[1];
    DV *cpcb;
    RESOLUTION_INFO *new_resinfo;
    int i, cpcbout;
    VPP_CPCB0_OUTPUT_RES res_tot, res_act;
    VPP_BE_ENC_CX_CTRL_PARAMS CxParams;

    cpcb = &(vpp_obj->dv[cpcbID]);

    new_resinfo = (RESOLUTION_INFO *)&m_resinfo_table[resID];

    /* set CPCB resolution when CPCB is inactive */
    THINVPP_CPCB_SetOutputResolution(vpp_obj, cpcbID, resID);

    /*when reset cpcb, do not update disp_win*/
    if(resID == RES_RESET){
        cpcb->vbi_num = 0; // reset VBI counter
        cpcb->status = STATUS_INACTIVE;
        return (MV_THINVPP_OK);
    }

    /*set BE fifo, if aux channel is connected to this cpcb*/
    if (CPCB_1 == cpcbID){
        res_tot.HRes = new_resinfo->width;
        res_tot.VRes = new_resinfo->height;
        res_act.HRes = new_resinfo->active_width;
        res_act.VRes = new_resinfo->active_height;
        THINVPP_SCL_SetBeFifo(vpp_obj, (PVPP_CPCB0_OUTPUT_RES)&res_tot, (PVPP_CPCB0_OUTPUT_RES)&res_act);
    }

    cpcb->output_res = resID;

    /* set VOUT intput according to CPCB resolution (interlaced or progressive) */
    for (i=0; i<cpcb->num_of_vouts; i++){
        if (cpcbID == CPCB_1) {
            if (new_resinfo->scan == SCAN_PROGRESSIVE)
                cpcbout = VPP_VOP_CPCB0_PROG; /* CPCB-0 progressive */
            else
                cpcbout = VPP_VOP_CPCB0_INTER; /* CPCB-0 interlaced */
        } else if (cpcbID == CPCB_2) {
            if (new_resinfo->scan == SCAN_PROGRESSIVE)
                cpcbout = VPP_VOP_CPCB1_PROG; /* CPCB-1 progressive */
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                cpcbout = VPP_VOP_NO_INPUT; /* no input */
#else
                cpcbout = VPP_VOP_CPCB1_INTER; /* CPCB-1 interlaced */
#endif
        } else if (cpcbID == CPCB_3) {
            if (new_resinfo->scan == SCAN_PROGRESSIVE)
                cpcbout = VPP_VOP_CPCB2_PROG; /* CPCB-2 progressive */
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                cpcbout = VPP_VOP_CPCB2_INTER; /* CPCB-2 interlaced */
#else
                cpcbout = VPP_VOP_NO_INPUT; /* no input */
#endif
        } else
            cpcbout = VPP_VOP_NO_INPUT;

        THINVPP_BE_SetVoutInput(vpp_obj, cpcb->voutID[i], cpcbout);
    }

    /* set SD encoder output format */
    THINVPP_BE_SetVoutFormat(vpp_obj, VOUT_SD, OUTPUT_COLOR_FMT_YCBCR444, OUTPUT_BIT_DEPTH_12BIT);

    if (vpp_obj->vout[VOUT_HD].dvID == cpcbID) {
        if ((resID == RES_VGA_480P60) || (resID == RES_VGA_480P5994)){
            THINVPP_BE_SetVoutFormat(vpp_obj, VOUT_HD, OUTPUT_COLOR_FMT_RGB888, OUTPUT_BIT_DEPTH_12BIT);
            // Configure HD path with default component controls
            CxParams.CxSyncMode = VPP_BE_ENC_CX_SYNC_ON_YG; // embedded sync on G channel
            CxParams.DisableClipping = 0; // clipping disabled
            CxParams.DigitalSync = 0; // Hsync and Vsync is sent out
            CxParams.HSyncPolarity = 0; // Hsync polarity not inverted
            CxParams.VSyncPolarity = 1; // Vsync polarity inverted
            BE_ENC_SetHDCxOutCtrl(vpp_obj, VPP_BE_ENC_CX_RGB, &CxParams);

        } else {
            THINVPP_BE_SetVoutFormat(vpp_obj, VOUT_HD, OUTPUT_COLOR_FMT_YCBCR444, OUTPUT_BIT_DEPTH_12BIT);
            // Configure HD path with default component controls
            CxParams.CxSyncMode = VPP_BE_ENC_CX_SYNC_ON_YG; // embedded sync on Y channel
            CxParams.DisableClipping = 1; // clipping enabled
            CxParams.DigitalSync = 0; // Hsync and Vsync is sent out
            CxParams.HSyncPolarity = 0; // Hsync polarity not inverted
            CxParams.VSyncPolarity = 1; // Vsync polarity inverted
            BE_ENC_SetHDCxOutCtrl(vpp_obj, VPP_BE_ENC_CX_YPbPr, &CxParams);
        }
    }

    /* set SD encoder/DAC resolution which connected to this CPCB */
    if (vpp_obj->vout[VOUT_SD].dvID == cpcbID) {
        THINVPP_BE_SetSDacResolution(vpp_obj, resID);
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
        THINVPP_BE_SetSDacOversampling(vpp_obj, 4);
#else
        THINVPP_BE_SetSDacOversampling(vpp_obj, 8);
#endif
    }

    /* set HD encoder/DAC resolution which connected to this CPCB */
    if (vpp_obj->vout[VOUT_HD].dvID == cpcbID) {
        THINVPP_BE_SetHDacResolution(vpp_obj, resID);
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
        if (m_resinfo_table[resID].type == TYPE_SD)
            THINVPP_BE_SetHDacOversampling(vpp_obj, resID, 4);
        else
            THINVPP_BE_SetHDacOversampling(vpp_obj, resID, 2);
#else
        if (m_resinfo_table[resID].type == TYPE_SD)
            THINVPP_BE_SetHDacOversampling(vpp_obj, resID, 8);
        else
            THINVPP_BE_SetHDacOversampling(vpp_obj, resID, 4);
#endif
    }

    return (MV_THINVPP_OK);
}
