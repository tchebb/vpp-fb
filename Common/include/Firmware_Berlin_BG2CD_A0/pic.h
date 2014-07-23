/*
 * Copyright Marvell Semiconductor, Inc. 2006. All rights reserved.
 *
 * Register address mapping configure file for rom testing code.
 */

#ifdef	_pic_h
#else
#define	_pic_h						"           pic_h >>>    "
#include	"ctypes.h"
#pragma	pack(4)
#ifdef	__cplusplus
	extern	"C"
	{
#endif
#ifdef	h_cmn
#else
#define	h_cmn
#define	\
	AR_cmn \
		18
#define	\
	AB_cmn \
		7
typedef struct SIE_cmn {
	#define	RA_cmn_fSrcPolSel0 			0x00000
	#define	w32cmn_fSrcPolSel0 			{										\
					UNSG32				ufSrcPolSel0_pol			 : 32;		\
										}
	/* @'00000 */	union {	UNSG32		u32cmn_fSrcPolSel0;
								struct	w32cmn_fSrcPolSel0;
										};
	/* ---:--- */	#define	    bcmn_fSrcPolSel0_pol				   32 /*bit*/
	#define	RA_cmn_fSrcPolSel1 			0x00004
	#define	w32cmn_fSrcPolSel1 			{										\
					UNSG32				ufSrcPolSel1_pol			 : 32;		\
										}
	/* @'00004 */	union {	UNSG32		u32cmn_fSrcPolSel1;
								struct	w32cmn_fSrcPolSel1;
										};
	/* ---:--- */	#define	    bcmn_fSrcPolSel1_pol				   32 /*bit*/
	#define	RA_cmn_fSrcPolSel2 			0x00008
	#define	w32cmn_fSrcPolSel2 			{										\
					UNSG32				ufSrcPolSel2_pol			 : 32;		\
										}
	/* @'00008 */	union {	UNSG32		u32cmn_fSrcPolSel2;
								struct	w32cmn_fSrcPolSel2;
										};
	/* ---:--- */	#define	    bcmn_fSrcPolSel2_pol				   32 /*bit*/
	#define	RA_cmn_fSrcSensSel0 		0x0000C
	#define	w32cmn_fSrcSensSel0 		{										\
					UNSG32				ufSrcSensSel0_sens			 : 32;		\
										}
	/* @'0000C */	union {	UNSG32		u32cmn_fSrcSensSel0;
								struct	w32cmn_fSrcSensSel0;
										};
	/* ---:--- */	#define	    bcmn_fSrcSensSel0_sens				   32 /*bit*/
	#define	RA_cmn_fSrcSensSel1 		0x00010
	#define	w32cmn_fSrcSensSel1 		{										\
					UNSG32				ufSrcSensSel1_sens			 : 32;		\
										}
	/* @'00010 */	union {	UNSG32		u32cmn_fSrcSensSel1;
								struct	w32cmn_fSrcSensSel1;
										};
	/* ---:--- */	#define	    bcmn_fSrcSensSel1_sens				   32 /*bit*/
	#define	RA_cmn_fSrcSensSel2 		0x00014
	#define	w32cmn_fSrcSensSel2 		{										\
					UNSG32				ufSrcSensSel2_sens			 : 32;		\
										}
	/* @'00014 */	union {	UNSG32		u32cmn_fSrcSensSel2;
								struct	w32cmn_fSrcSensSel2;
										};
	/* ---:--- */	#define	    bcmn_fSrcSensSel2_sens				   32 /*bit*/
	#define	RA_cmn_fIntSts0 			0x00018
	#define	w32cmn_fIntSts0 			{										\
					UNSG32				ufIntSts0_ists_0i			 :  1;		\
					UNSG32				ufIntSts0_ists_1i			 :  1;		\
					UNSG32				ufIntSts0_ists_2i			 :  1;		\
					UNSG32				ufIntSts0_ists_3i			 :  1;		\
					UNSG32				ufIntSts0_ists_4i			 :  1;		\
					UNSG32				ufIntSts0_ists_5i			 :  1;		\
					UNSG32				ufIntSts0_ists_6i			 :  1;		\
					UNSG32				ufIntSts0_ists_7i			 :  1;		\
					UNSG32				ufIntSts0_ists_8i			 :  1;		\
					UNSG32				ufIntSts0_ists_9i			 :  1;		\
					UNSG32				ufIntSts0_ists_10i			 :  1;		\
					UNSG32				ufIntSts0_ists_11i			 :  1;		\
					UNSG32				ufIntSts0_ists_12i			 :  1;		\
					UNSG32				ufIntSts0_ists_13i			 :  1;		\
					UNSG32				ufIntSts0_ists_14i			 :  1;		\
					UNSG32				ufIntSts0_ists_15i			 :  1;		\
					UNSG32				ufIntSts0_ists_16i			 :  1;		\
					UNSG32				ufIntSts0_ists_17i			 :  1;		\
					UNSG32				ufIntSts0_ists_18i			 :  1;		\
					UNSG32				ufIntSts0_ists_19i			 :  1;		\
					UNSG32				ufIntSts0_ists_20i			 :  1;		\
					UNSG32				ufIntSts0_ists_21i			 :  1;		\
					UNSG32				ufIntSts0_ists_22i			 :  1;		\
					UNSG32				ufIntSts0_ists_23i			 :  1;		\
					UNSG32				ufIntSts0_ists_24i			 :  1;		\
					UNSG32				ufIntSts0_ists_25i			 :  1;		\
					UNSG32				ufIntSts0_ists_26i			 :  1;		\
					UNSG32				ufIntSts0_ists_27i			 :  1;		\
					UNSG32				ufIntSts0_ists_28i			 :  1;		\
					UNSG32				ufIntSts0_ists_29i			 :  1;		\
					UNSG32				ufIntSts0_ists_30i			 :  1;		\
					UNSG32				ufIntSts0_ists_31i			 :  1;		\
										}
	/* @'00018 */	union {	UNSG32		u32cmn_fIntSts0;
								struct	w32cmn_fIntSts0;
										};
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_0i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_1i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_2i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_3i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_4i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_5i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_6i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_7i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_8i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_9i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_10i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_11i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_12i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_13i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_14i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_15i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_16i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_17i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_18i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_19i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_20i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_21i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_22i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_23i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_24i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_25i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_26i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_27i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_28i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_29i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_30i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts0_ists_31i				    1 /*bit*/
	#define	RA_cmn_fIntSts1 			0x0001C
	#define	w32cmn_fIntSts1 			{										\
					UNSG32				ufIntSts1_ists_0i			 :  1;		\
					UNSG32				ufIntSts1_ists_1i			 :  1;		\
					UNSG32				ufIntSts1_ists_2i			 :  1;		\
					UNSG32				ufIntSts1_ists_3i			 :  1;		\
					UNSG32				ufIntSts1_ists_4i			 :  1;		\
					UNSG32				ufIntSts1_ists_5i			 :  1;		\
					UNSG32				ufIntSts1_ists_6i			 :  1;		\
					UNSG32				ufIntSts1_ists_7i			 :  1;		\
					UNSG32				ufIntSts1_ists_8i			 :  1;		\
					UNSG32				ufIntSts1_ists_9i			 :  1;		\
					UNSG32				ufIntSts1_ists_10i			 :  1;		\
					UNSG32				ufIntSts1_ists_11i			 :  1;		\
					UNSG32				ufIntSts1_ists_12i			 :  1;		\
					UNSG32				ufIntSts1_ists_13i			 :  1;		\
					UNSG32				ufIntSts1_ists_14i			 :  1;		\
					UNSG32				ufIntSts1_ists_15i			 :  1;		\
					UNSG32				ufIntSts1_ists_16i			 :  1;		\
					UNSG32				ufIntSts1_ists_17i			 :  1;		\
					UNSG32				ufIntSts1_ists_18i			 :  1;		\
					UNSG32				ufIntSts1_ists_19i			 :  1;		\
					UNSG32				ufIntSts1_ists_20i			 :  1;		\
					UNSG32				ufIntSts1_ists_21i			 :  1;		\
					UNSG32				ufIntSts1_ists_22i			 :  1;		\
					UNSG32				ufIntSts1_ists_23i			 :  1;		\
					UNSG32				ufIntSts1_ists_24i			 :  1;		\
					UNSG32				ufIntSts1_ists_25i			 :  1;		\
					UNSG32				ufIntSts1_ists_26i			 :  1;		\
					UNSG32				ufIntSts1_ists_27i			 :  1;		\
					UNSG32				ufIntSts1_ists_28i			 :  1;		\
					UNSG32				ufIntSts1_ists_29i			 :  1;		\
					UNSG32				ufIntSts1_ists_30i			 :  1;		\
					UNSG32				ufIntSts1_ists_31i			 :  1;		\
										}
	/* @'0001C */	union {	UNSG32		u32cmn_fIntSts1;
								struct	w32cmn_fIntSts1;
										};
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_0i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_1i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_2i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_3i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_4i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_5i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_6i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_7i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_8i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_9i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_10i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_11i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_12i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_13i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_14i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_15i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_16i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_17i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_18i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_19i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_20i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_21i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_22i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_23i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_24i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_25i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_26i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_27i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_28i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_29i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_30i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts1_ists_31i				    1 /*bit*/
	#define	RA_cmn_fIntSts2 			0x00020
	#define	w32cmn_fIntSts2 			{										\
					UNSG32				ufIntSts2_ists_0i			 :  1;		\
					UNSG32				ufIntSts2_ists_1i			 :  1;		\
					UNSG32				ufIntSts2_ists_2i			 :  1;		\
					UNSG32				ufIntSts2_ists_3i			 :  1;		\
					UNSG32				ufIntSts2_ists_4i			 :  1;		\
					UNSG32				ufIntSts2_ists_5i			 :  1;		\
					UNSG32				ufIntSts2_ists_6i			 :  1;		\
					UNSG32				ufIntSts2_ists_7i			 :  1;		\
					UNSG32				ufIntSts2_ists_8i			 :  1;		\
					UNSG32				ufIntSts2_ists_9i			 :  1;		\
					UNSG32				ufIntSts2_ists_10i			 :  1;		\
					UNSG32				ufIntSts2_ists_11i			 :  1;		\
					UNSG32				ufIntSts2_ists_12i			 :  1;		\
					UNSG32				ufIntSts2_ists_13i			 :  1;		\
					UNSG32				ufIntSts2_ists_14i			 :  1;		\
					UNSG32				ufIntSts2_ists_15i			 :  1;		\
					UNSG32				ufIntSts2_ists_16i			 :  1;		\
					UNSG32				ufIntSts2_ists_17i			 :  1;		\
					UNSG32				ufIntSts2_ists_18i			 :  1;		\
					UNSG32				ufIntSts2_ists_19i			 :  1;		\
					UNSG32				ufIntSts2_ists_20i			 :  1;		\
					UNSG32				ufIntSts2_ists_21i			 :  1;		\
					UNSG32				ufIntSts2_ists_22i			 :  1;		\
					UNSG32				ufIntSts2_ists_23i			 :  1;		\
					UNSG32				ufIntSts2_ists_24i			 :  1;		\
					UNSG32				ufIntSts2_ists_25i			 :  1;		\
					UNSG32				ufIntSts2_ists_26i			 :  1;		\
					UNSG32				ufIntSts2_ists_27i			 :  1;		\
					UNSG32				ufIntSts2_ists_28i			 :  1;		\
					UNSG32				ufIntSts2_ists_29i			 :  1;		\
					UNSG32				ufIntSts2_ists_30i			 :  1;		\
					UNSG32				ufIntSts2_ists_31i			 :  1;		\
										}
	/* @'00020 */	union {	UNSG32		u32cmn_fIntSts2;
								struct	w32cmn_fIntSts2;
										};
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_0i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_1i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_2i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_3i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_4i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_5i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_6i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_7i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_8i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_9i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_10i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_11i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_12i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_13i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_14i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_15i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_16i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_17i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_18i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_19i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_20i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_21i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_22i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_23i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_24i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_25i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_26i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_27i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_28i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_29i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_30i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_fIntSts2_ists_31i				    1 /*bit*/
	#define	RA_cmn_nSrcPolSel0 			0x00024
	#define	w32cmn_nSrcPolSel0 			{										\
					UNSG32				unSrcPolSel0_pol			 : 32;		\
										}
	/* @'00024 */	union {	UNSG32		u32cmn_nSrcPolSel0;
								struct	w32cmn_nSrcPolSel0;
										};
	/* ---:--- */	#define	    bcmn_nSrcPolSel0_pol				   32 /*bit*/
	#define	RA_cmn_nSrcPolSel1 			0x00028
	#define	w32cmn_nSrcPolSel1 			{										\
					UNSG32				unSrcPolSel1_pol			 : 32;		\
										}
	/* @'00028 */	union {	UNSG32		u32cmn_nSrcPolSel1;
								struct	w32cmn_nSrcPolSel1;
										};
	/* ---:--- */	#define	    bcmn_nSrcPolSel1_pol				   32 /*bit*/
	#define	RA_cmn_nSrcPolSel2 			0x0002C
	#define	w32cmn_nSrcPolSel2 			{										\
					UNSG32				unSrcPolSel2_pol			 : 32;		\
										}
	/* @'0002C */	union {	UNSG32		u32cmn_nSrcPolSel2;
								struct	w32cmn_nSrcPolSel2;
										};
	/* ---:--- */	#define	    bcmn_nSrcPolSel2_pol				   32 /*bit*/
	#define	RA_cmn_nSrcSensSel0 		0x00030
	#define	w32cmn_nSrcSensSel0 		{										\
					UNSG32				unSrcSensSel0_sens			 : 32;		\
										}
	/* @'00030 */	union {	UNSG32		u32cmn_nSrcSensSel0;
								struct	w32cmn_nSrcSensSel0;
										};
	/* ---:--- */	#define	    bcmn_nSrcSensSel0_sens				   32 /*bit*/
	#define	RA_cmn_nSrcSensSel1 		0x00034
	#define	w32cmn_nSrcSensSel1 		{										\
					UNSG32				unSrcSensSel1_sens			 : 32;		\
										}
	/* @'00034 */	union {	UNSG32		u32cmn_nSrcSensSel1;
								struct	w32cmn_nSrcSensSel1;
										};
	/* ---:--- */	#define	    bcmn_nSrcSensSel1_sens				   32 /*bit*/
	#define	RA_cmn_nSrcSensSel2 		0x00038
	#define	w32cmn_nSrcSensSel2 		{										\
					UNSG32				unSrcSensSel2_sens			 : 32;		\
										}
	/* @'00038 */	union {	UNSG32		u32cmn_nSrcSensSel2;
								struct	w32cmn_nSrcSensSel2;
										};
	/* ---:--- */	#define	    bcmn_nSrcSensSel2_sens				   32 /*bit*/
	#define	RA_cmn_nIntSts0 			0x0003C
	#define	w32cmn_nIntSts0 			{										\
					UNSG32				unIntSts0_ists_0i			 :  1;		\
					UNSG32				unIntSts0_ists_1i			 :  1;		\
					UNSG32				unIntSts0_ists_2i			 :  1;		\
					UNSG32				unIntSts0_ists_3i			 :  1;		\
					UNSG32				unIntSts0_ists_4i			 :  1;		\
					UNSG32				unIntSts0_ists_5i			 :  1;		\
					UNSG32				unIntSts0_ists_6i			 :  1;		\
					UNSG32				unIntSts0_ists_7i			 :  1;		\
					UNSG32				unIntSts0_ists_8i			 :  1;		\
					UNSG32				unIntSts0_ists_9i			 :  1;		\
					UNSG32				unIntSts0_ists_10i			 :  1;		\
					UNSG32				unIntSts0_ists_11i			 :  1;		\
					UNSG32				unIntSts0_ists_12i			 :  1;		\
					UNSG32				unIntSts0_ists_13i			 :  1;		\
					UNSG32				unIntSts0_ists_14i			 :  1;		\
					UNSG32				unIntSts0_ists_15i			 :  1;		\
					UNSG32				unIntSts0_ists_16i			 :  1;		\
					UNSG32				unIntSts0_ists_17i			 :  1;		\
					UNSG32				unIntSts0_ists_18i			 :  1;		\
					UNSG32				unIntSts0_ists_19i			 :  1;		\
					UNSG32				unIntSts0_ists_20i			 :  1;		\
					UNSG32				unIntSts0_ists_21i			 :  1;		\
					UNSG32				unIntSts0_ists_22i			 :  1;		\
					UNSG32				unIntSts0_ists_23i			 :  1;		\
					UNSG32				unIntSts0_ists_24i			 :  1;		\
					UNSG32				unIntSts0_ists_25i			 :  1;		\
					UNSG32				unIntSts0_ists_26i			 :  1;		\
					UNSG32				unIntSts0_ists_27i			 :  1;		\
					UNSG32				unIntSts0_ists_28i			 :  1;		\
					UNSG32				unIntSts0_ists_29i			 :  1;		\
					UNSG32				unIntSts0_ists_30i			 :  1;		\
					UNSG32				unIntSts0_ists_31i			 :  1;		\
										}
	/* @'0003C */	union {	UNSG32		u32cmn_nIntSts0;
								struct	w32cmn_nIntSts0;
										};
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_0i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_1i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_2i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_3i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_4i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_5i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_6i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_7i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_8i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_9i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_10i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_11i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_12i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_13i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_14i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_15i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_16i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_17i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_18i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_19i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_20i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_21i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_22i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_23i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_24i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_25i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_26i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_27i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_28i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_29i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_30i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts0_ists_31i				    1 /*bit*/
	#define	RA_cmn_nIntSts1 			0x00040
	#define	w32cmn_nIntSts1 			{										\
					UNSG32				unIntSts1_ists_0i			 :  1;		\
					UNSG32				unIntSts1_ists_1i			 :  1;		\
					UNSG32				unIntSts1_ists_2i			 :  1;		\
					UNSG32				unIntSts1_ists_3i			 :  1;		\
					UNSG32				unIntSts1_ists_4i			 :  1;		\
					UNSG32				unIntSts1_ists_5i			 :  1;		\
					UNSG32				unIntSts1_ists_6i			 :  1;		\
					UNSG32				unIntSts1_ists_7i			 :  1;		\
					UNSG32				unIntSts1_ists_8i			 :  1;		\
					UNSG32				unIntSts1_ists_9i			 :  1;		\
					UNSG32				unIntSts1_ists_10i			 :  1;		\
					UNSG32				unIntSts1_ists_11i			 :  1;		\
					UNSG32				unIntSts1_ists_12i			 :  1;		\
					UNSG32				unIntSts1_ists_13i			 :  1;		\
					UNSG32				unIntSts1_ists_14i			 :  1;		\
					UNSG32				unIntSts1_ists_15i			 :  1;		\
					UNSG32				unIntSts1_ists_16i			 :  1;		\
					UNSG32				unIntSts1_ists_17i			 :  1;		\
					UNSG32				unIntSts1_ists_18i			 :  1;		\
					UNSG32				unIntSts1_ists_19i			 :  1;		\
					UNSG32				unIntSts1_ists_20i			 :  1;		\
					UNSG32				unIntSts1_ists_21i			 :  1;		\
					UNSG32				unIntSts1_ists_22i			 :  1;		\
					UNSG32				unIntSts1_ists_23i			 :  1;		\
					UNSG32				unIntSts1_ists_24i			 :  1;		\
					UNSG32				unIntSts1_ists_25i			 :  1;		\
					UNSG32				unIntSts1_ists_26i			 :  1;		\
					UNSG32				unIntSts1_ists_27i			 :  1;		\
					UNSG32				unIntSts1_ists_28i			 :  1;		\
					UNSG32				unIntSts1_ists_29i			 :  1;		\
					UNSG32				unIntSts1_ists_30i			 :  1;		\
					UNSG32				unIntSts1_ists_31i			 :  1;		\
										}
	/* @'00040 */	union {	UNSG32		u32cmn_nIntSts1;
								struct	w32cmn_nIntSts1;
										};
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_0i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_1i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_2i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_3i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_4i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_5i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_6i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_7i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_8i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_9i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_10i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_11i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_12i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_13i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_14i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_15i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_16i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_17i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_18i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_19i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_20i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_21i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_22i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_23i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_24i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_25i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_26i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_27i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_28i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_29i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_30i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts1_ists_31i				    1 /*bit*/
	#define	RA_cmn_nIntSts2 			0x00044
	#define	w32cmn_nIntSts2 			{										\
					UNSG32				unIntSts2_ists_0i			 :  1;		\
					UNSG32				unIntSts2_ists_1i			 :  1;		\
					UNSG32				unIntSts2_ists_2i			 :  1;		\
					UNSG32				unIntSts2_ists_3i			 :  1;		\
					UNSG32				unIntSts2_ists_4i			 :  1;		\
					UNSG32				unIntSts2_ists_5i			 :  1;		\
					UNSG32				unIntSts2_ists_6i			 :  1;		\
					UNSG32				unIntSts2_ists_7i			 :  1;		\
					UNSG32				unIntSts2_ists_8i			 :  1;		\
					UNSG32				unIntSts2_ists_9i			 :  1;		\
					UNSG32				unIntSts2_ists_10i			 :  1;		\
					UNSG32				unIntSts2_ists_11i			 :  1;		\
					UNSG32				unIntSts2_ists_12i			 :  1;		\
					UNSG32				unIntSts2_ists_13i			 :  1;		\
					UNSG32				unIntSts2_ists_14i			 :  1;		\
					UNSG32				unIntSts2_ists_15i			 :  1;		\
					UNSG32				unIntSts2_ists_16i			 :  1;		\
					UNSG32				unIntSts2_ists_17i			 :  1;		\
					UNSG32				unIntSts2_ists_18i			 :  1;		\
					UNSG32				unIntSts2_ists_19i			 :  1;		\
					UNSG32				unIntSts2_ists_20i			 :  1;		\
					UNSG32				unIntSts2_ists_21i			 :  1;		\
					UNSG32				unIntSts2_ists_22i			 :  1;		\
					UNSG32				unIntSts2_ists_23i			 :  1;		\
					UNSG32				unIntSts2_ists_24i			 :  1;		\
					UNSG32				unIntSts2_ists_25i			 :  1;		\
					UNSG32				unIntSts2_ists_26i			 :  1;		\
					UNSG32				unIntSts2_ists_27i			 :  1;		\
					UNSG32				unIntSts2_ists_28i			 :  1;		\
					UNSG32				unIntSts2_ists_29i			 :  1;		\
					UNSG32				unIntSts2_ists_30i			 :  1;		\
					UNSG32				unIntSts2_ists_31i			 :  1;		\
										}
	/* @'00044 */	union {	UNSG32		u32cmn_nIntSts2;
								struct	w32cmn_nIntSts2;
										};
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_0i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_1i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_2i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_3i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_4i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_5i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_6i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_7i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_8i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_9i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_10i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_11i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_12i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_13i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_14i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_15i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_16i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_17i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_18i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_19i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_20i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_21i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_22i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_23i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_24i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_25i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_26i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_27i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_28i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_29i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_30i				    1 /*bit*/
	/* ---:--- */	#define	    bcmn_nIntSts2_ists_31i				    1 /*bit*/
} SIE_cmn;
	#define	dftcmn_fSrcPolSel0 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fSrcPolSel0;
										} T32cmn_fSrcPolSel0;
	#define	dftcmn_fSrcPolSel1 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fSrcPolSel1;
										} T32cmn_fSrcPolSel1;
	#define	dftcmn_fSrcPolSel2 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fSrcPolSel2;
										} T32cmn_fSrcPolSel2;
	#define	dftcmn_fSrcSensSel0 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fSrcSensSel0;
										} T32cmn_fSrcSensSel0;
	#define	dftcmn_fSrcSensSel1 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fSrcSensSel1;
										} T32cmn_fSrcSensSel1;
	#define	dftcmn_fSrcSensSel2 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fSrcSensSel2;
										} T32cmn_fSrcSensSel2;
	#define	dftcmn_fIntSts0 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fIntSts0;
										} T32cmn_fIntSts0;
	#define	dftcmn_fIntSts1 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fIntSts1;
										} T32cmn_fIntSts1;
	#define	dftcmn_fIntSts2 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_fIntSts2;
										} T32cmn_fIntSts2;
	#define	dftcmn_nSrcPolSel0 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nSrcPolSel0;
										} T32cmn_nSrcPolSel0;
	#define	dftcmn_nSrcPolSel1 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nSrcPolSel1;
										} T32cmn_nSrcPolSel1;
	#define	dftcmn_nSrcPolSel2 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nSrcPolSel2;
										} T32cmn_nSrcPolSel2;
	#define	dftcmn_nSrcSensSel0 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nSrcSensSel0;
										} T32cmn_nSrcSensSel0;
	#define	dftcmn_nSrcSensSel1 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nSrcSensSel1;
										} T32cmn_nSrcSensSel1;
	#define	dftcmn_nSrcSensSel2 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nSrcSensSel2;
										} T32cmn_nSrcSensSel2;
	#define	dftcmn_nIntSts0 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nIntSts0;
										} T32cmn_nIntSts0;
	#define	dftcmn_nIntSts1 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nIntSts1;
										} T32cmn_nIntSts1;
	#define	dftcmn_nIntSts2 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32cmn_nIntSts2;
										} T32cmn_nIntSts2;
