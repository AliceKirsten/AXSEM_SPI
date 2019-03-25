/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/


#ifndef PORT_H
#define PORT_H

#include <stdint.h>
#include "ax8052regaddr.h"
#include "ax8052f143.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#define USE_HARDWARE_SPI (0)

#define USR_POUT         (PORTC)
#define USR_PDIR         (DIRC)

#define LMX_CE           (0x01)

#define CS_POUT          (PORTB)
#define CS_PDIR          (DIRB)

#define LMX_LE           (0x01)
#define FPGA_CS          (0x20)

#define LMX_ENABLE       USR_POUT |= LMX_CE;
#define LMX_DISABLE      USR_POUT &= ~LMX_CE;
#define LMX_CS_HI        CS_POUT |= LMX_LE;
#define LMX_CS_LO        CS_POUT &= ~LMX_LE;

#define FPGA_CS_HI       CS_POUT |= FPGA_CS;
#define FPGA_CS_LO       CS_POUT &= ~FPGA_CS;

#if (USE_HARDWARE_SPI)
//hardware spi settings
#define LMX_CLK          (0x02)
#define LMX_MOSI         (0x04)
#define LMX_MISO         (0x08)

#define LMX_SPMODE       (0x01)     //mode - master
#define LMX_CLKSRC       (0x06)     //clock - SysCore, prescaler - 1

#define SPI_MODE        (SPMODE)
#define SPI_CLKCFG      (SPCLKSRC)
#define SPI_DATA        (SPSHREG)
#define SPI_STATUS      (SPSTATUS)

#define LMX_TX_DONE      SPI_STATUS & 0x04
#define LMX_PUTC(c)      do {                       \
                            SPI_DATA = c;           \
                            while(!LMX_TX_DONE);    \
                         } while(0);
#define LMX_RX_FULL      SPI_STATUS & 0x01
#define LMX_GETC(c)      do {                       \
                            while(!LMX_RX_FULL);    \
                            c = SPI_DATA;           \
                         } while(0);
#else
//software spi settings
#define LMX_CLK          (0x08)
#define LMX_MOSI         (0x10)
#define LMX_MISO         (0x04)

inline void lmx_putc(uint8_t c);
inline uint8_t lmx_getc();
#define LMX_PUTC(c)      do { lmx_putc(c); } while(0);
#define LMX_GETC(c)      do { c = lmx_getc(); } while(0);

#define LED              (0x02)

void led_on();
void led_off();
void led_toggle();
#endif

void periph_init();
void lmx_spi_writepacket(uint32_t data);
uint32_t lmx_spi_readpacket();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PORT_H */


