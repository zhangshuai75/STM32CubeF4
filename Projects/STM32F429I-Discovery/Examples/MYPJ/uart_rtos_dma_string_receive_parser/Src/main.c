/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "api_define.h"
#include "main.h"

#include "uart6.h"
#include "task_dma_parser.h"

#include "uart7.h"
#include "task_test.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct uart_api *Uart6 = uart6_binding();
	Uart6->init();
	task_dma_parser(Uart6);
	
	struct uart_api *Uart7 = uart7_binding();
	Uart7->init();
	task_test(Uart7);
	
	osKernelStart();
	for(;;);
}
