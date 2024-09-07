/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "cmsis_os.h"
#include "uart_dma_callback_parser.h"
#include "task_dma_parser.h"


static void dma_uart_string_parser(const void *argument)
{
	struct uart_api *Uart6 = (struct uart_api *)argument;
	uint8_t *dma_string_checkout;
	
	Uart6->receive_dma(&uart_dma_1_callback_string_byte, 1);
	while(1) {
		do {
			dma_string_checkout = uart_dma_1_callback_string_out();
		} while(dma_string_checkout == NULL);
		printf("tdp:%s", dma_string_checkout);
	}
}

void task_dma_parser(struct uart_api *Uart)
{
	osThreadDef(dma_parser_id, dma_uart_string_parser, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(dma_parser_id), Uart);
}
