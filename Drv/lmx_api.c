
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
#define LMX_R2_CPP_POS              27
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

//LMX2581 r5 initialization value
#define LMX_R5_INIT_VAL             0x40870010

//LMX2581 reset registers values
#define LMX_R0_DEF_VAL              0x00000000
#define LMX_R1_DEF_VAL              0x00000001
#define LMX_R2_DEF_VAL              0x04000002
#define LMX_R3_DEF_VAL              0x20000003
#define LMX_R4_DEF_VAL              0x00000004
#define LMX_R5_DEF_VAL              0x00000005
#define LMX_R6_DEF_VAL              0x00000406
#define LMX_R7_DEF_VAL              0x00000007
#define LMX_R8_DEF_VAL              0x207ddbf8
#define LMX_R9_DEF_VAL              0x03c7c039
#define LMX_R10_DEF_VAL             0x210050ca
#define LMX_R13_DEF_VAL             0x0000c10d
#define LMX_R15_DEF_VAL             0x021fe00f

inline void LMX_SET_R5_INIT_VALUE(LMX_REGS_TypeDef* lmxr)
{
    lmxr->r5_data = LMX_R5_INIT_VAL;
}

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

    value |=(uint32_t)((R6)
                                                                                        |
                      ((bits->uwire_lock  & REG_BIT_MASK_1)  << LMX_R6_UWIRE_LOCK_POS)  |
                      ((bits->rd_addr     & REG_BIT_MASK_4)  << LMX_R6_RDADDR_POS));

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

#define F_VCO_MIN   1880
#define F_VCO_MAX   3760
#define F_IN        52

//default configuration
void lmx_config_default(LMX_REGS_TypeDef* lmxr)
{
    _LMX_R15_bits r15_bits;
    _LMX_R13_bits r13_bits;
    _LMX_R7_bits r7_bits;
    _LMX_R6_bits r6_bits;
    _LMX_R5_bits r5_bits;
    _LMX_R4_bits r4_bits;
    _LMX_R3_bits r3_bits;
    _LMX_R2_bits r2_bits;
    _LMX_R1_bits r1_bits;
    _LMX_R0_bits r0_bits;

    //set def reg values
    LMX_SET_DEF_REG_VALUES(lmxr);

    //set reg values
    r15_bits.vco_cap_man = 0;
    r15_bits.vco_capcode = 128; //default
    LMX_SET_R15_VALUES(lmxr, &r15_bits);

    //this settings may be unnecessary
    r13_bits.dld_err_cnt = 4;   //default
    r13_bits.dld_pass_cnt = 32; //default
    r13_bits.dld_tol = 5;       //Fpd = Fosc_in < 30 MHz
    LMX_SET_R13_VALUES(lmxr, &r13_bits);

    r7_bits.mux_select = 7;     //Fpll_r/2
    r7_bits.mux_pinmode = 2;    //default == 1
    r7_bits.mux_inv = 0;        //inverse mux output
    r7_bits.ld_select = 4;      //readback function
    r7_bits.ld_pinmode = 1;     //analog mode
    r7_bits.ld_inv = 0;         //direct ld output
    LMX_SET_R7_VALUES(lmxr, &r7_bits);

    r6_bits.rd_addr = 6;         //readback R6 reg
    LMX_SET_R6_VALUES(lmxr, &r6_bits);

    r5_bits.osc_freq = 0;
    r5_bits.bufen_dis = 1;      //bufen pin disabled
    r5_bits.outa_mux = 3;       //disable outa mux
    r5_bits.outb_mux = 1;       //enable outb mux
    r5_bits.reset = 0;          //clear reset bit
    r5_bits.mode = 0;
    r5_bits.vco_sel_mod = 0;
    r5_bits.pwdn_mode = 0;
    LMX_SET_R5_VALUES(lmxr, &r5_bits);

    //this settings may be unnecessary
    r4_bits.pfd_dly = 0;        //max phase detector delay (?)
    r4_bits.fl_toc = 0;         //max fastlock timeout
    r4_bits.fl_cpg = 0;         //fast lock pump gain
    LMX_SET_R4_VALUES(lmxr, &r4_bits);

    r3_bits.outb_pwr = 15;       //max outb power
    r3_bits.outa_pd = 1;
    LMX_SET_R3_VALUES(lmxr, &r3_bits);

    r2_bits.cpp = 1;            //default
    r2_bits.pll_den = 0;        //integer mode
    r2_bits.osc_2x = 1;
    LMX_SET_R2_VALUES(lmxr, &r2_bits);

    r1_bits.cgp = 0;            //normal pump gain
    r1_bits.frac_order = 0;     //sig-del modulator order (?)
    r1_bits.vco_sel = 0;
    LMX_SET_R1_VALUES(lmxr, &r1_bits);

    r0_bits.id = 0;             //readback part id
    r0_bits.frac_dither = 0;
    r0_bits.no_fcal = 0;        //do calibration
    r0_bits.pll_num = 0;        //integer mode
    LMX_SET_R0_VALUES(lmxr, &r0_bits);
}

//dividers calculator
uint8_t lmx_set_dividers(LMX_REGS_TypeDef* lmxr, uint32_t f_out)
{
    uint32_t f_vco, f_pd;
    uint32_t vco_div, pll_r, pll_n;//, pll_num, pll_den;

    if ((f_out * 38) < F_VCO_MIN || (f_out * 2) > F_VCO_MAX) return 0;

    //Fout = Fvco/((vco_div * 2) + 2)
    for (vco_div = 2; vco_div < 40; vco_div+=2)
    {
        f_vco = f_out * vco_div;
        if (f_vco > F_VCO_MIN && f_vco < F_VCO_MAX) break;
    }

    //Fvco = (Fosc_in * (2 ^ osc_2x) / pll_r) * (pll_n + (pll_num/pll_den))
    for (pll_r = 1; pll_r < 256; pll_r++)
    {
        f_pd = F_IN / pll_r;
        if (f_out%f_pd == 0) break;
    }

    pll_n = vco_div * (f_out / f_pd);
    vco_div = (vco_div >> 1) - 1;

    lmxr->r3_data &= ~((uint32_t)REG_BIT_MASK_5 << LMX_R3_VCO_DIV_POS);
    lmxr->r1_data &= ~((uint32_t)REG_BIT_MASK_8 << LMX_R1_PLL_R_POS);
    lmxr->r0_data &= ~((uint32_t)REG_BIT_MASK_12 << LMX_R0_PLL_N_POS);

    lmxr->r3_data |= (vco_div << LMX_R3_VCO_DIV_POS);
    lmxr->r1_data |= (pll_r << LMX_R1_PLL_R_POS);
    lmxr->r0_data |= (pll_n << LMX_R0_PLL_N_POS);

    return 1;
}
