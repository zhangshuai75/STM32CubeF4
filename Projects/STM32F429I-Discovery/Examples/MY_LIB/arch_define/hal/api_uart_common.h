/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_UART_COMMON_H
#define __API_UART_COMMON_H


               /*-----------API--------------*/
typedef int (*uart_api_1)(struct device *Dev, uint8_t *data, uint16_t length);
typedef int (*uart_api_2)(struct device *Dev, uint8_t *data, uint16_t length);

struct uart_common_api {
	uart_api_1 transmit;
	uart_api_2 receive;
};


               /*-----------APP--------------*/
static inline int uart_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int uart_transmit(struct device *Dev, uint8_t *data, uint16_t length)
{
	const struct uart_common_api *D_api = Dev->api;
	return D_api->transmit(Dev, data, length);
}

static inline int uart_receive(struct device *Dev, uint8_t *data, uint16_t length)
{
	const struct uart_common_api *D_api = Dev->api;
	return D_api->receive(Dev, data, length);
}


#endif
