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

#define VPP_CPCB_OVL_C

#include "maddr.h"

#include "thinvpp_api.h"
#include "thinvpp_bcmbuf.h"
#include "vpp_cpcb_ovl.h"
#include "vpp_cpcb_ovl_prv.h"
#if (BERLIN_CHIP_VERSION >= BERLIN_C_2)
#include "vpp.h"
#endif


/***************************************************************************************
 * FUNCTION: load the default register values of CPCB OVL block
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL default values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_LoadDefaultVal(THINVPP_OBJ *vpp_obj, int OvlUnit)
{
    CHECK_OVL_NUM(OvlUnit);

    if(VPP_CPCB_OVL0 == OvlUnit){
        WRITE_REG_DEFAULT_VAL(CPCB0_VO_BASE_CLR_0, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_VO_BASE_CLR_1, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_VO_BASE_CLR_2, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_OO_FIX_0, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_OO_FIX_1, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_OO_FIX_2, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_OO_FIX0_0, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_OO_FIX0_1, gCpcb0OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB0_OO_FIX0_2, gCpcb0OvlDefValues);
    }else if(VPP_CPCB_OVL2 == OvlUnit){
        WRITE_REG_DEFAULT_VAL(CPCB2_OO_FIX_0, gCpcb2OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB2_OO_FIX_1, gCpcb2OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB2_OO_FIX_2, gCpcb2OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB2_OO_FIX0_0, gCpcb2OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB2_OO_FIX0_1, gCpcb2OvlDefValues);
        WRITE_REG_DEFAULT_VAL(CPCB2_OO_FIX0_2, gCpcb2OvlDefValues);
    }

    return MV_THINVPP_OK;
}


/***************************************************************************************
 * FUNCTION: set the OSD Overlay mode and domain
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               pZOrder - *pZOrder for layer1 channel selection, *(pZOrder+1) for layer2 channel selection.....
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetChannelOrder(THINVPP_OBJ *vpp_obj, int OvlUnit, int *pZOrder)
{
    unsigned int RegVal;
    int RetVal = MV_THINVPP_OK;

    CHECK_OVL_NUM(OvlUnit);

    /*get the address of the first register of OSD overlay*/
    if(VPP_CPCB_OVL0 == OvlUnit) {
        /*set layer 1&2 z-order */
        RegVal = *pZOrder + (*(pZOrder + 1) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB0_OO_LAY12 << 2),  RegVal);

        /*set layer 3&4 z-order */
        RegVal = *(pZOrder + 2) + (*(pZOrder + 3) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB0_OO_LAY34 << 2),  RegVal);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        /*set layer 5&6 z-order */
        RegVal = *(pZOrder + 4) + (*(pZOrder + 5) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB0_OO_LAY56 << 2),  RegVal);

        /*set layer 7 z-order */
        RegVal = *(pZOrder + 6);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB0_OO_LAY7 << 2),  RegVal);
#endif
    } else if(VPP_CPCB_OVL1 == OvlUnit) {
        /*set layer 1&2 z-order */
        RegVal = *pZOrder + (*(pZOrder + 1) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB1_OO_LAY12 << 2),  RegVal);

        /*set layer 3&4 z-order */
        RegVal = *(pZOrder + 2) + (*(pZOrder + 3) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB1_OO_LAY34 << 2),  RegVal);

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        /*set layer 5&6 z-order */
        RegVal = *(pZOrder + 4) + (*(pZOrder + 5) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB1_OO_LAY56 << 2),  RegVal);

        /*set layer 7 z-order */
        RegVal = *(pZOrder + 6);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB1_OO_LAY7 << 2),  RegVal);
#endif
    } else {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        return (MV_THINVPP_EBADPARAM);
#else
        /*set layer 1&2 z-order */
        RegVal = *pZOrder + (*(pZOrder + 1) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB2_OO_LAY12 << 2),  RegVal);

        /*set layer 3&4 z-order */
        RegVal = *(pZOrder + 2) + (*(pZOrder + 3) << 4);
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, vpp_obj->base_addr + (CPCB2_OO_LAY34 << 2),  RegVal);
#endif
    }

    return RetVal;
}



