/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_STRING_TRANSMIT_PARSER_H
#define __UART_STRING_TRANSMIT_PARSER_H


typedef struct {
	uint8_t value_head;
	uint8_t value_data1;
	uint8_t value_data2;
	uint8_t value_data3;
	uint8_t value_data4;
	uint8_t value_data5;
	uint8_t value_sum;
}pzem004t_data_t;

typedef struct {
	char *value_command;
	char *value_device;
	int value_data1;
	int value_data2;
	int value_data3;
}uat_data_t;

int pzem_data_send(struct uart_api *Huart, pzem004t_data_t *Data);
int uart_at_command(struct uart_api *Huart, uat_data_t *Data);


#endif
