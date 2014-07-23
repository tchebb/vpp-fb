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

#ifndef __VPP_DEINT_H__
#define __VPP_DEINT_H__

#include "thinvpp_api.h"
#include "thinvpp_module.h"

/*-----------------------------------------------------------------------------
 * Macros
 *-----------------------------------------------------------------------------
 */

#define VPP_DEINTMAX_SIZE_OF_SBF_LIST          (16)


/*-----------------------------------------------------------------------------
 * Enums, Structures and Unions
 *-----------------------------------------------------------------------------
 */
typedef struct tagVPP_DEINTCAPS
{
    unsigned char   NumUnits;
    unsigned int  Flags;

} VPP_DEINTCAPS, *PVPP_DEINTCAPS;

typedef enum tagVPP_DEINTCADENCE_MODE_TYPE
{
    //Film Cadence Selection flags
    VPP_DEINTDISABLE_FLM_CAD = 0x000,
    VPP_DEINT32_FLM_CAD      = 0x001,
    VPP_DEINT22_FLM_CAD      = 0x002,
    VPP_DEINT2224_FLM_CAD    = 0x004,
    VPP_DEINT2332_FLM_CAD    = 0x008,
    VPP_DEINT32322_FLM_CAD   = 0x010,
    VPP_DEINT55_FLM_CAD      = 0x020,
    VPP_DEINT64_FLM_CAD      = 0x040,
    VPP_DEINT87_FLM_CAD      = 0x080,
    VPP_DEINTPROG_FLM_CAD1   = 0x100,
    VPP_DEINTPROG_FLM_CAD2   = 0x200,
    VPP_DEINTSELECT_ALL_CAD  = 0x3FF

}VPP_DEINTCADENCES;

typedef enum tagVPP_DEINTPRESET_MODE
{
    VPP_DEINTPRESET_2D_LINEAR = 0,
    VPP_DEINTPRESET_2D_VECTOR,
    VPP_DEINTPRESET_3D_LINEAR,
    VPP_DEINTPRESET_3D_VECTOR,
    VPP_DEINTPRESET_3D_MA_LINEAR,
    VPP_DEINTPRESET_3D_MA_VECTOR,
    VPP_DEINTPRESET_2D_LINEAR_USE_CURR_FIELD,
    VPP_DEINTPRESET_2D_VECTOR_USE_CURR_FIELD,
    VPP_DEINTPRESET_BYPASS_AND_FLD_BUFF_DISABLED,
    VPP_DEINTPRESET_BYPASS_AND_FLD_BUFF_ENABLED, //Support NR functionality
    VPP_DEINTPRESET_NONE, //Id not used currently in Kyoto
    VPP_DEINTPRESET_MAX_PRESETS,

} VPP_DEINTPRESET_MODE, *PVPP_DEINTPRESET_MODE;

typedef enum tagVPP_DEINTFLD_BUFF_MODE
{
    VPP_DEINTFLD_BUFF_MODE_20BIT = 0,
    VPP_DEINTFLD_BUFF_MODE_26BIT

}VPP_DEINTFLD_BUFF_MODE;

#if 0
typedef enum tagVPP_DEINTVI_MODE
{
    VPP_DEINTMODE_OFF = 0,
    VPP_DEINTMODE_SAFE ,
    VPP_DEINTMODE_AGGRESSIVE

}VPP_DEINTVI_MODE;

typedef enum tagVPP_DEINTCHROMA_MOT_VID_MODE
{
    VPP_DEINTCHROMA_MOT_VID_SAME_AS_LUMA = 0,
    VPP_DEINTCHROMA_MOT_FIXED_2D,
    VPP_DEINTCHROMA_MOT_INDEP_CHROMA_MOT,
    VPP_DEINTCHROMA_MOT_MAX_OF_CHROMA_AND_LUMA_MOT

}VPP_DEINTCHROMA_MOT_VID_MODE;
#endif

typedef enum tagVPP_DEINT_INPUT_TYPE
{
    VPP_DEINT_INPUT_HD = 0,
    VPP_DEINT_INPUT_SD_NTSC,
    VPP_DEINT_INPUT_SD_PAL,
    VPP_DEINT_INPUT_MAX
}VPP_DEINT_INPUT_TYPE;

typedef struct tagVPP_DEINTSTATUS
{
    unsigned int  FilmCadenceDetFlag;

} VPP_DEINTSTATUS, *PVPP_DEINTSTATUS;
#if 0
/*
 * These Params are mainly based on the mode.
 * So they are combined with SetPresetMode().
 */
typedef struct tagVPP_DINT_PRESET_MODE_PARAMS
{
    VPP_DEINTVI_MODE               ViMode;
    VPP_DEINTCHROMA_MOT_VID_MODE   ChrMotVidMode;
    int                           ChrMotFlmMode;

}VPP_DINT_PRESET_MODE_PARAMS, *PVPP_DINT_PRESET_MODE_PARAMS;
#endif

