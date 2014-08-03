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

#define _VPP_FRC_SCL_C_

#include "thinvpp_module.h"
#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "thinvpp_cpcb.h"

#include "vpp_frc_scl.h"
#include "vpp_frc_scl_prv.h"

#include "maddr.h"
#include "vpp.h"
#include "memmap.h"

#include "coeff_hpanasharp.h"
#include "coeff_h_bypass.h"
#include "coeff_hred_1_5.h"
#include "coeff_hred_2_7.h"

#include "coeff_vpanasharp.h"
#include "coeff_v_bypass.h"
#include "coeff_vred_1_5.h"
#include "coeff_vred_1_5_5taps.h"
#include "coeff_vred_1_5_3taps.h"
#include "coeff_vred_2_25.h"

typedef const unsigned short (* SCL_COEFF_PARAM)[12];

typedef struct SCL_COEFF_T {
    int format;
    SCL_COEFF_PARAM coeff;
}SCL_COEFF;

static SCL_COEFF m_scl_coeff_table[] = {
    {0x1A, coeff_hPanaSharp}, /* COEFF_H_PSHARP */
    {0x0B, coeff_h_bypass},   /* COEFF_H_BYPASS */
    {0x1A, coeff_hred_1_5},   /* COEFF_HRED_BY_1_5 */
    {0x1A, coeff_hred_2_7},   /* COEFF_HRED_BY_2_7 */

    {0x1A, coeff_vPanaSharp}, /* COEFF_V_PSHARP */
    {0x0B, coeff_v_bypass},   /* COEFF_V_BYPASS */
    {0x1A, coeff_vred_1_5},          /* COEFF_VRED_BY_1_5 */
    {0x1A, coeff_vred_1_5_5taps},    /* COEFF_VRED_BY_1_5_5taps */
    {0x1A, coeff_vred_1_5_3taps},    /* COEFF_VRED_BY_1_5_3taps */
    {0x1A, coeff_vred_2_25},  /* COEFF_VRED_BY_2_25 */
};

/***************************************************************************************
 * FUNCTION: internal fuction to get the start address of an FRC SCL instance by unit number
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4, 5)
 * RETURN:  the start address
 ***************************************************************************************/
unsigned int INTERNAL_FRC_SCL_GetRegStartAddr(THINVPP_OBJ *vpp_obj, int UnitNum)
{
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    if (UnitNum < VPP_FRC_SCL_BE)
        return (vpp_obj->base_addr + ((FRC0_OFFSET + UnitNum * 0x100) << 2));
    else
        return (vpp_obj->base_addr + ((FRC5_OFFSET + (UnitNum-VPP_FRC_SCL_BE) * 0x100) << 2));
#else
    if (UnitNum != VPP_FRC_SCL_BE)
        return (vpp_obj->base_addr + ((FRC0_OFFSET + UnitNum * 0x100) << 2));
    else
        return (vpp_obj->base_addr + (FRC5_OFFSET << 2));
#endif
}

static void Generate_Scl_Coefficiena(THINVPP_OBJ *vpp_obj, int sclID, int hv, int format, const unsigned short (* coeffs)[12])
{
    int line, i;
    unsigned int addr, value;

    if (!hv) {
        /*set H ctrl*/
        addr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, sclID) + (SCL_HCTRL_0 << 2);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, addr, format);
    } else {
        /*set V ctrl*/
        addr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, sclID) + (SCL_VCTRL_0 << 2);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, addr, format);
    }

    for (line=0; line<33; line++) {
        addr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, sclID) + (SCL_COEFF0_L * 4);
        for (i=0; i<12; i++) {
            value = coeffs[line][i];
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, addr, value&0x00ff);
            addr += 4;
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, addr, (value>>8)&0x00ff);
            addr += 4;
        }
        if (!hv)
            value = 0x40;
        else
            value = 0x00;
        value += line;
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, addr, value);
        addr += 4;
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, addr, 0x0ff);
    }

    return;
}

