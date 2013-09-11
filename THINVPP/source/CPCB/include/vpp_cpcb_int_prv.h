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

#ifndef _VPP_CPCB_INT_PRV_H_
#define _VPP_CPCB_INT_PRV_H_

/**********************************************************************
*macro definitions for interlacer                                                                            *
***********************************************************************/

/*register number in an INT unit*/
#define CPCB_INT_REG_NUM 26

/*get local buffer offset by register name*/
#define GET_CPCB_INT_OFF(RegName) (OFF_##RegName)

/**********************************************************************
*bit field definition for CPCB INT                                                                            *
***********************************************************************/

/*INT Control Register Bit Fields */
typedef union CPCB_INT_CTRL_T
{
    struct {
        unsigned int Enable               : 1;
        unsigned int Mode                 : 2;
        unsigned int FieldPol             : 1;
        unsigned int BitMode             : 1;
        unsigned int Reserved           :27;
    } field;

    unsigned int data;
} CPCB_INT_CTRL;

/*INT Memory Size Register Bit Fields */
typedef union CPCB_INT_MEMSIZE_L_T
{
    struct {
        unsigned int MemSizeL          : 8;
        unsigned int Reserved           :24;
    } field;

    unsigned int data;
} CPCB_INT_MEMSIZE_L;

typedef union CPCB_INT_MEMSIZE_H_T
{
    struct {
        unsigned int MemSizeH          : 4;
        unsigned int Reserved           :28;
    } field;

    unsigned int data;
} CPCB_INT_MEMSIZE_H;

/*INT Weighting Factor Register Bit Fields */
typedef union CPCB_INT_WF_L_T
{
    struct {
        unsigned int WFactorL           : 8;
        unsigned int Reserved           :24;
    } field;

    unsigned int data;
} CPCB_INT_WF_L;

typedef union CPCB_INT_WF_H_T
{
    struct {
        unsigned int WFactorH          : 1;
        unsigned int Reserved           :31;
    } field;

    unsigned int data;
} CPCB_INT_WF_H;

/*INT 12-bit Register Bit Fields */
typedef union CPCB_INT_12BITS_L_T
{
    struct {
        unsigned int LowByte             : 8;
        unsigned int Reserved           :24;
    } field;

    unsigned int data;
} CPCB_INT_12BITS_L;

typedef union CPCB_INT_12BITS_H_T
{
    struct {
        unsigned int High4Bits           : 4;
        unsigned int Reserved           :28;
    } field;

    unsigned int data;
} CPCB_INT_12BITS_H;

/**********************************************************************
*register offset definitions in local block buffer                                                        *
***********************************************************************/
#define  OFF_CPCB_INT_CTRL       0x00
#define  OFF_CPCB_INT_MEMSIZE_L  0x08
#define  OFF_CPCB_INT_WF_L       0x10
#define  OFF_CPCB_INT_FX_L       0x18

/**********************************************************************
*default register values of VPP CPCB INT block                                                      *
***********************************************************************/
/*CPCB INT register structure*/
typedef struct VPP_CPCB0_INT_T{
    unsigned int VPP_RA_Vpp_CPCB0_FLD;
}VPP_CPCB0_INT, *PVPP_CPCB0_INT;

typedef struct VPP_CPCB2_INT_T{
    unsigned int VPP_RA_Vpp_CPCB2_FLD;
}VPP_CPCB2_INT, *PVPP_CPCB2_INT;

/*CPCB INT register default values*/
const VPP_CPCB0_INT gCpcb0IntDefValues = {
    .VPP_RA_Vpp_CPCB0_FLD      = 0x0000000a
};

const VPP_CPCB2_INT gCpcb2IntDefValues = {
    .VPP_RA_Vpp_CPCB2_FLD      = 0x0000000a
};

#endif
