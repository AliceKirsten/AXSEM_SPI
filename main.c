/*
 */

#include <mcs51/8051.h>
#include "port.h"
#include "lmx_regs.h"

uint8_t coldstart = 1; /* caution: initialization with 1 is necessary! Variables are initialized upon _sdcc_external_startup returning 0
                        -> the coldstart value returned from _sdcc_external startup does not survive in the coldstart case*/
_LMX_R15_bits r15_bits;
_LMX_R7_bits r7_bits;
_LMX_R5_bits r5_bits;
_LMX_R3_bits r3_bits;
_LMX_R2_bits r2_bits;
_LMX_R1_bits r1_bits;
_LMX_R0_bits r0_bits;
LMX_REGS_TypeDef lmx_regs;
uint8_t _sdcc_external_startup(void)
{
    /* Slow, PRESC /1, no cal. Does NOT enable LPOSC. LPOSC is enabled upon configuring WTCFGA (MODE_TX_PERIODIC and receive_ack()) */
    LPOSCCONFIG = 0x09;
    LPXOSCGM = 0x8A;

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
    r15_bits.vco_capcode = 128;
    LMX_SET_R15_VALUES(&lmx_regs, &r15_bits);

    r7_bits.ld_pinmode = 3;
    r7_bits.fl_select = 4;
    r7_bits.mux_pinmode = 1;
    r7_bits.mux_select = 10;
    LMX_SET_R7_VALUES(&lmx_regs, &r7_bits);

    r5_bits.osc_freq = 0;
    r5_bits.reset = 0;
    LMX_SET_R5_VALUES(&lmx_regs, &r5_bits);

    r3_bits.vco_div = 18;
    r3_bits.outb_pwr = 47;
    r3_bits.outb_pd = 1;
    LMX_SET_R3_VALUES(&lmx_regs, &r3_bits);

    r2_bits.cpp = 1;
    r2_bits.osc_2x = 0;
    r2_bits.pll_den = 1;
    LMX_SET_R2_VALUES(&lmx_regs, &r2_bits);

    r1_bits.vco_sel = 0;
    r1_bits.pll_num = 0;
    r1_bits.pll_r = 1;
    LMX_SET_R1_VALUES(&lmx_regs, &r1_bits);

    r0_bits.no_fcal = 0;
    r0_bits.pll_n = 75;
    r0_bits.pll_num = 1;
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

    //program r0 again
    lmx_spi_writepacket(lmx_regs.r0_data);

    while(1)
    {
        lmx_regs.r6_data = lmx_spi_readpacket();
#if (!USE_HARDWARE_SPI)
        led_toggle();
#endif
        delay = 0;
        //wait 20 ms
        while(delay++ < 5678);
    }
}