/***************************************************************************************
 * FUNCTION: load the default register values to FRC SCL the unit
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4, 5)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int UnitNum)
{
    int RetVal = MV_THINVPP_OK;

    switch(UnitNum){
#if VPPFB_ENABLE_MAIN
        case VPP_FRC_SCL_MAIN:
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_CTRL0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_DLY_FRST_DE, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_DLY_DE_LRST, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_DLY_LRST_DE, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEHRES_L, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEHRES_H, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEVRES_L, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEVRES_H, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_FEVRES_L, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_FEVRES_H, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_SCLCLK_CTRL, gFrcScl0DefValues);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_SCLCLK_CTRL1, gFrcScl0DefValues);
#endif

            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IVRES_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IVRES_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IHRES_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IHRES_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OVRES_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OVRES_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OHRES_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OHRES_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_MEMSIZE_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_MEMSIZE_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VRATIO_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VRATIO_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VRATIO_2, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HRATIO_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HRATIO_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HRATIO_2, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VWRAP_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VWRAP_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VINITPH_EVEN, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VINITPH_ODD, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HINITPH, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VCTRL_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HCTRL_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_CTRL_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_NUMTAPS, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HTAP_OFFSET, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VTAP_OFFSET, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_STALL, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INIT_RATIO_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INIT_RATIO_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INIT_RATIO_2, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INC_RATIO_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INC_RATIO_1, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INC_RATIO_2, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_NLCRES_0, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_NLCRES_1, gFrcScl0DefValues);

            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_MEMCTRL, gFrcScl0DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_ALPH_CTRL, gFrcScl0DefValues);

            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_MAIN_LSIZE, gFrcSclNewDefValues);
            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_main_ols, gFrcSclNewDefValues);
            break;
#endif
#if VPPFB_ENABLE_PIP
        case VPP_FRC_SCL_PIP:
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_CTRL0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_DLY_FRST_DE, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_DLY_DE_LRST, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_DLY_LRST_DE, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEHRES_L, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEHRES_H, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEVRES_L, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_BEVRES_H, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_FEVRES_L, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_FEVRES_H, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_SCLCLK_CTRL, gFrcScl1DefValues);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, FRC_SCLCLK_CTRL1, gFrcScl1DefValues);
#endif

            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IVRES_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IVRES_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IHRES_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_IHRES_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OVRES_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OVRES_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OHRES_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_OHRES_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_MEMSIZE_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_MEMSIZE_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VRATIO_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VRATIO_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VRATIO_2, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HRATIO_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HRATIO_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HRATIO_2, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VWRAP_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VWRAP_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VINITPH_EVEN, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VINITPH_ODD, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HINITPH, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VCTRL_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HCTRL_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_CTRL_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_NUMTAPS, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_HTAP_OFFSET, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_VTAP_OFFSET, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_STALL, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INIT_RATIO_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INIT_RATIO_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INIT_RATIO_2, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INC_RATIO_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INC_RATIO_1, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_INC_RATIO_2, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_NLCRES_0, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_NLCRES_1, gFrcScl1DefValues);

            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_MEMCTRL, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(UnitNum, SCL_ALPH_CTRL, gFrcScl1DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_PIP_LSIZE, gFrcSclNewDefValues);
            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_pip_pix, gFrcSclNewDefValues);
            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_pip_ols, gFrcSclNewDefValues);
#if (BERLIN_CHIP_VERSION >= BERLIN_C_2)
            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_PIP_AL_IN, gFrcSclNewDefValues);
            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_PIP_AL_OUT, gFrcSclNewDefValues);
#endif
            break;
#endif

        case VPP_FRC_SCL_BE:
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_CTRL0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_DLY_FRST_DE, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_DLY_DE_LRST, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_DLY_LRST_DE, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_BEHRES_L, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_BEHRES_H, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_BEVRES_L, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_BEVRES_H, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_FEVRES_L, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_FEVRES_H, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_SCLCLK_CTRL, gFrcScl5DefValues);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, FRC_SCLCLK_CTRL1, gFrcScl5DefValues);
#endif

            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_IVRES_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_IVRES_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_IHRES_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_IHRES_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_OVRES_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_OVRES_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_OHRES_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_OHRES_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_MEMSIZE_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_MEMSIZE_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VRATIO_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VRATIO_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VRATIO_2, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_HRATIO_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_HRATIO_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_HRATIO_2, gFrcScl5DefValues);

            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VWRAP_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VWRAP_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VINITPH_EVEN, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VINITPH_ODD, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_HINITPH, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VCTRL_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_HCTRL_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_CTRL_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_NUMTAPS, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_HTAP_OFFSET, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_VTAP_OFFSET, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_STALL, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_INIT_RATIO_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_INIT_RATIO_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_INIT_RATIO_2, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_INC_RATIO_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_INC_RATIO_1, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_INC_RATIO_2, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_NLCRES_0, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_NLCRES_1, gFrcScl5DefValues);

            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_MEMCTRL, gFrcScl5DefValues);
            WRITE_FRC_SCL_DEFAULT_VAL(VPP_FRC_SCL_BE, SCL_ALPH_CTRL, gFrcScl5DefValues);

            WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_AUX_LSIZE, gFrcSclNewDefValues);

            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_FIFO_CTRL, gFrcSclNewDefValues.VPP_RA_FE_BE_FIFO_CTRL)))
                return RetVal;

            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_LRST, gFrcSclNewDefValues.VPP_RA_FE_BE_LRST)))
                return RetVal;

            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_FRST, gFrcSclNewDefValues.VPP_RA_FE_BE_FRST)))
                return RetVal;

            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_SYNC_CTRL, gFrcSclNewDefValues.VPP_RA_FE_BE_SYNC_CTRL)))
                return RetVal;

            break;

        default:
            return MV_THINVPP_EBADPARAM;
    }

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set HV resolution to FRC unit.
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4, 5)
 *               pFrcRes - pointer to the resolution data stucture
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetFrcParams(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_FRC_RES pFrcRes)
{
    unsigned int RegAddr;
    unsigned int Lowbyte, Highbits;
    int RetVal = MV_THINVPP_OK;

    CHECK_FRC_SCL_NUM(UnitNum);

    /*get register start address of the FRC_SCL unit */
    RegAddr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, UnitNum);

    /*get the low byte of H resolution*/
    Lowbyte = GET_LOWEST_BYTE(pFrcRes->HRes);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_BEHRES_L << 2), Lowbyte)))
         return RetVal;

    /*get high bits*/
    Highbits = pFrcRes->HRes >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_BEHRES_H << 2), Highbits)))
         return RetVal;

    /*set BE V resolution*/
    Lowbyte = GET_LOWEST_BYTE(pFrcRes->VRes);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_BEVRES_L << 2), Lowbyte)))
         return RetVal;

    Highbits = pFrcRes->VRes >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_BEVRES_H << 2), Highbits)))
         return RetVal;

    /* FEVRES need be set in SCL4*/
    if(VPP_FRC_SCL_BE == UnitNum){

        /*set V resolution*/
        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_FEVRES_L << 2), Lowbyte)))
            return RetVal;

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_FEVRES_H << 2), Highbits)))
            return RetVal;
    }
    return  RetVal;
}

