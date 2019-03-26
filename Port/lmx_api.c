
#include "lmx_regs.h"

//bitfields lengths
#define REG_BIT_MASK_1              0x1
#define REG_BIT_MASK_2              0x3
#define REG_BIT_MASK_3              0x7
#define REG_BIT_MASK_4              0xf
#define REG_BIT_MASK_5              0x1f
#define REG_BIT_MASK_6              0x3f
#define REG_BIT_MASK_8              0xff
#define REG_BIT_MASK_10             0x3ff
#define REG_BIT_MASK_12             0xfff
#define REG_BIT_MASK_20             0xffff
#define REG_BIT_MASK_22             0x3ffff

//R0 bitfields positions
#define LMX_R0_PLL_NUM_POS          4
#define LMX_R0_PLL_N_POS            16
#define LMX_R0_NO_FCAL_POS          28
#define LMX_R0_FRAC_DITHER_POS      29
#define LMX_R0_ID_POS               31

//R1 bitfields positions
#define LMX_R1_PLL_R_POS            4
#define LMX_R1_FRAC_ORDER_POS       12
#define LMX_R1_PLL_NUM_POS          15
#define LMX_R1_VCO_SEL_POS          25
#define LMX_R1_CPG_POS              27

//R2 bitfields positions
#define LMX_R2_PLL_DEN_POS          4
#define LMX_R2_CPP_POS              26
#define LMX_R2_OSC_2X_POS           29

//R3 bitfields positions
#define LMX_R3_OUTA_PD_POS          4
#define LMX_R3_OUTB_PD_POS          5
#define LMX_R3_OUTA_PWR_POS         6
#define LMX_R3_OUTB_PWR_POS         12
#define LMX_R3_VCO_DIV_POS          18

//R4 bitfields positions
#define LMX_R4_CPG_BLEED_POS        4
#define LMX_R4_FL_CPG_POS           11
#define LMX_R4_FL_TOC_POS           16
#define LMX_R4_FL_FREC_POS          28
#define LMX_R4_PFD_DLY_POS          29

//R5 bitfields positions
#define LMX_R5_RESET_POS            4
#define LMX_R5_PWDN_MODE_POS        5
#define LMX_R5_MODE_POS             8
#define LMX_R5_ZERO_DLY_POS         10
#define LMX_R5_OUTA_MUX_POS         11
#define LMX_R5_OUTB_MUX_POS         13
#define LMX_R5_VCO_SEL_MOD_POS      15
#define LMX_R5_BUFEN_DIS_POS        20
#define LMX_R5_OSC_FREQ_POS         21
#define LMX_R5_OUT_LDEN_POS         24

//R6 bitfields positions
#define LMX_R6_UWIRE_LOCK_POS       4
#define LMX_R6_RDADDR_POS           5
#define LMX_R6_RD_DIAG_POS          11

//R7 bitfields positions
#define LMX_R7_LD_PINMODE_POS       4
#define LMX_R7_LD_INV_POS           7
#define LMX_R7_LD_SELECT_POS        8
#define LMX_R7_MUX_PINMODE_POS      13
#define LMX_R7_MUX_INV_POS          16
#define LMX_R7_MUX_SELECT_POS       17
#define LMX_R7_FL_INV_POS           22
#define LMX_R7_FL_PINMODE_POS       23
#define LMX_R7_FL_SELECT_POS        26

//R13 bitfields positions
#define LMX_R13_DLD_TOL_POS         15
#define LMX_R13_DLD_PASS_CNT_POS    18
#define LMX_R13_DLD_ERR_CNT_POS     28

//R15 bitfields positions
#define LMX_R15_VCO_CAPCODE_POS     4
#define LMX_R15_VCO_CAP_MAN_POS     12

//LMX2581 reset registers values
#define LMX_R0_DEF_VAL              0x00000000
#define LMX_R1_DEF_VAL              0x00000001
#define LMX_R2_DEF_VAL              0x0C000012
#define LMX_R3_DEF_VAL              0x20000003
#define LMX_R4_DEF_VAL              0x00000004
#define LMX_R5_DEF_VAL              0x00000005
#define LMX_R6_DEF_VAL              0x00000406
#define LMX_R7_DEF_VAL              0x00001007
#define LMX_R8_DEF_VAL              0x207ddbf8
#define LMX_R9_DEF_VAL              0x03c7c039
#define LMX_R10_DEF_VAL             0x210050ca
#define LMX_R13_DEF_VAL             0x0000410d
#define LMX_R15_DEF_VAL             0x021fe00f

//registers address enumeration
typedef enum
{
    R0 = 0x00,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R13 = 0x0D,
    R15 = 0x0F
} LMX_REG;

