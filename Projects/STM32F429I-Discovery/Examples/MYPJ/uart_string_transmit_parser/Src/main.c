/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "uart_string_transmit_parser.h"
#include "main.h"
#ifdef UART3
#include "uart3.h"
#elif UART6
#include "uart6.h"
#endif


int main(void)
{
	system_initialization();
	uart_printf_init();
#ifdef UART3
	struct uart_api *Uart = (struct uart_api *)uart3_binding();
#elif UART6
	struct uart_api *Uart = (struct uart_api *)uart6_binding();
#endif
	Uart->init();
	
	pzem004t_data_t Pzem004t = {
		.value_head  = 0xB0,
		.value_data1 = 0xC0,
		.value_data2 = 0xA8,
		.value_data3 = 0x01,
		.value_data4 = 0x01,
		.value_data5 = 0x00,
		.value_sum   = (Pzem004t.value_head + Pzem004t.value_data1 +
										Pzem004t.value_data2 + Pzem004t.value_data3 +
										Pzem004t.value_data4 + Pzem004t.value_data5) & 0xFF,
	};
	pzem_data_send(Uart, &Pzem004t);
	
	/*---------------------------------------------------------*/
	uat_data_t Uat = {
		.value_command = "AT",
		.value_device  = "UART",
		.value_data1   = 115200,
		.value_data2   = 0,
		.value_data3   = 1,
	};
	uart_at_command(Uart, &Uat);
}
