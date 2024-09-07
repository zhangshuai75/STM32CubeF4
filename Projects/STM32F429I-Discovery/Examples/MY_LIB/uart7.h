/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART7_H
#define __UART7_H


#define UART7_CLK_ENABLE()              __HAL_RCC_UART7_CLK_ENABLE()
#define UART7_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define UART7_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()

#define UART7_FORCE_RESET()             __HAL_RCC_UART7_FORCE_RESET()
#define UART7_RELEASE_RESET()           __HAL_RCC_UART7_RELEASE_RESET()

#define UART7_BAUDRATE                  115200

#define UART7_TX_PIN                    GPIO_PIN_7
#define UART7_TX_GPIO_PORT              GPIOF
#define UART7_TX_AF                     GPIO_AF8_UART7

#define UART7_RX_PIN                    GPIO_PIN_6
#define UART7_RX_GPIO_PORT              GPIOF
#define UART7_RX_AF                     GPIO_AF8_UART7

#ifdef UART7_IT
void UART7_IRQHandler(void);

#ifdef UART7_DMA
#define DMA_UART7_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_UART7_TX_STREAM             DMA1_Stream1
#define DMA_UART7_RX_STREAM             DMA1_Stream3
#define DMA_UART7_TX_CHANNEL            DMA_CHANNEL_5
#define DMA_UART7_RX_CHANNEL            DMA_CHANNEL_5

#define DMA_UART7_TX_IRQn               DMA1_Stream1_IRQn
#define DMA_UART7_RX_IRQn               DMA1_Stream3_IRQn
#define DMA_UART7_TX_IRQHandler         DMA1_Stream1_IRQHandler
#define DMA_UART7_RX_IRQHandler         DMA1_Stream3_IRQHandler

void DMA_UART7_TX_IRQHandler(void);
void DMA_UART7_RX_IRQHandler(void);
#endif
#endif

struct uart_api* uart7_binding(void);


#endif