//fill LMX_REGS_TypeDef structure with reset registers values
inline void LMX_SET_DEF_REG_VALUES(LMX_REGS_TypeDef* lmxr)
{
    lmxr->r0_data = LMX_R0_DEF_VAL;
    lmxr->r1_data = LMX_R1_DEF_VAL;
    lmxr->r2_data = LMX_R2_DEF_VAL;
    lmxr->r3_data = LMX_R3_DEF_VAL;
    lmxr->r4_data = LMX_R4_DEF_VAL;
    lmxr->r5_data = LMX_R5_DEF_VAL;
    lmxr->r6_data = LMX_R6_DEF_VAL;
    lmxr->r7_data = LMX_R7_DEF_VAL;
    lmxr->r8_data = LMX_R8_DEF_VAL;
    lmxr->r9_data = LMX_R9_DEF_VAL;
    lmxr->r10_data = LMX_R10_DEF_VAL;
    lmxr->r13_data = LMX_R13_DEF_VAL;
    lmxr->r15_data = LMX_R15_DEF_VAL;
}

//TODO: add parameters verification

//fill R0 register
void LMX_SET_R0_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R0_bits* bits)
{
    uint32_t value = LMX_R0_DEF_VAL;

    value |=(uint32_t)((R0)                                                             |
                      ((bits->pll_num     & REG_BIT_MASK_12) << LMX_R0_PLL_NUM_POS)     |
                      ((bits->pll_n       & REG_BIT_MASK_12) << LMX_R0_PLL_N_POS)       |
                      ((bits->no_fcal     & REG_BIT_MASK_1)  << LMX_R0_NO_FCAL_POS)     |
                      ((bits->frac_dither & REG_BIT_MASK_2)  << LMX_R0_FRAC_DITHER_POS) |
                      ((bits->id          & REG_BIT_MASK_1)  << LMX_R0_ID_POS));
   lmxr->r0_data = value;
}

//fill R1 register
void LMX_SET_R1_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R1_bits* bits)
{
    uint32_t value = LMX_R1_DEF_VAL;

    value |=(uint32_t)((R1)                                                             |
                      ((bits->pll_r       & REG_BIT_MASK_8)  << LMX_R1_PLL_R_POS)       |
                      ((bits->frac_order  & REG_BIT_MASK_3)  << LMX_R1_FRAC_ORDER_POS)  |
                      ((bits->pll_num     & REG_BIT_MASK_10) << LMX_R1_PLL_NUM_POS)     |
                      ((bits->vco_sel     & REG_BIT_MASK_2)  << LMX_R1_VCO_SEL_POS)     |
                      ((bits->cgp         & REG_BIT_MASK_5)  << LMX_R1_CPG_POS));
    lmxr->r1_data = value;
}

//fill R2 register
void LMX_SET_R2_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R2_bits* bits)
{
    uint32_t value = LMX_R2_DEF_VAL;

    value |=(uint32_t)((R2)                                                             |
                      ((bits->pll_den     & REG_BIT_MASK_22) << LMX_R2_PLL_DEN_POS)     |
                      ((bits->cpp         & REG_BIT_MASK_1)  << LMX_R2_CPP_POS)         |
                      ((bits->osc_2x      & REG_BIT_MASK_1)  << LMX_R2_OSC_2X_POS));
    lmxr->r2_data = value;
}

//fill R3 register
void LMX_SET_R3_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R3_bits* bits)
{
    uint32_t value = LMX_R3_DEF_VAL;

    value |=(uint32_t)((R3)                                                             |
                      ((bits->outa_pd     & REG_BIT_MASK_1)  << LMX_R3_OUTA_PD_POS)     |
                      ((bits->outb_pd     & REG_BIT_MASK_1)  << LMX_R3_OUTB_PD_POS)     |
                      ((bits->outa_pwr    & REG_BIT_MASK_6)  << LMX_R3_OUTA_PWR_POS)    |
                      ((bits->outb_pwr    & REG_BIT_MASK_6)  << LMX_R3_OUTB_PWR_POS)    |
                      ((bits->vco_div     & REG_BIT_MASK_5)  << LMX_R3_VCO_DIV_POS));
    lmxr->r3_data = value;
}

//fill R4 register
void LMX_SET_R4_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R4_bits* bits)
{
    uint32_t value = LMX_R4_DEF_VAL;

    value |=(uint32_t)((R4)                                                             |
                      ((bits->cpg_bleed   & REG_BIT_MASK_6)  << LMX_R4_CPG_BLEED_POS)   |
                      ((bits->fl_cpg      & REG_BIT_MASK_5)  << LMX_R4_FL_CPG_POS)      |
                      ((bits->fl_toc      & REG_BIT_MASK_12) << LMX_R4_FL_TOC_POS)      |
                      ((bits->fl_frec     & REG_BIT_MASK_1)  << LMX_R4_FL_FREC_POS)     |
                      ((bits->pfd_dly     & REG_BIT_MASK_3)  << LMX_R4_PFD_DLY_POS));
    lmxr->r4_data = value;
}

