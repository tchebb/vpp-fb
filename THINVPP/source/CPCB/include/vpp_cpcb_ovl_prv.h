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

#ifndef _VPP_CPCB_OVL_PRV_H_
#define _VPP_CPCB_OVL_PRV_H_

/**********************************************************************
*macro for CPCB video overlay and OSD overlay                                                   *
***********************************************************************/

/*CPCB VOL unit number validation*/
#define CHECK_OVL_NUM(UnitNum)\
do{\
    if((UnitNum < VPP_CPCB_OVL0) ||(UnitNum >= VPP_CPCB_OVL_MAX))\
        return MV_THINVPP_EBADPARAM;\
}while(0)

/**********************************************************************
*default register value                                                                                          *
***********************************************************************/
/*CPCB OVL register structure*/
typedef struct VPP_CPCB0_OVL_T{
    unsigned int VPP_CPCB0_VO_BASE_CLR_0;
    unsigned int VPP_CPCB0_VO_BASE_CLR_1;
    unsigned int VPP_CPCB0_VO_BASE_CLR_2;
    unsigned int VPP_CPCB0_OO_FIX_0;
    unsigned int VPP_CPCB0_OO_FIX_1;
    unsigned int VPP_CPCB0_OO_FIX_2;
    unsigned int VPP_CPCB0_OO_FIX0_0;
    unsigned int VPP_CPCB0_OO_FIX0_1;
    unsigned int VPP_CPCB0_OO_FIX0_2;
}VPP_CPCB0_OVL, *PVPP_CPCB0_OVL;

typedef struct VPP_CPCB2_OVL_T{
    unsigned int VPP_CPCB2_OO_FIX_0;
    unsigned int VPP_CPCB2_OO_FIX_1;
    unsigned int VPP_CPCB2_OO_FIX_2;
    unsigned int VPP_CPCB2_OO_FIX0_0;
    unsigned int VPP_CPCB2_OO_FIX0_1;
    unsigned int VPP_CPCB2_OO_FIX0_2;
}VPP_CPCB2_OVL, * PVPP_CPCB2_OVL;

/*CPCB OVL register default values*/
const VPP_CPCB0_OVL gCpcb0OvlDefValues = {
    .VPP_CPCB0_VO_BASE_CLR_0    = 0x00000000,
    .VPP_CPCB0_VO_BASE_CLR_1    = 0x00000000,
    .VPP_CPCB0_VO_BASE_CLR_2    = 0x00000000,
    .VPP_CPCB0_OO_FIX_0         = 0x00000080,
    .VPP_CPCB0_OO_FIX_1         = 0x00000010,
    .VPP_CPCB0_OO_FIX_2         = 0x00000080,
    .VPP_CPCB0_OO_FIX0_0        = 0x00000080,
    .VPP_CPCB0_OO_FIX0_1        = 0x00000010,
    .VPP_CPCB0_OO_FIX0_2        = 0x00000080,
};

const VPP_CPCB2_OVL gCpcb2OvlDefValues = {
    .VPP_CPCB2_OO_FIX_0         = 0x00000080,
    .VPP_CPCB2_OO_FIX_1         = 0x00000010,
    .VPP_CPCB2_OO_FIX_2         = 0x00000080,
    .VPP_CPCB2_OO_FIX0_0        = 0x00000080,
    .VPP_CPCB2_OO_FIX0_1        = 0x00000010,
    .VPP_CPCB2_OO_FIX0_2        = 0x00000080,
};

#endif
