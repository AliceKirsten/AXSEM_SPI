/**
 * @file pal_trx_spi_block_mode.c
 *
 * @brief SPI based TRX access API using block mode
 *
 * This file implements the SPI based TRX access API.
 *
 * $Id: pal_trx_spi_block_mode.c 35560 2014-01-15 09:31:48Z uwalter $
 *
 * @author    Atmel Corporation: http://www.atmel.com
 * @author    Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2013, Atmel Corporation All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

/* === Includes ============================================================ */

#include "pal_trx_spi_block_mode.h"

/* === Externals ============================================================ */

/* === Macros =============================================================== */

#define TRX_SPI_CMD_WR  0x80       // SPI command  write
#define TRX_SPI_CMD_RD  0x00       // SPI command  read

/* === Types =============================================================== */

/* === Implementations ====================================================== */
uint16_t reg_addr;
/**
 * @brief Writes data into a transceiver registers
 *
 * This function writes data into transceiver registers.
 *
 * @param   addr Start address of the trx registers
 * @param   data Data to be written to trx registers
 * @param   length Amount of bytes to be written
 */
void pal_dev_write(trx_id_t dev_id, uint16_t addr, uint8_t *data, uint16_t length)
{
    uint8_t pkt[MAX_TRX_LEN];
    uint16_t i;

    /* Calculate register offset */
    CALC_REG_OFFSET(dev_id);
    reg_addr = GET_REG_ADDR(addr);

    /* Prepare the command byte and address MSB */
    pkt[1] = (uint8_t)(reg_addr & 0xff);
    pkt[0] = (uint8_t)(TRX_SPI_CMD_WR | (reg_addr >> 8));
    for (i = 0; i < length; i++) pkt[i+2] = data[i];

    ENTER_TRX_REGION();

    /* Send the register write command and data buffer bytes */
	spi_writepacket(pkt, length+2);

    LEAVE_TRX_REGION();
}

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
void pal_dev_read(trx_id_t dev_id, uint16_t addr, uint8_t *data, uint16_t length)
{
    /* Calculate register offset */
    CALC_REG_OFFSET(dev_id);
    reg_addr = GET_REG_ADDR(addr);

    ENTER_TRX_REGION();

    /* Send the register read command */
    PUTC(reg_addr >> 8)
    PUTC(reg_addr)

    /* Read data buffer bytes */
	spi_readpacket(data, length);

    LEAVE_TRX_REGION();
}

/**
 * @brief Writes data into a transceiver register
 *
 * This function writes a value into transceiver register.
 *
 * @param   addr Address of the trx register
 * @param   data Data to be written to trx register
 */
void pal_dev_reg_write(trx_id_t dev_id, uint16_t addr, uint8_t data)
{
	pal_dev_write(dev_id, addr, &data, 1);
}

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
uint8_t pal_dev_reg_read(trx_id_t dev_id, uint16_t addr)
{
	uint8_t ret_val;

	pal_dev_read(dev_id, addr, &ret_val, 1);

	return ret_val;
}

/**
 * @brief Subregister read
 *
 * @param   addr  Register address
 * @param   mask  Bit mask of the subregister
 * @param   pos   Bit position of the subregister
 *
 * @return  value of the read bit(s)
 */
uint8_t pal_dev_bit_read(trx_id_t dev_id, uint16_t addr, uint8_t mask, uint8_t pos)
{
    uint8_t ret;

    ret = pal_dev_reg_read(dev_id, addr);
    ret &= mask;
    ret >>= pos;

    return ret;
}

/**
 * @brief Subregister write
 *
 * @param[in]   addr  Register address
 * @param[in]   mask  Bit mask of the subregister
 * @param[in]   pos   Bit position of the subregister
 * @param[out]  new_value  Data, which is muxed into the register
 */
void pal_dev_bit_write(trx_id_t dev_id, uint16_t addr, uint8_t mask, uint8_t pos, uint8_t new_value)
{
    uint8_t current_reg_value;

    current_reg_value = pal_dev_reg_read(dev_id, addr);
    current_reg_value &= (uint8_t)~(uint32_t)mask;  // Implicit casting required to avoid IAR Pa091.
    new_value <<= pos;
    new_value &= mask;
    new_value |= current_reg_value;
    pal_dev_reg_write(dev_id, addr, new_value);
}

/* EOF */
