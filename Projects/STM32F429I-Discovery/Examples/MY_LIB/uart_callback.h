/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_CALLBACK_H
#define __UART_CALLBACK_H


#ifdef UART3_IT
extern __IO FlagStatus e_uart3_rx_callbake_flag;
#endif

#ifdef UART6_IT
extern __IO FlagStatus e_uart6_rx_callbake_flag;
#endif

#ifdef UART7_IT
extern __IO FlagStatus e_uart7_rx_callbake_flag;
#endif


#endif
