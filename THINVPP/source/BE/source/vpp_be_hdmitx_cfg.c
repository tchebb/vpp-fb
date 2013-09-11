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

/*-----------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------------
 */

#include "thinvpp_module.h"
#include "vpp_be_hdmitx.h"
#include "vpp_be_hdmitx_cfg.h"

/*-----------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------------
 */

// Memory size
const unsigned short HdmiTxMemSize = 0xFFFF;

// Deep color fifo read and write pointers
const unsigned char HdmiTxReadPtr  = 0x1F;
const unsigned char HdmiTxWritePtr = 0x00;

// Swap Control Flags
const int HdmiTxEnTmdsBitSwap = 0;
const int HdmiTxEnTmdsChnSwap = 0;

// BCH Rotate Setting
const int HdmiTxEnBchRot = 0;

// I2S Bus Params
VPP_BE_HDMITX_AUDIO_BUS_PARAMS I2SBusParams =\
{\
   {\
   0x0, /* ClkDelay */\
   0x0, /* DataShift*/\
   0x0, /* DataJustification */\
   0x0, /* LeftChnWordSelEdge*/\
   0x0, /* DataLatchingEdge  */\
   0x2, /* PortCfg - Port 1  */\
   }\
};
const unsigned int HdmiTxTmdsClkCfg = 0x0F83E0;

