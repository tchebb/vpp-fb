
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

#include "thinvpp_common.h"
#include "hdmi_cmn.h"

static const CEA_RES_INFO VideoCodeMap[] =
{
    {0 , 0,    0,   0,  RES_INFO_FRM_FMT_UNDEF, CEA_PICT_AR_NONE},//0  - Undefined
    {1 , 640,  480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//1  - 640*480p   @59.94/60Hz 4:3
    {2 , 720,  480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//2  - 720*480p   @59.94/60Hz 4:3
    {3 , 720,  480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//3  - 720*480p   @59.94/60Hz 16:9
    {4 , 1280, 720, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//4  - 1280*720p  @59.94/60Hz 16:9
    {5 , 1920, 1080,60, RES_INFO_INTERLACED   , CEA_PICT_AR_16_9},//5  - 1920*1080i @59.94/60Hz 16:9
    {6 , 1440, 480, 60, RES_INFO_INTERLACED   , CEA_PICT_AR_4_3 },//6  - 1440*480i  @59.94/60Hz 4:3
    {7 , 1440, 480, 60, RES_INFO_INTERLACED   , CEA_PICT_AR_16_9},//7  - 1440*480i  @59.94/60Hz 16:9
    {8 , 1440, 240, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//8  - 1440*240p  @59.94/60Hz 4:3
    {9 , 1440, 240, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//9  - 1440*240p  @59.94/60Hz 16:9
    {10, 2880, 480, 60, RES_INFO_INTERLACED   , CEA_PICT_AR_4_3 },//10 - 2880*480i  @59.94/60Hz 4:3
    {11, 2880, 480, 60, RES_INFO_INTERLACED   , CEA_PICT_AR_16_9},//11 - 2880*480i  @59.94/60Hz 16:9
    {12, 2880, 240, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//12 - 2880*240p  @59.94/60Hz 4:3
    {13, 2880, 240, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//13 - 2880*240p  @59.94/60Hz 16:9
    {14, 1440, 480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//14 - 1440*480p  @59.94/60Hz 4:3
    {15, 1440, 480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//15 - 1440*480p  @59.94/60Hz 16:9
    {16, 1920, 1080,60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//16 - 1920*1080p @59.94/60Hz 16:9
    {17, 720,  576, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//17 - 720*576p   @50Hz       4:3
    {18, 720,  576, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//18 - 720*576p   @50Hz       16:9
    {19, 1280, 720, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//19 - 1280*720p  @50Hz       16:9
    {20, 1920, 1080,50, RES_INFO_INTERLACED   , CEA_PICT_AR_16_9},//20 - 1920*1080i @50Hz       16:9
    {21, 1440, 576, 50, RES_INFO_INTERLACED   , CEA_PICT_AR_4_3 },//21 - 1440*576i  @50Hz       4:3
    {22, 1440, 576, 50, RES_INFO_INTERLACED   , CEA_PICT_AR_16_9},//22 - 1440*576i  @50Hz       16:9
    {23, 1440, 288, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//23 - 1440*288p  @50Hz       4:3
    {24, 1440, 288, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//24 - 1440*288p  @50Hz       16:9
    {25, 2880, 576, 50, RES_INFO_INTERLACED   , CEA_PICT_AR_4_3 },//25 - 2880*576i  @50Hz       4:3
    {26, 2880, 576, 50, RES_INFO_INTERLACED   , CEA_PICT_AR_16_9},//26 - 2880*576i  @50Hz       16:9
    {27, 2880, 288, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//27 - 2880*288p  @50Hz       4:3
    {28, 2880, 288, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//28 - 2880*288p  @50Hz       16:9
    {29, 1440, 576, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//29 - 1440*576p  @50Hz       4:3
    {30, 1440, 576, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//30 - 1440*576p  @50Hz       16:9
    {31, 1920,1080, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//31 - 1920*1080p @50Hz       16:9
    {32, 1920,1080, 24, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//32 - 1920*1080p @23.97/24Hz 16:9
    {33, 1920,1080, 25, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//33 - 1920*1080p @25Hz       16:9
    {34, 1920,1080, 30, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//34 - 1920*1080p @29.97/30Hz 16:9
    {35, 2880, 480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//35 - 2880*480p  @59.94/60Hz 4:3
    {36, 2880, 480, 60, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//36 - 2880*480p  @59.94/60Hz 16:9
    {37, 2880, 576, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_4_3 },//37 - 2880*576p  @59.94/60Hz 4:3
    {38, 2880, 576, 50, RES_INFO_PROGRESSIVE  , CEA_PICT_AR_16_9},//38 - 2880*576p  @59.94/60Hz 16:9
};

// FIFO wrap around condition
#define FIFO_WRAP_AROUND(curElem,maxElem)    (((curElem)>=(maxElem))?0:(curElem))

/*-----------------------------------------------------------------------------
 * Description  : This function returns if the given video id code is
 *              : defined in the table
 * Arguments    : VideoIDCode - Video ID code
 * Returns      : 1, if it is defined
 *              : 0, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int IsVideoIDCodeDefined (unsigned short VideoIDCode)
{
    unsigned short MaxVideoIDCode;
    MaxVideoIDCode = sizeof(VideoCodeMap)/sizeof(CEA_RES_INFO);

    // Check given VideoID
    if (VideoIDCode == 0 || VideoIDCode >= MaxVideoIDCode)
    {
        return 0;
    }

    return 1;
}

/*-----------------------------------------------------------------------------
 * Description  : This function returns resolution information from the
 *              : given Video ID code
 * Arguments    : VideoIDCode - Video ID code
 *              : pResInfo - Pointer to resolution information (Output)
 * Returns      : 1, on success
 *              : 0, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int GetResForVideoID (CEA_RES_INFO *pResInfo)
{
    unsigned short MaxVideoIDCode;
    unsigned short VideoIDCode;

    if (pResInfo == NULL)
    {
        return 0;
    }

    MaxVideoIDCode = sizeof(VideoCodeMap)/sizeof(CEA_RES_INFO);
    VideoIDCode    = pResInfo->VideoIDCode;

    // Check given VideoID
    if (VideoIDCode == 0 || VideoIDCode >= MaxVideoIDCode)
    {
        return 0;
    }

    pResInfo->HActive       = VideoCodeMap[VideoIDCode].HActive;
    pResInfo->VActive       = VideoCodeMap[VideoIDCode].VActive;
    pResInfo->RefreshRate   = VideoCodeMap[VideoIDCode].RefreshRate;
    pResInfo->FrmFmt        = VideoCodeMap[VideoIDCode].FrmFmt;
    pResInfo->AspRatio      = VideoCodeMap[VideoIDCode].AspRatio;
    return 1;
}

/*-----------------------------------------------------------------------------
 * Description  : This function returns Video ID code for the given resolution
 *              : information
 * Arguments    : pResInfo - Pointer to resolution information (Input)
 *              : VideoIDCode - Pointer to return Video ID code (Output)
 * Returns      : 1, on success
 *              : 0, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int GetVideoIDForRes (CEA_RES_INFO *pResInfo)
{
    unsigned short   MaxVideoIDCode;
    unsigned short   Count;

    MaxVideoIDCode = sizeof(VideoCodeMap)/sizeof(CEA_RES_INFO);

    if (pResInfo == NULL)
    {
        return 0;
    }

    pResInfo->VideoIDCode = 0;
    for (Count = 0; Count < MaxVideoIDCode; Count++)
    {
        if ((pResInfo->HActive      == VideoCodeMap[Count].HActive) &&
            (pResInfo->VActive      == VideoCodeMap[Count].VActive) &&
            (pResInfo->RefreshRate  == VideoCodeMap[Count].RefreshRate))
        {
            if (pResInfo->FrmFmt != RES_INFO_FRM_FMT_UNDEF)
            {
                if (pResInfo->FrmFmt != VideoCodeMap[Count].FrmFmt)
                    continue;
            }
            if (pResInfo->AspRatio != CEA_PICT_AR_NONE)
            {
                if (pResInfo->AspRatio != VideoCodeMap[Count].AspRatio)
                    continue;
            }
            break;
        }
    }

    if (Count == MaxVideoIDCode)
    {
        // Reached the end of loop without finding a match
        return 0;
    }

    pResInfo->VideoIDCode = Count;
    return 1;
}

/*-----------------------------------------------------------------------------
 * Description  : This function performs integer division rounding up
 * Arguments    : Num  - Numerator
 *              : Den  - Denominator
 *              : *Res - Pointer to return result
 * Returns      : 1, on success
 *              : 0, otherwise
 * Notes        : None
 *-----------------------------------------------------------------------------
 */
int IntDivision (unsigned int Num, unsigned int Den, unsigned int *Res)
{
    unsigned int Rem;

    if (Num == 0 || Den == 0)
    {
        return 0;
    }

    *Res = Num / Den;
    Rem = Num % Den;
    if ((Rem<<1) >= Den) (*Res) += 1;

    return 1;
}