/***************************************************************************************
 * FUNCTION: set delay between DE  to line reset.
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4, 5)
 *               DeLrstDelay -delay value
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetDeLrstDelay(THINVPP_OBJ *vpp_obj, int UnitNum, unsigned int DeLrstDelay)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    CHECK_FRC_SCL_NUM(UnitNum);

    /*get register start address of the FRC_SCL unit */
    RegAddr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, UnitNum);

    /*set it to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_DLY_DE_LRST << 2), DeLrstDelay)))
         return RetVal;

    return  RetVal;
}

/***************************************************************************************
 * FUNCTION: set control information and I&O resolution to scaler
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4, 5)
 *               pIORes -pointer to I&O resolution
 *               pSclCtrl - pointer to scaler control information
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetSclCtrlParams(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_SCL_RES pIORes, PVPP_SCL_CTRL pSclCtrl)
{
    unsigned int RegAddr;
    unsigned int RegVal;
    unsigned int Lowbyte, Highbits;
    unsigned char  HSclPos;
    unsigned int HRatio, VRatio;
    unsigned char  HTapN, VTapN;
    unsigned char  Bit24or16;    /*24-bit or 16-bit in line buffer*/
    unsigned int SclMemSize;
    unsigned char MaxVTapNum, MaxVTap;
    unsigned int InitPh;
    unsigned int LineSize;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned int VTableSel = 0;
