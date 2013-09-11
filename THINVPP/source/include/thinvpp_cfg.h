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

#ifndef _VPP_CFG_H_
#define _VPP_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RESOLUTION_INFO_T {
    int active_width;
    int active_height;   /* active height of channel in pixel */
    int width;  /* width of channel in pixel */
    int height; /* height of channel in pixel */
    int hfrontporch; /* front porch of hsync */
    int hsyncwidth; /* hsync width */
    int hbackporch; /* back porch of hsync */
    int vfrontporch; /* front porch of vsync */
    int vsyncwidth; /* vsync width */
    int vbackporch; /* back porch of vsync */
    int type;   /* resolution type: HD or SD */
    int scan;   /* scan mode: progressive or interlaced */
    int frame_rate;   /* frame rate */
    int flag_3d;   /* 1 for 3D, 0 for 2D */
    int freq;   /* pixel frequency */
    int pts_per_cnt_4;   /* time interval in term of PTS for every 4 frames */
}RESOLUTION_INFO;

#ifndef _VPP_CFG_C_
/* VPP module constant tables */
extern const RESOLUTION_INFO m_resinfo_table[MAX_NUM_RESS];
#endif

#ifdef __cplusplus
}
#endif

#endif
