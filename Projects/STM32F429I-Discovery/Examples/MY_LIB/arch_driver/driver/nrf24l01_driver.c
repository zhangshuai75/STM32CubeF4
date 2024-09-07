/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "spi_driver.h"
#include "gpio_driver.h"
#include "api_spi_common.h"
#include "api_gpio_common.h"
#include "nrf24l01_driver.h"
#include "api_rf_common.h"


static int spi_register_write(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t tx_data[length+1];
	uint8_t dummy;
	uint16_t i;
	
	tx_data[0] = reg;
	for(i = 1; i <= length; i++) {
		tx_data[i] = *data;
		data++;
	}
	return spi_transmit_receive(Spi, tx_data, &dummy, length+1);
}

static int spi_register_read(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	int status;
	uint8_t rx_data[length+1];
	uint16_t i;
	
	status = spi_transmit_receive(Spi, &reg, rx_data, length+1);
	for(i = 0; i < length; i++) {
		data[i] = rx_data[i+1];
	}
	return status;
}

static int tx_addr_data_test(struct device *Dev)
{
	struct nrf24l01_data *D_data = Dev->data;
	const struct nrf24l01_config *D_config = Dev->config;
	
	uint8_t *rx = D_data->value_rx_data;
	uint8_t tx[5];
	int status;
	
	status = spi_register_read(D_data->Spi, NRF24L01_READ_REG | NRF24L01_TX_ADDR, rx, 5);
	printf("%X%X%X%X%X\r\n", rx[0],rx[1],rx[2],rx[3],rx[4]);
	
	tx[0] = D_config->value_tx_config[0];
	tx[1] = D_config->value_tx_config[1];
	tx[2] = D_config->value_tx_config[2];
	tx[3] = D_config->value_tx_config[3];
	tx[4] = D_config->value_tx_config[4];
	status = spi_register_write(D_data->Spi, NRF24L01_WRITE_REG | NRF24L01_TX_ADDR, tx, 5);
	status = spi_register_read(D_data->Spi, NRF24L01_READ_REG | NRF24L01_TX_ADDR, rx, 5);
	printf("%X%X%X%X%X\r\n", rx[0],rx[1],rx[2],rx[3],rx[4]);
	
	return status;
}

static int get_data(struct device *Dev)
{
	return 0;
}

static const struct rf_common_api Nrf24l01_api = {
	.device_test = tx_addr_data_test,
	.get         = get_data,
};

static struct nrf24l01_data Nrf24l01_data;

static const struct nrf24l01_config Nrf24l01_config = {
	.value_tx_config = {0xA5,0xA5,0xA5,0xA5,0xA5},
};

static int nrf24l01_device_init(struct device *Dev)
{
	struct nrf24l01_data *D_data = Dev->data;
	
	D_data->Spi = spi4_cs1_device_binding();
	D_data->Gpio = gpio_a0_device_binding();
	spi_init(D_data->Spi);
	gpio_init(D_data->Gpio);
	printf("NRF24L01 device init\r\n");
	
	return 0;
}

struct device Nrf24l01 = {
	.api    = &Nrf24l01_api,
	.data   = &Nrf24l01_data,
	.config = &Nrf24l01_config,
	.init   = nrf24l01_device_init,
};

struct device* nrf24l01_device_binding(void)
{
	return &Nrf24l01;
}


void a0_exti_handel(void)
{
	printf("NRF24L01 IRQ handel\r\n");
}
