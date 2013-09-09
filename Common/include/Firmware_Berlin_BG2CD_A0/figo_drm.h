/*
 * Copyright Marvell Semiconductor, Inc. 2006. All rights reserved.
 *
 * Register address mapping configure file for rom testing code.
 */

#ifndef	__Figo_Drm__H__
#define	__Figo_Drm__H__

    #define     RA_DRMDMX_SECSAT                               0xD848
    #define     RA_SECSTATUS_CFG                               0x0000
    #define   MSK32SECSTATUS_CFG_flag                             0x00000003
    #define     RA_DRMDMX_DTCM                                 0x0000
    #define        SECSTATUS_CFG_flag_DISABLED                              0x0
    #define        SECSTATUS_CFG_flag_FAILED                                0x2

#endif