SIGN32	cmn_import(SIE_cmn *p, char *regs);
SIGN32	cmn_export(SIE_cmn *p, char *regs);
#endif
#ifdef	h_perPIC
#else
#define	h_perPIC
#define	\
	AR_perPIC \
		8
#define	\
	AB_perPIC \
		5
typedef struct SIE_perPIC {
	#define	RA_perPIC_fTgtPolSel 		0x00000
	#define	w32perPIC_fTgtPolSel 		{										\
					UNSG32				ufTgtPolSel_pol				 :  1;		\
					UNSG32				_x00000	: 31;							\
										}
	/* @'00000 */	union {	UNSG32		u32perPIC_fTgtPolSel;
								struct	w32perPIC_fTgtPolSel;
										};
	/* ---:--- */	#define	    bperPIC_fTgtPolSel_pol				    1 /*bit*/
	#define	RA_perPIC_fTgtSensSel 		0x00004
	#define	w32perPIC_fTgtSensSel 		{										\
					UNSG32				ufTgtSensSel_sens			 :  1;		\
					UNSG32				_x00004	: 31;							\
										}
	/* @'00004 */	union {	UNSG32		u32perPIC_fTgtSensSel;
								struct	w32perPIC_fTgtSensSel;
										};
	/* ---:--- */	#define	    bperPIC_fTgtSensSel_sens			    1 /*bit*/
	#define	RA_perPIC_fIntE 			0x00008
	#define	w32perPIC_fIntE 			{										\
					UNSG32				ufIntE_ie					 : 32;		\
										}
	/* @'00008 */	union {	UNSG32		u32perPIC_fIntE;
								struct	w32perPIC_fIntE;
										};
	/* ---:--- */	#define	    bperPIC_fIntE_ie					   32 /*bit*/
	#define	RA_perPIC_fGIntE 			0x0000C
	#define	w32perPIC_fGIntE 			{										\
					UNSG32				ufGIntE_gIe					 :  1;		\
					UNSG32				_x0000C	: 31;							\
										}
	/* @'0000C */	union {	UNSG32		u32perPIC_fGIntE;
								struct	w32perPIC_fGIntE;
										};
	/* ---:--- */	#define	    bperPIC_fGIntE_gIe					    1 /*bit*/
	#define	RA_perPIC_nTgtPolSel 		0x00010
	#define	w32perPIC_nTgtPolSel 		{										\
					UNSG32				unTgtPolSel_pol				 :  1;		\
					UNSG32				_x00010	: 31;							\
										}
	/* @'00010 */	union {	UNSG32		u32perPIC_nTgtPolSel;
								struct	w32perPIC_nTgtPolSel;
										};
	/* ---:--- */	#define	    bperPIC_nTgtPolSel_pol				    1 /*bit*/
	#define	RA_perPIC_nTgtSensSel 		0x00014
	#define	w32perPIC_nTgtSensSel 		{										\
					UNSG32				unTgtSensSel_sens			 :  1;		\
					UNSG32				_x00014	: 31;							\
										}
	/* @'00014 */	union {	UNSG32		u32perPIC_nTgtSensSel;
								struct	w32perPIC_nTgtSensSel;
										};
	/* ---:--- */	#define	    bperPIC_nTgtSensSel_sens			    1 /*bit*/
	#define	RA_perPIC_nIntE 			0x00018
	#define	w32perPIC_nIntE 			{										\
					UNSG32				unIntE_ie					 : 32;		\
										}
	/* @'00018 */	union {	UNSG32		u32perPIC_nIntE;
								struct	w32perPIC_nIntE;
										};
	/* ---:--- */	#define	    bperPIC_nIntE_ie					   32 /*bit*/
	#define	RA_perPIC_nGIntE 			0x0001C
	#define	w32perPIC_nGIntE 			{										\
					UNSG32				unGIntE_gIe					 :  1;		\
					UNSG32				_x0001C	: 31;							\
										}
	/* @'0001C */	union {	UNSG32		u32perPIC_nGIntE;
								struct	w32perPIC_nGIntE;
										};
	/* ---:--- */	#define	    bperPIC_nGIntE_gIe					    1 /*bit*/
} SIE_perPIC;
	#define	dftperPIC_fTgtPolSel 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_fTgtPolSel;
										} T32perPIC_fTgtPolSel;
	#define	dftperPIC_fTgtSensSel 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_fTgtSensSel;
										} T32perPIC_fTgtSensSel;
	#define	dftperPIC_fIntE 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_fIntE;
										} T32perPIC_fIntE;
	#define	dftperPIC_fGIntE 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_fGIntE;
										} T32perPIC_fGIntE;
	#define	dftperPIC_nTgtPolSel 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_nTgtPolSel;
										} T32perPIC_nTgtPolSel;
	#define	dftperPIC_nTgtSensSel 		0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_nTgtSensSel;
										} T32perPIC_nTgtSensSel;
	#define	dftperPIC_nIntE 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_nIntE;
										} T32perPIC_nIntE;
	#define	dftperPIC_nGIntE 			0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32perPIC_nGIntE;
										} T32perPIC_nGIntE;
