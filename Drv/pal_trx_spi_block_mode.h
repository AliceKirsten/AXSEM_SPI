/**
 * @file pal_trx_spi_block_mode.h
 *
 * @brief SPI based TRX access API using block mode
 *
 * This header file declares prototypes of the SPI based TRX access API.
 *
 * $Id: pal_trx_spi_block_mode.h 35489 2013-12-19 13:22:07Z awachtle $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2012, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

/* Prevent double inclusion */
#ifndef PAL_TRX_SPI_BLOCK_MODE_H
#define PAL_TRX_SPI_BLOCK_MODE_H

/* === Includes ============================================================ */

#include "at86rf215.h"
#include "port.h"

/* === Macros =============================================================== */

#define MAX_TRX_LEN             8

/** Defines to handle register offset */
#define CALC_REG_OFFSET(var)    uint16_t offset = RF_BASE_ADDR_OFFSET * var
#define GET_REG_ADDR(reg)       offset + reg

/** Platform dependent defines */
#define ENTER_TRX_REGION();     { EA = 0; ATRF_CS = 0; } //global interrupt disable, pull cs low
#define LEAVE_TRX_REGION();     { EA = 1; ATRF_CS = 1; } //global interrupt enable, push cs high
#define PAL_WAIT_1_US()          delay_ms(1)             //delay

/* === Types =============================================================== */
/* === Externals ============================================================ */
/* === Prototypes =========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Writes data into a transceiver registers
     *
     * This function writes data into transceiver registers.
     *
     * @param   addr Start address of the trx registers
     * @param   data Data to be written to trx registers
     * @param   length Amount of bytes to be written
     */
    void pal_dev_write(trx_id_t dev_id, uint16_t addr, uint8_t *data, uint16_t length);

    /**
     * @brief Reads transceiver register values
     *
     * This function reads several bytes from transceiver registers.
     *
     * @param[in]   addr Specifies the start address of the trx register
     *              from which the data shall be read
     * @param[out]  data Pointer for read data
     * @param[in]   length Amount of bytes to be read
     *
     * @return value of the register read
     */
    void pal_dev_read(trx_id_t dev_id, uint16_t addr, uint8_t *data, uint16_t length);

    /**
     * @brief Writes data into a transceiver register
     *
     * This function writes a value into transceiver register.
     *
     * @param   addr Address of the trx register
     * @param   data Data to be written to trx register
     */
    void pal_dev_reg_write(trx_id_t dev_id, uint16_t addr, uint8_t data);

    /**
     * @brief Reads value from a transceiver register
     *
     * This function reads the current value from a transceiver register.
     *
     * @param   addr Specifies the address of the trx register
     *          from which the data shall be read
     *
     * @return value of the register read
     */
    uint8_t pal_dev_reg_read(trx_id_t dev_id, uint16_t addr);

    /**
     * @brief Subregister read
     *
     * @param   addr  Register address
     * @param   mask  Bit mask of the subregister
     * @param   pos   Bit position of the subregister
     *
     * @return  value of the read bit(s)
     */
    uint8_t pal_dev_bit_read(trx_id_t dev_id, uint16_t addr, uint8_t mask, uint8_t pos);

    /**
     * @brief Subregister write
     *
     * @param[in]   addr  Register address
     * @param[in]   mask  Bit mask of the subregister
     * @param[in]   pos   Bit position of the subregister
     * @param[out]  new_value  Data, which is muxed into the register
     */
    void pal_dev_bit_write(trx_id_t dev_id, uint16_t addr, uint8_t mask, uint8_t pos, uint8_t new_value);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* PAL_TRX_SPI_BLOCK_MODE_H */
/* EOF */
