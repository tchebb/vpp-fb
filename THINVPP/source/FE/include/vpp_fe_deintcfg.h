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

#ifndef	__VPP_DEINT_CFG__
#define	__VPP_DEINT_CFG__

/*-----------------------------------------------------------------------------
 * Macros
 *-----------------------------------------------------------------------------
 */

#define DEINT_NUM_UNITS     1

#define VPP_DEINTHD_MEMSIZE               (unsigned short)0x77F
#define VPP_DEINTSD_MEMSIZE               (unsigned short)0x2CF


//Deint VI Modes

/*
 * Deint Vector Interpolation Selection
 */
#define VPP_DEINTVI_NONE                               0x00
#define VPP_DEINTVI_REJECT                             0x01
#define VPP_DEINTVI_ENABLE_SLOPE                       0x02
#define VPP_DEINTVI_ENABLE_VARIANCE                    0x04
#define VPP_DEINTVI_ENABLE_HPF                         0x08
#define VPP_DEINTVI_ENABLE_DIAG_INTERPOL               0x10
#define VPP_DEINTVI_CTRL_INTERPOL_ANGLE_BASED_ON_EDGE  0x20
#define VPP_DEINTVI_SEL_MINIMA_FAR_AWAY_FROM_VERTICAL  0x40

#define VPP_DEINTVI_ALL             (VPP_DEINTVI_REJECT                    | \
                                      VPP_DEINTVI_ENABLE_SLOPE              | \
                                      VPP_DEINTVI_ENABLE_VARIANCE           | \
                                      VPP_DEINTVI_ENABLE_DIAG_INTERPOL      | \
                                      VPP_DEINTVI_CTRL_INTERPOL_ANGLE_BASED_ON_EDGE | \
                                      VPP_DEINTVI_SEL_MINIMA_FAR_AWAY_FROM_VERTICAL)

#define VPP_DEINTVI_AGGRESSIVE      (VPP_DEINTVI_REJECT                    | \
                                      VPP_DEINTVI_ENABLE_VARIANCE           | \
                                      VPP_DEINTVI_ENABLE_DIAG_INTERPOL      | \
                                      VPP_DEINTVI_CTRL_INTERPOL_ANGLE_BASED_ON_EDGE | \
                                      VPP_DEINTVI_SEL_MINIMA_FAR_AWAY_FROM_VERTICAL)

/*-----------------------------------------------------------------------------
 * Enums, Structures and Unions
 *-----------------------------------------------------------------------------
 */

///////////////////////////////////////ENUMs////////////////////////////////////////////////////////
//Deint Mode
typedef enum tagVPP_DEINTCFG_MODE
{
    VPP_DEINTMODE_BYPASS=0,
    VPP_DEINTMODE_SPATIAL_NEXT,
    VPP_DEINTMODE_SPATIAL_CURR,
    VPP_DEINTMODE_PROSCAN240,
    VPP_DEINTMODE_TEMPORAL_AVG_NEXT_PREV,
    VPP_DEINTMODE_TEMPORAL_NEXT,
    VPP_DEINTMODE_TEMPORAL_PREV,
    VPP_DEINTMODE_MA_3D

} VPP_DEINTCFG_MODE;

typedef enum tagVPP_DEINTCFG_FIFO_MODE
{
    VPP_DEINTDEMUX_FIFO_FREQ_RCLK_GT_2FREQ_WCLK = 0,
    VPP_DEINTDEMUX_FIFO_FREQ_RCLK_EQ_FREQ_WCLK,
    VPP_DEINTDEMUX_FIFO_FREQ_RCLK_EQ_2FREQ_WCLK,
    VPP_DEINTDEMUX_FIFO_FREQ_RCLK_EQ_4FREQ_WCLK

} VPP_DEINTCFG_FIFO_MODE;

typedef enum tagVPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL_ENUM
{
    VPP_DEINTMOTION_ADAPTIVE = 0,
    VPP_DEINTFORCED_SPATIAL,
    VPP_DEINTFORCED_TEMPORAL

}VPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL_ENUM;

