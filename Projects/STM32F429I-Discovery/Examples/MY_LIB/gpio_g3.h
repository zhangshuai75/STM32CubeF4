/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_G3_H
#define __GPIO_G3_H


#define PG3_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG3_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG3_PIN                   GPIO_PIN_3
#define PG3_PORT                  GPIOG

#ifdef G3_OUTPUT
#define G3_OUTPUT_LOW()       HAL_GPIO_WritePin(PG3_PORT, PG3_PIN, GPIO_PIN_RESET)
#define G3_OUTPUT_HIGH()      HAL_GPIO_WritePin(PG3_PORT, PG3_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_g3_binding(void);


#endif
