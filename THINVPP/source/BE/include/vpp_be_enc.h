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
* MARVELL intERNATIONAL LTD. (MIL), MARVELL TECHNOLOGY, INC. (MTI), MARVELL    *
* SEMICONDUCTOR, INC. (MSI), MARVELL ASIA PTE LTD. (MAPL), MARVELL JAPAN K.K.  *
* (MJKK), MARVELL ISRAEL LTD. (MSIL).                                          *
*******************************************************************************/

#ifndef __VPP_BE_ENC_H__
#define __VPP_BE_ENC_H__

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/*-----------------------------------------------------------------------------
 * Enums, Structures and Unions
 *-----------------------------------------------------------------------------
 */
#if (BERLIN_CHIP_VERSION >= BERLIN_BG2_B0)
/* Macro for checking VDAC calibration done */
#define VDAC_CAL_DONE(sts) ((sts) & 0x01) && !((sts) & 0x02) && ((sts) & (1<<27)) && ((sts) & (1<<30))
#endif
// Encoder path - SD/HD
typedef enum tagVPP_BE_ENC_PATH_TYPE
{
    VPP_BE_ENC_SD_PATH = 0,
    VPP_BE_ENC_HD_PATH,
    VPP_BE_ENC_PATH_MAX
}VPP_BE_ENC_PATH_TYPE, *PVPP_BE_ENC_PATH_TYPE;

/* SD Path output type
 * (Component and S-Video outputs are also governed by this setting as they
 *  share registers in the SD path)
 */
// Composite output formats
typedef enum tagVPP_BE_ENC_CV_FMTS
{
    VPP_BE_ENC_CVFMT_NTSC_M = 0,
    VPP_BE_ENC_CVFMT_NTSC_J,
    VPP_BE_ENC_CVFMT_PAL_BGH,
    VPP_BE_ENC_CVFMT_PAL_M,
    VPP_BE_ENC_CVFMT_MAX
}VPP_BE_ENC_CV_FMTS;

// Encoder ouput resolution
typedef enum tagVPP_BE_ENC_RES
{
    VPP_BE_ENC_RES_480i = 0,
    VPP_BE_ENC_RES_576i,
    VPP_BE_ENC_RES_480p,
    VPP_BE_ENC_RES_576p,
    VPP_BE_ENC_RES_720p60,
    VPP_BE_ENC_RES_720p50,
    VPP_BE_ENC_RES_1080i30,
    VPP_BE_ENC_RES_1080i25,
    VPP_BE_ENC_RES_1080p60,
    VPP_BE_ENC_RES_1080p50,
    VPP_BE_ENC_RES_1080p24,
    VPP_BE_ENC_RES_VGA_480p60,
    VPP_BE_ENC_RES_MAX
}VPP_BE_ENC_RES, *PVPP_BE_ENC_RES;

// Filter configuration for Composite and S-Video path

// Composite path Luma low pass filter configuration modes
typedef enum tagVPP_BE_ENC_CVBS_LUMA_LPF_CTRL_MODE
{
    VPP_BE_ENC_CVBS_LUMA_LPF_BYPASS = 0,
    VPP_BE_ENC_CVBS_LUMA_LPF_5MHZ_PASS_BAND,
    VPP_BE_ENC_CVBS_LUMA_LPF_RESERVED,
    VPP_BE_ENC_CVBS_LUMA_LPF_4MHZ_PASS_BAND
} VPP_BE_ENC_CVBS_LUMA_LPF_CTRL_MODE, *PVPP_BE_ENC_CVBS_LUMA_LPF_CTRL_MODE;

// Composite path chroma low pass filter configuration modes
typedef enum tagVPP_BE_ENC_CVBS_CHROMA_LPF_CTRL_MODE
{
    VPP_BE_ENC_CVBS_CHROMA_LPF_BYPASS = 0,
    VPP_BE_ENC_CVBS_CHROMA_LPF_1_3MHZ_PASS_BAND,
    VPP_BE_ENC_CVBS_CHROMA_LPF_2MHZ_PASS_BAND,
    VPP_BE_ENC_CVBS_CHROMA_LPF_3MHZ_PASS_BAND,
    VPP_BE_ENC_CVBS_CHROMA_LPF_SEL_MAX
} VPP_BE_ENC_CVBS_CHROMA_LPF_CTRL_MODE, *PVPP_BE_ENC_CVBS_CHROMA_LPF_CTRL_MODE;

