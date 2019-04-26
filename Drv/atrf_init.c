/**
 * @file atrf_init.c
 *
 * @brief This file implements functions for initializing ATRF and reset.
 *
 */

/* === INCLUDES ============================================================ */

#include "atrf_init.h"

/* === GLOBALS ============================================================= */

rf_cmd_state_t trx_state[RFBOTH];

/* === IMPLEMENTATION ====================================================== */

/**
 * @brief Resets transceiver(s)
 *
 * @param trx_id Transceiver identifier
 *
 * @return SUCCESS  if the transceiver returns TRX_OFF
 *         FAILURE  otherwise
 */
static int8_t trx_reset(trx_id_t trx_id)
{
    trx_id_t i = 0;
    uint8_t rst = 0;
    int8_t status = SUCCESS;

    if (trx_id == RFBOTH) //both trx
    {
        /* Trigger reset of all the device*/
        pal_dev_reg_write(RF09, RG_RF_RST, RF_RESET);
        PAL_WAIT_1_US();

        /* Check for trx status */
        for (i = (trx_id_t)0; i < RFBOTH; i++)
        {
            rst = 0;
            do
            {
                trx_state[i] = (rf_cmd_state_t)pal_dev_reg_read(i, RG_RF09_STATE);
                rst++;
            } while ((trx_state[i] != RF_TRXOFF) && rst < 100);
            if (trx_state[i] != RF_TRXOFF) status = FAILURE;
        }
    }
    else //single trx
    {
        /* Trigger reset of only a single trx_id; i.e. RF09 or RF24 */
        pal_dev_reg_write(trx_id, RG_RF09_CMD, RF_RESET);
        PAL_WAIT_1_US();

        /* Check for trx status */
        do
        {
            trx_state[trx_id] = (rf_cmd_state_t)pal_dev_reg_read(trx_id, RG_RF09_STATE);
            rst++;
        } while ((trx_state[trx_id] != RF_TRXOFF) && rst < 100);
        if (trx_state[trx_id] != RF_TRXOFF) status = FAILURE;
    }

    return status;
}

/**
 * @brief Applies channel settings by writing them to the transceiver
 *
 * @param trx_id Transceiver identifier
 *
 * @return SUCCESS if channel setting is successful
 */

uint8_t locked;

static int8_t apply_channel_settings(trx_id_t trx_id)
{
    uint32_t freq, spacing;
    uint16_t freq_val;


    /* Offset handling for 2.4GHz only */
    if (trx_id == RF24) freq = RF24_FRQ_DEF - 1500000000;
    else freq = RF09_FRQ_DEF;
    freq_val = (uint16_t)(freq / 25000); /* adjust to register scaling */

    /* Set channel spacing */
    spacing = RF_CH_SPACING_DEF;
    spacing /= 25000; /* adjust to register scaling */

    pal_dev_write(trx_id, RG_RF09_CCF0L, (uint8_t*)&freq_val, 2);
    pal_dev_reg_write(trx_id, RG_RF09_CS, (uint8_t)spacing);

    /*
     * Set channel and channel mode.
     * Touching the CNM register forces the calculation of the actual frequency.
     */
    pal_dev_reg_write(trx_id, RG_RF09_CNL, RF_CHANNEL_DEF);
    pal_dev_reg_write(trx_id, RG_RF09_CNM, RF_CHANNEL_DEF);

    /* Switch to TXPREP to trigger PLL settling process */
    trx_switch_state(trx_id, RF_TXPREP);
    /* Wait until channel set is completed */
    delay_ms(MAX_PLL_LOCK_DURATION);
    locked = pal_dev_bit_read(trx_id, SR_RF09_PLL_LS);
    if (!locked) return FAILURE;

	return SUCCESS;
}

/**
 * @brief Configures the PHY
 *
 * This function configures the PHY related settings.
 *
 * @param trx_id Transceiver identifier
 *
 * @return SUCCESS if the configuration was successful
 */
static int8_t config_phy(trx_id_t trx_id)
{
    uint8_t rx[4];
	int8_t status = SUCCESS;
	/* Modulation Option custom: BW nom.: 156 kHz */
	uint8_t sr = 1, rxrcut = 0, bw = 0, ifs = 0, agci = 0, pdt = 3;

	/* Rx settings: RXBWC, RXDFE, AGCC, AGCS */
    /* RXBWC */
    rx[0] = (ifs << RXBWC_IFS_SHIFT) | (bw << RXBWC_BW_SHIFT);
    /* RXDFE */
    rx[1] = (rxrcut << RXDFE_RCUT_SHIFT) | (sr << RXDFE_SR_SHIFT);
	/* AGCC */
	rx[2] = 0x81 | (agci << AGCC_AGCI_SHIFT) | (0 << AGCC_AVGS_SHIFT);
	/* AGCS */
	rx[3] = (pdt << AGCS_TGT_SHIFT) | (0x17 << AGCS_GCW_SHIFT); /* AGC target: -30 dB */
	pal_dev_write(trx_id, RG_RF09_RXBWC, rx, 4);

    /* Sets channel frequency and spacing */
    status = apply_channel_settings(trx_id);
    /* Sets the energy measurement duration */
	if (status == SUCCESS) pal_dev_reg_write(trx_id, RG_RF09_EDD, 0x05);

	return status;
}