typedef enum tagVPP_DEINTCFG_SPATIO_TEMP_MIXER_LUMA_CHROMA_SEL
{
    VPP_DEINTCFG_MAD2_ENG_MODE_LUMA_CHROMA_SEL_0 = 0x0,
    VPP_DEINTCFG_MAD2_ENG_MODE_LUMA_CHROMA_SEL_1,
    VPP_DEINTCFG_MAD2_ENG_MODE_LUMA_CHROMA_SEL_2,
    VPP_DEINTCFG_MAD2_ENG_MODE_LUMA_CHROMA_SEL_3,
    VPP_DEINTCFG_MAD2_ENG_MODE_LUMA_CHROMA_SEL_4,
    VPP_DEINTCFG_MAD2_ENG_MODE_LUMA_CHROMA_SEL_5

}VPP_DEINTCFG_SPATIO_TEMP_MIXER_LUMA_CHROMA_SEL;

typedef enum tagVPP_DEINTCFG_TEMP_TAP_SEL
{
    VPP_DEINTAVG_NXT_AND_PREV_FLD = 0,
    VPP_DEINTNXT_FLD,
    VPP_DEINTPREV_FLD,
    VPP_DEINTNXT_FLD_AND_PREV_FLD

}VPP_DEINTCFG_TEMP_TAP_SEL;

typedef enum tagVPP_DEINTCFG_FRAME_MOTION_CURR_FIELD
{
    VPP_DEINTUSE_MAD_ENGINE = 0,
    VPP_DEINTUSE_MAX_ENGINE,
    VPP_DEINTUSE_MEAN_OF_MAD_AND_MAX_ENGINES,
    VPP_DEINTUSE_MAX_OF_MAD_AND_MAX_ENGINES,
    VPP_DEINTUSE_ADAPT_BN_MAD_AND_MAX_ENGINES,
    VPP_DEINTUSE_ADAPT_BN_MEAN_OF_MAD_AND_MAX_ENGINES,
    VPP_DEINTUSE_ADAPT_BN_MAX_OF_MAD_AND_MAX_ENGINES,
    VPP_DEINTUSE_MAD2_ENGINES,
    VPP_DEINTUSE_MAX_ENGINES,
    VPP_DEINTUSE_MEAN_OF_MAD2_AND_MAX_ENGINES,
    VPP_DEINTUSE_MAX_OF_MAD2_AND_MAX_ENGINES,
    VPP_DEINTUSE_ADAPT_BN_MAD2_AND_MAX_ENGINES,
    VPP_DEINTUSE_ADAPT_BN_MEAN_OF_MAD2_AND_MAX_ENGINES,
    VPP_DEINTUSE_ADAPT_BN_MAX_OF_MAD2_AND_MAX_ENGINES

} VPP_DEINTCFG_FRAME_MOTION_CURR_FIELD;

typedef enum tagVPP_DEINTCFG_FRAME_MOTION_PREV_FIELD
{
    VPP_DEINTMEAN_OF_PREV_TOP_AND_BOT_MOT = 0,
    VPP_DEINTMAX_OF_PREV_TOP_AND_BOT_MOT,
    VPP_DEINTMAX_OF_PREV_TOP_AND_BOT_MOT_AND_2FLD_PREV_MOT,
    VPP_DEINTMAX_OF_2FLD_PREV_AND_MEAN_OF_PREV_TOP_AND_BOT_MOT

} VPP_DEINTCFG_FRAME_MOTION_PREV_FIELD;

typedef enum tagVPP_DEINTCFG_FRAME_MOTION_CTRL
{
    VPP_DEINTCURR_FRAME_MOT = 0,
    VPP_DEINTMAX_OF_CURR_AND_PREV_FRAME_MOT,
    VPP_DEINTMEAN_OF_CURR_AND_PREV_FRAME_MOT,
    VPP_DEINTPREV_FRAME_MOT

} VPP_DEINTCFG_FRAME_MOTION_CTRL;

typedef enum tagVPP_DEINTCFG_MOTION_COMB_CTRL
{
    VPP_DEINTUSE_FRAME_MOT = 0,
    VPP_DEINTUSE_FLD_MOT,
    VPP_DEINTUSE_MAX_OF_FRAME_AND_FLD_MOT,
    VPP_DEINTUSE_MAX_OF_FRAME_AND_FLD_MOT_WHEN_GBL_FRAME_MOT_EXCEED_THRES

} VPP_DEINTCFG_MOTION_COMB_CTRL;

