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

#define _THINVPP_BE_C_

#include "thinvpp_api.h"
#include "thinvpp_module.h"
#include "thinvpp_cfg.h"
#include "thinvpp_be.h"
#include "thinvpp_be_prv.h"

#include "vpp_be_vop.h"
#include "vpp_be_enc.h"
#include "vpp_be_hdmitx.h"
#include "hdmi_aux_data_pack.h"
#include "hdmi_cmn.h"
#include "vpp_be_hdmitx_cfg.h"
#include "gpio.h"

//#define EDID_RAWDATA_DUMP
//#define FAKE_EDID

              ///////////////////////////////////////////
              //                                       //
              //    BE functions for Berlin            //
              //                                       //
              ///////////////////////////////////////////

/*******************************************************************
 * FUNCTION: Reset all VPP BE blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_Reset(THINVPP_OBJ *vpp_obj)
{
    /* reset HD/SD encoder */
    BE_ENC_LoadDefaultVal(vpp_obj);

    /* set HDMI HPD pin configuration */
    HdmiHpdConfig();

    /* reset HDMI TX */
    HdmiTxReset (vpp_obj);

    return (MV_THINVPP_OK);
}

/*********************************************************************
 * FUNCTION: initialize all VPP BE blocks according to configuration
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ********************************************************************/
int THINVPP_BE_Config(THINVPP_OBJ *vpp_obj)
{
    /* set video DAC mapping: ABC(HD), DEF(SD) */
    BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_SD_DACS, VPP_BE_ENC_CVBS_SVIDEO_OUT); // D: CVBS, E: SVideo-Y, F: SVideo-C
    BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: select input for VOUTs in VPP BE blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           voutID - Vout
 *           cpcbout - CPCB output
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetVoutInput(THINVPP_OBJ *vpp_obj, int voutID, int cpcbout)
{
    VPP_VOP_HDMI_CTRL hdmi_ctrl;
    VPP_VOP_AHD_ASD_CTRL hdsd_ctrl;

    switch (voutID){
        case VOUT_HDMI:
            hdmi_ctrl.CBlank = 0x80; /* blank */
            hdmi_ctrl.InputSel = cpcbout;
            hdmi_ctrl.OutputAlign = VPP_VOP_8_10_MSB_ALIGN;
            BE_VOP_SetHdmiParams(vpp_obj, &hdmi_ctrl);
            break;
        case VOUT_HD:
            hdsd_ctrl.InputSel = cpcbout;
            hdsd_ctrl.OutputAlign = VPP_VOP_8_10_MSB_ALIGN;
            BE_VOP_SetAhdParams(vpp_obj, &hdsd_ctrl);
            break;
        case VOUT_SD:
            hdsd_ctrl.InputSel = cpcbout;
            hdsd_ctrl.OutputAlign = VPP_VOP_8_10_MSB_ALIGN;
            BE_VOP_SetAsdParams(vpp_obj, &hdsd_ctrl);
            break;
        default:
            break;
    }
    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: set output format for VOUTs in VPP BE blocks
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           voutID - Vout
 *           color_fmt - CPCB output color format
 *           bit_depth - CPCB output bit depth
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetVoutFormat(THINVPP_OBJ *vpp_obj, int voutID, int color_fmt, int bit_depth)
{
    int cpcbID;
    VOUT *vout;
    int round_mode;

    vout = &(vpp_obj->vout[voutID]);

    /*get CPCB ID which is connected to the Vout*/
    cpcbID = vout->dvID;

    /*map round mode to register value*/
    if(OUTPUT_BIT_DEPTH_12BIT == bit_depth){
        round_mode = VPP_VOP_DATA_BYPASS;
    }else if(OUTPUT_BIT_DEPTH_10BIT == bit_depth){
        round_mode = VPP_VOP_12_TO_10_BITS_ROUND;
    }else{
        round_mode = VPP_VOP_12_TO_8_BITS_ROUND;
    }

    switch (voutID){
        case VOUT_HDMI:
            /*set HDMI output bit depth*/
            BE_VOP_SetRoundMode(vpp_obj, VPP_VOP_HDMI, round_mode);

            /*set HDMI output DNS mode and CSC mode*/
            if(OUTPUT_COLOR_FMT_YCBCR422 == color_fmt){
                BE_VOP_SetHdmiDnsMode(vpp_obj, VPP_VOP_DNS_MODE_ENABLE);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_HDMI, VPP_VOP_CSC_BYPASS_MODE);
#else
                BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_HDMI, VPP_VOP_CSC_UV_SWAP);
#endif
            }else if(OUTPUT_COLOR_FMT_YCBCR444 == color_fmt){
                BE_VOP_SetHdmiDnsMode(vpp_obj, VPP_VOP_DNS_MODE_BYPASS);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_HDMI, VPP_VOP_CSC_BYPASS_MODE);
#else
                BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_HDMI, VPP_VOP_CSC_UV_SWAP);
