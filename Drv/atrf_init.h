#ifndef ATRF_INIT_H_INCLUDED
#define ATRF_INIT_H_INCLUDED

#include "pal_trx_spi_block_mode.h"

/* === MACROS ============================================================== */

#define SUCCESS                     0
#define FAILURE                     -1

/*
 * Time gap between each poll access in microseconds.
 * If the value is equal to zero, no time gap is applied.
 */
#define POLL_TIME_GAP              10

/* Maximum PLL lock duration in us */
#define MAX_PLL_LOCK_DURATION      200

/*
 * TAL default values
 */

/**
 * Default value of frequency
 */
#define RF09_FRQ_DEF                868710000
#define RF24_FRQ_DEF                2401200000

/**
 * Default value of channel
 */
#define RF_CHANNEL_DEF              0x00

/**
 * Default value of channel spacing
 */
#define RF_CH_SPACING_DEF           1200000

#ifdef __cplusplus
extern "C" {
#endif

/**
     * @brief Initializes the TRX
     *
     * This function is called to initialize the TRX. The transceiver is
     * initialized, and the TRX state machine is set to IDLE state.
     *
     * @return SUCCESS  if the transceiver state is changed to TRX_OFF and the
     *                 current device part number and version number are correct;
     *         FAILURE otherwise
     * @ingroup atrfApi
     */
    int8_t trx_init(trx_id_t trx_id);

    /**
     * @brief Switches receiver on or off
     *
     * This function switches the receiver on or off.
     *
     * @param trx_id Transceiver identifier
     * @param state New state of receiver
     *
     * @return
     *      - no return value
     * @ingroup atrfApi
     */
    void trx_switch_state(trx_id_t trx_id, uint8_t state);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // ATRF_INIT_H_INCLUDED
