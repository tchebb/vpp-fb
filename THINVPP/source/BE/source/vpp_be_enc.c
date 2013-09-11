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

#define _VPP_BE_ENC_C_

#include "thinvpp_api.h"
#include "thinvpp_module.h"
#include "thinvpp_common.h"
#include "thinvpp_bcmbuf.h"

#include "vpp_be_enc.h"
#include "vpp_be_enc_prv.h"
#include "vpp_be_enc_presets.h"

#include "maddr.h"
#include "vpp.h"

/*-----------------------------------------------------------------------------
 * Description  : This function sets component out control fields for SD
 *              : and HD outputs
 * Arguments    : EncPath    - SD/HD path
 *              : CxOutFmt   - component output format
 *              : pCXOutCtrl - Pointer to control field structure (Input)
 *              :            - If NULL, defaults would be set
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
static int BE_ENC_SetCxOutCtrl (THINVPP_OBJ *vpp_obj, int EncPath, int CxOutFmt, PVPP_BE_ENC_CX_CTRL_PARAMS pCxParams)
{
    ENC_SD_CX_OUT_CTRL_REGISTER CxOutCtrl;
    ENC_HD_OUT_CTRL_REGISTER2 ModeControl2;

    if (EncPath == VPP_BE_ENC_SD_PATH) {
        CxOutCtrl.Bits.OutMode = CxOutFmt;
        CxOutCtrl.Bits.SyncMode = pCxParams->CxSyncMode;
        CxOutCtrl.Bits.ClipDis = pCxParams->DisableClipping;
        CxOutCtrl.Bits.DigitalSyncEn = pCxParams->DigitalSync;
        CxOutCtrl.Bits.HSyncPolarity = pCxParams->HSyncPolarity;
        CxOutCtrl.Bits.VSyncPolarity = pCxParams->VSyncPolarity;
        WRITE_ENC_REG(E_CTRL_60, *((unsigned int *)&CxOutCtrl));

    } else if (EncPath == VPP_BE_ENC_HD_PATH) {

        ((ENC_HD_OUT_CTRL_REGISTER1 *)(&vpp_obj->be.enc.HdCtrl0))->Bits.Mode = CxOutFmt;
        ((ENC_HD_OUT_CTRL_REGISTER1 *)(&vpp_obj->be.enc.HdCtrl0))->Bits.SyncMode = pCxParams->CxSyncMode;
        WRITE_ENC_REG(E_CTRL_142, vpp_obj->be.enc.HdCtrl0);

        ModeControl2.Bits.ClipDis = pCxParams->DisableClipping;
        ModeControl2.Bits.DigitalSyncEn = pCxParams->DigitalSync;
        ModeControl2.Bits.HSyncPolarity = pCxParams->HSyncPolarity;
        ModeControl2.Bits.VSyncPolarity = pCxParams->VSyncPolarity;
        WRITE_ENC_REG(E_CTRL_143, *((unsigned int *)&ModeControl2));
    }

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This is the encoder reset function to load default value
 * Arguments    : None
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_LoadDefaultVal(THINVPP_OBJ *vpp_obj)
{
#if (BERLIN_CHIP_VERSION < BERLIN_BG2)
    volatile int vdac_ctrl;
#else
    T32DAC_ctrl_ctrl0 dac_ctrl0;
    T32DAC_ctrl_ctrl1 dac_ctrl1;
    T32VDAC_ctrl_misc1 vdac_misc1;
    T32VDAC_ctrl_misc2 vdac_misc2;
#endif
    VPP_BE_ENC_CX_CTRL_PARAMS CxParams;

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    WRITE_ENC_REG(E_CTRL_4, 3); // invert SD/HD DACs clock polarity
#endif

    // Set Mute Color
    WRITE_ENC_REG(E_CTRL_108, 0x80); // SD blank: Cr
    WRITE_ENC_REG(E_CTRL_109, 0x00); // SD blank: Y
    WRITE_ENC_REG(E_CTRL_110, 0x80); // SD blank: Cb

    WRITE_ENC_REG(E_CTRL_112, 0x80); // HD blank: Cr
    WRITE_ENC_REG(E_CTRL_113, 0x00); // HD blank: Y
    WRITE_ENC_REG(E_CTRL_114, 0x80); // HD blank: Cb

    WRITE_ENC_REG(E_CTRL_116, 0x00); // Mute color for DAC 0, 1, 2
    WRITE_ENC_REG(E_CTRL_117, 0x00); //
    WRITE_ENC_REG(E_CTRL_118, 0x00); // Mute color for DAC 3, 4, 5
    WRITE_ENC_REG(E_CTRL_119, 0x00); //

#if (BERLIN_CHIP_VERSION < BERLIN_BG2)
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    vdac_ctrl = 0x23f6ac;
#else
    vdac_ctrl = 0x27aeac;
#endif
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_b) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_c) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_d) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_e) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_f) >> 2), vdac_ctrl); // DAC control settings

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    vdac_ctrl = 0x3f6ac;
#else
    vdac_ctrl = 0x7aeac;
#endif

    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_b) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_c) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_d) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_e) >> 2), vdac_ctrl); // DAC control settings
    WRITE_ENC_REG(((RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_f) >> 2), vdac_ctrl); // DAC control settings
#else
    dac_ctrl0.u32 = VPP_REG_READ32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a);
    dac_ctrl1.u32 = VPP_REG_READ32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a + 4);
    vdac_misc1.u32 = VPP_REG_READ32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_misc1);
    vdac_misc2.u32 = VPP_REG_READ32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_misc2);
    // power down all dacs
    dac_ctrl1.uctrl1_pu = 0;
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_b + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_c + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_d + 4, dac_ctrl1.u32);
#if (BERLIN_CHIP_VERSION < BERLIN_BG2_A0)
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_e + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_f + 4, dac_ctrl1.u32);
#endif

    // set dac ctrl
    dac_ctrl0.uctrl0_mode = 2;
    dac_ctrl0.uctrl0_gin = 246;
    dac_ctrl0.uctrl0_off_in_p = 161;
    dac_ctrl0.uctrl0_off_in_m = 161;
    dac_ctrl1.uctrl1_en_cal = 1;
    dac_ctrl1.uctrl1_force_imp_ok = 0;
    dac_ctrl1.uctrl1_en_bline_cor = 0;
    dac_ctrl1.uctrl1_force_pd_outp = 0;
    vdac_misc1.umisc1_pu_gdac = 1;

    vdac_misc2.umisc2_rng_comp = 0x24;
    vdac_misc2.umisc2_rng_cvbs = 0x1F;
    vdac_misc2.umisc2_rng_svideo75 = 0xF;
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_misc2, vdac_misc2.u32);

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_B0)
    /* Dac Ctrl0 local variables */
    vpp_obj->be.enc.DacCtrl0_a = dac_ctrl0.u32;
    vpp_obj->be.enc.DacCtrl0_b = dac_ctrl0.u32;
    vpp_obj->be.enc.DacCtrl0_d = dac_ctrl0.u32;