#endif
    int RetVal = MV_THINVPP_OK;

    CHECK_FRC_SCL_NUM(UnitNum);

    /*get register start address of the FRC_SCL unit */
    RegAddr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, UnitNum);

    /*-------------------------
    -set input and output resolutions-
    --------------------------*/
    /*set input vertical resolution*/
    Lowbyte = GET_LOWEST_BYTE(pIORes->IVRes);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_IVRES_0 << 2), Lowbyte)))
        return RetVal;

    Highbits = pIORes->IVRes >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_IVRES_1 << 2), Highbits)))
        return RetVal;

    /*set input horizontal resolution*/
    Lowbyte = GET_LOWEST_BYTE(pIORes->IHRes);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_IHRES_0 << 2), Lowbyte)))
        return RetVal;

    Highbits = pIORes->IHRes >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_IHRES_1 << 2), Highbits)))
        return RetVal;

    /*set output vertical resolution*/
    Lowbyte = GET_LOWEST_BYTE(pIORes->OVRes);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_OVRES_0 << 2), Lowbyte)))
        return RetVal;

    Highbits = pIORes->OVRes >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_OVRES_1 << 2), Highbits)))
        return RetVal;

    /*set output horizontal resolution*/
    Lowbyte = GET_LOWEST_BYTE(pIORes->OHRes);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_OHRES_0 << 2), Lowbyte)))
        return RetVal;

    Highbits = pIORes->OHRes >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_OHRES_1 << 2), Highbits)))
        return RetVal;

    /*-------------------
    -set SCL control register-
    --------------------*/

    /*If auto, HSCL position is decided by HV resolutions*/
    if(VPP_SCL_HSCALE_AUTO == pSclCtrl->HScalePos){
        if(pIORes->IHRes > pIORes->OHRes){
	     HSclPos = VPP_SCL_HSCALE_BEFORE;
        }else if(pIORes->IHRes < pIORes->OHRes){
            HSclPos = VPP_SCL_HSCALE_AFTER;
        }else{
            HSclPos = VPP_SCL_HSCALE_ABSENT;
        }
    }else{
        HSclPos = pSclCtrl->HScalePos;
    }

    /*if non linear scaling, H scaler is after V scaler*/
    if(1 == pSclCtrl->NLEn)
        HSclPos = VPP_SCL_HSCALE_AFTER;

    RegVal = HSclPos+(pSclCtrl->InputClr<<2)+(pSclCtrl->OsdInput<<3)+(pSclCtrl->NLEn<<4)+(pSclCtrl->BitMode<<5)+(pSclCtrl->I565<<7);

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_CTRL_0 << 2), RegVal)))
        return RetVal;

    /*-------------------------------------
    -calculate horizontal and vertical scaling ratio -
    -------------------------------------*/
    if(1 == pSclCtrl->NLEn){
        HRatio = ((unsigned int) pIORes->IVRes << 20) / pIORes->OVRes;
    }else{
        HRatio = ((unsigned int) pIORes->IHRes << 20) / pIORes->OHRes;
    }

    if(HRatio > 0xF00000)
	  HRatio = 0xF00000;
    else if(HRatio < 0x004000)
         HRatio = 0x004000;

    Lowbyte = GET_LOWEST_BYTE(HRatio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_HRATIO_0 << 2), Lowbyte)))
         return RetVal;

    Highbits = GET_SECOND_BYTE(HRatio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_HRATIO_1 << 2), Highbits)))
         return RetVal;

    Highbits = GET_THIRD_BYTE(HRatio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_HRATIO_2 << 2), Highbits)))
         return RetVal;

    VRatio = ((unsigned int) pIORes->IVRes << 20) / pIORes->OVRes;

    if(VRatio > 0xF00000)
	  VRatio = 0xF00000;
    else if(VRatio < 0x004000)
         VRatio = 0x004000;

    Lowbyte = GET_LOWEST_BYTE(VRatio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_VRATIO_0 << 2), Lowbyte)))
         return RetVal;

    Highbits = GET_SECOND_BYTE(VRatio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_VRATIO_1 << 2), Highbits)))
         return RetVal;

    Highbits = GET_THIRD_BYTE(VRatio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_VRATIO_2 << 2), Highbits)))
         return RetVal;

    /*--------------------------
    -calculate htap and vtap numbers-
    ---------------------------*/
    /*H tap number*/
    if(pSclCtrl->HTapNum > VPP_SCL_HTAP_NUM_MAX){
        HTapN = VPP_SCL_HTAP_NUM_MAX;
    }else if(pSclCtrl->HTapNum < VPP_SCL_HTAP_NUM_MIN){
        HTapN = VPP_SCL_HTAP_NUM_MIN;
    }else
        HTapN = pSclCtrl->HTapNum;

    /*V tap number*/
    SclMemSize = (VPP_SCL_LINE_BUF_ADDR_MAX + 1) * 144;

    if(pSclCtrl->OsdInput){
        /*OSD input alway 24-bit AYC*/
        Bit24or16 = 1;
    }else{
        /*video input, packing in buffer is decided by H scaler position, input and output bit mode*/
        switch((HSclPos << 2) | pSclCtrl->BitMode){
            case 0:
	         Bit24or16 = 0;
		  break;
            case 3:
	         Bit24or16 = 1;
		  break;
            case 2:
	         Bit24or16 = 0;
		  break;

            case 8:
	         Bit24or16 = 0;
		  break;
            case 11:
	         Bit24or16 = 1;
		  break;
            case 10:
	         Bit24or16 = 1;
		  break;
            case 9:
	         Bit24or16 = 0;
		  break;

            case 12:
	         Bit24or16 = 0;
		  break;
            case 15:
	         Bit24or16 = 1;
		  break;
            case 14:
	         Bit24or16 = 0;
		  break;
            case 13:
	         Bit24or16 = 1;
		  break;

	     default:
		  Bit24or16 = 0;
	}
    }

    if(Bit24or16){

	 MaxVTap = VPP_SCL_VTAP_NUM_MAX_24BIT;

         if(VPP_SCL_HSCALE_BEFORE == HSclPos)
	     MaxVTapNum = (SclMemSize / pIORes->OHRes / 24) - 1;
	 else
	     MaxVTapNum = (SclMemSize / pIORes->IHRes / 24) - 1;

         if (MaxVTapNum < 5)
            MaxVTapNum = 3;
#if 0
         if (MaxVTapNum == 5) {
             if (pIORes->IVRes > pIORes->OVRes) // vertical downscaling
                 MaxVTapNum = 3;
         }
#endif
    }else{

	 MaxVTap = VPP_SCL_VTAP_NUM_MAX_16BIT;

         if(VPP_SCL_HSCALE_BEFORE == HSclPos)
	     MaxVTapNum = ((SclMemSize / pIORes->OHRes) >> 4) - 1;
	 else
	     MaxVTapNum = ((SclMemSize / pIORes->IHRes) >> 4) - 1;

         if (MaxVTapNum == 5) {
             if (pIORes->IVRes > pIORes->OVRes) // vertical downscaling
                 MaxVTapNum = 3;
         } else if (MaxVTapNum < 8) {
                 MaxVTapNum = 5;
         } else if (MaxVTapNum == 8) {
             if (pIORes->IVRes > pIORes->OVRes) // vertical downscaling
                 MaxVTapNum = 5;
         }

    }

    MaxVTapNum = (MaxVTapNum < MaxVTap) ? MaxVTapNum : MaxVTap;

    if(pSclCtrl->VTapNum > MaxVTapNum){
        VTapN = MaxVTapNum;
    }else if(pSclCtrl->VTapNum < VPP_SCL_VTAP_NUM_MIN){
        VTapN = VPP_SCL_VTAP_NUM_MIN;
    }else
        VTapN = pSclCtrl->VTapNum;

    if (pIORes->IVRes == pIORes->OVRes) { // no scaling vertically
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
        if ((UnitNum == VPP_FRC_SCL_MAIN)
         || (UnitNum == VPP_FRC_SCL_PIP)
         || (UnitNum == VPP_FRC_SCL_BE))
#endif
            VTapN = 2;
    }

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    if (pIORes->IVRes <= pIORes->OVRes) // upscaling or no scaling vertically
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_SCLCLK_CTRL1 << 2), 0x40); // slow SCL clock by half
    else
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (FRC_SCLCLK_CTRL1 << 2), 0x80);
#endif

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    if((VPP_FRC_SCL_DETAIL == UnitNum) || (VPP_FRC_SCL_MAIN == UnitNum)) {
        /*detail scaler only can be 2, 5 and 8 taps, main scaler should have the same tap number*/
        if(VTapN == 8){
            /*use table 2*/
            VTableSel = 1;
        }else if(VTapN == 5){
            /*use table 3*/
            VTableSel = 2;
        } else if (VTapN == 2){
            /*use table 1*/
            VTableSel = 0;
        }
    }