/***************************************************************************************
 * FUNCTION: set the OSD Overlay mode and domain
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               OsdCtrl - structure of mode and domain
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetCtrl(THINVPP_OBJ *vpp_obj, int OvlUnit, PVPP_OVL_OSD_CTRL pOsdCtrl)
{
    unsigned int RegAddr;
    unsigned int RegVal;
    int RetVal = MV_THINVPP_OK;

    CHECK_OVL_NUM(OvlUnit);

    RegVal = pOsdCtrl->OsdMode + (pOsdCtrl->OSdDomain << 1);

    /*get the address of the first register of OSD overlay*/
    /*get the address of the first register of video overlay*/
    if(VPP_CPCB_OVL0 == OvlUnit)
        RegAddr = vpp_obj->base_addr + (CPCB0_OO_CTRL << 2);
    else if(VPP_CPCB_OVL1 == OvlUnit)
        RegAddr = vpp_obj->base_addr + (CPCB1_OO_CTRL << 2);
    else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        return (MV_THINVPP_EBADPARAM);
#else
        RegAddr = vpp_obj->base_addr + (CPCB2_OO_CTRL << 2);
#endif

    /*writer the data from local buffer to BCM buffer*/
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, RegVal);

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set the OSD Overlay alpha
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               plane - plane1 or plane2
 *               PlaneAlpha - alpha value
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetPlaneAlpha(THINVPP_OBJ *vpp_obj, int OvlUnit, int plane, unsigned int PlaneAlpha)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    CHECK_OVL_NUM(OvlUnit);

    /*get the address of the first register of OSD overlay*/
    if(VPP_CPCB_OVL0 == OvlUnit)
        RegAddr = vpp_obj->base_addr + (CPCB0_OO_P1_AL << 2);
    else if(VPP_CPCB_OVL1 == OvlUnit)
        RegAddr = vpp_obj->base_addr + (CPCB1_OO_P1_AL << 2);
    else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        return (MV_THINVPP_EBADPARAM);
#else
        RegAddr = vpp_obj->base_addr + (CPCB2_OO_P1_AL << 2);
#endif

    if (Vpp_OVL_PLANE1 ==  plane){
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, PlaneAlpha);
    } else if (Vpp_OVL_PLANE2 == plane){
        THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, PlaneAlpha);
    } else
        return MV_THINVPP_EBADPARAM;

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set weighting factor for blending Main and Pip
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               BlendFactor - weighting factor for blending Main and Pip
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetVideoBlendingFactor(THINVPP_OBJ *vpp_obj, int OvlUnit, unsigned int BlendFactor)
{
    unsigned int RegAddr;
    int RetVal = MV_THINVPP_OK;

    CHECK_OVL_NUM(OvlUnit);

    /*get the address of the first register of video overlay*/
    if(VPP_CPCB_OVL0 == OvlUnit)
        RegAddr = vpp_obj->base_addr + (CPCB0_VO_WEIGHT << 2);
    else if(VPP_CPCB_OVL1 == OvlUnit)
        RegAddr = vpp_obj->base_addr + (CPCB1_VO_WEIGHT << 2);
    else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        return (MV_THINVPP_EBADPARAM);
#else
        RegAddr = vpp_obj->base_addr + (CPCB2_VO_WEIGHT << 2);
#endif

    /*writer the data from local buffer to BCM buffer*/
    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, BlendFactor);

    return RetVal;
}

/***************************************************************************************
 * FUNCTION: set the fixed color associated with each backend plane
 * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *               plane - plane number
 *               Color - plane fix color value
 * RETURN:  1 - succeed
 *                others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetPlaneColor(THINVPP_OBJ *vpp_obj, int OvlUnit, int Plane, unsigned int Color)
{
    unsigned int RegAddr, RegAddr1;
    unsigned int Byte;

    CHECK_OVL_NUM(OvlUnit);

    switch(Plane)
    {
        case Vpp_OVL_PLANE0:
            if(VPP_CPCB_OVL0 == OvlUnit) {
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX_0 << 2);
                RegAddr1 = vpp_obj->base_addr + (CPCB0_OO_FIX0_0 << 2);
            } else if(VPP_CPCB_OVL1 == OvlUnit) {
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX_0 << 2);
                RegAddr1 = vpp_obj->base_addr + (CPCB1_OO_FIX0_0 << 2);
            } else {
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM);
#else
                RegAddr = vpp_obj->base_addr + (CPCB2_OO_FIX_0 << 2);
                RegAddr1 = vpp_obj->base_addr + (CPCB2_OO_FIX0_0 << 2);
#endif
            }

	     /*set FIX and FIX0 register for base plane*/
	     /*write the first byte*/
            Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Byte);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr1 , Byte);

            /*write the second byte*/
	    Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4 , Byte);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr1 + 4 , Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8 , Byte);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr1 + 8 , Byte);
	    break;

	case Vpp_OVL_PLANE1:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX1_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX1_0 << 2);
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM);
#else
                RegAddr = vpp_obj->base_addr + (CPCB2_OO_FIX1_0 << 2);
