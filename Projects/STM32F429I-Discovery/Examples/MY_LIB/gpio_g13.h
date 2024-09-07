/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_G13_H
#define __GPIO_G13_H


#define PG13_CLK_ENABLE()         __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG13_CLK_DISABLE()        __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG13_PIN                  GPIO_PIN_13
#define PG13_PORT                 GPIOG

#ifdef G13_OUTPUT
#define G13_OUTPUT_LOW()      HAL_GPIO_WritePin(PG13_PORT, PG13_PIN, GPIO_PIN_RESET)
#define G13_OUTPUT_HIGH()     HAL_GPIO_WritePin(PG13_PORT, PG13_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_g13_binding(void);


#endif
