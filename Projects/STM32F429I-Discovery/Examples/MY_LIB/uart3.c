/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "uart3.h"
#include "api_define.h"


UART_HandleTypeDef UartHandle3;

static void _UART3_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef UART3_DMA
	static DMA_HandleTypeDef DmaHandle_uart3_tx;
	static DMA_HandleTypeDef DmaHandle_uart3_rx;
	
	UART_HandleTypeDef *pUartHandle3;
	pUartHandle3 = &UartHandle3;
	#endif
	
	USART3_TX_GPIO_CLK_ENABLE();
	USART3_RX_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = USART3_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = USART3_TX_AF;
	HAL_GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = USART3_RX_PIN;
	GPIO_InitStruct.Alternate = USART3_RX_AF;
	HAL_GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStruct);
	
	USART3_CLK_ENABLE();
	USART3_FORCE_RESET();
	USART3_RELEASE_RESET();
	
	#ifdef UART3_IT
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	
	#ifdef UART3_DMA
	DMA_UART3_CLK_ENABLE();
	
	DmaHandle_uart3_tx.Instance                 = DMA_UART3_TX_STREAM;
	DmaHandle_uart3_tx.Init.Channel             = DMA_UART3_TX_CHANNEL;
	DmaHandle_uart3_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_uart3_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_uart3_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_uart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_uart3_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_uart3_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_uart3_tx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_uart3_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_uart3_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_uart3_tx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_uart3_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pUartHandle3, hdmatx, DmaHandle_uart3_tx);
	HAL_DMA_Init(&DmaHandle_uart3_tx);
	
	DmaHandle_uart3_rx.Instance                 = DMA_UART3_RX_STREAM;
	DmaHandle_uart3_rx.Init.Channel             = DMA_UART3_RX_CHANNEL;
	DmaHandle_uart3_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_uart3_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_uart3_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_uart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_uart3_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_uart3_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_uart3_rx.Init.Priority            = DMA_PRIORITY_LOW;
	DmaHandle_uart3_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	DmaHandle_uart3_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_uart3_rx.Init.MemBurst            = DMA_MBURST_INC4;
	DmaHandle_uart3_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
	
	__HAL_LINKDMA(pUartHandle3, hdmarx, DmaHandle_uart3_rx);
	HAL_DMA_Init(&DmaHandle_uart3_rx);
	
	HAL_NVIC_SetPriority(DMA_UART3_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_UART3_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_UART3_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_UART3_RX_IRQn);
	#endif
	#endif
}

static void uart3_init(void)
{
	if(HAL_UART_GetState(&UartHandle3) == HAL_UART_STATE_RESET)
	{
		UartHandle3.Instance          = USART3;
		UartHandle3.Init.BaudRate     = USART3_BAUDRATE;
		UartHandle3.Init.WordLength   = UART_WORDLENGTH_8B;
		UartHandle3.Init.StopBits     = UART_STOPBITS_1;
		UartHandle3.Init.Parity       = UART_PARITY_NONE;
		UartHandle3.Init.Mode         = UART_MODE_TX_RX;
		UartHandle3.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
		UartHandle3.Init.OverSampling = UART_OVERSAMPLING_16;
		
		_UART3_MspInit();
		HAL_UART_Init(&UartHandle3);
		printf("UART3 HAL init\r\n");
	}
}

static void _UART3_MspDeInit(void)
{
	HAL_GPIO_DeInit(USART3_TX_GPIO_PORT, USART3_TX_PIN);
	HAL_GPIO_DeInit(USART3_RX_GPIO_PORT, USART3_RX_PIN);
	
	HAL_UART_DeInit(&UartHandle3);
	
	#ifdef UART3_IT
	HAL_NVIC_DisableIRQ(USART3_IRQn);
	
	#ifdef UART3_DMA
	HAL_DMA_DeInit(UartHandle3.hdmatx);
	HAL_DMA_DeInit(UartHandle3.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_UART3_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_UART3_RX_IRQn);
	#endif
	#endif
}

static void uart3_error(void)
{
	_UART3_MspDeInit();
	uart3_init();
}

static int uart3_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit(&UartHandle3, data, length, timeout);
	if(e_status == HAL_ERROR) {
		uart3_error();
	}
	return e_status;
}

static int uart3_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive(&UartHandle3, data, length, timeout);
	if(e_status == HAL_ERROR) {
		uart3_error();
	}
	return e_status;
}

#ifdef UART3_IT
static int uart3_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit_IT(&UartHandle3, data, length);
	if(e_status == HAL_ERROR) {
		uart3_error();
	}
	return e_status;
}

static int uart3_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive_IT(&UartHandle3, data, length);
	if(e_status == HAL_ERROR) {
		uart3_error();
	}
	return e_status;
}

#ifdef UART3_DMA
static int uart3_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Transmit_DMA(&UartHandle3, data, length);
	if(e_status == HAL_ERROR) {
		uart3_error();
	}
	return e_status;
}

static int uart3_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_UART_Receive_DMA(&UartHandle3, data, length);
	if(e_status == HAL_ERROR) {
		uart3_error();
	}
	return e_status;
}
#endif
#endif

static struct uart_api Uart3_api = {
	.init         = uart3_init,
	.transmit     = uart3_transmit,
	.receive      = uart3_receive,
	#ifdef UART3_IT
	.transmit_it  = uart3_transmit_it,
	.receive_it   = uart3_receive_it,
	#ifdef UART3_DMA
	.transmit_dma = uart3_transmit_dma,
	.receive_dma  = uart3_receive_dma,
	#endif
	#endif
};

#ifdef UART3_IT
void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle3);
}

#ifdef UART3_DMA
void DMA_UART3_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(UartHandle3.hdmatx);
}

void DMA_UART3_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(UartHandle3.hdmarx);
}
#endif
#endif

struct uart_api* uart3_binding(void)
{
	return &Uart3_api; //¶Ç»¼¦ì¸m
}
