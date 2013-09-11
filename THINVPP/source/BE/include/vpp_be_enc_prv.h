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

#ifndef _VPP_BE_ENC_PRV_H_
#define _VPP_BE_ENC_PRV_H_

#define WRITE_ENC_REG(RegName, Value) \
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (RegName << 2), Value)

#define MUTE_SD_ENC_INPUTS     0x01
#define MUTE_HD_ENC_INPUTS     0x01
#define MUTE_SD_ENC_OUTPUTS    0x7
#define MUTE_HD_ENC_OUTPUTS    0x7

/**********************************************************************
* Bit field definition for BE ENC                                     *
***********************************************************************/

/* SD and HD DAC Mode Register */
typedef struct tagENC_DAC_MODE_REGISTER_BITS {
    REG_WIDTH DacSel            : 4;
    REG_WIDTH OverSampleFactor  : 4;
}ENC_DAC_MODE_REGISTER_BITS;

typedef union tagENC_DAC_MODE_REGISTER {
    ENC_DAC_MODE_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_DAC_MODE_REGISTER;

/* Filter Control Register */
typedef struct tagENC_SD_CV_OUT_FILT_CTRL_REGISTER1_BITS {
    REG_WIDTH CVLumaLPFCtrl                : 2;
    REG_WIDTH CVChromaLPFCtrl              : 2;
    REG_WIDTH LumaNotchFilterCtrl          : 2;
    REG_WIDTH SVideoChromaLPFCtrl          : 2;
}ENC_SD_CV_OUT_FILT_CTRL_REGISTER1_BITS;

typedef union tagENC_SD_CV_OUT_FILT_CTRL_REGISTER1 {
    ENC_SD_CV_OUT_FILT_CTRL_REGISTER1_BITS Bits;
    REG_WIDTH Value;
}ENC_SD_CV_OUT_FILT_CTRL_REGISTER1;

/* Gradient Select Registers */
typedef struct tagENC_SD_CV_OUT_GRAD_SELECT_REGISTER1_BITS {
    REG_WIDTH SyncGradient                 : 3;
    REG_WIDTH Reserved1                    : 1;
    REG_WIDTH BlankGradient                : 3;
}ENC_SD_CV_OUT_GRAD_SELECT_REGISTER1_BITS;

typedef union tagENC_SD_CV_OUT_GRAD_SELECT_REGISTER1 {
    ENC_SD_CV_OUT_GRAD_SELECT_REGISTER1_BITS Bits;
    REG_WIDTH Value;
}ENC_SD_CV_OUT_GRAD_SELECT_REGISTER1;

/* Subcarrier frequency reset control Register */
typedef struct tagENC_SD_CV_OUT_SC_GEN_RESET_FREQ_REGISTER_BITS {
    REG_WIDTH Reserved1                     : 2;
    REG_WIDTH ResetCtrl                     : 2;
}ENC_SD_CV_OUT_SC_GEN_RESET_FREQ_REGISTER_BITS;

typedef union tagENC_SD_CV_OUT_SC_GEN_RESET_FREQ_REGISTER {
    ENC_SD_CV_OUT_SC_GEN_RESET_FREQ_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_SD_CV_OUT_SC_GEN_RESET_FREQ_REGISTER;

/* Component OUT Control Register */
typedef struct tagENC_SD_CX_OUT_CTRL_REGISTER_BITS {
    REG_WIDTH OutMode                       : 2;
    REG_WIDTH SyncMode                      : 2;
    REG_WIDTH ClipDis                       : 1;
    REG_WIDTH DigitalSyncEn                 : 1;
    REG_WIDTH HSyncPolarity                 : 1;
    REG_WIDTH VSyncPolarity                 : 1;
}ENC_SD_CX_OUT_CTRL_REGISTER_BITS;

typedef union tagENC_SD_CX_OUT_CTRL_REGISTER {
    ENC_SD_CX_OUT_CTRL_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_SD_CX_OUT_CTRL_REGISTER;

/* Closed Caption Control Register */
typedef struct tagENC_VBI_DATA_CC_CTRL_REGISTER_BITS {
    REG_WIDTH EnCCTopField                  : 1;
    REG_WIDTH EnCCBtmField                  : 1;
    REG_WIDTH EnContCC                      : 1;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    REG_WIDTH EnOnCVBS                      : 1;
    REG_WIDTH EnOnSVideo                    : 1;
    REG_WIDTH EnOnComponent                 : 1;
#if (BERLIN_CHIP_VERSION >= BERLIN_C_0)
    REG_WIDTH CheckSumPolarity              : 1;
    REG_WIDTH Reserved                      : 1;
#else
    REG_WIDTH Reserved                      : 2;
#endif
#else // Berlin_A_0
    REG_WIDTH Reserved                      : 5;
#endif
}ENC_VBI_DATA_CC_CTRL_REGISTER_BITS;

typedef union tagENC_VBI_DATA_CC_CTRL_REGISTER {
    ENC_VBI_DATA_CC_CTRL_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_VBI_DATA_CC_CTRL_REGISTER;

/* WSS, CGMS Control Register */
typedef struct tagENC_VBI_DATA_WSS_CGMS_CTRL_REGISTER_BITS {
    REG_WIDTH EnWssTopField                 : 1;
    REG_WIDTH EnWssBtmField                 : 1;
    REG_WIDTH CgmsWssCtrl                   : 1;
    REG_WIDTH EnContWss                     : 1;
    REG_WIDTH EnHWCgmsCrcGen                : 1;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    REG_WIDTH EnOnCVBS                      : 1;
    REG_WIDTH EnOnSVideo                    : 1;
    REG_WIDTH EnOnComponent                 : 1;
#else // Berlin_A0
    REG_WIDTH Reserved                      : 3;
#endif
}ENC_VBI_DATA_WSS_CGMS_CTRL_REGISTER_BITS;

typedef union tagENC_VBI_DATA_WSS_CGMS_CTRL_REGISTER
{
    ENC_VBI_DATA_WSS_CGMS_CTRL_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_VBI_DATA_WSS_CGMS_CTRL_REGISTER;

/* TT Control Register */
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
typedef struct tagENC_VBI_DATA_TT_CTRL_REGISTER_BITS {
    REG_WIDTH EnTT                          : 1;
    REG_WIDTH BitOrder                      : 1;
    REG_WIDTH EnOnCVBS                      : 1;
    REG_WIDTH EnOnSVideo                    : 1;
    REG_WIDTH EnOnComponent                 : 1;
}ENC_VBI_DATA_TT_CTRL_REGISTER_BITS;

typedef union tagENC_VBI_DATA_TT_CTRL_REGISTER
{
    ENC_VBI_DATA_TT_CTRL_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_VBI_DATA_TT_CTRL_REGISTER;
#endif

/* Encoder I/Os mute control register bits */
typedef struct tagENC_MUTE_CTRL_REGISTER_BITS {
    REG_WIDTH SdEncInpMute    : 1;
    REG_WIDTH HdEncInpMute    : 1;
    REG_WIDTH SdEncOutMute    : 3;
    REG_WIDTH HdEncOutMute    : 3;
}ENC_MUTE_CTRL_REGISTER_BITS;

typedef union tagENC_MUTE_CTRL_REGISTER {
    ENC_MUTE_CTRL_REGISTER_BITS Bits;
    REG_WIDTH Value;
}ENC_MUTE_CTRL_REGISTER;


/* HD Out Control Registers */
typedef struct tagENC_HD_OUT_CTRL_REGISTER1_BITS {
    REG_WIDTH Mode                         : 2;
    REG_WIDTH SyncMode                     : 2;
    REG_WIDTH TgMode                       : 3;
}ENC_HD_OUT_CTRL_REGISTER1_BITS;

typedef union tagENC_HD_OUT_CTRL_REGISTER1 {
    ENC_HD_OUT_CTRL_REGISTER1_BITS Bits;
    REG_WIDTH Value;
}ENC_HD_OUT_CTRL_REGISTER1;

typedef struct tagENC_HD_OUT_CTRL_REGISTER2_BITS {
    REG_WIDTH ClipDis                      : 1;
    REG_WIDTH DigitalSyncEn                : 1;
    REG_WIDTH HSyncPolarity                : 1;
    REG_WIDTH VSyncPolarity                : 1;
}ENC_HD_OUT_CTRL_REGISTER2_BITS;

typedef union tagENC_HD_OUT_CTRL_REGISTER2 {
    ENC_HD_OUT_CTRL_REGISTER2_BITS Bits;
    REG_WIDTH Value;
}ENC_HD_OUT_CTRL_REGISTER2;

#endif // _VPP_OUT_ENC_PRV_H_
