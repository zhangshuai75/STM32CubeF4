/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include <string.h>
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "uart_string_transmit_parser.h"


int pzem_data_send(struct uart_api *Huart, pzem004t_data_t *Data)
{
	Huart->transmit((uint8_t *)Data, 7, 1000);
	return 0;
}

int uart_at_command(struct uart_api *Huart, uat_data_t *Data)
{
	char buffer[] = "\0";
	
	sprintf(buffer, "%s+%s=%d,%d,%d", Data->value_command,
																		Data->value_device,
																		Data->value_data1,
																		Data->value_data2,
																		Data->value_data3);
	Huart->transmit((uint8_t *)buffer, strlen(buffer), 1000);
	return 0;
}
