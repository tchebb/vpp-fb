/*
 * Copyright Marvell Semiconductor, Inc. 2006. All rights reserved.
 *
 * Register address mapping configure file for rom testing code.
 */

#ifndef drmdmx_h
#define drmdmx_h (){}
#include "ctypes.h"
#pragma pack(1)
    #define     RA_SECSTATUS_CFG                               0x0000
    #define        SECSTATUS_CFG_flag_DISABLED                              0x0
    #define        SECSTATUS_CFG_flag_ENABLED                               0x1
    #define        SECSTATUS_CFG_flag_FAILED                                0x2
    #define     w32SECSTATUS_CFG                               {\
            UNSG32 uCFG_flag                                   :  2;\
            UNSG32 uCFG_Reserved                               : 14;\
            UNSG32 uCFG_errCode                                : 16;\
          }
    typedef union  T32SECSTATUS_CFG
          { UNSG32 u32;
            struct w32SECSTATUS_CFG;
                 } T32SECSTATUS_CFG;
    #define     RA_DRMDMX_DTCM                                 0x0000
    #define     RA_DRMDMX_SECSAT                               0xD848
#pragma  pack()
#endif
