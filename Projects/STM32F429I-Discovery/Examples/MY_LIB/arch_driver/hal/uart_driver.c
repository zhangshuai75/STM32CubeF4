/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "uart_driver.h"
#include "api_uart_common.h"


static int transmit_data(struct device *Dev, uint8_t *data, uint16_t length)
{
	struct uart_data *D_data = Dev->data;
	const struct uart_config *D_config = Dev->config;
	struct uart_api *Uart_hal = D_data->Uart_hal;
	int status;
	
	switch (D_config->e_mode) {
		case POLLING:
			status = Uart_hal->transmit(data, length, D_config->value_tx_timeout);
			break;
		case IT:
			status = Uart_hal->transmit_it(data, length);
			break;
		case DMA:
			status = Uart_hal->transmit_dma(data, length);
			break;
		default:
			return -1;
	}
	return status;
}

static int receive_data(struct device *Dev, uint8_t *data, uint16_t length)
{
	struct uart_data *D_data = Dev->data;
	const struct uart_config *D_config = Dev->config;
	struct uart_api *Uart_hal = D_data->Uart_hal;
	int status;
	
	switch (D_config->e_mode) {
		case POLLING:
			status = Uart_hal->receive(data, length, D_config->value_rx_timeout);
			break;
		case IT:
			status = Uart_hal->receive_it(data, length);
			break;
		case DMA:
			status = Uart_hal->receive_dma(data, length);
			break;
		default:
			return -1;
	}
	return status;
}

static const struct uart_common_api Uart_common_api = {
	.transmit = transmit_data,
	.receive  = receive_data,
};


#ifdef UART3_DEV
#include "uart3.h"
static struct uart_data Uart3_data;

static const struct uart_config Uart3_config = {
	.value_tx_timeout = 100,
	.value_rx_timeout = 100,
	.e_mode           = DMA,
};

static int uart3_device_init(struct device *Dev)
{
	struct uart_data *D_data = Dev->data;
	
	D_data->Uart_hal = uart3_binding();
	D_data->Uart_hal->init();
	printf("UART3 device init\r\n");
	
	return 0;
}

struct device Uart_3 = {
	.api    = &Uart_common_api,
	.data   = &Uart3_data,
	.config = &Uart3_config,
	.init   = uart3_device_init,
};

struct device* uart3_device_binding(void)
{
	return &Uart_3;
}

#ifdef UART3_IT
__weak void uart3_tx_callback_handel(struct device *Dev)
{
}
__weak void uart3_rx_callback_handel(struct device *Dev)
{
}
__weak void uart3_error_callback_handel(struct device *Dev)
{
}
#endif
#endif


#ifdef UART6_DEV
#include "uart6.h"
static struct uart_data Uart6_data;

static const struct uart_config Uart6_config = {
	.value_tx_timeout = 100,
	.value_rx_timeout = 100,
	.e_mode           = POLLING,
};

static int uart6_device_init(struct device *Dev)
{
	struct uart_data *D_data = Dev->data;
	
	D_data->Uart_hal = uart6_binding();
	D_data->Uart_hal->init();
	printf("UART6 device init\r\n");
	
	return 0;
}

struct device Uart_6 = {
	.api    = &Uart_common_api,
	.data   = &Uart6_data,
	.config = &Uart6_config,
	.init   = uart6_device_init,
};

struct device* uart6_device_binding(void)
{
	return &Uart_6;
}

#ifdef UART6_IT
__weak void uart6_tx_callback_handel(struct device *Dev)
{
}
__weak void uart6_rx_callback_handel(struct device *Dev)
{
}
__weak void uart6_error_callback_handel(struct device *Dev)
{
}
#endif
#endif


#ifdef UART7_DEV
#include "uart7.h"
static struct uart_data Uart7_data;

static const struct uart_config Uart7_config = {
	.value_tx_timeout = 100,
	.value_rx_timeout = 100,
	.e_mode           = POLLING,
};

static int uart7_device_init(struct device *Dev)
{
	struct uart_data *D_data = Dev->data;
	
	D_data->Uart_hal = uart7_binding();
	D_data->Uart_hal->init();
	printf("UART7 device init\r\n");
	
	return 0;
}

struct device Uart_7 = {
	.api    = &Uart_common_api,
	.data   = &Uart7_data,
	.config = &Uart7_config,
	.init   = uart7_device_init,
};

struct device* uart7_device_binding(void)
{
	return &Uart_7;
}

#ifdef UART7_IT
__weak void uart7_tx_callback_handel(struct device *Dev)
{
}
__weak void uart7_rx_callback_handel(struct device *Dev)
{
}
__weak void uart7_error_callback_handel(struct device *Dev)
{
}
#endif
#endif


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		uart3_tx_callback_handel(&Uart_3);
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		uart6_tx_callback_handel(&Uart_6);
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		uart7_tx_callback_handel(&Uart_7);
	}
	#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		uart3_rx_callback_handel(&Uart_3);
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		uart6_rx_callback_handel(&Uart_6);
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		uart7_rx_callback_handel(&Uart_7);
	}
	#endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		uart3_error_callback_handel(&Uart_3);
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		uart6_error_callback_handel(&Uart_6);
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		uart7_error_callback_handel(&Uart_7);
	}
	#endif
}
