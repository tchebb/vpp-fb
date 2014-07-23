
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

#include "thinvpp_module.h"
#include "hdmi_cmn.h"
#include "hdmi_aux_data_pack.h"
/*-----------------------------------------------------------------------------
 * Static Function Prototypes
 *-----------------------------------------------------------------------------
 */
/*-----------------------------------------------------------------------------
 * Description  : This function calculates checksum for the info frame
 *              : packets
 * Arguments    : pDataBuf - Pointer to data buffer whose checksum has to be
 *              : calculated
 *              : Length - Length of data buffer
 * Returns      : 1, on success
 *              : 0, otherwise
 * Notes        : Checksum is calculated such that byte-wide sum of all three
 *              : bytes of the Packet Header and all valid bytes of the
 *              : InfoFrame Packet contents (determined by length), plus the
 *              : checksum itself, equals zero. (Ref Hdmi Spec 1.3)
 *-----------------------------------------------------------------------------
 */
int VppFillChkSum (
            unsigned char *pDataBuf,
            unsigned char Length)
{
    unsigned char ChkSum = 0;
    unsigned char i;

    if (pDataBuf == NULL || Length == 0)
    {
        return 0;
    }

    for (i = 0; i < Length; i++)
    {
        ChkSum += pDataBuf[i];
    }

    pDataBuf[3] = (0x100 - ChkSum);
    return 1;
}

/*-----------------------------------------------------------------------------
 * Description  : This function packs the given data as AVI info frame
 *              : packet
 * Arguments    : pAVIData - Pointer to AVI info frame data (Input)
 *              : pDataBuf - Pointer to data buffer to pack the
 *              : info frame (Output)
 * Returns      : 1, on success
 *              : 0, otherwise
 * Notes        : Ref CEA-861-D
 *-----------------------------------------------------------------------------
 */
// Auxiliary video information frame
int VppPackAVIInfoFrame(
            PAVI_INFO_FRAME pAVIData,
            unsigned char *pDataBuf)
{
    int    RetCode;

    if (pAVIData == NULL || pDataBuf == NULL)
    {
        return 0;
    }

    // Packet Header
    pDataBuf[0] = (1 << 7) | (CEA_INFO_FRM_AVI); // Info frame type
    pDataBuf[1] = CEA_AVI_FRM_VERS;              // Version
    pDataBuf[2] = CEA_AVI_FRM_LEN;               // Info frame length

    // Checksum will be calculated and filled in the end
    pDataBuf[3] = 0x0;

    // Packet Data Bytes
    // Data byte 1
    pDataBuf[4] = (pAVIData->ColorSpace << 5)        |
                  (pAVIData->ActFmtInfoPresent << 4) |
                  (pAVIData->BarInfo << 2)           |
                  (pAVIData->ScanInfo);

    // Data byte 2
    pDataBuf[5] = (pAVIData->Calorimetry << 6)       |
                  (pAVIData->PicAspectRatio << 4)    |
                  (pAVIData->ActFmtAspectRatio);

    // Data byte 3
    pDataBuf[6] = (pAVIData->ITContent << 7)         |
                  (pAVIData->ExtCalorimetry << 4)    |
                  (pAVIData->RGBQuantRange << 2)     |
                  (pAVIData->ScalingInfo);

    // Data byte 4
    pDataBuf[7] = (pAVIData->VideoIdCode);

    // Data byte 5
    pDataBuf[8] = (pAVIData->PixRepeatCnt);

    // Rest of the Data bytes - Bar information
    pDataBuf[9]  = (pAVIData->TopBar && 0xFF);
    pDataBuf[10] = (pAVIData->TopBar >> 8);
    pDataBuf[11] = (pAVIData->BottomBar && 0xFF);
    pDataBuf[12] = (pAVIData->BottomBar >> 8);
    pDataBuf[13] = (pAVIData->LeftBar && 0xFF);
    pDataBuf[14] = (pAVIData->LeftBar >> 8);
    pDataBuf[15] = (pAVIData->RightBar && 0xFF);
    pDataBuf[16] = (pAVIData->RightBar >> 8);

    // Length of the packet is length of the data bytes +
    // size of header (4 bytes)
    RetCode = VppFillChkSum(pDataBuf, (CEA_AVI_FRM_LEN + FRM_HDR_LEN));
    return RetCode;
}