// Composite path Luma notch filter configuration modes
typedef enum tagVPP_BE_ENC_CVBS_LUMA_NOTCH_FLTR_CTRL_MODE
{
    VPP_BE_ENC_CVBS_LUMA_NOTCH_FLTR_BYPASS = 0,
    VPP_BE_ENC_CVBS_LUMA_4_43_NOTCH_FLTR,
    VPP_BE_ENC_CVBS_LUMA_NOTCH_FLTR_RESERVED,
    VPP_BE_ENC_CVBS_LUMA_3_58_NOTCH_FLTR
} VPP_BE_ENC_CVBS_LUMA_NOTCH_FLTR_CTRL_MODE, *PVPP_BE_ENC_CVBS_LUMA_NOTCH_FLTR_CTRL_MODE;

// S-Video path chroma low pass filter configuration modes
typedef enum tagVPP_BE_ENC_SVIDEO_CHROMA_LPF_CTRL_MODE
{
    VPP_BE_ENC_SVIDEO_CHROMA_LPF_BYPASS = 0,
    VPP_BE_ENC_SVIDEO_CHROMA_LPF_1_3MHZ_PASS_BAND,
    VPP_BE_ENC_SVIDEO_CHROMA_LPF_2MHZ_PASS_BAND,
    VPP_BE_ENC_SVIDEO_CHROMA_LPF_3MHZ_PASS_BAND,
    VPP_BE_ENC_SVIDEO_CHROMA_LPF_SEL_MAX
} VPP_BE_ENC_SVIDEO_CHROMA_LPF_CTRL_MODE, *PVPP_BE_ENC_SVIDEO_CHROMA_LPF_CTRL_MODE;

// S-Video Luma selection modes - defines the point at which S-Video luma
// have to be tapped
typedef enum tagVPP_BE_ENC_SVIDEO_LUMA_SEL_MODE
{
    VPP_BE_ENC_SVIDEO_LUMA_FROM_UPSMPLR_OUT = 0,
    VPP_BE_ENC_SVIDEO_LUMA_FROM_YLPF_OUT,
    VPP_BE_ENC_SVIDEO_LUMA_FROM_NOTCH_OUT,
    VPP_BE_ENC_SVIDEO_LUMA_SEL_MAX
} VPP_BE_ENC_SVIDEO_LUMA_SEL_MODE, *PVPP_BE_ENC_SVIDEO_LUMA_SEL_MODE;

// Composite,S-Video Sync Gradient
typedef enum tagVPP_BE_ENC_CV_PATH_SYNC_GRAD_SEL_MODE
{
    VPP_BE_ENC_SYNC_140NS_GRADIENT = 0, // 140 ns
    VPP_BE_ENC_SYNC_250NS_GRADIENT,     // 250 ns
    VPP_BE_ENC_SYNC_300NS_GRADIENT,     // 300 ns
    VPP_BE_ENC_SYNC_GRADIENT_MAX
}VPP_BE_ENC_CV_PATH_SYNC_GRAD_SEL_MODE, *PVPP_BE_ENC_CV_PATH_SYNC_GRAD_SEL_MODE;

// Component Out Sync Gradient Select
typedef enum tagVPP_BE_ENC_CX_SYNC_GRAD_SELECT
{
    VPP_BE_ENC_CX_140NS_70NS_GRADIENT = 0,  // 140/70 ns
    VPP_BE_ENC_CX_27NS_54NS_GRADIENT,       // 27/54 ns
    VPP_BE_ENC_CX_GRADIENT_MAX
}VPP_BE_ENC_CX_SYNC_GRAD_SELECT, *PVPP_BE_ENC_CX_SYNC_GRAD_SELECT;

// Data Enable active lines mask mode
typedef enum tagVPP_BE_ENC_DE_MASK_MODE
{
    VPP_BE_ENC_DE_MASK_DISABLE = 0,
    VPP_BE_ENC_DE_MASK_HALF_LINE_START_OF_TOP_FLD = 1,
    VPP_BE_ENC_DE_MASK_HALF_LINE_END_OF_TOP_FLD = 2,
    VPP_BE_ENC_DE_MASK_HALF_LINE_START_OF_BTM_FLD = 4,
    VPP_BE_ENC_DE_MASK_HALF_LINE_END_OF_BTM_FLD = 8
}VPP_BE_ENC_DE_MASK_MODE, *PVPP_BE_ENC_DE_MASK_MODE;