#endif

    pSclCtrl->VTapNum = VTapN;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_NUMTAPS << 2), (HTapN << 4) + VTapN)))
         return RetVal;

    /*---------------------------------------------------------------
    -set aux scaler for loopback channel or total input pixel number(new register)-
    ----------------------------------------------------------------*/
    switch(UnitNum){
        case VPP_FRC_SCL_BE:
            /*set aux scaler for loopback channel*/
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_SYNC_CTRL, VTapN - 1)))
                return RetVal;
            break;

	default:
	    break;
    }

    /*------------------------------------
    -set initial phase for DDA, always progressive-
    -------------------------------------*/
    InitPh = 128 * (HTapN % 2);

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_HINITPH << 2), InitPh)))
         return RetVal;

    InitPh = 128 * (VTapN % 2);

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_VINITPH_EVEN << 2), InitPh)))
         return RetVal;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_VINITPH_ODD << 2), InitPh)))
         return RetVal;

    /*----------------------
    -set line size (new rigister)-
    -----------------------*/
    if(VPP_SCL_HSCALE_BEFORE == HSclPos)
         LineSize = pIORes->OHRes;
    else
         LineSize = pIORes->IHRes;

    if(Bit24or16)
	  LineSize = (LineSize + 5) / 6;
    else
	  LineSize = (LineSize + 8) / 9;

    if (UnitNum == VPP_FRC_SCL_BE)
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + BA_Vpp_AUX_LSIZE_lsize, LineSize);
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    else if (UnitNum == VPP_FRC_SCL_GFX2)
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_MOSD_LSIZE, LineSize);
#endif
    else if (UnitNum != VPP_FRC_SCL_DETAIL)
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + BA_Vpp_MAIN_LSIZE_lsize + UnitNum * 4, LineSize);

    /*load non linear scaler parameter*/
    if(1 == pSclCtrl->NLEn)
	 FRC_SCL_SetNLParams(vpp_obj, UnitNum, pIORes, pSclCtrl->CenterFrac);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    if(VPP_FRC_SCL_DETAIL == UnitNum){
        /*H scaler always uses table 2*/
        RegVal = 1 + (VTableSel << 4);
        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_COEFF_CTRL << 2), RegVal)))
            return RetVal;
    }else{
#endif
        /*load HV filter coefficiets*/
        if (pSclCtrl->DynamicLoad)
            FRC_SCL_SetSclCoeff(vpp_obj, UnitNum, pIORes, pSclCtrl);
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    }
#endif
    return RetVal;
}

int FRC_SCL_SetSclCoeff(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_SCL_RES pIORes, PVPP_SCL_CTRL pSclCtrl)
{
    int tempHorSclCoeffMode,tempVerSclCoeffMode;
    unsigned int Ratio;

    PLANE *plane;

    CHECK_FRC_SCL_NUM(UnitNum);

    if (UnitNum == VPP_FRC_SCL_MAIN)
        plane = &vpp_obj->plane[PLANE_MAIN];
    else if (UnitNum == VPP_FRC_SCL_PIP)
        plane = &vpp_obj->plane[PLANE_PIP];
    else if (UnitNum == VPP_FRC_SCL_OSD)
        plane = &vpp_obj->plane[PLANE_GFX0];
    else if (UnitNum == VPP_FRC_SCL_PG)
        plane = &vpp_obj->plane[PLANE_PG];
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
    else if (UnitNum == VPP_FRC_SCL_GFX2)
        plane = &vpp_obj->plane[PLANE_GFX2];
#endif
    else if (UnitNum == VPP_FRC_SCL_BE)
        plane = &vpp_obj->plane[PLANE_AUX];

        {
            if(NULL != pIORes){
                /* horizontal scaling ratio */
                Ratio = (pIORes->IHRes  << 10) / pIORes->OHRes;
                if (Ratio < 1024)   // For Ratio < 1
                    tempHorSclCoeffMode = COEFF_H_PSHARP;
                else if(Ratio == 1024)    // For Ratio = 1
                    tempHorSclCoeffMode = COEFF_H_BYPASS;
                else if(Ratio > 1024  &&  Ratio < 2202)    // For Ratio = 1.5
                    tempHorSclCoeffMode = COEFF_HRED_BY_1_5;
                else if(Ratio >= 2202 && Ratio < 3584)    // For Ratio = 2.7
                    tempHorSclCoeffMode = COEFF_HRED_BY_2_7;
                else
                    tempHorSclCoeffMode = COEFF_H_PSHARP;
            }else{
                tempHorSclCoeffMode = -1;
            }
            printk("Galois : HorSclCoeffMode: %i\n", tempHorSclCoeffMode);
        }

        {
            if(NULL != pIORes){
                /* vertical scaling ratio */
                Ratio = (pIORes->IVRes << 10) / pIORes->OVRes;
                if(Ratio == 1024 )    // For Ratio = 1
                    tempVerSclCoeffMode = COEFF_V_BYPASS;
                else if (pSclCtrl->VTapNum == 5)
                    tempVerSclCoeffMode = COEFF_VRED_BY_1_5_5taps;
                else if (pSclCtrl->VTapNum == 3)
                    tempVerSclCoeffMode = COEFF_VRED_BY_1_5_3taps;
                else if(Ratio < 1024)    // For Ratio < 1
                    tempVerSclCoeffMode = COEFF_V_PSHARP;
                else if(Ratio > 1024  &&  Ratio < 2176)    // For Ratio = 1.5
                    tempVerSclCoeffMode = COEFF_VRED_BY_1_5;
                else if(Ratio >= 2176 && Ratio < 2816)    // For Ratio = 2.25
                    tempVerSclCoeffMode = COEFF_VRED_BY_2_25;
                else
                    tempVerSclCoeffMode = COEFF_V_PSHARP;
            }else{
                tempVerSclCoeffMode = -1;
            }
            printk("Galois : VerSclCoeffMode: %i\n", tempVerSclCoeffMode);
        }

    if(-1 != tempHorSclCoeffMode) {
        Generate_Scl_Coefficiena(vpp_obj, UnitNum, 0, m_scl_coeff_table[tempHorSclCoeffMode].format, m_scl_coeff_table[tempHorSclCoeffMode].coeff);
    }

    if(-1 != tempVerSclCoeffMode) {
        Generate_Scl_Coefficiena(vpp_obj, UnitNum, 1, m_scl_coeff_table[tempVerSclCoeffMode].format, m_scl_coeff_table[tempVerSclCoeffMode].coeff);
    }

    return MV_THINVPP_OK;
}