#endif
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_misc1, vdac_misc1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a, dac_ctrl0.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_b, dac_ctrl0.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_d, dac_ctrl0.u32);

    dac_ctrl0.uctrl0_mode = 3;

#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_B0)
    /* Dac Ctrl0 local variables */
    vpp_obj->be.enc.DacCtrl0_c = dac_ctrl0.u32;
#endif
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_c, dac_ctrl0.u32);
#if (BERLIN_CHIP_VERSION < BERLIN_BG2_A0)
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_e, dac_ctrl0.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_f, dac_ctrl0.u32);
#endif
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_b + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_c + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_d + 4, dac_ctrl1.u32);
#if (BERLIN_CHIP_VERSION < BERLIN_BG2_A0)
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_e + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_f + 4, dac_ctrl1.u32);
#endif

    // power up all dacs
    dac_ctrl1.uctrl1_pu = 1;
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_a + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_b + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_c + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_d + 4, dac_ctrl1.u32);
#if (BERLIN_CHIP_VERSION < BERLIN_BG2_A0)
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_e + 4, dac_ctrl1.u32);
    VPP_REG_WRITE32_RAW(RA_Vpp_VDAC_ctrl + RA_VDAC_ctrl_f + 4, dac_ctrl1.u32);
#endif
#endif

   // Reset encoder local variables
   vpp_obj->be.enc.SdDacMode = 0;
   vpp_obj->be.enc.HdDacMode = 0;
   vpp_obj->be.enc.SdWssCgmsCtrl = 0;
   vpp_obj->be.enc.HdWssCgmsCtrl = 0;
   vpp_obj->be.enc.EncIOMuteCtrl = 0;
   vpp_obj->be.enc.HdCtrl0 = 0;

    // Configure SD path with default component controls
    CxParams.CxSyncMode = VPP_BE_ENC_CX_SYNC_ON_YG; // embedded sync on Y channels
    CxParams.DisableClipping = 1; // clipping enabled
    CxParams.DigitalSync = 0; // Hsync and Vsync is sent out
    CxParams.HSyncPolarity = 0; // Hsync polarity not inverted
    CxParams.VSyncPolarity = 1; // Vsync polarity inverted
    BE_ENC_SetCxOutCtrl(vpp_obj, VPP_BE_ENC_SD_PATH, VPP_BE_ENC_CX_YPbPr, &CxParams);

    // Mute Inputs and Outputs
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.SdEncInpMute = MUTE_SD_ENC_INPUTS;
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.HdEncInpMute = MUTE_HD_ENC_INPUTS;
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.SdEncOutMute = MUTE_SD_ENC_OUTPUTS;
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.HdEncOutMute = MUTE_HD_ENC_OUTPUTS;
    WRITE_ENC_REG(E_CTRL_107, vpp_obj->be.enc.EncIOMuteCtrl);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : Configures the usage for the SD and HD DACs
 * Arguments    : pDacCtrlData - Pointer to DAC control data
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetDacUsage(THINVPP_OBJ *vpp_obj, int DacGrp, int DacMode)
{
    // Configure DAC usages
    if (DacGrp == VPP_BE_ENC_SD_DACS) { // SD DACs: 2(D), 1(E), 0(F)

        ((ENC_DAC_MODE_REGISTER *)(&vpp_obj->be.enc.SdDacMode))->Bits.DacSel = DacMode;
        WRITE_ENC_REG(E_CTRL_8, vpp_obj->be.enc.SdDacMode);

    } else if (DacGrp == VPP_BE_ENC_HD_DACS) { // HD DACs: 5(A), 4(B), 3(C)

        ((ENC_DAC_MODE_REGISTER *)(&vpp_obj->be.enc.HdDacMode))->Bits.DacSel = DacMode;
        WRITE_ENC_REG(E_CTRL_9, vpp_obj->be.enc.HdDacMode);
    }

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : Configures the voltage for the SD and HD DACs
 * Arguments    : DacGrp - Dac group
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetDacVoltage(THINVPP_OBJ *vpp_obj, int DacGrp, int OutRes)
{
    // Configure DAC voltage
    if (DacGrp == VPP_BE_ENC_SD_DACS) { // SD DACs: 2(D), 1(E), 0(F)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        WRITE_ENC_REG(E_CTRL_5, 0x09);
#else
        if (OutRes == VPP_BE_ENC_CVFMT_NTSC_M || OutRes == VPP_BE_ENC_CVFMT_NTSC_J)
            WRITE_ENC_REG(E_CTRL_5, 0x08);
        else if (OutRes == VPP_BE_ENC_CVFMT_PAL_BGH)
            WRITE_ENC_REG(E_CTRL_5, 0x0A);
#endif
    } else if (DacGrp == VPP_BE_ENC_HD_DACS) { // HD DACs: 5(A), 4(B), 3(C)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        WRITE_ENC_REG(E_CTRL_6, 0);
#else
#if (!defined(BERLIN_DTV_MERGE) || (BERLIN_CHIP_VERSION >= BERLIN_B_0))
        if (OutRes >= VPP_BE_ENC_RES_480p)
            WRITE_ENC_REG(E_CTRL_6, 0x0A);
        else
            WRITE_ENC_REG(E_CTRL_6, 0x0C);
#endif
#endif
    }

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : set oversampling factor for the SD and HD DACs
 * Arguments    : pDacCtrlData - Pointer to DAC control data
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetDacOversample(THINVPP_OBJ *vpp_obj, int DacGrp, int OvSmplFact)
{
    // Configure DACs
    if (DacGrp == VPP_BE_ENC_SD_DACS) {

        ((ENC_DAC_MODE_REGISTER *)(&vpp_obj->be.enc.SdDacMode))->Bits.OverSampleFactor = OvSmplFact;
        WRITE_ENC_REG(E_CTRL_8, vpp_obj->be.enc.SdDacMode);

    } else if (DacGrp == VPP_BE_ENC_HD_DACS) {

        ((ENC_DAC_MODE_REGISTER *)(&vpp_obj->be.enc.HdDacMode))->Bits.OverSampleFactor = OvSmplFact;
        WRITE_ENC_REG(E_CTRL_9, vpp_obj->be.enc.HdDacMode);
    }

    return MV_THINVPP_OK;
}



/*-----------------------------------------------------------------------------
 * Description  : This function sets HD timing values
 * Arguments    : OutRes      - Output resolution
 *              : pCompParams - Pointer to timing values structure (Input)
 *              :             - If NULL, defaults would be set for the given
 *              :             - resolution
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetSDTimingParams (THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_TIMING_PARAMS pSDTimingParams)
{
    PVPP_BE_ENC_TIMING_PARAMS   pSDParams;

    if (pSDTimingParams == NULL)
        pSDParams = &SDTimingPresets[OutRes];
    else
        pSDParams = pSDTimingParams;

    // Set timing parameters
    WRITE_ENC_REG(E_CTRL_10, pSDParams->HTotal & 0xff); // H total
    WRITE_ENC_REG(E_CTRL_11, (pSDParams->HTotal >> 8) & 0x03);
    WRITE_ENC_REG(E_CTRL_12, pSDParams->VTotal & 0xff); // V total
    WRITE_ENC_REG(E_CTRL_13, (pSDParams->VTotal >> 8) & 0x03);
    WRITE_ENC_REG(E_CTRL_14, pSDParams->HSyncWidth); // Hsync width
    WRITE_ENC_REG(E_CTRL_15, pSDParams->VSyncWidth); // Vsync width
    WRITE_ENC_REG(E_CTRL_16, pSDParams->HdeStart); // HDE start
    WRITE_ENC_REG(E_CTRL_17, pSDParams->VdeStart); // VDE start
    WRITE_ENC_REG(E_CTRL_18, pSDParams->HdeEnd & 0xff); // HDE end
    WRITE_ENC_REG(E_CTRL_19, (pSDParams->HdeEnd >> 8) & 0x03);
    WRITE_ENC_REG(E_CTRL_20, pSDParams->VdeEnd & 0xff); // VDE end
    WRITE_ENC_REG(E_CTRL_21, (pSDParams->VdeEnd >> 8) & 0x03);
    WRITE_ENC_REG(E_CTRL_22, pSDParams->BurstStart); // Burst start
    WRITE_ENC_REG(E_CTRL_23, pSDParams->BurstEnd); // Burst end
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    WRITE_ENC_REG(E_CTRL_48, pSDParams->VdePadUp); // VDE Pad Up
    WRITE_ENC_REG(E_CTRL_49, pSDParams->VdePadDown); // VDE Pad Down
    WRITE_ENC_REG(E_CTRL_50, pSDParams->VdePadYData); // VDE Pad Y Data
#else // Berlin_A0
    WRITE_ENC_REG(E_CTRL_48, pSDParams->DEMaskMode); // 1/2 line mask
#endif

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets HD timing values
 * Arguments    : OutRes      - Output resolution
 *              : pCompParams - Pointer to timing values structure (Input)
 *              :             - If NULL, defaults would be set for the given
 *              :             - resolution
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetHDTimingParams (THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_TIMING_PARAMS pHDTimingParams)
{
    PVPP_BE_ENC_TIMING_PARAMS  pHDParams;

    if (pHDTimingParams == NULL)
        pHDParams = &HDTimingPresets[OutRes];
    else
        pHDParams = pHDTimingParams;

    // Set timing parameters
    WRITE_ENC_REG(E_CTRL_128, pHDParams->HTotal & 0xff); // H total
    WRITE_ENC_REG(E_CTRL_129, (pHDParams->HTotal >> 8) & 0x1f);
    WRITE_ENC_REG(E_CTRL_130, pHDParams->VTotal & 0xff); // V total
    WRITE_ENC_REG(E_CTRL_131, (pHDParams->VTotal >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_132, pHDParams->HSyncWidth); // Hsync width
    WRITE_ENC_REG(E_CTRL_133, pHDParams->VSyncWidth); // Vsync width
    WRITE_ENC_REG(E_CTRL_134, pHDParams->HdeStart & 0xff); // HDE start
    WRITE_ENC_REG(E_CTRL_135, (pHDParams->HdeStart >> 8) & 0x1f);
    WRITE_ENC_REG(E_CTRL_136, pHDParams->VdeStart & 0xff); // VDE start
    WRITE_ENC_REG(E_CTRL_137, (pHDParams->VdeStart >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_138, pHDParams->HdeEnd & 0xff); // HDE end
    WRITE_ENC_REG(E_CTRL_139, (pHDParams->HdeEnd >> 8) & 0x1f);
    WRITE_ENC_REG(E_CTRL_140, pHDParams->VdeEnd & 0xff); // VDE end
    WRITE_ENC_REG(E_CTRL_141, (pHDParams->VdeEnd >> 8) & 0x07);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    WRITE_ENC_REG(E_CTRL_162, pHDParams->VdePadUp); // VDE Pad
    WRITE_ENC_REG(E_CTRL_149, pHDParams->VdePadYData); // VDE Pad Y Data
#else // Berlin_A0
    WRITE_ENC_REG(E_CTRL_162, pHDParams->DEMaskMode); // 1/2 line mask
#endif

    ((ENC_HD_OUT_CTRL_REGISTER1 *)(&vpp_obj->be.enc.HdCtrl0))->Bits.TgMode = pHDParams->SyncLevel;
    WRITE_ENC_REG(E_CTRL_142, vpp_obj->be.enc.HdCtrl0);
    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets CVBS and SVideo parameters
 * Arguments    : SdOutFmt - Output format (Ntsc/Pal)
 *              : pCvbsSVideoParams - Pointer to Cvbs and SVideo parameters
 *              :                   - (Input). If NULL, defaults would be set
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetCvbsSVideoParams(THINVPP_OBJ *vpp_obj, int SdOutFmt, PVPP_BE_ENC_CVBS_SVIDEO_PARAMS pCvbsSVideoParams)
{
    PVPP_BE_ENC_CVBS_SVIDEO_PARAMS  pSDParams;
    ENC_SD_CV_OUT_GRAD_SELECT_REGISTER1 CvOutGradSel1;
    ENC_SD_CV_OUT_SC_GEN_RESET_FREQ_REGISTER CvOutSCGenResetFreq;

    if (pCvbsSVideoParams == NULL)
        pSDParams = &CvbsSVideoPresets[SdOutFmt];
    else
        pSDParams = pCvbsSVideoParams;

    WRITE_ENC_REG(E_CTRL_26, pSDParams->NtscPal);
    WRITE_ENC_REG(E_CTRL_27, pSDParams->SyncPedestal);
    WRITE_ENC_REG(E_CTRL_28, pSDParams->SyncHeight & 0xff);
    WRITE_ENC_REG(E_CTRL_29, pSDParams->SyncHeight >> 8);

    CvOutGradSel1.Bits.SyncGradient = pSDParams->SyncGradient;
    CvOutGradSel1.Bits.BlankGradient = pSDParams->BlankGradient;
    WRITE_ENC_REG(E_CTRL_30, *((unsigned int *)&CvOutGradSel1));
    WRITE_ENC_REG(E_CTRL_31, pSDParams->BurstWindowGradient);

    WRITE_ENC_REG(E_CTRL_32, pSDParams->LumaClipping);
    WRITE_ENC_REG(E_CTRL_33, pSDParams->YSetupVal);
    WRITE_ENC_REG(E_CTRL_34, pSDParams->YScale & 0xff);
    WRITE_ENC_REG(E_CTRL_35, (pSDParams->YScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_36, pSDParams->CbScale & 0xff);
    WRITE_ENC_REG(E_CTRL_37, (pSDParams->CbScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_38, pSDParams->CrScale & 0xff);
    WRITE_ENC_REG(E_CTRL_39, (pSDParams->CrScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_40, pSDParams->LumaOffset & 0xff);
    WRITE_ENC_REG(E_CTRL_41, (pSDParams->LumaOffset >> 8) & 0x01);
    WRITE_ENC_REG(E_CTRL_42, pSDParams->MinOutDataLevel & 0xff);
    WRITE_ENC_REG(E_CTRL_43, (pSDParams->MinOutDataLevel >> 8) & 0x0f);
    WRITE_ENC_REG(E_CTRL_44, pSDParams->MaxOutputDataLevel & 0xff);
    WRITE_ENC_REG(E_CTRL_45, (pSDParams->MaxOutputDataLevel >> 8) & 0x0f);
    WRITE_ENC_REG(E_CTRL_57, pSDParams->HueOffset);

    // Set subcarrier parameters
    WRITE_ENC_REG(E_CTRL_52, pSDParams->SCFreq & 0xff);
    WRITE_ENC_REG(E_CTRL_53, (pSDParams->SCFreq >> 8) & 0xff);
    WRITE_ENC_REG(E_CTRL_54, (pSDParams->SCFreq >> 16) & 0xff);
    WRITE_ENC_REG(E_CTRL_55, (pSDParams->SCFreq >> 24) & 0xff);
    WRITE_ENC_REG(E_CTRL_56, pSDParams->SCInitialPhase);

    CvOutSCGenResetFreq.Value = 0;
    CvOutSCGenResetFreq.Bits.ResetCtrl = pSDParams->SCGenResetFreq;
    WRITE_ENC_REG(E_CTRL_58, *((unsigned int *)&CvOutSCGenResetFreq));

    BE_ENC_SetCVPathFltrParams(vpp_obj, &DefFltrParams);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets SD component parameters
 * Arguments    : OutRes      - Output resolution
 *              : pCompParams - Pointer to component parameters (Input)
 *              :             - If NULL, defaults would be set
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetSDComponentParams(THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_COMPONENT_PARAMS pCompParams)
{
    PVPP_BE_ENC_COMPONENT_PARAMS    pSDParams;

    if (pCompParams == NULL)
        pSDParams = &CompPresets[OutRes];
    else
        pSDParams = pCompParams;

    WRITE_ENC_REG(E_CTRL_61, pSDParams->SetupValue);
    WRITE_ENC_REG(E_CTRL_64, pSDParams->SyncPedestal);
    WRITE_ENC_REG(E_CTRL_62, pSDParams->SyncHeight & 0xff);
    WRITE_ENC_REG(E_CTRL_63, pSDParams->SyncHeight >> 8);
    WRITE_ENC_REG(E_CTRL_65, pSDParams->SyncGradient);

    WRITE_ENC_REG(E_CTRL_66, pSDParams->CbBScale & 0xff);
    WRITE_ENC_REG(E_CTRL_67, (pSDParams->CbBScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_68, pSDParams->YGScale & 0xff);
    WRITE_ENC_REG(E_CTRL_69, (pSDParams->YGScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_70, pSDParams->CrRScale & 0xff);
    WRITE_ENC_REG(E_CTRL_71, (pSDParams->CrRScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_72, pSDParams->CbBOffset & 0xff);
    WRITE_ENC_REG(E_CTRL_73, (pSDParams->CbBOffset >> 8) & 0x01);
    WRITE_ENC_REG(E_CTRL_74, pSDParams->YGOffset & 0xff);
    WRITE_ENC_REG(E_CTRL_75, (pSDParams->YGOffset >> 8) & 0x01);
    WRITE_ENC_REG(E_CTRL_76, pSDParams->CrROffset & 0xff);
    WRITE_ENC_REG(E_CTRL_77, (pSDParams->CrROffset >> 8) & 0x01);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets HD component parameters
 * Arguments    : OutRes      - Output resolution
 *              : pCompParams - Pointer to component parameters (Input)
 *              :             - If NULL, defaults would be set
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetHDComponentParams(THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_COMPONENT_PARAMS pCompParams)
{
    PVPP_BE_ENC_COMPONENT_PARAMS    pHDParams;

    if (pCompParams == NULL)
        pHDParams = &CompPresets[OutRes];
    else
        pHDParams = pCompParams;

    WRITE_ENC_REG(E_CTRL_144, pHDParams->SetupValue);
    WRITE_ENC_REG(E_CTRL_145, pHDParams->SyncPedestal);
    WRITE_ENC_REG(E_CTRL_146, pHDParams->SyncHeight & 0xff);
    WRITE_ENC_REG(E_CTRL_147, pHDParams->SyncHeight >> 8);
    WRITE_ENC_REG(E_CTRL_148, pHDParams->SyncGradient);

    WRITE_ENC_REG(E_CTRL_150, pHDParams->CbBScale & 0xff);
    WRITE_ENC_REG(E_CTRL_151, (pHDParams->CbBScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_152, pHDParams->YGScale & 0xff);
    WRITE_ENC_REG(E_CTRL_153, (pHDParams->YGScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_154, pHDParams->CrRScale & 0xff);
    WRITE_ENC_REG(E_CTRL_155, (pHDParams->CrRScale >> 8) & 0x07);
    WRITE_ENC_REG(E_CTRL_156, pHDParams->CbBOffset & 0xff);
    WRITE_ENC_REG(E_CTRL_157, (pHDParams->CbBOffset >> 8) & 0x01);
    WRITE_ENC_REG(E_CTRL_158, pHDParams->YGOffset & 0xff);
    WRITE_ENC_REG(E_CTRL_159, (pHDParams->YGOffset >> 8) & 0x01);
    WRITE_ENC_REG(E_CTRL_160, pHDParams->CrROffset & 0xff);
    WRITE_ENC_REG(E_CTRL_161, (pHDParams->CrROffset >> 8) & 0x01);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets component out control fields for HD Path
 * Arguments    : CxOutFmt   - component output format
 *              : pCXOutCtrl - Pointer to control field structure (Input)
 *              :            - If NULL, defaults would be set
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetHDCxOutCtrl (THINVPP_OBJ *vpp_obj, int CxOutMode, PVPP_BE_ENC_CX_CTRL_PARAMS pCXOutCtrl)
{
    BE_ENC_SetCxOutCtrl(vpp_obj, VPP_BE_ENC_HD_PATH, CxOutMode, pCXOutCtrl);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets component out control fields for SD Path
 * Arguments    : CxOutFmt   - component output format
 *              : pCXOutCtrl - Pointer to control field structure (Input)
 *              :            - If NULL, defaults would be set
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetSDCxOutCtrl (THINVPP_OBJ *vpp_obj, int CxOutMode, PVPP_BE_ENC_CX_CTRL_PARAMS pCXOutCtrl)
{
    BE_ENC_SetCxOutCtrl(vpp_obj, VPP_BE_ENC_SD_PATH, CxOutMode, pCXOutCtrl);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function sets the filter settings to be used for
 *              : composite and s-video output
 * Arguments    : pCVPathFltrParams - Pointer to filter config parameters
 * Returns      : MV_THINVPP_OK on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetCVPathFltrParams (THINVPP_OBJ *vpp_obj, PVPP_BE_ENC_CV_PATH_FLTR_PARAMS pCVPathFltrParams)
{
    ENC_SD_CV_OUT_FILT_CTRL_REGISTER1 CvOutFlterCtrl1;

    CvOutFlterCtrl1.Bits.CVLumaLPFCtrl = pCVPathFltrParams->CvbsLumaLPFCtrlMode;
    CvOutFlterCtrl1.Bits.CVChromaLPFCtrl = pCVPathFltrParams->CvbsChromaLPFCtrlMode;
    CvOutFlterCtrl1.Bits.LumaNotchFilterCtrl = pCVPathFltrParams->CvbsLumaNotchFilterCtrlMode;
    CvOutFlterCtrl1.Bits.SVideoChromaLPFCtrl = pCVPathFltrParams->SVideoChromaLPFCtrlMode;
    CvOutFlterCtrl1.Bits.SVideoChromaLPFCtrl = pCVPathFltrParams->SVideoChromaLPFCtrlMode;
    WRITE_ENC_REG(E_CTRL_24, *((unsigned int *)&CvOutFlterCtrl1));
    WRITE_ENC_REG(E_CTRL_25, (unsigned int)pCVPathFltrParams->SVideoLumaSelectMode);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function configures the mute settings for the SD encoder
 *              : input. Using this, encoder inpus would be read from the
 *              : fixed mute color registers
 * Arguments    : InpMute - Input mute control field
 *              : Update  - True, if hardware register has to be updated
 *              :         - False, otherwise
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetSDInpMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char InpMute, int  Update)
{
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.SdEncInpMute = InpMute;

    if (Update)
        WRITE_ENC_REG(E_CTRL_107, vpp_obj->be.enc.EncIOMuteCtrl);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function configures the mute settings for the HD encoder
 *              : input. Using this, encoder inpus would be read from the
 *              : fixed mute color registers
 * Arguments    : InpMute - Input mute control field
 *              : Update  - True, if hardware register has to be updated
 *              :         - False, otherwise
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetHDInpMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char InpMute, int  Update)
{
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.HdEncInpMute = InpMute;

    if (Update)
        WRITE_ENC_REG(E_CTRL_107, vpp_obj->be.enc.EncIOMuteCtrl);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function mutes the SD encoder output (dac input)
 * Arguments    : OutMute - Mute field
 *              : Update  - True, if hardware register has to be updated
 *              :         - False, otherwise
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetSDOutMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char OutMute, int Update)
{
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.SdEncOutMute = OutMute;

    if (Update)
        WRITE_ENC_REG(E_CTRL_107, vpp_obj->be.enc.EncIOMuteCtrl);

    return MV_THINVPP_OK;
}

/*-----------------------------------------------------------------------------
 * Description  : This function mutes the SD encoder output (dac input)
 * Arguments    : OutMute - Mute field
 *              : Update  - True, if hardware register has to be updated
 *              :         - False, otherwise
 * Returns      : MV_THINVPP_OK, on success
 *              : Error code, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int BE_ENC_SetHDOutMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char OutMute, int Update)
{
    ((ENC_MUTE_CTRL_REGISTER *)(&vpp_obj->be.enc.EncIOMuteCtrl))->Bits.HdEncOutMute = OutMute;

    if (Update)
        WRITE_ENC_REG(E_CTRL_107, vpp_obj->be.enc.EncIOMuteCtrl);

    return MV_THINVPP_OK;
}
