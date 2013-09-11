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

#ifndef __VPP_BE_ENC_PRESETS_H__
#define __VPP_BE_ENC_PRESETS_H__

#include "vpp_be_enc.h"

/*-----------------------------------------------------------------------------
 * Extern DataTypes
 *-----------------------------------------------------------------------------
 */

// Presets for timing parameters
extern VPP_BE_ENC_TIMING_PARAMS SDTimingPresets[VPP_BE_ENC_CVFMT_MAX];
extern VPP_BE_ENC_TIMING_PARAMS HDTimingPresets[VPP_BE_ENC_RES_MAX];

// Preset values for SD path CVBS and SVideo parameters
extern VPP_BE_ENC_CVBS_SVIDEO_PARAMS CvbsSVideoPresets[VPP_BE_ENC_CVFMT_MAX];
// Preset values for Component Out Parameters
extern VPP_BE_ENC_COMPONENT_PARAMS CompPresets[VPP_BE_ENC_RES_MAX];

// Default filter parameters for Composite, S-Video output
extern VPP_BE_ENC_CV_PATH_FLTR_PARAMS DefFltrParams;

// HD Sync mode for possible output types
extern VPP_BE_ENC_CX_TG_MODE HDTgMode[VPP_BE_ENC_RES_MAX];

#endif /* __VPP_BE_ENC_PRESETS_H__ */