typedef enum tagVPP_DEINTCFG_RECIRCUL_CTRL
{
    VPP_DEINTUSE_CURR_FRAME_MOT = 0,
    VPP_DEINTUSE_CURR_FRAME_MOT_WHEN_GTR_THAN_PREV_MOT = 2,

} VPP_DEINTCFG_RECIRCUL_CTRL;

typedef enum tagVPP_DEINTCFG_HORIZ_EXP_MODE
{
    VPP_DEINTNO_EXP = 0,
    VPP_DEINTUSE_3_PIX_EXP,
    VPP_DEINTUSE_5_PIX_EXP,
    VPP_DEINTUSE_7_PIX_EXP

} VPP_DEINTCFG_HORIZ_EXP_MODE;

typedef enum tagVPP_DEINTCFG_MOT_BIT_CTRL_FOR_FLM_32_DET
{
    VPP_DEINTUSE_MAD_ENGINE_FOR_FLM_32_DET = 0,
    VPP_DEINTUSE_MAD2_ENGINE_FOR_FLM_32_DET

} VPP_DEINTCFG_MOT_BIT_CTRL_FOR_FLM_32_DET;

typedef enum tagVPP_DEINTCFG_MAD_ENG_CTRL
{
    VPP_DEINTUSE_3x3_WIN_MAD_ENG_CTRL = 0,
    VPP_DEINTUSE_5x3_WIN_MAD_ENG_CTRL,
    VPP_DEINTUSE_7x3_WIN_MAD_ENG_CTRL

} VPP_DEINTCFG_MAD_ENG_CTRL;

typedef enum tagVPP_DEINTCFG_MAD2_ENG_CTRL
{
    VPP_DEINTCFG_MAD2_ENG_MODE_0 = 0x0,
    VPP_DEINTCFG_MAD2_ENG_MODE_1,
    VPP_DEINTCFG_MAD2_ENG_MODE_2,
    VPP_DEINTCFG_MAD2_ENG_MODE_3,
    VPP_DEINTCFG_MAD2_ENG_MODE_4,
    VPP_DEINTCFG_MAD2_ENG_MODE_5,
    VPP_DEINTCFG_MAD2_ENG_MODE_6,
    VPP_DEINTCFG_MAD2_ENG_MODE_7,
    VPP_DEINTCFG_MAD2_ENG_MODE_8,
    VPP_DEINTCFG_MAD2_ENG_MODE_9

} VPP_DEINTCFG_MAD2_ENG_CTRL;

typedef enum tagVPP_DEINTCFG_MAX_ENG_CTRL
{
    VPP_DEINTUSE_1x1_WIN_MAX_ENG_CTRL = 0,
    VPP_DEINTUSE_3x3_WIN_MAX_ENG_CTRL,
    VPP_DEINTUSE_5x3_WIN_MAX_ENG_CTRL,
    VPP_DEINTUSE_7x3_WIN_MAX_ENG_CTRL

} VPP_DEINTCFG_MAX_ENG_CTRL;

typedef enum tagVPP_DEINTCFG_VID_FLD_MOT_ENG_CTRL
{
    VPP_DEINTMAX_MOT_MAX_DET = 0,
    VPP_DEINTMAX_MOT_MIN_DET,
    VPP_DEINTMIN_MOT_MAX_DET,
    VPP_DEINTMIN_MOT_MIN_DET,
    VPP_DEINTMAX_MOT,
    VPP_DEINTMIN_MOT

} VPP_DEINTCFG_VID_FLD_MOT_ENG_CTRL;

typedef enum tagVPP_DEINTCFG_CHROMA_MOT_ENG_CTRL
{
    VPP_DEINTUSE_1x3_WIN_CHROMA_MOT_ENG_CTRL = 0,
    VPP_DEINTUSE_3x3_WIN_CHROMA_MOT_ENG_CTRL,
    VPP_DEINTUSE_5x3_WIN_CHROMA_MOT_ENG_CTRL,
    VPP_DEINTUSE_7x3_WIN_CHROMA_MOT_ENG_CTRL

} VPP_DEINTCFG_CHROMA_MOT_ENG_CTRL;

typedef enum tagVPP_DEINTCFG_BOOLEAN_OPER_FOR_FILM_CAD_LKUP
{
    VPP_DEINTFRAME_BASED_LKUP           = 10,
    VPP_DEINTFIELD_BASED_LKUP           = 12,
    VPP_DEINTFRAME_AND_FIELD_BASED_LKUP = 8,
    VPP_DEINTFRAME_OR_FIELD_BASED_LKUP  = 14

}VPP_DEINTCFG_BOOLEAN_OPER_FOR_FILM_CAD_LOOKUP;