/////////////////////////////THRESHOLD PARAMETERS///////////////////////////////////////////////////
typedef struct tagVPP_DEINT_THRES_PARAMS
{
    // Weave error thresholds
    unsigned char   InterFldDiffThresWveErrDet;                 // DIN29
    unsigned char   IntraFldGainThresForWveErrDet22FlmExit;     // DIN30
    unsigned char   IntraFldGainThresForWveErrDet22FlmEntry;    // DIN31

    unsigned char   InterFldDiffThresForWveErrDet22FlmSecExit;  // DIN32
    unsigned char   IntraFldDiffThresForWveErrDet22FlmSecExit;  // DIN33
    unsigned char   IntraFldGainThresForWveErrDet22FlmSecExit;  // DIN34

    // Noise Calibration thresholds
    unsigned int   NoiseCalibThresSADRegion0;                 // DIN42
    unsigned int   NoiseCalibThresSADRegion1;                 // DIN46
    unsigned int   NoiseCalibThresSADRegion2;                 // DIN50

    unsigned char    NoiseCalibFramePixMotThresBelowReg0;       // DIN53
    unsigned char    NoiseCalibFramePixMotThresBwReg0AndReg1;   // DIN54
    unsigned char    NoiseCalibFramePixMotThresBwReg1AndReg2;   // DIN55
    unsigned char    NoiseCalibFramePixMotThresAboveReg2;       // DIN56

    unsigned char    NoiseCalibFrameGblMotThresBelowReg0;       // DIN57
    unsigned char    NoiseCalibFrameGblMotThresBwReg0AndReg1;   // DIN58
    unsigned char    NoiseCalibFrameGblMotThresBwReg1AndReg2;   // DIN59
    unsigned char    NoiseCalibFrameGblMotThresAboveReg2;       // DIN60

    unsigned char    PixelThresFor32Det;                        // DIN61
    unsigned short   PostExitFineThresFor32;                    // DIN62
    unsigned char    PostExitCoarseThresFor32;                  // DIN64

    // Global thresholds for film detection
    unsigned char   NofInHardBldUpPh22Entry;                    // DIN77
    unsigned char   NofInSoftBldUpPh22Entry;                    // DIN78
    unsigned char   FixedGblFrameMotionThres;                   // DIN94
    unsigned char   LowerGblWeaveErrThres;                      // DIN95
    unsigned char   UpperGblWeaveErrThres;                      // DIN96

    unsigned char   GblWeaveErrThresFor32FilmModeExit;          // DIN97
    unsigned char   GblWeaveErrThresFor22FilmModeExit;          // DIN98
    unsigned char   GblWeaveErrThresForFilmModeExit;            // DIN99
    unsigned short  GblSecWeaveErrThres0ForFilmModeExit;        // DIN100
    unsigned short  GblSecWeaveErrThres1ForFilmModeExit;        // DIN102
    unsigned short  GblMotThresToCtrlFldMotion;                 // DIN104
}VPP_DEINT_THRES_PARAMS, *PVPP_DEINT_THRES_PARAMS;


typedef union tagVPP_VP_CLIENT_CLK
{
    struct {
        int    ClkEnable       : 1;
        int    WriteEnable     : 1;
        int    Read0Enable     : 1;
        int    Read1Enable     : 1;
        int    Reserved        :28;
    } field;

    int data;
} VPP_VP_CLIENT_CLK, *PVPP_VP_CLIENT_CLK;


typedef struct tagVPP_VP_CLIENT_SIZE
{
    int  ivRes;
    int  ihRes;
    int  IsProgressive;
}VPP_VP_CLIENT_SIZE,*PVPP_VP_CLIENT_SIZE;


///////////////////////////////////Advanced Deint Mode config parameters////////////////////////////////



typedef enum tagVPP_DEINTCHROMA_MOT_FLM_MODE
{
    VPP_DEINTCHROMA_MOT_FORCED_2D_DISABLE = 0,
    VPP_DEINTCHROMA_MOT_FORCED_2D_ENABLE

}VPP_DEINTCHROMA_MOT_FLM_MODE;
#if 0
typedef enum tagVPP_DEINTEXCL_PARAM_MODE
{
    VPP_DEINTEXCL_PARAM_MODE_NONE = 0,
    VPP_DEINTEXCL_PARAM_EXCLUSION_SEL,
    VPP_DEINTEXCL_PARAM_EXCLUSION_SEL_2ZONE

}VPP_DEINTEXCL_PARAM_MODE;

typedef enum tagVPP_DEINTUSER_CAD_MODE
{
    VPP_DEINTUSER_CAD_MODE_1 = 0,
    VPP_DEINTUSER_CAD_MODE_2

}VPP_DEINTUSER_CAD_MODE;
#endif
typedef struct tagVPP_DEINTADV_MD_PARAMS
{
    int      SmallMotFilmExit;         //SMFE
    int      EnablePostWveErrMode32;
    int      EnablePostWveErrMode22;
    int      EnablePostWveErrModeOther;
    int      EnableProgFlag;
    int      Enable32SMFE;             //Not used

    int      EnableIPodSplMode;        //special mode for Ipod
   int   EnableTemporalSplMode;    // special mode for Temporal

} VPP_DEINTADV_MD_PARAMS, *PVPP_DEINTADV_MD_PARAMS;

typedef struct tagVP_FB_CTRL_REG {
    REG_WIDTH FldBufReset                    : 1;
    REG_WIDTH WrMask                         : 1;
    REG_WIDTH RdMaskFldBufLow                : 1;
    REG_WIDTH RdMaskFldBufHigh               : 1;
    REG_WIDTH CrcCheckFldBufLow              : 1;
    REG_WIDTH CrcCheckFldBufHigh             : 1;
    REG_WIDTH DeintClientMode                : 1;
}VP_FB_CTRL_REG;

typedef union tagVP_FB_CTRL_BITS {
    VP_FB_CTRL_REG Bits;
    REG_WIDTH Value;
}VP_FB_CTRL_BITS;

///////////////////////////////////Advanced Deint Mode config parameters////////////////////////////////

/*-----------------------------------------------------------------------------
 * Function Prototypes
 *-----------------------------------------------------------------------------
 */
int FE_DEINT_SetVpDeintClientSize(THINVPP_OBJ* vpp_obj,PVPP_VP_CLIENT_SIZE pVpClientSize, int training);

#endif /*__VPP_DEINT_H__*/
