/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __TIMER3_H
#define __TIMER3_H


#define TIM3_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()

struct timer_api* timer3_binding(void);


#endif
