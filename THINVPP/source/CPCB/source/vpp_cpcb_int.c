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

#define _VPP_CPCB_INT_C_

#include "maddr.h"
#include "vpp.h"

#include "thinvpp_module.h"
#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_cpcb_int.h"
#include "vpp_cpcb_int_prv.h"

/*CPCB INT unit number validation*/
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
#define CHECK_INT_NUM(UnitNum)\
do{\
    if((UnitNum != VPP_CPCB_INT0) && (UnitNum != VPP_CPCB_INT2))\
        return MV_THINVPP_EBADPARAM;\
}while(0)

#else
#define CHECK_INT_NUM(UnitNum)\
do{\
    if((UnitNum != VPP_CPCB_INT0) && (UnitNum != VPP_CPCB_INT1))\
        return MV_THINVPP_EBADPARAM;\
}while(0)
#endif


/***************************************************************************************
 * FUNCTION: internal fuction to get the start address of an interlacer instance by unit number
 * PARAMS: CpcbUnit - INT unit number(INT0, INT1)
 * RETURN:  the start address
 ***************************************************************************************/
unsigned int INTERNAL_INT_GetRegStartAddr(THINVPP_OBJ *vpp_obj, int IntUnit)
{
    if(VPP_CPCB_INT0 == IntUnit)
        return (vpp_obj->base_addr + (CPCB0_INT_CTRL << 2));
    else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        return (vpp_obj->base_addr + (CPCB2_INT_CTRL << 2));
#else
        return (vpp_obj->base_addr + (CPCB1_INT_CTRL << 2));
#endif
}

/***************************************************************************************
 * FUNCTION: load the default register values of CPCB interlacer block
 * PARAMS: IntUnit - INT unit number(INT0, INT1)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB interlacer register values to BCM buffer
 ***************************************************************************************/
int CPCB_INT_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int IntUnit)
{
    CHECK_INT_NUM(IntUnit);

    if(VPP_CPCB_INT0 == IntUnit){
        WRITE_REG_DEFAULT_VAL_32BITS(RA_Vpp_CPCB0_FLD, gCpcb0IntDefValues);
        vpp_obj->cpcb.VppCpcb0IntCtrl = 0x00000000; //CPCB0_INT_CTRL

    }
    else if(VPP_CPCB_INT2 == IntUnit){
        WRITE_REG_DEFAULT_VAL_32BITS(RA_Vpp_CPCB2_FLD, gCpcb2IntDefValues);
        vpp_obj->cpcb.VppCpcb2IntCtrl = 0x00000000; //CPCB2_INT_CTRL

    }

    return(MV_THINVPP_OK);
}

/***************************************************************************************
 * FUNCTION: enable or disable interlacer in CPCB0 or CPCB1
 * PARAMS: IntUnit - INT unit number(INT0, INT1)
 *               Enable - 1: enable, 0: disable
 * RETURN:  1 - succeed
 *                others - failed to load CPCB interlacer register values to BCM buffer
 ***************************************************************************************/
int CPCB_INT_Enable(THINVPP_OBJ *vpp_obj, int IntUnit, unsigned int Enable)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    CHECK_INT_NUM(IntUnit);

    /*get register start address of the INT unit */
    RegAddr = INTERNAL_INT_GetRegStartAddr(vpp_obj, IntUnit);

    /*set CTRL register enable field to local buffer*/
    if (IntUnit == VPP_CPCB_INT0) {
        ((CPCB_INT_CTRL *)&(vpp_obj->cpcb.VppCpcb0IntCtrl))->field.Enable = Enable;
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, vpp_obj->cpcb.VppCpcb0IntCtrl);
    } else {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        ((CPCB_INT_CTRL *)&(vpp_obj->cpcb.VppCpcb2IntCtrl))->field.Enable = Enable;
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, vpp_obj->cpcb.VppCpcb2IntCtrl);
#else
        ((CPCB_INT_CTRL *)&(vpp_obj->cpcb.VppCpcb1IntCtrl))->field.Enable = Enable;
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, vpp_obj->cpcb.VppCpcb1IntCtrl);
#endif
    }

    return  RetVal;
}

/***************************************************************************************
 * FUNCTION: set interlacer parameters, include HVsync positions, VsampX and YC blank values
 * PARAMS: IntUnit - INT unit number(INT0, INT1)
 *               pParams - pointer to interlacer parameters structure
 * RETURN:  1 - succeed
 *                others - failed to load CPCB interlacer register values to BCM buffer
 ***************************************************************************************/
int CPCB_INT_SetParams(THINVPP_OBJ *vpp_obj, int IntUnit, PVPP_CPCB_INT_PARAMS pParams)
{
    unsigned int RegAddr;
    unsigned int LowBits, HighBits;
    unsigned int *pStructMember;
    int Count;
    int RetVal = MV_THINVPP_OK;

    CHECK_INT_NUM(IntUnit);

    /*get register address of the interlacer memory size register*/
    RegAddr = INTERNAL_INT_GetRegStartAddr(vpp_obj, IntUnit)  + OFF_CPCB_INT_MEMSIZE_L;

    /*get the low byte of memory size*/
    LowBits = GET_LOWEST_BYTE(pParams->MemSize);

    /*set low byte to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, LowBits)))
         return RetVal;

    /*get the high 4 bits of weight factor*/
    HighBits = pParams->MemSize >> 8;

    /*set high 4 bits to BCM buffer*/
    if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, HighBits)))
         return RetVal;

    /*get register address of FsampX register*/
    RegAddr = INTERNAL_INT_GetRegStartAddr(vpp_obj, IntUnit)  + OFF_CPCB_INT_FX_L;

    /*get pointer of FsampX in parameter structure*/
    pStructMember = (unsigned int*)pParams + 1;

    /*put all the remain structure members into buffers*/
    for(Count=0; Count<10;Count++){
        /*get low 8 bits*/
        LowBits = GET_LOWEST_BYTE(*pStructMember);

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, LowBits)))
             return RetVal;

        /*get high 4 bits*/
        HighBits = (*pStructMember) >> 8;

        if(MV_THINVPP_OK != (RetVal = THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, HighBits)))
         return RetVal;

        /*update address*/
	 RegAddr += 8;
	 pStructMember++;
    }

    return  RetVal;
}
