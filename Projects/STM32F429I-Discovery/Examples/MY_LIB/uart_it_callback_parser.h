/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_IT_CALLBACK_PARSER_H
#define __UART_IT_CALLBACK_PARSER_H


#define SEL_UART3_IT_CALLBACK_PARSER(x)         uart_it_1_callback_parser(x)
#define SEL_UART6_IT_CALLBACK_PARSER(x)         uart_it_2_callback_parser(x)
#define SEL_UART7_IT_CALLBACK_PARSER(x)         uart_it_3_callback_parser(x)

void uart_it_1_callback_parser(UART_HandleTypeDef *UartHandle); //for HAL_UART_RxCpltCallback()
void uart_it_2_callback_parser(UART_HandleTypeDef *UartHandle); //for HAL_UART_RxCpltCallback()
void uart_it_3_callback_parser(UART_HandleTypeDef *UartHandle); //for HAL_UART_RxCpltCallback()

extern uint8_t uart_it_1_callback_string_byte; //for uart->receive_it() use between this.c and main.c
#define it_1_string_out_buffer_length 1        //one byte
uint8_t* uart_it_1_callback_string_out(void);

extern uint8_t uart_it_2_callback_string_byte; //for uart->receive_it() use between this.c and main.c
#define it_2_string_out_buffer_length 100      //0x0D 0x0A end
uint8_t* uart_it_2_callback_string_out(void);

extern uint8_t uart_it_3_callback_string_byte; //for uart->receive_it() use between this.c and main.c
#define it_3_string_out_buffer_length 100      //0x0D 0x0A end
uint8_t* uart_it_3_callback_string_out(void);


#endif
