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

#ifndef __VPPDEINTPRV__
#define __VPPDEINTPRV__

#include "vpp_fe_deintcfg.h"
#include "vpp_fe_deint.h"

/*-----------------------------------------------------------------------------
 * Macros
 *-----------------------------------------------------------------------------
 */
/*load register default value by name*/
#define WRITE_VPDEINT_DEFAULT_VAL(RegName, DefValues) \
        THINVPP_BCMBUF_Write(thinvpp_obj->pVbiBcmBuf, thinvpp_obj->base_addr + (RegName << 2), DefValues.REG_##RegName)

//////////////////////////////DEFAULT CFG VALUES/////////////////////////////////////////////

/*-----------------------------------------------------------------------------
 * Globals
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Structure Definitions for Video Processor
 *-----------------------------------------------------------------------------
 */

typedef struct tagVP_DEINT_MODE_REG {
    REG_WIDTH Mode                           : 3;
    REG_WIDTH reserved                       : 4;
    REG_WIDTH FiPol                          : 1;
}VP_DEINT_MODE_REG;

typedef union tagVP_DEINT_MODE_BITS {
    VP_DEINT_MODE_REG Bits;
    REG_WIDTH Value;
}VP_DEINT_MODE_BITS;

typedef struct tagVP_CTRL_FIFO_CTRL {
    REG_WIDTH Rst                            : 1;
    REG_WIDTH WenMode                        : 1;
    REG_WIDTH Mode                           : 2;
    REG_WIDTH ManualReset                    : 1;
    REG_WIDTH AutoReset                      : 1;
    REG_WIDTH VpEnable                       : 1;
    REG_WIDTH DeintEnable                    : 1;
}VP_CTRL_FIFO_CTRL;

typedef union tagVP_CTRL_FIFO_CTRL_BITS {
    VP_CTRL_FIFO_CTRL Bits;
    REG_WIDTH Value;
}VP_CTRL_FIFO_CTRL_BITS;

/*-----------------------------------------------------------------------------
 * Structure Definitions for Deinterlacer
 *-----------------------------------------------------------------------------
 */

//////////////////////////////////////////////////////////
typedef struct tagDEINT_STM_CTRL1_REG {
    REG_WIDTH LumaVidCtrl                      : 2;
    REG_WIDTH ChromaVidCtrl                    : 2;
    REG_WIDTH LumaFlmCtrl                      : 2;
    REG_WIDTH ChromaFlmCtrl                    : 2;
}DEINT_STM_CTRL1_REG;


typedef struct tagDEINT_STM_CTRL2_REG {
    REG_WIDTH LumaChromaYMotionSel             : 3;
    REG_WIDTH LumaChromaCMotionSel             : 3;
    REG_WIDTH TempTapSelVidMotion              : 2;
}DEINT_STM_CTRL2_REG;

typedef union tagDEINT_STM_CTRL1_REG_BITS {
    DEINT_STM_CTRL1_REG Bits;
    REG_WIDTH Value;
}DEINT_STM_CTRL1_REG_BITS;

typedef union tagDEINT_STM_CTRL2_REG_BITS {
    DEINT_STM_CTRL2_REG Bits;
    REG_WIDTH Value;
}DEINT_STM_CTRL2_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_VI_CTRL_REG {
    REG_WIDTH EnShallowMinRej                : 1;
    REG_WIDTH EnSlope                        : 1;
    REG_WIDTH EnVarMeasure                   : 1;
    REG_WIDTH EnHighPassChar                 : 1;
    REG_WIDTH EnVectInterpol                 : 1;
    REG_WIDTH EnInterpolLumTrans             : 1;
    REG_WIDTH EnShallowMinDistFromVert       : 1;

}DEINT_VI_CTRL_REG;

typedef union tagDEINT_VI_CTRL_REG_BITS {
    DEINT_VI_CTRL_REG Bits;
    REG_WIDTH Value;
}DEINT_VI_CTRL_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_MCB_CTRL_REG1 {
    REG_WIDTH FrmMotionSelCurrFld            : 4;
    REG_WIDTH FrmMotionSelPrevFld            : 2;
    REG_WIDTH CombFrmMotionSelCurrAndPrev    : 2;
}DEINT_MCB_CTRL_REG1;

typedef union tagDEINT_MCB_CTRL_REG1_BITS {
    DEINT_MCB_CTRL_REG1 Bits;
    REG_WIDTH Value;
}DEINT_MCB_CTRL_REG1_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_MCB_CTRL_REG2 {
    REG_WIDTH MotionComb                     : 2;
    REG_WIDTH MotionReCirCtrl                : 2;
    REG_WIDTH WegtAvForMotionRecCirCtrl      : 4;
}DEINT_MCB_CTRL_REG2;

typedef union tagDEINT_MCB_CTRL_REG2_BITS {
    DEINT_MCB_CTRL_REG2 Bits;
    REG_WIDTH Value;
}DEINT_MCB_CTRL_REG2_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_MCB_CTRL_REG3 {
    REG_WIDTH HorizExpMotionCtrl             : 2;
    REG_WIDTH FxdThres32FilmOutput           : 1;
    REG_WIDTH GradThres32FilmOutput          : 1;
}DEINT_MCB_CTRL_REG3;

typedef union tagDEINT_MCB_CTRL_REG3_BITS {
    DEINT_MCB_CTRL_REG3 Bits;
    REG_WIDTH Value;
}DEINT_MCB_CTRL_REG3_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_MOT_ENG_CTRL_REG1 {
    REG_WIDTH MADEngCtrl                     : 2;
    REG_WIDTH MAD2EngCtrl                    : 4;
    REG_WIDTH MAXEngCtrl                     : 2;
}DEINT_MOT_ENG_CTRL_REG1;

typedef union tagDEINT_MOT_ENG_CTRL_REG1_BITS {
    DEINT_MOT_ENG_CTRL_REG1 Bits;
    REG_WIDTH Value;
}DEINT_MOT_ENG_CTRL_REG1_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_MOT_ENG_CTRL_REG2 {
    REG_WIDTH VidFldMotionEngCtrl            : 3;
    REG_WIDTH ChromaMotionEngCtrl            : 2;
}DEINT_MOT_ENG_CTRL_REG2;

typedef union tagDEINT_MOT_ENG_CTRL_REG2_BITS {
    DEINT_MOT_ENG_CTRL_REG2 Bits;
    REG_WIDTH Value;
}DEINT_MOT_ENG_CTRL_REG2_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_CTRL_REG {
    REG_WIDTH EnSplitZoneDet32               : 1;
    REG_WIDTH EnSplitZoneDet22               : 1;
    REG_WIDTH EnTopZoneDet32                 : 1;
    REG_WIDTH EnTopZoneDet22                 : 1;
    REG_WIDTH EnPixelExcl32                  : 1;
    REG_WIDTH EnPixelExcl22                  : 1;
    REG_WIDTH EnPixelExclAuxCad              : 1;
}DEINT_FLM_CAD_CTRL_REG;

typedef union tagDEINT_FLM_CAD_CTRL_REG_BITS {
    DEINT_FLM_CAD_CTRL_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_CTRL_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_DET_MODE_REG1 {
    REG_WIDTH En2224Det                      : 1;
    REG_WIDTH En2332Det                      : 1;
    REG_WIDTH En32322Det                     : 1;
    REG_WIDTH En55Det                        : 1;
    REG_WIDTH En64Det                        : 1;
    REG_WIDTH En87Det                        : 1;
    REG_WIDTH EnPrgCad1Det                   : 1;
    REG_WIDTH EnPrgCad2Det                   : 1;
}DEINT_FLM_CAD_DET_MODE_REG1;

typedef struct tagDEINT_FLM_CAD_DET_MODE_REG2 {
    REG_WIDTH En32CadDet                     : 1;
    REG_WIDTH En22CadDet                     : 1;
}DEINT_FLM_CAD_DET_MODE_REG2;

typedef union tagDEINT_FLM_CAD_DET_MODE_REG1_BITS {
    DEINT_FLM_CAD_DET_MODE_REG1 Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_DET_MODE_REG1_BITS;

typedef union tagDEINT_FLM_CAD_DET_MODE_REG2_BITS {
    DEINT_FLM_CAD_DET_MODE_REG2 Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_DET_MODE_REG2_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_PROG_FLAG_REG {
    REG_WIDTH EnDinPixFrameMADThresh         : 1;
    REG_WIDTH EnFxdGblMotionThresh           : 1;
    REG_WIDTH EnPixelExclusion               : 1;
    REG_WIDTH EnSmallFxdWin                  : 1;
}DEINT_FLM_CAD_PROG_FLAG_REG;

typedef union tagDEINT_FLM_CAD_PROG_FLAG_REG_BITS {
    DEINT_FLM_CAD_PROG_FLAG_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_PROG_FLAG_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_32CTRL1_REG {
    REG_WIDTH EnWveErrSig1For32Exit          : 1;
    REG_WIDTH EnWveErrSig2For32Exit          : 1;
    REG_WIDTH EnDynFldExitFor32Exit          : 1;
    REG_WIDTH EnPrevFldExitFor32Exit         : 1;
    REG_WIDTH EnWithinFldExitFor32Exit       : 1;
    REG_WIDTH EnNoiseCalibFrmMotionFor32     : 1;
    REG_WIDTH EnPostExitFor32                : 1;
    REG_WIDTH En32DetForProgInput            : 1;
}DEINT_FLM_CAD_32CTRL1_REG;

typedef struct tagDEINT_FLM_CAD_32CTRL2_REG {
    REG_WIDTH BoolOperToCtrlEntryInto32      : 4;
    REG_WIDTH BoolOperToCtrlExitFrom32       : 4;
}DEINT_FLM_CAD_32CTRL2_REG;

typedef union tagDEINT_FLM_CAD_32CTRL1_REG_BITS {
    DEINT_FLM_CAD_32CTRL1_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_32CTRL1_REG_BITS;

typedef union tagDEINT_FLM_CAD_32CTRL2_REG_BITS {
    DEINT_FLM_CAD_32CTRL2_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_32CTRL2_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_22CTRL_REG {
    REG_WIDTH EnWveErrSig1For22Exit          : 1;
    REG_WIDTH EnWveErrSig2For22Exit          : 1;
    REG_WIDTH EnDynFldExitFor22Exit          : 1;
    REG_WIDTH EnPrevFldExitFor22Exit         : 1;
    REG_WIDTH EnWithinFldExitFor22Exit       : 1;
}DEINT_FLM_CAD_22CTRL_REG;

typedef union tagDEINT_FLM_CAD_22CTRL_REG_BITS {
    DEINT_FLM_CAD_22CTRL_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_22CTRL_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_SPLCAD_CTRL1_REG {
    REG_WIDTH EnWveErrSig1ForSCExit          : 1;
    REG_WIDTH EnWveErrSig2ForSCExit          : 1;
    REG_WIDTH EnDynFldExitForSCExit          : 1;
    REG_WIDTH EnPrevFldExitForSCExit         : 1;
    REG_WIDTH EnWithinFldExitForSCExit       : 1;
    REG_WIDTH EnGradFrmMotionForSCEntry      : 1;
    REG_WIDTH                                : 2;
}DEINT_FLM_CAD_SPLCAD_CTRL1_REG;

typedef struct tagDEINT_FLM_CAD_SPLCAD_CTRL2_REG {
    REG_WIDTH BoolOperToCtrlEntryIntoSC      : 4;
    REG_WIDTH BoolOperToCtrlExitFromSC       : 4;
}DEINT_FLM_CAD_SPLCAD_CTRL2_REG;

typedef union tagDEINT_FLM_CAD_SPLCAD_CTRL1_REG_BITS {
    DEINT_FLM_CAD_SPLCAD_CTRL1_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_SPLCAD_CTRL1_REG_BITS;

typedef union tagDEINT_FLM_CAD_SPLCAD_CTRL2_REG_BITS {
    DEINT_FLM_CAD_SPLCAD_CTRL2_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_SPLCAD_CTRL2_REG_BITS;

//////////////////////////////////////////////////////////

typedef struct tagDEINT_FLM_CAD_SPL_CAD_LEN_REG {
    REG_WIDTH LenOfProgCadPat0       : 4;
    REG_WIDTH LenOfProgCadPat1       : 4;
}DEINT_FLM_CAD_SPL_CAD_LEN_REG;

typedef union tagDEINT_FLM_CAD_SPL_CAD_LEN_REG_BITS {
    DEINT_FLM_CAD_SPL_CAD_LEN_REG Bits;
    REG_WIDTH Value;
}DEINT_FLM_CAD_SPL_CAD_LEN_REG_BITS;

#endif // __VPPDEINTPRV__
