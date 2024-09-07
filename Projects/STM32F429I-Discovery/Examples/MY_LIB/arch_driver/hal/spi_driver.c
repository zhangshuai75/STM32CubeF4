/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "spi_driver.h"
#include "api_spi_common.h"


static int transmit_data(struct device *Dev, uint8_t *data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->transmit(data, length, D_config->value_tx_timeout);
}

static int receive_data(struct device *Dev, uint8_t *data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->receive(data, length, D_config->value_rx_timeout);
}

static int receive_data32(struct device *Dev, uint32_t *data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->receive32(data, length, D_config->value_rx_timeout);
}

static int transmit_receive_data(struct device *Dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->transmit_receive(tx_data, rx_data, length, D_config->value_tx_rx_timeout);
}

static const struct spi_common_api Spi_common_api = {
	.transmit         = transmit_data,
	.receive          = receive_data,
	.receive32        = receive_data32,
	.transmit_receive = transmit_receive_data,
};


#ifdef SPI4_CS1_DEV
#include "spi4_cs1.h"
static struct spi_data Spi4_cs1_data;

static const struct spi_config Spi4_cs1_config = {
	.value_tx_timeout    = 100,
	.value_rx_timeout    = 100,
	.value_tx_rx_timeout = 100,
};

static int spi4_cs1_device_init(struct device *Dev)
{
	struct spi_data *D_data = Dev->data;
	
	D_data->Spi_cs_hal = spi4_cs1_binding();
	D_data->Spi_cs_hal->init();
	printf("SPI4_CS1 device init\r\n");
	
	return 0;
}

struct device Spi_4_cs1 = {
	.api    = &Spi_common_api,
	.data   = &Spi4_cs1_data,
	.config = &Spi4_cs1_config,
	.init   = spi4_cs1_device_init,
};

struct device* spi4_cs1_device_binding(void)
{
	return &Spi_4_cs1;
}
#endif


#ifdef SPI5_CS1_DEV
#include "spi5_cs1.h"
static struct spi_data Spi5_cs1_data;

static const struct spi_config Spi5_cs1_config = {
	.value_tx_timeout    = 100,
	.value_rx_timeout    = 100,
	.value_tx_rx_timeout = 100,
};

static int spi5_cs1_device_init(struct device *Dev)
{
	struct spi_data *D_data = Dev->data;
	
	D_data->Spi_cs_hal = spi5_cs1_binding();
	D_data->Spi_cs_hal->init();
	printf("SPI5_CS1 device init\r\n");
	
	return 0;
}

struct device Spi_5_cs1 = {
	.api    = &Spi_common_api,
	.data   = &Spi5_cs1_data,
	.config = &Spi5_cs1_config,
	.init   = spi5_cs1_device_init,
};

struct device* spi5_cs1_device_binding(void)
{
	return &Spi_5_cs1;
}
#endif