// Component output modes
typedef enum tagVPP_BE_ENC_CX_FMT
{
    VPP_BE_ENC_CX_YPbPr = 0,
    VPP_BE_ENC_CX_RGB,
    VPP_BE_ENC_CX_GRAPHICS_RGB,
    VPP_BE_ENC_CX_FMT_MAX
}VPP_BE_ENC_CX_FMT, *PVPP_BE_ENC_CX_FMT;

// Component out sync configurations
typedef enum tagVPP_BE_ENC_CX_SYNC_MODE
{
    VPP_BE_ENC_CX_NO_SYNC = 0,
    VPP_BE_ENC_CX_SYNC_ON_YG,
    VPP_BE_ENC_CX_SYNC_ON_3CHN,
    VPP_BE_ENC_CX_SYNC_CFG_MAX
}VPP_BE_ENC_CX_SYNC_MODE, *PVPP_BE_ENC_CX_SYNC_MODE;

// Valid only for HD Path - check is this is required??
typedef enum tagVPP_BE_ENC_CX_TG_MODE
{
    VPP_BE_ENC_CX_480P_576P_BILEVEL_SYNC = 0,
    VPP_BE_ENC_CX_480I_576I_BILEVEL_SYNC = 1,
    VPP_BE_ENC_CX_720P_TRILEVEL_SYNC = 4,
    VPP_BE_ENC_CX_1080P_TRILEVEL_SYNC = 6,
    VPP_BE_ENC_CX_1080I_TRILEVEL_SYNC = 7,
    VPP_BE_ENC_CX_TG_MODE_MAX
}VPP_BE_ENC_CX_TG_MODE, *PVPP_BE_ENC_CX_TG_MODE;

/* Of the 6 DACs, first 3 are meant solely for handling SD outputs, the other 3
 * are shared for SD and HD outputs
 */
typedef enum tagVPP_BE_ENC_DAC_GRP
{
    VPP_BE_ENC_SD_DACS = 0, // 3 DACs used only for SD out
    VPP_BE_ENC_HD_DACS,     // 3 DACs used for both SD and HD
    VPP_BE_ENC_DAC_GRP_MAX
}VPP_BE_ENC_DAC_GRP, *PVPP_BE_ENC_DAC_GRP;

// Possible DAC configurations
// Mutually exclusive configuration between the two dac groups
// is to be handled by higher SW layers
typedef enum tagVPP_BE_ENC_DAC_MODE
{
    // DAC 2,1,0 - SD YCbCr/RGB
    VPP_BE_ENC_SD_COMPONENT_OUT = 0,
    // DAC 2,1 - SVideo, DAC0 - CVBS
    VPP_BE_ENC_SVIDEO_CVBS_OUT,
    // DAC 2 - CVBS, DAC 1,0 - SVideo
    VPP_BE_ENC_CVBS_SVIDEO_OUT,
    // DAC 2,1,0 - 3 CVBS outputs
    VPP_BE_ENC_CVBS_OUT,
    // DAC 2,1,0 - HD YCbCr/RGB
    VPP_BE_ENC_HD_COMPONENT_OUT,
    VPP_BE_ENC_DAC_MAX_MODE = 8
}VPP_BE_ENC_DAC_MODE, *PVPP_BE_ENC_DAC_MODE;

// OverSampling Factor
typedef enum tagVPP_BE_ENC_DAC_OVERSMPL_FACT
{
    VPP_BE_ENC_NO_OVERSAMPLING = 0,
    VPP_BE_ENC_2X_OVERSAMPLING,
    VPP_BE_ENC_4X_OVERSAMPLING,
    VPP_BE_ENC_8X_OVERSAMPLING,
    VPP_BE_ENC_MAX_OVERSAMPLING_FACTOR
}VPP_BE_ENC_DAC_OVERSMPL_FACT, *PVPP_BE_ENC_DAC_OVERSMPL_FACT;

