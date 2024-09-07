/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include <stdlib.h>
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "uart_string_receive_parser.h"
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

	uint8_t buffer[50];
	
	head_checkout(Uart, "GPABCD", buffer, 50);
	gps_data_t *Gps = a_parser(buffer);
	printf("START = %s\r\n", Gps->value_start);

/*---------------------------------------------------------*/
	char name[] = {0x0A,0x41};
	head_checkout(Uart, name, buffer, 50);
	version_data_t *Version = version_parser(buffer);
	
	char region[5];
	int re;
	sprintf(region, "%.5s\r\n", Version->value_region);
	re = strtol(region, NULL, 16);
	printf("region %d\r\n", re);
}
