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
 *  Include files
 *-----------------------------------------------------------------------------
 */

#include "vpp_be_enc.h"
#include "vpp_be_enc_presets.h"

// Presets for SD timing parameters
VPP_BE_ENC_TIMING_PARAMS SDTimingPresets[VPP_BE_ENC_CVFMT_MAX] = {
    { //NTSCM
        0x359,                              // HTotal
        0x20C,                              // VTotal
        0x3F,                               // HSync Width
        0x06,                               // VSync Width
        0x7C,                               // Hde Start
        0x24,                               // Vde Start
        0x347,                              // Hde End
        0x204,                              // Vde End
        0x48,                               // Burst Start
        0x6B,                               // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0xBA,                               // VDE PAD UP
        0xAA,                               // VDE PAD DOWN
        0x10,                               // VDE PAD Y DATA
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,        // DE Mask Mode
#endif
    },
    {//NTSCJ
        0x359,                              // HTotal
        0x20C,                              // VTotal
        0x3F,                               // HSync Width
        0x06,                               // VSync Width
        0x7C,                               // Hde Start
        0x24,                               // Vde Start
        0x347,                              // Hde End
        0x204,                              // Vde End
        0x48,                               // Burst Start
        0x6B,                               // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0xBA,                               // VDE PAD UP
        0xAA,                               // VDE PAD DOWN
        0x10,                               // VDE PAD Y DATA
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,        // DE Mask Mode
#endif
    },
    {//PAL BGH
        0x35F,                              // HTotal
        0x270,                              // VTotal
        0x3F,                               // HSync Width
        0x05,                               // VSync Width
        0x8D,                               // Hde Start
        0x2C,                               // Vde Start
        0x34C,                              // Hde End
        0x26C,                              // Vde End
        0x4B,                               // Burst Start
        0x6A,                               // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD UP
        0x10,                               // VDE PAD DOWN
        0x10,                               // VDE PAD Y DATA
#else // Berlin_A0
        (VPP_BE_ENC_DE_MASK_HALF_LINE_START_OF_TOP_FLD |
         VPP_BE_ENC_DE_MASK_HALF_LINE_END_OF_BTM_FLD)// DE Mask Mode
#endif
    },
    {//PAL M
        0x359,                              // HTotal
        0x20C,                              // VTotal
        0x40,                               // HSync Width
        0x06,                               // VSync Width
        0x7A,                               // Hde Start
        0x24,                               // Vde Start
        0x34A,                              // Hde End
        0x204,                              // Vde End
        0x48,                               // Burst Start
        0x6A,                               // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0xBA,                               // VDE PAD UP
        0xAA,                               // VDE PAD DOWN
        0x10,                               // VDE PAD Y DATA
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,        // DE Mask Mode
#endif
    },
};