#endif

            /*set FIX1 register for main*/
	    /*write the first byte*/
	    Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr , Byte);

	     /*write the second byte*/
	    Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4 , Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8 , Byte);
	    break;

	case Vpp_OVL_PLANE2:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX2_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX2_0 << 2);
            else
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
                return (MV_THINVPP_EBADPARAM);
#else
                RegAddr = vpp_obj->base_addr + (CPCB2_OO_FIX2_0 << 2);
#endif

            /*set FIX2 register for PIP*/
	    /*write the first byte*/
	    Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr , Byte);

	    /*write the second byte*/
	    Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4 , Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8 , Byte);
	    break;

	case Vpp_OVL_PLANE3:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX3_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX3_0 << 2);
            else
                return (MV_THINVPP_EBADPARAM);

	    /*write the first byte*/
	    Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr , Byte);

	    /*write the second byte*/
	    Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4 , Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8 , Byte);
	    break;

	case Vpp_OVL_PLANE3A:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX3A_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX3A_0 << 2);
            else
                return (MV_THINVPP_EBADPARAM);

	    /*write the first byte*/
	    Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Byte);

	    /*write the second byte*/
	    Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8, Byte);
	    break;
#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
        case Vpp_OVL_PLANE3B:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX3B_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX3B_0 << 2);
            else
                return (MV_THINVPP_EBADPARAM);

            /*write the first byte*/
            Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Byte);

            /*write the second byte*/
            Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8, Byte);
            break;

        case Vpp_OVL_PLANE3C:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX3C_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX3C_0 << 2);
            else
                return (MV_THINVPP_EBADPARAM);

            /*write the first byte*/
            Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Byte);

            /*write the second byte*/
            Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8, Byte);
            break;

        case Vpp_OVL_PLANE3D:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_FIX3D_0 << 2);
            else if(VPP_CPCB_OVL1 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_FIX3D_0 << 2);
            else
                return (MV_THINVPP_EBADPARAM);

            /*write the first byte*/
            Byte = GET_LOWEST_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr , Byte);

            /*write the second byte*/
            Byte = GET_SECOND_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 4, Byte);

            /*write the third byte*/
            Byte = GET_THIRD_BYTE(Color);
            THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr + 8, Byte);
            break;
#endif
	default:
	     return MV_THINVPP_EBADPARAM;
    }
    return (MV_THINVPP_OK);
}

#if (BERLIN_CHIP_VERSION >= BERLIN_B_0)
/***************************************************************************************
 * FUNCTION: set plane's border alpha  * PARAMS: OvlUnit - CPCB OVL unit number(OVL0, OVL1, OVL2)
 *         plane - plane number
 *         alpha - alpha value
 * RETURN:  1 - succeed
 *          others - failed to load CPCB OVL values to BCM buffer
 ***************************************************************************************/
int VPP_OVL_SetBorderAlpha(THINVPP_OBJ *vpp_obj, int OvlUnit, int Plane, int Alpha)
{
    unsigned int RegAddr;

    if ((OvlUnit != VPP_CPCB_OVL0) && (OvlUnit != VPP_CPCB_OVL1))
        return (MV_THINVPP_EBADPARAM);

    switch(Plane)
    {
        case Vpp_OVL_PLANE1:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P5_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P5_AL << 2);
            break;

        case Vpp_OVL_PLANE2:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P6_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P6_AL << 2);
            break;

        case Vpp_OVL_PLANE3:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P7_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P7_AL << 2);
            break;

        case Vpp_OVL_PLANE3A:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P7A_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P7A_AL << 2);
            break;

        case Vpp_OVL_PLANE3B:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P7B_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P7B_AL << 2);
            break;

        case Vpp_OVL_PLANE3C:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P7C_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P7C_AL << 2);
            break;

        case Vpp_OVL_PLANE3D:
            if(VPP_CPCB_OVL0 == OvlUnit)
                RegAddr = vpp_obj->base_addr + (CPCB0_OO_P7D_AL << 2);
            else
                RegAddr = vpp_obj->base_addr + (CPCB1_OO_P7D_AL << 2);
            break;

        default:
            return (MV_THINVPP_EBADPARAM);
    }

    THINVPP_BCMBUF_Write(vpp_obj->pVbiBcmBuf, RegAddr, Alpha);

    return (MV_THINVPP_OK);
}
#endif
