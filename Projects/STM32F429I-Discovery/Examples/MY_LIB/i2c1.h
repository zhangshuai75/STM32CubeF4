/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __I2C1_H
#define __I2C1_H


#define I2C1_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2C1_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_SDA_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOB_CLK_DISABLE()

#define I2C1_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2C1_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

#define I2C1_CLOCKSPEED                 400000

#define I2C1_SCL_PIN                    GPIO_PIN_6
#define I2C1_SCL_GPIO_PORT              GPIOB
#define I2C1_SCL_AF                     GPIO_AF4_I2C1

#define I2C1_SDA_PIN                    GPIO_PIN_9
#define I2C1_SDA_GPIO_PORT              GPIOB
#define I2C1_SDA_AF                     GPIO_AF4_I2C1

#define I2C1_REG_BIT                    I2C_MEMADD_SIZE_8BIT

#ifdef I2C1_IT
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);

#ifdef I2C1_DMA
#define DMA_I2C1_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_I2C1_TX_STREAM             DMA1_Stream6
#define DMA_I2C1_RX_STREAM             DMA1_Stream5
#define DMA_I2C1_TX_CHANNEL            DMA_CHANNEL_1
#define DMA_I2C1_RX_CHANNEL            DMA_CHANNEL_1

#define DMA_I2C1_TX_IRQn               DMA1_Stream6_IRQn
#define DMA_I2C1_RX_IRQn               DMA1_Stream5_IRQn
#define DMA_I2C1_TX_IRQHandler         DMA1_Stream6_IRQHandler
#define DMA_I2C1_RX_IRQHandler         DMA1_Stream5_IRQHandler

void DMA_I2C1_TX_IRQHandler(void);
void DMA_I2C1_RX_IRQHandler(void);
#endif
#endif

struct i2c_api* i2c1_binding(void);


#endif