// Presets for HD timing parameters
VPP_BE_ENC_TIMING_PARAMS HDTimingPresets[VPP_BE_ENC_RES_MAX] = {
    { //480i
        0x359,                              // HTotal
        0x20C,                              // VTotal
        0x3F,                               // HSync Width
        0x06,                               // VSync Width
        0x7A,                               // Hde Start
        0x24,                               // Vde Start
        0x346,                              // Hde End
        0x204,                              // Vde End
        0x47,                      // Burst Start
        0x69,                      // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x00,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,        // DE Mask Mode
#endif
        VPP_BE_ENC_CX_480I_576I_BILEVEL_SYNC, // bi-level sync
    },
    { // 576i
        0x35F,                              // HTotal
        0x270,                              // VTotal
        0x3F,                               // HSync Width
        0x05,                               // VSync Width
        0x84,                               // Hde Start
        0x2C,                               // Vde Start
        0x354,                              // Hde End
        0x26C,                              // Vde End
        0x4E,                               // Burst Start
        0x6C,                               // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x09,                               // VDE PAD
        0x00,                               // not used
        0x00,                               // VDE PAD Y Data
#else // Berlin_A0
        (VPP_BE_ENC_DE_MASK_HALF_LINE_START_OF_TOP_FLD |
         VPP_BE_ENC_DE_MASK_HALF_LINE_END_OF_BTM_FLD), // DE Mask Mode
#endif
        VPP_BE_ENC_CX_480I_576I_BILEVEL_SYNC, // bi-level sync
    },
    { // 480p
        0x359,                              // HTotal
        0x20C,                              // VTotal
        0x3F,                               // HSync Width
        0x06,                               // VSync Width
        0x7A,                               // Hde Start
        0x24,                               // Vde Start
        0x34A,                              // Hde End
        0x204,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x30,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_480P_576P_BILEVEL_SYNC, // bi-level sync
    },
    { // 576p
        0x35F,                              // HTotal
        0x270,                              // VTotal
        0x3F,                               // HSync Width
        0x05,                               // VSync Width
        0x84,                               // Hde Start
        0x2C,                               // Vde Start
        0x354,                              // Hde End
        0x26C,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x60,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_480P_576P_BILEVEL_SYNC, // bi-level sync
    },
    { // 720p60
        0x671,                              // HTotal
        0x2ED,                              // VTotal
        0x50,                               // HSync Width
        0x05,                               // VSync Width
        0x104,                              // Hde Start
        0x19,                               // Vde Start
        0x604,                              // Hde End
        0x2E9,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_720P_TRILEVEL_SYNC,   // tri-level sync
    },
    { // 720p50
        0x7BB,                              // HTotal
        0x2ED,                              // VTotal
        0x50,                               // HSync Width
        0x05,                               // VSync Width
        0x104,                              // Hde Start
        0x19,                               // Vde Start
        0x604,                              // Hde End
        0x2E9,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_720P_TRILEVEL_SYNC,   // tri-level sync
    },

    { // 1080i30
        0x897,                              // HTotal
        0x464,                              // VTotal
        0x58,                               // HSync Width
        0x0A,                               // VSync Width
        0xC0,                               // Hde Start
        0x29,                               // Vde Start
        0x840,                              // Hde End
        0x461,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_1080I_TRILEVEL_SYNC,    // tri-level sync
    },
    { // 1080i25
        0xA4F,                              // HTotal
        0x464,                              // VTotal
        0x58,                               // HSync Width
        0x0A,                               // VSync Width
        0xC0,                               // Hde Start
        0x29,                               // Vde Start
        0x840,                              // Hde End
        0x461,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_1080I_TRILEVEL_SYNC,    // tri-level sync
    },

    { // 1080p60
        0x897,                              // HTotal
        0x464,                              // VTotal
        0x58,                               // HSync Width
        0x05,                               // VSync Width
        0xC0,                               // Hde Start
        0x29,                               // Vde Start
        0x840,                              // Hde End
        0x461,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_1080P_TRILEVEL_SYNC,    // tri-level sync
    },

    { // 1080p50
        0xA4F,                              // HTotal
        0x464,                              // VTotal
        0x58,                               // HSync Width
        0x05,                               // VSync Width
        0xC0,                               // Hde Start
        0x29,                               // Vde Start
        0x840,                              // Hde End
        0x461,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_1080P_TRILEVEL_SYNC,    // tri-level sync
    },

    { // 1080p24
        0xABD,                              // HTotal
        0x464,                              // VTotal
        0x58,                               // HSync Width
        0x05,                               // VSync Width
        0xC0,                               // Hde Start
        0x29,                               // Vde Start
        0x840,                              // Hde End
        0x461,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x00,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_1080P_TRILEVEL_SYNC,    // tri-level sync
    },
    { // VGA_640x480p60
        0x31F,                              // HTotal
        0x20C,                              // VTotal
        0x60,                               // HSync Width
        0x02,                               // VSync Width
        0x90,                               // Hde Start
        0x23,                               // Vde Start
        0x310,                              // Hde End
        0x203,                              // Vde End
        0x0,                                // Burst Start
        0x0,                                // Burst End
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        0x30,                               // VDE PAD
        0x00,                               // not used
        0x10,                               // VDE PAD Y Data
#else // Berlin_A0
        VPP_BE_ENC_DE_MASK_DISABLE,         // DE Mask Mode
#endif
        VPP_BE_ENC_CX_480P_576P_BILEVEL_SYNC, // bi-level sync
    },
};

