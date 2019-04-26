/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/


#ifndef PORT_H
#define PORT_H

#include "compiler.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#define delay_20ms      (5678)
#define delay_5s        (1419500)

#define USE_HARDWARE_SPI (0)

#define SPI_DIR          (DIRC)
#define CS_DIR           (DIRB)
#define AT_DIR           (DIRA)

#define LMX_CE           (PORTB_0)
#define LMX_CS           (PORTC_0)
#define FPGA_CS          (PORTB_5)
#define ATRF_CS          (PORTA_5)

#define LMX_CE_MASK      (0x01)
#define LMX_CS_MASK      (0x01)
#define FPGA_CS_MASK     (0x20)
#define ATRF_CS_MASK     (0x20)

#define LMX_ENABLE       LMX_CE = 1;
#define LMX_DISABLE      LMX_CE = 0;

#if (USE_HARDWARE_SPI)
//hardware spi settings
#define SPI_CLK          (PORTC_1)
#define SPI_MOSI         (PORTC_2)
#define SPI_MISO         (PINC_3)

#define SPI_CLK_MASK     (0x02)
#define SPI_MOSI_MASK    (0x04)
#define SPI_MISO_MASK    (0x08)

#define SPI_SPMODE       (0x01)     //mode - master
#define SPI_CLKSRC       (0x06)     //clock - SysCore, prescaler - 1

#define SPI_MODE        (SPMODE)
#define SPI_CLKCFG      (SPCLKSRC)
#define SPI_DATA        (SPSHREG)
#define SPI_STATUS      (SPSTATUS)

#define TX_DONE          SPI_STATUS & 0x04
#define PUTC(c)          do {                       \
                            SPI_DATA = c;           \
                            while(!TX_DONE);        \
                         } while(0);
#define RX_FULL          SPI_STATUS & 0x01
#define GETC(c)         do {                        \
                            while(!RX_FULL);        \
                            c = SPI_DATA;           \
                         } while(0);
#else
//software spi settings
#define SPI_CLK          (PORTC_3)
#define SPI_MOSI         (PORTC_4)
#define SPI_MISO         (PINC_2)

#define SPI_CLK_MASK     (0x08)
#define SPI_MOSI_MASK    (0x10)
#define SPI_MISO_MASK    (0x04)

inline void putc(uint8_t c);
inline uint8_t getc();
#define PUTC(c)          do { putc(c); } while(0);
#define GETC(c)          do { c = getc(); } while(0);

#define LED              (PORTC_1)
#define LED_MASK         (0x02)

void led_on();
void led_off();
void led_toggle();
#endif

void periph_init();
void spi_writepacket(uint8_t* data, uint16_t length);
void spi_readpacket(uint8_t* data, uint16_t length);

void delay_ms(uint32_t ticks);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PORT_H */
