#ifndef RADIO_H_INCLUDED
#define RADIO_H_INCLUDED

#include "compiler.h"
#include "nbfi.h"

/*
 * AX5043
 */
//extern __reentrantb uint8_t ax5043_reset(void) __reentrant;

nbfi_status_t   RF_Init(nbfi_phy_channel_t  phy_channel,
                        rf_antenna_t        antenna,
                        int8_t              power,
                        uint32_t            freq);
nbfi_status_t   RF_Deinit();
nbfi_status_t   RF_Transmit(uint8_t*        pkt,
                            uint8_t         len,
                            rf_padding_t    padding,
                            rf_blocking_t   blocking);


#endif // RADIO_H_INCLUDED
