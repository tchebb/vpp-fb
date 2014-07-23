/*
 * Copyright Marvell Semiconductor, Inc. 2006. All rights reserved.
 *
 * Register address mapping configure file for rom testing code.
 */

#ifndef	__DRM__H__
#define	__DRM__H__

	#define	LSb32DRMROM_CMD_STAT_en					    0
	#define	LSb32DRMROM_CMD_RSP_DAT1_error			    0
	#define	RA_DRMROM_CMD_STAT 			0x00000
	#define	MSK32DRMROM_CMD_RSP_DAT1_error			       0xFFFFFFFF
	#define	RA_DRMROM_CMD_RSP_DAT1 		0x00020
	#define	MSK32DRMROM_CMD_RSP_CFG_tag				       0x000000FF
	#define	RA_DRMROM_CMD_RSP_CFG 		0x00018
	#define	RA_DRMROM_CMD_CMD_DAT3 		0x00014
	#define	RA_DRMROM_CMD_CMD_DAT2 		0x00010
	#define	RA_DRMROM_CMD_CMD_DAT1 		0x0000C
	#define	RA_DRMROM_CMD_CMD_DAT0 		0x00008
	#define	RA_DRMROM_CMD_CMD_CFG 		0x00004
	#define	DRMROM_CMD_TYPE_LD_ARMIMG 	0x1
	#define	MSK32DRMROM_CMD_CMD_CFG_nonce			       0xFFFF0000
	#define	MSK32DRMROM_CMD_STAT_en					       0x00000001
#endif

