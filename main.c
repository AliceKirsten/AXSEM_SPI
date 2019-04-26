/*
 */

#include <mcs51/8051.h>
#include "port.h"
#include "lmx_regs.h"
#include "nbfi.h"
#include "atrf_init.h"

const uint8_t trx_data_len = 36;
const uint8_t trx_data[36] = {0x97, 0x15, 0x7a, 0x6f, 0xc0, 0xff, 0xee, 0x01, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa8,
                              0xdd, 0xad, 0x94, 0xbe, 0xb0, 0x41, 0xbe, 0x21, 0xd7,
                              0xd9, 0x11, 0xfe, 0xda, 0xad, 0xec, 0x9a, 0x56, 0xd9};

uint8_t coldstart = 1; /* caution: initialization with 1 is necessary! Variables are initialized upon _sdcc_external_startup returning 0
                        -> the coldstart value returned from _sdcc_external startup does not survive in the coldstart case*/
volatile LMX_REGS_TypeDef __xdata lmx_regs;

uint8_t _sdcc_external_startup(void)
{
    /* No SysClock divider */
    CLKCON = 0x00;

    /* Both XOSC and LPXOSC are unconnected and disabled */
    MISCCTRL = 0x03;

    PALTRADIO = 0x00;       //pass through

    /* data pointer selector use DPTR0 */
    DPS = 0;

    /* unfreeze GPIO */
    GPIOENABLE = 1;

    coldstart = PCON & 0x40;

    return coldstart;
}

uint32_t readback = 0xa5a5a5a5;
uint32_t temp;
void main(void)
{
    periph_init();

    //set R5 reset bit
    LMX_SET_R5_INIT_VALUE(&lmx_regs);
    //reset lmx
    LMX_CS = 0;
    spi_writepacket((uint8_t*)&lmx_regs.r5_data, 4);
    LMX_CS = 1;

    //config lmx
    lmx_config_default(&lmx_regs);
    lmx_set_dividers(&lmx_regs, 52);

    //write reg values to device
    LMX_CS = 0;
    spi_writepacket((uint8_t*)&lmx_regs.r15_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r13_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r10_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r9_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r8_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r7_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r6_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r5_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r4_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r3_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r2_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r1_data, 4);
    spi_writepacket((uint8_t*)&lmx_regs.r0_data, 4);
    LMX_CS = 1;

    //wait 20 ms
    delay_ms(delay_20ms);
    //program r0 again
    spi_writepacket((uint8_t*)&lmx_regs.r0_data, 4);

    //program AXSEM TX Carrier
    //RF_Init(UL_CARRIER, PCB, RF_POWER, NBFI_UL_FREQ_BASE);
    RF_Init(UL_DBPSK_50_PROT_D, PCB, RF_POWER, NBFI_UL_FREQ_BASE);

    //program AR86RF215 RX I/Q interface
    if (trx_init(RF09) == SUCCESS) trx_switch_state(RF09, RF_RX);

    while(1)
    {
        RF_Transmit(trx_data, trx_data_len, NO_PADDING, BLOCKING);

        LMX_CS = 0;
        spi_writepacket((uint8_t*)&lmx_regs.r6_data, 4);
        LMX_CS = 1;
        spi_readpacket((uint8_t*)&readback, 4);

        delay_ms(delay_5s);


#if (!USE_HARDWARE_SPI)
        led_toggle();
#endif
    }
}