// Macrovision control
typedef enum tagVPP_BE_ENC_MV_CTRL
{
    VPP_BE_ENC_MV_OFF = 0,
    VPP_BE_ENC_MV_AGC,
    VPP_BE_ENC_MV_AGC_2LINE,
    VPP_BE_ENC_MV_AGC_4LINE,
    VPP_BE_ENC_MAX_MV_CTRL
}VPP_BE_ENC_MV_CTRL;

// Structure grouping the above filter configuration parameters
typedef struct tagVPP_BE_ENC_CV_PATH_FLTR_PARAMS
{
    char       CvbsLumaLPFCtrlMode;
    char       CvbsChromaLPFCtrlMode;
    char       CvbsLumaNotchFilterCtrlMode;
    char       SVideoChromaLPFCtrlMode;
    char       SVideoLumaSelectMode;
}VPP_BE_ENC_CV_PATH_FLTR_PARAMS, *PVPP_BE_ENC_CV_PATH_FLTR_PARAMS;

// Timing Parameters
typedef struct tagVPP_BE_ENC_TIMING_PARAMS
{
    unsigned short                              HTotal;
    unsigned short                              VTotal;
    unsigned char                               HSyncWidth;
    unsigned char                               VSyncWidth;
    unsigned short                              HdeStart;
    unsigned short                              VdeStart;
    unsigned short                              HdeEnd;
    unsigned short                              VdeEnd;
    unsigned char                               BurstStart;
    unsigned char                               BurstEnd;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned char                               VdePadUp;
    unsigned char                               VdePadDown;
    unsigned char                               VdePadYData;
#else // Berlin_A0
    unsigned char                               DEMaskMode;
#endif
    unsigned char                               SyncLevel;
}VPP_BE_ENC_TIMING_PARAMS, *PVPP_BE_ENC_TIMING_PARAMS;

// CVBS and SVideo Parameters
typedef struct tagVPP_BE_ENC_CVBS_SVIDEO_PARAMS
{
    int                                NtscPal;
    unsigned char                               SyncPedestal;
    unsigned short                              SyncHeight;
    unsigned char                               SyncGradient;
    unsigned char                               BlankGradient;
    unsigned char                               BurstWindowGradient;
    int                                LumaClipping;
    unsigned char                               YSetupVal;
    unsigned short                              YScale;
    unsigned short                              CbScale;
    unsigned short                              CrScale;
    unsigned short                              LumaOffset;
    unsigned char                               HueOffset;
    unsigned short                              MinOutDataLevel;
    unsigned short                              MaxOutputDataLevel;

    // Sub-carrier control - valid for composite
    unsigned int                              SCFreq;
    unsigned char                               SCInitialPhase;
    unsigned char                               SCGenResetFreq;
}VPP_BE_ENC_CVBS_SVIDEO_PARAMS, *PVPP_BE_ENC_CVBS_SVIDEO_PARAMS;

typedef struct tagVPP_BE_ENC_COMPONENT_PARAMS
{
    unsigned char                               SetupValue;
    unsigned char                               SyncPedestal;
    unsigned short                              SyncHeight;
    unsigned char                               SyncGradient;
    unsigned short                              CbBScale;
    unsigned short                              YGScale;
    unsigned short                              CrRScale;
    unsigned short                              CbBOffset;
    unsigned short                              YGOffset;
    unsigned short                              CrROffset;
}VPP_BE_ENC_COMPONENT_PARAMS, *PVPP_BE_ENC_COMPONENT_PARAMS;

// Component out control parameters
typedef struct tagVPP_BE_ENC_CX_CTRL_PARAMS
{
    unsigned char                              CxSyncMode;
    int                               DisableClipping;
    int                               DigitalSync;
    int                               HSyncPolarity;
    int                               VSyncPolarity;
}VPP_BE_ENC_CX_CTRL_PARAMS, *PVPP_BE_ENC_CX_CTRL_PARAMS;

// VBI Data enable control
typedef struct tagVPP_BE_ENC_CC_WSS_ENABLE_CTRL
{
    int    EnableTopFld;
    int    EnableBtmFld;
    int    EnableCont;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    int    EnableOnCVBS;
    int    EnableOnSVideo;
    int    EnableOnComponent;
#endif
}VPP_BE_ENC_CC_WSS_ENABLE_CTRL, *PVPP_BE_ENC_CC_WSS_ENABLE_CTRL;