#endif
            }else{
                BE_VOP_SetHdmiDnsMode(vpp_obj, VPP_VOP_DNS_MODE_BYPASS);
                if (m_resinfo_table[vpp_obj->dv[cpcbID].output_res].type == TYPE_HD){
                    /*when output HD format, color space is converted to 709 before feeding to CPCB*/
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_HDMI, VPP_VOP_CSC_YUV_709_TO_RGB);
                }else{
                    /*when output SD format, color space is converted to 601 before feeding to CPCB*/
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_HDMI, VPP_VOP_CSC_YUV_601_TO_RGB);
                }
            }
            break;

        case VOUT_HD:
            /*set analog HD output bit depth*/
            BE_VOP_SetRoundMode(vpp_obj, VPP_VOP_AHD, round_mode);

            /*set analog HD output CSC mode*/
            if(OUTPUT_COLOR_FMT_RGB888 == color_fmt){
                if (m_resinfo_table[vpp_obj->dv[cpcbID].output_res].type == TYPE_HD){
                    /*when output HD format, color space is converted to 709 before feeding to CPCB*/
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_AHD, VPP_VOP_CSC_YUV_709_TO_sRGB);
                }else{
                    /*when output SD format, color space is converted to 601 before feeding to CPCB*/
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_AHD, VPP_VOP_CSC_YUV_601_TO_sRGB);
                }
            } else {
                BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_AHD, VPP_VOP_CSC_BYPASS_MODE);
            }
            break;

        case VOUT_SD:
            /*set analog SD output bit depth*/
            BE_VOP_SetRoundMode(vpp_obj, VPP_VOP_ASD, round_mode);

            /*set analog SD output CSC mode*/
            if(OUTPUT_COLOR_FMT_RGB888 == color_fmt){
                if (m_resinfo_table[vpp_obj->dv[cpcbID].output_res].type == TYPE_HD){
                    /*when output HD format, color space is converted to 709 before feeding to CPCB*/
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_ASD, VPP_VOP_CSC_YUV_709_TO_sRGB);
                }else{
                    /*when output SD format, color space is converted to 601 before feeding to CPCB*/
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_ASD, VPP_VOP_CSC_YUV_601_TO_sRGB);
                }
            } else {
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
                /* If SD encoder is connected to CPCB_3 and CPCB_1 is in HD resolutuions, CSC is needed */
                if (( cpcbID == CPCB_3) && (m_resinfo_table[vpp_obj->dv[CPCB_1].output_res].type == TYPE_HD)){
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_ASD, VPP_VOP_CSC_709_TO_601);
                }else{
                    BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_ASD, VPP_VOP_CSC_BYPASS_MODE);
                }
#else
                BE_VOP_LoadCscCoeff(vpp_obj, VPP_VOP_ASD, VPP_VOP_CSC_MODES_NO_CHANGE);
#endif
            }
            break;
        default:
            break;
    }
    return (MV_THINVPP_OK);
}

/********************************************************************************
 * FUNCTION: Configure Hdmi Video format
 * INPUT: color_fmt - color format (RGB, YCbCr 444, 422)
 *      : bit_depth - 8/10/12 bit color
 *      : pixel_rept - 1/2/4 repetitions of pixel
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_ConfigHdmiVideoFmt(THINVPP_OBJ *vpp_obj, int color_fmt,
                              int bit_depth, int pixel_rept)
{
    BE_HDMITX_DATA  *pHdmiTx;
    int             resID;
    int             retCode;
    int             aspRatio;

    pHdmiTx = (BE_HDMITX_DATA*)(vpp_obj->be.hdmiTx);

    // Check if CPCB path is configured
    resID = vpp_obj->dv[CPCB_OF_VOUT(vpp_obj,VOUT_HDMI)].output_res;
    if (resID == RES_INVALID)
    {
        return (MV_THINVPP_EBADPARAM);
    }

    if (pHdmiTx->videoParams.DispRes == resID &&
        pHdmiTx->videoParams.VideoFmt == color_fmt &&
        pHdmiTx->videoParams.ColorDepth == bit_depth &&
        (pHdmiTx->videoParams.PixelRpt+1) == pixel_rept)
    {
        return (MV_THINVPP_OK);
    }

    // Configure Video Parameters
    pHdmiTx->videoParams.DispRes = resID;

    // Save color_fmt and bit_depth
    pHdmiTx->videoParams.VideoFmt = color_fmt;
    pHdmiTx->videoParams.ColorDepth = bit_depth;

    // Set pixel repetition
    pHdmiTx->videoParams.PixelRpt = (VPP_BE_HDMITX_PIXEL_RPT_TYPE)(pixel_rept - 1);

    if ((m_resinfo_table[resID].type == TYPE_SD) &&
        (m_resinfo_table[resID].scan == SCAN_INTERLACED) &&
        (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_NONE))
    {
        // Force pixel repetition of 2 for 480i, 576i if no pixel repetition was defined
        pHdmiTx->videoParams.PixelRpt = VPP_BE_HDMITX_PIXEL_RPT_BY_2;
    }

    if (m_resinfo_table[resID].type == TYPE_SD)
        aspRatio = ASPECT_RATIO_4BY3;
    else
        aspRatio = ASPECT_RATIO_16BY9;
    // Config AVI packet
    retCode = HdmiTxConfigAVIInfoFrame (vpp_obj,
                    aspRatio, SCAN_DATA_NONE,
                    0 /* No extended calorimetry */, 1 /* New AVI Infoframe */);
    return (retCode);
}

