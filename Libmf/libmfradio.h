#ifndef LIBMFRADIO_H
#define LIBMFRADIO_H

#include "compiler.h"

#if defined(SDCC)
#pragma callee_saves radio_read16,radio_read24,radio_read32,radio_write16,radio_write24,radio_write32
#endif

#define radio_probeirq         ax5043_probeirq
#define radio_comminit         ax5043_comminit
#define radio_commsleepexit    ax5043_commsleepexit
#define radio_reset            ax5043_reset
#define radio_readfifo         ax5043_readfifo
#define radio_writefifo        ax5043_writefifo
#define radio_enter_deepsleep  ax5043_enter_deepsleep
#define radio_wakeup_deepsleep ax5043_wakeup_deepsleep
#define RACC                   0x0c
#define FDATA                  0x029
#define FSTAT                  0x028
#define DEEPSLEEP              1
#define VREGDELAY              10

#define RADIO_SILICONREVISION  AX5043_SILICONREVISION
#define RADIO_SCRATCH          AX5043_SCRATCH
#define RADIO_PWRMODE          AX5043_PWRMODE

#define PWRMODE_PWRDOWN        0x00
#define PWRMODE_DEEPSLEEP      0x01

#define SILICONREV1            0x51
#undef SILICONREV2

#define RADIO_OK                0
#define RADIO_ERR_REVISION      1
#define RADIO_ERR_COMM          2
#define RADIO_ERR_IRQ           3
#define RADIO_ERR_WAKEUPTIMEOUT 4

/*
 * AX5043
 */
extern  void ax5043_comminit(void) ;
extern  void ax5043_commsleepexit(void) ;
extern  uint8_t ax5043_reset(void) ;
extern  void ax5043_enter_deepsleep(void) ;
extern  uint8_t ax5043_wakeup_deepsleep(void) ;
extern  void ax5043_rclk_enable(uint8_t div) ;
extern  void ax5043_rclk_disable(void) ;
extern  void ax5043_readfifo(uint8_t *ptr, uint8_t len) ;
extern  void ax5043_writefifo(const uint8_t *ptr, uint8_t len) ;

#endif /* LIBMFRADIO_H */
