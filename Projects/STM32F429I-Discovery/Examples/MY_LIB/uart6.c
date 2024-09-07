/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "uart6.h"
#include "api_define.h"


UART_HandleTypeDef UartHandle6;

static void _UART6_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef UART6_DMA
	static DMA_HandleTypeDef DmaHandle_uart6_tx;
	static DMA_HandleTypeDef DmaHandle_uart6_rx;
	
	UART_HandleTypeDef *pUartHandle6;
	pUartHandle6 = &UartHandle6;
	#endif
	
	USART6_TX_GPIO_CLK_ENABLE();
	USART6_RX_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = USART6_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = USART6_TX_AF;
	HAL_GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = USART6_RX_PIN;
	GPIO_InitStruct.Alternate = USART6_RX_AF;
	HAL_GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStruct);
	
	USART6_CLK_ENABLE();
	USART6_FORCE_RESET();
	USART6_RELEASE_RESET();
	
	#ifdef UART6_IT
	HAL_NVIC_SetPriority(USART6_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART6_IRQn);
	
	#ifdef UART6_DMA
	DMA_UART6_CLK_ENABLE();
	
	DmaHandle_uart6_tx.Instance                 = DMA_UART6_TX_STREAM;
	DmaHandle_uart6_tx.Init.Channel             = DMA_UART6_TX_CHANNEL;
	DmaHandle_uart6_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_uart6_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_uart6_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_uart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_uart6_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_uart6_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_uart6_tx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_uart6_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_uart6_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_uart6_tx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_uart6_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pUartHandle6, hdmatx, DmaHandle_uart6_tx);
	HAL_DMA_Init(&DmaHandle_uart6_tx);
	
	DmaHandle_uart6_rx.Instance                 = DMA_UART6_RX_STREAM;
	DmaHandle_uart6_rx.Init.Channel             = DMA_UART6_RX_CHANNEL;
	DmaHandle_uart6_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_uart6_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_uart6_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_uart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_uart6_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_uart6_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_uart6_rx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_uart6_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_uart6_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_uart6_rx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_uart6_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pUartHandle6, hdmarx, DmaHandle_uart6_rx);
	HAL_DMA_Init(&DmaHandle_uart6_rx);
	
	HAL_NVIC_SetPriority(DMA_UART6_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_UART6_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_UART6_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_UART6_RX_IRQn);
	#endif
	#endif
}

static void uart6_init(void)
{
	if(HAL_UART_GetState(&UartHandle6) == HAL_UART_STATE_RESET)
	{
		UartHandle6.Instance          = USART6;
		UartHandle6.Init.BaudRate     = USART6_BAUDRATE;
		UartHandle6.Init.WordLength   = UART_WORDLENGTH_8B;
		UartHandle6.Init.StopBits     = UART_STOPBITS_1;
		UartHandle6.Init.Parity       = UART_PARITY_NONE;
		UartHandle6.Init.Mode         = UART_MODE_TX_RX;
		UartHandle6.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
		UartHandle6.Init.OverSampling = UART_OVERSAMPLING_16;
		
		_UART6_MspInit();
		HAL_UART_Init(&UartHandle6);
		printf("UART6 HAL init\r\n");
	}
}

static void _UART6_MspDeInit(void)
{
	HAL_GPIO_DeInit(USART6_TX_GPIO_PORT, USART6_TX_PIN);
	HAL_GPIO_DeInit(USART6_RX_GPIO_PORT, USART6_RX_PIN);
	
	HAL_UART_DeInit(&UartHandle6);
	
	#ifdef UART6_IT
	HAL_NVIC_DisableIRQ(USART6_IRQn);
	
	#ifdef UART6_DMA
	HAL_DMA_DeInit(UartHandle6.hdmatx);
	HAL_DMA_DeInit(UartHandle6.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_UART6_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_UART6_RX_IRQn);
	#endif
	#endif
}

static void uart6_error(void)
{
	_UART6_MspDeInit();
	uart6_init();
}

static int uart6_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit(&UartHandle6, data, length, timeout);
	if(e_status == HAL_ERROR) {
		uart6_error();
	}
	return e_status;
}

static int uart6_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive(&UartHandle6, data, length, timeout);
	if(e_status == HAL_ERROR) {
		uart6_error();
	}
	return e_status;
}

#ifdef UART6_IT
static int uart6_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit_IT(&UartHandle6, data, length);
	if(e_status == HAL_ERROR) {
		uart6_error();
	}
	return e_status;
}

static int uart6_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive_IT(&UartHandle6, data, length);
	if(e_status == HAL_ERROR) {
		uart6_error();
	}
	return e_status;
}

#ifdef UART6_DMA
static int uart6_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit_DMA(&UartHandle6, data, length);
	if(e_status == HAL_ERROR) {
		uart6_error();
	}
	return e_status;
}

static int uart6_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive_DMA(&UartHandle6, data, length);
	if(e_status == HAL_ERROR) {
		uart6_error();
	}
	return e_status;
}
#endif
#endif

static struct uart_api Uart6_api = {
	.init         = uart6_init,
	.transmit     = uart6_transmit,
	.receive      = uart6_receive,
	#ifdef UART6_IT
	.transmit_it  = uart6_transmit_it,
	.receive_it   = uart6_receive_it,
	#ifdef UART6_DMA
	.transmit_dma = uart6_transmit_dma,
	.receive_dma  = uart6_receive_dma,
	#endif
	#endif
};

#ifdef UART6_IT
void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle6);
}

#ifdef UART6_DMA
void DMA_UART6_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(UartHandle6.hdmatx);
}

void DMA_UART6_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(UartHandle6.hdmarx);
}
#endif
#endif

struct uart_api* uart6_binding(void)
{
	return &Uart6_api; //¶Ç»¼¦ì¸m
}
