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

#ifndef __VPP_BE_HDMITX_CFG_H__
#define __VPP_BE_HDMITX_CFG_H__

/*-----------------------------------------------------------------------------
 * Externed Variables
 *-----------------------------------------------------------------------------
 */

// Memory size
extern const unsigned short HdmiTxMemSize;

// Deep color fifo read and write pointers
extern const unsigned char HdmiTxReadPtr;
extern const unsigned char HdmiTxWritePtr;

// Swap Control Flags
extern const int HdmiTxEnTmdsBitSwap;
extern const int HdmiTxEnTmdsChnSwap;

// BCH Rotate Setting
extern const int HdmiTxEnBchRot;

// I2S Bus Params
extern VPP_BE_HDMITX_AUDIO_BUS_PARAMS I2SBusParams;
extern const unsigned int HdmiTxTmdsClkCfg;

#endif // __VPP_BE_HDMITX_CFG_H__