/********************************************************************************
 * FUNCTION: Set Hdmi Video format
 * INPUT: *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 ********************************************************************************/
int THINVPP_BE_SetHdmiVideoFmt(THINVPP_OBJ *vpp_obj)
{
    BE_HDMITX_DATA  *pHdmiTx;
    int             retCode;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    int resID;
    int clk_ctrl;
#endif

    pHdmiTx = (BE_HDMITX_DATA*)(vpp_obj->be.hdmiTx);

    // Check DispRes
    if (pHdmiTx->videoParams.DispRes == RES_INVALID)
    {
        return (MV_THINVPP_OK);
    }

    /* TODO: set HDMI VOP clock dividor according to CPCB resolution */
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    resID = pHdmiTx->videoParams.DispRes;
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
    if (m_resinfo_table[resID].freq <= 27027){
        if (m_resinfo_table[resID].scan == SCAN_PROGRESSIVE) {
            if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_4)
                clk_ctrl = VPP_VOP_CLK_D1;
            else if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_2)
                clk_ctrl = VPP_VOP_CLK_D2;
            else
                clk_ctrl = VPP_VOP_CLK_D4;
        } else {
            if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_4)
                clk_ctrl = VPP_VOP_CLK_D2;
            else
                clk_ctrl = VPP_VOP_CLK_D4;
        }
    } else if (m_resinfo_table[resID].freq >= 148000) {
        if (m_resinfo_table[resID].scan == SCAN_PROGRESSIVE)
            clk_ctrl = VPP_VOP_CLK_D1;
        else
            clk_ctrl = VPP_VOP_CLK_D2;
    } else
        clk_ctrl = VPP_VOP_CLK_D2;
#else
    if (m_resinfo_table[resID].freq <= 27027){
        if (m_resinfo_table[resID].scan == SCAN_PROGRESSIVE) {
            if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_4)
                clk_ctrl = VPP_VOP_CLK_D2;
            else if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_2)
                clk_ctrl = VPP_VOP_CLK_D4;
            else
                clk_ctrl = VPP_VOP_CLK_D8;
        } else {
            if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_4)
                clk_ctrl = VPP_VOP_CLK_D4;
            else
                clk_ctrl = VPP_VOP_CLK_D8;
        }
    } else if (m_resinfo_table[resID].freq >= 148000) {
        if (m_resinfo_table[resID].scan == SCAN_PROGRESSIVE)
            clk_ctrl = VPP_VOP_CLK_D2;
        else
            clk_ctrl = VPP_VOP_CLK_D4;
    } else
        clk_ctrl = VPP_VOP_CLK_D4;
#endif
    BE_VOP_ClkSelect(vpp_obj, VPP_VOP_HDMI, clk_ctrl);
