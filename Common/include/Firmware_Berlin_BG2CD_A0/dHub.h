/*
 * Copyright Marvell Semiconductor, Inc. 2006. All rights reserved.
 *
 * Register address mapping configure file for rom testing code.
 */

#ifndef dHub_h
#define dHub_h (){}
#include "ctypes.h"
#pragma pack(1)
#ifdef __cplusplus
  extern "C" {
#endif
#ifndef _DOCC_H_BITOPS_
#define _DOCC_H_BITOPS_ (){}
    #define _bSETMASK_(b)                                      ((b)<32 ? (1<<((b)&31)) : 0)
    #define _NSETMASK_(msb,lsb)                                (_bSETMASK_((msb)+1)-_bSETMASK_(lsb))
    #define _bCLRMASK_(b)                                      (~_bSETMASK_(b))
    #define _NCLRMASK_(msb,lsb)                                (~_NSETMASK_(msb,lsb))
    #define _BFGET_(r,msb,lsb)                                 (_NSETMASK_((msb)-(lsb),0)&((r)>>(lsb)))
    #define _BFSET_(r,msb,lsb,v)                               do{ (r)&=_NCLRMASK_(msb,lsb); (r)|=_NSETMASK_(msb,lsb)&((v)<<(lsb)); }while(0)
#endif

    typedef struct SIE_SemaINTR {
    #define     w32SemaINTR_mask                               {\
            UNSG32 umask_empty                                 :  1;\
            UNSG32 umask_full                                  :  1;\
            UNSG32 umask_almostEmpty                           :  1;\
            UNSG32 umask_almostFull                            :  1;\
            UNSG32 RSVDx0_b4                                   : 28;\
          }
    union { UNSG32 u32SemaINTR_mask;
            struct w32SemaINTR_mask;
          };
    } SIE_SemaINTR;
    typedef union  T32SemaINTR_mask
          { UNSG32 u32;
            struct w32SemaINTR_mask;
                 } T32SemaINTR_mask;

    #define     RA_Semaphore_CFG                               0x0000
    #define     RA_Semaphore_INTR                              0x0004
    typedef struct SIE_Semaphore {
    #define     w32Semaphore_CFG                               {\
            UNSG32 uCFG_DEPTH                                  : 16;\
            UNSG32 RSVDx0_b16                                  : 16;\
          }
    union { UNSG32 u32Semaphore_CFG;
            struct w32Semaphore_CFG;
          };
              SIE_SemaINTR                                     ie_INTR[3];
    #define     w32Semaphore_mask                              {\
            UNSG32 umask_full                                  :  1;\
            UNSG32 umask_emp                                   :  1;\
            UNSG32 RSVDx10_b2                                  : 30;\
          }
    union { UNSG32 u32Semaphore_mask;
            struct w32Semaphore_mask;
          };
    } SIE_Semaphore;
    typedef union  T32Semaphore_CFG
          { UNSG32 u32;
            struct w32Semaphore_CFG;
                 } T32Semaphore_CFG;
    typedef union  T32Semaphore_mask
          { UNSG32 u32;
            struct w32Semaphore_mask;
                 } T32Semaphore_mask;

    #define     w32SemaQuery_RESP                              {\
            UNSG32 uRESP_CNT                                   : 16;\
            UNSG32 uRESP_PTR                                   : 16;\
          }
    typedef union  T32SemaQuery_RESP
          { UNSG32 u32;
            struct w32SemaQuery_RESP;
                 } T32SemaQuery_RESP;

    #define        SemaQueryMap_ADDR_master_producer                        0x0
    #define        SemaQueryMap_ADDR_master_consumer                        0x1

    #define     w32SemaQueryMap_ADDR                           {\
            UNSG32 uADDR_byte                                  :  2;\
            UNSG32 uADDR_ID                                    :  5;\
            UNSG32 uADDR_master                                :  1;\
            UNSG32 RSVDx0_b8                                   : 24;\
          }
    typedef union  T32SemaQueryMap_ADDR
          { UNSG32 u32;
            struct w32SemaQueryMap_ADDR;
                 } T32SemaQueryMap_ADDR;

    #define     RA_SemaHub_Query                               0x0000
    #define     RA_SemaHub_ARR                                 0x0100
    #define     RA_SemaHub_PUSH                                0x0380
    #define     RA_SemaHub_POP                                 0x0384
    #define     RA_SemaHub_empty                               0x0388
    #define     RA_SemaHub_full                                0x038C
    #define     RA_SemaHub_almostEmpty                         0x0390
    #define     RA_SemaHub_almostFull                          0x0394

    #define     w32SemaHub_PUSH                                {\
            UNSG32 uPUSH_ID                                    :  8;\
            UNSG32 uPUSH_delta                                 :  8;\
            UNSG32 RSVDx380_b16                                : 16;\
          }
    typedef union  T32SemaHub_PUSH
          { UNSG32 u32;
            struct w32SemaHub_PUSH;
                 } T32SemaHub_PUSH;
    #define     w32SemaHub_POP                                 {\
            UNSG32 uPOP_ID                                     :  8;\
            UNSG32 uPOP_delta                                  :  8;\
            UNSG32 RSVDx384_b16                                : 16;\
          }
    typedef union  T32SemaHub_POP
          { UNSG32 u32;
            struct w32SemaHub_POP;
                 } T32SemaHub_POP;

    #define     RA_FiFo_CFG                                    0x0000
    #define     RA_FiFo_START                                  0x0004
    #define     RA_FiFo_CLEAR                                  0x0008
    #define     RA_FiFo_FLUSH                                  0x000C
    typedef struct SIE_FiFo {
    #define     w32FiFo_CFG                                    {\
            UNSG32 uCFG_BASE                                   : 20;\
            UNSG32 RSVDx0_b20                                  : 12;\
          }
    union { UNSG32 u32FiFo_CFG;
            struct w32FiFo_CFG;
          };
    #define     w32FiFo_START                                  {\
            UNSG32 uSTART_EN                                   :  1;\
            UNSG32 RSVDx4_b1                                   : 31;\
          }
    union { UNSG32 u32FiFo_START;
            struct w32FiFo_START;
          };
    #define     w32FiFo_CLEAR                                  {\
            UNSG32 uCLEAR_EN                                   :  1;\
            UNSG32 RSVDx8_b1                                   : 31;\
          }
    union { UNSG32 u32FiFo_CLEAR;
            struct w32FiFo_CLEAR;
          };
    #define     w32FiFo_FLUSH                                  {\
            UNSG32 uFLUSH_EN                                   :  1;\
            UNSG32 RSVDxC_b1                                   : 31;\
          }
    union { UNSG32 u32FiFo_FLUSH;
            struct w32FiFo_FLUSH;
          };
    } SIE_FiFo;
    typedef union  T32FiFo_CFG
          { UNSG32 u32;
            struct w32FiFo_CFG;
                 } T32FiFo_CFG;

    #define     RA_HBO_FiFoCtl                                 0x0000
    #define     RA_HBO_ARR                                     0x0400
    #define     RA_HBO_BUSY                                    0x0600

    typedef struct SIE_dHubCmdHDR {
    #define     w32dHubCmdHDR_DESC                             {\
            UNSG32 uDESC_size                                  : 16;\
            UNSG32 uDESC_sizeMTU                               :  1;\
            UNSG32 uDESC_semOpMTU                              :  1;\
            UNSG32 uDESC_chkSemId                              :  5;\
            UNSG32 uDESC_updSemId                              :  5;\
            UNSG32 uDESC_interrupt                             :  1;\
            UNSG32 RSVDx0_b29                                  :  3;\
          }
    union { UNSG32 u32dHubCmdHDR_DESC;
            struct w32dHubCmdHDR_DESC;
          };
    } SIE_dHubCmdHDR;

    typedef struct SIE_dHubCmd {
    #define     w32dHubCmd_MEM                                 {\
            UNSG32 uMEM_addr                                   : 32;\
          }
    union { UNSG32 u32dHubCmd_MEM;
            struct w32dHubCmd_MEM;
          };
              SIE_dHubCmdHDR                                   ie_HDR;
    } SIE_dHubCmd;

    #define     RA_dHubChannel_CFG                             0x0000
    #define     RA_dHubChannel_START                           0x0004
    #define     RA_dHubChannel_CLEAR                           0x0008
    #define     RA_dHubChannel_FLUSH                           0x000C

    typedef struct SIE_dHubChannel {
    #define     w32dHubChannel_CFG                             {\
            UNSG32 uCFG_MTU                                    :  2;\
            UNSG32 uCFG_QoS                                    :  1;\
            UNSG32 uCFG_selfLoop                               :  1;\
            UNSG32 uCFG_intrCtl                                :  1;\
            UNSG32 uCFG_hScan                                  :  1;\
            UNSG32 uCFG_vScan                                  :  1;\
            UNSG32 RSVDx0_b7                                   : 25;\
          }
    union { UNSG32 u32dHubChannel_CFG;
            struct w32dHubChannel_CFG;
          };
    #define     w32dHubChannel_START                           {\
            UNSG32 uSTART_EN                                   :  1;\
            UNSG32 RSVDx4_b1                                   : 31;\
          }
    union { UNSG32 u32dHubChannel_START;
            struct w32dHubChannel_START;
          };
    #define     w32dHubChannel_CLEAR                           {\
            UNSG32 uCLEAR_EN                                   :  1;\
            UNSG32 RSVDx8_b1                                   : 31;\
          }
    union { UNSG32 u32dHubChannel_CLEAR;
            struct w32dHubChannel_CLEAR;
          };
    #define     w32dHubChannel_FLUSH                           {\
            UNSG32 uFLUSH_EN                                   :  1;\
            UNSG32 RSVDxC_b1                                   : 31;\
          }
    union { UNSG32 u32dHubChannel_FLUSH;
            struct w32dHubChannel_FLUSH;
          };
    } SIE_dHubChannel;

    #define        dHubChannel_CFG_MTU_8byte                                0x0
    #define        dHubChannel_CFG_MTU_32byte                               0x1
    #define        dHubChannel_CFG_MTU_128byte                              0x2
    #define        dHubChannel_CFG_MTU_1024byte                             0x3
    typedef union  T32dHubChannel_CFG
          { UNSG32 u32;
            struct w32dHubChannel_CFG;
                 } T32dHubChannel_CFG;


    #define     RA_dHubReg_SemaHub                             0x0000
    #define     RA_dHubReg_HBO                                 0x0400
    #define     RA_dHubReg_ARR                                 0x0B00
    #define     RA_dHubReg_BUSY                                0x0C00
    #define     RA_dHubReg_PENDING                             0x0C04

    #define     RA_dHubReg2D_dHub                              0x0000
    #define     RA_dHubReg2D_ARR                               0x0D00
    #define     RA_dHubReg2D_BUSY                              0x0F00

    #define     RA_dHubCmd2D_MEM                               0x0000
    #define     RA_dHubCmd2D_DESC                              0x0004
    #define     RA_dHubCmd2D_START                             0x0008
    #define     RA_dHubCmd2D_CLEAR                             0x000C
    #define     RA_dHubCmd2D_HDR                               0x0010

    typedef struct SIE_dHubCmd2D {
    #define     w32dHubCmd2D_MEM                               {\
            UNSG32 uMEM_addr                                   : 32;\
          }
    union { UNSG32 u32dHubCmd2D_MEM;
            struct w32dHubCmd2D_MEM;
          };
    #define     w32dHubCmd2D_DESC                              {\
            UNSG32 uDESC_stride                                : 16;\
            UNSG32 uDESC_numLine                               : 13;\
            UNSG32 uDESC_hdrLoop                               :  2;\
            UNSG32 uDESC_interrupt                             :  1;\
          }
    union { UNSG32 u32dHubCmd2D_DESC;
            struct w32dHubCmd2D_DESC;
          };
    #define     w32dHubCmd2D_START                             {\
            UNSG32 uSTART_EN                                   :  1;\
            UNSG32 RSVDx8_b1                                   : 31;\
          }
    union { UNSG32 u32dHubCmd2D_START;
            struct w32dHubCmd2D_START;
          };
    #define     w32dHubCmd2D_CLEAR                             {\
            UNSG32 uCLEAR_EN                                   :  1;\
            UNSG32 RSVDxC_b1                                   : 31;\
          }
    union { UNSG32 u32dHubCmd2D_CLEAR;
            struct w32dHubCmd2D_CLEAR;
          };
              SIE_dHubCmdHDR                                   ie_HDR[4];
    } SIE_dHubCmd2D;


#ifdef __cplusplus
  }
#endif
#pragma  pack()
#endif
