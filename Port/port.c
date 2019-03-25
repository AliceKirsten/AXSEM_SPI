/*
 * port.c - definitions for portable functions
 * mini BS board AXSEM MCU and periphery initialization
 */

#include "port.h"

void periph_init()
{
    /* init GPIO */
    CS_PDIR  |= (FPGA_CS|LMX_LE);
    USR_PDIR |= (LMX_MOSI|LMX_CLK|LMX_CE);

#if (USE_HARDWARE_SPI)
    /* init SPI */
    SPI_MODE = LMX_SPMODE;
    SPI_CLKCFG = LMX_CLKSRC;
#else
    USR_PDIR |= LED;
#endif
    FPGA_CS_HI
    LMX_ENABLE
    LMX_CS_HI
}

uint8_t d1, d2, d3, d4;
void lmx_spi_writepacket(uint32_t data)
{
    d4 = (data & 0xFF000000) >> 24;
    d3 = (data & 0x00FF0000) >> 16;
    d2 = (data & 0x0000FF00) >> 8;
    d1 = (data & 0x000000FF);

    LMX_CS_LO

    LMX_PUTC(d4)
    LMX_PUTC(d3)
    LMX_PUTC(d2)
    LMX_PUTC(d1)

    LMX_CS_HI
}

uint32_t lmx_spi_readpacket()
{
    uint32_t data = 0;

    LMX_GETC(d4)
    LMX_GETC(d3)
    LMX_GETC(d2)
    LMX_GETC(d1)

    data = (uint32_t)((d4 << 24)    |
                      (d3 << 16)    |
                      (d2 << 8)     |
                      (d1));
    return data;
}

#if (!USE_HARDWARE_SPI)
inline void lmx_putc(uint8_t c)
{
    uint8_t i = 0;

    do
    {
        //set data
        if (c & 0x80) USR_POUT |= LMX_MOSI;
        else USR_POUT &= ~LMX_MOSI;
        //clock high
        USR_POUT |= LMX_CLK;
        //shift data (msb first!)
        c <<= 1;
        //clock low
        USR_POUT &= ~LMX_CLK;
    } while (++i < 8);
    //pull mosi to low after transmission
    USR_POUT &= ~LMX_MOSI;
}

inline uint8_t lmx_getc()
{
    uint8_t i = 0;
    uint8_t c = 0;

    do
    {
        //clock high
        USR_POUT |= LMX_CLK;
        //shift data (msb first!)
        //set data
        if (USR_POUT & LMX_MISO) c |= 1;
        c <<= 1;
        //clock low
        USR_POUT &= ~LMX_CLK;
    } while (++i < 8);
    return c;
}

void led_on()
{
    USR_POUT |= LED;
}

void led_off()
{
    USR_POUT &= ~LED;
}

void led_toggle()
{
    USR_POUT ^= LED;
}
#endif