typedef enum tagVPP_DEINTCFG_CLNT_MODE
{
    VPP_DEINTCLNT_20BIT_MODE = 0,
    VPP_DEINTCLNT_26BIT_MODE

}VPP_DEINTCFG_CLNT_MODE;

///////////////////////////////////////STRUCT////////////////////////////////////////////////////////

//Deint Saptio-Temporal Mixer Control Parameters
typedef struct tagVPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL
{
    VPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL_ENUM       LumaCtrlForVideoPix;
    VPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL_ENUM       ChromaCtrlForVideoPix;
    VPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL_ENUM       LumaCtrlForFilmPix;
    VPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL_ENUM       ChromaCtrlForFilmPix;

    VPP_DEINTCFG_SPATIO_TEMP_MIXER_LUMA_CHROMA_SEL LumaChromaMotSelForY;
    //VPP_DEINTCFG_SPATIO_TEMP_MIXER_LUMA_CHROMA_SEL LumaChromaMotSelForC;

    VPP_DEINTCFG_TEMP_TAP_SEL                      TempTapSel;

}VPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL, *PVPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL;

//Deint Motion Combiner Control Parameters
typedef struct tagVPP_DEINTCFG_MOT_COM_CTRL_PARAMS
{
    VPP_DEINTCFG_FRAME_MOTION_CURR_FIELD           FrameMotCurrField;
    VPP_DEINTCFG_FRAME_MOTION_PREV_FIELD           FrameMotPrevField;
    VPP_DEINTCFG_FRAME_MOTION_CTRL                 FrameMotCtrl;
    VPP_DEINTCFG_MOTION_COMB_CTRL                  MotCombCtrl;
    VPP_DEINTCFG_RECIRCUL_CTRL                     RecirculCtrl;
    unsigned char                                           WeightAvValue;
    VPP_DEINTCFG_HORIZ_EXP_MODE                    HorizExpMode;
    VPP_DEINTCFG_MOT_BIT_CTRL_FOR_FLM_32_DET       FixFlm32DetMode;
    VPP_DEINTCFG_MOT_BIT_CTRL_FOR_FLM_32_DET       GradFlm32DetMode;

} VPP_DEINTCFG_MOT_COM_CTRL_PARAMS, *PVPP_DEINTCFG_MOT_COM_CTRL_PARAMS;

//Deint Motion Engine Control Parameters
typedef struct tagVPP_DEINTCFG_MOT_ENG_CTRL_PARAMS
{
    VPP_DEINTCFG_MAD_ENG_CTRL                      MadEngCtrl;
    VPP_DEINTCFG_MAD2_ENG_CTRL                     Mad2EngCtrl;
    VPP_DEINTCFG_MAX_ENG_CTRL                      MaxEngCtrl;
    VPP_DEINTCFG_VID_FLD_MOT_ENG_CTRL              VidFldMotEngCtrl;
    VPP_DEINTCFG_CHROMA_MOT_ENG_CTRL               ChromaMotEngCtrl;

} VPP_DEINTCFG_MOT_ENG_CTRL_PARAMS, *PVPP_DEINTCFG_MOT_ENG_CTRL_PARAMS;

//Deint Preset Mode Parameters
typedef struct tagVPP_DEINTCFG_DEINT_PRESET_MODE_PARAMS
{
    VPP_DEINTCFG_MODE                              DeintMode;
    unsigned short                                          ViCtrl;
    PVPP_DEINTCFG_SPATIO_TEMP_MIXER_CTRL           pSpatioTemporalMixerCtrl;

} VPP_DEINTCFG_DEINT_PRESET_MODE_PARAMS, *PVPP_DEINTCFG_DEINT_PRESET_MODE_PARAMS;

//Deint Line/Pixel Exclusion for Film Cadence Detection
typedef struct tagVPP_DEINTCFG_EXCLUSION_FOR_FILM_CAD_DET
{
    unsigned char NoOfLinesExclFromBottom;
    unsigned char NoOfLinesExclFromTop;
    unsigned char NoOfLinesExclFromRight;
    unsigned char NoOfLinesExclFromLeft;

}VPP_DEINTCFG_EXCLUSION_FOR_FILM_CAD_DET;