/***************************************************************************************
 * FUNCTION: set non linear scaler parameters
 * PARAMS: UnitNum - unit number(0, 1, 2, 3, 4, 5)
 *               pIORes -pointer to I&O resolution
 *               CenterFrac - central undistorted franction of output frame
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetNLParams(THINVPP_OBJ *vpp_obj, int UnitNum, PVPP_SCL_RES pIORes, unsigned char CenterFrac)
{
    unsigned int RegAddr;
    int Ihres, Ivres, Ohres, Ovres;
    unsigned int Center;
    unsigned int Temp1, Temp2;
    unsigned int MaxCenterFrac;
    unsigned int tail_ores, scl_nlcres, c_ratio, c_ires, tail_ires, nl_inc_ratio, nl_init_ratio;
    unsigned int Lowbyte, Highbits;

    int RetVal = MV_THINVPP_OK;

    CHECK_FRC_SCL_NUM(UnitNum);

    /*get register start address of the FRC_SCL unit */
    RegAddr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, UnitNum);

    /*input  center validation*/
    Ihres = pIORes->IHRes;
    Ivres = pIORes->IVRes;
    Ohres = pIORes->OHRes;
    Ovres = pIORes->OVRes;

    Center = CenterFrac;

    Temp1 = Ihres * Ovres;
    Temp2 = Ivres * Ohres;

    if(Temp1 < Temp2)
        MaxCenterFrac = ((Temp1 * VPP_SCL_MAX_EXP << 9) / Temp2 - (VPP_SCL_MAX_EXP  << 8) - 256) / (VPP_SCL_MAX_EXP -1);
    else
        MaxCenterFrac = ( (VPP_SCL_MAX_RED << 8) + 256 - (Temp1 << 9) / Temp2) / (VPP_SCL_MAX_RED - 1);

    if(Center > MaxCenterFrac)
        Center = MaxCenterFrac;

    /*minimum tail length limitation*/
    tail_ores = ((256 - Center) * Ohres) >> 9 ;

    if(tail_ores < 5){
        tail_ores = 5;
        Center = 256 - (tail_ores << 9) / Ohres;
    }

    /*Calculation of scl_nlcres*/
    scl_nlcres = Ohres - ( tail_ores << 1);

    c_ratio = Ivres; //perform c_ratio = (Ivres << 20) / Ovres;
    c_ratio <<= 20;
    c_ratio = c_ratio / Ovres;
    c_ires = (c_ratio * scl_nlcres) >> 20;
    tail_ires = ((Ihres - c_ires) >> 1);
    nl_inc_ratio = ((c_ratio - (tail_ires << 20) / tail_ores) << 1) / (tail_ores + 1);
    nl_init_ratio = c_ratio - (nl_inc_ratio) * tail_ores;

    //Validation of nl_inc_ratio and nl_init_ratio values
    //Calculated nl_inc_ratio and nl_init_ratio values needs to be validated against the boundary conditions and
    //corrected if required.
    if(nl_init_ratio <= 0)
    {
        nl_init_ratio = 0;
        nl_inc_ratio = (tail_ires << 21) / (tail_ores * (tail_ores - 1));
    }
    else if(nl_init_ratio >= 15728640)      //2^20 * 15
    {
        nl_init_ratio = 15728640;
        nl_inc_ratio = ((tail_ires << 21) / tail_ores -  nl_init_ratio) / (tail_ores - 1);
    }
    /*set init ratio*/
    Lowbyte = GET_LOWEST_BYTE(nl_init_ratio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_INIT_RATIO_0 << 2), Lowbyte)))
         return RetVal;

    Highbits = GET_SECOND_BYTE(nl_init_ratio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_INIT_RATIO_1 << 2), Highbits)))
         return RetVal;

    Highbits = GET_THIRD_BYTE(nl_init_ratio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_INIT_RATIO_2 << 2), Highbits)))
         return RetVal;

    /*set increment ratio*/
    Lowbyte = GET_LOWEST_BYTE(nl_inc_ratio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_INC_RATIO_0 << 2), Lowbyte)))
         return RetVal;

    Highbits = GET_SECOND_BYTE(nl_inc_ratio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_INC_RATIO_1 << 2), Highbits)))
         return RetVal;

    Highbits = GET_THIRD_BYTE(nl_inc_ratio);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_INC_RATIO_2 << 2), Highbits)))
         return RetVal;

    /*set center*/
    Lowbyte = GET_LOWEST_BYTE(scl_nlcres);
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_NLCRES_0 << 2), Lowbyte)))
         return RetVal;

    Highbits = scl_nlcres >> 8;
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_NLCRES_1 << 2), Highbits)))
         return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: load the default register values to SCL back end switch
 * PARAMS: void
 * RETURN:  1 - succeed
 *                others - failed to load CPCB EE default values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_LoadSwDefault(THINVPP_OBJ *vpp_obj)
{
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)

    WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_CPCB0_PL_EN, gFrcSclBeSwDefValues);
    WRITE_FRC_SCL_DEFAULT_VAL_32BITS(RA_Vpp_CPCB1_PL_EN, gFrcSclBeSwDefValues);

    vpp_obj->scl.VppFrcSclBeSwitch0 = gFrcSclBeSwDefValues.VPP_RA_Vpp_CPCB0_PL_EN;
    vpp_obj->scl.VppFrcSclBeSwitch1 = gFrcSclBeSwDefValues.VPP_RA_Vpp_CPCB1_PL_EN;

