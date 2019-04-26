#ifndef LMX_REGS_H_INCLUDED
#define LMX_REGS_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

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

#define IS_LMX_REG(x)   ((x == R0)  || (x == R1)  || (x == R2) || \
                         (x == R3)  || (x == R4)  || (x == R5) || \
                         (x == R6)  || (x == R7)  || (x == R8) || \
                         (x == R9)  || (x == R10) ||              \
                         (x == R13) || (x == R15))

/* LMX2581 registers structure */
typedef struct
{
    uint32_t            r0_data;
    uint32_t            r1_data;
    uint32_t            r2_data;
    uint32_t            r3_data;
    uint32_t            r4_data;
    uint32_t            r5_data;
    uint32_t            r6_data;
    uint32_t            r7_data;
    uint32_t            r8_data;
    uint32_t            r9_data;
    uint32_t            r10_data;
    uint32_t            r13_data;
    uint32_t            r15_data;
} LMX_REGS_TypeDef;

/* Register R0 bitfield structure */
typedef struct
{
    uint32_t pll_num;
    uint32_t pll_n;
    uint32_t no_fcal;
    uint32_t frac_dither;
    uint32_t id;
} _LMX_R0_bits;

/* Register R1 bitfield structure */
typedef struct
{
    uint32_t pll_r;
    uint32_t frac_order;
    uint32_t pll_num;
    uint32_t vco_sel;
    uint32_t cgp;
} _LMX_R1_bits;

/* Register R2 bitfield structure */
typedef struct
{
    uint32_t pll_den;
    uint32_t cpp;
    uint32_t osc_2x;
} _LMX_R2_bits;

/* Register R3 bitfield structure */
typedef struct
{
    uint32_t outa_pd;
    uint32_t outb_pd;
    uint32_t outa_pwr;
    uint32_t outb_pwr;
    uint32_t vco_div;
} _LMX_R3_bits;

/* Register R4 bitfield structure */
typedef struct
{
    uint32_t cpg_bleed;
    uint32_t fl_cpg;
    uint32_t fl_toc;
    uint32_t fl_frec;
    uint32_t pfd_dly;
} _LMX_R4_bits;

/* Register R5 bitfield structure */
typedef struct
{
    uint32_t reset;
    uint32_t pwdn_mode;
    uint32_t mode;
    uint32_t zero_dly;
    uint32_t outa_mux;
    uint32_t outb_mux;
    uint32_t vco_sel_mod;
    uint32_t bufen_dis;
    uint32_t osc_freq;
    uint32_t out_lden;
} _LMX_R5_bits;

/* Register R6 bitfield structure */
typedef struct
{
    uint32_t uwire_lock;
    uint32_t rd_addr;
} _LMX_R6_bits;

/* Register R7 bitfield structure */
typedef struct
{
    uint32_t ld_pinmode;
    uint32_t ld_inv;
    uint32_t ld_select;
    uint32_t mux_pinmode;
    uint32_t mux_inv;
    uint32_t mux_select;
    uint32_t fl_inv;
    uint32_t fl_pinmode;
    uint32_t fl_select;
} _LMX_R7_bits;

/* Register R13 bitfield structure */
typedef struct
{
    uint32_t dld_tol;
    uint32_t dld_pass_cnt;
    uint32_t dld_err_cnt;
} _LMX_R13_bits;

/* Register R15 bitfield structure */
typedef struct
{
    uint32_t vco_capcode;
    uint32_t vco_cap_man;
} _LMX_R15_bits;

inline void LMX_SET_R5_INIT_VALUE(LMX_REGS_TypeDef* lmxr);
inline void LMX_SET_DEF_REG_VALUES(LMX_REGS_TypeDef* lmxr);

void lmx_config_default(LMX_REGS_TypeDef* lmxr);
uint8_t lmx_set_dividers(LMX_REGS_TypeDef* lmxr, uint32_t f_out);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // LMX_REGS_H_INCLUDED
