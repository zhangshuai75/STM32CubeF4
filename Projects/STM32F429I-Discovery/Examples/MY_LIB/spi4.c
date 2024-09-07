/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "spi4.h"


SPI_HandleTypeDef SpiHandle4;

static void _SPI4_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef SPI4_DMA
	static DMA_HandleTypeDef DmaHandle_spi4_tx;
	static DMA_HandleTypeDef DmaHandle_spi4_rx;
	
	SPI_HandleTypeDef *pSpiHandle4;
	pSpiHandle4 = &SpiHandle4;
	#endif
	
	SPI4_SCK_GPIO_CLK_ENABLE();
	SPI4_MISO_GPIO_CLK_ENABLE();
	SPI4_MOSI_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = SPI4_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = SPI4_SCK_AF;
	HAL_GPIO_Init(SPI4_SCK_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI4_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI4_MISO_AF;
	HAL_GPIO_Init(SPI4_MISO_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI4_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI4_MOSI_AF;
	HAL_GPIO_Init(SPI4_MOSI_GPIO_PORT, &GPIO_InitStruct);
	
	SPI4_CLK_ENABLE();
	SPI4_FORCE_RESET();
	SPI4_RELEASE_RESET();
	
	#ifdef SPI4_IT
	HAL_NVIC_SetPriority(SPI4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(SPI4_IRQn);
	
	#ifdef SPI4_DMA
	DMA_SPI4_CLK_ENABLE();
	
	DmaHandle_spi4_tx.Instance                 = DMA_SPI4_TX_STREAM;
	DmaHandle_spi4_tx.Init.Channel             = DMA_SPI4_TX_CHANNEL;
	DmaHandle_spi4_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_spi4_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi4_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi4_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi4_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi4_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi4_tx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_spi4_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_spi4_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_spi4_tx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_spi4_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pSpiHandle4, hdmatx, DmaHandle_spi4_tx);
	HAL_DMA_Init(&DmaHandle_spi4_tx);
	
	DmaHandle_spi4_rx.Instance                 = DMA_SPI4_RX_STREAM;
	DmaHandle_spi4_rx.Init.Channel             = DMA_SPI4_RX_CHANNEL;
	DmaHandle_spi4_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_spi4_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi4_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi4_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi4_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi4_rx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_spi4_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_spi4_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_spi4_rx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_spi4_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pSpiHandle4, hdmarx, DmaHandle_spi4_rx);
	HAL_DMA_Init(&DmaHandle_spi4_rx);
	
	HAL_NVIC_SetPriority(DMA_SPI4_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_SPI4_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_SPI4_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_SPI4_RX_IRQn);
	#endif
	#endif
}

void spi4_init(void)
{
	if(HAL_SPI_GetState(&SpiHandle4) == HAL_SPI_STATE_RESET)
	{
		SpiHandle4.Instance               = SPI4;
		SpiHandle4.Init.Mode              = SPI_MODE_MASTER;
		SpiHandle4.Init.Direction         = SPI_DIRECTION_2LINES;
		SpiHandle4.Init.DataSize          = SPI_DATASIZE_8BIT;
		SpiHandle4.Init.CLKPolarity       = SPI4_CLKPOLARITY;
		SpiHandle4.Init.CLKPhase          = SPI4_CLKPHASE;
		SpiHandle4.Init.NSS               = SPI_NSS_SOFT;
		SpiHandle4.Init.BaudRatePrescaler = SPI4_BAUDRATEPRESCALER;
		SpiHandle4.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		SpiHandle4.Init.TIMode            = SPI_TIMODE_DISABLE;
		SpiHandle4.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		SpiHandle4.Init.CRCPolynomial     = 7;
		
		_SPI4_MspInit();
		HAL_SPI_Init(&SpiHandle4);
	}
}

void _SPI4_MspDeInit(void)
{
	HAL_GPIO_DeInit(SPI4_SCK_GPIO_PORT, SPI4_SCK_PIN);
	HAL_GPIO_DeInit(SPI4_MISO_GPIO_PORT, SPI4_MISO_PIN);
	HAL_GPIO_DeInit(SPI4_MOSI_GPIO_PORT, SPI4_MOSI_PIN);
	
	HAL_SPI_DeInit(&SpiHandle4);
	
	#ifdef SPI4_IT
	HAL_NVIC_DisableIRQ(SPI4_IRQn);
	
	#ifdef SPI4_DMA
	HAL_DMA_DeInit(SpiHandle4.hdmatx);
	HAL_DMA_DeInit(SpiHandle4.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_SPI4_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_SPI4_RX_IRQn);
	#endif
	#endif
}

#ifdef SPI4_IT
void SPI4_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&SpiHandle4);
}

#ifdef SPI4_DMA
void DMA_SPI4_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle4.hdmatx);
}

void DMA_SPI4_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle4.hdmarx);
}
#endif
#endif
