/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __I2C3_H
#define __I2C3_H


#define I2C3_CLK_ENABLE()               __HAL_RCC_I2C3_CLK_ENABLE()
#define I2C3_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define I2C3_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define I2C3_SDA_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOC_CLK_DISABLE()

#define I2C3_FORCE_RESET()              __HAL_RCC_I2C3_FORCE_RESET()
#define I2C3_RELEASE_RESET()            __HAL_RCC_I2C3_RELEASE_RESET()

#define I2C3_CLOCKSPEED                 400000

#define I2C3_SCL_PIN                    GPIO_PIN_8
#define I2C3_SCL_GPIO_PORT              GPIOA
#define I2C3_SCL_AF                     GPIO_AF4_I2C3

#define I2C3_SDA_PIN                    GPIO_PIN_9
#define I2C3_SDA_GPIO_PORT              GPIOC
#define I2C3_SDA_AF                     GPIO_AF4_I2C3

#define I2C3_REG_BIT                    I2C_MEMADD_SIZE_8BIT

#ifdef I2C3_IT
void I2C3_EV_IRQHandler(void);
void I2C3_ER_IRQHandler(void);

#ifdef I2C3_DMA
#define DMA_I2C3_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_I2C3_TX_STREAM             DMA1_Stream4
#define DMA_I2C3_RX_STREAM             DMA1_Stream2
#define DMA_I2C3_TX_CHANNEL            DMA_CHANNEL_3
#define DMA_I2C3_RX_CHANNEL            DMA_CHANNEL_3

#define DMA_I2C3_TX_IRQn               DMA1_Stream4_IRQn
#define DMA_I2C3_RX_IRQn               DMA1_Stream2_IRQn
#define DMA_I2C3_TX_IRQHandler         DMA1_Stream4_IRQHandler
#define DMA_I2C3_RX_IRQHandler         DMA1_Stream2_IRQHandler

void DMA_I2C3_TX_IRQHandler(void);
void DMA_I2C3_RX_IRQHandler(void);
#endif
#endif

struct i2c_api* i2c3_binding(void);


#endif
