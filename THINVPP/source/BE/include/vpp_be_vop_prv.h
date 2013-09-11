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

#ifndef _VPP_BE_VOP_PRV_H_
#define _VPP_BE_VOP_PRV_H_

/**********************************************************************
*macro definitions for backend VOP                                                                       *
***********************************************************************/
/*register number in a CSC block, include coeffs and offsets*/
#define VPP_VOP_CSC_REG_NUM          32

/*CSC coeff index*/
#define VPP_VOP_CSC_MAX_COEFF_INDEX  9

/*CSC offset index*/
#define VPP_VOP_CSC_MAX_OFFSET_INDEX 3

  /**********************************************************************
*VOP Coefficients and Offsets for AHD/ASD/HDMI/TTL24/TTL30 Channel CSC           *
***********************************************************************/
const unsigned short VppVopCscCoeff[VPP_VOP_CSC_MAX_MODES][VPP_VOP_CSC_MAX_COEFF_INDEX] = {
    /*  C0       C1      C2      C3      C4      C5      C6      C7      C8   */
    {   0x200,  0,      0,      0,      0x200,  0,      0,      0,      0x200 }, //Bypass Mode
    {   0x20A,  0,      0x3B,   0x203B, 0x200,  0x206A, 0x26,   0,      0x20D }, //601->709
    {   0x1FB,  0,      0x2039, 0x33,   0x200,  0x62,   0x2025, 0,      0x1F7 }, //709->601
    {   0x106,  0x20CA, 0x203C, 0x25,   0x16E,  0x6D,   0x2018, 0x20EE, 0x106 }, //RGB->YUV(709)
    {   0x3A2,  0x200,  0,      0x205E, 0x200,  0x20EB, 0,      0x200,  0x314 }, //YUV(709)->RGB
    {   0x106,  0x20AE, 0x2058, 0x3A,   0x12D,  0x99,   0x202A, 0x20DB, 0x106 }, //RGB->YUV(601)
    {   0x377,  0x200,  0,      0x20AC, 0x200,  0x2165, 0,      0x200,  0x2BE },  //YUV(601)->RGB
    {   0x0E1,  0x20AD, 0x2034, 0x20,   0x13A,  0x5D,   0x2015, 0x20CC, 0x0E1 }, //sRGB->YUV(709)
    {   0x439,  0x254,  0,      0x206D, 0x254,  0x2111, 0,      0x254,  0x396 },  //YUV(709)->sRGB
    {   0x0E1,  0x2095, 0x204C, 0x32,   0x102,  0x84,   0x2025, 0x20BC, 0x0E1 }, //sRGB->YUV(601)
    {   0x408,  0x254,  0,      0x20C9, 0x254,  0x21A0, 0,      0x254,  0x331 },  //YUV(601)->sRGB
    {   0,  0,      0x200,      0,      0x200,  0,      0x200,      0,      0 }, // U <-> V swap mode
};

const unsigned int VppVopCscOffset[VPP_VOP_CSC_MAX_MODES][VPP_VOP_CSC_MAX_OFFSET_INDEX] = {
    /* A0       A1          A2      */
    { 0,        0,          0       }, //Bypass Mode
    { 0x2110F,  0x2968,     0x20CD9 }, //601->709
    { 0x0F76,   0x22540,    0x0B66  }, //709->601
    { 0x8000,   0,          0x8000  }, //RGB->YUV(709)
    { 0x2E84F,  0x5228,     0x2C542 }, //YUV(709)->RGB
    { 0x8000,   0,          0x8000  }, //RGB->YUV(601)
    { 0x2DDB2,  0x8478,     0x2AF8A }, //YUV(601)->RGB
    { 0x8000,   0x1000,     0x8000  }, //sRGB->YUV(709)
    { 0x321F3,  0x4D37,     0x2F8DA }, //YUV(709)->sRGB
    { 0x8000,   0x1000,     0x8000  }, //sRGB->YUV(601)
    { 0x31591,  0x8864,     0x2DFA4 }, //YUV(601)->sRGB
    { 0,        0,          0       }, //U <-> V swap Mode
};

/**********************************************************************
*bit field definition for VOP block                                                                            *
***********************************************************************/
typedef union VPP_VOP_CLK_POL_T
{
    struct {
        unsigned int Ttl30ClkPol                 : 1;
        unsigned int Ttl24ClkPol                 : 1;
        unsigned int reserved                    :30;
    } field;

    unsigned int data;
} VPP_VOP_CLK_POL;

/**********************************************************************
*bit field definition for HDMI fomater control                                                                        *
***********************************************************************/
#if !(BERLIN_CHIP_VERSION >= BERLIN_BG2)
typedef union VPP_VOP_HDMI_FRMT_CTRL_T
{
    struct {
        unsigned int Enable                   : 1;
        unsigned int Mode                     : 1;
        unsigned int Load                     : 1;
        unsigned int ViewID                   : 1;
        unsigned int Polarity                 : 1;
        unsigned int reserved                 :27;
    } field;

    unsigned int data;
} VPP_VOP_HDMI_FRMT_CTRL;

#else
typedef union VPP_VOP_HDMI_FRMT_CTRL0_T
{
    struct {
        unsigned int Enable                   : 1;
        unsigned int Mode                     : 1;
        unsigned int Load                     : 1;
        unsigned int ASInsert                 : 1;
        unsigned int ViewID                   : 2;
        unsigned int PackMode                 : 2;
        unsigned int reserved                 :24;
    } field;

    unsigned int data;
} VPP_VOP_HDMI_FRMT_CTRL0;
#endif

#endif