//fill R5 register
void LMX_SET_R5_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R5_bits* bits)
{
    uint32_t value = LMX_R5_DEF_VAL;

    value |=(uint32_t)((R5)                                                             |
                      ((bits->reset       & REG_BIT_MASK_1)  << LMX_R5_RESET_POS)       |
                      ((bits->pwdn_mode   & REG_BIT_MASK_3)  << LMX_R5_PWDN_MODE_POS)   |
                      ((bits->mode        & REG_BIT_MASK_2)  << LMX_R5_MODE_POS)        |
                      ((bits->zero_dly    & REG_BIT_MASK_1)  << LMX_R5_ZERO_DLY_POS)    |
                      ((bits->outa_mux    & REG_BIT_MASK_2)  << LMX_R5_OUTA_MUX_POS)    |
                      ((bits->outb_mux    & REG_BIT_MASK_2)  << LMX_R5_OUTB_MUX_POS)    |
                      ((bits->vco_sel_mod & REG_BIT_MASK_2)  << LMX_R5_VCO_SEL_MOD_POS) |
                      ((bits->bufen_dis   & REG_BIT_MASK_1)  << LMX_R5_BUFEN_DIS_POS)   |
                      ((bits->osc_freq    & REG_BIT_MASK_3)  << LMX_R5_OSC_FREQ_POS)    |
                      ((bits->out_lden    & REG_BIT_MASK_1)  << LMX_R5_OUT_LDEN_POS));
    lmxr->r5_data = value;
}

//fill R6 register
void LMX_SET_R6_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R6_bits* bits)
{
    uint32_t value = LMX_R6_DEF_VAL;

    value |=(uint32_t)((R6)                                                             |
                      ((bits->uwire_lock  & REG_BIT_MASK_1)  << LMX_R6_UWIRE_LOCK_POS));
    lmxr->r6_data = value;
}

//fill R7 register
void LMX_SET_R7_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R7_bits* bits)
{
    uint32_t value = LMX_R7_DEF_VAL;

    value |=(uint32_t)((R7)                                                             |
                      ((bits->ld_pinmode  & REG_BIT_MASK_3)  << LMX_R7_LD_PINMODE_POS)  |
                      ((bits->ld_inv      & REG_BIT_MASK_1)  << LMX_R7_LD_INV_POS)      |
                      ((bits->ld_select   & REG_BIT_MASK_5)  << LMX_R7_LD_SELECT_POS)   |
                      ((bits->mux_pinmode & REG_BIT_MASK_3)  << LMX_R7_MUX_PINMODE_POS) |
                      ((bits->mux_inv     & REG_BIT_MASK_1)  << LMX_R7_MUX_INV_POS)     |
                      ((bits->mux_select  & REG_BIT_MASK_5)  << LMX_R7_MUX_SELECT_POS)  |
                      ((bits->fl_inv      & REG_BIT_MASK_1)  << LMX_R7_FL_INV_POS)      |
                      ((bits->fl_pinmode  & REG_BIT_MASK_3)  << LMX_R7_FL_PINMODE_POS)  |
                      ((bits->fl_select   & REG_BIT_MASK_5)  << LMX_R7_FL_SELECT_POS));
    lmxr->r7_data = value;
}

//fill R13 register
void LMX_SET_R13_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R13_bits* bits)
{
    uint32_t value = LMX_R13_DEF_VAL;

    value |=(uint32_t)((R13)                                                              |
                      ((bits->dld_tol      & REG_BIT_MASK_3)  << LMX_R13_DLD_TOL_POS)     |
                      ((bits->dld_pass_cnt & REG_BIT_MASK_10) << LMX_R13_DLD_PASS_CNT_POS)|
                      ((bits->dld_err_cnt  & REG_BIT_MASK_4)  << LMX_R13_DLD_ERR_CNT_POS));
    lmxr->r13_data = value;
}

//fill R15 register
void LMX_SET_R15_VALUES(LMX_REGS_TypeDef* lmxr, _LMX_R15_bits* bits)
{
    uint32_t value = LMX_R15_DEF_VAL;

    value |=(uint32_t)((R15)                                                              |
                      ((bits->vco_capcode  & REG_BIT_MASK_8)  << LMX_R15_VCO_CAPCODE_POS) |
                      ((bits->vco_cap_man  & REG_BIT_MASK_1)  << LMX_R15_VCO_CAP_MAN_POS));
    lmxr->r15_data = value;
}
