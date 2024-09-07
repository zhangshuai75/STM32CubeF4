/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "cmsis_os.h"
#include "uart_dma_callback_parser.h"
#include "task_test.h"


static void uart_test(const void *argument)
{
	struct uart_api *Uart7 = (struct uart_api *)argument;
	uint8_t *dma_string_checkout;
	
	Uart7->receive_dma(&uart_dma_3_callback_string_byte, 1);
	while(1) {
		do {
			dma_string_checkout = uart_dma_3_callback_string_out();
		} while(dma_string_checkout == NULL);
		printf("tt:%s", dma_string_checkout);
	}
}

void task_test(struct uart_api *Uart)
{
	osThreadDef(test_id, uart_test, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(test_id), Uart);
}
