/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI4_H
#define __SPI4_H


#define SPI4_CLK_ENABLE()               __HAL_RCC_SPI4_CLK_ENABLE()
#define SPI4_SCK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()
#define SPI4_MISO_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()
#define SPI4_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()
#define SPI4_MISO_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOE_CLK_DISABLE()
#define SPI4_MOSI_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOE_CLK_DISABLE()

#define SPI4_FORCE_RESET()              __HAL_RCC_SPI4_FORCE_RESET()
#define SPI4_RELEASE_RESET()            __HAL_RCC_SPI4_RELEASE_RESET()

#define SPI4_CLKPOLARITY                SPI_POLARITY_LOW
#define SPI4_CLKPHASE                   SPI_PHASE_1EDGE
#define SPI4_BAUDRATEPRESCALER          SPI_BAUDRATEPRESCALER_32

#define SPI4_SCK_PIN                    GPIO_PIN_12
#define SPI4_SCK_GPIO_PORT              GPIOE
#define SPI4_SCK_AF                     GPIO_AF5_SPI4

#define SPI4_MISO_PIN                   GPIO_PIN_13
#define SPI4_MISO_GPIO_PORT             GPIOE
#define SPI4_MISO_AF                    GPIO_AF5_SPI4

#define SPI4_MOSI_PIN                   GPIO_PIN_14
#define SPI4_MOSI_GPIO_PORT             GPIOE
#define SPI4_MOSI_AF                    GPIO_AF5_SPI4

#ifdef SPI4_IT
void SPI4_IRQHandler(void);

#ifdef SPI4_DMA
#define DMA_SPI4_CLK_ENABLE()          __HAL_RCC_DMA2_CLK_ENABLE()

#define DMA_SPI4_TX_STREAM             DMA2_Stream1
#define DMA_SPI4_RX_STREAM             DMA2_Stream0
#define DMA_SPI4_TX_CHANNEL            DMA_CHANNEL_4
#define DMA_SPI4_RX_CHANNEL            DMA_CHANNEL_4

#define DMA_SPI4_TX_IRQn               DMA2_Stream1_IRQn
#define DMA_SPI4_RX_IRQn               DMA2_Stream0_IRQn
#define DMA_SPI4_TX_IRQHandler         DMA2_Stream1_IRQHandler
#define DMA_SPI4_RX_IRQHandler         DMA2_Stream0_IRQHandler

void DMA_SPI4_TX_IRQHandler(void);
void DMA_SPI4_RX_IRQHandler(void);
#endif
#endif

void spi4_init(void);
void _SPI4_MspDeInit(void);


#endif
