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

#ifndef _VPP_CPCB_FGG_PRV_H_
#define _VPP_CPCB_FGG_PRV_H_

/**********************************************************************
*macro for CPCB register offset calculation                                                             *
***********************************************************************/

/*register number in FGG, put CPCB0 MISC register to FGG block*/
#define CPCB_FGG_REG_NUM (8)

/*CPCB FGG base address*/
#define CPCB0_FGG_REG_BASE CPCB0_FGG_CTRL

/*calculate the CPCB FGG register offset*/
#define GET_FGG_OFF(RegName)  ((RegName) - CPCB0_FGG_REG_BASE)

/*get hardware address by register name*/
#define GET_FGG_ADDR(RegName)  (vpp_obj->base_addr +( ((CPCB0_FGG_REG_BASE + (OFF_##RegName)) << 2)))

/**********************************************************************
*register offset definitions in local block buffer and register map                               *
***********************************************************************/

#define OFF_VPP_CPCB0_FGG_CTRL     GET_FGG_OFF(CPCB0_FGG_CTRL)
#define OFF_VPP_CPCB0_FGG_GAIN    GET_FGG_OFF(CPCB0_FGG_GAIN)
#define OFF_VPP_CPCB0_FGG_TEMP    GET_FGG_OFF(CPCB0_FGG_TEMP)
#define OFF_VPP_CPCB0_FGG_LTH_L   GET_FGG_OFF(CPCB0_FGG_LTH_L)
#define OFF_VPP_CPCB0_FGG_LTH_H   GET_FGG_OFF(CPCB0_FGG_LTH_H)
#define OFF_VPP_CPCB0_FGG_HTH_L   GET_FGG_OFF(CPCB0_FGG_HTH_L)
#define OFF_VPP_CPCB0_FGG_HTH_H   GET_FGG_OFF(CPCB0_FGG_HTH_H)
#define OFF_VPP_CPCB0_MISC_CTRL     GET_FGG_OFF(CPCB0_INT_CTRL) /*the offset in local buffer*/

#if 0
/**********************************************************************
*default register value                                                                                          *
***********************************************************************/
/*CPCB FGG register structure*/
typedef struct VPP_CPCB0_FGG_T{
    unsigned int VPP_CPCB0_FGG_CTRL;
    unsigned int VPP_CPCB0_FGG_GAIN;
    unsigned int VPP_CPCB0_FGG_TEMP;
    unsigned int VPP_CPCB0_FGG_LTH_L;
    unsigned int VPP_CPCB0_FGG_LTH_H;
    unsigned int VPP_CPCB0_FGG_HTH_L;
    unsigned int VPP_CPCB0_FGG_HTH_H;
    unsigned int VPP_CPCB0_MISC_CTRL;

}VPP_CPCB0_FGG, * PVPP_CPCB0_FGG;

/*CPCB FGG register default values*/
const VPP_CPCB0_FGG gCpcb0FggDefValues = {
    .VPP_CPCB0_FGG_CTRL        = 0x00000000,// default disable FGG for both Main & PIP
    .VPP_CPCB0_FGG_GAIN        = 0x00000020,
    .VPP_CPCB0_FGG_TEMP        = 0x00000000,
    .VPP_CPCB0_FGG_LTH_L       = 0x00000000,
    .VPP_CPCB0_FGG_LTH_H       = 0x00000000,
    .VPP_CPCB0_FGG_HTH_L       = 0x000000FF,
    .VPP_CPCB0_FGG_HTH_H       = 0x0000000F,
    .VPP_CPCB0_MISC_CTRL       = 0x00000000
};
#endif
#endif
