/*
 * port.c - definitions for portable functions
 * mini BS board AXSEM MCU and periphery initialization
 */

#include "port.h"

void periph_init()
{
    /* set GPIO levels */
    LMX_ENABLE
    ATRF_CS = 1;
    FPGA_CS = 1;
    LMX_CS = 1;

    /* init GPIO as outputs */
    AT_DIR  |= (ATRF_CS_MASK);
    CS_DIR  |= (FPGA_CS_MASK|LMX_CS_MASK);
    SPI_DIR |= (SPI_MOSI_MASK|SPI_CLK_MASK|LMX_CE_MASK);

#if (USE_HARDWARE_SPI)
    /* init SPI */
    SPI_MODE = LMX_SPMODE;
    SPI_CLKCFG = LMX_CLKSRC;
#else
    SPI_DIR |= LED_MASK;
#endif
}

void spi_writepacket(uint8_t* data, uint16_t length)
{
    uint8_t i;

    for (i = 0; i < length; i++) PUTC(data[i])
}

void spi_readpacket(uint8_t* data, uint16_t length)
{
    uint8_t i;

    for (i = 0; i < length; i++) GETC(data[i])
}

void delay_ms(uint32_t ticks)
{
    uint32_t t = 0;
    while(t++ < ticks);
}

#if (!USE_HARDWARE_SPI)
inline void putc(uint8_t c)
{
    uint8_t i = 0;

    do
    {
        //set data
        if (c & 0x80) SPI_MOSI = 1;
        else SPI_MOSI = 0;
        //clock high
        SPI_CLK = 1;
        //shift data (msb first!)
        c <<= 1;
        //clock low
        SPI_CLK = 0;
    } while (++i < 8);
    //pull mosi to low after transmission
    SPI_MOSI = 0;
}

inline uint8_t getc()
{
    uint8_t i = 0;
    uint8_t c = 0;

    do
    {
        //clock high
        SPI_CLK = 1;
        //shift data (msb first!)
        c <<= 1;
        //set data
        c |= SPI_MISO;
        //clock low
        SPI_CLK = 0;

    } while (++i < 8);
    return c;
}

void led_on()
{
    LED = 1;
}

void led_off()
{
    LED = 0;
}

void led_toggle()
{
    LED ^= 1;
}
#endif