// Preset values for SD path CVBS and SVideo parameters
VPP_BE_ENC_CVBS_SVIDEO_PARAMS CvbsSVideoPresets[VPP_BE_ENC_CVFMT_MAX] = {
    { //NTSCM
        0x1,                                // NTSC
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x4D,                               // Sync Pedestal
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0x3BE,                              // Sync Height
#else
        0x49B,                              // Sync Height
#endif
#else
        0x3F,                               // Sync Pedestal
        0x3C3,                              // Sync Height
#endif
        VPP_BE_ENC_SYNC_140NS_GRADIENT,    // Sync Gradient
        VPP_BE_ENC_SYNC_140NS_GRADIENT,    // Blank Gradient
        VPP_BE_ENC_SYNC_300NS_GRADIENT,    // Burst Window Gradient
        0x0,                                // Luma Clipping
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0xB4,                               // Y setup value
        0x287,                              // Luma Scale
        0x228,                              // Cb Scale
        0x30A,                              // Cr Scale
#else
        0xDC,                               // Y setup value
        0x323,                              // Luma Scale
        0x2C1,                              // Cb Scale
        0x3DD,                              // Cr Scale
#endif
#else
        0xB4,                               // Y setup value
        0x290,                              // Luma Scale
        0x240,                              // Cb Scale
        0x328,                              // Cr Scale
#endif
        0x110,                              // Luma Offset
        0x0,                                // Hue Offset
        0x00,                               // Min Data Output
        0x0FFF,                             // Max Data Output
        0x21F07C1F,                         // SC Freq
        0x0,                                // SC Initial Phase
        0x1,                                // SC Reset frequency - every two lines
    },
    { // NTSCJ
        0x1,                                // NTSC
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x4D,                               // Sync Pedestal
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0x3BE,                              // Sync Height
#else
        0x49B,                              // Sync Height
#endif
#else
        0x3F,                               // Sync Pedestal
        0x3C3,                              // Sync Height
#endif
        VPP_BE_ENC_SYNC_140NS_GRADIENT,     // Sync Gradient
        VPP_BE_ENC_SYNC_140NS_GRADIENT,     // Blank Gradient
        VPP_BE_ENC_SYNC_300NS_GRADIENT,     // Burst Window Gradient
        0x0,                                // Luma Clipping
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0x00,                               // Y setup value
        0x2B8,                              // Luma Scale
        0x253,                              // Cb Scale
        0x345,                              // Cr Scale
#else
        0x00,                               // Y setup value
        0x36B,                              // Luma Scale
        0x2FB,                              // Cb Scale
        0x418,                              // Cr Scale
#endif
#else
        0x00,                               // Y setup value
        0x2CB,                              // Luma Scale
        0x26F,                              // Cb Scale
        0x358,                              // Cr Scale
#endif
        0x110,                              // Luma Offset
        0x0,                                // Hue Offset
        0x00,                               // Min Data Output
        0x0FFF,                             // Max Data Output
        0x21F07C1F,                         // SC Freq
        0x0,                                // SC Initial Phase
        0x1,                                // SC Reset frequency - every two lines
    },
    { // PAL BGH
        0x0,                                // PAL
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x4D,                               // Sync Pedestal
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0x3F1,                              // Sync Height
#else
        0x4D6,                              // Sync Height
#endif
#else
        0x3F,                               // Sync Pedestal
        0x3F3,                              // Sync Height
#endif
        VPP_BE_ENC_SYNC_250NS_GRADIENT,     // Sync Gradient
        VPP_BE_ENC_SYNC_300NS_GRADIENT,     // Blank Gradient
        VPP_BE_ENC_SYNC_250NS_GRADIENT,     // Burst Window Gradient
        0x0,                                // Luma Clipping
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0x00,                               // Y setup value
        0x2AA,                              // Luma Scale
        0x247,                              // Cb Scale
        0x334,                              // Cr Scale
#else
        0x00,                               // Y setup value
        0x347,                              // Luma Scale
        0x2CD,                              // Cb Scale
        0x3FB,                              // Cr Scale
#endif
#else
        0x00,                               // Y setup value
        0x2AD,                              // Luma Scale
        0x24A,                              // Cb Scale
        0x340,                              // Cr Scale
#endif
        0x110,                              // Luma Offset
        0x0,                                // Hue Offset
        0x00,                               // Min Data Output
        0x0FFF,                             // Max Data Output
        0x2A098ACB,                         // SC Freq
        0x0,                                // SC Initial Phase
        0x3,                                // SC Reset frequency
    },
    { // PAL M
        0x0,                                // PAL
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x4D,                               // Sync Pedestal
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0x3BE,                              // Sync Height
#else
        0x44E,                              // Sync Height
#endif
#else
        0x3F,                               // Sync Pedestal
        0x384,                              // Sync Height
#endif
        VPP_BE_ENC_SYNC_140NS_GRADIENT,     // Sync Gradient
        VPP_BE_ENC_SYNC_250NS_GRADIENT,     // Blank Gradient
        VPP_BE_ENC_SYNC_140NS_GRADIENT,     // Burst Window Gradient
        0x0,                                // Luma Clipping
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_A0)
        0xB4,                               // Y setup value
        0x287,                              // Luma Scale
        0x228,                              // Cb Scale
        0x30A,                              // Cr Scale
#else
        0xCF,                               // Y setup value
        0x2E8,                              // Luma Scale
        0x27B,                              // Cb Scale
        0x37F,                              // Cr Scale
#endif
#else
        0xA9,                               // Y setup value
        0x260,                              // Luma Scale
        0x207,                              // Cb Scale
        0x2DB,                              // Cr Scale
#endif
        0x110,                              // Luma Offset
        0x0,                                // Hue Offset
        0x00,                               // Min Data Output
        0x0FFF,                             // Max Data Output
        0x21E6EFE3,                         // SC Freq
        0x0,                                // SC Initial Phase
        0x1,                                // SC Reset frequency - - every two lines
    }
};

