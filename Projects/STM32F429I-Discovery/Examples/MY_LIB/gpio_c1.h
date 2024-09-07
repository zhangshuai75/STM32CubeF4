/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_C1_H
#define __GPIO_C1_H


#define PC1_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define PC1_CLK_DISABLE()         __HAL_RCC_GPIOC_CLK_DISABLE()

#define PC1_PIN                   GPIO_PIN_1
#define PC1_PORT                  GPIOC

#ifdef C1_OUTPUT
#define C1_OUTPUT_LOW()       HAL_GPIO_WritePin(PC1_PORT, PC1_PIN, GPIO_PIN_RESET)
#define C1_OUTPUT_HIGH()      HAL_GPIO_WritePin(PC1_PORT, PC1_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_c1_binding(void);


#endif