typedef struct tagVPP_BE_ENC_VBI_ENABLE_CTRL
{
    VPP_BE_ENC_CC_WSS_ENABLE_CTRL  CCWssEnableCtrl;
    int                            EnHWCgmsCrcGen;
}VPP_BE_ENC_VBI_ENABLE_CTRL, *PVPP_BE_ENC_VBI_ENABLE_CTRL;

// Configuration parameters for VBI data (CC, CGMS, WSS)
typedef struct tagVPP_BE_ENC_VBI_CONFIG
{
    unsigned short  Height;
    unsigned short  DataStartPos;
    unsigned int  Freq;
    unsigned char   TopFieldLineNum;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
    unsigned char   FilterCtrl;
#endif
}VPP_BE_ENC_VBI_CONFIG, *PVPP_BE_ENC_VBI_CONFIG;

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
// TT enable control
typedef struct tagVPP_BE_ENC_TT_ENABLE_CTRL
{
    int    EnableTT;
    int    BitOrder;
    int    EnableOnCVBS;
    int    EnableOnSVideo;
    int    EnableOnComponent;
}VPP_BE_ENC_TT_ENABLE_CTRL, *PVPP_BE_ENC_TT_ENABLE_CTRL;

// Configuration parameters for TT
typedef struct tagVPP_BE_ENC_TT_CONFIG
{
    unsigned short  Height;
    unsigned short  DataStartPos;
    unsigned int  Freq;
    unsigned char   TTBytes;
}VPP_BE_ENC_TT_CONFIG, *PVPP_BE_ENC_TT_CONFIG;
#endif

// DAC control data
typedef struct tagVPP_BE_ENC_DAC_CTRL
{
    int DacMode;
    int OvSmplFact;
}VPP_BE_ENC_DAC_CTRL, *PVPP_BE_ENC_DAC_CTRL;

/*-----------------------------------------------------------------------------
 * Function Prototypes
 *-----------------------------------------------------------------------------
 */
int BE_ENC_LoadDefaultVal(THINVPP_OBJ *vpp_obj);
int BE_ENC_SetDacUsage(THINVPP_OBJ *vpp_obj, int DacGrp, int DacMode);
int BE_ENC_SetDacVoltage(THINVPP_OBJ *vpp_obj, int DacGrp, int OutRes);
int BE_ENC_SetDacOversample(THINVPP_OBJ *vpp_obj, int DacGrp, int OvSmplFact);
int BE_ENC_SetSDTimingParams (THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_TIMING_PARAMS pSDTimingParams);
int BE_ENC_SetHDTimingParams (THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_TIMING_PARAMS pHDTimingParams);
int BE_ENC_SetCvbsSVideoParams(THINVPP_OBJ *vpp_obj, int SdOutFmt, PVPP_BE_ENC_CVBS_SVIDEO_PARAMS pCvbsSVideoParams);
int BE_ENC_SetSDComponentParams(THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_COMPONENT_PARAMS pCompParams);
int BE_ENC_SetHDComponentParams(THINVPP_OBJ *vpp_obj, int OutRes, PVPP_BE_ENC_COMPONENT_PARAMS pCompParams);
int BE_ENC_SetHDCxOutCtrl (THINVPP_OBJ *vpp_obj, int CxOutMode, PVPP_BE_ENC_CX_CTRL_PARAMS pCXOutCtrl);
int BE_ENC_SetSDCxOutCtrl (THINVPP_OBJ *vpp_obj, int CxOutMode, PVPP_BE_ENC_CX_CTRL_PARAMS pCXOutCtrl);
int BE_ENC_SetCVPathFltrParams (THINVPP_OBJ *vpp_obj, PVPP_BE_ENC_CV_PATH_FLTR_PARAMS pCVPathFltrParams);
int BE_ENC_SetSDInpMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char InpMute, int Update);
int BE_ENC_SetHDInpMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char InpMute, int Update);
int BE_ENC_SetSDOutMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char OutMute, int Update);
int BE_ENC_SetHDOutMuteCtrl(THINVPP_OBJ *vpp_obj, unsigned char OutMute, int Update);
#endif /* __VPP_BE_ENC_H__ */