#else

    WRITE_REG_DEFAULT_VAL(FRC_BE_SW_L, gFrcSclBeSwDefValues);
    WRITE_REG_DEFAULT_VAL(FRC_BE_SW_H, gFrcSclBeSwDefValues);
    WRITE_REG_DEFAULT_VAL(FRC_BE_SW1_L, gFrcSclBeSwDefValues);
    WRITE_REG_DEFAULT_VAL(FRC_BE_SW1_H, gFrcSclBeSwDefValues);
    WRITE_REG_DEFAULT_VAL(FRC_BE_SW2, gFrcSclBeSwDefValues);

    vpp_obj->scl.VppFrcSclBeSwitch = gFrcSclBeSwDefValues.VPP_FRC_BE_SW1_L;

#endif
    return (MV_THINVPP_OK);
}

/***************************************************************************************
 * FUNCTION: set scaler to CPCB path route
 * PARAMS: chanID - FE data channel
 *               BESwitch - CPCB unit and path selection
 * RETURN:  1 - succeed
 *                others - failed to load CPCB BE switch values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetBeSwitch(THINVPP_OBJ *vpp_obj, int chanID, int BESwitch)
{
    int RetVal = MV_THINVPP_OK;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)

    switch(chanID){
        case CHAN_MAIN:
            if (BESwitch == CPCB_1) { // main -> CPCB-1
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.main = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.main = 0;
            } else if (BESwitch == CPCB_2){ // main -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.main = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.main = 1;
            } else { // main -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.main = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.main = 0;
            }
            break;
        case CHAN_PIP:
            if (BESwitch == CPCB_1) { // pip -> CPCB-1
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.pip = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.pip = 0;
            } else if (BESwitch == CPCB_2){ // pip -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.pip = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.pip = 1;
            } else { // pip -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.pip = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.pip = 0;
            }
            break;
        case CHAN_GFX0:
            if (BESwitch == CPCB_1) { // GFX0 -> CPCB-1
                printk("Setting BESwitch: GFX0 -> CPCB-1\n");
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.ig = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.ig = 0;
            } else if (BESwitch == CPCB_2){ // GFX0 -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.ig = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.ig = 1;
            } else { // GFX0 -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.ig = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.ig = 0;
            }
            break;
        case CHAN_PG:
            if (BESwitch == CPCB_1) { // PG -> CPCB-1
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.pg = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.pg = 0;
            } else if (BESwitch == CPCB_2){ // PG -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.pg = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.pg = 1;
            } else { // PG -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.pg = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.pg = 0;
            }
            break;
        case CHAN_GFX1:
            if (BESwitch == CPCB_1) { // GFX1 -> CPCB-1
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.cursor = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.cursor = 0;
            } else if (BESwitch == CPCB_2){ // GFX1 -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.cursor = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.cursor = 1;
            } else { // GFX1 -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.cursor = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.cursor = 0;
            }
            break;
        case CHAN_GFX2:
            if (BESwitch == CPCB_1) { // GFX2 -> CPCB-1
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.mosd = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.mosd = 0;
            } else if (BESwitch == CPCB_2){ // GFX2 -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.mosd = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.mosd = 1;
            } else { // GFX2 -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.mosd = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.mosd = 0;
            }
            break;
        case CHAN_BG:
            if (BESwitch == CPCB_1) { // BG -> CPCB-1
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.bg = 1;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.bg = 0;
            } else if (BESwitch == CPCB_2){ // BG -> CPCB-2
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.bg = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.bg = 1;
            } else { // BG -> no connection
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch0)))->field.bg = 0;
                ((CPCB_PL_EN *)(&(vpp_obj->scl.VppFrcSclBeSwitch1)))->field.bg = 0;
            }
            break;
    }

    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_CPCB0_PL_EN, vpp_obj->scl.VppFrcSclBeSwitch0);
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_CPCB1_PL_EN, vpp_obj->scl.VppFrcSclBeSwitch1);

#else

    if(BESwitch >= VPP_SCL_BE_SWITCH_MAX ||BESwitch < VPP_SCL_BE_CPCB0_PATH0)
        return MV_THINVPP_EBADPARAM;

    switch(chanID){

        case CHAN_MAIN:
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (FRC_BE_SW_L << 2), 0xf0|BESwitch)))
                return RetVal;
            break;

        case CHAN_PIP:
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (FRC_BE_SW_H << 2), 0xf0|BESwitch)))
                return RetVal;
            break;

        case CHAN_OSD:
            /*set OSD switch field to local buffer*/
            ((VPP_FRC_FRC_BE_SW1_L *)(&(vpp_obj->scl.VppFrcSclBeSwitch)))->field.OsdSwitch = BESwitch;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (FRC_BE_SW1_L << 2), vpp_obj->scl.VppFrcSclBeSwitch)))
                return RetVal;
            break;

        case CHAN_BG:
            /*set BG switch field to local buffer*/
            ((VPP_FRC_FRC_BE_SW1_L *)(&(vpp_obj->scl.VppFrcSclBeSwitch)))->field.BgSwitch = BESwitch;
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (FRC_BE_SW1_L << 2), vpp_obj->scl.VppFrcSclBeSwitch)))
                return RetVal;
            break;

        case CHAN_PG:
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (FRC_BE_SW1_H << 2), 0xf0|BESwitch)))
                return RetVal;
            break;

        case CHAN_AUX:
            if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (FRC_BE_SW2 << 2), 0xf0|BESwitch)))
                return RetVal;
            break;
    }