#endif

    // Reset HDMI FIFO
    BE_HDMITX_ResetFifo (vpp_obj);

    // Mute both audio and video out
    THINVPP_BE_SetHdmiMute (vpp_obj, 0, 1);
    THINVPP_BE_SetHdmiMute (vpp_obj, 1, 1);

    // Disable all host packets
    BE_HDMITX_DisableHostPkt (vpp_obj, VPP_BE_HDMITX_MAX_PKT_INDEX, VPP_BE_HDMITX_HOST_PKT_TX_EVERY_VSYNC);

    // Disable audio - as a safer resort to just muting
    BE_HDMITX_EnableAudioPkt(vpp_obj, 0);

    // Configure HDMI VOP Path
    THINVPP_BE_SetVoutFormat (vpp_obj, VOUT_HDMI,
                          pHdmiTx->videoParams.VideoFmt, pHdmiTx->videoParams.ColorDepth);

    if (pHdmiTx->curOutHdmiMode)
    {
        retCode = BE_HDMITX_SetVideoFmtParams(
                        vpp_obj, VPP_BE_HDMITX_OUT_HDMI, &pHdmiTx->videoParams);
        // Send AVI Info Frame
        BE_HDMITX_SendHostPkt(vpp_obj, 0,
                          VPP_BE_HDMITX_HOST_PKT_TX_EVERY_VSYNC);

    }
    else
    {
        retCode = BE_HDMITX_SetVideoFmtParams(
                        vpp_obj, VPP_BE_HDMITX_OUT_DVI, &pHdmiTx->videoParams);
    }
    if (retCode != MV_THINVPP_OK)
    {
        // Error in configuration - leave it muted
        return retCode;
    }

    // Unmute video
    THINVPP_BE_SetHdmiMute (vpp_obj, 1, 0);
    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: mute Hdmi video/audio
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           video - video/audio to be muted
 *           mute - 1: mute 0:un-mute
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHdmiMute (THINVPP_OBJ *vpp_obj, int video, int muteEn)
{
    int vMute, aMute;
    BE_HDMITX_DATA  *pHdmiTx;
    pHdmiTx = (BE_HDMITX_DATA*)(vpp_obj->be.hdmiTx);

    BE_HDMITX_GetMuteSts (vpp_obj, &aMute, &vMute);
    if (video)
    {
        if (vMute == muteEn)
            return (MV_THINVPP_OK);
        BE_HDMITX_SetMute (vpp_obj, aMute, muteEn);
    }
    else //audio
    {
        if (aMute == muteEn)
            return (MV_THINVPP_OK);
        BE_HDMITX_SetMute (vpp_obj, muteEn, vMute);
    }
    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: set HD DAC oversampling rate
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - HD resolution ID
 *           ovsmpl - oversampling rate
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHDacOversampling(THINVPP_OBJ *vpp_obj, int resID, int ovsmpl)
{
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    int clk_ctrl;

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
    if (m_resinfo_table[resID].freq <= 27027){
        if (m_resinfo_table[resID].scan == SCAN_INTERLACED) {
            if (ovsmpl >= 8) {
                clk_ctrl = VPP_VOP_CLK_D1;
                ovsmpl = VPP_BE_ENC_8X_OVERSAMPLING;
            } else if (ovsmpl >= 4) {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D4;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            }
        } else {
            if (ovsmpl >= 4) {
                clk_ctrl = VPP_VOP_CLK_D1;
                ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
            } else if (ovsmpl >= 2) {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D4;
                ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
            }
        }
    } else if (m_resinfo_table[resID].freq >= 148000) {
        if (m_resinfo_table[resID].scan == SCAN_INTERLACED) {
            if (ovsmpl >= 2) {
                clk_ctrl = VPP_VOP_CLK_D1;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
            }
        } else {
            clk_ctrl = VPP_VOP_CLK_D1;
            ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
        }
    } else {
        if (ovsmpl >= 2) {
            clk_ctrl = VPP_VOP_CLK_D1;
            ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
        } else {
            clk_ctrl = VPP_VOP_CLK_D2;
            ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
        }
    }
#else
    if (m_resinfo_table[resID].freq <= 27027){
        if (m_resinfo_table[resID].scan == SCAN_INTERLACED) {
            if (ovsmpl >= 8) {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_8X_OVERSAMPLING;
            } else if (ovsmpl >= 4) {
                clk_ctrl = VPP_VOP_CLK_D4;
                ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D8;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            }
        } else {
            if (ovsmpl >= 8) {
                clk_ctrl = VPP_VOP_CLK_D1;
                ovsmpl = VPP_BE_ENC_8X_OVERSAMPLING;
            } else if (ovsmpl >= 4) {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
            } else if (ovsmpl >= 2) {
                clk_ctrl = VPP_VOP_CLK_D4;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D8;
                ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
            }
        }
    } else if (m_resinfo_table[resID].freq >= 148000) {
        if (m_resinfo_table[resID].scan == SCAN_INTERLACED) {
            if (ovsmpl >= 4) {
                clk_ctrl = VPP_VOP_CLK_D1;
                ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
            } else if (ovsmpl >= 2) {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D4;
                ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
            }
        } else {
            if (ovsmpl >= 2) {
                clk_ctrl = VPP_VOP_CLK_D1;
                ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
            } else {
                clk_ctrl = VPP_VOP_CLK_D2;
                ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
            }
        }
    } else {
        if (ovsmpl >= 4) {
            clk_ctrl = VPP_VOP_CLK_D1;
            ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
        } else if (ovsmpl >= 2) {
            clk_ctrl = VPP_VOP_CLK_D2;
            ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
        } else {
            clk_ctrl = VPP_VOP_CLK_D4;
            ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
        }
    }
#endif
    BE_VOP_ClkSelect(vpp_obj, VPP_VOP_AHD, clk_ctrl);
#else
    ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
#endif

    BE_ENC_SetDacOversample(vpp_obj, VPP_BE_ENC_HD_DACS, ovsmpl);

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: set SD DAC oversampling rate
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           ovsmpl - oversampling rate
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetSDacOversampling(THINVPP_OBJ *vpp_obj, int ovsmpl)
{
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    int clk_ctrl;

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
    if (ovsmpl >= 4) {
        clk_ctrl = VPP_VOP_CLK_D1;
        ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
    } else if (ovsmpl >= 2) {
        clk_ctrl = VPP_VOP_CLK_D2;
        ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
    } else {
        clk_ctrl = VPP_VOP_CLK_D4;
        ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
    }
#else
    if (ovsmpl >= 8) {
        clk_ctrl = VPP_VOP_CLK_D1;
        ovsmpl = VPP_BE_ENC_8X_OVERSAMPLING;
    } else if (ovsmpl >= 4) {
        clk_ctrl = VPP_VOP_CLK_D2;
        ovsmpl = VPP_BE_ENC_4X_OVERSAMPLING;
    } else if (ovsmpl >= 2) {
        clk_ctrl = VPP_VOP_CLK_D4;
        ovsmpl = VPP_BE_ENC_2X_OVERSAMPLING;
    } else {
        clk_ctrl = VPP_VOP_CLK_D8;
        ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
    }
#endif
    BE_VOP_ClkSelect(vpp_obj, VPP_VOP_ASD, clk_ctrl);
#else
    ovsmpl = VPP_BE_ENC_NO_OVERSAMPLING;
#endif
    BE_ENC_SetDacOversample(vpp_obj, VPP_BE_ENC_SD_DACS, ovsmpl);

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: set HD DAC resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetHDacResolution(THINVPP_OBJ *vpp_obj, int resID)
{
    /* mute HD DAC input/output */
    BE_ENC_SetHDInpMuteCtrl(vpp_obj, 0x1, 0);
    BE_ENC_SetHDOutMuteCtrl(vpp_obj, 0x7, 1);

    switch (resID) {
        case RES_NTSC_M: // 480I
        case RES_NTSC_J: // 480I
        case RES_PAL_M: // 480I
        case RES_525I60: // 480I
        case RES_525I5994:
#if 1 // HD doesn't support 480I/576I output, use SD encoder instead
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_SD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_480i);
#endif
#else
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_480i, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_480i, NULL);
#endif
            break;
        case RES_PAL_BGH: // 576I
        case RES_625I50: // 576I
#if 1 // HD doesn't support 480I/576I output, use SD encoder instead
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_SD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_576i);
#endif
#else
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_576i, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_576i, NULL);
#endif
            break;
        case RES_525P60: // 480P
        case RES_525P5994:
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_480p);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_480p, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_480p, NULL);
            break;
        case RES_625P50: // 576P
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_576p);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_576p, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_576p, NULL);
            break;
        case RES_720P60: // 720P60
        case RES_720P5994: // 720P5994
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_720p60);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_720p60, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_720p60, NULL);
            break;
        case RES_720P50: // 720P50
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_720p50);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_720p50, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_720p50, NULL);
            break;
        case RES_1080I60: // 1080I60
        case RES_1080I5994: // 1080I5994
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_1080i30);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_1080i30, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_1080i30, NULL);
            break;
        case RES_1080I50: // 1080I50
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_1080i25);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_1080i25, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_1080i25, NULL);
            break; // not support yet
        case RES_1080P30: // 1080P30
        case RES_1080P2997: // 1080P2997
        case RES_1080P60: // 1080P60
        case RES_1080P5994: // 1080P5994
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_1080p60);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_1080p60, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_1080p60, NULL);
            break;
        case RES_1080P25: // 1080P25
        case RES_1080P50: // 1080P50
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_1080p50);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_1080p50, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_1080p50, NULL);
            break;
        case RES_1080P24: // 1080P24
        case RES_1080P2398: // 1080P2398
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_1080p24);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_1080p24, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_1080p24, NULL);
            break;
        case RES_VGA_480P60: // VGA 640x480P60
        case RES_VGA_480P5994:
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_HD_COMPONENT_OUT); // A: Cb/B, B: Y/G, C: Cr/R
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_HD_DACS, VPP_BE_ENC_RES_VGA_480p60);
#endif
            BE_ENC_SetHDTimingParams(vpp_obj, VPP_BE_ENC_RES_VGA_480p60, NULL);
            BE_ENC_SetHDComponentParams(vpp_obj, VPP_BE_ENC_RES_VGA_480p60, NULL);
            break;
    }

    /* unmute HD DAC input/output */
    BE_ENC_SetHDInpMuteCtrl(vpp_obj, 0, 0);
    BE_ENC_SetHDOutMuteCtrl(vpp_obj, 0, 1);

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: set SD DAC resolution
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           resID - resolution ID
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetSDacResolution(THINVPP_OBJ *vpp_obj, int resID)
{
    VPP_BE_ENC_VBI_ENABLE_CTRL CCEnMode;

    /* mute SD DAC input/output */
    BE_ENC_SetSDInpMuteCtrl(vpp_obj, 0x1, 0);
    BE_ENC_SetSDOutMuteCtrl(vpp_obj, 0x7, 1);

    if (resID == RES_INVALID)
        return (MV_THINVPP_OK);

    switch (resID) {
        case RES_525I60: // 480I
        case RES_525I5994:
        case RES_NTSC_M: // NTSC-M
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_SD_DACS, VPP_BE_ENC_CVBS_SVIDEO_OUT);         // DAC 2 - CVBS, DAC 1,0 - SVideo
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_SD_DACS, VPP_BE_ENC_CVFMT_NTSC_M);
            BE_ENC_SetSDTimingParams(vpp_obj, VPP_BE_ENC_CVFMT_NTSC_M, NULL);
            BE_ENC_SetCvbsSVideoParams(vpp_obj, VPP_BE_ENC_CVFMT_NTSC_M, NULL);
            BE_ENC_SetSDComponentParams(vpp_obj, VPP_BE_ENC_RES_480i, NULL);
            /* set CC mode & parameters */
            CCEnMode.CCWssEnableCtrl.EnableTopFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableBtmFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableCont = 1;//set 0x00 when there is no CC data
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            CCEnMode.CCWssEnableCtrl.EnableOnCVBS = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnSVideo = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnComponent = 1;
#endif
            break;

        case RES_NTSC_J: // NTSC-J
            BE_ENC_SetSDTimingParams(vpp_obj, VPP_BE_ENC_CVFMT_NTSC_J, NULL);
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_SD_DACS, VPP_BE_ENC_CVFMT_NTSC_J);
            BE_ENC_SetCvbsSVideoParams(vpp_obj, VPP_BE_ENC_CVFMT_NTSC_J, NULL);
            BE_ENC_SetSDComponentParams(vpp_obj, VPP_BE_ENC_RES_480i, NULL);
            /* set CC mode & parameters */
            CCEnMode.CCWssEnableCtrl.EnableTopFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableBtmFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableCont = 1;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            CCEnMode.CCWssEnableCtrl.EnableOnCVBS = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnSVideo = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnComponent = 1;