/**
     * @brief Initializes the TRX
     *
     * This function is called to initialize the TRX. The transceiver is
     * initialized, and the TRX state machine is set to IDLE state.
     *
     * @return SUCCESS  if the transceiver state is changed to TRX_OFF and the
     *                 current device part number and version number are correct;
     *         FAILURE otherwise
     */




int8_t trx_init(trx_id_t trx_id)
{
    /* Reset trx */
    if (trx_reset(RFBOTH) != 0) return FAILURE;

    /* Check if RF215 is connected */
    if ((pal_dev_reg_read(RF09, RG_RF_PN) != 0x34) || (pal_dev_reg_read(RF09, RG_RF_VN) != 0x03)) return FAILURE;

//RF_EDOFF

    /* Single Energy Detection */
   // pal_dev_bit_write(trx_id, SR_RF09_EDC_EDM, RF_EDSINGLE);
    /* Configure transceiver */
    pal_dev_reg_write(trx_id, RG_BBC0_IRQM, BB_IRQ_NO_IRQ);
    pal_dev_reg_write(trx_id, RG_BBC1_IRQM, BB_IRQ_NO_IRQ);
    pal_dev_reg_write(trx_id, RG_RF09_IRQM, RF_IRQ_ALL_IRQ);
    /* RF part: RF enable, BB disabled, IQIF enabled */
    pal_dev_bit_write(trx_id, SR_RF_IQIFC1_CHPM, RF_MODE_RF);
    /* Set LVDS clock skew */
    pal_dev_bit_write(trx_id, SR_RF_IQIFC1_SKEWDRV, 0x02);
    /* Set LVDS current and voltage to max */
    pal_dev_bit_write(trx_id, SR_RF_IQIFC0_CMV, 0x03);
    pal_dev_bit_write(trx_id, SR_RF_IQIFC0_DRV, 0x03);
    /* Set I/Q IF in common mode */
    pal_dev_bit_write(trx_id, SR_RF_IQIFC0_CMV1V2, 1);
    /* Enable embedded control at I/Q IF */
    pal_dev_bit_write(trx_id, SR_RF_IQIFC0_EEC, 0);

    pal_dev_bit_write(trx_id, SR_RF_IQIFC0_EXTLB, 0);

    /* Keep analog voltage regulator on during TRXOFF */
    pal_dev_bit_write(trx_id, SR_RF09_AUXS_AVEN, 1);

    /* Config RF_FE */
    if (config_phy(trx_id) != SUCCESS) return FAILURE;




    return SUCCESS;
} /* tal_init() */


/**
 * @brief Switches receiver on or off
 *
 * This function switches the receiver on or off.
 *
 * @param trx_id Transceiver identifier
 * @param state New state of receiver
 *
 * @return
 *        no return value
 *
 */


void trx_switch_state(trx_id_t trx_id, uint8_t state)
{
    if (state == trx_state[trx_id]) return;

    switch (state)
    {
        case RF_SLEEP:
        case RF_TRXOFF:
            pal_dev_reg_write(trx_id, RG_RF09_CMD, RF_TRXOFF);
            if (state == RF_TRXOFF) break;
            pal_dev_reg_write(trx_id, RG_RF09_CMD, RF_SLEEP);
            break;
        case RF_RX:
        case RF_TXPREP:
            pal_dev_reg_write(trx_id, RG_RF09_CMD, RF_TXPREP);
            do
            {
                trx_state[trx_id] = (rf_cmd_state_t)pal_dev_reg_read(trx_id, RG_RF09_STATE);
                if (trx_state[trx_id] != RF_TXPREP)
                {
        #if (POLL_TIME_GAP > 0)
                    delay_ms(POLL_TIME_GAP); /* Delay to reduce SPI storm */
        #endif
                }
            }
            while (trx_state[trx_id] != RF_TXPREP);
            if (state == RF_TXPREP) break;
            pal_dev_reg_write(trx_id, RG_RF09_CMD, RF_RX);
            do
            {
                trx_state[trx_id] = (rf_cmd_state_t)pal_dev_reg_read(trx_id, RG_RF09_STATE);
                if (trx_state[trx_id] != RF_RX)
                {
        #if (POLL_TIME_GAP > 0)
                    delay_ms(POLL_TIME_GAP); /* Delay to reduce SPI storm */
        #endif
                }
            }
            while (trx_state[trx_id] != RF_RX);
            break;
        default:
            break;
    }
    trx_state[trx_id] = state;



}