#endif

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set BE FIFO for loopback
 * PARAMS: pCpcb0Tot - CPCB0 output total resolution
 *               pCpcb0Res - CPCB0 active resolution
 * RETURN:  1 - succeed
 *                others - failed to load CPCB BE FIFO values to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetBeFifo(THINVPP_OBJ *vpp_obj, PVPP_FRC_RES pCpcb0Tot, PVPP_FRC_RES pCpcb0Res)
{
    unsigned int RegVal;
    int RetVal = MV_THINVPP_OK;

    RegVal = (pCpcb0Tot->HRes - pCpcb0Res->HRes) >> 1;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_LRST, RegVal)))
        return RetVal;

    RegVal = pCpcb0Tot->VRes - pCpcb0Res->VRes - 1;

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_FE_BE + RA_FE_BE_FRST, RegVal)))
        return RetVal;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set main or PIP scaler working mode
 * PARAMS: UnitNum - unit number(0, 1)
 *               WorkMode -1: off-line mode 0: in-line mode
 * RETURN:  1 - succeed
 *                others - failed to load register to BCM buffer
 ***************************************************************************************/
int FRC_SCL_SetWorkMode(THINVPP_OBJ *vpp_obj, int UnitNum, int WorkMode)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    if((UnitNum != VPP_FRC_SCL_MAIN) && (UnitNum != VPP_FRC_SCL_PIP) && (UnitNum != VPP_FRC_SCL_DETAIL))
        return MV_THINVPP_EBADPARAM;

    /*get register start address of the FRC_SCL unit */
    RegAddr = INTERNAL_FRC_SCL_GetRegStartAddr(vpp_obj, UnitNum);

    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + (SCL_STALL << 2), (WorkMode<<7))))
        return RetVal;

    if ((UnitNum == VPP_FRC_SCL_MAIN) || (UnitNum == VPP_FRC_SCL_PIP))
        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + RA_Vpp_main_ols + (UnitNum << 2), WorkMode)))
            return RetVal;

    return RetVal;
}

#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
/***************************************************************************************
 * FUNCTION: control Hscaler chopping
 * PARAMS: UnitNum - unit number(0, 1)
 *         Value - 0, 1, 2, 3
 * RETURN:  1 - succeed
 *                others - failed to load register to BCM buffer
 ***************************************************************************************/
int FRC_SCL_ChopCtrl(THINVPP_OBJ *vpp_obj, int UnitNum, int Value)
{
    if((UnitNum != VPP_FRC_SCL_MAIN) && (UnitNum != VPP_FRC_SCL_PIP))
        return MV_THINVPP_EBADPARAM;

    /*get register start address of the FRC_SCL unit */
    if (UnitNum == VPP_FRC_SCL_MAIN)
        VPP_REG_WRITE32(RA_Vpp_MAIN_SCL_CROP, Value);
    else
        VPP_REG_WRITE32(RA_Vpp_PIP_SCL_CROP, Value);

    return (MV_THINVPP_OK);
}
#endif
