/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_DMA_CALLBACK_PARSER_H
#define __UART_DMA_CALLBACK_PARSER_H


#define SEL_UART3_DMA_CALLBACK_PARSER(x)        uart_dma_2_callback_parser(x)
#define SEL_UART6_DMA_CALLBACK_PARSER(x)        uart_dma_1_callback_parser(x)
#define SEL_UART7_DMA_CALLBACK_PARSER(x)        uart_dma_3_callback_parser(x)

void uart_dma_1_callback_parser(UART_HandleTypeDef *UartHandle); //for HAL_UART_RxCpltCallback()
void uart_dma_2_callback_parser(UART_HandleTypeDef *UartHandle); //for HAL_UART_RxCpltCallback()
void uart_dma_3_callback_parser(UART_HandleTypeDef *UartHandle); //for HAL_UART_RxCpltCallback()

extern uint8_t uart_dma_1_callback_string_byte; //for uart->receive_dma() use between this.c and main.c
#define dma_1_string_out_buffer_length 1        //one byte
uint8_t* uart_dma_1_callback_string_out(void);

extern uint8_t uart_dma_2_callback_string_byte; //for uart->receive_dma() use between this.c and main.c
#define dma_2_string_out_buffer_length 100      //0x0D 0x0A end
uint8_t* uart_dma_2_callback_string_out(void);

extern uint8_t uart_dma_3_callback_string_byte; //for uart->receive_dma() use between this.c and main.c
#define dma_3_string_out_buffer_length 100      //0x0D 0x0A end
uint8_t* uart_dma_3_callback_string_out(void);


#endif
