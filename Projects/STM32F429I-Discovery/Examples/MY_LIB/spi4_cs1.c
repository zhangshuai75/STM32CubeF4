/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "spi4.h"
#include "spi4_cs1.h"
#include "api_define.h"


#define SPI4C1_HIGH()      HAL_GPIO_WritePin(SPI4C1_OUTPUT_PORT, SPI4C1_OUTPUT_PIN, GPIO_PIN_SET)
#define SPI4C1_LOW()       HAL_GPIO_WritePin(SPI4C1_OUTPUT_PORT, SPI4C1_OUTPUT_PIN, GPIO_PIN_RESET)

extern SPI_HandleTypeDef SpiHandle4;

static void spi4_cs1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SPI4C1_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = SPI4C1_OUTPUT_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	
	HAL_GPIO_Init(SPI4C1_OUTPUT_PORT, &GPIO_InitStruct);
	spi4_init();
	printf("SPI4_CS1 HAL init\r\n");
}

static void spi4_cs1_error(void)
{
	SPI4C1_OUTPUT_CLK_DISABLE();
	_SPI4_MspDeInit();
	spi4_cs1_init();
}

static int spi4_cs1_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_Transmit(&SpiHandle4, data, length, timeout);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

static int spi4_cs1_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_Receive(&SpiHandle4, data, length, timeout);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

static int spi4_cs1_receive32(uint32_t *data, uint16_t length, uint32_t timeout)
{
	int e_status;
	uint8_t rx_data[4];
	uint16_t i;
	
	for(i = 0; i < length; i++) {
		SPI4C1_LOW();
		e_status = HAL_SPI_Receive(&SpiHandle4, rx_data, 4, timeout);
		SPI4C1_HIGH();
		data[i] = (rx_data[0] << 24) | (rx_data[1] << 16) | (rx_data[2] << 8) | rx_data[3];
		if(e_status != HAL_OK) {
			spi4_cs1_error();
			return e_status;
		}
	}
	return e_status;
}

static int spi4_cs1_transmit_receive(uint8_t *tx_data, uint8_t *rx_data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_TransmitReceive(&SpiHandle4, tx_data, rx_data, length, timeout);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

#ifdef SPI4C1_IT
static int spi4_cs1_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_Transmit_IT(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

static int spi4_cs1_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_Receive_IT(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

static int spi4_cs1_transmit_receive_it(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_TransmitReceive_IT(&SpiHandle4, tx_data, rx_data, length);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

#ifdef SPI4C1_DMA
static int spi4_cs1_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_Transmit_DMA(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

static int spi4_cs1_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_Receive_DMA(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}

static int spi4_cs1_transmit_receive_dma(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	SPI4C1_LOW();
	e_status = HAL_SPI_TransmitReceive_DMA(&SpiHandle4, tx_data, rx_data, length);
	SPI4C1_HIGH();
	if(e_status != HAL_OK) {
		spi4_cs1_error();
	}
	return e_status;
}
#endif
#endif

static struct spi_api Spi4_cs1_api = {
	.init                 = spi4_cs1_init,
	.transmit             = spi4_cs1_transmit,
	.receive              = spi4_cs1_receive,
	.receive32            = spi4_cs1_receive32,
	.transmit_receive     = spi4_cs1_transmit_receive,
	#ifdef SPI4C1_IT
	.transmit_it          = spi4_cs1_transmit_it,
	.receive_it           = spi4_cs1_receive_it,
	.transmit_receive_it  = spi4_cs1_transmit_receive_it,
	#ifdef SPI4C1_DMA
	.transmit_dma         = spi4_cs1_transmit_dma,
	.receive_dma          = spi4_cs1_receive_dma,
	.transmit_receive_dma = spi4_cs1_transmit_receive_dma,
	#endif
	#endif
};

struct spi_api* spi4_cs1_binding(void)
{
	return &Spi4_cs1_api; //¶Ç»¼¦ì¸m
}
