/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "uart7.h"
#include "api_define.h"


UART_HandleTypeDef UartHandle7;

static void _UART7_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef UART7_DMA
	static DMA_HandleTypeDef DmaHandle_uart7_tx;
	static DMA_HandleTypeDef DmaHandle_uart7_rx;
	
	UART_HandleTypeDef *pUartHandle7;
	pUartHandle7 = &UartHandle7;
	#endif
	
	UART7_TX_GPIO_CLK_ENABLE();
	UART7_RX_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = UART7_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = UART7_TX_AF;
	HAL_GPIO_Init(UART7_TX_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = UART7_RX_PIN;
	GPIO_InitStruct.Alternate = UART7_RX_AF;
	HAL_GPIO_Init(UART7_RX_GPIO_PORT, &GPIO_InitStruct);
	
	UART7_CLK_ENABLE();
	UART7_FORCE_RESET();
	UART7_RELEASE_RESET();
	
	#ifdef UART7_IT
	HAL_NVIC_SetPriority(UART7_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(UART7_IRQn);
	
	#ifdef UART7_DMA
	DMA_UART7_CLK_ENABLE();
	
	DmaHandle_uart7_tx.Instance                 = DMA_UART7_TX_STREAM;
	DmaHandle_uart7_tx.Init.Channel             = DMA_UART7_TX_CHANNEL;
	DmaHandle_uart7_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_uart7_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_uart7_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_uart7_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_uart7_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_uart7_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_uart7_tx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_uart7_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_uart7_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_uart7_tx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_uart7_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pUartHandle7, hdmatx, DmaHandle_uart7_tx);
	HAL_DMA_Init(&DmaHandle_uart7_tx);
	
	DmaHandle_uart7_rx.Instance                 = DMA_UART7_RX_STREAM;
	DmaHandle_uart7_rx.Init.Channel             = DMA_UART7_RX_CHANNEL;
	DmaHandle_uart7_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_uart7_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_uart7_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_uart7_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_uart7_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_uart7_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_uart7_rx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_uart7_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_uart7_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_uart7_rx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_uart7_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pUartHandle7, hdmarx, DmaHandle_uart7_rx);
	HAL_DMA_Init(&DmaHandle_uart7_rx);
	
	HAL_NVIC_SetPriority(DMA_UART7_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_UART7_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_UART7_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_UART7_RX_IRQn);
	#endif
	#endif
}

static void uart7_init(void)
{
	if(HAL_UART_GetState(&UartHandle7) == HAL_UART_STATE_RESET)
	{
		UartHandle7.Instance          = UART7;
		UartHandle7.Init.BaudRate     = UART7_BAUDRATE;
		UartHandle7.Init.WordLength   = UART_WORDLENGTH_8B;
		UartHandle7.Init.StopBits     = UART_STOPBITS_1;
		UartHandle7.Init.Parity       = UART_PARITY_NONE;
		UartHandle7.Init.Mode         = UART_MODE_TX_RX;
		UartHandle7.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
		UartHandle7.Init.OverSampling = UART_OVERSAMPLING_16;
		
		_UART7_MspInit();
		HAL_UART_Init(&UartHandle7);
		printf("UART7 HAL init\r\n");
	}
}

static void _UART7_MspDeInit(void)
{
	HAL_GPIO_DeInit(UART7_TX_GPIO_PORT, UART7_TX_PIN);
	HAL_GPIO_DeInit(UART7_RX_GPIO_PORT, UART7_RX_PIN);
	
	HAL_UART_DeInit(&UartHandle7);
	
	#ifdef UART7_IT
	HAL_NVIC_DisableIRQ(UART7_IRQn);
	
	#ifdef UART7_DMA
	HAL_DMA_DeInit(UartHandle7.hdmatx);
	HAL_DMA_DeInit(UartHandle7.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_UART7_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_UART7_RX_IRQn);
	#endif
	#endif
}

static void uart7_error(void)
{
	_UART7_MspDeInit();
	uart7_init();
}

static int uart7_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit(&UartHandle7, data, length, timeout);
	if(e_status == HAL_ERROR) {
		uart7_error();
	}
	return e_status;
}

static int uart7_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive(&UartHandle7, data, length, timeout);
	if(e_status == HAL_ERROR) {
		uart7_error();
	}
	return e_status;
}

#ifdef UART7_IT
static int uart7_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit_IT(&UartHandle7, data, length);
	if(e_status == HAL_ERROR) {
		uart7_error();
	}
	return e_status;
}

static int uart7_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive_IT(&UartHandle7, data, length);
	if(e_status == HAL_ERROR) {
		uart7_error();
	}
	return e_status;
}

#ifdef UART7_DMA
static int uart7_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit_DMA(&UartHandle7, data, length);
	if(e_status == HAL_ERROR) {
		uart7_error();
	}
	return e_status;
}

static int uart7_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive_DMA(&UartHandle7, data, length);
	if(e_status == HAL_ERROR) {
		uart7_error();
	}
	return e_status;
}
#endif
#endif

static struct uart_api Uart7_api = {
	.init         = uart7_init,
	.transmit     = uart7_transmit,
	.receive      = uart7_receive,
	#ifdef UART7_IT
	.transmit_it  = uart7_transmit_it,
	.receive_it   = uart7_receive_it,
	#ifdef UART7_DMA
	.transmit_dma = uart7_transmit_dma,
	.receive_dma  = uart7_receive_dma,
	#endif
	#endif
};

#ifdef UART7_IT
void UART7_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle7);
}

#ifdef UART7_DMA
void DMA_UART7_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(UartHandle7.hdmatx);
}

void DMA_UART7_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(UartHandle7.hdmarx);
}
#endif
#endif

struct uart_api* uart7_binding(void)
{
	return &Uart7_api; //¶Ç»¼¦ì¸m
}