#endif
            break;

        case RES_PAL_M: // PAL-M
            BE_ENC_SetSDTimingParams(vpp_obj, VPP_BE_ENC_CVFMT_PAL_M, NULL);
            BE_ENC_SetCvbsSVideoParams(vpp_obj, VPP_BE_ENC_CVFMT_PAL_M, NULL);
            BE_ENC_SetSDComponentParams(vpp_obj, VPP_BE_ENC_RES_480i, NULL);
            /* set CC mode & parameters */
            CCEnMode.CCWssEnableCtrl.EnableTopFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableBtmFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableCont = 1;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            CCEnMode.CCWssEnableCtrl.EnableOnCVBS = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnSVideo = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnComponent = 1;
#endif
            break;

        case RES_625I50: // 576I
        case RES_PAL_BGH: // PAL-BGH
            BE_ENC_SetDacUsage(vpp_obj, VPP_BE_ENC_SD_DACS, VPP_BE_ENC_CVBS_SVIDEO_OUT);         // DAC 2 - CVBS, DAC 1,0 - SVideo
            BE_ENC_SetDacVoltage(vpp_obj, VPP_BE_ENC_SD_DACS, VPP_BE_ENC_CVFMT_PAL_BGH);
            BE_ENC_SetSDTimingParams(vpp_obj, VPP_BE_ENC_CVFMT_PAL_BGH, NULL);
            BE_ENC_SetCvbsSVideoParams(vpp_obj, VPP_BE_ENC_CVFMT_PAL_BGH, NULL);
            BE_ENC_SetSDComponentParams(vpp_obj, VPP_BE_ENC_RES_576i, NULL);
            /* set CC mode & parameters */
            CCEnMode.CCWssEnableCtrl.EnableTopFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableBtmFld = 0;
            CCEnMode.CCWssEnableCtrl.EnableCont = 1;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            CCEnMode.CCWssEnableCtrl.EnableOnCVBS = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnSVideo = 1;
            CCEnMode.CCWssEnableCtrl.EnableOnComponent = 1;
