/*
 */

#include <mcs51/8051.h>
#include "port.h"
#include "lmx_regs.h"

uint8_t coldstart = 1; /* caution: initialization with 1 is necessary! Variables are initialized upon _sdcc_external_startup returning 0
                        -> the coldstart value returned from _sdcc_external startup does not survive in the coldstart case*/
_LMX_R15_bits r15_bits;
_LMX_R13_bits r13_bits;
_LMX_R7_bits r7_bits;
_LMX_R5_bits r5_bits;
_LMX_R4_bits r4_bits;
_LMX_R3_bits r3_bits;
_LMX_R2_bits r2_bits;
_LMX_R1_bits r1_bits;
_LMX_R0_bits r0_bits;
LMX_REGS_TypeDef lmx_regs;

uint8_t _sdcc_external_startup(void)
{
    /* No SysClock divider */
    CLKCON = 0x00;

    /* Both XOSC and LPXOSC are unconnected and disabled */
    MISCCTRL = 0x03;

    /* data pointer selector use DPTR0 */
    DPS = 0;

    /* unfreeze GPIO */
    GPIOENABLE = 1;

    coldstart = PCON & 0x40;

    return coldstart;
}

void main(void)
{
    uint16_t delay = 0;
    uint32_t readback = 0;

    periph_init();

    //set def reg values
    LMX_SET_DEF_REG_VALUES(&lmx_regs);

    //set R5 reset bit
    r5_bits.reset = 1;
    LMX_SET_R5_VALUES(&lmx_regs, &r5_bits);
    //reset lmx
    lmx_spi_writepacket(lmx_regs.r5_data);

    //set necessary reg values
    r15_bits.vco_cap_man = 0;
    r15_bits.vco_capcode = 128; //default
    LMX_SET_R15_VALUES(&lmx_regs, &r15_bits);

    r13_bits.dld_err_cnt = 4;   //default
    r13_bits.dld_pass_cnt = 32; //default
    r13_bits.dld_tol = 5;       //Fpd = Fosc_in < 30 MHz
    LMX_SET_R13_VALUES(&lmx_regs, &r13_bits);

    r7_bits.mux_select = 10;    //pull to gnd
    r7_bits.mux_pinmode = 1;    //default
    r7_bits.mux_inv = 1;        //inverse mux output
    r7_bits.ld_select = 4;      //readback function
    r7_bits.ld_pinmode = 1;     //push-pull mode
    r7_bits.ld_inv = 1;         //inverse ld output
    LMX_SET_R7_VALUES(&lmx_regs, &r7_bits);

    r5_bits.bufen_dis = 1;      //bufen pin disabled
    r5_bits.outb_mux = 1;       //enable outb mux
    r5_bits.reset = 0;          //clear reset bit
    LMX_SET_R5_VALUES(&lmx_regs, &r5_bits);

    r4_bits.pfd_dly = 7;        //max phase detector delay (?)
    r4_bits.fl_toc = 4095;      //max fastlock timeout
    r4_bits.fl_cpg = 1;         //fast lock pump gain
    LMX_SET_R4_VALUES(&lmx_regs, &r4_bits);

    r3_bits.vco_div = 18;       //vco_div = 38
    r3_bits.outb_pwr = 47;      //max outb power
    LMX_SET_R3_VALUES(&lmx_regs, &r3_bits);

    r2_bits.cpp = 1;            //default
    r2_bits.pll_den = 1;        //integer mode
    LMX_SET_R2_VALUES(&lmx_regs, &r2_bits);

    r1_bits.cgp = 1;            //normal pump gain
    r1_bits.frac_order = 3;     //sig-del modulator order
    r1_bits.pll_r = 1;          //no Fosc_in division
    LMX_SET_R1_VALUES(&lmx_regs, &r1_bits);

    r0_bits.id = 1;             //readback part id
    r0_bits.no_fcal = 1;        //no calibration
    r0_bits.pll_n = 75;         //Fvco = Fosc_in * (pll_n + (pll_num/pll_den))
    r0_bits.pll_num = 1;        //integer mode
    LMX_SET_R0_VALUES(&lmx_regs, &r0_bits);

    //write reg values to device
    lmx_spi_writepacket(lmx_regs.r15_data);
    lmx_spi_writepacket(lmx_regs.r13_data);
    lmx_spi_writepacket(lmx_regs.r10_data);
    lmx_spi_writepacket(lmx_regs.r9_data);
    lmx_spi_writepacket(lmx_regs.r8_data);
    lmx_spi_writepacket(lmx_regs.r7_data);
    lmx_spi_writepacket(lmx_regs.r6_data);
    lmx_spi_writepacket(lmx_regs.r5_data);
    lmx_spi_writepacket(lmx_regs.r4_data);
    lmx_spi_writepacket(lmx_regs.r3_data);
    lmx_spi_writepacket(lmx_regs.r2_data);
    lmx_spi_writepacket(lmx_regs.r1_data);
    lmx_spi_writepacket(lmx_regs.r0_data);

    //wait 20 ms
    while(delay++ < 5678);

    //program r0 again with freq calibration instruction
    r0_bits.no_fcal = 0;
    lmx_spi_writepacket(lmx_regs.r0_data);

    while(1)
    {

        readback = lmx_spi_readpacket();
#if (!USE_HARDWARE_SPI)
        led_toggle();
#endif
        delay = 0;
        //wait 20 ms
        while(delay++ < 5678);
    }
}
