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

#define _VPP_CFG_C_

#include "thinvpp_module.h"
#include "thinvpp_cfg.h"

/////////////////////////////////////////////////////////////
// VPP module constant tables
/////////////////////////////////////////////////////////////

/* VPP TG standard timing format information table */
const RESOLUTION_INFO m_resinfo_table[MAX_NUM_RESS] = {
                     /* { active_width, active_height, width, height, hfrontporch, hsyncwidth, hbackporch, vfrontporch, vsyncwidth, vbackporch, type, scan, frame_rate, flag_3d, freq, pts_per_cnt_4 } */
    /* RES_NTSC_M    */ {     720,          480,         858,    525,    19,          62,         57,         4,           3,          15,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_59P94, 0, 27000, 6006 },
    /* RES_NTSC_J    */ {     720,          480,         858,    525,    19,          62,         57,         4,           3,          15,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_59P94, 0, 27000, 6006 },
    /* RES_PAL_M    */ {     720,          480,         858,    525,    19,          62,         57,         4,           3,          15,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_59P94, 0, 27000, 6006 },
    /* RES_PAL_BGH     */ {     720,          576,         864,    625,    12,          63,         69,         2,           3,          19,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_50, 0, 27000, 7200 },
    /* RES_525I60    */ {     720,          480,         858,    525,    19,          62,         57,         4,           3,          15,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_60, 0, 27027, 6000 },
    /* RES_525I5994    */ {     720,          480,         858,    525,    19,          62,         57,         4,           3,          15,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_59P94, 0, 27000, 6006 },
    /* RES_625I50     */ {     720,          576,         864,    625,    12,          63,         69,         2,           3,          19,   TYPE_SD, SCAN_INTERLACED, FRAME_RATE_50, 0, 27000, 7200 },
    /* RES_525P60  */ {     720,          480,         858,    525,    16,          62,         60,         9,           6,          30,   TYPE_SD, SCAN_PROGRESSIVE, FRAME_RATE_60, 0, 27027, 6000 },
    /* RES_525P5994  */ {     720,          480,         858,    525,    16,          62,         60,         9,           6,          30,   TYPE_SD, SCAN_PROGRESSIVE, FRAME_RATE_59P94, 0, 27000, 6006 },
    /* RES_625P50  */ {     720,          576,         864,    625,    12,          64,         68,         5,           5,          39,   TYPE_SD, SCAN_PROGRESSIVE, FRAME_RATE_50, 0, 27000, 7200 },
    /* RES_720P30  */ {    1280,          720,         3300,   750,    1760,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_30, 0, 74250, 12000 },
    /* RES_720P2997  */ {    1280,          720,         3300,   750,    1760,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_29P97, 0, 74176, 12012 },
    /* RES_720P25  */ {    1280,          720,         3960,   750,    2420,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_25, 0, 74250, 14400 },
    /* RES_720P60  */ {    1280,          720,         1650,   750,    110,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_60, 0, 74250, 6000 },
    /* RES_720P5994  */ {    1280,          720,         1650,   750,    110,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_59P94, 0, 74176, 6006 },
    /* RES_720P50  */ {    1280,          720,         1980,   750,    440,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_50, 0, 74250, 7200 },
    /* RES_1080I60 */ {    1920,         1080,         2200,   1125,   88,          44,         148,        2,           5,          15,   TYPE_HD, SCAN_INTERLACED, FRAME_RATE_60, 0, 148500, 6000 },
    /* RES_1080I5994 */ {    1920,         1080,         2200,   1125,   88,          44,         148,        2,           5,          15,   TYPE_HD, SCAN_INTERLACED, FRAME_RATE_59P94, 0, 148352, 6006 },
    /* RES_1080I50 */ {    1920,         1080,         2640,   1125,   528,         44,         148,        2,           5,          15,   TYPE_HD, SCAN_INTERLACED, FRAME_RATE_50, 0, 148500, 7200 },
    /* RES_1080P30 */ {    1920,         1080,         2200,   1125,   88,          44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_30, 0, 74250, 12000 },
    /* RES_1080P2997 */ {    1920,         1080,         2200,   1125,   88,          44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_29P97, 0, 74176, 12012 },
    /* RES_1080P25 */ {    1920,         1080,         2640,   1125,   528,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_25, 0, 74250, 14400 },
    /* RES_1080P24 */ {    1920,         1080,         2750,   1125,   638,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_24, 0, 74250, 15000 },
    /* RES_1080P2398 */ {    1920,         1080,         2750,   1125,   638,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_23P98, 0, 74176, 15015 },
    /* RES_1080P60 */ {    1920,         1080,         2200,   1125,   88,          44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_60, 0, 148500, 6000 },
    /* RES_1080P5994 */ {    1920,         1080,         2200,   1125,   88,          44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_59P94, 0, 148352, 6006 },
    /* RES_1080P50 */ {    1920,         1080,         2640,   1125,   528,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_50, 0, 148500, 7200 },
    /* RES_VGA_480P60  */ {640,          480,         800,    525,    16,          96,         48,         10,           2,          33,   TYPE_SD, SCAN_PROGRESSIVE, FRAME_RATE_60, 0, 25200, 6000 },
    /* RES_VGA_480P5994  */ {640,          480,         800,    525,    16,          96,         48,         10,           2,          33,   TYPE_SD, SCAN_PROGRESSIVE, FRAME_RATE_59P94, 0, 25175, 6006 },
    /* RES_720P50_3D  */ {    1280,          720,         1980,   750,    440,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_100, 1, 148500, 7200 },
    /* RES_720P60_3D  */ {    1280,          720,         1650,   750,    110,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_120, 1, 148500, 6000 },
    /* RES_720P5994_3D  */ {    1280,          720,         1650,   750,    110,         40,         220,        5,           5,          20,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_119P88, 1, 148352, 6006 },
    /* RES_1080P24_3D */ {    1920,         1080,         2750,   1125,   638,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_48, 1, 148500, 15000 },
    /* RES_1080P2398_3D */ {    1920,         1080,         2750,   1125,   638,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_47P96, 1, 148352, 15015 },
    /* RES_1080P30_3D */ {    1920,         1080,         2200,   1125,   88,          44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_60, 1, 148500, 12000 },
    /* RES_1080P2997_3D */ {    1920,         1080,         2200,   1125,   88,          44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_59P94, 1, 148352, 12012 },
    /* RES_1080P25_3D */ {    1920,         1080,         2640,   1125,   528,         44,         148,        4,           5,          36,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_50, 1, 148500, 14400 },
    /* RES_LVDS_1920X540P60_3D */ {    1920,         540,         1980,   625,   8,         44,         8,        16,           5,          64,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_120, 1, 148500, 6000 },
    /* RES_LVDS_1920X540P30_3D */ {    1920,         540,         1980,   625,   8,         44,         8,        16,           5,          64,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_60, 1, 74250, 12000 },
    /* RES_LVDS_1920X540P24_3D */ {    1920,         540,         2475,   625, 407,         44,       104,        16,           5,          64,   TYPE_HD, SCAN_PROGRESSIVE, FRAME_RATE_48, 1, 74250, 15000 },
    /* RES_RESET   */ {       0,            0,            1,      1,     0,          0,           0,        0,           0,           0,         0,                0, 0,    0 }
};
