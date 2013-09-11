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

#ifndef _VPP_CPCB_TG_PRV_H_
#define _VPP_CPCB_TG_PRV_H_

/**********************************************************************
*macro for CPCB timing generator                                                                         *
***********************************************************************/

/*CPCB unit number validation*/
#define CHECK_CPCB_NUM(UnitNum)\
do{\
    if((UnitNum < VPP_CPCB0) || (UnitNum >= VPP_CPCB_MAX))\
        return MV_THINVPP_EBADPARAM;\
}while(0)

/**********************************************************************
*bit field definition for CPCB INT                                                                            *
***********************************************************************/

/*CPCB clock control Register Bit Fields */
typedef union VPP_CPCB_CLK_CTRL_T
{
    struct {
        unsigned int ClkSwitch               : 1;
        unsigned int ClkD3Switch           : 1;
        unsigned int ClkEn                      : 1;
        unsigned int ClkSel                    : 3;
        unsigned int Reserved              :26;
    } field;

    unsigned int data;
} VPP_CPCB_CLK_CTRL;

/**********************************************************************
*default register value                                                                                          *
***********************************************************************/
/*CPCB TG register structure*/
typedef struct VPP_CPCB0_TG_T{
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    unsigned int VPP_CPCB0_DB_CTRL;
#endif
    unsigned int VPP_CPCB0_MODE;
    unsigned int VPP_RA_Vpp_cpcb0Clk;

} VPP_CPCB0_TG, *PVPP_CPCB0_TG;

typedef struct VPP_CPCB2_TG_T{
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    unsigned int VPP_CPCB2_DB_CTRL;
#endif
    unsigned int VPP_CPCB2_MODE;
    unsigned int VPP_RA_Vpp_cpcb2Clk;

} VPP_CPCB2_TG, *PVPP_CPCB2_TG;


/*CPCB TG register default values*/
const VPP_CPCB0_TG gCpcb0TgDefValues = {
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    .VPP_CPCB0_DB_CTRL      = 0x00000000,
#endif
    .VPP_CPCB0_MODE         = 0x00000000, //default to free-run mode
    .VPP_RA_Vpp_cpcb0Clk    = 0x0000000D
};


const VPP_CPCB2_TG gCpcb2TgDefValues = {
#if !((BERLIN_CHIP_VERSION >= BERLIN_B_0))
    .VPP_CPCB2_DB_CTRL       = 0x00000000,
#endif
    .VPP_CPCB2_MODE          = 0x00000000, //default to free-run mode
    .VPP_RA_Vpp_cpcb2Clk     = 0x0000000D
};

#endif