#endif
            break;
    }

    /* unmute SD DAC input/output */
    BE_ENC_SetSDInpMuteCtrl(vpp_obj, 0, 0);
    BE_ENC_SetSDOutMuteCtrl(vpp_obj, 0, 1);

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: mute AHD/ASD output
 * PARAMS:   *vpp_obj - pointer to VPP object
 *           mute - 1: mute 0:un-mute
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
int THINVPP_BE_SetDacMute(THINVPP_OBJ *vpp_obj, int mute, int vout)
{
    if(vout == VOUT_SD){
        if(mute){
            BE_ENC_SetSDInpMuteCtrl(vpp_obj, 0x1, 0);
            BE_ENC_SetSDOutMuteCtrl(vpp_obj, 0x7, 1);
        }else{
            BE_ENC_SetSDInpMuteCtrl(vpp_obj, 0, 0);
            BE_ENC_SetSDOutMuteCtrl(vpp_obj, 0, 1);
        }
    }else{
        if(mute){
            BE_ENC_SetHDInpMuteCtrl(vpp_obj, 0x1, 0);
            BE_ENC_SetHDOutMuteCtrl(vpp_obj, 0x7, 1);
        }else{
            BE_ENC_SetHDInpMuteCtrl(vpp_obj, 0, 0);
            BE_ENC_SetHDOutMuteCtrl(vpp_obj, 0, 1);
        }
    }
    return (MV_THINVPP_OK);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////LOCAL STATIC FUNCTIONS/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************
 * FUNCTION: config Hdmi HPD pin
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
static void HdmiHpdConfig()
{
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
     *((volatile int *)0xf7fcd020) = 0xd455;
#endif
     SM_GPIO_PortWrite(1, 1); // set SM GPIO port 1 to high, this is input/output control of SM GPIO port 7
}

/*******************************************************************
 * FUNCTION: Reset Hdmi Tx components
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxReset (THINVPP_OBJ *vpp_obj)
{
    int             retVal;
    BE_HDMITX_DATA  *pHdmiTxData;

    if (vpp_obj->be.hdmiTx == 0)
    {
        // Init HDMI Tx
        retVal = HdmiTxInit (vpp_obj);
        if (retVal != MV_THINVPP_OK)
        {
            return retVal;
        }
    }

    /* Reset data store */
    pHdmiTxData = (BE_HDMITX_DATA*)(vpp_obj->be.hdmiTx);
    pHdmiTxData->videoParams.DispRes = RES_INVALID;
    pHdmiTxData->frameCntr = -1;

    /* Reset Hdmi Tx    */
    BE_HDMITX_LoadDefaultVal(vpp_obj);

    /* Reset Hdmi Phy   */
    BE_HDMIPHY_LoadDefaultVal(vpp_obj);

    // Assume receiver is already connected on startup
    pHdmiTxData->rxConnected = 1;
    pHdmiTxData->curOutHdmiMode = 1; // HDMI Mode
//    pHdmiTxData->curOutHdmiMode = 0; // DVI Mode
    if (pHdmiTxData->rxConnected)
    {
        // Receiver is already connected
        // TODO: Why does this line break things?
        HdmiTxHandleHotPlug (vpp_obj, 1);
    }

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: Initialize Hdmi Tx - allocate memory for data storage
 *         : and create required OS components
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN: MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxInit (THINVPP_OBJ *vpp_obj)
{
    BE_HDMITX_DATA  *pHdmiTxData;

    // Allocate memory for data store
    pHdmiTxData = (BE_HDMITX_DATA*)THINVPP_MALLOC(sizeof(BE_HDMITX_DATA));
    if (pHdmiTxData == NULL)
    {
        return MV_THINVPP_ENOMEM;
    }
    THINVPP_MEMSET(pHdmiTxData, 0, sizeof(BE_HDMITX_DATA));

    // Save the address in vpp_obj
    vpp_obj->be.hdmiTx = (unsigned int)(pHdmiTxData);

    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: Handle hot plug event
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN:   MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxHandleHotPlug (THINVPP_OBJ *vpp_obj, int rxConnected)
{
    BE_HDMITX_DATA  *pHdmiTx;

    pHdmiTx = (BE_HDMITX_DATA*)(vpp_obj->be.hdmiTx);
    if (rxConnected)
    {

        //BE_HDMITX_EnablePhyFifo(vpp_obj, 0, 0);

        // Receiver plugged in
        pHdmiTx->videoParams.DispRes = RES_INVALID;
        pHdmiTx->frameCntr   = -1;

        BE_HDMIPHY_SetDAMP(vpp_obj, 0x492);
        BE_HDMIPHY_SetEAMP(vpp_obj, 0x249);

        // Mute Output
        BE_HDMITX_SetMute (vpp_obj, 1, 1);
    }
    else
    {
        BE_HDMIPHY_SetDAMP(vpp_obj, 0);
        BE_HDMIPHY_SetEAMP(vpp_obj, 0);

        //BE_HDMITX_EnablePhyFifo(vpp_obj, 0, 0);

        // Mute Output
        BE_HDMITX_SetMute (vpp_obj, 1, 1);
    }
    return (MV_THINVPP_OK);
}

/*******************************************************************
 * FUNCTION: Construct AVI info frame packet
 * PARAMS:   *vpp_obj - pointer to VPP object
 * RETURN:   MV_THINVPP_OK
 ******************************************************************/
static int HdmiTxConfigAVIInfoFrame (THINVPP_OBJ *vpp_obj,
                                     int aspRatio, int scanInfo,
                                     int extCalorimetry, int newFrame)
{
    BE_HDMITX_DATA      *pHdmiTx;
    AVI_INFO_FRAME      AVIInfoFrame;
    unsigned char               DataBuf[31];
    CEA_RES_INFO        ResInfo;
    int                 resID;

    pHdmiTx = (BE_HDMITX_DATA*)(vpp_obj->be.hdmiTx);

    // Create AVI Infoframe packet to be sent
    THINVPP_MEMSET(&AVIInfoFrame, 0, sizeof(AVI_INFO_FRAME));
    THINVPP_MEMSET(DataBuf, 0, 31);

    resID = pHdmiTx->videoParams.DispRes;
    if (m_resinfo_table[resID].type == TYPE_HD)
        aspRatio = ASPECT_RATIO_16BY9; // force asp ratio of HD resolution to 16x9

    if (newFrame)
    {
        // Set color space
        if (pHdmiTx->videoParams.VideoFmt == OUTPUT_COLOR_FMT_YCBCR444)
            AVIInfoFrame.ColorSpace = CEA_COLSP_YCBCR_444;
        else if (pHdmiTx->videoParams.VideoFmt == OUTPUT_COLOR_FMT_YCBCR422)
            AVIInfoFrame.ColorSpace = CEA_COLSP_YCBCR_422;
        else
            AVIInfoFrame.ColorSpace = CEA_COLSP_RGB;

        AVIInfoFrame.ActFmtInfoPresent = 0;
        AVIInfoFrame.PixRepeatCnt = pHdmiTx->videoParams.PixelRpt;
        AVIInfoFrame.ActFmtAspectRatio = CEA_ACT_FMT_AR_SAME_AS_PICT;

        if ((aspRatio == HDMI_USE_EXISTING) || (scanInfo == HDMI_USE_EXISTING) ||
            (extCalorimetry == HDMI_USE_EXISTING))
        {
            // For a new infoframe all these fields should have valid content
            return (MV_THINVPP_EBADPARAM);
        }
    }

    // Set aspect ratio
    if (aspRatio != HDMI_USE_EXISTING)
    {
        if (aspRatio == ASPECT_RATIO_4BY3)
            AVIInfoFrame.PicAspectRatio = CEA_PICT_AR_4_3;
        else if (aspRatio == ASPECT_RATIO_16BY9)
            AVIInfoFrame.PicAspectRatio = CEA_PICT_AR_16_9;
        else
            AVIInfoFrame.PicAspectRatio = CEA_PICT_AR_NONE;
    }

    // Set scan information
    if (scanInfo != HDMI_USE_EXISTING)
    {
        if (scanInfo == OVER_SCAN_DATA)
            AVIInfoFrame.ScanInfo = CEA_OVER_SCAN_DATA;
        else if (scanInfo == UNDER_SCAN_DATA)
            AVIInfoFrame.ScanInfo = CEA_UNDER_SCAN_DATA;
        else
            AVIInfoFrame.ScanInfo = CEA_SCAN_DATA_NONE;
    }

    // Set calorimetry
    if (extCalorimetry != HDMI_USE_EXISTING)
    {
        if (extCalorimetry == 1)
        {
            AVIInfoFrame.Calorimetry = CEA_CAL_EXT_FMT;
            if (m_resinfo_table[resID].type == TYPE_SD) {
                AVIInfoFrame.ExtCalorimetry = CEA_EXT_CAL_XVYCC_601_FMT;
            }
            else {
                AVIInfoFrame.ExtCalorimetry = CEA_EXT_CAL_XVYCC_709_FMT;
            }
        }
        else
        {
            if (m_resinfo_table[resID].type == TYPE_SD) {
                AVIInfoFrame.Calorimetry = CEA_CAL_ITU601_FMT;
            }
            else {
                AVIInfoFrame.Calorimetry = CEA_CAL_ITU709_FMT;
            }
            AVIInfoFrame.ExtCalorimetry = CEA_EXT_CAL_MAX; // Reserved
        }
    }

    // Get Video ID code
    ResInfo.HActive     = m_resinfo_table[resID].active_width;
    ResInfo.VActive     = m_resinfo_table[resID].active_height;
    switch (resID)
    {
        case RES_525I60:
        case RES_525I5994:
        case RES_525P60:
        case RES_525P5994:
        case RES_720P60:
        case RES_720P5994:
        case RES_1080I60:
        case RES_1080I5994:
        case RES_1080P60:
        case RES_1080P5994:
        case RES_VGA_480P60:
        case RES_VGA_480P5994:
        case RES_720P60_3D:
        case RES_720P5994_3D:
            ResInfo.RefreshRate = 60;
            break;
        case RES_625I50:
        case RES_625P50:
        case RES_720P50:
        case RES_1080I50:
        case RES_1080P50:
        case RES_720P50_3D:
            ResInfo.RefreshRate = 50;
            break;
        case RES_1080P24:
        case RES_1080P2398:
        case RES_1080P24_3D:
        case RES_1080P2398_3D:
            ResInfo.RefreshRate = 24;
            break;
        case RES_1080P25:
        case RES_1080P25_3D:
            ResInfo.RefreshRate = 25;
            break;
        case RES_1080P30:
        case RES_1080P2997:
        case RES_1080P30_3D:
        case RES_1080P2997_3D:
            ResInfo.RefreshRate = 30;
            break;
        default:
            ResInfo.RefreshRate = 0;
            break;
    }
    if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_2)
    {
        ResInfo.HActive *= 2;
    }
    else if (pHdmiTx->videoParams.PixelRpt == VPP_BE_HDMITX_PIXEL_RPT_BY_4)
    {
        ResInfo.HActive *= 4;
    }
    ResInfo.FrmFmt   = (m_resinfo_table[resID].scan == SCAN_INTERLACED);
    ResInfo.AspRatio = AVIInfoFrame.PicAspectRatio;

    GetVideoIDForRes (&ResInfo);
    AVIInfoFrame.VideoIdCode = ResInfo.VideoIDCode;

    THINVPP_MEMSET(DataBuf, 0, 31);
    VppPackAVIInfoFrame(&AVIInfoFrame, DataBuf);

    // Set host packet data
    BE_HDMITX_SetHostPktTxData (vpp_obj, 0, DataBuf);
    return (MV_THINVPP_OK);
}

