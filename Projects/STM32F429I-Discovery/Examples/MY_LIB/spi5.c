/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "spi5.h"


SPI_HandleTypeDef SpiHandle5;

static void _SPI5_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef SPI5_DMA
	static DMA_HandleTypeDef DmaHandle_spi5_tx;
	static DMA_HandleTypeDef DmaHandle_spi5_rx;
	
	SPI_HandleTypeDef *pSpiHandle5;
	pSpiHandle5 = &SpiHandle5;
	#endif
	
	SPI5_SCK_GPIO_CLK_ENABLE();
	SPI5_MISO_GPIO_CLK_ENABLE();
	SPI5_MOSI_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = SPI5_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = SPI5_SCK_AF;
	HAL_GPIO_Init(SPI5_SCK_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI5_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI5_MISO_AF;
	HAL_GPIO_Init(SPI5_MISO_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI5_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI5_MOSI_AF;
	HAL_GPIO_Init(SPI5_MOSI_GPIO_PORT, &GPIO_InitStruct);
	
	SPI5_CLK_ENABLE();
	SPI5_FORCE_RESET();
	SPI5_RELEASE_RESET();
	
	#ifdef SPI5_IT
	HAL_NVIC_SetPriority(SPI5_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(SPI5_IRQn);
	
	#ifdef SPI5_DMA
	DMA_SPI5_CLK_ENABLE();
	
	DmaHandle_spi5_tx.Instance                 = DMA_SPI5_TX_STREAM;
	DmaHandle_spi5_tx.Init.Channel             = DMA_SPI5_TX_CHANNEL;
	DmaHandle_spi5_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_spi5_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi5_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi5_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi5_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi5_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi5_tx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_spi5_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_spi5_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_spi5_tx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_spi5_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pSpiHandle5, hdmatx, DmaHandle_spi5_tx);
	HAL_DMA_Init(&DmaHandle_spi5_tx);
	
	DmaHandle_spi5_rx.Instance                 = DMA_SPI5_RX_STREAM;
	DmaHandle_spi5_rx.Init.Channel             = DMA_SPI5_RX_CHANNEL;
	DmaHandle_spi5_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_spi5_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi5_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi5_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi5_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi5_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi5_rx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_spi5_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_spi5_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_spi5_rx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_spi5_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pSpiHandle5, hdmarx, DmaHandle_spi5_rx);
	HAL_DMA_Init(&DmaHandle_spi5_rx);
	
	HAL_NVIC_SetPriority(DMA_SPI5_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_SPI5_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_SPI5_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_SPI5_RX_IRQn);
	#endif
	#endif
}

void spi5_init(void)
{
	if(HAL_SPI_GetState(&SpiHandle5) == HAL_SPI_STATE_RESET)
	{
		SpiHandle5.Instance               = SPI5;
		SpiHandle5.Init.Mode              = SPI_MODE_MASTER;
		SpiHandle5.Init.Direction         = SPI_DIRECTION_2LINES;
		SpiHandle5.Init.DataSize          = SPI_DATASIZE_8BIT;
		SpiHandle5.Init.CLKPolarity       = SPI5_CLKPOLARITY;
		SpiHandle5.Init.CLKPhase          = SPI5_CLKPHASE;
		SpiHandle5.Init.NSS               = SPI_NSS_SOFT;
		SpiHandle5.Init.BaudRatePrescaler = SPI5_BAUDRATEPRESCALER;
		SpiHandle5.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		SpiHandle5.Init.TIMode            = SPI_TIMODE_DISABLE;
		SpiHandle5.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		SpiHandle5.Init.CRCPolynomial     = 7;
		
		_SPI5_MspInit();
		HAL_SPI_Init(&SpiHandle5);
	}
}

void _SPI5_MspDeInit(void)
{
	HAL_GPIO_DeInit(SPI5_SCK_GPIO_PORT, SPI5_SCK_PIN);
	HAL_GPIO_DeInit(SPI5_MISO_GPIO_PORT, SPI5_MISO_PIN);
	HAL_GPIO_DeInit(SPI5_MOSI_GPIO_PORT, SPI5_MOSI_PIN);
	
	HAL_SPI_DeInit(&SpiHandle5);
	
	#ifdef SPI5_IT
	HAL_NVIC_DisableIRQ(SPI5_IRQn);
	
	#ifdef SPI5_DMA
	HAL_DMA_DeInit(SpiHandle5.hdmatx);
	HAL_DMA_DeInit(SpiHandle5.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_SPI5_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_SPI5_RX_IRQn);
	#endif
	#endif
}

#ifdef SPI5_IT
void SPI5_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&SpiHandle5);
}

#ifdef SPI5_DMA
void DMA_SPI5_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle5.hdmatx);
}

void DMA_SPI5_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle5.hdmarx);
}
#endif
#endif
