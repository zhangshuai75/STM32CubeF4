/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H


enum uart_mode{
	POLLING,
	IT,
	DMA,
};

struct uart_data {
	struct uart_api *Uart_hal;
};

struct uart_config {
	uint8_t value_tx_timeout;
	uint8_t value_rx_timeout;
	enum uart_mode e_mode;
};

#ifdef UART3_DEV
struct device* uart3_device_binding(void);
#endif

#ifdef UART6_DEV
struct device* uart6_device_binding(void);
#endif

#ifdef UART7_DEV
struct device* uart7_device_binding(void);
#endif


#endif
