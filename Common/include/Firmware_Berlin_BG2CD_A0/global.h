/*
 * Copyright Marvell Semiconductor, Inc. 2006. All rights reserved.
 *
 * Register address mapping configure file for rom testing code.
 */

#ifndef global_h
#define global_h (){}
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
#ifndef h_clkD1
#define h_clkD1 (){}
    #define     RA_clkD1_ctrl                                  0x0000
    #define       bclkD1_ctrl_ClkEn                            1
    #define        clkD1_ctrl_ClkEn_enable                                  0x1
    #define        clkD1_ctrl_ClkEn_disable                                 0x0
    #define       bclkD1_ctrl_ClkPllSel                        3
    #define        clkD1_ctrl_ClkPllSel_AVPllB4                             0x0
    #define        clkD1_ctrl_ClkPllSel_AVPllB5                             0x1
    #define        clkD1_ctrl_ClkPllSel_AVPllB6                             0x2
    #define        clkD1_ctrl_ClkPllSel_AVPllB7                             0x3
    #define        clkD1_ctrl_ClkPllSel_SYSPLL                              0x4
    #define       bclkD1_ctrl_ClkPllSwitch                     1
    #define        clkD1_ctrl_ClkPllSwitch_SYSPLL                           0x0
    #define        clkD1_ctrl_ClkPllSwitch_AVPLL                            0x1
    #define       bclkD1_ctrl_ClkSwitch                        1
    #define        clkD1_ctrl_ClkSwitch_SrcClk                              0x0
    #define        clkD1_ctrl_ClkSwitch_DivClk                              0x1
    #define       bclkD1_ctrl_ClkD3Switch                      1
    #define        clkD1_ctrl_ClkD3Switch_NonDiv3Clk                        0x0
    #define        clkD1_ctrl_ClkD3Switch_Div3Clk                           0x1
    #define       bclkD1_ctrl_ClkSel                           3
    #define        clkD1_ctrl_ClkSel_d2                                     0x1
    #define        clkD1_ctrl_ClkSel_d4                                     0x2
    #define        clkD1_ctrl_ClkSel_d6                                     0x3
    #define        clkD1_ctrl_ClkSel_d8                                     0x4
    #define        clkD1_ctrl_ClkSel_d12                                    0x5
    typedef struct SIE_clkD1 {
    #define     w32clkD1_ctrl                                  {\
            UNSG32 uctrl_ClkEn                                 :  1;\
            UNSG32 uctrl_ClkPllSel                             :  3;\
            UNSG32 uctrl_ClkPllSwitch                          :  1;\
            UNSG32 uctrl_ClkSwitch                             :  1;\
            UNSG32 uctrl_ClkD3Switch                           :  1;\
            UNSG32 uctrl_ClkSel                                :  3;\
            UNSG32 RSVDx0_b10                                  : 22;\
          }
    union { UNSG32 u32clkD1_ctrl;
            struct w32clkD1_ctrl;
          };
    } SIE_clkD1;
    typedef union  T32clkD1_ctrl
          { UNSG32 u32;
            struct w32clkD1_ctrl;
                 } T32clkD1_ctrl;
    typedef union  TclkD1_ctrl
          { UNSG32 u32[1];
            struct {
            struct w32clkD1_ctrl;
                   };
                 } TclkD1_ctrl;
#endif
#ifndef h_clkD2
#define h_clkD2 (){}
    #define     RA_clkD2_ctrl                                  0x0000
    #define       bclkD2_ctrl_ClkEn                            1
    #define        clkD2_ctrl_ClkEn_enable                                  0x1
    #define        clkD2_ctrl_ClkEn_disable                                 0x0
    #define       bclkD2_ctrl_ClkPllSel                        3
    #define        clkD2_ctrl_ClkPllSel_AVPllB4                             0x0
    #define        clkD2_ctrl_ClkPllSel_AVPllB5                             0x1
    #define        clkD2_ctrl_ClkPllSel_AVPllB6                             0x2
    #define        clkD2_ctrl_ClkPllSel_AVPllB7                             0x3
    #define        clkD2_ctrl_ClkPllSel_SYSPLL                              0x4
    #define       bclkD2_ctrl_ClkPllSwitch                     1
    #define        clkD2_ctrl_ClkPllSwitch_SYSPLL                           0x0
    #define        clkD2_ctrl_ClkPllSwitch_AVPLL                            0x1
    #define       bclkD2_ctrl_ClkSwitch                        1
    #define        clkD2_ctrl_ClkSwitch_SrcClk                              0x0
    #define        clkD2_ctrl_ClkSwitch_DivClk                              0x1
    #define       bclkD2_ctrl_ClkD3Switch                      1
    #define        clkD2_ctrl_ClkD3Switch_NonDiv3Clk                        0x0
    #define        clkD2_ctrl_ClkD3Switch_Div3Clk                           0x1
    #define       bclkD2_ctrl_ClkSel                           3
    #define        clkD2_ctrl_ClkSel_d2                                     0x1
    #define        clkD2_ctrl_ClkSel_d4                                     0x2
    #define        clkD2_ctrl_ClkSel_d6                                     0x3
    #define        clkD2_ctrl_ClkSel_d8                                     0x4
    #define        clkD2_ctrl_ClkSel_d12                                    0x5
    typedef struct SIE_clkD2 {
    #define     w32clkD2_ctrl                                  {\
            UNSG32 uctrl_ClkEn                                 :  1;\
            UNSG32 uctrl_ClkPllSel                             :  3;\
            UNSG32 uctrl_ClkPllSwitch                          :  1;\
            UNSG32 uctrl_ClkSwitch                             :  1;\
            UNSG32 uctrl_ClkD3Switch                           :  1;\
            UNSG32 uctrl_ClkSel                                :  3;\
            UNSG32 RSVDx0_b10                                  : 22;\
          }
    union { UNSG32 u32clkD2_ctrl;
            struct w32clkD2_ctrl;
          };
    } SIE_clkD2;
    typedef union  T32clkD2_ctrl
          { UNSG32 u32;
            struct w32clkD2_ctrl;
                 } T32clkD2_ctrl;
    typedef union  TclkD2_ctrl
          { UNSG32 u32[1];
            struct {
            struct w32clkD2_ctrl;
                   };
                 } TclkD2_ctrl;
#endif
#ifndef h_clkD4
#define h_clkD4 (){}
    #define     RA_clkD4_ctrl                                  0x0000
    #define       bclkD4_ctrl_ClkEn                            1
    #define        clkD4_ctrl_ClkEn_enable                                  0x1
    #define        clkD4_ctrl_ClkEn_disable                                 0x0
    #define       bclkD4_ctrl_ClkPllSel                        3
    #define        clkD4_ctrl_ClkPllSel_AVPllB4                             0x0
    #define        clkD4_ctrl_ClkPllSel_AVPllB5                             0x1
    #define        clkD4_ctrl_ClkPllSel_AVPllB6                             0x2
    #define        clkD4_ctrl_ClkPllSel_AVPllB7                             0x3
    #define        clkD4_ctrl_ClkPllSel_SYSPLL                              0x4
    #define       bclkD4_ctrl_ClkPllSwitch                     1
    #define        clkD4_ctrl_ClkPllSwitch_SYSPLL                           0x0
    #define        clkD4_ctrl_ClkPllSwitch_AVPLL                            0x1
    #define       bclkD4_ctrl_ClkSwitch                        1
    #define        clkD4_ctrl_ClkSwitch_SrcClk                              0x0
    #define        clkD4_ctrl_ClkSwitch_DivClk                              0x1
    #define       bclkD4_ctrl_ClkD3Switch                      1
    #define        clkD4_ctrl_ClkD3Switch_NonDiv3Clk                        0x0
    #define        clkD4_ctrl_ClkD3Switch_Div3Clk                           0x1
    #define       bclkD4_ctrl_ClkSel                           3
    #define        clkD4_ctrl_ClkSel_d2                                     0x1
    #define        clkD4_ctrl_ClkSel_d4                                     0x2
    #define        clkD4_ctrl_ClkSel_d6                                     0x3
    #define        clkD4_ctrl_ClkSel_d8                                     0x4
    #define        clkD4_ctrl_ClkSel_d12                                    0x5
    typedef struct SIE_clkD4 {
    #define     w32clkD4_ctrl                                  {\
            UNSG32 uctrl_ClkEn                                 :  1;\
            UNSG32 uctrl_ClkPllSel                             :  3;\
            UNSG32 uctrl_ClkPllSwitch                          :  1;\
            UNSG32 uctrl_ClkSwitch                             :  1;\
            UNSG32 uctrl_ClkD3Switch                           :  1;\
            UNSG32 uctrl_ClkSel                                :  3;\
            UNSG32 RSVDx0_b10                                  : 22;\
          }
    union { UNSG32 u32clkD4_ctrl;
            struct w32clkD4_ctrl;
          };
    } SIE_clkD4;
    typedef union  T32clkD4_ctrl
          { UNSG32 u32;
            struct w32clkD4_ctrl;
                 } T32clkD4_ctrl;
    typedef union  TclkD4_ctrl
          { UNSG32 u32[1];
            struct {
            struct w32clkD4_ctrl;
                   };
                 } TclkD4_ctrl;
#endif
#ifndef h_clkD6
#define h_clkD6 (){}
    #define     RA_clkD6_ctrl                                  0x0000
    #define       bclkD6_ctrl_ClkEn                            1
    #define        clkD6_ctrl_ClkEn_enable                                  0x1
    #define        clkD6_ctrl_ClkEn_disable                                 0x0
    #define       bclkD6_ctrl_ClkPllSel                        3
    #define        clkD6_ctrl_ClkPllSel_AVPllB4                             0x0
    #define        clkD6_ctrl_ClkPllSel_AVPllB5                             0x1
    #define        clkD6_ctrl_ClkPllSel_AVPllB6                             0x2
    #define        clkD6_ctrl_ClkPllSel_AVPllB7                             0x3
    #define        clkD6_ctrl_ClkPllSel_SYSPLL                              0x4
    #define       bclkD6_ctrl_ClkPllSwitch                     1
    #define        clkD6_ctrl_ClkPllSwitch_SYSPLL                           0x0
    #define        clkD6_ctrl_ClkPllSwitch_AVPLL                            0x1
    #define       bclkD6_ctrl_ClkSwitch                        1
    #define        clkD6_ctrl_ClkSwitch_SrcClk                              0x0
    #define        clkD6_ctrl_ClkSwitch_DivClk                              0x1
    #define       bclkD6_ctrl_ClkD3Switch                      1
    #define        clkD6_ctrl_ClkD3Switch_NonDiv3Clk                        0x0
    #define        clkD6_ctrl_ClkD3Switch_Div3Clk                           0x1
    #define       bclkD6_ctrl_ClkSel                           3
    #define        clkD6_ctrl_ClkSel_d2                                     0x1
    #define        clkD6_ctrl_ClkSel_d4                                     0x2
    #define        clkD6_ctrl_ClkSel_d6                                     0x3
    #define        clkD6_ctrl_ClkSel_d8                                     0x4
    #define        clkD6_ctrl_ClkSel_d12                                    0x5
    typedef struct SIE_clkD6 {
    #define     w32clkD6_ctrl                                  {\
            UNSG32 uctrl_ClkEn                                 :  1;\
            UNSG32 uctrl_ClkPllSel                             :  3;\
            UNSG32 uctrl_ClkPllSwitch                          :  1;\
            UNSG32 uctrl_ClkSwitch                             :  1;\
            UNSG32 uctrl_ClkD3Switch                           :  1;\
            UNSG32 uctrl_ClkSel                                :  3;\
            UNSG32 RSVDx0_b10                                  : 22;\
          }
    union { UNSG32 u32clkD6_ctrl;
            struct w32clkD6_ctrl;
          };
    } SIE_clkD6;
    typedef union  T32clkD6_ctrl
          { UNSG32 u32;
            struct w32clkD6_ctrl;
                 } T32clkD6_ctrl;
    typedef union  TclkD6_ctrl
          { UNSG32 u32[1];
            struct {
            struct w32clkD6_ctrl;
                   };
                 } TclkD6_ctrl;
#endif
#ifndef h_clkD8
#define h_clkD8 (){}
    #define     RA_clkD8_ctrl                                  0x0000
    #define       bclkD8_ctrl_ClkEn                            1
    #define        clkD8_ctrl_ClkEn_enable                                  0x1
    #define        clkD8_ctrl_ClkEn_disable                                 0x0
    #define       bclkD8_ctrl_ClkPllSel                        3
    #define        clkD8_ctrl_ClkPllSel_AVPllB4                             0x0
    #define        clkD8_ctrl_ClkPllSel_AVPllB5                             0x1
    #define        clkD8_ctrl_ClkPllSel_AVPllB6                             0x2
    #define        clkD8_ctrl_ClkPllSel_AVPllB7                             0x3
    #define        clkD8_ctrl_ClkPllSel_SYSPLL                              0x4
    #define       bclkD8_ctrl_ClkPllSwitch                     1
    #define        clkD8_ctrl_ClkPllSwitch_SYSPLL                           0x0
    #define        clkD8_ctrl_ClkPllSwitch_AVPLL                            0x1
    #define       bclkD8_ctrl_ClkSwitch                        1
    #define        clkD8_ctrl_ClkSwitch_SrcClk                              0x0
    #define        clkD8_ctrl_ClkSwitch_DivClk                              0x1
    #define       bclkD8_ctrl_ClkD3Switch                      1
    #define        clkD8_ctrl_ClkD3Switch_NonDiv3Clk                        0x0
    #define        clkD8_ctrl_ClkD3Switch_Div3Clk                           0x1
    #define       bclkD8_ctrl_ClkSel                           3
    #define        clkD8_ctrl_ClkSel_d2                                     0x1
    #define        clkD8_ctrl_ClkSel_d4                                     0x2
    #define        clkD8_ctrl_ClkSel_d6                                     0x3
    #define        clkD8_ctrl_ClkSel_d8                                     0x4
    #define        clkD8_ctrl_ClkSel_d12                                    0x5
    typedef struct SIE_clkD8 {
    #define     w32clkD8_ctrl                                  {\
            UNSG32 uctrl_ClkEn                                 :  1;\
            UNSG32 uctrl_ClkPllSel                             :  3;\
            UNSG32 uctrl_ClkPllSwitch                          :  1;\
            UNSG32 uctrl_ClkSwitch                             :  1;\
            UNSG32 uctrl_ClkD3Switch                           :  1;\
            UNSG32 uctrl_ClkSel                                :  3;\
            UNSG32 RSVDx0_b10                                  : 22;\
          }
    union { UNSG32 u32clkD8_ctrl;
            struct w32clkD8_ctrl;
          };
    } SIE_clkD8;
    typedef union  T32clkD8_ctrl
          { UNSG32 u32;
            struct w32clkD8_ctrl;
                 } T32clkD8_ctrl;
    typedef union  TclkD8_ctrl
          { UNSG32 u32[1];
            struct {
            struct w32clkD8_ctrl;
                   };
                 } TclkD8_ctrl;
#endif
#ifndef h_droCount
#define h_droCount (){}
    #define     RA_droCount_result                             0x0000
    #define       bdroCount_result_value                       16
    typedef struct SIE_droCount {
    #define     w32droCount_result                             {\
            UNSG32 uresult_value                               : 16;\
            UNSG32 RSVDx0_b16                                  : 16;\
          }
    union { UNSG32 u32droCount_result;
            struct w32droCount_result;
          };
    } SIE_droCount;
    typedef union  T32droCount_result
          { UNSG32 u32;
            struct w32droCount_result;
                 } T32droCount_result;
    typedef union  TdroCount_result
          { UNSG32 u32[1];
            struct {
            struct w32droCount_result;
                   };
                 } TdroCount_result;
#endif
#ifndef h_efuse
#define h_efuse (){}
    #define     RA_efuse_ctrl                                  0x0000
    #define       befuse_ctrl_PROG_SEQ_CODE                    1
    #define       befuse_ctrl_PROG_SEQ_CODE_CLK                1
    #define       befuse_ctrl_SCLK                             1
    #define       befuse_ctrl_PRDT                             1
    #define       befuse_ctrl_POR_B                            1
    #define       befuse_ctrl_CSB                              1
    #define       befuse_ctrl_PGM                              1
    #define       befuse_ctrl_WPROT                            1
    #define       befuse_ctrl_TEST                             4
    #define     RA_efuse_status_match                          0x0004
    #define       befuse_status_match_MATCH_VALUE              1
    #define     RA_efuse_status_qout                           0x0008
    #define       befuse_status_qout_QOUT_31_0                 32
    #define     RA_efuse_status_qout1                          0x000C
    #define       befuse_status_qout_QOUT_63_32                32
    #define     RA_efuse_status_qout2                          0x0010
    #define       befuse_status_qout_QOUT_95_64                32
    #define     RA_efuse_status_qout3                          0x0014
    #define       befuse_status_qout_QOUT_127_96               32
    #define     RA_efuse_status_qout4                          0x0018
    #define       befuse_status_qout_QOUT_159_128              32
    #define     RA_efuse_status_qout5                          0x001C
    #define       befuse_status_qout_QOUT_191_160              32
    #define     RA_efuse_status_qout6                          0x0020
    #define       befuse_status_qout_QOUT_223_192              32
    #define     RA_efuse_status_qout7                          0x0024
    #define       befuse_status_qout_QOUT_255_224              32
    #define     RA_efuse_status_qout8                          0x0028
    #define       befuse_status_qout_QOUT_256                  1
    typedef struct SIE_efuse {
    #define     w32efuse_ctrl                                  {\
            UNSG32 uctrl_PROG_SEQ_CODE                         :  1;\
            UNSG32 uctrl_PROG_SEQ_CODE_CLK                     :  1;\
            UNSG32 uctrl_SCLK                                  :  1;\
            UNSG32 uctrl_PRDT                                  :  1;\
            UNSG32 uctrl_POR_B                                 :  1;\
            UNSG32 uctrl_CSB                                   :  1;\
            UNSG32 uctrl_PGM                                   :  1;\
            UNSG32 uctrl_WPROT                                 :  1;\
            UNSG32 uctrl_TEST                                  :  4;\
            UNSG32 RSVDx0_b12                                  : 20;\
          }
    union { UNSG32 u32efuse_ctrl;
            struct w32efuse_ctrl;
          };
    #define     w32efuse_status_match                          {\
            UNSG32 ustatus_match_MATCH_VALUE                   :  1;\
            UNSG32 RSVDx4_b1                                   : 31;\
          }
    union { UNSG32 u32efuse_status_match;
            struct w32efuse_status_match;
          };
    #define     w32efuse_status_qout                           {\
            UNSG32 ustatus_qout_QOUT_31_0                      : 32;\
          }
    union { UNSG32 u32efuse_status_qout;
            struct w32efuse_status_qout;
          };
    #define     w32efuse_status_qout1                          {\
            UNSG32 ustatus_qout_QOUT_63_32                     : 32;\
          }
    union { UNSG32 u32efuse_status_qout1;
            struct w32efuse_status_qout1;
          };
    #define     w32efuse_status_qout2                          {\
            UNSG32 ustatus_qout_QOUT_95_64                     : 32;\
          }
    union { UNSG32 u32efuse_status_qout2;
            struct w32efuse_status_qout2;
          };
    #define     w32efuse_status_qout3                          {\
            UNSG32 ustatus_qout_QOUT_127_96                    : 32;\
          }
    union { UNSG32 u32efuse_status_qout3;
            struct w32efuse_status_qout3;
          };
    #define     w32efuse_status_qout4                          {\
            UNSG32 ustatus_qout_QOUT_159_128                   : 32;\
          }
    union { UNSG32 u32efuse_status_qout4;
            struct w32efuse_status_qout4;
          };
    #define     w32efuse_status_qout5                          {\
            UNSG32 ustatus_qout_QOUT_191_160                   : 32;\
          }
    union { UNSG32 u32efuse_status_qout5;
            struct w32efuse_status_qout5;
          };
    #define     w32efuse_status_qout6                          {\
            UNSG32 ustatus_qout_QOUT_223_192                   : 32;\
          }
    union { UNSG32 u32efuse_status_qout6;
            struct w32efuse_status_qout6;
          };
    #define     w32efuse_status_qout7                          {\
            UNSG32 ustatus_qout_QOUT_255_224                   : 32;\
          }
    union { UNSG32 u32efuse_status_qout7;
            struct w32efuse_status_qout7;
          };
    #define     w32efuse_status_qout8                          {\
            UNSG32 ustatus_qout_QOUT_256                       :  1;\
            UNSG32 RSVDx28_b1                                  : 31;\
          }
    union { UNSG32 u32efuse_status_qout8;
            struct w32efuse_status_qout8;
          };
    } SIE_efuse;
    typedef union  T32efuse_ctrl
          { UNSG32 u32;
            struct w32efuse_ctrl;
                 } T32efuse_ctrl;
    typedef union  T32efuse_status_match
          { UNSG32 u32;
            struct w32efuse_status_match;
                 } T32efuse_status_match;
    typedef union  T32efuse_status_qout
          { UNSG32 u32;
            struct w32efuse_status_qout;
                 } T32efuse_status_qout;
    typedef union  T32efuse_status_qout1
          { UNSG32 u32;
            struct w32efuse_status_qout1;
                 } T32efuse_status_qout1;
    typedef union  T32efuse_status_qout2
          { UNSG32 u32;
            struct w32efuse_status_qout2;
                 } T32efuse_status_qout2;
    typedef union  T32efuse_status_qout3
          { UNSG32 u32;
            struct w32efuse_status_qout3;
                 } T32efuse_status_qout3;
    typedef union  T32efuse_status_qout4
          { UNSG32 u32;
            struct w32efuse_status_qout4;
                 } T32efuse_status_qout4;
    typedef union  T32efuse_status_qout5
          { UNSG32 u32;
            struct w32efuse_status_qout5;
                 } T32efuse_status_qout5;
    typedef union  T32efuse_status_qout6
          { UNSG32 u32;
            struct w32efuse_status_qout6;
                 } T32efuse_status_qout6;
    typedef union  T32efuse_status_qout7
          { UNSG32 u32;
            struct w32efuse_status_qout7;
                 } T32efuse_status_qout7;
    typedef union  T32efuse_status_qout8
          { UNSG32 u32;
            struct w32efuse_status_qout8;
                 } T32efuse_status_qout8;
    typedef union  Tefuse_ctrl
          { UNSG32 u32[1];
            struct {
            struct w32efuse_ctrl;
                   };
                 } Tefuse_ctrl;
    typedef union  Tefuse_status_match
          { UNSG32 u32[1];
            struct {
            struct w32efuse_status_match;
                   };
                 } Tefuse_status_match;
    typedef union  Tefuse_status_qout
          { UNSG32 u32[9];
            struct {
            struct w32efuse_status_qout;
            struct w32efuse_status_qout1;
            struct w32efuse_status_qout2;
            struct w32efuse_status_qout3;
            struct w32efuse_status_qout4;
            struct w32efuse_status_qout5;
            struct w32efuse_status_qout6;
            struct w32efuse_status_qout7;
            struct w32efuse_status_qout8;
                   };
                 } Tefuse_status_qout;
#endif
#ifndef h_Gbl
#define h_Gbl (){}
    #define     RA_Gbl_pinMux                                  0x0000
    #define       bGbl_pinMux_gp0                              3
    #define        Gbl_pinMux_gp0_MODE_0                                    0x0
    #define        Gbl_pinMux_gp0_MODE_1                                    0x1
    #define        Gbl_pinMux_gp0_MODE_2                                    0x2
    #define        Gbl_pinMux_gp0_MODE_3                                    0x3
    #define       bGbl_pinMux_gp1                              3
    #define        Gbl_pinMux_gp1_MODE_0                                    0x0
    #define        Gbl_pinMux_gp1_MODE_1                                    0x1
    #define        Gbl_pinMux_gp1_MODE_6                                    0x6
    #define        Gbl_pinMux_gp1_MODE_7                                    0x7
    #define       bGbl_pinMux_gp2                              3
    #define        Gbl_pinMux_gp2_MODE_0                                    0x0
    #define        Gbl_pinMux_gp2_MODE_1                                    0x1
    #define        Gbl_pinMux_gp2_MODE_2                                    0x2
    #define        Gbl_pinMux_gp2_MODE_3                                    0x3
    #define        Gbl_pinMux_gp2_MODE_6                                    0x6
    #define        Gbl_pinMux_gp2_MODE_7                                    0x7
    #define       bGbl_pinMux_gp3                              3
    #define        Gbl_pinMux_gp3_MODE_0                                    0x0
    #define        Gbl_pinMux_gp3_MODE_1                                    0x1
    #define        Gbl_pinMux_gp3_MODE_2                                    0x2
    #define        Gbl_pinMux_gp3_MODE_3                                    0x3
    #define        Gbl_pinMux_gp3_MODE_4                                    0x4
    #define        Gbl_pinMux_gp3_MODE_6                                    0x6
    #define        Gbl_pinMux_gp3_MODE_7                                    0x7
    #define       bGbl_pinMux_gp4                              3
    #define        Gbl_pinMux_gp4_MODE_0                                    0x0
    #define        Gbl_pinMux_gp4_MODE_1                                    0x1
    #define        Gbl_pinMux_gp4_MODE_2                                    0x2
    #define        Gbl_pinMux_gp4_MODE_3                                    0x3
    #define        Gbl_pinMux_gp4_MODE_4                                    0x4
    #define        Gbl_pinMux_gp4_MODE_6                                    0x6
    #define        Gbl_pinMux_gp4_MODE_7                                    0x7
    #define       bGbl_pinMux_gp5                              3
    #define        Gbl_pinMux_gp5_MODE_0                                    0x0
    #define        Gbl_pinMux_gp5_MODE_1                                    0x1
    #define        Gbl_pinMux_gp5_MODE_2                                    0x2
    #define        Gbl_pinMux_gp5_MODE_3                                    0x3
    #define        Gbl_pinMux_gp5_MODE_4                                    0x4
    #define        Gbl_pinMux_gp5_MODE_6                                    0x6
    #define        Gbl_pinMux_gp5_MODE_7                                    0x7
    #define       bGbl_pinMux_gp6                              3
    #define        Gbl_pinMux_gp6_MODE_0                                    0x0
    #define        Gbl_pinMux_gp6_MODE_1                                    0x1
    #define       bGbl_pinMux_gp7                              3
    #define        Gbl_pinMux_gp7_MODE_0                                    0x0
    #define        Gbl_pinMux_gp7_MODE_1                                    0x1
    #define        Gbl_pinMux_gp7_MODE_2                                    0x2
    #define       bGbl_pinMux_gp8                              3
    #define        Gbl_pinMux_gp8_MODE_0                                    0x0
    #define        Gbl_pinMux_gp8_MODE_1                                    0x1
    #define       bGbl_pinMux_gp9                              3
    #define        Gbl_pinMux_gp9_MODE_0                                    0x0
    #define        Gbl_pinMux_gp9_MODE_1                                    0x1
    #define        Gbl_pinMux_gp9_MODE_3                                    0x3
    #define       bGbl_pinMux_gp10                             2
    #define        Gbl_pinMux_gp10_MODE_0                                   0x0
    #define        Gbl_pinMux_gp10_MODE_1                                   0x1
    #define     RA_Gbl_pinMux1                                 0x0004
    #define       bGbl_pinMux_gp11                             2
    #define        Gbl_pinMux_gp11_MODE_0                                   0x0
    #define        Gbl_pinMux_gp11_MODE_1                                   0x1
    #define       bGbl_pinMux_gp12                             3
    #define        Gbl_pinMux_gp12_MODE_0                                   0x0
    #define        Gbl_pinMux_gp12_MODE_1                                   0x1
    #define       bGbl_pinMux_gp13                             3
    #define        Gbl_pinMux_gp13_MODE_0                                   0x0
    #define        Gbl_pinMux_gp13_MODE_1                                   0x1
    #define        Gbl_pinMux_gp13_MODE_2                                   0x2
    #define       bGbl_pinMux_gp14                             1
    #define        Gbl_pinMux_gp14_MODE_0                                   0x0
    #define        Gbl_pinMux_gp14_MODE_1                                   0x1
    #define       bGbl_pinMux_gp15                             3
    #define        Gbl_pinMux_gp15_MODE_0                                   0x0
    #define        Gbl_pinMux_gp15_MODE_1                                   0x1
    #define       bGbl_pinMux_gp16                             3
    #define        Gbl_pinMux_gp16_MODE_0                                   0x0
    #define        Gbl_pinMux_gp16_MODE_1                                   0x1
    #define        Gbl_pinMux_gp16_MODE_2                                   0x2
    #define        Gbl_pinMux_gp16_MODE_4                                   0x4
    #define       bGbl_pinMux_gp17                             3
    #define        Gbl_pinMux_gp17_MODE_0                                   0x0
    #define        Gbl_pinMux_gp17_MODE_1                                   0x1
    #define        Gbl_pinMux_gp17_MODE_2                                   0x2
    #define        Gbl_pinMux_gp17_MODE_3                                   0x3
    #define        Gbl_pinMux_gp17_MODE_4                                   0x4
    #define        Gbl_pinMux_gp17_MODE_5                                   0x5
    #define       bGbl_pinMux_gp18                             2
    #define        Gbl_pinMux_gp18_MODE_0                                   0x0
    #define        Gbl_pinMux_gp18_MODE_1                                   0x1
    #define        Gbl_pinMux_gp18_MODE_2                                   0x2
    #define        Gbl_pinMux_gp18_MODE_3                                   0x3
    #define       bGbl_pinMux_gp19                             2
    #define        Gbl_pinMux_gp19_MODE_0                                   0x0
    #define        Gbl_pinMux_gp19_MODE_1                                   0x1
    #define        Gbl_pinMux_gp19_MODE_2                                   0x2
    #define        Gbl_pinMux_gp19_MODE_3                                   0x3
    #define       bGbl_pinMux_gp20                             2
    #define        Gbl_pinMux_gp20_MODE_0                                   0x0
    #define        Gbl_pinMux_gp20_MODE_1                                   0x1
    #define        Gbl_pinMux_gp20_MODE_2                                   0x2
    #define       bGbl_pinMux_gp21                             3
    #define        Gbl_pinMux_gp21_MODE_0                                   0x0
    #define        Gbl_pinMux_gp21_MODE_1                                   0x1
    #define        Gbl_pinMux_gp21_MODE_2                                   0x2
    #define        Gbl_pinMux_gp21_MODE_3                                   0x3
    #define        Gbl_pinMux_gp21_MODE_7                                   0x7
    #define       bGbl_pinMux_gp22                             3
    #define        Gbl_pinMux_gp22_MODE_0                                   0x0
    #define        Gbl_pinMux_gp22_MODE_1                                   0x1
    #define        Gbl_pinMux_gp22_MODE_2                                   0x2
    #define        Gbl_pinMux_gp22_MODE_3                                   0x3
    #define        Gbl_pinMux_gp22_MODE_4                                   0x4
    #define     RA_Gbl_pinMux2                                 0x0008
    #define       bGbl_pinMux_gp23                             3
    #define        Gbl_pinMux_gp23_MODE_0                                   0x0
    #define        Gbl_pinMux_gp23_MODE_1                                   0x1
    #define        Gbl_pinMux_gp23_MODE_2                                   0x2
    #define        Gbl_pinMux_gp23_MODE_3                                   0x3
    #define        Gbl_pinMux_gp23_MODE_4                                   0x4
    #define        Gbl_pinMux_gp23_MODE_7                                   0x7
    #define       bGbl_pinMux_gp24                             2
    #define        Gbl_pinMux_gp24_MODE_0                                   0x0
    #define        Gbl_pinMux_gp24_MODE_1                                   0x1
    #define        Gbl_pinMux_gp24_MODE_2                                   0x2
    #define       bGbl_pinMux_gp25                             2
    #define        Gbl_pinMux_gp25_MODE_0                                   0x0
    #define        Gbl_pinMux_gp25_MODE_1                                   0x1
    #define        Gbl_pinMux_gp25_MODE_2                                   0x2
    #define        Gbl_pinMux_gp25_MODE_3                                   0x3
    #define       bGbl_pinMux_gp26                             1
    #define        Gbl_pinMux_gp26_MODE_0                                   0x0
    #define        Gbl_pinMux_gp26_MODE_1                                   0x1
    #define       bGbl_pinMux_gp27                             2
    #define        Gbl_pinMux_gp27_MODE_0                                   0x0
    #define        Gbl_pinMux_gp27_MODE_1                                   0x1
    #define        Gbl_pinMux_gp27_MODE_3                                   0x3
    #define       bGbl_pinMux_gp28                             3
    #define        Gbl_pinMux_gp28_MODE_0                                   0x0
    #define        Gbl_pinMux_gp28_MODE_1                                   0x1
    #define        Gbl_pinMux_gp28_MODE_2                                   0x2
    #define        Gbl_pinMux_gp28_MODE_5                                   0x5
    #define       bGbl_pinMux_gp29                             3
    #define        Gbl_pinMux_gp29_MODE_0                                   0x0
    #define        Gbl_pinMux_gp29_MODE_2                                   0x2
    #define        Gbl_pinMux_gp29_MODE_5                                   0x5
    #define        Gbl_pinMux_gp29_MODE_6                                   0x6
    #define     RA_Gbl_bootStrap                               0x000C
    #define       bGbl_bootStrap_softwareStrap                 7
    #define       bGbl_bootStrap_bootSrc                       2
    #define       bGbl_bootStrap_sysPllByps                    1
    #define        Gbl_bootStrap_sysPllByps_PLL_OUT                         0x0
    #define        Gbl_bootStrap_sysPllByps_BYPS                            0x1
    #define       bGbl_bootStrap_memPllByps                    1
    #define        Gbl_bootStrap_memPllByps_PLL_OUT                         0x0
    #define        Gbl_bootStrap_memPllByps_BYPS                            0x1
    #define       bGbl_bootStrap_cpuPllByps                    1
    #define        Gbl_bootStrap_cpuPllByps_PLL_OUT                         0x0
    #define        Gbl_bootStrap_cpuPllByps_BYPS                            0x1
    #define       bGbl_bootStrap_pllPwrDown                    1
    #define        Gbl_bootStrap_pllPwrDown_POWER_UP                        0x0
    #define        Gbl_bootStrap_pllPwrDown_POWER_DOWN                      0x1
    #define       bGbl_bootStrap_refClk12P5M                   1
    #define        Gbl_bootStrap_refClk12P5M_REFCLK25M                      0x0
    #define        Gbl_bootStrap_refClk12P5M_REFCLK12P5M                    0x1
    #define       bGbl_bootStrap_socJtagFromSM                 1
    #define        Gbl_bootStrap_socJtagFromSM_fromPinMux                   0x0
    #define        Gbl_bootStrap_socJtagFromSM_fromSM                       0x1
    #define       bGbl_bootStrap_nandV18Enable                 1
    #define        Gbl_bootStrap_nandV18Enable_V1R8                         0x1
    #define        Gbl_bootStrap_nandV18Enable_V3R3                         0x0
    #define       bGbl_bootStrap_spi1V18Enable                 1
    #define        Gbl_bootStrap_spi1V18Enable_V1R8                         0x0
    #define        Gbl_bootStrap_spi1V18Enable_V3R3                         0x1
    #define       bGbl_bootStrap_nandV25Enable                 1
    #define       bGbl_bootStrap_spi1V25Enable                 1
    #define       bGbl_bootStrap_ENG_EN                        1
    #define        Gbl_bootStrap_ENG_EN_PRODUCTION_MODE                     0x0
    #define        Gbl_bootStrap_ENG_EN_DEVELOPE_MODE                       0x1
    #define     RA_Gbl_anaGrpCtl                               0x0010
    #define       bGbl_anaGrpCtl_anaGrpPu                      1
    #define       bGbl_anaGrpCtl_anaGrpBgSel                   2
    #define       bGbl_anaGrpCtl_anaGrpPuXtl                   1
    #define       bGbl_anaGrpCtl_anaGrpGainX2                  1
    #define       bGbl_anaGrpCtl_anaGrpSelClkDigDiv1           2
    #define       bGbl_anaGrpCtl_anaGrpSelClkDigDiv2           2
    #define       bGbl_anaGrpCtl_anaGrpSelClkDigDiv3           2
    #define       bGbl_anaGrpCtl_anaGrpSelClkDigDiv4           2
    #define       bGbl_anaGrpCtl_anaGrpPuOsc                   1
    #define       bGbl_anaGrpCtl_anaGrpSpeedOsc                2
    #define       bGbl_anaGrpCtl_anaGrpTestAna                 4
    #define     RA_Gbl_sysPllCtl                               0x0014
    #define       bGbl_sysPllCtl_sysPllPu                      1
    #define       bGbl_sysPllCtl_sysPllRfDiv                   5
    #define       bGbl_sysPllCtl_sysPllFbDiv                   9
    #define       bGbl_sysPllCtl_sysPllVddm                    2
    #define        Gbl_sysPllCtl_sysPllVddm_1R40v                           0x0
    #define        Gbl_sysPllCtl_sysPllVddm_1R45v                           0x1
    #define        Gbl_sysPllCtl_sysPllVddm_1R50v                           0x2
    #define        Gbl_sysPllCtl_sysPllVddm_1R55v                           0x3
    #define       bGbl_sysPllCtl_sysPllVddl                    4
    #define        Gbl_sysPllCtl_sysPllVddl_0R78v                           0x1
    #define        Gbl_sysPllCtl_sysPllVddl_0R82v                           0x2
    #define        Gbl_sysPllCtl_sysPllVddl_0R86v                           0x3
    #define        Gbl_sysPllCtl_sysPllVddl_0R90v                           0x4
    #define        Gbl_sysPllCtl_sysPllVddl_0R94v                           0x5
    #define        Gbl_sysPllCtl_sysPllVddl_0R98v                           0x6
    #define        Gbl_sysPllCtl_sysPllVddl_1R02v                           0x7
    #define        Gbl_sysPllCtl_sysPllVddl_1R06v                           0x8
    #define        Gbl_sysPllCtl_sysPllVddl_1R10v                           0x9
    #define        Gbl_sysPllCtl_sysPllVddl_1R14v                           0xA
    #define        Gbl_sysPllCtl_sysPllVddl_1R16v                           0xB
    #define       bGbl_sysPllCtl_sysPllVregIVRef               2
    #define       bGbl_sysPllCtl_sysPllIcp                     3
    #define        Gbl_sysPllCtl_sysPllIcp_2uA                              0x0
    #define        Gbl_sysPllCtl_sysPllIcp_3uA                              0x1
    #define        Gbl_sysPllCtl_sysPllIcp_4uA                              0x2
    #define        Gbl_sysPllCtl_sysPllIcp_5uA                              0x3
    #define        Gbl_sysPllCtl_sysPllIcp_6uA                              0x4
    #define        Gbl_sysPllCtl_sysPllIcp_7uA                              0x5
    #define        Gbl_sysPllCtl_sysPllIcp_8uA                              0x6
    #define        Gbl_sysPllCtl_sysPllIcp_9uA                              0x7
    #define       bGbl_sysPllCtl_sysPllKvco                    4
    #define        Gbl_sysPllCtl_sysPllKvco_1R25Gto1R35G                    0x1
    #define        Gbl_sysPllCtl_sysPllKvco_1R35Gto1R55G                    0x2
    #define        Gbl_sysPllCtl_sysPllKvco_1R55Gto1R75G                    0x3
    #define        Gbl_sysPllCtl_sysPllKvco_1R75Gto1R95G                    0x4
    #define        Gbl_sysPllCtl_sysPllKvco_1R95Gto2R15G                    0x5
    #define        Gbl_sysPllCtl_sysPllKvco_2R15Gto2R4G                     0x6
    #define        Gbl_sysPllCtl_sysPllKvco_2R4Gto2R5G                      0x7
    #define       bGbl_sysPllCtl_sysPllCtune                   2
    #define     RA_Gbl_sysPllCtl1                              0x0018
    #define       bGbl_sysPllCtl_sysPllVcoRng                  3
    #define       bGbl_sysPllCtl_sysPllVcoDivSelDiff           4
    #define       bGbl_sysPllCtl_sysPllVcoDivSelSe             4
    #define       bGbl_sysPllCtl_sysPllDiffClkEn               1
    #define       bGbl_sysPllCtl_sysPllSelVcoDiff              1
    #define       bGbl_sysPllCtl_sysPllSelVcoClkSe             1
    #define       bGbl_sysPllCtl_sysPllBypassFbDiv             1
    #define       bGbl_sysPllCtl_sysPllBypassEn                1
    #define       bGbl_sysPllCtl_sysPllGateClkCtrl             1
    #define       bGbl_sysPllCtl_sysPllLineUpEn                1
    #define       bGbl_sysPllCtl_sysPllIntpi                   4
    #define       bGbl_sysPllCtl_sysPllPiEn                    1
    #define       bGbl_sysPllCtl_sysPllSscClkEn                1
    #define       bGbl_sysPllCtl_sysPllClkDetEn                1
    #define       bGbl_sysPllCtl_sysPllFreqOffsetEn            1
    #define     RA_Gbl_sysPllCtl2                              0x001C
    #define       bGbl_sysPllCtl_sysPllFreqOffset              17
    #define       bGbl_sysPllCtl_sysPllFreqOffsetModeSel       1
    #define       bGbl_sysPllCtl_sysPllFreqOffsetValid         1
    #define       bGbl_sysPllCtl_sysPllSscEn                   1
    #define        Gbl_sysPllCtl_sysPllSscEn_Disable                        0x0
    #define        Gbl_sysPllCtl_sysPllSscEn_Enable                         0x1
    #define       bGbl_sysPllCtl_sysPllSscmode                 1
    #define        Gbl_sysPllCtl_sysPllSscmode_Centre                       0x0
    #define        Gbl_sysPllCtl_sysPllSscmode_Down                         0x1
    #define     RA_Gbl_sysPllCtl3                              0x0020
    #define       bGbl_sysPllCtl_sysPllSscFdiv                 16
    #define       bGbl_sysPllCtl_sysPllSscRnge                 11
    #define       bGbl_sysPllCtl_sysPllSscResetExt             1
    #define        Gbl_sysPllCtl_sysPllSscResetExt_Int                      0x0
    #define        Gbl_sysPllCtl_sysPllSscResetExt_Ext                      0x1
    #define       bGbl_sysPllCtl_sysPllTestMon                 4
    #define     RA_Gbl_sysPllCtl4                              0x0024
    #define       bGbl_sysPllCtl_sysPllRsvdIn                  4
    #define       bGbl_sysPllCtl_sysPllExtRst                  1
    #define     RA_Gbl_memPllCtl                               0x0028
    #define       bGbl_memPllCtl_memPllPu                      1
    #define       bGbl_memPllCtl_memPllRfDiv                   5
    #define       bGbl_memPllCtl_memPllFbDiv                   9
    #define       bGbl_memPllCtl_memPllVddm                    2
    #define        Gbl_memPllCtl_memPllVddm_1R40v                           0x0
    #define        Gbl_memPllCtl_memPllVddm_1R45v                           0x1
    #define        Gbl_memPllCtl_memPllVddm_1R50v                           0x2
    #define        Gbl_memPllCtl_memPllVddm_1R55v                           0x3
    #define       bGbl_memPllCtl_memPllVddl                    4
    #define        Gbl_memPllCtl_memPllVddl_0R78v                           0x1
    #define        Gbl_memPllCtl_memPllVddl_0R82v                           0x2
    #define        Gbl_memPllCtl_memPllVddl_0R86v                           0x3
    #define        Gbl_memPllCtl_memPllVddl_0R90v                           0x4
    #define       bGbl_memPllCtl_memPllVregIVRef               2
    #define       bGbl_memPllCtl_memPllIcp                     3
    #define        Gbl_memPllCtl_memPllIcp_2uA                              0x0
    #define        Gbl_memPllCtl_memPllIcp_3uA                              0x1
    #define        Gbl_memPllCtl_memPllIcp_4uA                              0x2
    #define        Gbl_memPllCtl_memPllIcp_5uA                              0x3
    #define        Gbl_memPllCtl_memPllIcp_6uA                              0x4
    #define        Gbl_memPllCtl_memPllIcp_7uA                              0x5
    #define        Gbl_memPllCtl_memPllIcp_8uA                              0x6
    #define        Gbl_memPllCtl_memPllIcp_9uA                              0x7
    #define       bGbl_memPllCtl_memPllKvco                    4
    #define        Gbl_memPllCtl_memPllKvco_1R25Gto1R35G                    0x1
    #define        Gbl_memPllCtl_memPllKvco_1R35Gto1R55G                    0x2
    #define        Gbl_memPllCtl_memPllKvco_1R55Gto1R75G                    0x3
    #define        Gbl_memPllCtl_memPllKvco_1R75Gto1R95G                    0x4
    #define        Gbl_memPllCtl_memPllKvco_1R95Gto2R15G                    0x5
    #define        Gbl_memPllCtl_memPllKvco_2R15Gto2R4G                     0x6
    #define        Gbl_memPllCtl_memPllKvco_2R4Gto2R5G                      0x7
    #define       bGbl_memPllCtl_memPllCtune                   2
    #define     RA_Gbl_memPllCtl1                              0x002C
    #define       bGbl_memPllCtl_memPllVcoRng                  3
    #define       bGbl_memPllCtl_memPllVcoDivSelDiff           4
    #define       bGbl_memPllCtl_memPllVcoDivSelSe             4
    #define       bGbl_memPllCtl_memPllDiffClkEn               1
    #define       bGbl_memPllCtl_memPllSelVcoDiff              1
    #define       bGbl_memPllCtl_memPllSelVcoClkSe             1
    #define       bGbl_memPllCtl_memPllBypassFbDiv             1
    #define       bGbl_memPllCtl_memPllBypassEn                1
    #define       bGbl_memPllCtl_memPllGateClkCtrl             1
    #define       bGbl_memPllCtl_memPllLineUpEn                1
    #define       bGbl_memPllCtl_memPllIntpi                   4
    #define       bGbl_memPllCtl_memPllPiEn                    1
    #define       bGbl_memPllCtl_memPllSscClkEn                1
    #define       bGbl_memPllCtl_memPllClkDetEn                1
    #define       bGbl_memPllCtl_memPllFreqOffsetEn            1
    #define     RA_Gbl_memPllCtl2                              0x0030
    #define       bGbl_memPllCtl_memPllFreqOffset              17
    #define       bGbl_memPllCtl_memPllFreqOffsetModeSel       1
    #define       bGbl_memPllCtl_memPllFreqOffsetValid         1
    #define       bGbl_memPllCtl_memPllSscEn                   1
    #define        Gbl_memPllCtl_memPllSscEn_Disable                        0x0
    #define        Gbl_memPllCtl_memPllSscEn_Enable                         0x1
    #define       bGbl_memPllCtl_memPllSscmode                 1
    #define        Gbl_memPllCtl_memPllSscmode_Centre                       0x0
    #define        Gbl_memPllCtl_memPllSscmode_Down                         0x1
    #define     RA_Gbl_memPllCtl3                              0x0034
    #define       bGbl_memPllCtl_memPllSscFdiv                 16
    #define       bGbl_memPllCtl_memPllSscRnge                 11
    #define       bGbl_memPllCtl_memPllSscResetExt             1
    #define        Gbl_memPllCtl_memPllSscResetExt_Int                      0x0
    #define        Gbl_memPllCtl_memPllSscResetExt_Ext                      0x1
    #define       bGbl_memPllCtl_memPllTestMon                 4
    #define     RA_Gbl_memPllCtl4                              0x0038
    #define       bGbl_memPllCtl_memPllRsvdIn                  4
    #define       bGbl_memPllCtl_memPllExtRst                  1
    #define     RA_Gbl_cpuPllCtl                               0x003C
    #define       bGbl_cpuPllCtl_cpuPllPu                      1
    #define       bGbl_cpuPllCtl_cpuPllRfDiv                   5
    #define       bGbl_cpuPllCtl_cpuPllFbDiv                   9
    #define       bGbl_cpuPllCtl_cpuPllVddm                    2
    #define        Gbl_cpuPllCtl_cpuPllVddm_1R40v                           0x0
    #define        Gbl_cpuPllCtl_cpuPllVddm_1R45v                           0x1
    #define        Gbl_cpuPllCtl_cpuPllVddm_1R50v                           0x2
    #define        Gbl_cpuPllCtl_cpuPllVddm_1R55v                           0x3
    #define       bGbl_cpuPllCtl_cpuPllVddl                    4
    #define        Gbl_cpuPllCtl_cpuPllVddl_0R78v                           0x1
    #define        Gbl_cpuPllCtl_cpuPllVddl_0R82v                           0x2
    #define        Gbl_cpuPllCtl_cpuPllVddl_0R86v                           0x3
    #define        Gbl_cpuPllCtl_cpuPllVddl_0R90v                           0x4
    #define        Gbl_cpuPllCtl_cpuPllVddl_0R94v                           0x5
    #define        Gbl_cpuPllCtl_cpuPllVddl_0R98v                           0x6
    #define        Gbl_cpuPllCtl_cpuPllVddl_1R02v                           0x7
    #define        Gbl_cpuPllCtl_cpuPllVddl_1R06v                           0x8
    #define        Gbl_cpuPllCtl_cpuPllVddl_1R10v                           0x9
    #define        Gbl_cpuPllCtl_cpuPllVddl_1R14v                           0xA
    #define        Gbl_cpuPllCtl_cpuPllVddl_1R16v                           0xB
    #define       bGbl_cpuPllCtl_cpuPllVregIVRef               2
    #define       bGbl_cpuPllCtl_cpuPllIcp                     3
    #define        Gbl_cpuPllCtl_cpuPllIcp_2uA                              0x0
    #define        Gbl_cpuPllCtl_cpuPllIcp_3uA                              0x1
    #define        Gbl_cpuPllCtl_cpuPllIcp_4uA                              0x2
    #define        Gbl_cpuPllCtl_cpuPllIcp_5uA                              0x3
    #define        Gbl_cpuPllCtl_cpuPllIcp_6uA                              0x4
    #define        Gbl_cpuPllCtl_cpuPllIcp_7uA                              0x5
    #define        Gbl_cpuPllCtl_cpuPllIcp_8uA                              0x6
    #define        Gbl_cpuPllCtl_cpuPllIcp_9uA                              0x7
    #define       bGbl_cpuPllCtl_cpuPllKvco                    4
    #define        Gbl_cpuPllCtl_cpuPllKvco_1R25Gto1R35G                    0x1
    #define        Gbl_cpuPllCtl_cpuPllKvco_1R35Gto1R55G                    0x2
    #define        Gbl_cpuPllCtl_cpuPllKvco_1R55Gto1R75G                    0x3
    #define        Gbl_cpuPllCtl_cpuPllKvco_1R75Gto1R95G                    0x4
    #define        Gbl_cpuPllCtl_cpuPllKvco_1R95Gto2R15G                    0x5
    #define        Gbl_cpuPllCtl_cpuPllKvco_2R15Gto2R4G                     0x6
    #define        Gbl_cpuPllCtl_cpuPllKvco_2R4Gto2R5G                      0x7
    #define       bGbl_cpuPllCtl_cpuPllCtune                   2
    #define     RA_Gbl_cpuPllCtl1                              0x0040
    #define       bGbl_cpuPllCtl_cpuPllVcoRng                  3
    #define       bGbl_cpuPllCtl_cpuPllVcoDivSelDiff           4
    #define       bGbl_cpuPllCtl_cpuPllVcoDivSelSe             4
    #define       bGbl_cpuPllCtl_cpuPllDiffClkEn               1
    #define       bGbl_cpuPllCtl_cpuPllSelVcoDiff              1
    #define       bGbl_cpuPllCtl_cpuPllSelVcoClkSe             1
    #define       bGbl_cpuPllCtl_cpuPllBypassFbDiv             1
    #define       bGbl_cpuPllCtl_cpuPllBypassEn                1
    #define       bGbl_cpuPllCtl_cpuPllGateClkCtrl             1
    #define       bGbl_cpuPllCtl_cpuPllLineUpEn                1
    #define       bGbl_cpuPllCtl_cpuPllIntpi                   4
    #define       bGbl_cpuPllCtl_cpuPllPiEn                    1
    #define       bGbl_cpuPllCtl_cpuPllSscClkEn                1
    #define       bGbl_cpuPllCtl_cpuPllClkDetEn                1
    #define       bGbl_cpuPllCtl_cpuPllFreqOffsetEn            1
    #define     RA_Gbl_cpuPllCtl2                              0x0044
    #define       bGbl_cpuPllCtl_cpuPllFreqOffset              17
    #define       bGbl_cpuPllCtl_cpuPllFreqOffsetModeSel       1
    #define       bGbl_cpuPllCtl_cpuPllFreqOffsetValid         1
    #define       bGbl_cpuPllCtl_cpuPllSscEn                   1
    #define        Gbl_cpuPllCtl_cpuPllSscEn_Disable                        0x0
    #define        Gbl_cpuPllCtl_cpuPllSscEn_Enable                         0x1
    #define       bGbl_cpuPllCtl_cpuPllSscmode                 1
    #define        Gbl_cpuPllCtl_cpuPllSscmode_Centre                       0x0
    #define        Gbl_cpuPllCtl_cpuPllSscmode_Down                         0x1
    #define     RA_Gbl_cpuPllCtl3                              0x0048
    #define       bGbl_cpuPllCtl_cpuPllSscFdiv                 16
    #define       bGbl_cpuPllCtl_cpuPllSscRnge                 11
    #define       bGbl_cpuPllCtl_cpuPllSscResetExt             1
    #define        Gbl_cpuPllCtl_cpuPllSscResetExt_Int                      0x0
    #define        Gbl_cpuPllCtl_cpuPllSscResetExt_Ext                      0x1
    #define       bGbl_cpuPllCtl_cpuPllTestMon                 4
    #define     RA_Gbl_cpuPllCtl4                              0x004C
    #define       bGbl_cpuPllCtl_cpuPllRsvdIn                  4
    #define       bGbl_cpuPllCtl_cpuPllExtRst                  1
    #define     RA_Gbl_avPllCtl                                0x0050
    #define       bGbl_avPllCtl_avPllResetPll_A                1
    #define       bGbl_avPllCtl_avPllPu_A                      1
    #define       bGbl_avPllCtl_avPllIntpi_A                   4
    #define       bGbl_avPllCtl_avPllVddr1p45V_A               2
    #define       bGbl_avPllCtl_avPllVddr0p9V_A                4
    #define       bGbl_avPllCtl_avPllVthVcoCal_A               2
    #define       bGbl_avPllCtl_avPllKvcoExt_A                 3
    #define       bGbl_avPllCtl_avPllKvcoExtEn_A               1
    #define       bGbl_avPllCtl_avPllV2iExt_A                  4
    #define       bGbl_avPllCtl_avPllV2iExtEn_A                1
    #define       bGbl_avPllCtl_avPllSpeed_A                   3
    #define       bGbl_avPllCtl_avPllClkDetEn_A                1
    #define     RA_Gbl_avPllCtl1                               0x0054
    #define       bGbl_avPllCtl_avPllRefDiv_A                  6
    #define       bGbl_avPllCtl_avPllFbDiv_A                   8
    #define       bGbl_avPllCtl_avPllIcp_A                     4
    #define       bGbl_avPllCtl_avPllLoadCap_A                 1
    #define       bGbl_avPllCtl_avPllPllCaliStart_A            1
    #define     RA_Gbl_avPllCtl2                               0x0058
    #define       bGbl_avPllCtl_avPllFreqOffsetC1_A            19
    #define     RA_Gbl_avPllCtl3                               0x005C
    #define       bGbl_avPllCtl_avPllFreqOffsetC2_A            19
    #define     RA_Gbl_avPllCtl4                               0x0060
    #define       bGbl_avPllCtl_avPllFreqOffsetC3_A            19
    #define     RA_Gbl_avPllCtl5                               0x0064
    #define       bGbl_avPllCtl_avPllFreqOffsetC4_A            19
    #define     RA_Gbl_avPllCtl6                               0x0068
    #define       bGbl_avPllCtl_avPllFreqOffsetC5_A            19
    #define     RA_Gbl_avPllCtl7                               0x006C
    #define       bGbl_avPllCtl_avPllFreqOffsetC6_A            19
    #define     RA_Gbl_avPllCtl8                               0x0070
    #define       bGbl_avPllCtl_avPllFreqOffsetC7_A            19
    #define     RA_Gbl_avPllCtl9                               0x0074
    #define       bGbl_avPllCtl_avPllFreqOffsetC8_A            19
    #define       bGbl_avPllCtl_avPllFreqOffsetReadyC_A        8
    #define       bGbl_avPllCtl_avPllReserveC1_A               2
    #define       bGbl_avPllCtl_avPllReserveC2_A               2
    #define     RA_Gbl_avPllCtl10                              0x0078
    #define       bGbl_avPllCtl_avPllReserveC3_A               2
    #define       bGbl_avPllCtl_avPllReserveC4_A               2
    #define       bGbl_avPllCtl_avPllReserveC5_A               2
    #define       bGbl_avPllCtl_avPllReserveC6_A               2
    #define       bGbl_avPllCtl_avPllReserveC7_A               2
    #define       bGbl_avPllCtl_avPllReserveC8_A               2
    #define       bGbl_avPllCtl_avPllEnLpC_A                   8
    #define       bGbl_avPllCtl_avPllPuC_A                     7
    #define     RA_Gbl_avPllCtl11                              0x007C
    #define       bGbl_avPllCtl_avPllResetC_A                  7
    #define       bGbl_avPllCtl_avPllDivHdmiC1_A               3
    #define       bGbl_avPllCtl_avPllDivHdmiC2_A               3
    #define       bGbl_avPllCtl_avPllDivHdmiC3_A               3
    #define       bGbl_avPllCtl_avPllDivHdmiC4_A               3
    #define       bGbl_avPllCtl_avPllDivHdmiC5_A               3
    #define       bGbl_avPllCtl_avPllDivHdmiC6_A               3
    #define       bGbl_avPllCtl_avPllDivHdmiC7_A               3
    #define       bGbl_avPllCtl_avPllDivAv1C1_A                3
    #define     RA_Gbl_avPllCtl12                              0x0080
    #define       bGbl_avPllCtl_avPllDivAv1C2_A                3
    #define       bGbl_avPllCtl_avPllDivAv1C3_A                3
    #define       bGbl_avPllCtl_avPllDivAv1C4_A                3
    #define       bGbl_avPllCtl_avPllDivAv1C5_A                3
    #define       bGbl_avPllCtl_avPllDivAv1C6_A                3
    #define       bGbl_avPllCtl_avPllDivAv1C7_A                3
    #define       bGbl_avPllCtl_avPllDivAv2C1_A                7
    #define       bGbl_avPllCtl_avPllDivAv2C2_A                7
    #define     RA_Gbl_avPllCtl13                              0x0084
    #define       bGbl_avPllCtl_avPllDivAv2C3_A                7
    #define       bGbl_avPllCtl_avPllDivAv2C4_A                7
    #define       bGbl_avPllCtl_avPllDivAv2C5_A                7
    #define       bGbl_avPllCtl_avPllDivAv2C6_A                7
    #define     RA_Gbl_avPllCtl14                              0x0088
    #define       bGbl_avPllCtl_avPllDivAv2C7_A                7
    #define       bGbl_avPllCtl_avPllDivAv3C1_A                4
    #define       bGbl_avPllCtl_avPllDivAv3C2_A                4
    #define       bGbl_avPllCtl_avPllDivAv3C3_A                4
    #define       bGbl_avPllCtl_avPllDivAv3C4_A                4
    #define       bGbl_avPllCtl_avPllDivAv3C5_A                4
    #define       bGbl_avPllCtl_avPllDivAv3C6_A                4
    #define     RA_Gbl_avPllCtl15                              0x008C
    #define       bGbl_avPllCtl_avPllDivAv3C7_A                4
    #define       bGbl_avPllCtl_avPllPSync1C1_A                17
    #define     RA_Gbl_avPllCtl16                              0x0090
    #define       bGbl_avPllCtl_avPllPSync1C2_A                17
    #define     RA_Gbl_avPllCtl17                              0x0094
    #define       bGbl_avPllCtl_avPllPSync1C3_A                17
    #define     RA_Gbl_avPllCtl18                              0x0098
    #define       bGbl_avPllCtl_avPllPSync1C4_A                17
    #define     RA_Gbl_avPllCtl19                              0x009C
    #define       bGbl_avPllCtl_avPllPSync1C5_A                17
    #define     RA_Gbl_avPllCtl20                              0x00A0
    #define       bGbl_avPllCtl_avPllPSync1C6_A                17
    #define     RA_Gbl_avPllCtl21                              0x00A4
    #define       bGbl_avPllCtl_avPllPSync1C7_A                17
    #define     RA_Gbl_avPllCtl22                              0x00A8
    #define       bGbl_avPllCtl_avPllPSync1C8_A                17
    #define     RA_Gbl_avPllCtl23                              0x00AC
    #define       bGbl_avPllCtl_avPllPSync2C1_A                17
    #define     RA_Gbl_avPllCtl24                              0x00B0
    #define       bGbl_avPllCtl_avPllPSync2C2_A                17
    #define     RA_Gbl_avPllCtl25                              0x00B4
    #define       bGbl_avPllCtl_avPllPSync2C3_A                17
    #define     RA_Gbl_avPllCtl26                              0x00B8
    #define       bGbl_avPllCtl_avPllPSync2C4_A                17
    #define     RA_Gbl_avPllCtl27                              0x00BC
    #define       bGbl_avPllCtl_avPllPSync2C5_A                17
    #define     RA_Gbl_avPllCtl28                              0x00C0
    #define       bGbl_avPllCtl_avPllPSync2C6_A                17
    #define     RA_Gbl_avPllCtl29                              0x00C4
    #define       bGbl_avPllCtl_avPllPSync2C7_A                17
    #define     RA_Gbl_avPllCtl30                              0x00C8
    #define       bGbl_avPllCtl_avPllPSync2C8_A                17
    #define       bGbl_avPllCtl_avPllEnDpllC_A                 8
    #define       bGbl_avPllCtl_avPllMasterSlaveB_A            1
    #define       bGbl_avPllCtl_avPllTestAna_A                 6
    #define     RA_Gbl_avPllCtl31                              0x00CC
    #define       bGbl_avPllCtl_avPllReservePll_A              4
    #define       bGbl_avPllCtl_avPllResetPll_B                1
    #define       bGbl_avPllCtl_avPllPu_B                      1
    #define       bGbl_avPllCtl_avPllIntpi_B                   4
    #define       bGbl_avPllCtl_avPllVddr1p45V_B               2
    #define       bGbl_avPllCtl_avPllVddr0p9V_B                4
    #define       bGbl_avPllCtl_avPllVthVcoCal_B               2
    #define       bGbl_avPllCtl_avPllKvcoExt_B                 3
    #define       bGbl_avPllCtl_avPllKvcoExtEn_B               1
    #define       bGbl_avPllCtl_avPllV2iExt_B                  4
    #define       bGbl_avPllCtl_avPllV2iExtEn_B                1
    #define       bGbl_avPllCtl_avPllSpeed_B                   3
    #define       bGbl_avPllCtl_avPllClkDetEn_B                1
    #define     RA_Gbl_avPllCtl32                              0x00D0
    #define       bGbl_avPllCtl_avPllRefDiv_B                  6
    #define       bGbl_avPllCtl_avPllFbDiv_B                   8
    #define       bGbl_avPllCtl_avPllIcp_B                     4
    #define       bGbl_avPllCtl_avPllLoadCap_B                 1
    #define       bGbl_avPllCtl_avPllPllCaliStart_B            1
    #define     RA_Gbl_avPllCtl33                              0x00D4
    #define       bGbl_avPllCtl_avPllFreqOffsetC1_B            19
    #define     RA_Gbl_avPllCtl34                              0x00D8
    #define       bGbl_avPllCtl_avPllFreqOffsetC2_B            19
    #define     RA_Gbl_avPllCtl35                              0x00DC
    #define       bGbl_avPllCtl_avPllFreqOffsetC3_B            19
    #define     RA_Gbl_avPllCtl36                              0x00E0
    #define       bGbl_avPllCtl_avPllFreqOffsetC4_B            19
    #define     RA_Gbl_avPllCtl37                              0x00E4
    #define       bGbl_avPllCtl_avPllFreqOffsetC5_B            19
    #define     RA_Gbl_avPllCtl38                              0x00E8
    #define       bGbl_avPllCtl_avPllFreqOffsetC6_B            19
    #define     RA_Gbl_avPllCtl39                              0x00EC
    #define       bGbl_avPllCtl_avPllFreqOffsetC7_B            19
    #define     RA_Gbl_avPllCtl40                              0x00F0
    #define       bGbl_avPllCtl_avPllFreqOffsetC8_B            19
    #define       bGbl_avPllCtl_avPllFreqOffsetReadyC_B        8
    #define       bGbl_avPllCtl_avPllReserveC1_B               2
    #define       bGbl_avPllCtl_avPllReserveC2_B               2
    #define     RA_Gbl_avPllCtl41                              0x00F4
    #define       bGbl_avPllCtl_avPllReserveC3_B               2
    #define       bGbl_avPllCtl_avPllReserveC4_B               2
    #define       bGbl_avPllCtl_avPllReserveC5_B               2
    #define       bGbl_avPllCtl_avPllReserveC6_B               2
    #define       bGbl_avPllCtl_avPllReserveC7_B               2
    #define       bGbl_avPllCtl_avPllReserveC8_B               2
    #define       bGbl_avPllCtl_avPllEnLpC_B                   8
    #define       bGbl_avPllCtl_avPllPuC_B                     7
    #define     RA_Gbl_avPllCtl42                              0x00F8
    #define       bGbl_avPllCtl_avPllResetC_B                  7
    #define       bGbl_avPllCtl_avPllDivHdmiC1_B               3
    #define       bGbl_avPllCtl_avPllDivHdmiC2_B               3
    #define       bGbl_avPllCtl_avPllDivHdmiC3_B               3
    #define       bGbl_avPllCtl_avPllDivHdmiC4_B               3
    #define       bGbl_avPllCtl_avPllDivHdmiC5_B               3
    #define       bGbl_avPllCtl_avPllDivHdmiC6_B               3
    #define       bGbl_avPllCtl_avPllDivHdmiC7_B               3
    #define       bGbl_avPllCtl_avPllDivAv1C1_B                3
    #define     RA_Gbl_avPllCtl43                              0x00FC
    #define       bGbl_avPllCtl_avPllDivAv1C2_B                3
    #define       bGbl_avPllCtl_avPllDivAv1C3_B                3
    #define       bGbl_avPllCtl_avPllDivAv1C4_B                3
    #define       bGbl_avPllCtl_avPllDivAv1C5_B                3
    #define       bGbl_avPllCtl_avPllDivAv1C6_B                3
    #define       bGbl_avPllCtl_avPllDivAv1C7_B                3
    #define       bGbl_avPllCtl_avPllDivAv2C1_B                7
    #define       bGbl_avPllCtl_avPllDivAv2C2_B                7
    #define     RA_Gbl_avPllCtl44                              0x0100
    #define       bGbl_avPllCtl_avPllDivAv2C3_B                7
    #define       bGbl_avPllCtl_avPllDivAv2C4_B                7
    #define       bGbl_avPllCtl_avPllDivAv2C5_B                7
    #define       bGbl_avPllCtl_avPllDivAv2C6_B                7
    #define     RA_Gbl_avPllCtl45                              0x0104
    #define       bGbl_avPllCtl_avPllDivAv2C7_B                7
    #define       bGbl_avPllCtl_avPllDivAv3C1_B                4
    #define       bGbl_avPllCtl_avPllDivAv3C2_B                4
    #define       bGbl_avPllCtl_avPllDivAv3C3_B                4
    #define       bGbl_avPllCtl_avPllDivAv3C4_B                4
    #define       bGbl_avPllCtl_avPllDivAv3C5_B                4
    #define       bGbl_avPllCtl_avPllDivAv3C6_B                4
    #define     RA_Gbl_avPllCtl46                              0x0108
    #define       bGbl_avPllCtl_avPllDivAv3C7_B                4
    #define       bGbl_avPllCtl_avPllPSync1C1_B                17
    #define     RA_Gbl_avPllCtl47                              0x010C
    #define       bGbl_avPllCtl_avPllPSync1C2_B                17
    #define     RA_Gbl_avPllCtl48                              0x0110
    #define       bGbl_avPllCtl_avPllPSync1C3_B                17
    #define     RA_Gbl_avPllCtl49                              0x0114
    #define       bGbl_avPllCtl_avPllPSync1C4_B                17
    #define     RA_Gbl_avPllCtl50                              0x0118
    #define       bGbl_avPllCtl_avPllPSync1C5_B                17
    #define     RA_Gbl_avPllCtl51                              0x011C
    #define       bGbl_avPllCtl_avPllPSync1C6_B                17
    #define     RA_Gbl_avPllCtl52                              0x0120
    #define       bGbl_avPllCtl_avPllPSync1C7_B                17
    #define     RA_Gbl_avPllCtl53                              0x0124
    #define       bGbl_avPllCtl_avPllPSync1C8_B                17
    #define     RA_Gbl_avPllCtl54                              0x0128
    #define       bGbl_avPllCtl_avPllPSync2C1_B                17
    #define     RA_Gbl_avPllCtl55                              0x012C
    #define       bGbl_avPllCtl_avPllPSync2C2_B                17
    #define     RA_Gbl_avPllCtl56                              0x0130
    #define       bGbl_avPllCtl_avPllPSync2C3_B                17
    #define     RA_Gbl_avPllCtl57                              0x0134
    #define       bGbl_avPllCtl_avPllPSync2C4_B                17
    #define     RA_Gbl_avPllCtl58                              0x0138
    #define       bGbl_avPllCtl_avPllPSync2C5_B                17
    #define     RA_Gbl_avPllCtl59                              0x013C
    #define       bGbl_avPllCtl_avPllPSync2C6_B                17
    #define     RA_Gbl_avPllCtl60                              0x0140
    #define       bGbl_avPllCtl_avPllPSync2C7_B                17
    #define     RA_Gbl_avPllCtl61                              0x0144
    #define       bGbl_avPllCtl_avPllPSync2C8_B                17
    #define       bGbl_avPllCtl_avPllEnDpllC_B                 8
    #define       bGbl_avPllCtl_avPllMasterSlaveB_B            1
    #define       bGbl_avPllCtl_avPllTestAna_B                 6
    #define     RA_Gbl_avPllCtl62                              0x0148
    #define       bGbl_avPllCtl_avPllReservePll_B              4
    #define     RA_Gbl_pllStatus                               0x014C
    #define       bGbl_pllStatus_sysPllLock                    1
    #define       bGbl_pllStatus_memPllLock                    1
    #define       bGbl_pllStatus_cpu1PllLock                   1
    #define       bGbl_pllStatus_avPllALock                    1
    #define       bGbl_pllStatus_avPllAKvcoOut                 3
    #define       bGbl_pllStatus_avPllACaliDone                1
    #define       bGbl_pllStatus_avPllBLock                    1
    #define       bGbl_pllStatus_avPllBKvcoOut                 3
    #define       bGbl_pllStatus_avPllBCaliDone                1
    #define       bGbl_pllStatus_cpuPllResOut                  4
    #define       bGbl_pllStatus_memPllResOut                  4
    #define       bGbl_pllStatus_sysPllResOut                  4
    #define     RA_Gbl_clkEnable                               0x0150
    #define       bGbl_clkEnable_sysClkEn                      1
    #define        Gbl_clkEnable_sysClkEn_enable                            0x1
    #define        Gbl_clkEnable_sysClkEn_disable                           0x0
    #define       bGbl_clkEnable_cfgClkEn                      1
    #define        Gbl_clkEnable_cfgClkEn_enable                            0x1
    #define        Gbl_clkEnable_cfgClkEn_disable                           0x0
    #define       bGbl_clkEnable_pCubeClkEn                    1
    #define        Gbl_clkEnable_pCubeClkEn_enable                          0x1
    #define        Gbl_clkEnable_pCubeClkEn_disable                         0x0
    #define       bGbl_clkEnable_vScopeClkEn                   1
    #define        Gbl_clkEnable_vScopeClkEn_enable                         0x1
    #define        Gbl_clkEnable_vScopeClkEn_disable                        0x0
    #define       bGbl_clkEnable_gfxClkEn                      1
    #define        Gbl_clkEnable_gfxClkEn_enable                            0x1
    #define        Gbl_clkEnable_gfxClkEn_disable                           0x0
    #define       bGbl_clkEnable_zspClkEn                      1
    #define        Gbl_clkEnable_zspClkEn_enable                            0x1
    #define        Gbl_clkEnable_zspClkEn_disable                           0x0
    #define       bGbl_clkEnable_perifClkEn                    1
    #define        Gbl_clkEnable_perifClkEn_enable                          0x1
    #define        Gbl_clkEnable_perifClkEn_disable                         0x0
    #define       bGbl_clkEnable_gethCoreClkEn                 1
    #define        Gbl_clkEnable_gethCoreClkEn_enable                       0x1
    #define        Gbl_clkEnable_gethCoreClkEn_disable                      0x0
    #define       bGbl_clkEnable_geth1CoreClkEn                1
    #define        Gbl_clkEnable_geth1CoreClkEn_enable                      0x1
    #define        Gbl_clkEnable_geth1CoreClkEn_disable                     0x0
    #define       bGbl_clkEnable_sataCoreClkEn                 1
    #define        Gbl_clkEnable_sataCoreClkEn_enable                       0x1
    #define        Gbl_clkEnable_sataCoreClkEn_disable                      0x0
    #define       bGbl_clkEnable_ahbApbCoreClkEn               1
    #define        Gbl_clkEnable_ahbApbCoreClkEn_enable                     0x1
    #define        Gbl_clkEnable_ahbApbCoreClkEn_disable                    0x0
    #define       bGbl_clkEnable_usb0CoreClkEn                 1
    #define        Gbl_clkEnable_usb0CoreClkEn_enable                       0x1
    #define        Gbl_clkEnable_usb0CoreClkEn_disable                      0x0
    #define       bGbl_clkEnable_usb1CoreClkEn                 1
    #define        Gbl_clkEnable_usb1CoreClkEn_enable                       0x1
    #define        Gbl_clkEnable_usb1CoreClkEn_disable                      0x0
    #define       bGbl_clkEnable_pBridgeCoreClkEn              1
    #define        Gbl_clkEnable_pBridgeCoreClkEn_enable                    0x1
    #define        Gbl_clkEnable_pBridgeCoreClkEn_disable                   0x0
    #define       bGbl_clkEnable_sdioCoreClkEn                 1
    #define        Gbl_clkEnable_sdioCoreClkEn_enable                       0x1
    #define        Gbl_clkEnable_sdioCoreClkEn_disable                      0x0
    #define       bGbl_clkEnable_sdio1CoreClkEn                1
    #define        Gbl_clkEnable_sdio1CoreClkEn_enable                      0x1
    #define        Gbl_clkEnable_sdio1CoreClkEn_disable                     0x0
    #define       bGbl_clkEnable_nfcCoreClkEn                  1
    #define        Gbl_clkEnable_nfcCoreClkEn_enable                        0x1
    #define        Gbl_clkEnable_nfcCoreClkEn_disable                       0x0
    #define       bGbl_clkEnable_nfcEccClkEn                   1
    #define        Gbl_clkEnable_nfcEccClkEn_enable                         0x1
    #define        Gbl_clkEnable_nfcEccClkEn_disable                        0x0
    #define       bGbl_clkEnable_smemcCoreClkEn                1
    #define        Gbl_clkEnable_smemcCoreClkEn_enable                      0x1
    #define        Gbl_clkEnable_smemcCoreClkEn_disable                     0x0
    #define       bGbl_clkEnable_appClkEn                      1
    #define        Gbl_clkEnable_appClkEn_enable                            0x1
    #define        Gbl_clkEnable_appClkEn_disable                           0x0
    #define       bGbl_clkEnable_vppSysClkEn                   1
    #define        Gbl_clkEnable_vppSysClkEn_enable                         0x1
    #define        Gbl_clkEnable_vppSysClkEn_disable                        0x0
    #define       bGbl_clkEnable_audio0ClkEn                   1
    #define        Gbl_clkEnable_audio0ClkEn_enable                         0x1
    #define        Gbl_clkEnable_audio0ClkEn_disable                        0x0
    #define       bGbl_clkEnable_audio1ClkEn                   1
    #define        Gbl_clkEnable_audio1ClkEn_enable                         0x1
    #define        Gbl_clkEnable_audio1ClkEn_disable                        0x0
    #define       bGbl_clkEnable_audio2ClkEn                   1
    #define        Gbl_clkEnable_audio2ClkEn_enable                         0x1
    #define        Gbl_clkEnable_audio2ClkEn_disable                        0x0
    #define       bGbl_clkEnable_audio3ClkEn                   1
    #define        Gbl_clkEnable_audio3ClkEn_enable                         0x1
    #define        Gbl_clkEnable_audio3ClkEn_disable                        0x0
    #define       bGbl_clkEnable_audioHdClkEn                  1
    #define        Gbl_clkEnable_audioHdClkEn_enable                        0x1
    #define        Gbl_clkEnable_audioHdClkEn_disable                       0x0
    #define       bGbl_clkEnable_video0ClkEn                   1
    #define        Gbl_clkEnable_video0ClkEn_enable                         0x1
    #define        Gbl_clkEnable_video0ClkEn_disable                        0x0
    #define       bGbl_clkEnable_video1ClkEn                   1
    #define        Gbl_clkEnable_video1ClkEn_enable                         0x1
    #define        Gbl_clkEnable_video1ClkEn_disable                        0x0
    #define       bGbl_clkEnable_video2ClkEn                   1
    #define        Gbl_clkEnable_video2ClkEn_enable                         0x1
    #define        Gbl_clkEnable_video2ClkEn_disable                        0x0
    #define       bGbl_clkEnable_PEX_mx_refclk_off             1
    #define        Gbl_clkEnable_PEX_mx_refclk_off_ON                       0x0
    #define        Gbl_clkEnable_PEX_mx_refclk_off_OFF                      0x1
    #define     RA_Gbl_clkSelect                               0x0154
    #define       bGbl_clkSelect_sysClkPllSel                  3
    #define        Gbl_clkSelect_sysClkPllSel_AVPllB4                       0x0
    #define        Gbl_clkSelect_sysClkPllSel_AVPllB5                       0x1
    #define        Gbl_clkSelect_sysClkPllSel_AVPllB6                       0x2
    #define        Gbl_clkSelect_sysClkPllSel_AVPllB7                       0x3
    #define        Gbl_clkSelect_sysClkPllSel_SYSPll                        0x4
    #define       bGbl_clkSelect_sysClkSel                     3
    #define        Gbl_clkSelect_sysClkSel_d2                               0x1
    #define        Gbl_clkSelect_sysClkSel_d4                               0x2
    #define        Gbl_clkSelect_sysClkSel_d6                               0x3
    #define        Gbl_clkSelect_sysClkSel_d8                               0x4
    #define        Gbl_clkSelect_sysClkSel_d12                              0x5
    #define       bGbl_clkSelect_cpu0ClkPllSel                 3
    #define        Gbl_clkSelect_cpu0ClkPllSel_AVPllB4                      0x0
    #define        Gbl_clkSelect_cpu0ClkPllSel_AVPllB5                      0x1
    #define        Gbl_clkSelect_cpu0ClkPllSel_AVPllB6                      0x2
    #define        Gbl_clkSelect_cpu0ClkPllSel_AVPllB7                      0x3
    #define        Gbl_clkSelect_cpu0ClkPllSel_MEMPLL                       0x4
    #define       bGbl_clkSelect_cpu0ClkSel                    3
    #define        Gbl_clkSelect_cpu0ClkSel_d2                              0x1
    #define        Gbl_clkSelect_cpu0ClkSel_d4                              0x2
    #define        Gbl_clkSelect_cpu0ClkSel_d6                              0x3
    #define        Gbl_clkSelect_cpu0ClkSel_d8                              0x4
    #define        Gbl_clkSelect_cpu0ClkSel_d12                             0x5
    #define       bGbl_clkSelect_cpu1ClkPllSel                 2
    #define        Gbl_clkSelect_cpu1ClkPllSel_AVPllA5                      0x0
    #define        Gbl_clkSelect_cpu1ClkPllSel_AVPllA6                      0x1
    #define        Gbl_clkSelect_cpu1ClkPllSel_AVPllB6                      0x2
    #define        Gbl_clkSelect_cpu1ClkPllSel_AVPllB7                      0x3
    #define       bGbl_clkSelect_cpu1ClkSel                    3
    #define        Gbl_clkSelect_cpu1ClkSel_d2                              0x1
    #define        Gbl_clkSelect_cpu1ClkSel_d4                              0x2
    #define        Gbl_clkSelect_cpu1ClkSel_d6                              0x3
    #define        Gbl_clkSelect_cpu1ClkSel_d8                              0x4
    #define        Gbl_clkSelect_cpu1ClkSel_d12                             0x5
    #define       bGbl_clkSelect_cfgClkPllSel                  3
    #define        Gbl_clkSelect_cfgClkPllSel_AVPllB4                       0x0
    #define        Gbl_clkSelect_cfgClkPllSel_AVPllB5                       0x1
    #define        Gbl_clkSelect_cfgClkPllSel_AVPllB6                       0x2
    #define        Gbl_clkSelect_cfgClkPllSel_AVPllB7                       0x3
    #define        Gbl_clkSelect_cfgClkPllSel_SYSPll                        0x4
    #define       bGbl_clkSelect_cfgClkSel                     3
    #define        Gbl_clkSelect_cfgClkSel_d2                               0x1
    #define        Gbl_clkSelect_cfgClkSel_d4                               0x2
    #define        Gbl_clkSelect_cfgClkSel_d6                               0x3
    #define        Gbl_clkSelect_cfgClkSel_d8                               0x4
    #define        Gbl_clkSelect_cfgClkSel_d12                              0x5
    #define       bGbl_clkSelect_gfxClkPllSel                  3
    #define        Gbl_clkSelect_gfxClkPllSel_AVPllB4                       0x0
    #define        Gbl_clkSelect_gfxClkPllSel_AVPllB5                       0x1
    #define        Gbl_clkSelect_gfxClkPllSel_AVPllB6                       0x2
    #define        Gbl_clkSelect_gfxClkPllSel_AVPllB7                       0x3
    #define        Gbl_clkSelect_gfxClkPllSel_SYSPll                        0x4
    #define     RA_Gbl_clkSelect1                              0x0158
    #define       bGbl_clkSelect_gfxClkSel                     3
    #define        Gbl_clkSelect_gfxClkSel_d2                               0x1
    #define        Gbl_clkSelect_gfxClkSel_d4                               0x2
    #define        Gbl_clkSelect_gfxClkSel_d6                               0x3
    #define        Gbl_clkSelect_gfxClkSel_d8                               0x4
    #define        Gbl_clkSelect_gfxClkSel_d12                              0x5
    #define       bGbl_clkSelect_zspClkPllSel                  3
    #define        Gbl_clkSelect_zspClkPllSel_AVPllB4                       0x0
    #define        Gbl_clkSelect_zspClkPllSel_AVPllB5                       0x1
    #define        Gbl_clkSelect_zspClkPllSel_AVPllB6                       0x2
    #define        Gbl_clkSelect_zspClkPllSel_AVPllB7                       0x3
    #define        Gbl_clkSelect_zspClkPllSel_SYSPll                        0x4
    #define       bGbl_clkSelect_zspClkSel                     3
    #define        Gbl_clkSelect_zspClkSel_d2                               0x1
    #define        Gbl_clkSelect_zspClkSel_d4                               0x2
    #define        Gbl_clkSelect_zspClkSel_d6                               0x3
    #define        Gbl_clkSelect_zspClkSel_d8                               0x4
    #define        Gbl_clkSelect_zspClkSel_d12                              0x5
    #define       bGbl_clkSelect_perifClkPllSel                3
    #define        Gbl_clkSelect_perifClkPllSel_AVPllB4                     0x0
    #define        Gbl_clkSelect_perifClkPllSel_AVPllB5                     0x1
    #define        Gbl_clkSelect_perifClkPllSel_AVPllB6                     0x2
    #define        Gbl_clkSelect_perifClkPllSel_AVPllB7                     0x3
    #define        Gbl_clkSelect_perifClkPllSel_SYSPll                      0x4
    #define       bGbl_clkSelect_perifClkSel                   3
    #define        Gbl_clkSelect_perifClkSel_d2                             0x1
    #define        Gbl_clkSelect_perifClkSel_d4                             0x2
    #define        Gbl_clkSelect_perifClkSel_d6                             0x3
    #define        Gbl_clkSelect_perifClkSel_d8                             0x4
    #define        Gbl_clkSelect_perifClkSel_d12                            0x5
    #define       bGbl_clkSelect_pCubeClkPllSel                3
    #define        Gbl_clkSelect_pCubeClkPllSel_AVPllB4                     0x0
    #define        Gbl_clkSelect_pCubeClkPllSel_AVPllB5                     0x1
    #define        Gbl_clkSelect_pCubeClkPllSel_AVPllB6                     0x2
    #define        Gbl_clkSelect_pCubeClkPllSel_AVPllB7                     0x3
    #define        Gbl_clkSelect_pCubeClkPllSel_SYSPll                      0x4
    #define       bGbl_clkSelect_pCubeClkSel                   3
    #define        Gbl_clkSelect_pCubeClkSel_d2                             0x1
    #define        Gbl_clkSelect_pCubeClkSel_d4                             0x2
    #define        Gbl_clkSelect_pCubeClkSel_d6                             0x3
    #define        Gbl_clkSelect_pCubeClkSel_d8                             0x4
    #define        Gbl_clkSelect_pCubeClkSel_d12                            0x5
    #define       bGbl_clkSelect_vScopeClkPllSel               3
    #define        Gbl_clkSelect_vScopeClkPllSel_AVPllB4                    0x0
    #define        Gbl_clkSelect_vScopeClkPllSel_AVPllB5                    0x1
    #define        Gbl_clkSelect_vScopeClkPllSel_AVPllB6                    0x2
    #define        Gbl_clkSelect_vScopeClkPllSel_AVPllB7                    0x3
    #define        Gbl_clkSelect_vScopeClkPllSel_SYSPll                     0x4
    #define       bGbl_clkSelect_vScopeClkSel                  3
    #define        Gbl_clkSelect_vScopeClkSel_d2                            0x1
    #define        Gbl_clkSelect_vScopeClkSel_d4                            0x2
    #define        Gbl_clkSelect_vScopeClkSel_d6                            0x3
    #define        Gbl_clkSelect_vScopeClkSel_d8                            0x4
    #define        Gbl_clkSelect_vScopeClkSel_d12                           0x5
    #define       bGbl_clkSelect_nfcEccClkPllSel               3
    #define        Gbl_clkSelect_nfcEccClkPllSel_AVPllB4                    0x0
    #define        Gbl_clkSelect_nfcEccClkPllSel_AVPllB5                    0x1
    #define        Gbl_clkSelect_nfcEccClkPllSel_AVPllB6                    0x2
    #define        Gbl_clkSelect_nfcEccClkPllSel_AVPllB7                    0x3
    #define        Gbl_clkSelect_nfcEccClkPllSel_SYSPll                     0x4
    #define     RA_Gbl_clkSelect2                              0x015C
    #define       bGbl_clkSelect_nfcEccClkSel                  3
    #define        Gbl_clkSelect_nfcEccClkSel_d2                            0x1
    #define        Gbl_clkSelect_nfcEccClkSel_d4                            0x2
    #define        Gbl_clkSelect_nfcEccClkSel_d6                            0x3
    #define        Gbl_clkSelect_nfcEccClkSel_d8                            0x4
    #define        Gbl_clkSelect_nfcEccClkSel_d12                           0x5
    #define       bGbl_clkSelect_vppSysClkPllSel               3
    #define        Gbl_clkSelect_vppSysClkPllSel_AVPllB4                    0x0
    #define        Gbl_clkSelect_vppSysClkPllSel_AVPllB5                    0x1
    #define        Gbl_clkSelect_vppSysClkPllSel_AVPllB6                    0x2
    #define        Gbl_clkSelect_vppSysClkPllSel_AVPllB7                    0x3
    #define        Gbl_clkSelect_vppSysClkPllSel_SYSPll                     0x4
    #define       bGbl_clkSelect_vppSysClkSel                  3
    #define        Gbl_clkSelect_vppSysClkSel_d2                            0x1
    #define        Gbl_clkSelect_vppSysClkSel_d4                            0x2
    #define        Gbl_clkSelect_vppSysClkSel_d6                            0x3
    #define        Gbl_clkSelect_vppSysClkSel_d8                            0x4
    #define        Gbl_clkSelect_vppSysClkSel_d12                           0x5
    #define       bGbl_clkSelect_appClkPllSel                  3
    #define        Gbl_clkSelect_appClkPllSel_AVPllB4                       0x0
    #define        Gbl_clkSelect_appClkPllSel_AVPllB5                       0x1
    #define        Gbl_clkSelect_appClkPllSel_AVPllB6                       0x2
    #define        Gbl_clkSelect_appClkPllSel_AVPllB7                       0x3
    #define        Gbl_clkSelect_appClkPllSel_SYSPll                        0x4
    #define       bGbl_clkSelect_appClkSel                     3
    #define        Gbl_clkSelect_appClkSel_d2                               0x1
    #define        Gbl_clkSelect_appClkSel_d4                               0x2
    #define        Gbl_clkSelect_appClkSel_d6                               0x3
    #define        Gbl_clkSelect_appClkSel_d8                               0x4
    #define        Gbl_clkSelect_appClkSel_d12                              0x5
    #define       bGbl_clkSelect_audioFastExtClkSel            1
    #define       bGbl_clkSelect_audioFastClkSel               1
    #define        Gbl_clkSelect_audioFastClkSel_pllClk                     0x0
    #define        Gbl_clkSelect_audioFastClkSel_extClk                     0x1
    #define       bGbl_clkSelect_audio0ClkSel                  3
    #define        Gbl_clkSelect_audio0ClkSel_d2                            0x1
    #define        Gbl_clkSelect_audio0ClkSel_d4                            0x2
    #define        Gbl_clkSelect_audio0ClkSel_d6                            0x3
    #define        Gbl_clkSelect_audio0ClkSel_d8                            0x4
    #define        Gbl_clkSelect_audio0ClkSel_d12                           0x5
    #define       bGbl_clkSelect_audio2ClkSel                  3
    #define        Gbl_clkSelect_audio2ClkSel_d2                            0x1
    #define        Gbl_clkSelect_audio2ClkSel_d4                            0x2
    #define        Gbl_clkSelect_audio2ClkSel_d6                            0x3
    #define        Gbl_clkSelect_audio2ClkSel_d8                            0x4
    #define        Gbl_clkSelect_audio2ClkSel_d12                           0x5
    #define       bGbl_clkSelect_audio3ClkSel                  3
    #define        Gbl_clkSelect_audio3ClkSel_d2                            0x1
    #define        Gbl_clkSelect_audio3ClkSel_d4                            0x2
    #define        Gbl_clkSelect_audio3ClkSel_d6                            0x3
    #define        Gbl_clkSelect_audio3ClkSel_d8                            0x4
    #define        Gbl_clkSelect_audio3ClkSel_d12                           0x5
    #define       bGbl_clkSelect_audioHdExtClkSel              1
    #define       bGbl_clkSelect_audioHdClkSel                 1
    #define        Gbl_clkSelect_audioHdClkSel_pllClk                       0x0
    #define        Gbl_clkSelect_audioHdClkSel_extClk                       0x1
    #define       bGbl_clkSelect_audio1ExtClkSel               1
    #define       bGbl_clkSelect_audio1ClkPllSel               1
    #define        Gbl_clkSelect_audio1ClkPllSel_AVPllB3                    0x0
    #define        Gbl_clkSelect_audio1ClkPllSel_AVPllA3                    0x1
    #define       bGbl_clkSelect_audio1SrcClkSel               1
    #define        Gbl_clkSelect_audio1SrcClkSel_pllClk                     0x0
    #define        Gbl_clkSelect_audio1SrcClkSel_extClk                     0x1
    #define     RA_Gbl_clkSelect3                              0x0160
    #define       bGbl_clkSelect_audio1ClkSel                  3
    #define        Gbl_clkSelect_audio1ClkSel_d2                            0x1
    #define        Gbl_clkSelect_audio1ClkSel_d4                            0x2
    #define        Gbl_clkSelect_audio1ClkSel_d6                            0x3
    #define        Gbl_clkSelect_audio1ClkSel_d8                            0x4
    #define        Gbl_clkSelect_audio1ClkSel_d12                           0x5
    #define       bGbl_clkSelect_video0ExtClkSel               1
    #define       bGbl_clkSelect_video0ClkSel                  1
    #define        Gbl_clkSelect_video0ClkSel_pllClk                        0x0
    #define        Gbl_clkSelect_video0ClkSel_extClk                        0x1
    #define       bGbl_clkSelect_video1ExtClkSel               1
    #define       bGbl_clkSelect_video1ClkSel                  1
    #define        Gbl_clkSelect_video1ClkSel_pllClk                        0x0
    #define        Gbl_clkSelect_video1ClkSel_extClk                        0x1
    #define       bGbl_clkSelect_video1ClkPllSel               1
    #define        Gbl_clkSelect_video1ClkPllSel_AVPllA2                    0x0
    #define        Gbl_clkSelect_video1ClkPllSel_AVPllB2                    0x1
    #define       bGbl_clkSelect_video2ExtClkSel               1
    #define       bGbl_clkSelect_video2ClkSel                  1
    #define        Gbl_clkSelect_video2ClkSel_pllClk                        0x0
    #define        Gbl_clkSelect_video2ClkSel_extClk                        0x1
    #define       bGbl_clkSelect_video2ClkPllSel               1
    #define        Gbl_clkSelect_video2ClkPllSel_AVPllB1                    0x0
    #define        Gbl_clkSelect_video2ClkPllSel_AVPllA5                    0x1
    #define     RA_Gbl_ClkSwitch                               0x0164
    #define       bGbl_ClkSwitch_sysPLLSWBypass                1
    #define        Gbl_ClkSwitch_sysPLLSWBypass_refClk                      0x1
    #define        Gbl_ClkSwitch_sysPLLSWBypass_pllClk                      0x0
    #define       bGbl_ClkSwitch_memPLLSWBypass                1
    #define        Gbl_ClkSwitch_memPLLSWBypass_refClk                      0x1
    #define        Gbl_ClkSwitch_memPLLSWBypass_pllClk                      0x0
    #define       bGbl_ClkSwitch_cpu1PLLSWBypass               1
    #define        Gbl_ClkSwitch_cpu1PLLSWBypass_refClk                     0x1
    #define        Gbl_ClkSwitch_cpu1PLLSWBypass_pllClk                     0x0
    #define       bGbl_ClkSwitch_sysClkPllSwitch               1
    #define        Gbl_ClkSwitch_sysClkPllSwitch_SYSPLL                     0x0
    #define        Gbl_ClkSwitch_sysClkPllSwitch_AVPLL                      0x1
    #define       bGbl_ClkSwitch_sysClkSwitch                  1
    #define        Gbl_ClkSwitch_sysClkSwitch_SrcClk                        0x0
    #define        Gbl_ClkSwitch_sysClkSwitch_DivClk                        0x1
    #define       bGbl_ClkSwitch_sysClkD3Switch                1
    #define        Gbl_ClkSwitch_sysClkD3Switch_NonDiv3Clk                  0x0
    #define        Gbl_ClkSwitch_sysClkD3Switch_Div3Clk                     0x1
    #define       bGbl_ClkSwitch_cpu0ClkPllSwitch              1
    #define        Gbl_ClkSwitch_cpu0ClkPllSwitch_CPUPLL                    0x0
    #define        Gbl_ClkSwitch_cpu0ClkPllSwitch_MEMPLL                    0x1
    #define       bGbl_ClkSwitch_cpu0ClkSwitch                 1
    #define        Gbl_ClkSwitch_cpu0ClkSwitch_SrcClk                       0x0
    #define        Gbl_ClkSwitch_cpu0ClkSwitch_DivClk                       0x1
    #define       bGbl_ClkSwitch_cpu0ClkD3Switch               1
    #define        Gbl_ClkSwitch_cpu0ClkD3Switch_NonDiv3Clk                 0x0
    #define        Gbl_ClkSwitch_cpu0ClkD3Switch_Div3Clk                    0x1
    #define       bGbl_ClkSwitch_cpu1ClkPllSwitch              1
    #define        Gbl_ClkSwitch_cpu1ClkPllSwitch_CPU1PLL                   0x0
    #define        Gbl_ClkSwitch_cpu1ClkPllSwitch_AVPLL                     0x1
    #define       bGbl_ClkSwitch_cpu1ClkSwitch                 1
    #define        Gbl_ClkSwitch_cpu1ClkSwitch_SrcClk                       0x0
    #define        Gbl_ClkSwitch_cpu1ClkSwitch_DivClk                       0x1
    #define       bGbl_ClkSwitch_cpu1ClkD3Switch               1
    #define        Gbl_ClkSwitch_cpu1ClkD3Switch_NonDiv3Clk                 0x0
    #define        Gbl_ClkSwitch_cpu1ClkD3Switch_Div3Clk                    0x1
    #define       bGbl_ClkSwitch_cfgClkPllSwitch               1
    #define        Gbl_ClkSwitch_cfgClkPllSwitch_SYSPLL                     0x0
    #define        Gbl_ClkSwitch_cfgClkPllSwitch_AVPLL                      0x1
    #define       bGbl_ClkSwitch_cfgClkSwitch                  1
    #define        Gbl_ClkSwitch_cfgClkSwitch_SrcClk                        0x0
    #define        Gbl_ClkSwitch_cfgClkSwitch_DivClk                        0x1
    #define       bGbl_ClkSwitch_cfgClkD3Switch                1
    #define        Gbl_ClkSwitch_cfgClkD3Switch_NonDiv3Clk                  0x0
    #define        Gbl_ClkSwitch_cfgClkD3Switch_Div3Clk                     0x1
    #define       bGbl_ClkSwitch_gfxClkPllSwitch               1
    #define        Gbl_ClkSwitch_gfxClkPllSwitch_SYSPLL                     0x0
    #define        Gbl_ClkSwitch_gfxClkPllSwitch_AVPLL                      0x1
    #define       bGbl_ClkSwitch_gfxClkSwitch                  1
    #define        Gbl_ClkSwitch_gfxClkSwitch_SrcClk                        0x0
    #define        Gbl_ClkSwitch_gfxClkSwitch_DivClk                        0x1
    #define       bGbl_ClkSwitch_gfxClkD3Switch                1
    #define        Gbl_ClkSwitch_gfxClkD3Switch_NonDiv3Clk                  0x0
    #define        Gbl_ClkSwitch_gfxClkD3Switch_Div3Clk                     0x1
    #define       bGbl_ClkSwitch_zspClkPllSwitch               1
    #define        Gbl_ClkSwitch_zspClkPllSwitch_SYSPLL                     0x0
    #define        Gbl_ClkSwitch_zspClkPllSwitch_AVPLL                      0x1
    #define       bGbl_ClkSwitch_zspClkSwitch                  1
    #define        Gbl_ClkSwitch_zspClkSwitch_SrcClk                        0x0
    #define        Gbl_ClkSwitch_zspClkSwitch_DivClk                        0x1
    #define       bGbl_ClkSwitch_zspClkD3Switch                1
    #define        Gbl_ClkSwitch_zspClkD3Switch_NonDiv3Clk                  0x0
    #define        Gbl_ClkSwitch_zspClkD3Switch_Div3Clk                     0x1
    #define       bGbl_ClkSwitch_perifClkPllSwitch             1
    #define        Gbl_ClkSwitch_perifClkPllSwitch_SYSPLL                   0x0
    #define        Gbl_ClkSwitch_perifClkPllSwitch_AVPLL                    0x1
    #define       bGbl_ClkSwitch_perifClkSwitch                1
    #define        Gbl_ClkSwitch_perifClkSwitch_SrcClk                      0x0
    #define        Gbl_ClkSwitch_perifClkSwitch_DivClk                      0x1
    #define       bGbl_ClkSwitch_perifClkD3Switch              1
    #define        Gbl_ClkSwitch_perifClkD3Switch_NonDiv3Clk                0x0
    #define        Gbl_ClkSwitch_perifClkD3Switch_Div3Clk                   0x1
    #define       bGbl_ClkSwitch_pCubeClkPllSwitch             1
    #define        Gbl_ClkSwitch_pCubeClkPllSwitch_SYSPLL                   0x0
    #define        Gbl_ClkSwitch_pCubeClkPllSwitch_AVPLL                    0x1
    #define       bGbl_ClkSwitch_pCubeClkSwitch                1
    #define        Gbl_ClkSwitch_pCubeClkSwitch_SrcClk                      0x0
    #define        Gbl_ClkSwitch_pCubeClkSwitch_DivClk                      0x1
    #define       bGbl_ClkSwitch_pCubeClkD3Switch              1
    #define        Gbl_ClkSwitch_pCubeClkD3Switch_NonDiv3Clk                0x0
    #define        Gbl_ClkSwitch_pCubeClkD3Switch_Div3Clk                   0x1
    #define       bGbl_ClkSwitch_vScopeClkPllSwitch            1
    #define        Gbl_ClkSwitch_vScopeClkPllSwitch_SYSPLL                  0x0
    #define        Gbl_ClkSwitch_vScopeClkPllSwitch_AVPLL                   0x1
    #define       bGbl_ClkSwitch_vScopeClkSwitch               1
    #define        Gbl_ClkSwitch_vScopeClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_vScopeClkSwitch_DivClk                     0x1
    #define     RA_Gbl_ClkSwitch1                              0x0168
    #define       bGbl_ClkSwitch_vScopeClkD3Switch             1
    #define        Gbl_ClkSwitch_vScopeClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_vScopeClkD3Switch_Div3Clk                  0x1
    #define       bGbl_ClkSwitch_nfcEccClkPllSwitch            1
    #define        Gbl_ClkSwitch_nfcEccClkPllSwitch_SYSPLL                  0x0
    #define        Gbl_ClkSwitch_nfcEccClkPllSwitch_AVPLL                   0x1
    #define       bGbl_ClkSwitch_nfcEccClkSwitch               1
    #define        Gbl_ClkSwitch_nfcEccClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_nfcEccClkSwitch_DivClk                     0x1
    #define       bGbl_ClkSwitch_nfcEccClkD3Switch             1
    #define        Gbl_ClkSwitch_nfcEccClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_nfcEccClkD3Switch_Div3Clk                  0x1
    #define       bGbl_ClkSwitch_vppSysClkPllSwitch            1
    #define        Gbl_ClkSwitch_vppSysClkPllSwitch_SYSPLL                  0x0
    #define        Gbl_ClkSwitch_vppSysClkPllSwitch_AVPLL                   0x1
    #define       bGbl_ClkSwitch_vppSysClkSwitch               1
    #define        Gbl_ClkSwitch_vppSysClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_vppSysClkSwitch_DivClk                     0x1
    #define       bGbl_ClkSwitch_vppSysClkD3Switch             1
    #define        Gbl_ClkSwitch_vppSysClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_vppSysClkD3Switch_Div3Clk                  0x1
    #define       bGbl_ClkSwitch_appClkPllSwitch               1
    #define        Gbl_ClkSwitch_appClkPllSwitch_SYSPLL                     0x0
    #define        Gbl_ClkSwitch_appClkPllSwitch_AVPLL                      0x1
    #define       bGbl_ClkSwitch_appClkSwitch                  1
    #define        Gbl_ClkSwitch_appClkSwitch_SrcClk                        0x0
    #define        Gbl_ClkSwitch_appClkSwitch_DivClk                        0x1
    #define       bGbl_ClkSwitch_appClkD3Switch                1
    #define        Gbl_ClkSwitch_appClkD3Switch_NonDiv3Clk                  0x0
    #define        Gbl_ClkSwitch_appClkD3Switch_Div3Clk                     0x1
    #define       bGbl_ClkSwitch_audio0ClkSwitch               1
    #define        Gbl_ClkSwitch_audio0ClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_audio0ClkSwitch_DivClk                     0x1
    #define       bGbl_ClkSwitch_audio0ClkD3Switch             1
    #define        Gbl_ClkSwitch_audio0ClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_audio0ClkD3Switch_Div3Clk                  0x1
    #define       bGbl_ClkSwitch_audio1ClkSwitch               1
    #define        Gbl_ClkSwitch_audio1ClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_audio1ClkSwitch_DivClk                     0x1
    #define       bGbl_ClkSwitch_audio1ClkD3Switch             1
    #define        Gbl_ClkSwitch_audio1ClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_audio1ClkD3Switch_Div3Clk                  0x1
    #define       bGbl_ClkSwitch_audio2ClkSwitch               1
    #define        Gbl_ClkSwitch_audio2ClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_audio2ClkSwitch_DivClk                     0x1
    #define       bGbl_ClkSwitch_audio2ClkD3Switch             1
    #define        Gbl_ClkSwitch_audio2ClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_audio2ClkD3Switch_Div3Clk                  0x1
    #define       bGbl_ClkSwitch_audio3ClkSwitch               1
    #define        Gbl_ClkSwitch_audio3ClkSwitch_SrcClk                     0x0
    #define        Gbl_ClkSwitch_audio3ClkSwitch_DivClk                     0x1
    #define       bGbl_ClkSwitch_audio3ClkD3Switch             1
    #define        Gbl_ClkSwitch_audio3ClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_ClkSwitch_audio3ClkD3Switch_Div3Clk                  0x1
    #define     RA_Gbl_PadSelect                               0x016C
    #define       bGbl_PadSelect_GBL_PDB                       1
    #define        Gbl_PadSelect_GBL_PDB_NORMAL                             0x1
    #define        Gbl_PadSelect_GBL_PDB_PWRDN                              0x0
    #define       bGbl_PadSelect_NAND_PDB                      1
    #define        Gbl_PadSelect_NAND_PDB_NORMAL                            0x1
    #define        Gbl_PadSelect_NAND_PDB_PWRDN                             0x0
    #define       bGbl_PadSelect_SD0_PDB                       1
    #define        Gbl_PadSelect_SD0_PDB_NORMAL                             0x1
    #define        Gbl_PadSelect_SD0_PDB_PWRDN                              0x0
    #define       bGbl_PadSelect_SD1_PDB                       1
    #define        Gbl_PadSelect_SD1_PDB_NORMAL                             0x1
    #define        Gbl_PadSelect_SD1_PDB_PWRDN                              0x0
    #define       bGbl_PadSelect_SPI_PDB                       1
    #define        Gbl_PadSelect_SPI_PDB_NORMAL                             0x1
    #define        Gbl_PadSelect_SPI_PDB_PWRDN                              0x0
    #define       bGbl_PadSelect_CLK0_V18EN                    1
    #define        Gbl_PadSelect_CLK0_V18EN_V1P8                            0x1
    #define        Gbl_PadSelect_CLK0_V18EN_V3R3                            0x0
    #define       bGbl_PadSelect_DVIO0_V18EN                   1
    #define        Gbl_PadSelect_DVIO0_V18EN_V1P8                           0x1
    #define        Gbl_PadSelect_DVIO0_V18EN_V3R3                           0x0
    #define       bGbl_PadSelect_GBL_V18EN                     1
    #define        Gbl_PadSelect_GBL_V18EN_V1P8                             0x1
    #define        Gbl_PadSelect_GBL_V18EN_V3R3                             0x0
    #define       bGbl_PadSelect_SPI0_V18EN                    1
    #define        Gbl_PadSelect_SPI0_V18EN_V1P8                            0x1
    #define        Gbl_PadSelect_SPI0_V18EN_V3R3                            0x0
    #define       bGbl_PadSelect_SD0_V18EN                     1
    #define        Gbl_PadSelect_SD0_V18EN_V1P8                             0x1
    #define        Gbl_PadSelect_SD0_V18EN_V3R3                             0x0
    #define       bGbl_PadSelect_SD10_V18EN                    1
    #define        Gbl_PadSelect_SD10_V18EN_V1P8                            0x1
    #define        Gbl_PadSelect_SD10_V18EN_V3R3                            0x0
    #define       bGbl_PadSelect_CLK0_V25EN                    1
    #define        Gbl_PadSelect_CLK0_V25EN_Enable                          0x1
    #define        Gbl_PadSelect_CLK0_V25EN_Disable                         0x0
    #define       bGbl_PadSelect_DVIO0_V25EN                   1
    #define        Gbl_PadSelect_DVIO0_V25EN_Enable                         0x1
    #define        Gbl_PadSelect_DVIO0_V25EN_Disable                        0x0
    #define       bGbl_PadSelect_TS0_V25EN                     1
    #define        Gbl_PadSelect_TS0_V25EN_Enable                           0x1
    #define        Gbl_PadSelect_TS0_V25EN_Disable                          0x0
    #define       bGbl_PadSelect_SPI0_V25EN                    1
    #define        Gbl_PadSelect_SPI0_V25EN_Enable                          0x1
    #define        Gbl_PadSelect_SPI0_V25EN_Disable                         0x0
    #define       bGbl_PadSelect_U6_V25EN                      1
    #define        Gbl_PadSelect_U6_V25EN_Enable                            0x1
    #define        Gbl_PadSelect_U6_V25EN_Disable                           0x0
    #define       bGbl_PadSelect_U7_V25EN                      1
    #define        Gbl_PadSelect_U7_V25EN_Enable                            0x1
    #define        Gbl_PadSelect_U7_V25EN_Disable                           0x0
    #define       bGbl_PadSelect_U8_V25EN                      1
    #define        Gbl_PadSelect_U8_V25EN_Enable                            0x1
    #define        Gbl_PadSelect_U8_V25EN_Disable                           0x0
    #define       bGbl_PadSelect_W14_V25EN                     1
    #define        Gbl_PadSelect_W14_V25EN_Enable                           0x1
    #define        Gbl_PadSelect_W14_V25EN_Disable                          0x0
    #define       bGbl_PadSelect_DVU0_V25EN                    1
    #define        Gbl_PadSelect_DVU0_V25EN_Enable                          0x1
    #define        Gbl_PadSelect_DVU0_V25EN_Disable                         0x0
    #define       bGbl_PadSelect_GBL_V25EN                     1
    #define        Gbl_PadSelect_GBL_V25EN_Enable                           0x1
    #define        Gbl_PadSelect_GBL_V25EN_Disable                          0x0
    #define       bGbl_PadSelect_SD0_V25EN                     1
    #define        Gbl_PadSelect_SD0_V25EN_Enable                           0x1
    #define        Gbl_PadSelect_SD0_V25EN_Disable                          0x0
    #define       bGbl_PadSelect_DVIO_OEN                      1
    #define        Gbl_PadSelect_DVIO_OEN_Enable                            0x1
    #define        Gbl_PadSelect_DVIO_OEN_Disable                           0x0
    #define       bGbl_PadSelect_CLK0_ZN                       3
    #define       bGbl_PadSelect_CLK0_ZP                       3
    #define       bGbl_PadSelect_DVIO0_ZN                      3
    #define     RA_Gbl_PadSelect1                              0x0170
    #define       bGbl_PadSelect_DVIO0_ZP                      3
    #define       bGbl_PadSelect_ND0_ZN                        4
    #define       bGbl_PadSelect_ND0_ZP                        4
    #define       bGbl_PadSelect_GBL_ZN                        4
    #define       bGbl_PadSelect_GBL_ZP                        4
    #define       bGbl_PadSelect_SPI0_ZN                       4
    #define       bGbl_PadSelect_SPI0_ZP                       4
    #define       bGbl_PadSelect_SD0_ZN                        4
    #define     RA_Gbl_PadSelect2                              0x0174
    #define       bGbl_PadSelect_SD0_ZP                        4
    #define       bGbl_PadSelect_SD10_ZN                       4
    #define       bGbl_PadSelect_SD10_ZP                       4
    #define       bGbl_PadSelect_DVIO_1_V18EN                  1
    #define        Gbl_PadSelect_DVIO_1_V18EN_V1P8                          0x1
    #define        Gbl_PadSelect_DVIO_1_V18EN_V3R3                          0x0
    #define       bGbl_PadSelect_I2S_V18EN                     1
    #define        Gbl_PadSelect_I2S_V18EN_V1P8                             0x1
    #define        Gbl_PadSelect_I2S_V18EN_V3R3                             0x0
    #define       bGbl_PadSelect_DVIO_1_V25EN                  1
    #define        Gbl_PadSelect_DVIO_1_V25EN_Enable                        0x1
    #define        Gbl_PadSelect_DVIO_1_V25EN_Disable                       0x0
    #define       bGbl_PadSelect_I2S_V25EN                     1
    #define        Gbl_PadSelect_I2S_V25EN_Enable                           0x1
    #define        Gbl_PadSelect_I2S_V25EN_Disable                          0x0
    #define       bGbl_PadSelect_DVIO_1_ZN                     3
    #define       bGbl_PadSelect_DVIO_1_ZP                     3
    #define       bGbl_PadSelect_I2S_ZN                        3
    #define       bGbl_PadSelect_I2S_ZP                        3
    #define     RA_Gbl_ResetTrigger                            0x0178
    #define       bGbl_ResetTrigger_chipReset                  1
    #define        Gbl_ResetTrigger_chipReset_assert                        0x1
    #define        Gbl_ResetTrigger_chipReset_deassert                      0x0
    #define       bGbl_ResetTrigger_audio0ClkReset             1
    #define        Gbl_ResetTrigger_audio0ClkReset_assert                   0x1
    #define        Gbl_ResetTrigger_audio0ClkReset_deassert                 0x0
    #define       bGbl_ResetTrigger_audio1ClkReset             1
    #define        Gbl_ResetTrigger_audio1ClkReset_assert                   0x1
    #define        Gbl_ResetTrigger_audio1ClkReset_deassert                 0x0
    #define       bGbl_ResetTrigger_audio2ClkReset             1
    #define        Gbl_ResetTrigger_audio2ClkReset_assert                   0x1
    #define        Gbl_ResetTrigger_audio2ClkReset_deassert                 0x0
    #define       bGbl_ResetTrigger_audio3ClkReset             1
    #define        Gbl_ResetTrigger_audio3ClkReset_assert                   0x1
    #define        Gbl_ResetTrigger_audio3ClkReset_deassert                 0x0
    #define       bGbl_ResetTrigger_audioHdClkReset            1
    #define        Gbl_ResetTrigger_audioHdClkReset_assert                  0x1
    #define        Gbl_ResetTrigger_audioHdClkReset_deassert                0x0
    #define       bGbl_ResetTrigger_sysPllSyncReset            1
    #define        Gbl_ResetTrigger_sysPllSyncReset_assert                  0x1
    #define        Gbl_ResetTrigger_sysPllSyncReset_deassert                0x0
    #define       bGbl_ResetTrigger_memPllSyncReset            1
    #define        Gbl_ResetTrigger_memPllSyncReset_assert                  0x1
    #define        Gbl_ResetTrigger_memPllSyncReset_deassert                0x0
    #define       bGbl_ResetTrigger_cpu1PllSyncReset           1
    #define        Gbl_ResetTrigger_cpu1PllSyncReset_assert                 0x1
    #define        Gbl_ResetTrigger_cpu1PllSyncReset_deassert               0x0
    #define       bGbl_ResetTrigger_cpu0SyncReset              1
    #define        Gbl_ResetTrigger_cpu0SyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_cpu0SyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_cpu1SyncReset              1
    #define        Gbl_ResetTrigger_cpu1SyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_cpu1SyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_socDdrSyncReset            1
    #define        Gbl_ResetTrigger_socDdrSyncReset_assert                  0x1
    #define        Gbl_ResetTrigger_socDdrSyncReset_deassert                0x0
    #define       bGbl_ResetTrigger_gfxSyncReset               1
    #define        Gbl_ResetTrigger_gfxSyncReset_assert                     0x1
    #define        Gbl_ResetTrigger_gfxSyncReset_deassert                   0x0
    #define       bGbl_ResetTrigger_zspSyncReset               1
    #define        Gbl_ResetTrigger_zspSyncReset_assert                     0x1
    #define        Gbl_ResetTrigger_zspSyncReset_deassert                   0x0
    #define       bGbl_ResetTrigger_avioSyncReset              1
    #define        Gbl_ResetTrigger_avioSyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_avioSyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_perifSyncReset             1
    #define        Gbl_ResetTrigger_perifSyncReset_assert                   0x1
    #define        Gbl_ResetTrigger_perifSyncReset_deassert                 0x0
    #define       bGbl_ResetTrigger_gethSyncReset              1
    #define        Gbl_ResetTrigger_gethSyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_gethSyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_sataSyncReset              1
    #define        Gbl_ResetTrigger_sataSyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_sataSyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_geth1SyncReset             1
    #define        Gbl_ResetTrigger_geth1SyncReset_assert                   0x1
    #define        Gbl_ResetTrigger_geth1SyncReset_deassert                 0x0
    #define       bGbl_ResetTrigger_ahbApbSyncReset            1
    #define        Gbl_ResetTrigger_ahbApbSyncReset_assert                  0x1
    #define        Gbl_ResetTrigger_ahbApbSyncReset_deassert                0x0
    #define       bGbl_ResetTrigger_nanfSyncReset              1
    #define        Gbl_ResetTrigger_nanfSyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_nanfSyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_smemcSyncReset             1
    #define        Gbl_ResetTrigger_smemcSyncReset_assert                   0x1
    #define        Gbl_ResetTrigger_smemcSyncReset_deassert                 0x0
    #define       bGbl_ResetTrigger_drmSyncReset               1
    #define        Gbl_ResetTrigger_drmSyncReset_assert                     0x1
    #define        Gbl_ResetTrigger_drmSyncReset_deassert                   0x0
    #define       bGbl_ResetTrigger_usb0SyncReset              1
    #define        Gbl_ResetTrigger_usb0SyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_usb0SyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_usb1SyncReset              1
    #define        Gbl_ResetTrigger_usb1SyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_usb1SyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_pBridgeSyncReset           1
    #define        Gbl_ResetTrigger_pBridgeSyncReset_assert                 0x1
    #define        Gbl_ResetTrigger_pBridgeSyncReset_deassert               0x0
    #define       bGbl_ResetTrigger_vppSyncReset               1
    #define        Gbl_ResetTrigger_vppSyncReset_assert                     0x1
    #define        Gbl_ResetTrigger_vppSyncReset_deassert                   0x0
    #define       bGbl_ResetTrigger_vipSyncReset               1
    #define        Gbl_ResetTrigger_vipSyncReset_assert                     0x1
    #define        Gbl_ResetTrigger_vipSyncReset_deassert                   0x0
    #define       bGbl_ResetTrigger_appSyncReset               1
    #define        Gbl_ResetTrigger_appSyncReset_assert                     0x1
    #define        Gbl_ResetTrigger_appSyncReset_deassert                   0x0
    #define       bGbl_ResetTrigger_sdioSyncReset              1
    #define        Gbl_ResetTrigger_sdioSyncReset_assert                    0x1
    #define        Gbl_ResetTrigger_sdioSyncReset_deassert                  0x0
    #define       bGbl_ResetTrigger_sdio1SyncReset             1
    #define        Gbl_ResetTrigger_sdio1SyncReset_assert                   0x1
    #define        Gbl_ResetTrigger_sdio1SyncReset_deassert                 0x0
    #define       bGbl_ResetTrigger_hdmirxSyncReset            1
    #define        Gbl_ResetTrigger_hdmirxSyncReset_assert                  0x1
    #define        Gbl_ResetTrigger_hdmirxSyncReset_deassert                0x0
    #define     RA_Gbl_ResetStatus                             0x017C
    #define       bGbl_ResetStatus_ChipResetStatus             1
    #define        Gbl_ResetStatus_ChipResetStatus_asserted                 0x1
    #define        Gbl_ResetStatus_ChipResetStatus_deasserted               0x0
    #define       bGbl_ResetStatus_wd0Status                   1
    #define        Gbl_ResetStatus_wd0Status_asserted                       0x1
    #define        Gbl_ResetStatus_wd0Status_deasserted                     0x0
    #define       bGbl_ResetStatus_wd1Status                   1
    #define        Gbl_ResetStatus_wd1Status_asserted                       0x1
    #define        Gbl_ResetStatus_wd1Status_deasserted                     0x0
    #define       bGbl_ResetStatus_wd2Status                   1
    #define        Gbl_ResetStatus_wd2Status_asserted                       0x1
    #define        Gbl_ResetStatus_wd2Status_deasserted                     0x0
    #define       bGbl_ResetStatus_audio0ClkResetStatus        1
    #define        Gbl_ResetStatus_audio0ClkResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_audio0ClkResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_audio1ClkResetStatus        1
    #define        Gbl_ResetStatus_audio1ClkResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_audio1ClkResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_audio2ClkResetStatus        1
    #define        Gbl_ResetStatus_audio2ClkResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_audio2ClkResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_audio3ClkResetStatus        1
    #define        Gbl_ResetStatus_audio3ClkResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_audio3ClkResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_audioHdClkResetStatus       1
    #define        Gbl_ResetStatus_audioHdClkResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_audioHdClkResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_sysPllSyncResetStatus       1
    #define        Gbl_ResetStatus_sysPllSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_sysPllSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_memPllSyncResetStatus       1
    #define        Gbl_ResetStatus_memPllSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_memPllSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_cpu1PllSyncResetStatus      1
    #define        Gbl_ResetStatus_cpu1PllSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_cpu1PllSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_avPllASyncResetStatus       1
    #define        Gbl_ResetStatus_avPllASyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_avPllASyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_avPllBSyncResetStatus       1
    #define        Gbl_ResetStatus_avPllBSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_avPllBSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_cpu0SyncResetStatus         1
    #define        Gbl_ResetStatus_cpu0SyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_cpu0SyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_cpu1SyncResetStatus         1
    #define        Gbl_ResetStatus_cpu1SyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_cpu1SyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_socDdrSyncResetStatus       1
    #define        Gbl_ResetStatus_socDdrSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_socDdrSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_gfxSyncResetStatus          1
    #define        Gbl_ResetStatus_gfxSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_gfxSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_zspSyncResetStatus          1
    #define        Gbl_ResetStatus_zspSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_zspSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_avioSyncResetStatus         1
    #define        Gbl_ResetStatus_avioSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_avioSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_perifSyncResetStatus        1
    #define        Gbl_ResetStatus_perifSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_perifSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_gethSyncResetStatus         1
    #define        Gbl_ResetStatus_gethSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_gethSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_geth1SyncResetStatus        1
    #define        Gbl_ResetStatus_geth1SyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_geth1SyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_sataSyncResetStatus         1
    #define        Gbl_ResetStatus_sataSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_sataSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_ahbApbSyncResetStatus       1
    #define        Gbl_ResetStatus_ahbApbSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_ahbApbSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_nanfSyncResetStatus         1
    #define        Gbl_ResetStatus_nanfSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_nanfSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_smemcSyncResetStatus        1
    #define        Gbl_ResetStatus_smemcSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_smemcSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_drmSyncResetStatus          1
    #define        Gbl_ResetStatus_drmSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_drmSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_usb0SyncResetStatus         1
    #define        Gbl_ResetStatus_usb0SyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_usb0SyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_usb1SyncResetStatus         1
    #define        Gbl_ResetStatus_usb1SyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_usb1SyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_pBridgeSyncResetStatus      1
    #define        Gbl_ResetStatus_pBridgeSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_pBridgeSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_vppSyncResetStatus          1
    #define        Gbl_ResetStatus_vppSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_vppSyncResetStatus_deasserted              0x0
    #define     RA_Gbl_ResetStatus1                            0x0180
    #define       bGbl_ResetStatus_vipSyncResetStatus          1
    #define        Gbl_ResetStatus_vipSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_vipSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_appSyncResetStatus          1
    #define        Gbl_ResetStatus_appSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_appSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_sdioSyncResetStatus         1
    #define        Gbl_ResetStatus_sdioSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_sdioSyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_sdio1SyncResetStatus        1
    #define        Gbl_ResetStatus_sdio1SyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_sdio1SyncResetStatus_deasserted              0x0
    #define       bGbl_ResetStatus_hdmirxSyncResetStatus       1
    #define        Gbl_ResetStatus_hdmirxSyncResetStatus_asserted              0x1
    #define        Gbl_ResetStatus_hdmirxSyncResetStatus_deasserted              0x0
    #define     RA_Gbl_sw_generic0                             0x0184
    #define       bGbl_sw_generic0_swReg0                      32
    #define     RA_Gbl_sw_generic1                             0x0188
    #define       bGbl_sw_generic1_swReg1                      32
    #define     RA_Gbl_sw_generic2                             0x018C
    #define       bGbl_sw_generic2_swReg2                      32
    #define     RA_Gbl_sw_generic3                             0x0190
    #define       bGbl_sw_generic3_swReg3                      32
    #define     RA_Gbl_ChipCntl0                               0x0194
    #define       bGbl_ChipCntl0_dCacheCfgCPU0                 2
    #define       bGbl_ChipCntl0_iCacheCfgCPU0                 2
    #define       bGbl_ChipCntl0_dCacheCfgCPU1                 2
    #define       bGbl_ChipCntl0_iCacheCfgCPU1                 2
    #define       bGbl_ChipCntl0_cg_bpass0Cpu0                 1
    #define       bGbl_ChipCntl0_cg_bpass0Cpu1                 1
    #define       bGbl_ChipCntl0_wfiJtagClkEn                  1
    #define        Gbl_ChipCntl0_wfiJtagClkEn_RUNNING                       0x1
    #define        Gbl_ChipCntl0_wfiJtagClkEn_FREEZE                        0x0
    #define     RA_Gbl_ChipCntl1                               0x0198
    #define       bGbl_ChipCntl1_bpm_wtc                       2
    #define       bGbl_ChipCntl1_bpm_rtc                       2
    #define       bGbl_ChipCntl1_icl0data_wtc                  2
    #define       bGbl_ChipCntl1_icl0data_rtc                  2
    #define       bGbl_ChipCntl1_icl0tag_wtc                   2
    #define       bGbl_ChipCntl1_icl0tag_rtc                   2
    #define       bGbl_ChipCntl1_icl1data_wtc                  2
    #define       bGbl_ChipCntl1_icl1data_rtc                  2
    #define       bGbl_ChipCntl1_icl1tag_wtc                   2
    #define       bGbl_ChipCntl1_icl1tag_rtc                   2
    #define       bGbl_ChipCntl1_dcl1data_wtc                  2
    #define       bGbl_ChipCntl1_dcl1data_rtc                  2
    #define       bGbl_ChipCntl1_dcl1tag_wtc                   2
    #define       bGbl_ChipCntl1_dcl1tag_rtc                   2
    #define       bGbl_ChipCntl1_dcl1state_wtc                 2
    #define       bGbl_ChipCntl1_dcl1state_rtc                 2
    #define     RA_Gbl_ChipCntl11                              0x019C
    #define       bGbl_ChipCntl1_dcl1attr_wtc                  2
    #define       bGbl_ChipCntl1_dcl1attr_rtc                  2
    #define       bGbl_ChipCntl1_dcl1fifo_wtc                  2
    #define       bGbl_ChipCntl1_dcl1fifo_rtc                  2
    #define       bGbl_ChipCntl1_dcl0data_wtc                  2
    #define       bGbl_ChipCntl1_dcl0data_rtc                  2
    #define       bGbl_ChipCntl1_dcl0tag_wtc                   2
    #define       bGbl_ChipCntl1_dcl0tag_rtc                   2
    #define       bGbl_ChipCntl1_l2c_dataram_wtc               2
    #define       bGbl_ChipCntl1_l2c_dataram_rtc               3
    #define       bGbl_ChipCntl1_l2c_dirtyram_wtc              3
    #define       bGbl_ChipCntl1_l2c_dirtyram_rtc              2
    #define       bGbl_ChipCntl1_l2c_lockram_wtc               3
    #define       bGbl_ChipCntl1_l2c_lockram_rtc               2
    #define     RA_Gbl_ChipCntl12                              0x01A0
    #define       bGbl_ChipCntl1_l2c_eccram_wtc                2
    #define       bGbl_ChipCntl1_l2c_eccram_rtc                3
    #define       bGbl_ChipCntl1_l2c_tagram_wtc                3
    #define       bGbl_ChipCntl1_l2c_tagram_rtc                3
    #define       bGbl_ChipCntl1_l2c_tzram_wtc                 3
    #define       bGbl_ChipCntl1_l2c_tzram_rtc                 2
    #define       bGbl_ChipCntl1_l2c_validram_wtc              3
    #define       bGbl_ChipCntl1_l2c_validram_rtc              2
    #define       bGbl_ChipCntl1_mmu_wtc                       2
    #define       bGbl_ChipCntl1_mmu_rtc                       2
    #define       bGbl_ChipCntl1_sf_wtc                        2
    #define       bGbl_ChipCntl1_sf_rtc                        2
    #define     RA_Gbl_RWTC_avio31to0                          0x01A4
    #define       bGbl_RWTC_avio31to0_value                    32
    #define     RA_Gbl_RWTC_avio41to32                         0x01A8
    #define       bGbl_RWTC_avio41to32_value                   10
    #define     RA_Gbl_RWTC_gfx2D31to0                         0x01AC
    #define       bGbl_RWTC_gfx2D31to0_value                   32
    #define     RA_Gbl_RWTC_gfx2D41to32                        0x01B0
    #define       bGbl_RWTC_gfx2D41to32_value                  10
    #define     RA_Gbl_RWTC_gfx3D31to0                         0x01B4
    #define       bGbl_RWTC_gfx3D31to0_value                   32
    #define     RA_Gbl_RWTC_gfx3D41to32                        0x01B8
    #define       bGbl_RWTC_gfx3D41to32_value                  10
    #define     RA_Gbl_RWTC_soc31to0                           0x01BC
    #define       bGbl_RWTC_soc31to0_value                     32
    #define     RA_Gbl_RWTC_soc41to32                          0x01C0
    #define       bGbl_RWTC_soc41to32_value                    10
    #define     RA_Gbl_RWTC_vPro31to0                          0x01C4
    #define       bGbl_RWTC_vPro31to0_value                    32
    #define     RA_Gbl_RWTC_vPro41to32                         0x01C8
    #define       bGbl_RWTC_vPro41to32_value                   10
    #define     RA_Gbl_ProductId                               0x01CC
    #define       bGbl_ProductId_Id                            32
    #define     RA_Gbl_ProductId_ext                           0x01D0
    #define       bGbl_ProductId_ext_ID_EXT                    8
    #define     RA_Gbl_FPGAR                                   0x01D4
    #define       bGbl_FPGAR_FPGAR                             32
    #define     RA_Gbl_FPGARW                                  0x01D8
    #define       bGbl_FPGARW_FPGARW                           32
    #define     RA_Gbl_RingOscCtl                              0x01DC
    #define       bGbl_RingOscCtl_centerInit                   1
    #define        Gbl_RingOscCtl_centerInit_OFF                            0x0
    #define        Gbl_RingOscCtl_centerInit_ON                             0x1
    #define       bGbl_RingOscCtl_avioTopInit                  1
    #define        Gbl_RingOscCtl_avioTopInit_OFF                           0x0
    #define        Gbl_RingOscCtl_avioTopInit_ON                            0x1
    #define       bGbl_RingOscCtl_avioBotInit                  1
    #define        Gbl_RingOscCtl_avioBotInit_OFF                           0x0
    #define        Gbl_RingOscCtl_avioBotInit_ON                            0x1
    #define       bGbl_RingOscCtl_usbTopInit                   1
    #define        Gbl_RingOscCtl_usbTopInit_OFF                            0x0
    #define        Gbl_RingOscCtl_usbTopInit_ON                             0x1
    #define       bGbl_RingOscCtl_cpu1TopInit                  1
    #define        Gbl_RingOscCtl_cpu1TopInit_OFF                           0x0
    #define        Gbl_RingOscCtl_cpu1TopInit_ON                            0x1
    #define       bGbl_RingOscCtl_cpu0TopInit                  1
    #define        Gbl_RingOscCtl_cpu0TopInit_OFF                           0x0
    #define        Gbl_RingOscCtl_cpu0TopInit_ON                            0x1
    #define       bGbl_RingOscCtl_cpuBotInit                   1
    #define        Gbl_RingOscCtl_cpuBotInit_OFF                            0x0
    #define        Gbl_RingOscCtl_cpuBotInit_ON                             0x1
    #define       bGbl_RingOscCtl_topRiteInit                  1
    #define        Gbl_RingOscCtl_topRiteInit_OFF                           0x0
    #define        Gbl_RingOscCtl_topRiteInit_ON                            0x1
    #define       bGbl_RingOscCtl_midRiteInit                  1
    #define        Gbl_RingOscCtl_midRiteInit_OFF                           0x0
    #define        Gbl_RingOscCtl_midRiteInit_ON                            0x1
    #define       bGbl_RingOscCtl_botRiteInit                  1
    #define        Gbl_RingOscCtl_botRiteInit_OFF                           0x0
    #define        Gbl_RingOscCtl_botRiteInit_ON                            0x1
    #define     RA_Gbl_PLLBypsBootStrapEn                      0x01E0
    #define       bGbl_PLLBypsBootStrapEn_sysPLLBypsEn         1
    #define        Gbl_PLLBypsBootStrapEn_sysPLLBypsEn_Disable              0x0
    #define        Gbl_PLLBypsBootStrapEn_sysPLLBypsEn_Enable               0x1
    #define       bGbl_PLLBypsBootStrapEn_memPLLBypsEn         1
    #define        Gbl_PLLBypsBootStrapEn_memPLLBypsEn_Disable              0x0
    #define        Gbl_PLLBypsBootStrapEn_memPLLBypsEn_Enable               0x1
    #define       bGbl_PLLBypsBootStrapEn_cpu1PLLBypsEn        1
    #define        Gbl_PLLBypsBootStrapEn_cpu1PLLBypsEn_Disable              0x0
    #define        Gbl_PLLBypsBootStrapEn_cpu1PLLBypsEn_Enable              0x1
    #define     RA_Gbl_IO_CALIBRATE_IN                         0x01E4
    #define       bGbl_IO_CALIBRATE_IN_DO                      1
    #define        Gbl_IO_CALIBRATE_IN_DO_NMOS                              0x0
    #define        Gbl_IO_CALIBRATE_IN_DO_PMOS                              0x1
    #define       bGbl_IO_CALIBRATE_IN_CAL_EN                  1
    #define        Gbl_IO_CALIBRATE_IN_CAL_EN_DISABLE                       0x0
    #define        Gbl_IO_CALIBRATE_IN_CAL_EN_ENABLE                        0x1
    #define       bGbl_IO_CALIBRATE_IN_ZP_CAL                  3
    #define       bGbl_IO_CALIBRATE_IN_ZN_CAL                  3
    #define       bGbl_IO_CALIBRATE_IN_RON_ADJ                 3
    #define       bGbl_IO_CALIBRATE_IN_TSI_CAL_N_EN            1
    #define       bGbl_IO_CALIBRATE_IN_TSI_CAL_P_EN            1
    #define       bGbl_IO_CALIBRATE_IN_TSI_ODR                 3
    #define       bGbl_IO_CALIBRATE_IN_TSI_ODR_EN              1
    #define       bGbl_IO_CALIBRATE_IN_TSI_ZN                  4
    #define       bGbl_IO_CALIBRATE_IN_TSI_ZP                  4
    #define       bGbl_IO_CALIBRATE_IN_TSI_ZP_AFT_CAL          4
    #define       bGbl_IO_CALIBRATE_IN_NAND_CAL_N_EN           1
    #define       bGbl_IO_CALIBRATE_IN_NAND_CAL_P_EN           1
    #define     RA_Gbl_IO_CALIBRATE_IN1                        0x01E8
    #define       bGbl_IO_CALIBRATE_IN_NAND_ODR                3
    #define       bGbl_IO_CALIBRATE_IN_NAND_ODR_EN             1
    #define       bGbl_IO_CALIBRATE_IN_NAND_ZN                 4
    #define       bGbl_IO_CALIBRATE_IN_NAND_ZP                 4
    #define       bGbl_IO_CALIBRATE_IN_NAND_ZP_AFT_CAL         4
    #define       bGbl_IO_CALIBRATE_IN_SPI_CAL_N_EN            1
    #define       bGbl_IO_CALIBRATE_IN_SPI_CAL_P_EN            1
    #define       bGbl_IO_CALIBRATE_IN_SPI_ODR                 3
    #define       bGbl_IO_CALIBRATE_IN_SPI_ODR_EN              1
    #define       bGbl_IO_CALIBRATE_IN_SPI_ZN                  4
    #define       bGbl_IO_CALIBRATE_IN_SPI_ZP                  4
    #define     RA_Gbl_IO_CALIBRATE_IN2                        0x01EC
    #define       bGbl_IO_CALIBRATE_IN_SPI_ZP_AFT_CAL          4
    #define       bGbl_IO_CALIBRATE_IN_SD0_CAL_N_EN            1
    #define       bGbl_IO_CALIBRATE_IN_SD0_CAL_P_EN            1
    #define       bGbl_IO_CALIBRATE_IN_SD0_ODR                 3
    #define       bGbl_IO_CALIBRATE_IN_SD0_ODR_EN              1
    #define       bGbl_IO_CALIBRATE_IN_SD0_ZN                  4
    #define       bGbl_IO_CALIBRATE_IN_SD0_ZP                  4
    #define       bGbl_IO_CALIBRATE_IN_SD0_ZP_AFT_CAL          4
    #define       bGbl_IO_CALIBRATE_IN_SD1_CAL_N_EN            1
    #define       bGbl_IO_CALIBRATE_IN_SD1_CAL_P_EN            1
    #define       bGbl_IO_CALIBRATE_IN_SD1_ODR                 3
    #define       bGbl_IO_CALIBRATE_IN_SD1_ODR_EN              1
    #define       bGbl_IO_CALIBRATE_IN_SD1_ZN                  4
    #define     RA_Gbl_IO_CALIBRATE_IN3                        0x01F0
    #define       bGbl_IO_CALIBRATE_IN_SD1_ZP                  4
    #define       bGbl_IO_CALIBRATE_IN_SD1_ZP_AFT_CAL          4
    #define       bGbl_IO_CALIBRATE_IN_DVIO_1_DO               1
    #define        Gbl_IO_CALIBRATE_IN_DVIO_1_DO_NMOS                       0x0
    #define        Gbl_IO_CALIBRATE_IN_DVIO_1_DO_PMOS                       0x1
    #define       bGbl_IO_CALIBRATE_IN_DVIO_1_CAL_EN           1
    #define        Gbl_IO_CALIBRATE_IN_DVIO_1_CAL_EN_DISABLE                0x0
    #define        Gbl_IO_CALIBRATE_IN_DVIO_1_CAL_EN_ENABLE                 0x1
    #define       bGbl_IO_CALIBRATE_IN_DVIO_1_ZP_CAL           3
    #define       bGbl_IO_CALIBRATE_IN_DVIO_1_ZN_CAL           3
    #define       bGbl_IO_CALIBRATE_IN_DVIO_1_RON_ADJ          3
    #define       bGbl_IO_CALIBRATE_IN_I2S_DO                  1
    #define        Gbl_IO_CALIBRATE_IN_I2S_DO_NMOS                          0x0
    #define        Gbl_IO_CALIBRATE_IN_I2S_DO_PMOS                          0x1
    #define       bGbl_IO_CALIBRATE_IN_I2S_CAL_EN              1
    #define        Gbl_IO_CALIBRATE_IN_I2S_CAL_EN_DISABLE                   0x0
    #define        Gbl_IO_CALIBRATE_IN_I2S_CAL_EN_ENABLE                    0x1
    #define       bGbl_IO_CALIBRATE_IN_I2S_ZP_CAL              3
    #define       bGbl_IO_CALIBRATE_IN_I2S_ZN_CAL              3
    #define       bGbl_IO_CALIBRATE_IN_I2S_RON_ADJ             3
    #define     RA_Gbl_IO_CALBRATE_OUT                         0x01F4
    #define       bGbl_IO_CALBRATE_OUT_INC                     1
    #define       bGbl_IO_CALBRATE_OUT_TSI_CAL_N_INC           1
    #define       bGbl_IO_CALBRATE_OUT_TSI_CAL_P_INC           1
    #define       bGbl_IO_CALBRATE_OUT_SD0_CAL_N_INC           1
    #define       bGbl_IO_CALBRATE_OUT_SD0_CAL_P_INC           1
    #define       bGbl_IO_CALBRATE_OUT_SD1_CAL_N_INC           1
    #define       bGbl_IO_CALBRATE_OUT_SD1_CAL_P_INC           1
    #define       bGbl_IO_CALBRATE_OUT_NAND_CAL_N_INC          1
    #define       bGbl_IO_CALBRATE_OUT_NAND_CAL_P_INC          1
    #define       bGbl_IO_CALBRATE_OUT_DVIO_1_INC              1
    #define       bGbl_IO_CALBRATE_OUT_I2S_INC                 1
    #define     RA_Gbl_SECURE_SCAN_EN                          0x01F8
    #define       bGbl_SECURE_SCAN_EN_SET                      1
    #define     RA_Gbl_NandWPn                                 0x01FC
    #define       bGbl_NandWPn_Sel                             1
    #define     RA_Gbl_RingCntCntl                             0x0200
    #define       bGbl_RingCntCntl_centerStart                 1
    #define       bGbl_RingCntCntl_centerStop                  1
    #define       bGbl_RingCntCntl_avioTopStart                1
    #define       bGbl_RingCntCntl_avioTopStop                 1
    #define       bGbl_RingCntCntl_avioBotStart                1
    #define       bGbl_RingCntCntl_avioBotStop                 1
    #define       bGbl_RingCntCntl_usbTopStart                 1
    #define       bGbl_RingCntCntl_usbTopStop                  1
    #define       bGbl_RingCntCntl_cpu1TopStart                1
    #define       bGbl_RingCntCntl_cpu1TopStop                 1
    #define       bGbl_RingCntCntl_cpu0TopStart                1
    #define       bGbl_RingCntCntl_cpu0TopStop                 1
    #define       bGbl_RingCntCntl_cpuBotStart                 1
    #define       bGbl_RingCntCntl_cpuBotStop                  1
    #define       bGbl_RingCntCntl_topRiteStart                1
    #define       bGbl_RingCntCntl_topRiteStop                 1
    #define       bGbl_RingCntCntl_midRiteStart                1
    #define       bGbl_RingCntCntl_midRiteStop                 1
    #define       bGbl_RingCntCntl_botRiteStart                1
    #define       bGbl_RingCntCntl_botRiteStop                 1
    #define     RA_Gbl_topSvtDro0Cnt                           0x0204
    #define     RA_Gbl_topLvtDro1Cnt                           0x0208
    #define     RA_Gbl_topSvtDro2Cnt                           0x020C
    #define     RA_Gbl_topLvtDro3Cnt                           0x0210
    #define     RA_Gbl_topSvtDro4Cnt                           0x0214
    #define     RA_Gbl_topLvtDro5Cnt                           0x0218
    #define     RA_Gbl_avioSvtDro0Cnt                          0x021C
    #define     RA_Gbl_avioLvtDro1Cnt                          0x0220
    #define     RA_Gbl_avioSvtDro2Cnt                          0x0224
    #define     RA_Gbl_avioLvtDro3Cnt                          0x0228
    #define     RA_Gbl_gfx3DCoreClkCtrl                        0x022C
    #define       bGbl_gfx3DCoreClkCtrl_clkEN                  1
    #define        Gbl_gfx3DCoreClkCtrl_clkEN_enable                        0x1
    #define        Gbl_gfx3DCoreClkCtrl_clkEN_disable                       0x0
    #define       bGbl_gfx3DCoreClkCtrl_ClkPllSel              3
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSel_AVPllB4                   0x0
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSel_AVPllB5                   0x1
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSel_AVPllB6                   0x2
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSel_AVPllB7                   0x3
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSel_SYSPll                    0x4
    #define       bGbl_gfx3DCoreClkCtrl_ClkPllSwitch           1
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSwitch_SYSPLL                 0x0
    #define        Gbl_gfx3DCoreClkCtrl_ClkPllSwitch_AVPLL                  0x1
    #define       bGbl_gfx3DCoreClkCtrl_ClkSwitch              1
    #define        Gbl_gfx3DCoreClkCtrl_ClkSwitch_SrcClk                    0x0
    #define        Gbl_gfx3DCoreClkCtrl_ClkSwitch_DivClk                    0x1
    #define       bGbl_gfx3DCoreClkCtrl_ClkD3Switch            1
    #define        Gbl_gfx3DCoreClkCtrl_ClkD3Switch_NonDiv3Clk              0x0
    #define        Gbl_gfx3DCoreClkCtrl_ClkD3Switch_Div3Clk                 0x1
    #define       bGbl_gfx3DCoreClkCtrl_ClkSel                 3
    #define        Gbl_gfx3DCoreClkCtrl_ClkSel_d2                           0x1
    #define        Gbl_gfx3DCoreClkCtrl_ClkSel_d4                           0x2
    #define        Gbl_gfx3DCoreClkCtrl_ClkSel_d6                           0x3
    #define        Gbl_gfx3DCoreClkCtrl_ClkSel_d8                           0x4
    #define        Gbl_gfx3DCoreClkCtrl_ClkSel_d12                          0x5
    #define     RA_Gbl_gfx3DSysClkCtrl                         0x0230
    #define       bGbl_gfx3DSysClkCtrl_clkEN                   1
    #define        Gbl_gfx3DSysClkCtrl_clkEN_enable                         0x1
    #define        Gbl_gfx3DSysClkCtrl_clkEN_disable                        0x0
    #define       bGbl_gfx3DSysClkCtrl_ClkPllSel               3
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSel_AVPllB4                    0x0
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSel_AVPllB5                    0x1
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSel_AVPllB6                    0x2
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSel_AVPllB7                    0x3
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSel_SYSPll                     0x4
    #define       bGbl_gfx3DSysClkCtrl_ClkPllSwitch            1
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSwitch_SYSPLL                  0x0
    #define        Gbl_gfx3DSysClkCtrl_ClkPllSwitch_AVPLL                   0x1
    #define       bGbl_gfx3DSysClkCtrl_ClkSwitch               1
    #define        Gbl_gfx3DSysClkCtrl_ClkSwitch_SrcClk                     0x0
    #define        Gbl_gfx3DSysClkCtrl_ClkSwitch_DivClk                     0x1
    #define       bGbl_gfx3DSysClkCtrl_ClkD3Switch             1
    #define        Gbl_gfx3DSysClkCtrl_ClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_gfx3DSysClkCtrl_ClkD3Switch_Div3Clk                  0x1
    #define       bGbl_gfx3DSysClkCtrl_ClkSel                  3
    #define        Gbl_gfx3DSysClkCtrl_ClkSel_d2                            0x1
    #define        Gbl_gfx3DSysClkCtrl_ClkSel_d4                            0x2
    #define        Gbl_gfx3DSysClkCtrl_ClkSel_d6                            0x3
    #define        Gbl_gfx3DSysClkCtrl_ClkSel_d8                            0x4
    #define        Gbl_gfx3DSysClkCtrl_ClkSel_d12                           0x5
    #define     RA_Gbl_arcRefClkCtrl                           0x0234
    #define       bGbl_arcRefClkCtrl_clkEN                     1
    #define        Gbl_arcRefClkCtrl_clkEN_enable                           0x1
    #define        Gbl_arcRefClkCtrl_clkEN_disable                          0x0
    #define       bGbl_arcRefClkCtrl_ClkPllSel                 3
    #define        Gbl_arcRefClkCtrl_ClkPllSel_AVPllB4                      0x0
    #define        Gbl_arcRefClkCtrl_ClkPllSel_AVPllB5                      0x1
    #define        Gbl_arcRefClkCtrl_ClkPllSel_AVPllB6                      0x2
    #define        Gbl_arcRefClkCtrl_ClkPllSel_AVPllB7                      0x3
    #define        Gbl_arcRefClkCtrl_ClkPllSel_SYSPll                       0x4
    #define       bGbl_arcRefClkCtrl_ClkPllSwitch              1
    #define        Gbl_arcRefClkCtrl_ClkPllSwitch_SYSPLL                    0x0
    #define        Gbl_arcRefClkCtrl_ClkPllSwitch_AVPLL                     0x1
    #define       bGbl_arcRefClkCtrl_ClkSwitch                 1
    #define        Gbl_arcRefClkCtrl_ClkSwitch_SrcClk                       0x0
    #define        Gbl_arcRefClkCtrl_ClkSwitch_DivClk                       0x1
    #define       bGbl_arcRefClkCtrl_ClkD3Switch               1
    #define        Gbl_arcRefClkCtrl_ClkD3Switch_NonDiv3Clk                 0x0
    #define        Gbl_arcRefClkCtrl_ClkD3Switch_Div3Clk                    0x1
    #define       bGbl_arcRefClkCtrl_ClkSel                    3
    #define        Gbl_arcRefClkCtrl_ClkSel_d2                              0x1
    #define        Gbl_arcRefClkCtrl_ClkSel_d4                              0x2
    #define        Gbl_arcRefClkCtrl_ClkSel_d6                              0x3
    #define        Gbl_arcRefClkCtrl_ClkSel_d8                              0x4
    #define        Gbl_arcRefClkCtrl_ClkSel_d12                             0x5
    #define     RA_Gbl_vipClkCtrl                              0x0238
    #define       bGbl_vipClkCtrl_clkEN                        1
    #define        Gbl_vipClkCtrl_clkEN_enable                              0x1
    #define        Gbl_vipClkCtrl_clkEN_disable                             0x0
    #define       bGbl_vipClkCtrl_ClkPllSel                    3
    #define        Gbl_vipClkCtrl_ClkPllSel_AVPllB4                         0x0
    #define        Gbl_vipClkCtrl_ClkPllSel_AVPllB5                         0x1
    #define        Gbl_vipClkCtrl_ClkPllSel_AVPllB6                         0x2
    #define        Gbl_vipClkCtrl_ClkPllSel_AVPllB7                         0x3
    #define        Gbl_vipClkCtrl_ClkPllSel_SYSPll                          0x4
    #define       bGbl_vipClkCtrl_ClkPllSwitch                 1
    #define        Gbl_vipClkCtrl_ClkPllSwitch_SYSPLL                       0x0
    #define        Gbl_vipClkCtrl_ClkPllSwitch_AVPLL                        0x1
    #define       bGbl_vipClkCtrl_ClkSwitch                    1
    #define        Gbl_vipClkCtrl_ClkSwitch_SrcClk                          0x0
    #define        Gbl_vipClkCtrl_ClkSwitch_DivClk                          0x1
    #define       bGbl_vipClkCtrl_ClkD3Switch                  1
    #define        Gbl_vipClkCtrl_ClkD3Switch_NonDiv3Clk                    0x0
    #define        Gbl_vipClkCtrl_ClkD3Switch_Div3Clk                       0x1
    #define       bGbl_vipClkCtrl_ClkSel                       3
    #define        Gbl_vipClkCtrl_ClkSel_d2                                 0x1
    #define        Gbl_vipClkCtrl_ClkSel_d4                                 0x2
    #define        Gbl_vipClkCtrl_ClkSel_d6                                 0x3
    #define        Gbl_vipClkCtrl_ClkSel_d8                                 0x4
    #define        Gbl_vipClkCtrl_ClkSel_d12                                0x5
    #define     RA_Gbl_sdioXinClkCtrl                          0x023C
    #define       bGbl_sdioXinClkCtrl_ClkEN                    1
    #define        Gbl_sdioXinClkCtrl_ClkEN_enable                          0x1
    #define        Gbl_sdioXinClkCtrl_ClkEN_disable                         0x0
    #define       bGbl_sdioXinClkCtrl_ClkPllSel                3
    #define        Gbl_sdioXinClkCtrl_ClkPllSel_AVPllB4                     0x0
    #define        Gbl_sdioXinClkCtrl_ClkPllSel_AVPllB5                     0x1
    #define        Gbl_sdioXinClkCtrl_ClkPllSel_AVPllB6                     0x2
    #define        Gbl_sdioXinClkCtrl_ClkPllSel_AVPllB7                     0x3
    #define        Gbl_sdioXinClkCtrl_ClkPllSel_SYSPll                      0x4
    #define       bGbl_sdioXinClkCtrl_ClkPllSwitch             1
    #define        Gbl_sdioXinClkCtrl_ClkPllSwitch_SYSPLL                   0x0
    #define        Gbl_sdioXinClkCtrl_ClkPllSwitch_AVPLL                    0x1
    #define       bGbl_sdioXinClkCtrl_ClkSwitch                1
    #define        Gbl_sdioXinClkCtrl_ClkSwitch_SrcClk                      0x0
    #define        Gbl_sdioXinClkCtrl_ClkSwitch_DivClk                      0x1
    #define       bGbl_sdioXinClkCtrl_ClkD3Switch              1
    #define        Gbl_sdioXinClkCtrl_ClkD3Switch_NonDiv3Clk                0x0
    #define        Gbl_sdioXinClkCtrl_ClkD3Switch_Div3Clk                   0x1
    #define       bGbl_sdioXinClkCtrl_ClkSel                   3
    #define        Gbl_sdioXinClkCtrl_ClkSel_d2                             0x1
    #define        Gbl_sdioXinClkCtrl_ClkSel_d4                             0x2
    #define        Gbl_sdioXinClkCtrl_ClkSel_d6                             0x3
    #define        Gbl_sdioXinClkCtrl_ClkSel_d8                             0x4
    #define        Gbl_sdioXinClkCtrl_ClkSel_d12                            0x5
    #define     RA_Gbl_sdio1XinClkCtrl                         0x0240
    #define       bGbl_sdio1XinClkCtrl_ClkEN                   1
    #define        Gbl_sdio1XinClkCtrl_ClkEN_enable                         0x1
    #define        Gbl_sdio1XinClkCtrl_ClkEN_disable                        0x0
    #define       bGbl_sdio1XinClkCtrl_ClkPllSel               3
    #define        Gbl_sdio1XinClkCtrl_ClkPllSel_AVPllB4                    0x0
    #define        Gbl_sdio1XinClkCtrl_ClkPllSel_AVPllB5                    0x1
    #define        Gbl_sdio1XinClkCtrl_ClkPllSel_AVPllB6                    0x2
    #define        Gbl_sdio1XinClkCtrl_ClkPllSel_AVPllB7                    0x3
    #define        Gbl_sdio1XinClkCtrl_ClkPllSel_SYSPll                     0x4
    #define       bGbl_sdio1XinClkCtrl_ClkPllSwitch            1
    #define        Gbl_sdio1XinClkCtrl_ClkPllSwitch_SYSPLL                  0x0
    #define        Gbl_sdio1XinClkCtrl_ClkPllSwitch_AVPLL                   0x1
    #define       bGbl_sdio1XinClkCtrl_ClkSwitch               1
    #define        Gbl_sdio1XinClkCtrl_ClkSwitch_SrcClk                     0x0
    #define        Gbl_sdio1XinClkCtrl_ClkSwitch_DivClk                     0x1
    #define       bGbl_sdio1XinClkCtrl_ClkD3Switch             1
    #define        Gbl_sdio1XinClkCtrl_ClkD3Switch_NonDiv3Clk               0x0
    #define        Gbl_sdio1XinClkCtrl_ClkD3Switch_Div3Clk                  0x1
    #define       bGbl_sdio1XinClkCtrl_ClkSel                  3
    #define        Gbl_sdio1XinClkCtrl_ClkSel_d2                            0x1
    #define        Gbl_sdio1XinClkCtrl_ClkSel_d4                            0x2
    #define        Gbl_sdio1XinClkCtrl_ClkSel_d6                            0x3
    #define        Gbl_sdio1XinClkCtrl_ClkSel_d8                            0x4
    #define        Gbl_sdio1XinClkCtrl_ClkSel_d12                           0x5
    #define     RA_Gbl_gfx3DExtraClkCtrl                       0x0244
    #define       bGbl_gfx3DExtraClkCtrl_ClkEN                 1
    #define        Gbl_gfx3DExtraClkCtrl_ClkEN_enable                       0x1
    #define        Gbl_gfx3DExtraClkCtrl_ClkEN_disable                      0x0
    #define       bGbl_gfx3DExtraClkCtrl_ClkPllSel             3
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSel_AVPllB4                  0x0
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSel_AVPllB5                  0x1
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSel_AVPllB6                  0x2
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSel_AVPllB7                  0x3
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSel_SYSPll                   0x4
    #define       bGbl_gfx3DExtraClkCtrl_ClkPllSwitch          1
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSwitch_SYSPLL                0x0
    #define        Gbl_gfx3DExtraClkCtrl_ClkPllSwitch_AVPLL                 0x1
    #define       bGbl_gfx3DExtraClkCtrl_ClkSwitch             1
    #define        Gbl_gfx3DExtraClkCtrl_ClkSwitch_SrcClk                   0x0
    #define        Gbl_gfx3DExtraClkCtrl_ClkSwitch_DivClk                   0x1
    #define       bGbl_gfx3DExtraClkCtrl_ClkD3Switch           1
    #define        Gbl_gfx3DExtraClkCtrl_ClkD3Switch_NonDiv3Clk              0x0
    #define        Gbl_gfx3DExtraClkCtrl_ClkD3Switch_Div3Clk                0x1
    #define       bGbl_gfx3DExtraClkCtrl_ClkSel                3
    #define        Gbl_gfx3DExtraClkCtrl_ClkSel_d2                          0x1
    #define        Gbl_gfx3DExtraClkCtrl_ClkSel_d4                          0x2
    #define        Gbl_gfx3DExtraClkCtrl_ClkSel_d6                          0x3
    #define        Gbl_gfx3DExtraClkCtrl_ClkSel_d8                          0x4
    #define        Gbl_gfx3DExtraClkCtrl_ClkSel_d12                         0x5
    #define     RA_Gbl_gfx3DReset                              0x0248
    #define       bGbl_gfx3DReset_SyncReset                    1
    #define        Gbl_gfx3DReset_SyncReset_assert                          0x1
    #define        Gbl_gfx3DReset_SyncReset_deassert                        0x0
    #define     RA_Gbl_gc360ClkCtrl                            0x024C
    #define       bGbl_gc360ClkCtrl_ClkEN                      1
    #define        Gbl_gc360ClkCtrl_ClkEN_enable                            0x1
    #define        Gbl_gc360ClkCtrl_ClkEN_disable                           0x0
    #define       bGbl_gc360ClkCtrl_ClkPllSel                  3
    #define        Gbl_gc360ClkCtrl_ClkPllSel_AVPllB4                       0x0
    #define        Gbl_gc360ClkCtrl_ClkPllSel_AVPllB5                       0x1
    #define        Gbl_gc360ClkCtrl_ClkPllSel_AVPllB6                       0x2
    #define        Gbl_gc360ClkCtrl_ClkPllSel_AVPllB7                       0x3
    #define        Gbl_gc360ClkCtrl_ClkPllSel_SYSPll                        0x4
    #define       bGbl_gc360ClkCtrl_ClkPllSwitch               1
    #define        Gbl_gc360ClkCtrl_ClkPllSwitch_SYSPLL                     0x0
    #define        Gbl_gc360ClkCtrl_ClkPllSwitch_AVPLL                      0x1
    #define       bGbl_gc360ClkCtrl_ClkSwitch                  1
    #define        Gbl_gc360ClkCtrl_ClkSwitch_SrcClk                        0x0
    #define        Gbl_gc360ClkCtrl_ClkSwitch_DivClk                        0x1
    #define       bGbl_gc360ClkCtrl_ClkD3Switch                1
    #define        Gbl_gc360ClkCtrl_ClkD3Switch_NonDiv3Clk                  0x0
    #define        Gbl_gc360ClkCtrl_ClkD3Switch_Div3Clk                     0x1
    #define       bGbl_gc360ClkCtrl_ClkSel                     3
    #define        Gbl_gc360ClkCtrl_ClkSel_d2                               0x1
    #define        Gbl_gc360ClkCtrl_ClkSel_d4                               0x2
    #define        Gbl_gc360ClkCtrl_ClkSel_d6                               0x3
    #define        Gbl_gc360ClkCtrl_ClkSel_d8                               0x4
    #define        Gbl_gc360ClkCtrl_ClkSel_d12                              0x5
    #define     RA_Gbl_sdioDllMstRef                           0x0250
    #define       bGbl_sdioDllMstRef_ClkEN                     1
    #define        Gbl_sdioDllMstRef_ClkEN_enable                           0x1
    #define        Gbl_sdioDllMstRef_ClkEN_disable                          0x0
    #define       bGbl_sdioDllMstRef_ClkPllSel                 3
    #define        Gbl_sdioDllMstRef_ClkPllSel_AVPllB4                      0x0
    #define        Gbl_sdioDllMstRef_ClkPllSel_AVPllB5                      0x1
    #define        Gbl_sdioDllMstRef_ClkPllSel_AVPllB6                      0x2
    #define        Gbl_sdioDllMstRef_ClkPllSel_AVPllB7                      0x3
    #define        Gbl_sdioDllMstRef_ClkPllSel_SYSPll                       0x4
    #define       bGbl_sdioDllMstRef_ClkPllSwitch              1
    #define        Gbl_sdioDllMstRef_ClkPllSwitch_SYSPLL                    0x0
    #define        Gbl_sdioDllMstRef_ClkPllSwitch_AVPLL                     0x1
    #define       bGbl_sdioDllMstRef_ClkSwitch                 1
    #define        Gbl_sdioDllMstRef_ClkSwitch_SrcClk                       0x0
    #define        Gbl_sdioDllMstRef_ClkSwitch_DivClk                       0x1
    #define       bGbl_sdioDllMstRef_ClkD3Switch               1
    #define        Gbl_sdioDllMstRef_ClkD3Switch_NonDiv3Clk                 0x0
    #define        Gbl_sdioDllMstRef_ClkD3Switch_Div3Clk                    0x1
    #define       bGbl_sdioDllMstRef_ClkSel                    3
    #define        Gbl_sdioDllMstRef_ClkSel_d2                              0x1
    #define        Gbl_sdioDllMstRef_ClkSel_d4                              0x2
    #define        Gbl_sdioDllMstRef_ClkSel_d6                              0x3
    #define        Gbl_sdioDllMstRef_ClkSel_d8                              0x4
    #define        Gbl_sdioDllMstRef_ClkSel_d12                             0x5
    #define     RA_Gbl_sdioDllMstCtrl                          0x0254
    #define       bGbl_sdioDllMstCtrl_PH_SEL1                  5
    #define       bGbl_sdioDllMstCtrl_PH_SEL2                  5
    #define       bGbl_sdioDllMstCtrl_PH_SEL3                  5
    #define       bGbl_sdioDllMstCtrl_PH_SEL4                  5
    #define       bGbl_sdioDllMstCtrl_AUTO_UPDATE_EN           1
    #define       bGbl_sdioDllMstCtrl_UPDATE_EN                1
    #define       bGbl_sdioDllMstCtrl_RESET                    1
    #define       bGbl_sdioDllMstCtrl_GAIN2X                   1
    #define       bGbl_sdioDllMstCtrl_TEST_EN                  1
    #define       bGbl_sdioDllMstCtrl_BYPASS_EN                1
    #define     RA_Gbl_sdioDllMstCtrl1                         0x0258
    #define       bGbl_sdioDllMstCtrl_DELAY_TEST               9
    #define       bGbl_sdioDllMstCtrl_RESERVE                  5
    #define     RA_Gbl_sdioDllMstStatus                        0x025C
    #define       bGbl_sdioDllMstStatus_DELAY_CTRL2            9
    #define       bGbl_sdioDllMstStatus_DELAY_CTRL3            9
    #define       bGbl_sdioDllMstStatus_DELAY_CTRL4            9
    #define       bGbl_sdioDllMstStatus_PRE_LOCK               1
    #define       bGbl_sdioDllMstStatus_DLL_LOCK               1
    #define     RA_Gbl_sdioDllMstStatus1                       0x0260
    #define       bGbl_sdioDllMstStatus_DELAY_OUT              8
    #define     RA_Gbl_sdioPortSel                             0x0264
    #define       bGbl_sdioPortSel_port0                       1
    #define       bGbl_sdioPortSel_port1                       1
    #define     RA_Gbl_gc360Reset                              0x0268
    #define       bGbl_gc360Reset_SyncReset                    1
    #define        Gbl_gc360Reset_SyncReset_assert                          0x1
    #define        Gbl_gc360Reset_SyncReset_deassert                        0x0
    #define     RA_Gbl_SpdifRxReset                            0x026C
    #define       bGbl_SpdifRxReset_SyncReset                  1
    #define        Gbl_SpdifRxReset_SyncReset_assert                        0x1
    #define        Gbl_SpdifRxReset_SyncReset_deassert                      0x0
    #define     RA_Gbl_gfx3DDisRamClkGate                      0x0270
    #define       bGbl_gfx3DDisRamClkGate_drcg                 1
    #define        Gbl_gfx3DDisRamClkGate_drcg_drcgActive                   0x1
    #define        Gbl_gfx3DDisRamClkGate_drcg_drcgInactive                 0x0
    #define     RA_Gbl_gfx3DResetStatus                        0x0274
    #define       bGbl_gfx3DResetStatus_SyncReset              1
    #define        Gbl_gfx3DResetStatus_SyncReset_assert                    0x1
    #define        Gbl_gfx3DResetStatus_SyncReset_deassert                  0x0
    #define     RA_Gbl_gc360DisRCG                             0x0278
    #define       bGbl_gc360DisRCG_drcg                        1
    #define        Gbl_gc360DisRCG_drcg_drcgActive                          0x1
    #define        Gbl_gc360DisRCG_drcg_drcgInactive                        0x0
    #define     RA_Gbl_gc360ResetStatus                        0x027C
    #define       bGbl_gc360ResetStatus_SyncReset              1
    #define        Gbl_gc360ResetStatus_SyncReset_assert                    0x1
    #define        Gbl_gc360ResetStatus_SyncReset_deassert                  0x0
    #define     RA_Gbl_SpdifRxResetStatus                      0x0280
    #define       bGbl_SpdifRxResetStatus_SyncReset            1
    #define        Gbl_SpdifRxResetStatus_SyncReset_assert                  0x1
    #define        Gbl_SpdifRxResetStatus_SyncReset_deassert                0x0
    #define     RA_Gbl_DroEnable                               0x0284
    #define       bGbl_DroEnable_EnDroCounter                  1
    #define        Gbl_DroEnable_EnDroCounter_assert                        0x1
    #define        Gbl_DroEnable_EnDroCounter_deassert                      0x0
    #define     RA_Gbl_DroCounter                              0x0288
    #define       bGbl_DroCounter_CountVal                     32
    #define     RA_Gbl_DroDone                                 0x028C
    #define       bGbl_DroDone_status                          1
    #define     RA_Gbl_cpussSvtDro0Cnt                         0x0290
    #define     RA_Gbl_cpussLvtDro1Cnt                         0x0294
    #define     RA_Gbl_cpussSvtDro2Cnt                         0x0298
    #define     RA_Gbl_cpussLvtDro3Cnt                         0x029C
    #define     RA_Gbl_vMetaSvtDro0Cnt                         0x02A0
    #define     RA_Gbl_vMetaLvtDro1Cnt                         0x02A4
    #define     RA_Gbl_gfx3DSvtDro0Cnt                         0x02A8
    #define     RA_Gbl_gfx3DLvtDro1Cnt                         0x02AC
    #define     RA_Gbl_INT_ID                                  0x02B0
    #define       bGbl_INT_ID_VALUE                            8
    #define     RA_Gbl_hdmirxFpllRefClk                        0x02B4
    #define     RA_Gbl_hdmirxTClk                              0x02B8
    #define     RA_Gbl_hdmirxMClk                              0x02BC
    #define     RA_Gbl_gethRgmiiClk                            0x02C0
    #define     RA_Gbl_pcieTestClk                             0x02C4
    #define     RA_Gbl_stickyResetN                            0x02C8
    #define       bGbl_stickyResetN_gethRgmiiMemRstn           1
    #define        Gbl_stickyResetN_gethRgmiiMemRstn_asserted               0x0
    #define        Gbl_stickyResetN_gethRgmiiMemRstn_deasserted              0x1
    #define       bGbl_stickyResetN_gethRgmiiRstn              1
    #define        Gbl_stickyResetN_gethRgmiiRstn_asserted                  0x0
    #define        Gbl_stickyResetN_gethRgmiiRstn_deasserted                0x1
    #define       bGbl_stickyResetN_cpuPllRstn                 1
    #define        Gbl_stickyResetN_cpuPllRstn_asserted                     0x0
    #define        Gbl_stickyResetN_cpuPllRstn_deasserted                   0x1
    #define       bGbl_stickyResetN_memPllRstn                 1
    #define        Gbl_stickyResetN_memPllRstn_asserted                     0x0
    #define        Gbl_stickyResetN_memPllRstn_deasserted                   0x1
    #define       bGbl_stickyResetN_sysPllRstn                 1
    #define        Gbl_stickyResetN_sysPllRstn_asserted                     0x0
    #define        Gbl_stickyResetN_sysPllRstn_deasserted                   0x1
    #define     RA_Gbl_gethRgmii_dll                           0x02CC
    #define       bGbl_gethRgmii_dll_tx_delay                  9
    #define       bGbl_gethRgmii_dll_rx_delay                  9
    #define     RA_Gbl_funcSel                                 0x02D0
    #define       bGbl_funcSel_pcie_sata_sel                   1
    #define       bGbl_funcSel_gmac_eth_sel                    1
    #define     RA_Gbl_efuse                                   0x02D4
    #define     RA_Gbl_chipCntl                                0x0300
    #define       bGbl_chipCntl_pcieDownMap                    1
    #define        Gbl_chipCntl_pcieDownMap_M512                            0x0
    #define        Gbl_chipCntl_pcieDownMap_M256                            0x1
    #define       bGbl_chipCntl_pcie_rc                        1
    #define        Gbl_chipCntl_pcie_rc_END_POINT                           0x0
    #define        Gbl_chipCntl_pcie_rc_ROOT_COMPLEX                        0x1
    #define     RA_Gbl_bootStrapEn                             0x0304
    #define       bGbl_bootStrapEn_pllPwrDownEn                1
    #define        Gbl_bootStrapEn_pllPwrDownEn_Disable                     0x0
    #define        Gbl_bootStrapEn_pllPwrDownEn_Enable                      0x1
    #define       bGbl_bootStrapEn_refClk12P5MEn               1
    #define        Gbl_bootStrapEn_refClk12P5MEn_Disable                    0x0
    #define        Gbl_bootStrapEn_refClk12P5MEn_Enable                     0x1
    #define     RA_Gbl_axiClkEn                                0x0308
    #define       bGbl_axiClkEn_avioAxiClkEn                   1
    #define        Gbl_axiClkEn_avioAxiClkEn_enable                         0x1
    #define        Gbl_axiClkEn_avioAxiClkEn_disable                        0x0
    #define     RA_Gbl_ahbClkEn                                0x030C
    #define       bGbl_ahbClkEn_avioAhbClkEn                   1
    #define        Gbl_ahbClkEn_avioAhbClkEn_enable                         0x1
    #define        Gbl_ahbClkEn_avioAhbClkEn_disable                        0x0
    #define     RA_Gbl_SPI1_SS0nCntl                           0x8000
    #define       bGbl_SPI1_SS0nCntl_PU_EN                     1
    #define       bGbl_SPI1_SS0nCntl_PD_EN                     1
    #define     RA_Gbl_SPI1_SS1nCntl                           0x8004
    #define       bGbl_SPI1_SS1nCntl_PU_EN                     1
    #define       bGbl_SPI1_SS1nCntl_PD_EN                     1
    #define     RA_Gbl_SPI1_SS2nCntl                           0x8008
    #define       bGbl_SPI1_SS2nCntl_PU_EN                     1
    #define       bGbl_SPI1_SS2nCntl_PD_EN                     1
    #define     RA_Gbl_SPI1_SCLKCntl                           0x800C
    #define       bGbl_SPI1_SCLKCntl_PU_EN                     1
    #define       bGbl_SPI1_SCLKCntl_PD_EN                     1
    #define     RA_Gbl_SPI1_SDOCntl                            0x8010
    #define       bGbl_SPI1_SDOCntl_PU_EN                      1
    #define       bGbl_SPI1_SDOCntl_PD_EN                      1
    #define     RA_Gbl_SPI1_SDICntl                            0x8014
    #define       bGbl_SPI1_SDICntl_PU_EN                      1
    #define       bGbl_SPI1_SDICntl_PD_EN                      1
    #define     RA_Gbl_URT0_RXDCntl                            0x8018
    #define       bGbl_URT0_RXDCntl_PU_EN                      1
    #define       bGbl_URT0_RXDCntl_PD_EN                      1
    #define     RA_Gbl_URT0_TXDCntl                            0x801C
    #define       bGbl_URT0_TXDCntl_PU_EN                      1
    #define       bGbl_URT0_TXDCntl_PD_EN                      1
    #define     RA_Gbl_DVIO0Cntl                               0x8020
    #define       bGbl_DVIO0Cntl_PU_EN                         1
    #define       bGbl_DVIO0Cntl_PD_EN                         1
    #define       bGbl_DVIO0Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO1Cntl                               0x8024
    #define       bGbl_DVIO1Cntl_PU_EN                         1
    #define       bGbl_DVIO1Cntl_PD_EN                         1
    #define       bGbl_DVIO1Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO2Cntl                               0x8028
    #define       bGbl_DVIO2Cntl_PU_EN                         1
    #define       bGbl_DVIO2Cntl_PD_EN                         1
    #define       bGbl_DVIO2Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO3Cntl                               0x802C
    #define       bGbl_DVIO3Cntl_PU_EN                         1
    #define       bGbl_DVIO3Cntl_PD_EN                         1
    #define       bGbl_DVIO3Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO4Cntl                               0x8030
    #define       bGbl_DVIO4Cntl_PU_EN                         1
    #define       bGbl_DVIO4Cntl_PD_EN                         1
    #define       bGbl_DVIO4Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO5Cntl                               0x8034
    #define       bGbl_DVIO5Cntl_PU_EN                         1
    #define       bGbl_DVIO5Cntl_PD_EN                         1
    #define       bGbl_DVIO5Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO6Cntl                               0x8038
    #define       bGbl_DVIO6Cntl_PU_EN                         1
    #define       bGbl_DVIO6Cntl_PD_EN                         1
    #define       bGbl_DVIO6Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO7Cntl                               0x803C
    #define       bGbl_DVIO7Cntl_PU_EN                         1
    #define       bGbl_DVIO7Cntl_PD_EN                         1
    #define       bGbl_DVIO7Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO8Cntl                               0x8040
    #define       bGbl_DVIO8Cntl_PU_EN                         1
    #define       bGbl_DVIO8Cntl_PD_EN                         1
    #define       bGbl_DVIO8Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO9Cntl                               0x8044
    #define       bGbl_DVIO9Cntl_PU_EN                         1
    #define       bGbl_DVIO9Cntl_PD_EN                         1
    #define       bGbl_DVIO9Cntl_SLP_DI                        1
    #define     RA_Gbl_DVIO10Cntl                              0x8048
    #define       bGbl_DVIO10Cntl_PU_EN                        1
    #define       bGbl_DVIO10Cntl_PD_EN                        1
    #define       bGbl_DVIO10Cntl_SLP_DI                       1
    #define     RA_Gbl_DVIO11Cntl                              0x804C
    #define       bGbl_DVIO11Cntl_PU_EN                        1
    #define       bGbl_DVIO11Cntl_PD_EN                        1
    #define       bGbl_DVIO11Cntl_SLP_DI                       1
    #define     RA_Gbl_DV0_CLKCntl                             0x8050
    #define       bGbl_DV0_CLKCntl_PU_EN                       1
    #define       bGbl_DV0_CLKCntl_PD_EN                       1
    #define       bGbl_DV0_CLKCntl_SLP_DI                      1
    #define     RA_Gbl_DV0_HSCntl                              0x8054
    #define       bGbl_DV0_HSCntl_PU_EN                        1
    #define       bGbl_DV0_HSCntl_PD_EN                        1
    #define       bGbl_DV0_HSCntl_SLP_DI                       1
    #define     RA_Gbl_DV0_VSCntl                              0x8058
    #define       bGbl_DV0_VSCntl_PU_EN                        1
    #define       bGbl_DV0_VSCntl_PD_EN                        1
    #define       bGbl_DV0_VSCntl_SLP_DI                       1
    #define     RA_Gbl_DV0_FIDCntl                             0x805C
    #define       bGbl_DV0_FIDCntl_PU_EN                       1
    #define       bGbl_DV0_FIDCntl_PD_EN                       1
    #define       bGbl_DV0_FIDCntl_SLP_DI                      1
    #define     RA_Gbl_I2S0_BCLKCntl                           0x8060
    #define       bGbl_I2S0_BCLKCntl_PU_EN                     1
    #define       bGbl_I2S0_BCLKCntl_PD_EN                     1
    #define       bGbl_I2S0_BCLKCntl_SLP_DI                    1
    #define     RA_Gbl_I2S0_LRCKCntl                           0x8064
    #define       bGbl_I2S0_LRCKCntl_PU_EN                     1
    #define       bGbl_I2S0_LRCKCntl_PD_EN                     1
    #define       bGbl_I2S0_LRCKCntl_SLP_DI                    1
    #define     RA_Gbl_I2S0_DO0Cntl                            0x8068
    #define       bGbl_I2S0_DO0Cntl_PU_EN                      1
    #define       bGbl_I2S0_DO0Cntl_PD_EN                      1
    #define       bGbl_I2S0_DO0Cntl_SLP_DI                     1
    #define     RA_Gbl_I2S0_DO1Cntl                            0x806C
    #define       bGbl_I2S0_DO1Cntl_PU_EN                      1
    #define       bGbl_I2S0_DO1Cntl_PD_EN                      1
    #define       bGbl_I2S0_DO1Cntl_SLP_DI                     1
    #define     RA_Gbl_I2S0_DO2Cntl                            0x8070
    #define       bGbl_I2S0_DO2Cntl_PU_EN                      1
    #define       bGbl_I2S0_DO2Cntl_PD_EN                      1
    #define       bGbl_I2S0_DO2Cntl_SLP_DI                     1
    #define     RA_Gbl_I2S0_DO3Cntl                            0x8074
    #define       bGbl_I2S0_DO3Cntl_PU_EN                      1
    #define       bGbl_I2S0_DO3Cntl_PD_EN                      1
    #define       bGbl_I2S0_DO3Cntl_SLP_DI                     1
    #define     RA_Gbl_SPDIFICntl                              0x8078
    #define       bGbl_SPDIFICntl_PU_EN                        1
    #define       bGbl_SPDIFICntl_PD_EN                        1
    #define       bGbl_SPDIFICntl_SLP_DI                       1
    #define     RA_Gbl_I2S1_LRCKCntl                           0x807C
    #define       bGbl_I2S1_LRCKCntl_PU_EN                     1
    #define       bGbl_I2S1_LRCKCntl_PD_EN                     1
    #define       bGbl_I2S1_LRCKCntl_SLP_DI                    1
    #define     RA_Gbl_I2S1_BCLKCntl                           0x8080
    #define       bGbl_I2S1_BCLKCntl_PU_EN                     1
    #define       bGbl_I2S1_BCLKCntl_PD_EN                     1
    #define       bGbl_I2S1_BCLKCntl_SLP_DI                    1
    #define     RA_Gbl_I2S1_DOCntl                             0x8084
    #define       bGbl_I2S1_DOCntl_PU_EN                       1
    #define       bGbl_I2S1_DOCntl_PD_EN                       1
    #define       bGbl_I2S1_DOCntl_SLP_DI                      1
    #define     RA_Gbl_I2S2_LRCKCntl                           0x8088
    #define       bGbl_I2S2_LRCKCntl_PU_EN                     1
    #define       bGbl_I2S2_LRCKCntl_PD_EN                     1
    #define       bGbl_I2S2_LRCKCntl_SLP_DI                    1
    #define     RA_Gbl_I2S2_BCLKCntl                           0x808C
    #define       bGbl_I2S2_BCLKCntl_PU_EN                     1
    #define       bGbl_I2S2_BCLKCntl_PD_EN                     1
    #define       bGbl_I2S2_BCLKCntl_SLP_DI                    1
    #define     RA_Gbl_I2S2_DI_0Cntl                           0x8090
    #define       bGbl_I2S2_DI_0Cntl_PU_EN                     1
    #define       bGbl_I2S2_DI_0Cntl_PD_EN                     1
    #define       bGbl_I2S2_DI_0Cntl_SLP_DI                    1
    #define     RA_Gbl_SPDIFOCntl                              0x8094
    #define       bGbl_SPDIFOCntl_PU_EN                        1
    #define       bGbl_SPDIFOCntl_PD_EN                        1
    #define       bGbl_SPDIFOCntl_SLP_DI                       1
    typedef struct SIE_Gbl {
    #define     w32Gbl_pinMux                                  {\
            UNSG32 upinMux_gp0                                 :  3;\
            UNSG32 upinMux_gp1                                 :  3;\
            UNSG32 upinMux_gp2                                 :  3;\
            UNSG32 upinMux_gp3                                 :  3;\
            UNSG32 upinMux_gp4                                 :  3;\
            UNSG32 upinMux_gp5                                 :  3;\
            UNSG32 upinMux_gp6                                 :  3;\
            UNSG32 upinMux_gp7                                 :  3;\
            UNSG32 upinMux_gp8                                 :  3;\
            UNSG32 upinMux_gp9                                 :  3;\
            UNSG32 upinMux_gp10                                :  2;\
          }
    union { UNSG32 u32Gbl_pinMux;
            struct w32Gbl_pinMux;
          };
    #define     w32Gbl_pinMux1                                 {\
            UNSG32 upinMux_gp11                                :  2;\
            UNSG32 upinMux_gp12                                :  3;\
            UNSG32 upinMux_gp13                                :  3;\
            UNSG32 upinMux_gp14                                :  1;\
            UNSG32 upinMux_gp15                                :  3;\
            UNSG32 upinMux_gp16                                :  3;\
            UNSG32 upinMux_gp17                                :  3;\
            UNSG32 upinMux_gp18                                :  2;\
            UNSG32 upinMux_gp19                                :  2;\
            UNSG32 upinMux_gp20                                :  2;\
            UNSG32 upinMux_gp21                                :  3;\
            UNSG32 upinMux_gp22                                :  3;\
            UNSG32 RSVDx4_b30                                  :  2;\
          }
    union { UNSG32 u32Gbl_pinMux1;
            struct w32Gbl_pinMux1;
          };
    #define     w32Gbl_pinMux2                                 {\
            UNSG32 upinMux_gp23                                :  3;\
            UNSG32 upinMux_gp24                                :  2;\
            UNSG32 upinMux_gp25                                :  2;\
            UNSG32 upinMux_gp26                                :  1;\
            UNSG32 upinMux_gp27                                :  2;\
            UNSG32 upinMux_gp28                                :  3;\
            UNSG32 upinMux_gp29                                :  3;\
            UNSG32 RSVDx8_b16                                  : 16;\
          }
    union { UNSG32 u32Gbl_pinMux2;
            struct w32Gbl_pinMux2;
          };
    #define     w32Gbl_bootStrap                               {\
            UNSG32 ubootStrap_softwareStrap                    :  7;\
            UNSG32 ubootStrap_bootSrc                          :  2;\
            UNSG32 ubootStrap_sysPllByps                       :  1;\
            UNSG32 ubootStrap_memPllByps                       :  1;\
            UNSG32 ubootStrap_cpuPllByps                       :  1;\
            UNSG32 ubootStrap_pllPwrDown                       :  1;\
            UNSG32 ubootStrap_refClk12P5M                      :  1;\
            UNSG32 ubootStrap_socJtagFromSM                    :  1;\
            UNSG32 ubootStrap_nandV18Enable                    :  1;\
            UNSG32 ubootStrap_spi1V18Enable                    :  1;\
            UNSG32 ubootStrap_nandV25Enable                    :  1;\
            UNSG32 ubootStrap_spi1V25Enable                    :  1;\
            UNSG32 ubootStrap_ENG_EN                           :  1;\
            UNSG32 RSVDxC_b20                                  : 12;\
          }
    union { UNSG32 u32Gbl_bootStrap;
            struct w32Gbl_bootStrap;
          };
    #define     w32Gbl_anaGrpCtl                               {\
            UNSG32 uanaGrpCtl_anaGrpPu                         :  1;\
            UNSG32 uanaGrpCtl_anaGrpBgSel                      :  2;\
            UNSG32 uanaGrpCtl_anaGrpPuXtl                      :  1;\
            UNSG32 uanaGrpCtl_anaGrpGainX2                     :  1;\
            UNSG32 uanaGrpCtl_anaGrpSelClkDigDiv1              :  2;\
            UNSG32 uanaGrpCtl_anaGrpSelClkDigDiv2              :  2;\
            UNSG32 uanaGrpCtl_anaGrpSelClkDigDiv3              :  2;\
            UNSG32 uanaGrpCtl_anaGrpSelClkDigDiv4              :  2;\
            UNSG32 uanaGrpCtl_anaGrpPuOsc                      :  1;\
            UNSG32 uanaGrpCtl_anaGrpSpeedOsc                   :  2;\
            UNSG32 uanaGrpCtl_anaGrpTestAna                    :  4;\
            UNSG32 RSVDx10_b20                                 : 12;\
          }
    union { UNSG32 u32Gbl_anaGrpCtl;
            struct w32Gbl_anaGrpCtl;
          };
    #define     w32Gbl_sysPllCtl                               {\
            UNSG32 usysPllCtl_sysPllPu                         :  1;\
            UNSG32 usysPllCtl_sysPllRfDiv                      :  5;\
            UNSG32 usysPllCtl_sysPllFbDiv                      :  9;\
            UNSG32 usysPllCtl_sysPllVddm                       :  2;\
            UNSG32 usysPllCtl_sysPllVddl                       :  4;\
            UNSG32 usysPllCtl_sysPllVregIVRef                  :  2;\
            UNSG32 usysPllCtl_sysPllIcp                        :  3;\
            UNSG32 usysPllCtl_sysPllKvco                       :  4;\
            UNSG32 usysPllCtl_sysPllCtune                      :  2;\
          }
    union { UNSG32 u32Gbl_sysPllCtl;
            struct w32Gbl_sysPllCtl;
          };
    #define     w32Gbl_sysPllCtl1                              {\
            UNSG32 usysPllCtl_sysPllVcoRng                     :  3;\
            UNSG32 usysPllCtl_sysPllVcoDivSelDiff              :  4;\
            UNSG32 usysPllCtl_sysPllVcoDivSelSe                :  4;\
            UNSG32 usysPllCtl_sysPllDiffClkEn                  :  1;\
            UNSG32 usysPllCtl_sysPllSelVcoDiff                 :  1;\
            UNSG32 usysPllCtl_sysPllSelVcoClkSe                :  1;\
            UNSG32 usysPllCtl_sysPllBypassFbDiv                :  1;\
            UNSG32 usysPllCtl_sysPllBypassEn                   :  1;\
            UNSG32 usysPllCtl_sysPllGateClkCtrl                :  1;\
            UNSG32 usysPllCtl_sysPllLineUpEn                   :  1;\
            UNSG32 usysPllCtl_sysPllIntpi                      :  4;\
            UNSG32 usysPllCtl_sysPllPiEn                       :  1;\
            UNSG32 usysPllCtl_sysPllSscClkEn                   :  1;\
            UNSG32 usysPllCtl_sysPllClkDetEn                   :  1;\
            UNSG32 usysPllCtl_sysPllFreqOffsetEn               :  1;\
            UNSG32 RSVDx18_b26                                 :  6;\
          }
    union { UNSG32 u32Gbl_sysPllCtl1;
            struct w32Gbl_sysPllCtl1;
          };
    #define     w32Gbl_sysPllCtl2                              {\
            UNSG32 usysPllCtl_sysPllFreqOffset                 : 17;\
            UNSG32 usysPllCtl_sysPllFreqOffsetModeSel          :  1;\
            UNSG32 usysPllCtl_sysPllFreqOffsetValid            :  1;\
            UNSG32 usysPllCtl_sysPllSscEn                      :  1;\
            UNSG32 usysPllCtl_sysPllSscmode                    :  1;\
            UNSG32 RSVDx1C_b21                                 : 11;\
          }
    union { UNSG32 u32Gbl_sysPllCtl2;
            struct w32Gbl_sysPllCtl2;
          };
    #define     w32Gbl_sysPllCtl3                              {\
            UNSG32 usysPllCtl_sysPllSscFdiv                    : 16;\
            UNSG32 usysPllCtl_sysPllSscRnge                    : 11;\
            UNSG32 usysPllCtl_sysPllSscResetExt                :  1;\
            UNSG32 usysPllCtl_sysPllTestMon                    :  4;\
          }
    union { UNSG32 u32Gbl_sysPllCtl3;
            struct w32Gbl_sysPllCtl3;
          };
    #define     w32Gbl_sysPllCtl4                              {\
            UNSG32 usysPllCtl_sysPllRsvdIn                     :  4;\
            UNSG32 usysPllCtl_sysPllExtRst                     :  1;\
            UNSG32 RSVDx24_b5                                  : 27;\
          }
    union { UNSG32 u32Gbl_sysPllCtl4;
            struct w32Gbl_sysPllCtl4;
          };
    #define     w32Gbl_memPllCtl                               {\
            UNSG32 umemPllCtl_memPllPu                         :  1;\
            UNSG32 umemPllCtl_memPllRfDiv                      :  5;\
            UNSG32 umemPllCtl_memPllFbDiv                      :  9;\
            UNSG32 umemPllCtl_memPllVddm                       :  2;\
            UNSG32 umemPllCtl_memPllVddl                       :  4;\
            UNSG32 umemPllCtl_memPllVregIVRef                  :  2;\
            UNSG32 umemPllCtl_memPllIcp                        :  3;\
            UNSG32 umemPllCtl_memPllKvco                       :  4;\
            UNSG32 umemPllCtl_memPllCtune                      :  2;\
          }
    union { UNSG32 u32Gbl_memPllCtl;
            struct w32Gbl_memPllCtl;
          };
    #define     w32Gbl_memPllCtl1                              {\
            UNSG32 umemPllCtl_memPllVcoRng                     :  3;\
            UNSG32 umemPllCtl_memPllVcoDivSelDiff              :  4;\
            UNSG32 umemPllCtl_memPllVcoDivSelSe                :  4;\
            UNSG32 umemPllCtl_memPllDiffClkEn                  :  1;\
            UNSG32 umemPllCtl_memPllSelVcoDiff                 :  1;\
            UNSG32 umemPllCtl_memPllSelVcoClkSe                :  1;\
            UNSG32 umemPllCtl_memPllBypassFbDiv                :  1;\
            UNSG32 umemPllCtl_memPllBypassEn                   :  1;\
            UNSG32 umemPllCtl_memPllGateClkCtrl                :  1;\
            UNSG32 umemPllCtl_memPllLineUpEn                   :  1;\
            UNSG32 umemPllCtl_memPllIntpi                      :  4;\
            UNSG32 umemPllCtl_memPllPiEn                       :  1;\
            UNSG32 umemPllCtl_memPllSscClkEn                   :  1;\
            UNSG32 umemPllCtl_memPllClkDetEn                   :  1;\
            UNSG32 umemPllCtl_memPllFreqOffsetEn               :  1;\
            UNSG32 RSVDx2C_b26                                 :  6;\
          }
    union { UNSG32 u32Gbl_memPllCtl1;
            struct w32Gbl_memPllCtl1;
          };
    #define     w32Gbl_memPllCtl2                              {\
            UNSG32 umemPllCtl_memPllFreqOffset                 : 17;\
            UNSG32 umemPllCtl_memPllFreqOffsetModeSel          :  1;\
            UNSG32 umemPllCtl_memPllFreqOffsetValid            :  1;\
            UNSG32 umemPllCtl_memPllSscEn                      :  1;\
            UNSG32 umemPllCtl_memPllSscmode                    :  1;\
            UNSG32 RSVDx30_b21                                 : 11;\
          }
    union { UNSG32 u32Gbl_memPllCtl2;
            struct w32Gbl_memPllCtl2;
          };
    #define     w32Gbl_memPllCtl3                              {\
            UNSG32 umemPllCtl_memPllSscFdiv                    : 16;\
            UNSG32 umemPllCtl_memPllSscRnge                    : 11;\
            UNSG32 umemPllCtl_memPllSscResetExt                :  1;\
            UNSG32 umemPllCtl_memPllTestMon                    :  4;\
          }
    union { UNSG32 u32Gbl_memPllCtl3;
            struct w32Gbl_memPllCtl3;
          };
    #define     w32Gbl_memPllCtl4                              {\
            UNSG32 umemPllCtl_memPllRsvdIn                     :  4;\
            UNSG32 umemPllCtl_memPllExtRst                     :  1;\
            UNSG32 RSVDx38_b5                                  : 27;\
          }
    union { UNSG32 u32Gbl_memPllCtl4;
            struct w32Gbl_memPllCtl4;
          };
    #define     w32Gbl_cpuPllCtl                               {\
            UNSG32 ucpuPllCtl_cpuPllPu                         :  1;\
            UNSG32 ucpuPllCtl_cpuPllRfDiv                      :  5;\
            UNSG32 ucpuPllCtl_cpuPllFbDiv                      :  9;\
            UNSG32 ucpuPllCtl_cpuPllVddm                       :  2;\
            UNSG32 ucpuPllCtl_cpuPllVddl                       :  4;\
            UNSG32 ucpuPllCtl_cpuPllVregIVRef                  :  2;\
            UNSG32 ucpuPllCtl_cpuPllIcp                        :  3;\
            UNSG32 ucpuPllCtl_cpuPllKvco                       :  4;\
            UNSG32 ucpuPllCtl_cpuPllCtune                      :  2;\
          }
    union { UNSG32 u32Gbl_cpuPllCtl;
            struct w32Gbl_cpuPllCtl;
          };
    #define     w32Gbl_cpuPllCtl1                              {\
            UNSG32 ucpuPllCtl_cpuPllVcoRng                     :  3;\
            UNSG32 ucpuPllCtl_cpuPllVcoDivSelDiff              :  4;\
            UNSG32 ucpuPllCtl_cpuPllVcoDivSelSe                :  4;\
            UNSG32 ucpuPllCtl_cpuPllDiffClkEn                  :  1;\
            UNSG32 ucpuPllCtl_cpuPllSelVcoDiff                 :  1;\
            UNSG32 ucpuPllCtl_cpuPllSelVcoClkSe                :  1;\
            UNSG32 ucpuPllCtl_cpuPllBypassFbDiv                :  1;\
            UNSG32 ucpuPllCtl_cpuPllBypassEn                   :  1;\
            UNSG32 ucpuPllCtl_cpuPllGateClkCtrl                :  1;\
            UNSG32 ucpuPllCtl_cpuPllLineUpEn                   :  1;\
            UNSG32 ucpuPllCtl_cpuPllIntpi                      :  4;\
            UNSG32 ucpuPllCtl_cpuPllPiEn                       :  1;\
            UNSG32 ucpuPllCtl_cpuPllSscClkEn                   :  1;\
            UNSG32 ucpuPllCtl_cpuPllClkDetEn                   :  1;\
            UNSG32 ucpuPllCtl_cpuPllFreqOffsetEn               :  1;\
            UNSG32 RSVDx40_b26                                 :  6;\
          }
    union { UNSG32 u32Gbl_cpuPllCtl1;
            struct w32Gbl_cpuPllCtl1;
          };
    #define     w32Gbl_cpuPllCtl2                              {\
            UNSG32 ucpuPllCtl_cpuPllFreqOffset                 : 17;\
            UNSG32 ucpuPllCtl_cpuPllFreqOffsetModeSel          :  1;\
            UNSG32 ucpuPllCtl_cpuPllFreqOffsetValid            :  1;\
            UNSG32 ucpuPllCtl_cpuPllSscEn                      :  1;\
            UNSG32 ucpuPllCtl_cpuPllSscmode                    :  1;\
            UNSG32 RSVDx44_b21                                 : 11;\
          }
    union { UNSG32 u32Gbl_cpuPllCtl2;
            struct w32Gbl_cpuPllCtl2;
          };
    #define     w32Gbl_cpuPllCtl3                              {\
            UNSG32 ucpuPllCtl_cpuPllSscFdiv                    : 16;\
            UNSG32 ucpuPllCtl_cpuPllSscRnge                    : 11;\
            UNSG32 ucpuPllCtl_cpuPllSscResetExt                :  1;\
            UNSG32 ucpuPllCtl_cpuPllTestMon                    :  4;\
          }
    union { UNSG32 u32Gbl_cpuPllCtl3;
            struct w32Gbl_cpuPllCtl3;
          };
    #define     w32Gbl_cpuPllCtl4                              {\
            UNSG32 ucpuPllCtl_cpuPllRsvdIn                     :  4;\
            UNSG32 ucpuPllCtl_cpuPllExtRst                     :  1;\
            UNSG32 RSVDx4C_b5                                  : 27;\
          }
    union { UNSG32 u32Gbl_cpuPllCtl4;
            struct w32Gbl_cpuPllCtl4;
          };
    #define     w32Gbl_avPllCtl                                {\
            UNSG32 uavPllCtl_avPllResetPll_A                   :  1;\
            UNSG32 uavPllCtl_avPllPu_A                         :  1;\
            UNSG32 uavPllCtl_avPllIntpi_A                      :  4;\
            UNSG32 uavPllCtl_avPllVddr1p45V_A                  :  2;\
            UNSG32 uavPllCtl_avPllVddr0p9V_A                   :  4;\
            UNSG32 uavPllCtl_avPllVthVcoCal_A                  :  2;\
            UNSG32 uavPllCtl_avPllKvcoExt_A                    :  3;\
            UNSG32 uavPllCtl_avPllKvcoExtEn_A                  :  1;\
            UNSG32 uavPllCtl_avPllV2iExt_A                     :  4;\
            UNSG32 uavPllCtl_avPllV2iExtEn_A                   :  1;\
            UNSG32 uavPllCtl_avPllSpeed_A                      :  3;\
            UNSG32 uavPllCtl_avPllClkDetEn_A                   :  1;\
            UNSG32 RSVDx50_b27                                 :  5;\
          }
    union { UNSG32 u32Gbl_avPllCtl;
            struct w32Gbl_avPllCtl;
          };
    #define     w32Gbl_avPllCtl1                               {\
            UNSG32 uavPllCtl_avPllRefDiv_A                     :  6;\
            UNSG32 uavPllCtl_avPllFbDiv_A                      :  8;\
            UNSG32 uavPllCtl_avPllIcp_A                        :  4;\
            UNSG32 uavPllCtl_avPllLoadCap_A                    :  1;\
            UNSG32 uavPllCtl_avPllPllCaliStart_A               :  1;\
            UNSG32 RSVDx54_b20                                 : 12;\
          }
    union { UNSG32 u32Gbl_avPllCtl1;
            struct w32Gbl_avPllCtl1;
          };
    #define     w32Gbl_avPllCtl2                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC1_A               : 19;\
            UNSG32 RSVDx58_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl2;
            struct w32Gbl_avPllCtl2;
          };
    #define     w32Gbl_avPllCtl3                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC2_A               : 19;\
            UNSG32 RSVDx5C_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl3;
            struct w32Gbl_avPllCtl3;
          };
    #define     w32Gbl_avPllCtl4                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC3_A               : 19;\
            UNSG32 RSVDx60_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl4;
            struct w32Gbl_avPllCtl4;
          };
    #define     w32Gbl_avPllCtl5                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC4_A               : 19;\
            UNSG32 RSVDx64_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl5;
            struct w32Gbl_avPllCtl5;
          };
    #define     w32Gbl_avPllCtl6                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC5_A               : 19;\
            UNSG32 RSVDx68_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl6;
            struct w32Gbl_avPllCtl6;
          };
    #define     w32Gbl_avPllCtl7                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC6_A               : 19;\
            UNSG32 RSVDx6C_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl7;
            struct w32Gbl_avPllCtl7;
          };
    #define     w32Gbl_avPllCtl8                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC7_A               : 19;\
            UNSG32 RSVDx70_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl8;
            struct w32Gbl_avPllCtl8;
          };
    #define     w32Gbl_avPllCtl9                               {\
            UNSG32 uavPllCtl_avPllFreqOffsetC8_A               : 19;\
            UNSG32 uavPllCtl_avPllFreqOffsetReadyC_A           :  8;\
            UNSG32 uavPllCtl_avPllReserveC1_A                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC2_A                  :  2;\
            UNSG32 RSVDx74_b31                                 :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl9;
            struct w32Gbl_avPllCtl9;
          };
    #define     w32Gbl_avPllCtl10                              {\
            UNSG32 uavPllCtl_avPllReserveC3_A                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC4_A                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC5_A                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC6_A                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC7_A                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC8_A                  :  2;\
            UNSG32 uavPllCtl_avPllEnLpC_A                      :  8;\
            UNSG32 uavPllCtl_avPllPuC_A                        :  7;\
            UNSG32 RSVDx78_b27                                 :  5;\
          }
    union { UNSG32 u32Gbl_avPllCtl10;
            struct w32Gbl_avPllCtl10;
          };
    #define     w32Gbl_avPllCtl11                              {\
            UNSG32 uavPllCtl_avPllResetC_A                     :  7;\
            UNSG32 uavPllCtl_avPllDivHdmiC1_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC2_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC3_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC4_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC5_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC6_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC7_A                  :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C1_A                   :  3;\
            UNSG32 RSVDx7C_b31                                 :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl11;
            struct w32Gbl_avPllCtl11;
          };
    #define     w32Gbl_avPllCtl12                              {\
            UNSG32 uavPllCtl_avPllDivAv1C2_A                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C3_A                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C4_A                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C5_A                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C6_A                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C7_A                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv2C1_A                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C2_A                   :  7;\
          }
    union { UNSG32 u32Gbl_avPllCtl12;
            struct w32Gbl_avPllCtl12;
          };
    #define     w32Gbl_avPllCtl13                              {\
            UNSG32 uavPllCtl_avPllDivAv2C3_A                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C4_A                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C5_A                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C6_A                   :  7;\
            UNSG32 RSVDx84_b28                                 :  4;\
          }
    union { UNSG32 u32Gbl_avPllCtl13;
            struct w32Gbl_avPllCtl13;
          };
    #define     w32Gbl_avPllCtl14                              {\
            UNSG32 uavPllCtl_avPllDivAv2C7_A                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv3C1_A                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C2_A                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C3_A                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C4_A                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C5_A                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C6_A                   :  4;\
            UNSG32 RSVDx88_b31                                 :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl14;
            struct w32Gbl_avPllCtl14;
          };
    #define     w32Gbl_avPllCtl15                              {\
            UNSG32 uavPllCtl_avPllDivAv3C7_A                   :  4;\
            UNSG32 uavPllCtl_avPllPSync1C1_A                   : 17;\
            UNSG32 RSVDx8C_b21                                 : 11;\
          }
    union { UNSG32 u32Gbl_avPllCtl15;
            struct w32Gbl_avPllCtl15;
          };
    #define     w32Gbl_avPllCtl16                              {\
            UNSG32 uavPllCtl_avPllPSync1C2_A                   : 17;\
            UNSG32 RSVDx90_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl16;
            struct w32Gbl_avPllCtl16;
          };
    #define     w32Gbl_avPllCtl17                              {\
            UNSG32 uavPllCtl_avPllPSync1C3_A                   : 17;\
            UNSG32 RSVDx94_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl17;
            struct w32Gbl_avPllCtl17;
          };
    #define     w32Gbl_avPllCtl18                              {\
            UNSG32 uavPllCtl_avPllPSync1C4_A                   : 17;\
            UNSG32 RSVDx98_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl18;
            struct w32Gbl_avPllCtl18;
          };
    #define     w32Gbl_avPllCtl19                              {\
            UNSG32 uavPllCtl_avPllPSync1C5_A                   : 17;\
            UNSG32 RSVDx9C_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl19;
            struct w32Gbl_avPllCtl19;
          };
    #define     w32Gbl_avPllCtl20                              {\
            UNSG32 uavPllCtl_avPllPSync1C6_A                   : 17;\
            UNSG32 RSVDxA0_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl20;
            struct w32Gbl_avPllCtl20;
          };
    #define     w32Gbl_avPllCtl21                              {\
            UNSG32 uavPllCtl_avPllPSync1C7_A                   : 17;\
            UNSG32 RSVDxA4_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl21;
            struct w32Gbl_avPllCtl21;
          };
    #define     w32Gbl_avPllCtl22                              {\
            UNSG32 uavPllCtl_avPllPSync1C8_A                   : 17;\
            UNSG32 RSVDxA8_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl22;
            struct w32Gbl_avPllCtl22;
          };
    #define     w32Gbl_avPllCtl23                              {\
            UNSG32 uavPllCtl_avPllPSync2C1_A                   : 17;\
            UNSG32 RSVDxAC_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl23;
            struct w32Gbl_avPllCtl23;
          };
    #define     w32Gbl_avPllCtl24                              {\
            UNSG32 uavPllCtl_avPllPSync2C2_A                   : 17;\
            UNSG32 RSVDxB0_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl24;
            struct w32Gbl_avPllCtl24;
          };
    #define     w32Gbl_avPllCtl25                              {\
            UNSG32 uavPllCtl_avPllPSync2C3_A                   : 17;\
            UNSG32 RSVDxB4_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl25;
            struct w32Gbl_avPllCtl25;
          };
    #define     w32Gbl_avPllCtl26                              {\
            UNSG32 uavPllCtl_avPllPSync2C4_A                   : 17;\
            UNSG32 RSVDxB8_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl26;
            struct w32Gbl_avPllCtl26;
          };
    #define     w32Gbl_avPllCtl27                              {\
            UNSG32 uavPllCtl_avPllPSync2C5_A                   : 17;\
            UNSG32 RSVDxBC_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl27;
            struct w32Gbl_avPllCtl27;
          };
    #define     w32Gbl_avPllCtl28                              {\
            UNSG32 uavPllCtl_avPllPSync2C6_A                   : 17;\
            UNSG32 RSVDxC0_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl28;
            struct w32Gbl_avPllCtl28;
          };
    #define     w32Gbl_avPllCtl29                              {\
            UNSG32 uavPllCtl_avPllPSync2C7_A                   : 17;\
            UNSG32 RSVDxC4_b17                                 : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl29;
            struct w32Gbl_avPllCtl29;
          };
    #define     w32Gbl_avPllCtl30                              {\
            UNSG32 uavPllCtl_avPllPSync2C8_A                   : 17;\
            UNSG32 uavPllCtl_avPllEnDpllC_A                    :  8;\
            UNSG32 uavPllCtl_avPllMasterSlaveB_A               :  1;\
            UNSG32 uavPllCtl_avPllTestAna_A                    :  6;\
          }
    union { UNSG32 u32Gbl_avPllCtl30;
            struct w32Gbl_avPllCtl30;
          };
    #define     w32Gbl_avPllCtl31                              {\
            UNSG32 uavPllCtl_avPllReservePll_A                 :  4;\
            UNSG32 uavPllCtl_avPllResetPll_B                   :  1;\
            UNSG32 uavPllCtl_avPllPu_B                         :  1;\
            UNSG32 uavPllCtl_avPllIntpi_B                      :  4;\
            UNSG32 uavPllCtl_avPllVddr1p45V_B                  :  2;\
            UNSG32 uavPllCtl_avPllVddr0p9V_B                   :  4;\
            UNSG32 uavPllCtl_avPllVthVcoCal_B                  :  2;\
            UNSG32 uavPllCtl_avPllKvcoExt_B                    :  3;\
            UNSG32 uavPllCtl_avPllKvcoExtEn_B                  :  1;\
            UNSG32 uavPllCtl_avPllV2iExt_B                     :  4;\
            UNSG32 uavPllCtl_avPllV2iExtEn_B                   :  1;\
            UNSG32 uavPllCtl_avPllSpeed_B                      :  3;\
            UNSG32 uavPllCtl_avPllClkDetEn_B                   :  1;\
            UNSG32 RSVDxCC_b31                                 :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl31;
            struct w32Gbl_avPllCtl31;
          };
    #define     w32Gbl_avPllCtl32                              {\
            UNSG32 uavPllCtl_avPllRefDiv_B                     :  6;\
            UNSG32 uavPllCtl_avPllFbDiv_B                      :  8;\
            UNSG32 uavPllCtl_avPllIcp_B                        :  4;\
            UNSG32 uavPllCtl_avPllLoadCap_B                    :  1;\
            UNSG32 uavPllCtl_avPllPllCaliStart_B               :  1;\
            UNSG32 RSVDxD0_b20                                 : 12;\
          }
    union { UNSG32 u32Gbl_avPllCtl32;
            struct w32Gbl_avPllCtl32;
          };
    #define     w32Gbl_avPllCtl33                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC1_B               : 19;\
            UNSG32 RSVDxD4_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl33;
            struct w32Gbl_avPllCtl33;
          };
    #define     w32Gbl_avPllCtl34                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC2_B               : 19;\
            UNSG32 RSVDxD8_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl34;
            struct w32Gbl_avPllCtl34;
          };
    #define     w32Gbl_avPllCtl35                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC3_B               : 19;\
            UNSG32 RSVDxDC_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl35;
            struct w32Gbl_avPllCtl35;
          };
    #define     w32Gbl_avPllCtl36                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC4_B               : 19;\
            UNSG32 RSVDxE0_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl36;
            struct w32Gbl_avPllCtl36;
          };
    #define     w32Gbl_avPllCtl37                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC5_B               : 19;\
            UNSG32 RSVDxE4_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl37;
            struct w32Gbl_avPllCtl37;
          };
    #define     w32Gbl_avPllCtl38                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC6_B               : 19;\
            UNSG32 RSVDxE8_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl38;
            struct w32Gbl_avPllCtl38;
          };
    #define     w32Gbl_avPllCtl39                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC7_B               : 19;\
            UNSG32 RSVDxEC_b19                                 : 13;\
          }
    union { UNSG32 u32Gbl_avPllCtl39;
            struct w32Gbl_avPllCtl39;
          };
    #define     w32Gbl_avPllCtl40                              {\
            UNSG32 uavPllCtl_avPllFreqOffsetC8_B               : 19;\
            UNSG32 uavPllCtl_avPllFreqOffsetReadyC_B           :  8;\
            UNSG32 uavPllCtl_avPllReserveC1_B                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC2_B                  :  2;\
            UNSG32 RSVDxF0_b31                                 :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl40;
            struct w32Gbl_avPllCtl40;
          };
    #define     w32Gbl_avPllCtl41                              {\
            UNSG32 uavPllCtl_avPllReserveC3_B                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC4_B                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC5_B                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC6_B                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC7_B                  :  2;\
            UNSG32 uavPllCtl_avPllReserveC8_B                  :  2;\
            UNSG32 uavPllCtl_avPllEnLpC_B                      :  8;\
            UNSG32 uavPllCtl_avPllPuC_B                        :  7;\
            UNSG32 RSVDxF4_b27                                 :  5;\
          }
    union { UNSG32 u32Gbl_avPllCtl41;
            struct w32Gbl_avPllCtl41;
          };
    #define     w32Gbl_avPllCtl42                              {\
            UNSG32 uavPllCtl_avPllResetC_B                     :  7;\
            UNSG32 uavPllCtl_avPllDivHdmiC1_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC2_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC3_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC4_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC5_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC6_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivHdmiC7_B                  :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C1_B                   :  3;\
            UNSG32 RSVDxF8_b31                                 :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl42;
            struct w32Gbl_avPllCtl42;
          };
    #define     w32Gbl_avPllCtl43                              {\
            UNSG32 uavPllCtl_avPllDivAv1C2_B                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C3_B                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C4_B                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C5_B                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C6_B                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv1C7_B                   :  3;\
            UNSG32 uavPllCtl_avPllDivAv2C1_B                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C2_B                   :  7;\
          }
    union { UNSG32 u32Gbl_avPllCtl43;
            struct w32Gbl_avPllCtl43;
          };
    #define     w32Gbl_avPllCtl44                              {\
            UNSG32 uavPllCtl_avPllDivAv2C3_B                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C4_B                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C5_B                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv2C6_B                   :  7;\
            UNSG32 RSVDx100_b28                                :  4;\
          }
    union { UNSG32 u32Gbl_avPllCtl44;
            struct w32Gbl_avPllCtl44;
          };
    #define     w32Gbl_avPllCtl45                              {\
            UNSG32 uavPllCtl_avPllDivAv2C7_B                   :  7;\
            UNSG32 uavPllCtl_avPllDivAv3C1_B                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C2_B                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C3_B                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C4_B                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C5_B                   :  4;\
            UNSG32 uavPllCtl_avPllDivAv3C6_B                   :  4;\
            UNSG32 RSVDx104_b31                                :  1;\
          }
    union { UNSG32 u32Gbl_avPllCtl45;
            struct w32Gbl_avPllCtl45;
          };
    #define     w32Gbl_avPllCtl46                              {\
            UNSG32 uavPllCtl_avPllDivAv3C7_B                   :  4;\
            UNSG32 uavPllCtl_avPllPSync1C1_B                   : 17;\
            UNSG32 RSVDx108_b21                                : 11;\
          }
    union { UNSG32 u32Gbl_avPllCtl46;
            struct w32Gbl_avPllCtl46;
          };
    #define     w32Gbl_avPllCtl47                              {\
            UNSG32 uavPllCtl_avPllPSync1C2_B                   : 17;\
            UNSG32 RSVDx10C_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl47;
            struct w32Gbl_avPllCtl47;
          };
    #define     w32Gbl_avPllCtl48                              {\
            UNSG32 uavPllCtl_avPllPSync1C3_B                   : 17;\
            UNSG32 RSVDx110_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl48;
            struct w32Gbl_avPllCtl48;
          };
    #define     w32Gbl_avPllCtl49                              {\
            UNSG32 uavPllCtl_avPllPSync1C4_B                   : 17;\
            UNSG32 RSVDx114_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl49;
            struct w32Gbl_avPllCtl49;
          };
    #define     w32Gbl_avPllCtl50                              {\
            UNSG32 uavPllCtl_avPllPSync1C5_B                   : 17;\
            UNSG32 RSVDx118_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl50;
            struct w32Gbl_avPllCtl50;
          };
    #define     w32Gbl_avPllCtl51                              {\
            UNSG32 uavPllCtl_avPllPSync1C6_B                   : 17;\
            UNSG32 RSVDx11C_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl51;
            struct w32Gbl_avPllCtl51;
          };
    #define     w32Gbl_avPllCtl52                              {\
            UNSG32 uavPllCtl_avPllPSync1C7_B                   : 17;\
            UNSG32 RSVDx120_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl52;
            struct w32Gbl_avPllCtl52;
          };
    #define     w32Gbl_avPllCtl53                              {\
            UNSG32 uavPllCtl_avPllPSync1C8_B                   : 17;\
            UNSG32 RSVDx124_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl53;
            struct w32Gbl_avPllCtl53;
          };
    #define     w32Gbl_avPllCtl54                              {\
            UNSG32 uavPllCtl_avPllPSync2C1_B                   : 17;\
            UNSG32 RSVDx128_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl54;
            struct w32Gbl_avPllCtl54;
          };
    #define     w32Gbl_avPllCtl55                              {\
            UNSG32 uavPllCtl_avPllPSync2C2_B                   : 17;\
            UNSG32 RSVDx12C_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl55;
            struct w32Gbl_avPllCtl55;
          };
    #define     w32Gbl_avPllCtl56                              {\
            UNSG32 uavPllCtl_avPllPSync2C3_B                   : 17;\
            UNSG32 RSVDx130_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl56;
            struct w32Gbl_avPllCtl56;
          };
    #define     w32Gbl_avPllCtl57                              {\
            UNSG32 uavPllCtl_avPllPSync2C4_B                   : 17;\
            UNSG32 RSVDx134_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl57;
            struct w32Gbl_avPllCtl57;
          };
    #define     w32Gbl_avPllCtl58                              {\
            UNSG32 uavPllCtl_avPllPSync2C5_B                   : 17;\
            UNSG32 RSVDx138_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl58;
            struct w32Gbl_avPllCtl58;
          };
    #define     w32Gbl_avPllCtl59                              {\
            UNSG32 uavPllCtl_avPllPSync2C6_B                   : 17;\
            UNSG32 RSVDx13C_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl59;
            struct w32Gbl_avPllCtl59;
          };
    #define     w32Gbl_avPllCtl60                              {\
            UNSG32 uavPllCtl_avPllPSync2C7_B                   : 17;\
            UNSG32 RSVDx140_b17                                : 15;\
          }
    union { UNSG32 u32Gbl_avPllCtl60;
            struct w32Gbl_avPllCtl60;
          };
    #define     w32Gbl_avPllCtl61                              {\
            UNSG32 uavPllCtl_avPllPSync2C8_B                   : 17;\
            UNSG32 uavPllCtl_avPllEnDpllC_B                    :  8;\
            UNSG32 uavPllCtl_avPllMasterSlaveB_B               :  1;\
            UNSG32 uavPllCtl_avPllTestAna_B                    :  6;\
          }
    union { UNSG32 u32Gbl_avPllCtl61;
            struct w32Gbl_avPllCtl61;
          };
    #define     w32Gbl_avPllCtl62                              {\
            UNSG32 uavPllCtl_avPllReservePll_B                 :  4;\
            UNSG32 RSVDx148_b4                                 : 28;\
          }
    union { UNSG32 u32Gbl_avPllCtl62;
            struct w32Gbl_avPllCtl62;
          };
    #define     w32Gbl_pllStatus                               {\
            UNSG32 upllStatus_sysPllLock                       :  1;\
            UNSG32 upllStatus_memPllLock                       :  1;\
            UNSG32 upllStatus_cpu1PllLock                      :  1;\
            UNSG32 upllStatus_avPllALock                       :  1;\
            UNSG32 upllStatus_avPllAKvcoOut                    :  3;\
            UNSG32 upllStatus_avPllACaliDone                   :  1;\
            UNSG32 upllStatus_avPllBLock                       :  1;\
            UNSG32 upllStatus_avPllBKvcoOut                    :  3;\
            UNSG32 upllStatus_avPllBCaliDone                   :  1;\
            UNSG32 upllStatus_cpuPllResOut                     :  4;\
            UNSG32 upllStatus_memPllResOut                     :  4;\
            UNSG32 upllStatus_sysPllResOut                     :  4;\
            UNSG32 RSVDx14C_b25                                :  7;\
          }
    union { UNSG32 u32Gbl_pllStatus;
            struct w32Gbl_pllStatus;
          };
    #define     w32Gbl_clkEnable                               {\
            UNSG32 uclkEnable_sysClkEn                         :  1;\
            UNSG32 uclkEnable_cfgClkEn                         :  1;\
            UNSG32 uclkEnable_pCubeClkEn                       :  1;\
            UNSG32 uclkEnable_vScopeClkEn                      :  1;\
            UNSG32 uclkEnable_gfxClkEn                         :  1;\
            UNSG32 uclkEnable_zspClkEn                         :  1;\
            UNSG32 uclkEnable_perifClkEn                       :  1;\
            UNSG32 uclkEnable_gethCoreClkEn                    :  1;\
            UNSG32 uclkEnable_geth1CoreClkEn                   :  1;\
            UNSG32 uclkEnable_sataCoreClkEn                    :  1;\
            UNSG32 uclkEnable_ahbApbCoreClkEn                  :  1;\
            UNSG32 uclkEnable_usb0CoreClkEn                    :  1;\
            UNSG32 uclkEnable_usb1CoreClkEn                    :  1;\
            UNSG32 uclkEnable_pBridgeCoreClkEn                 :  1;\
            UNSG32 uclkEnable_sdioCoreClkEn                    :  1;\
            UNSG32 uclkEnable_sdio1CoreClkEn                   :  1;\
            UNSG32 uclkEnable_drmFigoClkEn                     :  1;\
            UNSG32 uclkEnable_nfcCoreClkEn                     :  1;\
            UNSG32 uclkEnable_nfcEccClkEn                      :  1;\
            UNSG32 uclkEnable_smemcCoreClkEn                   :  1;\
            UNSG32 uclkEnable_appClkEn                         :  1;\
            UNSG32 uclkEnable_vppSysClkEn                      :  1;\
            UNSG32 uclkEnable_audio0ClkEn                      :  1;\
            UNSG32 uclkEnable_audio1ClkEn                      :  1;\
            UNSG32 uclkEnable_audio2ClkEn                      :  1;\
            UNSG32 uclkEnable_audio3ClkEn                      :  1;\
            UNSG32 uclkEnable_audioHdClkEn                     :  1;\
            UNSG32 uclkEnable_video0ClkEn                      :  1;\
            UNSG32 uclkEnable_video1ClkEn                      :  1;\
            UNSG32 uclkEnable_video2ClkEn                      :  1;\
            UNSG32 uclkEnable_PEX_mx_refclk_off                :  1;\
            UNSG32 RSVDx150_b31                                :  1;\
          }
    union { UNSG32 u32Gbl_clkEnable;
            struct w32Gbl_clkEnable;
          };
    #define     w32Gbl_clkSelect                               {\
            UNSG32 uclkSelect_sysClkPllSel                     :  3;\
            UNSG32 uclkSelect_sysClkSel                        :  3;\
            UNSG32 uclkSelect_cpu0ClkPllSel                    :  3;\
            UNSG32 uclkSelect_cpu0ClkSel                       :  3;\
            UNSG32 uclkSelect_cpu1ClkPllSel                    :  2;\
            UNSG32 uclkSelect_cpu1ClkSel                       :  3;\
            UNSG32 uclkSelect_drmFigoClkPllSel                 :  3;\
            UNSG32 uclkSelect_drmFigoClkSel                    :  3;\
            UNSG32 uclkSelect_cfgClkPllSel                     :  3;\
            UNSG32 uclkSelect_cfgClkSel                        :  3;\
            UNSG32 uclkSelect_gfxClkPllSel                     :  3;\
          }
    union { UNSG32 u32Gbl_clkSelect;
            struct w32Gbl_clkSelect;
          };
    #define     w32Gbl_clkSelect1                              {\
            UNSG32 uclkSelect_gfxClkSel                        :  3;\
            UNSG32 uclkSelect_zspClkPllSel                     :  3;\
            UNSG32 uclkSelect_zspClkSel                        :  3;\
            UNSG32 uclkSelect_perifClkPllSel                   :  3;\
            UNSG32 uclkSelect_perifClkSel                      :  3;\
            UNSG32 uclkSelect_pCubeClkPllSel                   :  3;\
            UNSG32 uclkSelect_pCubeClkSel                      :  3;\
            UNSG32 uclkSelect_vScopeClkPllSel                  :  3;\
            UNSG32 uclkSelect_vScopeClkSel                     :  3;\
            UNSG32 uclkSelect_nfcEccClkPllSel                  :  3;\
            UNSG32 RSVDx158_b30                                :  2;\
          }
    union { UNSG32 u32Gbl_clkSelect1;
            struct w32Gbl_clkSelect1;
          };
    #define     w32Gbl_clkSelect2                              {\
            UNSG32 uclkSelect_nfcEccClkSel                     :  3;\
            UNSG32 uclkSelect_vppSysClkPllSel                  :  3;\
            UNSG32 uclkSelect_vppSysClkSel                     :  3;\
            UNSG32 uclkSelect_appClkPllSel                     :  3;\
            UNSG32 uclkSelect_appClkSel                        :  3;\
            UNSG32 uclkSelect_audioFastExtClkSel               :  1;\
            UNSG32 uclkSelect_audioFastClkSel                  :  1;\
            UNSG32 uclkSelect_audio0ClkSel                     :  3;\
            UNSG32 uclkSelect_audio2ClkSel                     :  3;\
            UNSG32 uclkSelect_audio3ClkSel                     :  3;\
            UNSG32 uclkSelect_audioHdExtClkSel                 :  1;\
            UNSG32 uclkSelect_audioHdClkSel                    :  1;\
            UNSG32 uclkSelect_audio1ExtClkSel                  :  1;\
            UNSG32 uclkSelect_audio1ClkPllSel                  :  1;\
            UNSG32 uclkSelect_audio1SrcClkSel                  :  1;\
            UNSG32 RSVDx15C_b31                                :  1;\
          }
    union { UNSG32 u32Gbl_clkSelect2;
            struct w32Gbl_clkSelect2;
          };
    #define     w32Gbl_clkSelect3                              {\
            UNSG32 uclkSelect_audio1ClkSel                     :  3;\
            UNSG32 uclkSelect_video0ExtClkSel                  :  1;\
            UNSG32 uclkSelect_video0ClkSel                     :  1;\
            UNSG32 uclkSelect_video1ExtClkSel                  :  1;\
            UNSG32 uclkSelect_video1ClkSel                     :  1;\
            UNSG32 uclkSelect_video1ClkPllSel                  :  1;\
            UNSG32 uclkSelect_video2ExtClkSel                  :  1;\
            UNSG32 uclkSelect_video2ClkSel                     :  1;\
            UNSG32 uclkSelect_video2ClkPllSel                  :  1;\
            UNSG32 RSVDx160_b11                                : 21;\
          }
    union { UNSG32 u32Gbl_clkSelect3;
            struct w32Gbl_clkSelect3;
          };
    #define     w32Gbl_ClkSwitch                               {\
            UNSG32 uClkSwitch_sysPLLSWBypass                   :  1;\
            UNSG32 uClkSwitch_memPLLSWBypass                   :  1;\
            UNSG32 uClkSwitch_cpu1PLLSWBypass                  :  1;\
            UNSG32 uClkSwitch_sysClkPllSwitch                  :  1;\
            UNSG32 uClkSwitch_sysClkSwitch                     :  1;\
            UNSG32 uClkSwitch_sysClkD3Switch                   :  1;\
            UNSG32 uClkSwitch_cpu0ClkPllSwitch                 :  1;\
            UNSG32 uClkSwitch_cpu0ClkSwitch                    :  1;\
            UNSG32 uClkSwitch_cpu0ClkD3Switch                  :  1;\
            UNSG32 uClkSwitch_cpu1ClkPllSwitch                 :  1;\
            UNSG32 uClkSwitch_cpu1ClkSwitch                    :  1;\
            UNSG32 uClkSwitch_cpu1ClkD3Switch                  :  1;\
            UNSG32 uClkSwitch_drmFigoClkPllSwitch              :  1;\
            UNSG32 uClkSwitch_drmFigoClkSwitch                 :  1;\
            UNSG32 uClkSwitch_drmFigoClkD3Switch               :  1;\
            UNSG32 uClkSwitch_cfgClkPllSwitch                  :  1;\
            UNSG32 uClkSwitch_cfgClkSwitch                     :  1;\
            UNSG32 uClkSwitch_cfgClkD3Switch                   :  1;\
            UNSG32 uClkSwitch_gfxClkPllSwitch                  :  1;\
            UNSG32 uClkSwitch_gfxClkSwitch                     :  1;\
            UNSG32 uClkSwitch_gfxClkD3Switch                   :  1;\
            UNSG32 uClkSwitch_zspClkPllSwitch                  :  1;\
            UNSG32 uClkSwitch_zspClkSwitch                     :  1;\
            UNSG32 uClkSwitch_zspClkD3Switch                   :  1;\
            UNSG32 uClkSwitch_perifClkPllSwitch                :  1;\
            UNSG32 uClkSwitch_perifClkSwitch                   :  1;\
            UNSG32 uClkSwitch_perifClkD3Switch                 :  1;\
            UNSG32 uClkSwitch_pCubeClkPllSwitch                :  1;\
            UNSG32 uClkSwitch_pCubeClkSwitch                   :  1;\
            UNSG32 uClkSwitch_pCubeClkD3Switch                 :  1;\
            UNSG32 uClkSwitch_vScopeClkPllSwitch               :  1;\
            UNSG32 uClkSwitch_vScopeClkSwitch                  :  1;\
          }
    union { UNSG32 u32Gbl_ClkSwitch;
            struct w32Gbl_ClkSwitch;
          };
    #define     w32Gbl_ClkSwitch1                              {\
            UNSG32 uClkSwitch_vScopeClkD3Switch                :  1;\
            UNSG32 uClkSwitch_nfcEccClkPllSwitch               :  1;\
            UNSG32 uClkSwitch_nfcEccClkSwitch                  :  1;\
            UNSG32 uClkSwitch_nfcEccClkD3Switch                :  1;\
            UNSG32 uClkSwitch_vppSysClkPllSwitch               :  1;\
            UNSG32 uClkSwitch_vppSysClkSwitch                  :  1;\
            UNSG32 uClkSwitch_vppSysClkD3Switch                :  1;\
            UNSG32 uClkSwitch_appClkPllSwitch                  :  1;\
            UNSG32 uClkSwitch_appClkSwitch                     :  1;\
            UNSG32 uClkSwitch_appClkD3Switch                   :  1;\
            UNSG32 uClkSwitch_audio0ClkSwitch                  :  1;\
            UNSG32 uClkSwitch_audio0ClkD3Switch                :  1;\
            UNSG32 uClkSwitch_audio1ClkSwitch                  :  1;\
            UNSG32 uClkSwitch_audio1ClkD3Switch                :  1;\
            UNSG32 uClkSwitch_audio2ClkSwitch                  :  1;\
            UNSG32 uClkSwitch_audio2ClkD3Switch                :  1;\
            UNSG32 uClkSwitch_audio3ClkSwitch                  :  1;\
            UNSG32 uClkSwitch_audio3ClkD3Switch                :  1;\
            UNSG32 RSVDx168_b18                                : 14;\
          }
    union { UNSG32 u32Gbl_ClkSwitch1;
            struct w32Gbl_ClkSwitch1;
          };
    #define     w32Gbl_PadSelect                               {\
            UNSG32 uPadSelect_GBL_PDB                          :  1;\
            UNSG32 uPadSelect_NAND_PDB                         :  1;\
            UNSG32 uPadSelect_SD0_PDB                          :  1;\
            UNSG32 uPadSelect_SD1_PDB                          :  1;\
            UNSG32 uPadSelect_SPI_PDB                          :  1;\
            UNSG32 uPadSelect_CLK0_V18EN                       :  1;\
            UNSG32 uPadSelect_DVIO0_V18EN                      :  1;\
            UNSG32 uPadSelect_GBL_V18EN                        :  1;\
            UNSG32 uPadSelect_SPI0_V18EN                       :  1;\
            UNSG32 uPadSelect_SD0_V18EN                        :  1;\
            UNSG32 uPadSelect_SD10_V18EN                       :  1;\
            UNSG32 uPadSelect_CLK0_V25EN                       :  1;\
            UNSG32 uPadSelect_DVIO0_V25EN                      :  1;\
            UNSG32 uPadSelect_TS0_V25EN                        :  1;\
            UNSG32 uPadSelect_SPI0_V25EN                       :  1;\
            UNSG32 uPadSelect_U6_V25EN                         :  1;\
            UNSG32 uPadSelect_U7_V25EN                         :  1;\
            UNSG32 uPadSelect_U8_V25EN                         :  1;\
            UNSG32 uPadSelect_W14_V25EN                        :  1;\
            UNSG32 uPadSelect_DVU0_V25EN                       :  1;\
            UNSG32 uPadSelect_GBL_V25EN                        :  1;\
            UNSG32 uPadSelect_SD0_V25EN                        :  1;\
            UNSG32 uPadSelect_DVIO_OEN                         :  1;\
            UNSG32 uPadSelect_CLK0_ZN                          :  3;\
            UNSG32 uPadSelect_CLK0_ZP                          :  3;\
            UNSG32 uPadSelect_DVIO0_ZN                         :  3;\
          }
    union { UNSG32 u32Gbl_PadSelect;
            struct w32Gbl_PadSelect;
          };
    #define     w32Gbl_PadSelect1                              {\
            UNSG32 uPadSelect_DVIO0_ZP                         :  3;\
            UNSG32 uPadSelect_ND0_ZN                           :  4;\
            UNSG32 uPadSelect_ND0_ZP                           :  4;\
            UNSG32 uPadSelect_GBL_ZN                           :  4;\
            UNSG32 uPadSelect_GBL_ZP                           :  4;\
            UNSG32 uPadSelect_SPI0_ZN                          :  4;\
            UNSG32 uPadSelect_SPI0_ZP                          :  4;\
            UNSG32 uPadSelect_SD0_ZN                           :  4;\
            UNSG32 RSVDx170_b31                                :  1;\
          }
    union { UNSG32 u32Gbl_PadSelect1;
            struct w32Gbl_PadSelect1;
          };
    #define     w32Gbl_PadSelect2                              {\
            UNSG32 uPadSelect_SD0_ZP                           :  4;\
            UNSG32 uPadSelect_SD10_ZN                          :  4;\
            UNSG32 uPadSelect_SD10_ZP                          :  4;\
            UNSG32 uPadSelect_DVIO_1_V18EN                     :  1;\
            UNSG32 uPadSelect_I2S_V18EN                        :  1;\
            UNSG32 uPadSelect_DVIO_1_V25EN                     :  1;\
            UNSG32 uPadSelect_I2S_V25EN                        :  1;\
            UNSG32 uPadSelect_DVIO_1_ZN                        :  3;\
            UNSG32 uPadSelect_DVIO_1_ZP                        :  3;\
            UNSG32 uPadSelect_I2S_ZN                           :  3;\
            UNSG32 uPadSelect_I2S_ZP                           :  3;\
            UNSG32 RSVDx174_b28                                :  4;\
          }
    union { UNSG32 u32Gbl_PadSelect2;
            struct w32Gbl_PadSelect2;
          };
    #define     w32Gbl_ResetTrigger                            {\
            UNSG32 uResetTrigger_chipReset                     :  1;\
            UNSG32 uResetTrigger_audio0ClkReset                :  1;\
            UNSG32 uResetTrigger_audio1ClkReset                :  1;\
            UNSG32 uResetTrigger_audio2ClkReset                :  1;\
            UNSG32 uResetTrigger_audio3ClkReset                :  1;\
            UNSG32 uResetTrigger_audioHdClkReset               :  1;\
            UNSG32 uResetTrigger_sysPllSyncReset               :  1;\
            UNSG32 uResetTrigger_memPllSyncReset               :  1;\
            UNSG32 uResetTrigger_cpu1PllSyncReset              :  1;\
            UNSG32 uResetTrigger_cpu0SyncReset                 :  1;\
            UNSG32 uResetTrigger_cpu1SyncReset                 :  1;\
            UNSG32 uResetTrigger_socDdrSyncReset               :  1;\
            UNSG32 uResetTrigger_gfxSyncReset                  :  1;\
            UNSG32 uResetTrigger_zspSyncReset                  :  1;\
            UNSG32 uResetTrigger_avioSyncReset                 :  1;\
            UNSG32 uResetTrigger_perifSyncReset                :  1;\
            UNSG32 uResetTrigger_gethSyncReset                 :  1;\
            UNSG32 uResetTrigger_sataSyncReset                 :  1;\
            UNSG32 uResetTrigger_geth1SyncReset                :  1;\
            UNSG32 uResetTrigger_ahbApbSyncReset               :  1;\
            UNSG32 uResetTrigger_nanfSyncReset                 :  1;\
            UNSG32 uResetTrigger_smemcSyncReset                :  1;\
            UNSG32 uResetTrigger_drmSyncReset                  :  1;\
            UNSG32 uResetTrigger_usb0SyncReset                 :  1;\
            UNSG32 uResetTrigger_usb1SyncReset                 :  1;\
            UNSG32 uResetTrigger_pBridgeSyncReset              :  1;\
            UNSG32 uResetTrigger_vppSyncReset                  :  1;\
            UNSG32 uResetTrigger_vipSyncReset                  :  1;\
            UNSG32 uResetTrigger_appSyncReset                  :  1;\
            UNSG32 uResetTrigger_sdioSyncReset                 :  1;\
            UNSG32 uResetTrigger_sdio1SyncReset                :  1;\
            UNSG32 uResetTrigger_hdmirxSyncReset               :  1;\
          }
    union { UNSG32 u32Gbl_ResetTrigger;
            struct w32Gbl_ResetTrigger;
          };
    #define     w32Gbl_ResetStatus                             {\
            UNSG32 uResetStatus_ChipResetStatus                :  1;\
            UNSG32 uResetStatus_wd0Status                      :  1;\
            UNSG32 uResetStatus_wd1Status                      :  1;\
            UNSG32 uResetStatus_wd2Status                      :  1;\
            UNSG32 uResetStatus_audio0ClkResetStatus           :  1;\
            UNSG32 uResetStatus_audio1ClkResetStatus           :  1;\
            UNSG32 uResetStatus_audio2ClkResetStatus           :  1;\
            UNSG32 uResetStatus_audio3ClkResetStatus           :  1;\
            UNSG32 uResetStatus_audioHdClkResetStatus          :  1;\
            UNSG32 uResetStatus_sysPllSyncResetStatus          :  1;\
            UNSG32 uResetStatus_memPllSyncResetStatus          :  1;\
            UNSG32 uResetStatus_cpu1PllSyncResetStatus         :  1;\
            UNSG32 uResetStatus_avPllASyncResetStatus          :  1;\
            UNSG32 uResetStatus_avPllBSyncResetStatus          :  1;\
            UNSG32 uResetStatus_cpu0SyncResetStatus            :  1;\
            UNSG32 uResetStatus_cpu1SyncResetStatus            :  1;\
            UNSG32 uResetStatus_socDdrSyncResetStatus          :  1;\
            UNSG32 uResetStatus_gfxSyncResetStatus             :  1;\
            UNSG32 uResetStatus_zspSyncResetStatus             :  1;\
            UNSG32 uResetStatus_avioSyncResetStatus            :  1;\
            UNSG32 uResetStatus_perifSyncResetStatus           :  1;\
            UNSG32 uResetStatus_gethSyncResetStatus            :  1;\
            UNSG32 uResetStatus_geth1SyncResetStatus           :  1;\
            UNSG32 uResetStatus_sataSyncResetStatus            :  1;\
            UNSG32 uResetStatus_ahbApbSyncResetStatus          :  1;\
            UNSG32 uResetStatus_nanfSyncResetStatus            :  1;\
            UNSG32 uResetStatus_smemcSyncResetStatus           :  1;\
            UNSG32 uResetStatus_drmSyncResetStatus             :  1;\
            UNSG32 uResetStatus_usb0SyncResetStatus            :  1;\
            UNSG32 uResetStatus_usb1SyncResetStatus            :  1;\
            UNSG32 uResetStatus_pBridgeSyncResetStatus         :  1;\
            UNSG32 uResetStatus_vppSyncResetStatus             :  1;\
          }
    union { UNSG32 u32Gbl_ResetStatus;
            struct w32Gbl_ResetStatus;
          };
    #define     w32Gbl_ResetStatus1                            {\
            UNSG32 uResetStatus_vipSyncResetStatus             :  1;\
            UNSG32 uResetStatus_appSyncResetStatus             :  1;\
            UNSG32 uResetStatus_sdioSyncResetStatus            :  1;\
            UNSG32 uResetStatus_sdio1SyncResetStatus           :  1;\
            UNSG32 uResetStatus_hdmirxSyncResetStatus          :  1;\
            UNSG32 RSVDx180_b5                                 : 27;\
          }
    union { UNSG32 u32Gbl_ResetStatus1;
            struct w32Gbl_ResetStatus1;
          };
    #define     w32Gbl_sw_generic0                             {\
            UNSG32 usw_generic0_swReg0                         : 32;\
          }
    union { UNSG32 u32Gbl_sw_generic0;
            struct w32Gbl_sw_generic0;
          };
    #define     w32Gbl_sw_generic1                             {\
            UNSG32 usw_generic1_swReg1                         : 32;\
          }
    union { UNSG32 u32Gbl_sw_generic1;
            struct w32Gbl_sw_generic1;
          };
    #define     w32Gbl_sw_generic2                             {\
            UNSG32 usw_generic2_swReg2                         : 32;\
          }
    union { UNSG32 u32Gbl_sw_generic2;
            struct w32Gbl_sw_generic2;
          };
    #define     w32Gbl_sw_generic3                             {\
            UNSG32 usw_generic3_swReg3                         : 32;\
          }
    union { UNSG32 u32Gbl_sw_generic3;
            struct w32Gbl_sw_generic3;
          };
    #define     w32Gbl_ChipCntl0                               {\
            UNSG32 uChipCntl0_dCacheCfgCPU0                    :  2;\
            UNSG32 uChipCntl0_iCacheCfgCPU0                    :  2;\
            UNSG32 uChipCntl0_dCacheCfgCPU1                    :  2;\
            UNSG32 uChipCntl0_iCacheCfgCPU1                    :  2;\
            UNSG32 uChipCntl0_cg_bpass0Cpu0                    :  1;\
            UNSG32 uChipCntl0_cg_bpass0Cpu1                    :  1;\
            UNSG32 uChipCntl0_wfiJtagClkEn                     :  1;\
            UNSG32 RSVDx194_b11                                : 21;\
          }
    union { UNSG32 u32Gbl_ChipCntl0;
            struct w32Gbl_ChipCntl0;
          };
    #define     w32Gbl_ChipCntl1                               {\
            UNSG32 uChipCntl1_bpm_wtc                          :  2;\
            UNSG32 uChipCntl1_bpm_rtc                          :  2;\
            UNSG32 uChipCntl1_icl0data_wtc                     :  2;\
            UNSG32 uChipCntl1_icl0data_rtc                     :  2;\
            UNSG32 uChipCntl1_icl0tag_wtc                      :  2;\
            UNSG32 uChipCntl1_icl0tag_rtc                      :  2;\
            UNSG32 uChipCntl1_icl1data_wtc                     :  2;\
            UNSG32 uChipCntl1_icl1data_rtc                     :  2;\
            UNSG32 uChipCntl1_icl1tag_wtc                      :  2;\
            UNSG32 uChipCntl1_icl1tag_rtc                      :  2;\
            UNSG32 uChipCntl1_dcl1data_wtc                     :  2;\
            UNSG32 uChipCntl1_dcl1data_rtc                     :  2;\
            UNSG32 uChipCntl1_dcl1tag_wtc                      :  2;\
            UNSG32 uChipCntl1_dcl1tag_rtc                      :  2;\
            UNSG32 uChipCntl1_dcl1state_wtc                    :  2;\
            UNSG32 uChipCntl1_dcl1state_rtc                    :  2;\
          }
    union { UNSG32 u32Gbl_ChipCntl1;
            struct w32Gbl_ChipCntl1;
          };
    #define     w32Gbl_ChipCntl11                              {\
            UNSG32 uChipCntl1_dcl1attr_wtc                     :  2;\
            UNSG32 uChipCntl1_dcl1attr_rtc                     :  2;\
            UNSG32 uChipCntl1_dcl1fifo_wtc                     :  2;\
            UNSG32 uChipCntl1_dcl1fifo_rtc                     :  2;\
            UNSG32 uChipCntl1_dcl0data_wtc                     :  2;\
            UNSG32 uChipCntl1_dcl0data_rtc                     :  2;\
            UNSG32 uChipCntl1_dcl0tag_wtc                      :  2;\
            UNSG32 uChipCntl1_dcl0tag_rtc                      :  2;\
            UNSG32 uChipCntl1_l2c_dataram_wtc                  :  2;\
            UNSG32 uChipCntl1_l2c_dataram_rtc                  :  3;\
            UNSG32 uChipCntl1_l2c_dirtyram_wtc                 :  3;\
            UNSG32 uChipCntl1_l2c_dirtyram_rtc                 :  2;\
            UNSG32 uChipCntl1_l2c_lockram_wtc                  :  3;\
            UNSG32 uChipCntl1_l2c_lockram_rtc                  :  2;\
            UNSG32 RSVDx19C_b31                                :  1;\
          }
    union { UNSG32 u32Gbl_ChipCntl11;
            struct w32Gbl_ChipCntl11;
          };
    #define     w32Gbl_ChipCntl12                              {\
            UNSG32 uChipCntl1_l2c_eccram_wtc                   :  2;\
            UNSG32 uChipCntl1_l2c_eccram_rtc                   :  3;\
            UNSG32 uChipCntl1_l2c_tagram_wtc                   :  3;\
            UNSG32 uChipCntl1_l2c_tagram_rtc                   :  3;\
            UNSG32 uChipCntl1_l2c_tzram_wtc                    :  3;\
            UNSG32 uChipCntl1_l2c_tzram_rtc                    :  2;\
            UNSG32 uChipCntl1_l2c_validram_wtc                 :  3;\
            UNSG32 uChipCntl1_l2c_validram_rtc                 :  2;\
            UNSG32 uChipCntl1_mmu_wtc                          :  2;\
            UNSG32 uChipCntl1_mmu_rtc                          :  2;\
            UNSG32 uChipCntl1_sf_wtc                           :  2;\
            UNSG32 uChipCntl1_sf_rtc                           :  2;\
            UNSG32 RSVDx1A0_b29                                :  3;\
          }
    union { UNSG32 u32Gbl_ChipCntl12;
            struct w32Gbl_ChipCntl12;
          };
    #define     w32Gbl_RWTC_avio31to0                          {\
            UNSG32 uRWTC_avio31to0_value                       : 32;\
          }
    union { UNSG32 u32Gbl_RWTC_avio31to0;
            struct w32Gbl_RWTC_avio31to0;
          };
    #define     w32Gbl_RWTC_avio41to32                         {\
            UNSG32 uRWTC_avio41to32_value                      : 10;\
            UNSG32 RSVDx1A8_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_RWTC_avio41to32;
            struct w32Gbl_RWTC_avio41to32;
          };
    #define     w32Gbl_RWTC_gfx2D31to0                         {\
            UNSG32 uRWTC_gfx2D31to0_value                      : 32;\
          }
    union { UNSG32 u32Gbl_RWTC_gfx2D31to0;
            struct w32Gbl_RWTC_gfx2D31to0;
          };
    #define     w32Gbl_RWTC_gfx2D41to32                        {\
            UNSG32 uRWTC_gfx2D41to32_value                     : 10;\
            UNSG32 RSVDx1B0_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_RWTC_gfx2D41to32;
            struct w32Gbl_RWTC_gfx2D41to32;
          };
    #define     w32Gbl_RWTC_gfx3D31to0                         {\
            UNSG32 uRWTC_gfx3D31to0_value                      : 32;\
          }
    union { UNSG32 u32Gbl_RWTC_gfx3D31to0;
            struct w32Gbl_RWTC_gfx3D31to0;
          };
    #define     w32Gbl_RWTC_gfx3D41to32                        {\
            UNSG32 uRWTC_gfx3D41to32_value                     : 10;\
            UNSG32 RSVDx1B8_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_RWTC_gfx3D41to32;
            struct w32Gbl_RWTC_gfx3D41to32;
          };
    #define     w32Gbl_RWTC_soc31to0                           {\
            UNSG32 uRWTC_soc31to0_value                        : 32;\
          }
    union { UNSG32 u32Gbl_RWTC_soc31to0;
            struct w32Gbl_RWTC_soc31to0;
          };
    #define     w32Gbl_RWTC_soc41to32                          {\
            UNSG32 uRWTC_soc41to32_value                       : 10;\
            UNSG32 RSVDx1C0_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_RWTC_soc41to32;
            struct w32Gbl_RWTC_soc41to32;
          };
    #define     w32Gbl_RWTC_vPro31to0                          {\
            UNSG32 uRWTC_vPro31to0_value                       : 32;\
          }
    union { UNSG32 u32Gbl_RWTC_vPro31to0;
            struct w32Gbl_RWTC_vPro31to0;
          };
    #define     w32Gbl_RWTC_vPro41to32                         {\
            UNSG32 uRWTC_vPro41to32_value                      : 10;\
            UNSG32 RSVDx1C8_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_RWTC_vPro41to32;
            struct w32Gbl_RWTC_vPro41to32;
          };
    #define     w32Gbl_ProductId                               {\
            UNSG32 uProductId_Id                               : 32;\
          }
    union { UNSG32 u32Gbl_ProductId;
            struct w32Gbl_ProductId;
          };
    #define     w32Gbl_ProductId_ext                           {\
            UNSG32 uProductId_ext_ID_EXT                       :  8;\
            UNSG32 RSVDx1D0_b8                                 : 24;\
          }
    union { UNSG32 u32Gbl_ProductId_ext;
            struct w32Gbl_ProductId_ext;
          };
    #define     w32Gbl_FPGAR                                   {\
            UNSG32 uFPGAR_FPGAR                                : 32;\
          }
    union { UNSG32 u32Gbl_FPGAR;
            struct w32Gbl_FPGAR;
          };
    #define     w32Gbl_FPGARW                                  {\
            UNSG32 uFPGARW_FPGARW                              : 32;\
          }
    union { UNSG32 u32Gbl_FPGARW;
            struct w32Gbl_FPGARW;
          };
    #define     w32Gbl_RingOscCtl                              {\
            UNSG32 uRingOscCtl_centerInit                      :  1;\
            UNSG32 uRingOscCtl_avioTopInit                     :  1;\
            UNSG32 uRingOscCtl_avioBotInit                     :  1;\
            UNSG32 uRingOscCtl_usbTopInit                      :  1;\
            UNSG32 uRingOscCtl_cpu1TopInit                     :  1;\
            UNSG32 uRingOscCtl_cpu0TopInit                     :  1;\
            UNSG32 uRingOscCtl_cpuBotInit                      :  1;\
            UNSG32 uRingOscCtl_topRiteInit                     :  1;\
            UNSG32 uRingOscCtl_midRiteInit                     :  1;\
            UNSG32 uRingOscCtl_botRiteInit                     :  1;\
            UNSG32 RSVDx1DC_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_RingOscCtl;
            struct w32Gbl_RingOscCtl;
          };
    #define     w32Gbl_PLLBypsBootStrapEn                      {\
            UNSG32 uPLLBypsBootStrapEn_sysPLLBypsEn            :  1;\
            UNSG32 uPLLBypsBootStrapEn_memPLLBypsEn            :  1;\
            UNSG32 uPLLBypsBootStrapEn_cpu1PLLBypsEn           :  1;\
            UNSG32 RSVDx1E0_b3                                 : 29;\
          }
    union { UNSG32 u32Gbl_PLLBypsBootStrapEn;
            struct w32Gbl_PLLBypsBootStrapEn;
          };
    #define     w32Gbl_IO_CALIBRATE_IN                         {\
            UNSG32 uIO_CALIBRATE_IN_DO                         :  1;\
            UNSG32 uIO_CALIBRATE_IN_CAL_EN                     :  1;\
            UNSG32 uIO_CALIBRATE_IN_ZP_CAL                     :  3;\
            UNSG32 uIO_CALIBRATE_IN_ZN_CAL                     :  3;\
            UNSG32 uIO_CALIBRATE_IN_RON_ADJ                    :  3;\
            UNSG32 uIO_CALIBRATE_IN_TSI_CAL_N_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_TSI_CAL_P_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_TSI_ODR                    :  3;\
            UNSG32 uIO_CALIBRATE_IN_TSI_ODR_EN                 :  1;\
            UNSG32 uIO_CALIBRATE_IN_TSI_ZN                     :  4;\
            UNSG32 uIO_CALIBRATE_IN_TSI_ZP                     :  4;\
            UNSG32 uIO_CALIBRATE_IN_TSI_ZP_AFT_CAL             :  4;\
            UNSG32 uIO_CALIBRATE_IN_NAND_CAL_N_EN              :  1;\
            UNSG32 uIO_CALIBRATE_IN_NAND_CAL_P_EN              :  1;\
            UNSG32 RSVDx1E4_b31                                :  1;\
          }
    union { UNSG32 u32Gbl_IO_CALIBRATE_IN;
            struct w32Gbl_IO_CALIBRATE_IN;
          };
    #define     w32Gbl_IO_CALIBRATE_IN1                        {\
            UNSG32 uIO_CALIBRATE_IN_NAND_ODR                   :  3;\
            UNSG32 uIO_CALIBRATE_IN_NAND_ODR_EN                :  1;\
            UNSG32 uIO_CALIBRATE_IN_NAND_ZN                    :  4;\
            UNSG32 uIO_CALIBRATE_IN_NAND_ZP                    :  4;\
            UNSG32 uIO_CALIBRATE_IN_NAND_ZP_AFT_CAL            :  4;\
            UNSG32 uIO_CALIBRATE_IN_SPI_CAL_N_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_SPI_CAL_P_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_SPI_ODR                    :  3;\
            UNSG32 uIO_CALIBRATE_IN_SPI_ODR_EN                 :  1;\
            UNSG32 uIO_CALIBRATE_IN_SPI_ZN                     :  4;\
            UNSG32 uIO_CALIBRATE_IN_SPI_ZP                     :  4;\
            UNSG32 RSVDx1E8_b30                                :  2;\
          }
    union { UNSG32 u32Gbl_IO_CALIBRATE_IN1;
            struct w32Gbl_IO_CALIBRATE_IN1;
          };
    #define     w32Gbl_IO_CALIBRATE_IN2                        {\
            UNSG32 uIO_CALIBRATE_IN_SPI_ZP_AFT_CAL             :  4;\
            UNSG32 uIO_CALIBRATE_IN_SD0_CAL_N_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_SD0_CAL_P_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_SD0_ODR                    :  3;\
            UNSG32 uIO_CALIBRATE_IN_SD0_ODR_EN                 :  1;\
            UNSG32 uIO_CALIBRATE_IN_SD0_ZN                     :  4;\
            UNSG32 uIO_CALIBRATE_IN_SD0_ZP                     :  4;\
            UNSG32 uIO_CALIBRATE_IN_SD0_ZP_AFT_CAL             :  4;\
            UNSG32 uIO_CALIBRATE_IN_SD1_CAL_N_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_SD1_CAL_P_EN               :  1;\
            UNSG32 uIO_CALIBRATE_IN_SD1_ODR                    :  3;\
            UNSG32 uIO_CALIBRATE_IN_SD1_ODR_EN                 :  1;\
            UNSG32 uIO_CALIBRATE_IN_SD1_ZN                     :  4;\
          }
    union { UNSG32 u32Gbl_IO_CALIBRATE_IN2;
            struct w32Gbl_IO_CALIBRATE_IN2;
          };
    #define     w32Gbl_IO_CALIBRATE_IN3                        {\
            UNSG32 uIO_CALIBRATE_IN_SD1_ZP                     :  4;\
            UNSG32 uIO_CALIBRATE_IN_SD1_ZP_AFT_CAL             :  4;\
            UNSG32 uIO_CALIBRATE_IN_DVIO_1_DO                  :  1;\
            UNSG32 uIO_CALIBRATE_IN_DVIO_1_CAL_EN              :  1;\
            UNSG32 uIO_CALIBRATE_IN_DVIO_1_ZP_CAL              :  3;\
            UNSG32 uIO_CALIBRATE_IN_DVIO_1_ZN_CAL              :  3;\
            UNSG32 uIO_CALIBRATE_IN_DVIO_1_RON_ADJ             :  3;\
            UNSG32 uIO_CALIBRATE_IN_I2S_DO                     :  1;\
            UNSG32 uIO_CALIBRATE_IN_I2S_CAL_EN                 :  1;\
            UNSG32 uIO_CALIBRATE_IN_I2S_ZP_CAL                 :  3;\
            UNSG32 uIO_CALIBRATE_IN_I2S_ZN_CAL                 :  3;\
            UNSG32 uIO_CALIBRATE_IN_I2S_RON_ADJ                :  3;\
            UNSG32 RSVDx1F0_b30                                :  2;\
          }
    union { UNSG32 u32Gbl_IO_CALIBRATE_IN3;
            struct w32Gbl_IO_CALIBRATE_IN3;
          };
    #define     w32Gbl_IO_CALBRATE_OUT                         {\
            UNSG32 uIO_CALBRATE_OUT_INC                        :  1;\
            UNSG32 uIO_CALBRATE_OUT_TSI_CAL_N_INC              :  1;\
            UNSG32 uIO_CALBRATE_OUT_TSI_CAL_P_INC              :  1;\
            UNSG32 uIO_CALBRATE_OUT_SD0_CAL_N_INC              :  1;\
            UNSG32 uIO_CALBRATE_OUT_SD0_CAL_P_INC              :  1;\
            UNSG32 uIO_CALBRATE_OUT_SD1_CAL_N_INC              :  1;\
            UNSG32 uIO_CALBRATE_OUT_SD1_CAL_P_INC              :  1;\
            UNSG32 uIO_CALBRATE_OUT_NAND_CAL_N_INC             :  1;\
            UNSG32 uIO_CALBRATE_OUT_NAND_CAL_P_INC             :  1;\
            UNSG32 uIO_CALBRATE_OUT_DVIO_1_INC                 :  1;\
            UNSG32 uIO_CALBRATE_OUT_I2S_INC                    :  1;\
            UNSG32 RSVDx1F4_b11                                : 21;\
          }
    union { UNSG32 u32Gbl_IO_CALBRATE_OUT;
            struct w32Gbl_IO_CALBRATE_OUT;
          };
    #define     w32Gbl_SECURE_SCAN_EN                          {\
            UNSG32 uSECURE_SCAN_EN_SET                         :  1;\
            UNSG32 RSVDx1F8_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_SECURE_SCAN_EN;
            struct w32Gbl_SECURE_SCAN_EN;
          };
    #define     w32Gbl_NandWPn                                 {\
            UNSG32 uNandWPn_Sel                                :  1;\
            UNSG32 RSVDx1FC_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_NandWPn;
            struct w32Gbl_NandWPn;
          };
    #define     w32Gbl_RingCntCntl                             {\
            UNSG32 uRingCntCntl_centerStart                    :  1;\
            UNSG32 uRingCntCntl_centerStop                     :  1;\
            UNSG32 uRingCntCntl_avioTopStart                   :  1;\
            UNSG32 uRingCntCntl_avioTopStop                    :  1;\
            UNSG32 uRingCntCntl_avioBotStart                   :  1;\
            UNSG32 uRingCntCntl_avioBotStop                    :  1;\
            UNSG32 uRingCntCntl_usbTopStart                    :  1;\
            UNSG32 uRingCntCntl_usbTopStop                     :  1;\
            UNSG32 uRingCntCntl_cpu1TopStart                   :  1;\
            UNSG32 uRingCntCntl_cpu1TopStop                    :  1;\
            UNSG32 uRingCntCntl_cpu0TopStart                   :  1;\
            UNSG32 uRingCntCntl_cpu0TopStop                    :  1;\
            UNSG32 uRingCntCntl_cpuBotStart                    :  1;\
            UNSG32 uRingCntCntl_cpuBotStop                     :  1;\
            UNSG32 uRingCntCntl_topRiteStart                   :  1;\
            UNSG32 uRingCntCntl_topRiteStop                    :  1;\
            UNSG32 uRingCntCntl_midRiteStart                   :  1;\
            UNSG32 uRingCntCntl_midRiteStop                    :  1;\
            UNSG32 uRingCntCntl_botRiteStart                   :  1;\
            UNSG32 uRingCntCntl_botRiteStop                    :  1;\
            UNSG32 RSVDx200_b20                                : 12;\
          }
    union { UNSG32 u32Gbl_RingCntCntl;
            struct w32Gbl_RingCntCntl;
          };
              SIE_droCount                                     ie_topSvtDro0Cnt;
              SIE_droCount                                     ie_topLvtDro1Cnt;
              SIE_droCount                                     ie_topSvtDro2Cnt;
              SIE_droCount                                     ie_topLvtDro3Cnt;
              SIE_droCount                                     ie_topSvtDro4Cnt;
              SIE_droCount                                     ie_topLvtDro5Cnt;
              SIE_droCount                                     ie_avioSvtDro0Cnt;
              SIE_droCount                                     ie_avioLvtDro1Cnt;
              SIE_droCount                                     ie_avioSvtDro2Cnt;
              SIE_droCount                                     ie_avioLvtDro3Cnt;
    #define     w32Gbl_gfx3DCoreClkCtrl                        {\
            UNSG32 ugfx3DCoreClkCtrl_clkEN                     :  1;\
            UNSG32 ugfx3DCoreClkCtrl_ClkPllSel                 :  3;\
            UNSG32 ugfx3DCoreClkCtrl_ClkPllSwitch              :  1;\
            UNSG32 ugfx3DCoreClkCtrl_ClkSwitch                 :  1;\
            UNSG32 ugfx3DCoreClkCtrl_ClkD3Switch               :  1;\
            UNSG32 ugfx3DCoreClkCtrl_ClkSel                    :  3;\
            UNSG32 RSVDx22C_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_gfx3DCoreClkCtrl;
            struct w32Gbl_gfx3DCoreClkCtrl;
          };
    #define     w32Gbl_gfx3DSysClkCtrl                         {\
            UNSG32 ugfx3DSysClkCtrl_clkEN                      :  1;\
            UNSG32 ugfx3DSysClkCtrl_ClkPllSel                  :  3;\
            UNSG32 ugfx3DSysClkCtrl_ClkPllSwitch               :  1;\
            UNSG32 ugfx3DSysClkCtrl_ClkSwitch                  :  1;\
            UNSG32 ugfx3DSysClkCtrl_ClkD3Switch                :  1;\
            UNSG32 ugfx3DSysClkCtrl_ClkSel                     :  3;\
            UNSG32 RSVDx230_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_gfx3DSysClkCtrl;
            struct w32Gbl_gfx3DSysClkCtrl;
          };
    #define     w32Gbl_arcRefClkCtrl                           {\
            UNSG32 uarcRefClkCtrl_clkEN                        :  1;\
            UNSG32 uarcRefClkCtrl_ClkPllSel                    :  3;\
            UNSG32 uarcRefClkCtrl_ClkPllSwitch                 :  1;\
            UNSG32 uarcRefClkCtrl_ClkSwitch                    :  1;\
            UNSG32 uarcRefClkCtrl_ClkD3Switch                  :  1;\
            UNSG32 uarcRefClkCtrl_ClkSel                       :  3;\
            UNSG32 RSVDx234_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_arcRefClkCtrl;
            struct w32Gbl_arcRefClkCtrl;
          };
    #define     w32Gbl_vipClkCtrl                              {\
            UNSG32 uvipClkCtrl_clkEN                           :  1;\
            UNSG32 uvipClkCtrl_ClkPllSel                       :  3;\
            UNSG32 uvipClkCtrl_ClkPllSwitch                    :  1;\
            UNSG32 uvipClkCtrl_ClkSwitch                       :  1;\
            UNSG32 uvipClkCtrl_ClkD3Switch                     :  1;\
            UNSG32 uvipClkCtrl_ClkSel                          :  3;\
            UNSG32 RSVDx238_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_vipClkCtrl;
            struct w32Gbl_vipClkCtrl;
          };
    #define     w32Gbl_sdioXinClkCtrl                          {\
            UNSG32 usdioXinClkCtrl_ClkEN                       :  1;\
            UNSG32 usdioXinClkCtrl_ClkPllSel                   :  3;\
            UNSG32 usdioXinClkCtrl_ClkPllSwitch                :  1;\
            UNSG32 usdioXinClkCtrl_ClkSwitch                   :  1;\
            UNSG32 usdioXinClkCtrl_ClkD3Switch                 :  1;\
            UNSG32 usdioXinClkCtrl_ClkSel                      :  3;\
            UNSG32 RSVDx23C_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_sdioXinClkCtrl;
            struct w32Gbl_sdioXinClkCtrl;
          };
    #define     w32Gbl_sdio1XinClkCtrl                         {\
            UNSG32 usdio1XinClkCtrl_ClkEN                      :  1;\
            UNSG32 usdio1XinClkCtrl_ClkPllSel                  :  3;\
            UNSG32 usdio1XinClkCtrl_ClkPllSwitch               :  1;\
            UNSG32 usdio1XinClkCtrl_ClkSwitch                  :  1;\
            UNSG32 usdio1XinClkCtrl_ClkD3Switch                :  1;\
            UNSG32 usdio1XinClkCtrl_ClkSel                     :  3;\
            UNSG32 RSVDx240_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_sdio1XinClkCtrl;
            struct w32Gbl_sdio1XinClkCtrl;
          };
    #define     w32Gbl_gfx3DExtraClkCtrl                       {\
            UNSG32 ugfx3DExtraClkCtrl_ClkEN                    :  1;\
            UNSG32 ugfx3DExtraClkCtrl_ClkPllSel                :  3;\
            UNSG32 ugfx3DExtraClkCtrl_ClkPllSwitch             :  1;\
            UNSG32 ugfx3DExtraClkCtrl_ClkSwitch                :  1;\
            UNSG32 ugfx3DExtraClkCtrl_ClkD3Switch              :  1;\
            UNSG32 ugfx3DExtraClkCtrl_ClkSel                   :  3;\
            UNSG32 RSVDx244_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_gfx3DExtraClkCtrl;
            struct w32Gbl_gfx3DExtraClkCtrl;
          };
    #define     w32Gbl_gfx3DReset                              {\
            UNSG32 ugfx3DReset_SyncReset                       :  1;\
            UNSG32 RSVDx248_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_gfx3DReset;
            struct w32Gbl_gfx3DReset;
          };
    #define     w32Gbl_gc360ClkCtrl                            {\
            UNSG32 ugc360ClkCtrl_ClkEN                         :  1;\
            UNSG32 ugc360ClkCtrl_ClkPllSel                     :  3;\
            UNSG32 ugc360ClkCtrl_ClkPllSwitch                  :  1;\
            UNSG32 ugc360ClkCtrl_ClkSwitch                     :  1;\
            UNSG32 ugc360ClkCtrl_ClkD3Switch                   :  1;\
            UNSG32 ugc360ClkCtrl_ClkSel                        :  3;\
            UNSG32 RSVDx24C_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_gc360ClkCtrl;
            struct w32Gbl_gc360ClkCtrl;
          };
    #define     w32Gbl_sdioDllMstRef                           {\
            UNSG32 usdioDllMstRef_ClkEN                        :  1;\
            UNSG32 usdioDllMstRef_ClkPllSel                    :  3;\
            UNSG32 usdioDllMstRef_ClkPllSwitch                 :  1;\
            UNSG32 usdioDllMstRef_ClkSwitch                    :  1;\
            UNSG32 usdioDllMstRef_ClkD3Switch                  :  1;\
            UNSG32 usdioDllMstRef_ClkSel                       :  3;\
            UNSG32 RSVDx250_b10                                : 22;\
          }
    union { UNSG32 u32Gbl_sdioDllMstRef;
            struct w32Gbl_sdioDllMstRef;
          };
    #define     w32Gbl_sdioDllMstCtrl                          {\
            UNSG32 usdioDllMstCtrl_PH_SEL1                     :  5;\
            UNSG32 usdioDllMstCtrl_PH_SEL2                     :  5;\
            UNSG32 usdioDllMstCtrl_PH_SEL3                     :  5;\
            UNSG32 usdioDllMstCtrl_PH_SEL4                     :  5;\
            UNSG32 usdioDllMstCtrl_AUTO_UPDATE_EN              :  1;\
            UNSG32 usdioDllMstCtrl_UPDATE_EN                   :  1;\
            UNSG32 usdioDllMstCtrl_RESET                       :  1;\
            UNSG32 usdioDllMstCtrl_GAIN2X                      :  1;\
            UNSG32 usdioDllMstCtrl_TEST_EN                     :  1;\
            UNSG32 usdioDllMstCtrl_BYPASS_EN                   :  1;\
            UNSG32 RSVDx254_b26                                :  6;\
          }
    union { UNSG32 u32Gbl_sdioDllMstCtrl;
            struct w32Gbl_sdioDllMstCtrl;
          };
    #define     w32Gbl_sdioDllMstCtrl1                         {\
            UNSG32 usdioDllMstCtrl_DELAY_TEST                  :  9;\
            UNSG32 usdioDllMstCtrl_RESERVE                     :  5;\
            UNSG32 RSVDx258_b14                                : 18;\
          }
    union { UNSG32 u32Gbl_sdioDllMstCtrl1;
            struct w32Gbl_sdioDllMstCtrl1;
          };
    #define     w32Gbl_sdioDllMstStatus                        {\
            UNSG32 usdioDllMstStatus_DELAY_CTRL2               :  9;\
            UNSG32 usdioDllMstStatus_DELAY_CTRL3               :  9;\
            UNSG32 usdioDllMstStatus_DELAY_CTRL4               :  9;\
            UNSG32 usdioDllMstStatus_PRE_LOCK                  :  1;\
            UNSG32 usdioDllMstStatus_DLL_LOCK                  :  1;\
            UNSG32 RSVDx25C_b29                                :  3;\
          }
    union { UNSG32 u32Gbl_sdioDllMstStatus;
            struct w32Gbl_sdioDllMstStatus;
          };
    #define     w32Gbl_sdioDllMstStatus1                       {\
            UNSG32 usdioDllMstStatus_DELAY_OUT                 :  8;\
            UNSG32 RSVDx260_b8                                 : 24;\
          }
    union { UNSG32 u32Gbl_sdioDllMstStatus1;
            struct w32Gbl_sdioDllMstStatus1;
          };
    #define     w32Gbl_sdioPortSel                             {\
            UNSG32 usdioPortSel_port0                          :  1;\
            UNSG32 usdioPortSel_port1                          :  1;\
            UNSG32 RSVDx264_b2                                 : 30;\
          }
    union { UNSG32 u32Gbl_sdioPortSel;
            struct w32Gbl_sdioPortSel;
          };
    #define     w32Gbl_gc360Reset                              {\
            UNSG32 ugc360Reset_SyncReset                       :  1;\
            UNSG32 RSVDx268_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_gc360Reset;
            struct w32Gbl_gc360Reset;
          };
    #define     w32Gbl_SpdifRxReset                            {\
            UNSG32 uSpdifRxReset_SyncReset                     :  1;\
            UNSG32 RSVDx26C_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_SpdifRxReset;
            struct w32Gbl_SpdifRxReset;
          };
    #define     w32Gbl_gfx3DDisRamClkGate                      {\
            UNSG32 ugfx3DDisRamClkGate_drcg                    :  1;\
            UNSG32 RSVDx270_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_gfx3DDisRamClkGate;
            struct w32Gbl_gfx3DDisRamClkGate;
          };
    #define     w32Gbl_gfx3DResetStatus                        {\
            UNSG32 ugfx3DResetStatus_SyncReset                 :  1;\
            UNSG32 RSVDx274_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_gfx3DResetStatus;
            struct w32Gbl_gfx3DResetStatus;
          };
    #define     w32Gbl_gc360DisRCG                             {\
            UNSG32 ugc360DisRCG_drcg                           :  1;\
            UNSG32 RSVDx278_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_gc360DisRCG;
            struct w32Gbl_gc360DisRCG;
          };
    #define     w32Gbl_gc360ResetStatus                        {\
            UNSG32 ugc360ResetStatus_SyncReset                 :  1;\
            UNSG32 RSVDx27C_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_gc360ResetStatus;
            struct w32Gbl_gc360ResetStatus;
          };
    #define     w32Gbl_SpdifRxResetStatus                      {\
            UNSG32 uSpdifRxResetStatus_SyncReset               :  1;\
            UNSG32 RSVDx280_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_SpdifRxResetStatus;
            struct w32Gbl_SpdifRxResetStatus;
          };
    #define     w32Gbl_DroEnable                               {\
            UNSG32 uDroEnable_EnDroCounter                     :  1;\
            UNSG32 RSVDx284_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_DroEnable;
            struct w32Gbl_DroEnable;
          };
    #define     w32Gbl_DroCounter                              {\
            UNSG32 uDroCounter_CountVal                        : 32;\
          }
    union { UNSG32 u32Gbl_DroCounter;
            struct w32Gbl_DroCounter;
          };
    #define     w32Gbl_DroDone                                 {\
            UNSG32 uDroDone_status                             :  1;\
            UNSG32 RSVDx28C_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_DroDone;
            struct w32Gbl_DroDone;
          };
              SIE_droCount                                     ie_cpussSvtDro0Cnt;
              SIE_droCount                                     ie_cpussLvtDro1Cnt;
              SIE_droCount                                     ie_cpussSvtDro2Cnt;
              SIE_droCount                                     ie_cpussLvtDro3Cnt;
              SIE_droCount                                     ie_vMetaSvtDro0Cnt;
              SIE_droCount                                     ie_vMetaLvtDro1Cnt;
              SIE_droCount                                     ie_gfx3DSvtDro0Cnt;
              SIE_droCount                                     ie_gfx3DLvtDro1Cnt;
    #define     w32Gbl_INT_ID                                  {\
            UNSG32 uINT_ID_VALUE                               :  8;\
            UNSG32 RSVDx2B0_b8                                 : 24;\
          }
    union { UNSG32 u32Gbl_INT_ID;
            struct w32Gbl_INT_ID;
          };
              SIE_clkD1                                        ie_hdmirxFpllRefClk;
              SIE_clkD4                                        ie_hdmirxTClk;
              SIE_clkD8                                        ie_hdmirxMClk;
              SIE_clkD8                                        ie_gethRgmiiClk;
              SIE_clkD4                                        ie_pcieTestClk;
    #define     w32Gbl_stickyResetN                            {\
            UNSG32 ustickyResetN_gethRgmiiMemRstn              :  1;\
            UNSG32 ustickyResetN_gethRgmiiRstn                 :  1;\
            UNSG32 ustickyResetN_cpuPllRstn                    :  1;\
            UNSG32 ustickyResetN_memPllRstn                    :  1;\
            UNSG32 ustickyResetN_sysPllRstn                    :  1;\
            UNSG32 RSVDx2C8_b5                                 : 27;\
          }
    union { UNSG32 u32Gbl_stickyResetN;
            struct w32Gbl_stickyResetN;
          };
    #define     w32Gbl_gethRgmii_dll                           {\
            UNSG32 ugethRgmii_dll_tx_delay                     :  9;\
            UNSG32 ugethRgmii_dll_rx_delay                     :  9;\
            UNSG32 RSVDx2CC_b18                                : 14;\
          }
    union { UNSG32 u32Gbl_gethRgmii_dll;
            struct w32Gbl_gethRgmii_dll;
          };
    #define     w32Gbl_funcSel                                 {\
            UNSG32 ufuncSel_pcie_sata_sel                      :  1;\
            UNSG32 ufuncSel_gmac_eth_sel                       :  1;\
            UNSG32 RSVDx2D0_b2                                 : 30;\
          }
    union { UNSG32 u32Gbl_funcSel;
            struct w32Gbl_funcSel;
          };
              SIE_efuse                                        ie_efuse;
    #define     w32Gbl_chipCntl                                {\
            UNSG32 uchipCntl_pcieDownMap                       :  1;\
            UNSG32 uchipCntl_pcie_rc                           :  1;\
            UNSG32 RSVDx300_b2                                 : 30;\
          }
    union { UNSG32 u32Gbl_chipCntl;
            struct w32Gbl_chipCntl;
          };
    #define     w32Gbl_bootStrapEn                             {\
            UNSG32 ubootStrapEn_pllPwrDownEn                   :  1;\
            UNSG32 ubootStrapEn_refClk12P5MEn                  :  1;\
            UNSG32 RSVDx304_b2                                 : 30;\
          }
    union { UNSG32 u32Gbl_bootStrapEn;
            struct w32Gbl_bootStrapEn;
          };
    #define     w32Gbl_axiClkEn                                {\
            UNSG32 uaxiClkEn_avioAxiClkEn                      :  1;\
            UNSG32 RSVDx308_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_axiClkEn;
            struct w32Gbl_axiClkEn;
          };
    #define     w32Gbl_ahbClkEn                                {\
            UNSG32 uahbClkEn_avioAhbClkEn                      :  1;\
            UNSG32 RSVDx30C_b1                                 : 31;\
          }
    union { UNSG32 u32Gbl_ahbClkEn;
            struct w32Gbl_ahbClkEn;
          };
             UNSG8 RSVDx310                                    [31984];
    #define     w32Gbl_SPI1_SS0nCntl                           {\
            UNSG32 uSPI1_SS0nCntl_PU_EN                        :  1;\
            UNSG32 uSPI1_SS0nCntl_PD_EN                        :  1;\
            UNSG32 RSVDx8000_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_SPI1_SS0nCntl;
            struct w32Gbl_SPI1_SS0nCntl;
          };
    #define     w32Gbl_SPI1_SS1nCntl                           {\
            UNSG32 uSPI1_SS1nCntl_PU_EN                        :  1;\
            UNSG32 uSPI1_SS1nCntl_PD_EN                        :  1;\
            UNSG32 RSVDx8004_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_SPI1_SS1nCntl;
            struct w32Gbl_SPI1_SS1nCntl;
          };
    #define     w32Gbl_SPI1_SS2nCntl                           {\
            UNSG32 uSPI1_SS2nCntl_PU_EN                        :  1;\
            UNSG32 uSPI1_SS2nCntl_PD_EN                        :  1;\
            UNSG32 RSVDx8008_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_SPI1_SS2nCntl;
            struct w32Gbl_SPI1_SS2nCntl;
          };
    #define     w32Gbl_SPI1_SCLKCntl                           {\
            UNSG32 uSPI1_SCLKCntl_PU_EN                        :  1;\
            UNSG32 uSPI1_SCLKCntl_PD_EN                        :  1;\
            UNSG32 RSVDx800C_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_SPI1_SCLKCntl;
            struct w32Gbl_SPI1_SCLKCntl;
          };
    #define     w32Gbl_SPI1_SDOCntl                            {\
            UNSG32 uSPI1_SDOCntl_PU_EN                         :  1;\
            UNSG32 uSPI1_SDOCntl_PD_EN                         :  1;\
            UNSG32 RSVDx8010_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_SPI1_SDOCntl;
            struct w32Gbl_SPI1_SDOCntl;
          };
    #define     w32Gbl_SPI1_SDICntl                            {\
            UNSG32 uSPI1_SDICntl_PU_EN                         :  1;\
            UNSG32 uSPI1_SDICntl_PD_EN                         :  1;\
            UNSG32 RSVDx8014_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_SPI1_SDICntl;
            struct w32Gbl_SPI1_SDICntl;
          };
    #define     w32Gbl_URT0_RXDCntl                            {\
            UNSG32 uURT0_RXDCntl_PU_EN                         :  1;\
            UNSG32 uURT0_RXDCntl_PD_EN                         :  1;\
            UNSG32 RSVDx8018_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_URT0_RXDCntl;
            struct w32Gbl_URT0_RXDCntl;
          };
    #define     w32Gbl_URT0_TXDCntl                            {\
            UNSG32 uURT0_TXDCntl_PU_EN                         :  1;\
            UNSG32 uURT0_TXDCntl_PD_EN                         :  1;\
            UNSG32 RSVDx801C_b2                                : 30;\
          }
    union { UNSG32 u32Gbl_URT0_TXDCntl;
            struct w32Gbl_URT0_TXDCntl;
          };
    #define     w32Gbl_DVIO0Cntl                               {\
            UNSG32 uDVIO0Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO0Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO0Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8020_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO0Cntl;
            struct w32Gbl_DVIO0Cntl;
          };
    #define     w32Gbl_DVIO1Cntl                               {\
            UNSG32 uDVIO1Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO1Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO1Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8024_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO1Cntl;
            struct w32Gbl_DVIO1Cntl;
          };
    #define     w32Gbl_DVIO2Cntl                               {\
            UNSG32 uDVIO2Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO2Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO2Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8028_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO2Cntl;
            struct w32Gbl_DVIO2Cntl;
          };
    #define     w32Gbl_DVIO3Cntl                               {\
            UNSG32 uDVIO3Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO3Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO3Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx802C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO3Cntl;
            struct w32Gbl_DVIO3Cntl;
          };
    #define     w32Gbl_DVIO4Cntl                               {\
            UNSG32 uDVIO4Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO4Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO4Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8030_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO4Cntl;
            struct w32Gbl_DVIO4Cntl;
          };
    #define     w32Gbl_DVIO5Cntl                               {\
            UNSG32 uDVIO5Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO5Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO5Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8034_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO5Cntl;
            struct w32Gbl_DVIO5Cntl;
          };
    #define     w32Gbl_DVIO6Cntl                               {\
            UNSG32 uDVIO6Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO6Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO6Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8038_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO6Cntl;
            struct w32Gbl_DVIO6Cntl;
          };
    #define     w32Gbl_DVIO7Cntl                               {\
            UNSG32 uDVIO7Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO7Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO7Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx803C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO7Cntl;
            struct w32Gbl_DVIO7Cntl;
          };
    #define     w32Gbl_DVIO8Cntl                               {\
            UNSG32 uDVIO8Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO8Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO8Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8040_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO8Cntl;
            struct w32Gbl_DVIO8Cntl;
          };
    #define     w32Gbl_DVIO9Cntl                               {\
            UNSG32 uDVIO9Cntl_PU_EN                            :  1;\
            UNSG32 uDVIO9Cntl_PD_EN                            :  1;\
            UNSG32 uDVIO9Cntl_SLP_DI                           :  1;\
            UNSG32 RSVDx8044_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO9Cntl;
            struct w32Gbl_DVIO9Cntl;
          };
    #define     w32Gbl_DVIO10Cntl                              {\
            UNSG32 uDVIO10Cntl_PU_EN                           :  1;\
            UNSG32 uDVIO10Cntl_PD_EN                           :  1;\
            UNSG32 uDVIO10Cntl_SLP_DI                          :  1;\
            UNSG32 RSVDx8048_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO10Cntl;
            struct w32Gbl_DVIO10Cntl;
          };
    #define     w32Gbl_DVIO11Cntl                              {\
            UNSG32 uDVIO11Cntl_PU_EN                           :  1;\
            UNSG32 uDVIO11Cntl_PD_EN                           :  1;\
            UNSG32 uDVIO11Cntl_SLP_DI                          :  1;\
            UNSG32 RSVDx804C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DVIO11Cntl;
            struct w32Gbl_DVIO11Cntl;
          };
    #define     w32Gbl_DV0_CLKCntl                             {\
            UNSG32 uDV0_CLKCntl_PU_EN                          :  1;\
            UNSG32 uDV0_CLKCntl_PD_EN                          :  1;\
            UNSG32 uDV0_CLKCntl_SLP_DI                         :  1;\
            UNSG32 RSVDx8050_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DV0_CLKCntl;
            struct w32Gbl_DV0_CLKCntl;
          };
    #define     w32Gbl_DV0_HSCntl                              {\
            UNSG32 uDV0_HSCntl_PU_EN                           :  1;\
            UNSG32 uDV0_HSCntl_PD_EN                           :  1;\
            UNSG32 uDV0_HSCntl_SLP_DI                          :  1;\
            UNSG32 RSVDx8054_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DV0_HSCntl;
            struct w32Gbl_DV0_HSCntl;
          };
    #define     w32Gbl_DV0_VSCntl                              {\
            UNSG32 uDV0_VSCntl_PU_EN                           :  1;\
            UNSG32 uDV0_VSCntl_PD_EN                           :  1;\
            UNSG32 uDV0_VSCntl_SLP_DI                          :  1;\
            UNSG32 RSVDx8058_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DV0_VSCntl;
            struct w32Gbl_DV0_VSCntl;
          };
    #define     w32Gbl_DV0_FIDCntl                             {\
            UNSG32 uDV0_FIDCntl_PU_EN                          :  1;\
            UNSG32 uDV0_FIDCntl_PD_EN                          :  1;\
            UNSG32 uDV0_FIDCntl_SLP_DI                         :  1;\
            UNSG32 RSVDx805C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_DV0_FIDCntl;
            struct w32Gbl_DV0_FIDCntl;
          };
    #define     w32Gbl_I2S0_BCLKCntl                           {\
            UNSG32 uI2S0_BCLKCntl_PU_EN                        :  1;\
            UNSG32 uI2S0_BCLKCntl_PD_EN                        :  1;\
            UNSG32 uI2S0_BCLKCntl_SLP_DI                       :  1;\
            UNSG32 RSVDx8060_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S0_BCLKCntl;
            struct w32Gbl_I2S0_BCLKCntl;
          };
    #define     w32Gbl_I2S0_LRCKCntl                           {\
            UNSG32 uI2S0_LRCKCntl_PU_EN                        :  1;\
            UNSG32 uI2S0_LRCKCntl_PD_EN                        :  1;\
            UNSG32 uI2S0_LRCKCntl_SLP_DI                       :  1;\
            UNSG32 RSVDx8064_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S0_LRCKCntl;
            struct w32Gbl_I2S0_LRCKCntl;
          };
    #define     w32Gbl_I2S0_DO0Cntl                            {\
            UNSG32 uI2S0_DO0Cntl_PU_EN                         :  1;\
            UNSG32 uI2S0_DO0Cntl_PD_EN                         :  1;\
            UNSG32 uI2S0_DO0Cntl_SLP_DI                        :  1;\
            UNSG32 RSVDx8068_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S0_DO0Cntl;
            struct w32Gbl_I2S0_DO0Cntl;
          };
    #define     w32Gbl_I2S0_DO1Cntl                            {\
            UNSG32 uI2S0_DO1Cntl_PU_EN                         :  1;\
            UNSG32 uI2S0_DO1Cntl_PD_EN                         :  1;\
            UNSG32 uI2S0_DO1Cntl_SLP_DI                        :  1;\
            UNSG32 RSVDx806C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S0_DO1Cntl;
            struct w32Gbl_I2S0_DO1Cntl;
          };
    #define     w32Gbl_I2S0_DO2Cntl                            {\
            UNSG32 uI2S0_DO2Cntl_PU_EN                         :  1;\
            UNSG32 uI2S0_DO2Cntl_PD_EN                         :  1;\
            UNSG32 uI2S0_DO2Cntl_SLP_DI                        :  1;\
            UNSG32 RSVDx8070_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S0_DO2Cntl;
            struct w32Gbl_I2S0_DO2Cntl;
          };
    #define     w32Gbl_I2S0_DO3Cntl                            {\
            UNSG32 uI2S0_DO3Cntl_PU_EN                         :  1;\
            UNSG32 uI2S0_DO3Cntl_PD_EN                         :  1;\
            UNSG32 uI2S0_DO3Cntl_SLP_DI                        :  1;\
            UNSG32 RSVDx8074_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S0_DO3Cntl;
            struct w32Gbl_I2S0_DO3Cntl;
          };
    #define     w32Gbl_SPDIFICntl                              {\
            UNSG32 uSPDIFICntl_PU_EN                           :  1;\
            UNSG32 uSPDIFICntl_PD_EN                           :  1;\
            UNSG32 uSPDIFICntl_SLP_DI                          :  1;\
            UNSG32 RSVDx8078_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_SPDIFICntl;
            struct w32Gbl_SPDIFICntl;
          };
    #define     w32Gbl_I2S1_LRCKCntl                           {\
            UNSG32 uI2S1_LRCKCntl_PU_EN                        :  1;\
            UNSG32 uI2S1_LRCKCntl_PD_EN                        :  1;\
            UNSG32 uI2S1_LRCKCntl_SLP_DI                       :  1;\
            UNSG32 RSVDx807C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S1_LRCKCntl;
            struct w32Gbl_I2S1_LRCKCntl;
          };
    #define     w32Gbl_I2S1_BCLKCntl                           {\
            UNSG32 uI2S1_BCLKCntl_PU_EN                        :  1;\
            UNSG32 uI2S1_BCLKCntl_PD_EN                        :  1;\
            UNSG32 uI2S1_BCLKCntl_SLP_DI                       :  1;\
            UNSG32 RSVDx8080_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S1_BCLKCntl;
            struct w32Gbl_I2S1_BCLKCntl;
          };
    #define     w32Gbl_I2S1_DOCntl                             {\
            UNSG32 uI2S1_DOCntl_PU_EN                          :  1;\
            UNSG32 uI2S1_DOCntl_PD_EN                          :  1;\
            UNSG32 uI2S1_DOCntl_SLP_DI                         :  1;\
            UNSG32 RSVDx8084_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S1_DOCntl;
            struct w32Gbl_I2S1_DOCntl;
          };
    #define     w32Gbl_I2S2_LRCKCntl                           {\
            UNSG32 uI2S2_LRCKCntl_PU_EN                        :  1;\
            UNSG32 uI2S2_LRCKCntl_PD_EN                        :  1;\
            UNSG32 uI2S2_LRCKCntl_SLP_DI                       :  1;\
            UNSG32 RSVDx8088_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S2_LRCKCntl;
            struct w32Gbl_I2S2_LRCKCntl;
          };
    #define     w32Gbl_I2S2_BCLKCntl                           {\
            UNSG32 uI2S2_BCLKCntl_PU_EN                        :  1;\
            UNSG32 uI2S2_BCLKCntl_PD_EN                        :  1;\
            UNSG32 uI2S2_BCLKCntl_SLP_DI                       :  1;\
            UNSG32 RSVDx808C_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S2_BCLKCntl;
            struct w32Gbl_I2S2_BCLKCntl;
          };
    #define     w32Gbl_I2S2_DI_0Cntl                           {\
            UNSG32 uI2S2_DI_0Cntl_PU_EN                        :  1;\
            UNSG32 uI2S2_DI_0Cntl_PD_EN                        :  1;\
            UNSG32 uI2S2_DI_0Cntl_SLP_DI                       :  1;\
            UNSG32 RSVDx8090_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_I2S2_DI_0Cntl;
            struct w32Gbl_I2S2_DI_0Cntl;
          };
    #define     w32Gbl_SPDIFOCntl                              {\
            UNSG32 uSPDIFOCntl_PU_EN                           :  1;\
            UNSG32 uSPDIFOCntl_PD_EN                           :  1;\
            UNSG32 uSPDIFOCntl_SLP_DI                          :  1;\
            UNSG32 RSVDx8094_b3                                : 29;\
          }
    union { UNSG32 u32Gbl_SPDIFOCntl;
            struct w32Gbl_SPDIFOCntl;
          };
    } SIE_Gbl;
    typedef union  T32Gbl_pinMux
          { UNSG32 u32;
            struct w32Gbl_pinMux;
                 } T32Gbl_pinMux;
    typedef union  T32Gbl_pinMux1
          { UNSG32 u32;
            struct w32Gbl_pinMux1;
                 } T32Gbl_pinMux1;
    typedef union  T32Gbl_pinMux2
          { UNSG32 u32;
            struct w32Gbl_pinMux2;
                 } T32Gbl_pinMux2;
    typedef union  T32Gbl_bootStrap
          { UNSG32 u32;
            struct w32Gbl_bootStrap;
                 } T32Gbl_bootStrap;
    typedef union  T32Gbl_anaGrpCtl
          { UNSG32 u32;
            struct w32Gbl_anaGrpCtl;
                 } T32Gbl_anaGrpCtl;
    typedef union  T32Gbl_sysPllCtl
          { UNSG32 u32;
            struct w32Gbl_sysPllCtl;
                 } T32Gbl_sysPllCtl;
    typedef union  T32Gbl_sysPllCtl1
          { UNSG32 u32;
            struct w32Gbl_sysPllCtl1;
                 } T32Gbl_sysPllCtl1;
    typedef union  T32Gbl_sysPllCtl2
          { UNSG32 u32;
            struct w32Gbl_sysPllCtl2;
                 } T32Gbl_sysPllCtl2;
    typedef union  T32Gbl_sysPllCtl3
          { UNSG32 u32;
            struct w32Gbl_sysPllCtl3;
                 } T32Gbl_sysPllCtl3;
    typedef union  T32Gbl_sysPllCtl4
          { UNSG32 u32;
            struct w32Gbl_sysPllCtl4;
                 } T32Gbl_sysPllCtl4;
    typedef union  T32Gbl_memPllCtl
          { UNSG32 u32;
            struct w32Gbl_memPllCtl;
                 } T32Gbl_memPllCtl;
    typedef union  T32Gbl_memPllCtl1
          { UNSG32 u32;
            struct w32Gbl_memPllCtl1;
                 } T32Gbl_memPllCtl1;
    typedef union  T32Gbl_memPllCtl2
          { UNSG32 u32;
            struct w32Gbl_memPllCtl2;
                 } T32Gbl_memPllCtl2;
    typedef union  T32Gbl_memPllCtl3
          { UNSG32 u32;
            struct w32Gbl_memPllCtl3;
                 } T32Gbl_memPllCtl3;
    typedef union  T32Gbl_memPllCtl4
          { UNSG32 u32;
            struct w32Gbl_memPllCtl4;
                 } T32Gbl_memPllCtl4;
    typedef union  T32Gbl_cpuPllCtl
          { UNSG32 u32;
            struct w32Gbl_cpuPllCtl;
                 } T32Gbl_cpuPllCtl;
    typedef union  T32Gbl_cpuPllCtl1
          { UNSG32 u32;
            struct w32Gbl_cpuPllCtl1;
                 } T32Gbl_cpuPllCtl1;
    typedef union  T32Gbl_cpuPllCtl2
          { UNSG32 u32;
            struct w32Gbl_cpuPllCtl2;
                 } T32Gbl_cpuPllCtl2;
    typedef union  T32Gbl_cpuPllCtl3
          { UNSG32 u32;
            struct w32Gbl_cpuPllCtl3;
                 } T32Gbl_cpuPllCtl3;
    typedef union  T32Gbl_cpuPllCtl4
          { UNSG32 u32;
            struct w32Gbl_cpuPllCtl4;
                 } T32Gbl_cpuPllCtl4;
    typedef union  T32Gbl_avPllCtl
          { UNSG32 u32;
            struct w32Gbl_avPllCtl;
                 } T32Gbl_avPllCtl;
    typedef union  T32Gbl_avPllCtl1
          { UNSG32 u32;
            struct w32Gbl_avPllCtl1;
                 } T32Gbl_avPllCtl1;
    typedef union  T32Gbl_avPllCtl2
          { UNSG32 u32;
            struct w32Gbl_avPllCtl2;
                 } T32Gbl_avPllCtl2;
    typedef union  T32Gbl_avPllCtl3
          { UNSG32 u32;
            struct w32Gbl_avPllCtl3;
                 } T32Gbl_avPllCtl3;
    typedef union  T32Gbl_avPllCtl4
          { UNSG32 u32;
            struct w32Gbl_avPllCtl4;
                 } T32Gbl_avPllCtl4;
    typedef union  T32Gbl_avPllCtl5
          { UNSG32 u32;
            struct w32Gbl_avPllCtl5;
                 } T32Gbl_avPllCtl5;
    typedef union  T32Gbl_avPllCtl6
          { UNSG32 u32;
            struct w32Gbl_avPllCtl6;
                 } T32Gbl_avPllCtl6;
    typedef union  T32Gbl_avPllCtl7
          { UNSG32 u32;
            struct w32Gbl_avPllCtl7;
                 } T32Gbl_avPllCtl7;
    typedef union  T32Gbl_avPllCtl8
          { UNSG32 u32;
            struct w32Gbl_avPllCtl8;
                 } T32Gbl_avPllCtl8;
    typedef union  T32Gbl_avPllCtl9
          { UNSG32 u32;
            struct w32Gbl_avPllCtl9;
                 } T32Gbl_avPllCtl9;
    typedef union  T32Gbl_avPllCtl10
          { UNSG32 u32;
            struct w32Gbl_avPllCtl10;
                 } T32Gbl_avPllCtl10;
    typedef union  T32Gbl_avPllCtl11
          { UNSG32 u32;
            struct w32Gbl_avPllCtl11;
                 } T32Gbl_avPllCtl11;
    typedef union  T32Gbl_avPllCtl12
          { UNSG32 u32;
            struct w32Gbl_avPllCtl12;
                 } T32Gbl_avPllCtl12;
    typedef union  T32Gbl_avPllCtl13
          { UNSG32 u32;
            struct w32Gbl_avPllCtl13;
                 } T32Gbl_avPllCtl13;
    typedef union  T32Gbl_avPllCtl14
          { UNSG32 u32;
            struct w32Gbl_avPllCtl14;
                 } T32Gbl_avPllCtl14;
    typedef union  T32Gbl_avPllCtl15
          { UNSG32 u32;
            struct w32Gbl_avPllCtl15;
                 } T32Gbl_avPllCtl15;
    typedef union  T32Gbl_avPllCtl16
          { UNSG32 u32;
            struct w32Gbl_avPllCtl16;
                 } T32Gbl_avPllCtl16;
    typedef union  T32Gbl_avPllCtl17
          { UNSG32 u32;
            struct w32Gbl_avPllCtl17;
                 } T32Gbl_avPllCtl17;
    typedef union  T32Gbl_avPllCtl18
          { UNSG32 u32;
            struct w32Gbl_avPllCtl18;
                 } T32Gbl_avPllCtl18;
    typedef union  T32Gbl_avPllCtl19
          { UNSG32 u32;
            struct w32Gbl_avPllCtl19;
                 } T32Gbl_avPllCtl19;
    typedef union  T32Gbl_avPllCtl20
          { UNSG32 u32;
            struct w32Gbl_avPllCtl20;
                 } T32Gbl_avPllCtl20;
    typedef union  T32Gbl_avPllCtl21
          { UNSG32 u32;
            struct w32Gbl_avPllCtl21;
                 } T32Gbl_avPllCtl21;
    typedef union  T32Gbl_avPllCtl22
          { UNSG32 u32;
            struct w32Gbl_avPllCtl22;
                 } T32Gbl_avPllCtl22;
    typedef union  T32Gbl_avPllCtl23
          { UNSG32 u32;
            struct w32Gbl_avPllCtl23;
                 } T32Gbl_avPllCtl23;
    typedef union  T32Gbl_avPllCtl24
          { UNSG32 u32;
            struct w32Gbl_avPllCtl24;
                 } T32Gbl_avPllCtl24;
    typedef union  T32Gbl_avPllCtl25
          { UNSG32 u32;
            struct w32Gbl_avPllCtl25;
                 } T32Gbl_avPllCtl25;
    typedef union  T32Gbl_avPllCtl26
          { UNSG32 u32;
            struct w32Gbl_avPllCtl26;
                 } T32Gbl_avPllCtl26;
    typedef union  T32Gbl_avPllCtl27
          { UNSG32 u32;
            struct w32Gbl_avPllCtl27;
                 } T32Gbl_avPllCtl27;
    typedef union  T32Gbl_avPllCtl28
          { UNSG32 u32;
            struct w32Gbl_avPllCtl28;
                 } T32Gbl_avPllCtl28;
    typedef union  T32Gbl_avPllCtl29
          { UNSG32 u32;
            struct w32Gbl_avPllCtl29;
                 } T32Gbl_avPllCtl29;
    typedef union  T32Gbl_avPllCtl30
          { UNSG32 u32;
            struct w32Gbl_avPllCtl30;
                 } T32Gbl_avPllCtl30;
    typedef union  T32Gbl_avPllCtl31
          { UNSG32 u32;
            struct w32Gbl_avPllCtl31;
                 } T32Gbl_avPllCtl31;
    typedef union  T32Gbl_avPllCtl32
          { UNSG32 u32;
            struct w32Gbl_avPllCtl32;
                 } T32Gbl_avPllCtl32;
    typedef union  T32Gbl_avPllCtl33
          { UNSG32 u32;
            struct w32Gbl_avPllCtl33;
                 } T32Gbl_avPllCtl33;
    typedef union  T32Gbl_avPllCtl34
          { UNSG32 u32;
            struct w32Gbl_avPllCtl34;
                 } T32Gbl_avPllCtl34;
    typedef union  T32Gbl_avPllCtl35
          { UNSG32 u32;
            struct w32Gbl_avPllCtl35;
                 } T32Gbl_avPllCtl35;
    typedef union  T32Gbl_avPllCtl36
          { UNSG32 u32;
            struct w32Gbl_avPllCtl36;
                 } T32Gbl_avPllCtl36;
    typedef union  T32Gbl_avPllCtl37
          { UNSG32 u32;
            struct w32Gbl_avPllCtl37;
                 } T32Gbl_avPllCtl37;
    typedef union  T32Gbl_avPllCtl38
          { UNSG32 u32;
            struct w32Gbl_avPllCtl38;
                 } T32Gbl_avPllCtl38;
    typedef union  T32Gbl_avPllCtl39
          { UNSG32 u32;
            struct w32Gbl_avPllCtl39;
                 } T32Gbl_avPllCtl39;
    typedef union  T32Gbl_avPllCtl40
          { UNSG32 u32;
            struct w32Gbl_avPllCtl40;
                 } T32Gbl_avPllCtl40;
    typedef union  T32Gbl_avPllCtl41
          { UNSG32 u32;
            struct w32Gbl_avPllCtl41;
                 } T32Gbl_avPllCtl41;
    typedef union  T32Gbl_avPllCtl42
          { UNSG32 u32;
            struct w32Gbl_avPllCtl42;
                 } T32Gbl_avPllCtl42;
    typedef union  T32Gbl_avPllCtl43
          { UNSG32 u32;
            struct w32Gbl_avPllCtl43;
                 } T32Gbl_avPllCtl43;
    typedef union  T32Gbl_avPllCtl44
          { UNSG32 u32;
            struct w32Gbl_avPllCtl44;
                 } T32Gbl_avPllCtl44;
    typedef union  T32Gbl_avPllCtl45
          { UNSG32 u32;
            struct w32Gbl_avPllCtl45;
                 } T32Gbl_avPllCtl45;
    typedef union  T32Gbl_avPllCtl46
          { UNSG32 u32;
            struct w32Gbl_avPllCtl46;
                 } T32Gbl_avPllCtl46;
    typedef union  T32Gbl_avPllCtl47
          { UNSG32 u32;
            struct w32Gbl_avPllCtl47;
                 } T32Gbl_avPllCtl47;
    typedef union  T32Gbl_avPllCtl48
          { UNSG32 u32;
            struct w32Gbl_avPllCtl48;
                 } T32Gbl_avPllCtl48;
    typedef union  T32Gbl_avPllCtl49
          { UNSG32 u32;
            struct w32Gbl_avPllCtl49;
                 } T32Gbl_avPllCtl49;
    typedef union  T32Gbl_avPllCtl50
          { UNSG32 u32;
            struct w32Gbl_avPllCtl50;
                 } T32Gbl_avPllCtl50;
    typedef union  T32Gbl_avPllCtl51
          { UNSG32 u32;
            struct w32Gbl_avPllCtl51;
                 } T32Gbl_avPllCtl51;
    typedef union  T32Gbl_avPllCtl52
          { UNSG32 u32;
            struct w32Gbl_avPllCtl52;
                 } T32Gbl_avPllCtl52;
    typedef union  T32Gbl_avPllCtl53
          { UNSG32 u32;
            struct w32Gbl_avPllCtl53;
                 } T32Gbl_avPllCtl53;
    typedef union  T32Gbl_avPllCtl54
          { UNSG32 u32;
            struct w32Gbl_avPllCtl54;
                 } T32Gbl_avPllCtl54;
    typedef union  T32Gbl_avPllCtl55
          { UNSG32 u32;
            struct w32Gbl_avPllCtl55;
                 } T32Gbl_avPllCtl55;
    typedef union  T32Gbl_avPllCtl56
          { UNSG32 u32;
            struct w32Gbl_avPllCtl56;
                 } T32Gbl_avPllCtl56;
    typedef union  T32Gbl_avPllCtl57
          { UNSG32 u32;
            struct w32Gbl_avPllCtl57;
                 } T32Gbl_avPllCtl57;
    typedef union  T32Gbl_avPllCtl58
          { UNSG32 u32;
            struct w32Gbl_avPllCtl58;
                 } T32Gbl_avPllCtl58;
    typedef union  T32Gbl_avPllCtl59
          { UNSG32 u32;
            struct w32Gbl_avPllCtl59;
                 } T32Gbl_avPllCtl59;
    typedef union  T32Gbl_avPllCtl60
          { UNSG32 u32;
            struct w32Gbl_avPllCtl60;
                 } T32Gbl_avPllCtl60;
    typedef union  T32Gbl_avPllCtl61
          { UNSG32 u32;
            struct w32Gbl_avPllCtl61;
                 } T32Gbl_avPllCtl61;
    typedef union  T32Gbl_avPllCtl62
          { UNSG32 u32;
            struct w32Gbl_avPllCtl62;
                 } T32Gbl_avPllCtl62;
    typedef union  T32Gbl_pllStatus
          { UNSG32 u32;
            struct w32Gbl_pllStatus;
                 } T32Gbl_pllStatus;
    typedef union  T32Gbl_clkEnable
          { UNSG32 u32;
            struct w32Gbl_clkEnable;
                 } T32Gbl_clkEnable;
    typedef union  T32Gbl_clkSelect
          { UNSG32 u32;
            struct w32Gbl_clkSelect;
                 } T32Gbl_clkSelect;
    typedef union  T32Gbl_clkSelect1
          { UNSG32 u32;
            struct w32Gbl_clkSelect1;
                 } T32Gbl_clkSelect1;
    typedef union  T32Gbl_clkSelect2
          { UNSG32 u32;
            struct w32Gbl_clkSelect2;
                 } T32Gbl_clkSelect2;
    typedef union  T32Gbl_clkSelect3
          { UNSG32 u32;
            struct w32Gbl_clkSelect3;
                 } T32Gbl_clkSelect3;
    typedef union  T32Gbl_ClkSwitch
          { UNSG32 u32;
            struct w32Gbl_ClkSwitch;
                 } T32Gbl_ClkSwitch;
    typedef union  T32Gbl_ClkSwitch1
          { UNSG32 u32;
            struct w32Gbl_ClkSwitch1;
                 } T32Gbl_ClkSwitch1;
    typedef union  T32Gbl_PadSelect
          { UNSG32 u32;
            struct w32Gbl_PadSelect;
                 } T32Gbl_PadSelect;
    typedef union  T32Gbl_PadSelect1
          { UNSG32 u32;
            struct w32Gbl_PadSelect1;
                 } T32Gbl_PadSelect1;
    typedef union  T32Gbl_PadSelect2
          { UNSG32 u32;
            struct w32Gbl_PadSelect2;
                 } T32Gbl_PadSelect2;
    typedef union  T32Gbl_ResetTrigger
          { UNSG32 u32;
            struct w32Gbl_ResetTrigger;
                 } T32Gbl_ResetTrigger;
    typedef union  T32Gbl_ResetStatus
          { UNSG32 u32;
            struct w32Gbl_ResetStatus;
                 } T32Gbl_ResetStatus;
    typedef union  T32Gbl_ResetStatus1
          { UNSG32 u32;
            struct w32Gbl_ResetStatus1;
                 } T32Gbl_ResetStatus1;
    typedef union  T32Gbl_sw_generic0
          { UNSG32 u32;
            struct w32Gbl_sw_generic0;
                 } T32Gbl_sw_generic0;
    typedef union  T32Gbl_sw_generic1
          { UNSG32 u32;
            struct w32Gbl_sw_generic1;
                 } T32Gbl_sw_generic1;
    typedef union  T32Gbl_sw_generic2
          { UNSG32 u32;
            struct w32Gbl_sw_generic2;
                 } T32Gbl_sw_generic2;
    typedef union  T32Gbl_sw_generic3
          { UNSG32 u32;
            struct w32Gbl_sw_generic3;
                 } T32Gbl_sw_generic3;
    typedef union  T32Gbl_ChipCntl0
          { UNSG32 u32;
            struct w32Gbl_ChipCntl0;
                 } T32Gbl_ChipCntl0;
    typedef union  T32Gbl_ChipCntl1
          { UNSG32 u32;
            struct w32Gbl_ChipCntl1;
                 } T32Gbl_ChipCntl1;
    typedef union  T32Gbl_ChipCntl11
          { UNSG32 u32;
            struct w32Gbl_ChipCntl11;
                 } T32Gbl_ChipCntl11;
    typedef union  T32Gbl_ChipCntl12
          { UNSG32 u32;
            struct w32Gbl_ChipCntl12;
                 } T32Gbl_ChipCntl12;
    typedef union  T32Gbl_RWTC_avio31to0
          { UNSG32 u32;
            struct w32Gbl_RWTC_avio31to0;
                 } T32Gbl_RWTC_avio31to0;
    typedef union  T32Gbl_RWTC_avio41to32
          { UNSG32 u32;
            struct w32Gbl_RWTC_avio41to32;
                 } T32Gbl_RWTC_avio41to32;
    typedef union  T32Gbl_RWTC_gfx2D31to0
          { UNSG32 u32;
            struct w32Gbl_RWTC_gfx2D31to0;
                 } T32Gbl_RWTC_gfx2D31to0;
    typedef union  T32Gbl_RWTC_gfx2D41to32
          { UNSG32 u32;
            struct w32Gbl_RWTC_gfx2D41to32;
                 } T32Gbl_RWTC_gfx2D41to32;
    typedef union  T32Gbl_RWTC_gfx3D31to0
          { UNSG32 u32;
            struct w32Gbl_RWTC_gfx3D31to0;
                 } T32Gbl_RWTC_gfx3D31to0;
    typedef union  T32Gbl_RWTC_gfx3D41to32
          { UNSG32 u32;
            struct w32Gbl_RWTC_gfx3D41to32;
                 } T32Gbl_RWTC_gfx3D41to32;
    typedef union  T32Gbl_RWTC_soc31to0
          { UNSG32 u32;
            struct w32Gbl_RWTC_soc31to0;
                 } T32Gbl_RWTC_soc31to0;
    typedef union  T32Gbl_RWTC_soc41to32
          { UNSG32 u32;
            struct w32Gbl_RWTC_soc41to32;
                 } T32Gbl_RWTC_soc41to32;
    typedef union  T32Gbl_RWTC_vPro31to0
          { UNSG32 u32;
            struct w32Gbl_RWTC_vPro31to0;
                 } T32Gbl_RWTC_vPro31to0;
    typedef union  T32Gbl_RWTC_vPro41to32
          { UNSG32 u32;
            struct w32Gbl_RWTC_vPro41to32;
                 } T32Gbl_RWTC_vPro41to32;
    typedef union  T32Gbl_ProductId
          { UNSG32 u32;
            struct w32Gbl_ProductId;
                 } T32Gbl_ProductId;
    typedef union  T32Gbl_ProductId_ext
          { UNSG32 u32;
            struct w32Gbl_ProductId_ext;
                 } T32Gbl_ProductId_ext;
    typedef union  T32Gbl_FPGAR
          { UNSG32 u32;
            struct w32Gbl_FPGAR;
                 } T32Gbl_FPGAR;
    typedef union  T32Gbl_FPGARW
          { UNSG32 u32;
            struct w32Gbl_FPGARW;
                 } T32Gbl_FPGARW;
    typedef union  T32Gbl_RingOscCtl
          { UNSG32 u32;
            struct w32Gbl_RingOscCtl;
                 } T32Gbl_RingOscCtl;
    typedef union  T32Gbl_PLLBypsBootStrapEn
          { UNSG32 u32;
            struct w32Gbl_PLLBypsBootStrapEn;
                 } T32Gbl_PLLBypsBootStrapEn;
    typedef union  T32Gbl_IO_CALIBRATE_IN
          { UNSG32 u32;
            struct w32Gbl_IO_CALIBRATE_IN;
                 } T32Gbl_IO_CALIBRATE_IN;
    typedef union  T32Gbl_IO_CALIBRATE_IN1
          { UNSG32 u32;
            struct w32Gbl_IO_CALIBRATE_IN1;
                 } T32Gbl_IO_CALIBRATE_IN1;
    typedef union  T32Gbl_IO_CALIBRATE_IN2
          { UNSG32 u32;
            struct w32Gbl_IO_CALIBRATE_IN2;
                 } T32Gbl_IO_CALIBRATE_IN2;
    typedef union  T32Gbl_IO_CALIBRATE_IN3
          { UNSG32 u32;
            struct w32Gbl_IO_CALIBRATE_IN3;
                 } T32Gbl_IO_CALIBRATE_IN3;
    typedef union  T32Gbl_IO_CALBRATE_OUT
          { UNSG32 u32;
            struct w32Gbl_IO_CALBRATE_OUT;
                 } T32Gbl_IO_CALBRATE_OUT;
    typedef union  T32Gbl_SECURE_SCAN_EN
          { UNSG32 u32;
            struct w32Gbl_SECURE_SCAN_EN;
                 } T32Gbl_SECURE_SCAN_EN;
    typedef union  T32Gbl_NandWPn
          { UNSG32 u32;
            struct w32Gbl_NandWPn;
                 } T32Gbl_NandWPn;
    typedef union  T32Gbl_RingCntCntl
          { UNSG32 u32;
            struct w32Gbl_RingCntCntl;
                 } T32Gbl_RingCntCntl;
    typedef union  T32Gbl_gfx3DCoreClkCtrl
          { UNSG32 u32;
            struct w32Gbl_gfx3DCoreClkCtrl;
                 } T32Gbl_gfx3DCoreClkCtrl;
    typedef union  T32Gbl_gfx3DSysClkCtrl
          { UNSG32 u32;
            struct w32Gbl_gfx3DSysClkCtrl;
                 } T32Gbl_gfx3DSysClkCtrl;
    typedef union  T32Gbl_arcRefClkCtrl
          { UNSG32 u32;
            struct w32Gbl_arcRefClkCtrl;
                 } T32Gbl_arcRefClkCtrl;
    typedef union  T32Gbl_vipClkCtrl
          { UNSG32 u32;
            struct w32Gbl_vipClkCtrl;
                 } T32Gbl_vipClkCtrl;
    typedef union  T32Gbl_sdioXinClkCtrl
          { UNSG32 u32;
            struct w32Gbl_sdioXinClkCtrl;
                 } T32Gbl_sdioXinClkCtrl;
    typedef union  T32Gbl_sdio1XinClkCtrl
          { UNSG32 u32;
            struct w32Gbl_sdio1XinClkCtrl;
                 } T32Gbl_sdio1XinClkCtrl;
    typedef union  T32Gbl_gfx3DExtraClkCtrl
          { UNSG32 u32;
            struct w32Gbl_gfx3DExtraClkCtrl;
                 } T32Gbl_gfx3DExtraClkCtrl;
    typedef union  T32Gbl_gfx3DReset
          { UNSG32 u32;
            struct w32Gbl_gfx3DReset;
                 } T32Gbl_gfx3DReset;
    typedef union  T32Gbl_gc360ClkCtrl
          { UNSG32 u32;
            struct w32Gbl_gc360ClkCtrl;
                 } T32Gbl_gc360ClkCtrl;
    typedef union  T32Gbl_sdioDllMstRef
          { UNSG32 u32;
            struct w32Gbl_sdioDllMstRef;
                 } T32Gbl_sdioDllMstRef;
    typedef union  T32Gbl_sdioDllMstCtrl
          { UNSG32 u32;
            struct w32Gbl_sdioDllMstCtrl;
                 } T32Gbl_sdioDllMstCtrl;
    typedef union  T32Gbl_sdioDllMstCtrl1
          { UNSG32 u32;
            struct w32Gbl_sdioDllMstCtrl1;
                 } T32Gbl_sdioDllMstCtrl1;
    typedef union  T32Gbl_sdioDllMstStatus
          { UNSG32 u32;
            struct w32Gbl_sdioDllMstStatus;
                 } T32Gbl_sdioDllMstStatus;
    typedef union  T32Gbl_sdioDllMstStatus1
          { UNSG32 u32;
            struct w32Gbl_sdioDllMstStatus1;
                 } T32Gbl_sdioDllMstStatus1;
    typedef union  T32Gbl_sdioPortSel
          { UNSG32 u32;
            struct w32Gbl_sdioPortSel;
                 } T32Gbl_sdioPortSel;
    typedef union  T32Gbl_gc360Reset
          { UNSG32 u32;
            struct w32Gbl_gc360Reset;
                 } T32Gbl_gc360Reset;
    typedef union  T32Gbl_SpdifRxReset
          { UNSG32 u32;
            struct w32Gbl_SpdifRxReset;
                 } T32Gbl_SpdifRxReset;
    typedef union  T32Gbl_gfx3DDisRamClkGate
          { UNSG32 u32;
            struct w32Gbl_gfx3DDisRamClkGate;
                 } T32Gbl_gfx3DDisRamClkGate;
    typedef union  T32Gbl_gfx3DResetStatus
          { UNSG32 u32;
            struct w32Gbl_gfx3DResetStatus;
                 } T32Gbl_gfx3DResetStatus;
    typedef union  T32Gbl_gc360DisRCG
          { UNSG32 u32;
            struct w32Gbl_gc360DisRCG;
                 } T32Gbl_gc360DisRCG;
    typedef union  T32Gbl_gc360ResetStatus
          { UNSG32 u32;
            struct w32Gbl_gc360ResetStatus;
                 } T32Gbl_gc360ResetStatus;
    typedef union  T32Gbl_SpdifRxResetStatus
          { UNSG32 u32;
            struct w32Gbl_SpdifRxResetStatus;
                 } T32Gbl_SpdifRxResetStatus;
    typedef union  T32Gbl_DroEnable
          { UNSG32 u32;
            struct w32Gbl_DroEnable;
                 } T32Gbl_DroEnable;
    typedef union  T32Gbl_DroCounter
          { UNSG32 u32;
            struct w32Gbl_DroCounter;
                 } T32Gbl_DroCounter;
    typedef union  T32Gbl_DroDone
          { UNSG32 u32;
            struct w32Gbl_DroDone;
                 } T32Gbl_DroDone;
    typedef union  T32Gbl_INT_ID
          { UNSG32 u32;
            struct w32Gbl_INT_ID;
                 } T32Gbl_INT_ID;
    typedef union  T32Gbl_stickyResetN
          { UNSG32 u32;
            struct w32Gbl_stickyResetN;
                 } T32Gbl_stickyResetN;
    typedef union  T32Gbl_gethRgmii_dll
          { UNSG32 u32;
            struct w32Gbl_gethRgmii_dll;
                 } T32Gbl_gethRgmii_dll;
    typedef union  T32Gbl_funcSel
          { UNSG32 u32;
            struct w32Gbl_funcSel;
                 } T32Gbl_funcSel;
    typedef union  T32Gbl_chipCntl
          { UNSG32 u32;
            struct w32Gbl_chipCntl;
                 } T32Gbl_chipCntl;
    typedef union  T32Gbl_bootStrapEn
          { UNSG32 u32;
            struct w32Gbl_bootStrapEn;
                 } T32Gbl_bootStrapEn;
    typedef union  T32Gbl_axiClkEn
          { UNSG32 u32;
            struct w32Gbl_axiClkEn;
                 } T32Gbl_axiClkEn;
    typedef union  T32Gbl_ahbClkEn
          { UNSG32 u32;
            struct w32Gbl_ahbClkEn;
                 } T32Gbl_ahbClkEn;
    typedef union  T32Gbl_SPI1_SS0nCntl
          { UNSG32 u32;
            struct w32Gbl_SPI1_SS0nCntl;
                 } T32Gbl_SPI1_SS0nCntl;
    typedef union  T32Gbl_SPI1_SS1nCntl
          { UNSG32 u32;
            struct w32Gbl_SPI1_SS1nCntl;
                 } T32Gbl_SPI1_SS1nCntl;
    typedef union  T32Gbl_SPI1_SS2nCntl
          { UNSG32 u32;
            struct w32Gbl_SPI1_SS2nCntl;
                 } T32Gbl_SPI1_SS2nCntl;
    typedef union  T32Gbl_SPI1_SCLKCntl
          { UNSG32 u32;
            struct w32Gbl_SPI1_SCLKCntl;
                 } T32Gbl_SPI1_SCLKCntl;
    typedef union  T32Gbl_SPI1_SDOCntl
          { UNSG32 u32;
            struct w32Gbl_SPI1_SDOCntl;
                 } T32Gbl_SPI1_SDOCntl;
    typedef union  T32Gbl_SPI1_SDICntl
          { UNSG32 u32;
            struct w32Gbl_SPI1_SDICntl;
                 } T32Gbl_SPI1_SDICntl;
    typedef union  T32Gbl_URT0_RXDCntl
          { UNSG32 u32;
            struct w32Gbl_URT0_RXDCntl;
                 } T32Gbl_URT0_RXDCntl;
    typedef union  T32Gbl_URT0_TXDCntl
          { UNSG32 u32;
            struct w32Gbl_URT0_TXDCntl;
                 } T32Gbl_URT0_TXDCntl;
    typedef union  T32Gbl_DVIO0Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO0Cntl;
                 } T32Gbl_DVIO0Cntl;
    typedef union  T32Gbl_DVIO1Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO1Cntl;
                 } T32Gbl_DVIO1Cntl;
    typedef union  T32Gbl_DVIO2Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO2Cntl;
                 } T32Gbl_DVIO2Cntl;
    typedef union  T32Gbl_DVIO3Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO3Cntl;
                 } T32Gbl_DVIO3Cntl;
    typedef union  T32Gbl_DVIO4Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO4Cntl;
                 } T32Gbl_DVIO4Cntl;
    typedef union  T32Gbl_DVIO5Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO5Cntl;
                 } T32Gbl_DVIO5Cntl;
    typedef union  T32Gbl_DVIO6Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO6Cntl;
                 } T32Gbl_DVIO6Cntl;
    typedef union  T32Gbl_DVIO7Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO7Cntl;
                 } T32Gbl_DVIO7Cntl;
    typedef union  T32Gbl_DVIO8Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO8Cntl;
                 } T32Gbl_DVIO8Cntl;
    typedef union  T32Gbl_DVIO9Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO9Cntl;
                 } T32Gbl_DVIO9Cntl;
    typedef union  T32Gbl_DVIO10Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO10Cntl;
                 } T32Gbl_DVIO10Cntl;
    typedef union  T32Gbl_DVIO11Cntl
          { UNSG32 u32;
            struct w32Gbl_DVIO11Cntl;
                 } T32Gbl_DVIO11Cntl;
    typedef union  T32Gbl_DV0_CLKCntl
          { UNSG32 u32;
            struct w32Gbl_DV0_CLKCntl;
                 } T32Gbl_DV0_CLKCntl;
    typedef union  T32Gbl_DV0_HSCntl
          { UNSG32 u32;
            struct w32Gbl_DV0_HSCntl;
                 } T32Gbl_DV0_HSCntl;
    typedef union  T32Gbl_DV0_VSCntl
          { UNSG32 u32;
            struct w32Gbl_DV0_VSCntl;
                 } T32Gbl_DV0_VSCntl;
    typedef union  T32Gbl_DV0_FIDCntl
          { UNSG32 u32;
            struct w32Gbl_DV0_FIDCntl;
                 } T32Gbl_DV0_FIDCntl;
    typedef union  T32Gbl_I2S0_BCLKCntl
          { UNSG32 u32;
            struct w32Gbl_I2S0_BCLKCntl;
                 } T32Gbl_I2S0_BCLKCntl;
    typedef union  T32Gbl_I2S0_LRCKCntl
          { UNSG32 u32;
            struct w32Gbl_I2S0_LRCKCntl;
                 } T32Gbl_I2S0_LRCKCntl;
    typedef union  T32Gbl_I2S0_DO0Cntl
          { UNSG32 u32;
            struct w32Gbl_I2S0_DO0Cntl;
                 } T32Gbl_I2S0_DO0Cntl;
    typedef union  T32Gbl_I2S0_DO1Cntl
          { UNSG32 u32;
            struct w32Gbl_I2S0_DO1Cntl;
                 } T32Gbl_I2S0_DO1Cntl;
    typedef union  T32Gbl_I2S0_DO2Cntl
          { UNSG32 u32;
            struct w32Gbl_I2S0_DO2Cntl;
                 } T32Gbl_I2S0_DO2Cntl;
    typedef union  T32Gbl_I2S0_DO3Cntl
          { UNSG32 u32;
            struct w32Gbl_I2S0_DO3Cntl;
                 } T32Gbl_I2S0_DO3Cntl;
    typedef union  T32Gbl_SPDIFICntl
          { UNSG32 u32;
            struct w32Gbl_SPDIFICntl;
                 } T32Gbl_SPDIFICntl;
    typedef union  T32Gbl_I2S1_LRCKCntl
          { UNSG32 u32;
            struct w32Gbl_I2S1_LRCKCntl;
                 } T32Gbl_I2S1_LRCKCntl;
    typedef union  T32Gbl_I2S1_BCLKCntl
          { UNSG32 u32;
            struct w32Gbl_I2S1_BCLKCntl;
                 } T32Gbl_I2S1_BCLKCntl;
    typedef union  T32Gbl_I2S1_DOCntl
          { UNSG32 u32;
            struct w32Gbl_I2S1_DOCntl;
                 } T32Gbl_I2S1_DOCntl;
    typedef union  T32Gbl_I2S2_LRCKCntl
          { UNSG32 u32;
            struct w32Gbl_I2S2_LRCKCntl;
                 } T32Gbl_I2S2_LRCKCntl;
    typedef union  T32Gbl_I2S2_BCLKCntl
          { UNSG32 u32;
            struct w32Gbl_I2S2_BCLKCntl;
                 } T32Gbl_I2S2_BCLKCntl;
    typedef union  T32Gbl_I2S2_DI_0Cntl
          { UNSG32 u32;
            struct w32Gbl_I2S2_DI_0Cntl;
                 } T32Gbl_I2S2_DI_0Cntl;
    typedef union  T32Gbl_SPDIFOCntl
          { UNSG32 u32;
            struct w32Gbl_SPDIFOCntl;
                 } T32Gbl_SPDIFOCntl;
    typedef union  TGbl_pinMux
          { UNSG32 u32[3];
            struct {
            struct w32Gbl_pinMux;
            struct w32Gbl_pinMux1;
            struct w32Gbl_pinMux2;
                   };
                 } TGbl_pinMux;
    typedef union  TGbl_bootStrap
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_bootStrap;
                   };
                 } TGbl_bootStrap;
    typedef union  TGbl_anaGrpCtl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_anaGrpCtl;
                   };
                 } TGbl_anaGrpCtl;
    typedef union  TGbl_sysPllCtl
          { UNSG32 u32[5];
            struct {
            struct w32Gbl_sysPllCtl;
            struct w32Gbl_sysPllCtl1;
            struct w32Gbl_sysPllCtl2;
            struct w32Gbl_sysPllCtl3;
            struct w32Gbl_sysPllCtl4;
                   };
                 } TGbl_sysPllCtl;
    typedef union  TGbl_memPllCtl
          { UNSG32 u32[5];
            struct {
            struct w32Gbl_memPllCtl;
            struct w32Gbl_memPllCtl1;
            struct w32Gbl_memPllCtl2;
            struct w32Gbl_memPllCtl3;
            struct w32Gbl_memPllCtl4;
                   };
                 } TGbl_memPllCtl;
    typedef union  TGbl_cpuPllCtl
          { UNSG32 u32[5];
            struct {
            struct w32Gbl_cpuPllCtl;
            struct w32Gbl_cpuPllCtl1;
            struct w32Gbl_cpuPllCtl2;
            struct w32Gbl_cpuPllCtl3;
            struct w32Gbl_cpuPllCtl4;
                   };
                 } TGbl_cpuPllCtl;
    typedef union  TGbl_avPllCtl
          { UNSG32 u32[63];
            struct {
            struct w32Gbl_avPllCtl;
            struct w32Gbl_avPllCtl1;
            struct w32Gbl_avPllCtl2;
            struct w32Gbl_avPllCtl3;
            struct w32Gbl_avPllCtl4;
            struct w32Gbl_avPllCtl5;
            struct w32Gbl_avPllCtl6;
            struct w32Gbl_avPllCtl7;
            struct w32Gbl_avPllCtl8;
            struct w32Gbl_avPllCtl9;
            struct w32Gbl_avPllCtl10;
            struct w32Gbl_avPllCtl11;
            struct w32Gbl_avPllCtl12;
            struct w32Gbl_avPllCtl13;
            struct w32Gbl_avPllCtl14;
            struct w32Gbl_avPllCtl15;
            struct w32Gbl_avPllCtl16;
            struct w32Gbl_avPllCtl17;
            struct w32Gbl_avPllCtl18;
            struct w32Gbl_avPllCtl19;
            struct w32Gbl_avPllCtl20;
            struct w32Gbl_avPllCtl21;
            struct w32Gbl_avPllCtl22;
            struct w32Gbl_avPllCtl23;
            struct w32Gbl_avPllCtl24;
            struct w32Gbl_avPllCtl25;
            struct w32Gbl_avPllCtl26;
            struct w32Gbl_avPllCtl27;
            struct w32Gbl_avPllCtl28;
            struct w32Gbl_avPllCtl29;
            struct w32Gbl_avPllCtl30;
            struct w32Gbl_avPllCtl31;
            struct w32Gbl_avPllCtl32;
            struct w32Gbl_avPllCtl33;
            struct w32Gbl_avPllCtl34;
            struct w32Gbl_avPllCtl35;
            struct w32Gbl_avPllCtl36;
            struct w32Gbl_avPllCtl37;
            struct w32Gbl_avPllCtl38;
            struct w32Gbl_avPllCtl39;
            struct w32Gbl_avPllCtl40;
            struct w32Gbl_avPllCtl41;
            struct w32Gbl_avPllCtl42;
            struct w32Gbl_avPllCtl43;
            struct w32Gbl_avPllCtl44;
            struct w32Gbl_avPllCtl45;
            struct w32Gbl_avPllCtl46;
            struct w32Gbl_avPllCtl47;
            struct w32Gbl_avPllCtl48;
            struct w32Gbl_avPllCtl49;
            struct w32Gbl_avPllCtl50;
            struct w32Gbl_avPllCtl51;
            struct w32Gbl_avPllCtl52;
            struct w32Gbl_avPllCtl53;
            struct w32Gbl_avPllCtl54;
            struct w32Gbl_avPllCtl55;
            struct w32Gbl_avPllCtl56;
            struct w32Gbl_avPllCtl57;
            struct w32Gbl_avPllCtl58;
            struct w32Gbl_avPllCtl59;
            struct w32Gbl_avPllCtl60;
            struct w32Gbl_avPllCtl61;
            struct w32Gbl_avPllCtl62;
                   };
                 } TGbl_avPllCtl;
    typedef union  TGbl_pllStatus
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_pllStatus;
                   };
                 } TGbl_pllStatus;
    typedef union  TGbl_clkEnable
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_clkEnable;
                   };
                 } TGbl_clkEnable;
    typedef union  TGbl_clkSelect
          { UNSG32 u32[4];
            struct {
            struct w32Gbl_clkSelect;
            struct w32Gbl_clkSelect1;
            struct w32Gbl_clkSelect2;
            struct w32Gbl_clkSelect3;
                   };
                 } TGbl_clkSelect;
    typedef union  TGbl_ClkSwitch
          { UNSG32 u32[2];
            struct {
            struct w32Gbl_ClkSwitch;
            struct w32Gbl_ClkSwitch1;
                   };
                 } TGbl_ClkSwitch;
    typedef union  TGbl_PadSelect
          { UNSG32 u32[3];
            struct {
            struct w32Gbl_PadSelect;
            struct w32Gbl_PadSelect1;
            struct w32Gbl_PadSelect2;
                   };
                 } TGbl_PadSelect;
    typedef union  TGbl_ResetTrigger
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_ResetTrigger;
                   };
                 } TGbl_ResetTrigger;
    typedef union  TGbl_ResetStatus
          { UNSG32 u32[2];
            struct {
            struct w32Gbl_ResetStatus;
            struct w32Gbl_ResetStatus1;
                   };
                 } TGbl_ResetStatus;
    typedef union  TGbl_sw_generic0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sw_generic0;
                   };
                 } TGbl_sw_generic0;
    typedef union  TGbl_sw_generic1
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sw_generic1;
                   };
                 } TGbl_sw_generic1;
    typedef union  TGbl_sw_generic2
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sw_generic2;
                   };
                 } TGbl_sw_generic2;
    typedef union  TGbl_sw_generic3
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sw_generic3;
                   };
                 } TGbl_sw_generic3;
    typedef union  TGbl_ChipCntl0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_ChipCntl0;
                   };
                 } TGbl_ChipCntl0;
    typedef union  TGbl_ChipCntl1
          { UNSG32 u32[3];
            struct {
            struct w32Gbl_ChipCntl1;
            struct w32Gbl_ChipCntl11;
            struct w32Gbl_ChipCntl12;
                   };
                 } TGbl_ChipCntl1;
    typedef union  TGbl_RWTC_avio31to0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_avio31to0;
                   };
                 } TGbl_RWTC_avio31to0;
    typedef union  TGbl_RWTC_avio41to32
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_avio41to32;
                   };
                 } TGbl_RWTC_avio41to32;
    typedef union  TGbl_RWTC_gfx2D31to0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_gfx2D31to0;
                   };
                 } TGbl_RWTC_gfx2D31to0;
    typedef union  TGbl_RWTC_gfx2D41to32
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_gfx2D41to32;
                   };
                 } TGbl_RWTC_gfx2D41to32;
    typedef union  TGbl_RWTC_gfx3D31to0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_gfx3D31to0;
                   };
                 } TGbl_RWTC_gfx3D31to0;
    typedef union  TGbl_RWTC_gfx3D41to32
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_gfx3D41to32;
                   };
                 } TGbl_RWTC_gfx3D41to32;
    typedef union  TGbl_RWTC_soc31to0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_soc31to0;
                   };
                 } TGbl_RWTC_soc31to0;
    typedef union  TGbl_RWTC_soc41to32
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_soc41to32;
                   };
                 } TGbl_RWTC_soc41to32;
    typedef union  TGbl_RWTC_vPro31to0
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_vPro31to0;
                   };
                 } TGbl_RWTC_vPro31to0;
    typedef union  TGbl_RWTC_vPro41to32
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RWTC_vPro41to32;
                   };
                 } TGbl_RWTC_vPro41to32;
    typedef union  TGbl_ProductId
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_ProductId;
                   };
                 } TGbl_ProductId;
    typedef union  TGbl_ProductId_ext
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_ProductId_ext;
                   };
                 } TGbl_ProductId_ext;
    typedef union  TGbl_FPGAR
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_FPGAR;
                   };
                 } TGbl_FPGAR;
    typedef union  TGbl_FPGARW
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_FPGARW;
                   };
                 } TGbl_FPGARW;
    typedef union  TGbl_RingOscCtl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RingOscCtl;
                   };
                 } TGbl_RingOscCtl;
    typedef union  TGbl_PLLBypsBootStrapEn
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_PLLBypsBootStrapEn;
                   };
                 } TGbl_PLLBypsBootStrapEn;
    typedef union  TGbl_IO_CALIBRATE_IN
          { UNSG32 u32[4];
            struct {
            struct w32Gbl_IO_CALIBRATE_IN;
            struct w32Gbl_IO_CALIBRATE_IN1;
            struct w32Gbl_IO_CALIBRATE_IN2;
            struct w32Gbl_IO_CALIBRATE_IN3;
                   };
                 } TGbl_IO_CALIBRATE_IN;
    typedef union  TGbl_IO_CALBRATE_OUT
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_IO_CALBRATE_OUT;
                   };
                 } TGbl_IO_CALBRATE_OUT;
    typedef union  TGbl_SECURE_SCAN_EN
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SECURE_SCAN_EN;
                   };
                 } TGbl_SECURE_SCAN_EN;
    typedef union  TGbl_NandWPn
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_NandWPn;
                   };
                 } TGbl_NandWPn;
    typedef union  TGbl_RingCntCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_RingCntCntl;
                   };
                 } TGbl_RingCntCntl;
    typedef union  TGbl_gfx3DCoreClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gfx3DCoreClkCtrl;
                   };
                 } TGbl_gfx3DCoreClkCtrl;
    typedef union  TGbl_gfx3DSysClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gfx3DSysClkCtrl;
                   };
                 } TGbl_gfx3DSysClkCtrl;
    typedef union  TGbl_arcRefClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_arcRefClkCtrl;
                   };
                 } TGbl_arcRefClkCtrl;
    typedef union  TGbl_vipClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_vipClkCtrl;
                   };
                 } TGbl_vipClkCtrl;
    typedef union  TGbl_sdioXinClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sdioXinClkCtrl;
                   };
                 } TGbl_sdioXinClkCtrl;
    typedef union  TGbl_sdio1XinClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sdio1XinClkCtrl;
                   };
                 } TGbl_sdio1XinClkCtrl;
    typedef union  TGbl_gfx3DExtraClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gfx3DExtraClkCtrl;
                   };
                 } TGbl_gfx3DExtraClkCtrl;
    typedef union  TGbl_gfx3DReset
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gfx3DReset;
                   };
                 } TGbl_gfx3DReset;
    typedef union  TGbl_gc360ClkCtrl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gc360ClkCtrl;
                   };
                 } TGbl_gc360ClkCtrl;
    typedef union  TGbl_sdioDllMstRef
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sdioDllMstRef;
                   };
                 } TGbl_sdioDllMstRef;
    typedef union  TGbl_sdioDllMstCtrl
          { UNSG32 u32[2];
            struct {
            struct w32Gbl_sdioDllMstCtrl;
            struct w32Gbl_sdioDllMstCtrl1;
                   };
                 } TGbl_sdioDllMstCtrl;
    typedef union  TGbl_sdioDllMstStatus
          { UNSG32 u32[2];
            struct {
            struct w32Gbl_sdioDllMstStatus;
            struct w32Gbl_sdioDllMstStatus1;
                   };
                 } TGbl_sdioDllMstStatus;
    typedef union  TGbl_sdioPortSel
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_sdioPortSel;
                   };
                 } TGbl_sdioPortSel;
    typedef union  TGbl_gc360Reset
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gc360Reset;
                   };
                 } TGbl_gc360Reset;
    typedef union  TGbl_SpdifRxReset
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SpdifRxReset;
                   };
                 } TGbl_SpdifRxReset;
    typedef union  TGbl_gfx3DDisRamClkGate
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gfx3DDisRamClkGate;
                   };
                 } TGbl_gfx3DDisRamClkGate;
    typedef union  TGbl_gfx3DResetStatus
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gfx3DResetStatus;
                   };
                 } TGbl_gfx3DResetStatus;
    typedef union  TGbl_gc360DisRCG
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gc360DisRCG;
                   };
                 } TGbl_gc360DisRCG;
    typedef union  TGbl_gc360ResetStatus
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gc360ResetStatus;
                   };
                 } TGbl_gc360ResetStatus;
    typedef union  TGbl_SpdifRxResetStatus
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SpdifRxResetStatus;
                   };
                 } TGbl_SpdifRxResetStatus;
    typedef union  TGbl_DroEnable
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DroEnable;
                   };
                 } TGbl_DroEnable;
    typedef union  TGbl_DroCounter
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DroCounter;
                   };
                 } TGbl_DroCounter;
    typedef union  TGbl_DroDone
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DroDone;
                   };
                 } TGbl_DroDone;
    typedef union  TGbl_INT_ID
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_INT_ID;
                   };
                 } TGbl_INT_ID;
    typedef union  TGbl_stickyResetN
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_stickyResetN;
                   };
                 } TGbl_stickyResetN;
    typedef union  TGbl_gethRgmii_dll
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_gethRgmii_dll;
                   };
                 } TGbl_gethRgmii_dll;
    typedef union  TGbl_funcSel
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_funcSel;
                   };
                 } TGbl_funcSel;
    typedef union  TGbl_chipCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_chipCntl;
                   };
                 } TGbl_chipCntl;
    typedef union  TGbl_bootStrapEn
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_bootStrapEn;
                   };
                 } TGbl_bootStrapEn;
    typedef union  TGbl_axiClkEn
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_axiClkEn;
                   };
                 } TGbl_axiClkEn;
    typedef union  TGbl_ahbClkEn
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_ahbClkEn;
                   };
                 } TGbl_ahbClkEn;
    typedef union  TGbl_SPI1_SS0nCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPI1_SS0nCntl;
                   };
                 } TGbl_SPI1_SS0nCntl;
    typedef union  TGbl_SPI1_SS1nCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPI1_SS1nCntl;
                   };
                 } TGbl_SPI1_SS1nCntl;
    typedef union  TGbl_SPI1_SS2nCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPI1_SS2nCntl;
                   };
                 } TGbl_SPI1_SS2nCntl;
    typedef union  TGbl_SPI1_SCLKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPI1_SCLKCntl;
                   };
                 } TGbl_SPI1_SCLKCntl;
    typedef union  TGbl_SPI1_SDOCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPI1_SDOCntl;
                   };
                 } TGbl_SPI1_SDOCntl;
    typedef union  TGbl_SPI1_SDICntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPI1_SDICntl;
                   };
                 } TGbl_SPI1_SDICntl;
    typedef union  TGbl_URT0_RXDCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_URT0_RXDCntl;
                   };
                 } TGbl_URT0_RXDCntl;
    typedef union  TGbl_URT0_TXDCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_URT0_TXDCntl;
                   };
                 } TGbl_URT0_TXDCntl;
    typedef union  TGbl_DVIO0Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO0Cntl;
                   };
                 } TGbl_DVIO0Cntl;
    typedef union  TGbl_DVIO1Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO1Cntl;
                   };
                 } TGbl_DVIO1Cntl;
    typedef union  TGbl_DVIO2Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO2Cntl;
                   };
                 } TGbl_DVIO2Cntl;
    typedef union  TGbl_DVIO3Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO3Cntl;
                   };
                 } TGbl_DVIO3Cntl;
    typedef union  TGbl_DVIO4Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO4Cntl;
                   };
                 } TGbl_DVIO4Cntl;
    typedef union  TGbl_DVIO5Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO5Cntl;
                   };
                 } TGbl_DVIO5Cntl;
    typedef union  TGbl_DVIO6Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO6Cntl;
                   };
                 } TGbl_DVIO6Cntl;
    typedef union  TGbl_DVIO7Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO7Cntl;
                   };
                 } TGbl_DVIO7Cntl;
    typedef union  TGbl_DVIO8Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO8Cntl;
                   };
                 } TGbl_DVIO8Cntl;
    typedef union  TGbl_DVIO9Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO9Cntl;
                   };
                 } TGbl_DVIO9Cntl;
    typedef union  TGbl_DVIO10Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO10Cntl;
                   };
                 } TGbl_DVIO10Cntl;
    typedef union  TGbl_DVIO11Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DVIO11Cntl;
                   };
                 } TGbl_DVIO11Cntl;
    typedef union  TGbl_DV0_CLKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DV0_CLKCntl;
                   };
                 } TGbl_DV0_CLKCntl;
    typedef union  TGbl_DV0_HSCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DV0_HSCntl;
                   };
                 } TGbl_DV0_HSCntl;
    typedef union  TGbl_DV0_VSCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DV0_VSCntl;
                   };
                 } TGbl_DV0_VSCntl;
    typedef union  TGbl_DV0_FIDCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_DV0_FIDCntl;
                   };
                 } TGbl_DV0_FIDCntl;
    typedef union  TGbl_I2S0_BCLKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S0_BCLKCntl;
                   };
                 } TGbl_I2S0_BCLKCntl;
    typedef union  TGbl_I2S0_LRCKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S0_LRCKCntl;
                   };
                 } TGbl_I2S0_LRCKCntl;
    typedef union  TGbl_I2S0_DO0Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S0_DO0Cntl;
                   };
                 } TGbl_I2S0_DO0Cntl;
    typedef union  TGbl_I2S0_DO1Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S0_DO1Cntl;
                   };
                 } TGbl_I2S0_DO1Cntl;
    typedef union  TGbl_I2S0_DO2Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S0_DO2Cntl;
                   };
                 } TGbl_I2S0_DO2Cntl;
    typedef union  TGbl_I2S0_DO3Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S0_DO3Cntl;
                   };
                 } TGbl_I2S0_DO3Cntl;
    typedef union  TGbl_SPDIFICntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPDIFICntl;
                   };
                 } TGbl_SPDIFICntl;
    typedef union  TGbl_I2S1_LRCKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S1_LRCKCntl;
                   };
                 } TGbl_I2S1_LRCKCntl;
    typedef union  TGbl_I2S1_BCLKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S1_BCLKCntl;
                   };
                 } TGbl_I2S1_BCLKCntl;
    typedef union  TGbl_I2S1_DOCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S1_DOCntl;
                   };
                 } TGbl_I2S1_DOCntl;
    typedef union  TGbl_I2S2_LRCKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S2_LRCKCntl;
                   };
                 } TGbl_I2S2_LRCKCntl;
    typedef union  TGbl_I2S2_BCLKCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S2_BCLKCntl;
                   };
                 } TGbl_I2S2_BCLKCntl;
    typedef union  TGbl_I2S2_DI_0Cntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_I2S2_DI_0Cntl;
                   };
                 } TGbl_I2S2_DI_0Cntl;
    typedef union  TGbl_SPDIFOCntl
          { UNSG32 u32[1];
            struct {
            struct w32Gbl_SPDIFOCntl;
                   };
                 } TGbl_SPDIFOCntl;
#endif
#ifdef __cplusplus
  }
#endif
#pragma  pack()
#endif
