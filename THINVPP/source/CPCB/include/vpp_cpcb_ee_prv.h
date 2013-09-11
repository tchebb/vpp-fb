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

#ifndef _VPP_CPCB_EE_PRV_H_
#define _VPP_CPCB_EE_PRV_H_

/**********************************************************************
*macro definitions for edge enhancer                                                                     *
***********************************************************************/

/*register number in an EE unit*/
#define CPCB_EE_REG_NUM (CPCB0_EE0_CTIGAIN - CPCB0_EE0_CTRL + 1)

/*CPCB EE base address*/
#define CPCB0_EE0_REG_BASE CPCB0_EE0_CTRL
#define CPCB0_EE1_REG_BASE CPCB0_EE1_CTRL

// Macros for DETAIL_LUT
#define FE_DET_MIN_LUT 0x00
#define FE_DET_MAX_LUT 0x0F

/*get hardware address by register name*/
#define GET_CPCB_EE_ADDR(RegName, UnitNum)  (INTERNAL_EE_GetRegStartAddr(vpp_obj, UnitNum) + ((OFF_##RegName) << 2))

/*CPCB EE unit number validation*/
#define CHECK_EE_NUM(UnitNum)\
do{\
    if((UnitNum < VPP_CPCB_EE0) ||(UnitNum >= VPP_CPCB_EE_MAX))\
        return MV_THINVPP_EBADPARAM;\
}while(0)

/**********************************************************************
*default register value                                                                                          *
***********************************************************************/
/*CPCB-0 EE register structure*/
typedef struct VPP_CPCB0_EE_T{
    unsigned int VPP_CPCB0_EE0_CTRL;
    unsigned int VPP_CPCB0_EE1_CTRL;
}VPP_CPCB0_EE, *PVPP_CPCB0_EE;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/*FE detail EE register structure*/
typedef struct VPP_FE_DET_T{
    unsigned int VPP_DET_CTRL;
}VPP_FE_DET, *PVPP_FE_DET;

#endif

/*CPCB-0 EE register default values*/
const VPP_CPCB0_EE gCpcb0EeDefValues = {
    .VPP_CPCB0_EE0_CTRL          = 0x00000001,//default enable upsampler in EE0
    .VPP_CPCB0_EE1_CTRL          = 0x00000001,//default enable upsampler in EE1
};

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/*FE detail EE register default values*/
const VPP_FE_DET gFeDetDefValues = {
    .VPP_DET_CTRL    = /*0x00000053*/0x00000000,
};

#endif

#endif/*_VPP_CPCB_EE_PRV_H_*/