SIGN32	perPIC_import(SIE_perPIC *p, char *regs);
SIGN32	perPIC_export(SIE_perPIC *p, char *regs);
#endif
#ifdef	h_PIC
#else
#define	h_PIC
#define	\
	AR_PIC \
		26
#define	\
	AB_PIC \
		7
typedef struct SIE_PIC {
	#define	RA_PIC_CPU0 				0x00000
	/* @'00000 */	SIE_perPIC 					ie_CPU0;
	#define	RA_PIC_cmn 					0x00020
	/* @'00020 */	SIE_cmn 					ie_cmn;
} SIE_PIC;
SIGN32	PIC_import(SIE_PIC *p, char *regs);
SIGN32	PIC_export(SIE_PIC *p, char *regs);
#endif
#ifdef	h_IRQ
#else
#define	h_IRQ
#define	\
	AR_IRQ \
		1
#define	\
	AB_IRQ \
		2
	#define	IRQ_dHubIntrAvio0 			0x0
	#define	IRQ_emmc_int 				0x1C
typedef struct SIE_IRQ {
	#define	RA_IRQ_dummy 				0x00000
	#define	w32IRQ_dummy 				{										\
					UNSG32				udummy_0x00000000			 : 32;		\
										}
	/* @'00000 */	union {	UNSG32		u32IRQ_dummy;
								struct	w32IRQ_dummy;
										};
	/* ---:--- */	#define	    bIRQ_dummy_0x00000000				   32 /*bit*/
} SIE_IRQ;
	#define	dftIRQ_dummy 				0x00000000
			typedef	union {	UNSG32		u32;
								struct	w32IRQ_dummy;
										} T32IRQ_dummy;
SIGN32	IRQ_import(SIE_IRQ *p, char *regs);
SIGN32	IRQ_export(SIE_IRQ *p, char *regs);
#endif
#pragma	pack()
#ifdef	__cplusplus
	}
#endif
#endif	/* _pic_h */