#if defined(BERLIN_DTV_MERGE) && (!((BERLIN_CHIP_VERSION >= BERLIN_B_0)))
// Preset values for Component Out Parameters
VPP_BE_ENC_COMPONENT_PARAMS CompPresets[VPP_BE_ENC_RES_MAX] = {
    { // 480i
        0x0,                                // Component Setup Value
        0x10,                               // Component Sync Pedestal
        0x408,                              // Component Sync Height
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
        0x2b0,                              // Cb/B Scale
        0x2be,                              // Y/G Scale
        0x2b4,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 576i
        0x0,                                // Component Setup Value
        0x10,                               // Component Sync Pedestal
        0x408,                              // Component Sync Height
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
        0x2b9,                              // Cb/B Scale
        0x2c4,                              // Y/G Scale
        0x2b0,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x111,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 480p
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
        0x2AD,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2AD,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 576p
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT, // Component Sync Gradient
        0x2AD,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2AD,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 720p60
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x276,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x276,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 720p50
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x276,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x276,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },

    { // 1080i30
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x2B2,                              // Cb/B Scale
        0x2BC,                              // Y/G Scale
        0x2B0,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 1080i25
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x276,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x276,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },

    { // 1080p60
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x276,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x276,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 1080p50
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x276,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x276,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 1080p24
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
        0x276,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x276,                              // Cr/R Scale
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // VGA_640x480p60
        0x0,                                // Component Setup Value
        0x3F,                               // Component Sync Pedestal
        0x3B4,                              // Component Sync Height
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
        0x281,                              // Cb/B Scale
        0x281,                              // Y/G Scale
        0x281,                              // Cr/R Scale
        0x110,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x110,                                // Cr/R Offset
    },
};
#else
// Preset values for Component Out Parameters
VPP_BE_ENC_COMPONENT_PARAMS CompPresets[VPP_BE_ENC_RES_MAX] = {
    { // 480i
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x14,                               // Component Sync Pedestal
        0x542,                              // Component Sync Height
#else
        0x10,                               // Component Sync Pedestal
        0x408,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x381,                              // Cb/B Scale
        0x394,                              // Y/G Scale
        0x387,                              // Cr/R Scale
#else
        0x2b0,                              // Cb/B Scale
        0x2be,                              // Y/G Scale
        0x2b4,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 576i
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x14,                               // Component Sync Pedestal
        0x542,                              // Component Sync Height
#else
        0x10,                               // Component Sync Pedestal
        0x408,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x38d,                              // Cb/B Scale
        0x39b,                              // Y/G Scale
        0x381,                              // Cr/R Scale
#else
        0x2b9,                              // Cb/B Scale
        0x2c4,                              // Y/G Scale
        0x2b0,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x111,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 480p
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x37d,                              // Cb/B Scale
        0x396,                              // Y/G Scale
        0x37d,                              // Cr/R Scale
#else
        0x2AD,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2AD,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 576p
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT, // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x37d,                              // Cb/B Scale
        0x396,                              // Y/G Scale
        0x37d,                              // Cr/R Scale
#else
        0x2AD,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2AD,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 720p60
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x37c,                              // Cb/B Scale
        0x396,                              // Y/G Scale
        0x381,                              // Cr/R Scale
#else
        0x2AC,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2B0,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 720p50
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x37d,                              // Cb/B Scale
        0x396,                              // Y/G Scale
        0x37d,                              // Cr/R Scale
#else
        0x2AD,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2AD,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },

    { // 1080i30
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x384,                              // Cb/B Scale
        0x391,                              // Y/G Scale
        0x381,                              // Cr/R Scale
#else
        0x2B2,                              // Cb/B Scale
        0x2BC,                              // Y/G Scale
        0x2B0,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 1080i25
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x384,                              // Cb/B Scale
        0x396,                              // Y/G Scale
        0x381,                              // Cr/R Scale
#else
        0x2B2,                              // Cb/B Scale
        0x2C0,                              // Y/G Scale
        0x2B0,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },

    { // 1080p60
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x36f,                              // Cb/B Scale
        0x37f,                              // Y/G Scale
        0x36f,                              // Cr/R Scale
#else
        0x2A2,                              // Cb/B Scale
        0x2AE,                              // Y/G Scale
        0x2A2,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 1080p50
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x36f,                              // Cb/B Scale
        0x37f,                              // Y/G Scale
        0x36f,                              // Cr/R Scale
#else
        0x2A2,                              // Cb/B Scale
        0x2AE,                              // Y/G Scale
        0x2A2,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // 1080p24
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_27NS_54NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x36f,                              // Cb/B Scale
        0x37f,                              // Y/G Scale
        0x36f,                              // Cr/R Scale
#else
        0x2A2,                              // Cb/B Scale
        0x2AE,                              // Y/G Scale
        0x2A2,                              // Cr/R Scale
#endif
        0x0,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x0,                                // Cr/R Offset
    },
    { // VGA_640x480p60
        0x0,                                // Component Setup Value
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x52,                               // Component Sync Pedestal
        0x53d,                              // Component Sync Height
#else
        0x3F,                               // Component Sync Pedestal
        0x404,                              // Component Sync Height
#endif
        VPP_BE_ENC_CX_140NS_70NS_GRADIENT,  // Component Sync Gradient
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2)
        0x37f,                              // Cb/B Scale
        0x37f,                              // Y/G Scale
        0x37f,                              // Cr/R Scale
#else
        0x2AE,                              // Cb/B Scale
        0x2AE,                              // Y/G Scale
        0x2AE,                              // Cr/R Scale
#endif
        0x110,                                // Cb/B Offset
        0x110,                              // Y/G Offset
        0x110,                                // Cr/R Offset
    },
};
#endif

// Default filter parameters for Composite, S-Video output
VPP_BE_ENC_CV_PATH_FLTR_PARAMS DefFltrParams = {
    VPP_BE_ENC_CVBS_LUMA_LPF_BYPASS,               // CVBS Luma LPF control
    VPP_BE_ENC_CVBS_CHROMA_LPF_1_3MHZ_PASS_BAND,   // CVBS Chroma LPF control
    VPP_BE_ENC_CVBS_LUMA_NOTCH_FLTR_BYPASS,        // CVBS Luma Notch filter control
    VPP_BE_ENC_SVIDEO_CHROMA_LPF_3MHZ_PASS_BAND,   // SVideo Chroma LPF control
    VPP_BE_ENC_SVIDEO_LUMA_FROM_UPSMPLR_OUT        // SVideo Luma Selection
};