//Deint Field Buffer Control Parameters
typedef struct tagVPP_DEINTCFG_FB_CTRL_PARAMS
{
    VPP_DEINTCFG_CLNT_MODE     DeintSdramClntMode;

}VPP_DEINTCFG_FB_CTRL_PARAMS, *PVPP_DEINTCFG_FB_CTRL_PARAMS;

typedef struct tagVPP_DEINTCFG_FILM_CADENCE_CONTROL
{
    int    En32SplitZoneDet;
    int    En22SplitZoneDet;

    int    En32TopZoneDet;
    int    En22TopZoneDet;

    int    En32PixExclusion;
    int    En22PixExclusion;
    int    EnAuxCadPixExclusion;

}VPP_DEINTCFG_FILM_CADENCE_CONTROL;

typedef struct tagVPP_DEINTCFG_PROG_FLAG_CONTROL
{
    int	 UsePixFrameMotThresForProgFlagDet;
    int	 UseFixedGblMotThres;
    int	 UsePixExclusion;
    int	 UseSmallerFixedWin;

}VPP_DEINTCFG_PROG_FLAG_CONTROL;

typedef struct tagVPP_DEINTCFG_32FILM_CADENCE_CONTROL
{
    int	 UseWeaveErrSig1For32ModeExit;
    int	 UseWeaveErrSig2For32ModeExit;
    int	 UseDynamicFieldFor32ModeExit;
    int	 UsePrevFieldFor32ModeExit;
    int	 UseWithinFieldFor32ModeExit;
    int	 UseNoiseCalibFrameMotFor32Mode;
    int	 EnPostExitFor32Mode;
    int	 EnProgInput32Detection;

    VPP_DEINTCFG_BOOLEAN_OPER_FOR_FILM_CAD_LOOKUP  BoolOperLkupFor32ModeEntry;
    VPP_DEINTCFG_BOOLEAN_OPER_FOR_FILM_CAD_LOOKUP  BoolOperLkupFor32ModeExit;

    unsigned char   NoOfFldsInHardBuildUpPhaseFor32ModeEntry;
    unsigned char   NoOfFldsInSoftBuildUpPhaseFor32ModeEntry;

}VPP_DEINTCFG_32FILM_CADENCE_CONTROL;

typedef struct tagVPP_DEINTCFG_22FILM_CADENCE_CONTROL
{
    int	 UseWeaveErrSig1For22ModeExit;
    int	 UseWeaveErrSig2For22ModeExit;
    int	 UseDynamicFieldFor22ModeExit;
    int	 UsePrevFieldFor22ModeExit;
    int	 UseWithinFieldFor22ModeExit;

    unsigned char    NoOfFldsInHardBuildUpPhaseFor22ModeEntry;
    unsigned char    NoOfFldsInSoftBuildUpPhaseFor22ModeEntry;

}VPP_DEINTCFG_22FILM_CADENCE_CONTROL;

typedef struct tagVPP_DEINTCFG_SPL_CADENCE_CONTROL
{
    int	 UseWeaveErrSig1ForSplCadModeExit;
    int	 UseWeaveErrSig2ForSplCadModeExit;
    int	 UseDynamicFieldForSplCadModeExit;
    int	 UsePrevFieldForSplCadModeExit;
    int	 UseWithinFieldForSplCadModeExit;
    int	 UseGradientFrameMotForSplCadModeExit;

    VPP_DEINTCFG_BOOLEAN_OPER_FOR_FILM_CAD_LOOKUP  BoolOperLkupForSplCadModeEntry;
    VPP_DEINTCFG_BOOLEAN_OPER_FOR_FILM_CAD_LOOKUP  BoolOperLkupForSplCadModeExit;

    unsigned char   NoOfFldsInHardBuildUpPhaseForSplCadModeEntry;
    unsigned char   NoOfFldsInSoftBuildUpPhaseForSplCadModeEntry;

    unsigned int  ProgCadPattern0;
    unsigned int  ProgCadPattern1;

    unsigned char   LenOfPattern0InFlds;
    unsigned char   LenOfPattern1InFlds;

}VPP_DEINTCFG_SPL_CADENCE_CONTROL;

#endif // __VPP_DEINT_CFG__
