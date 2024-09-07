/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "timer_callback.h"


uint32_t count;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *Htim)
{
	#ifdef TIMER3_EXTI
	if(Htim->Instance == TIM3) {
		printf("Timer conut %d\r\n", count++);
	}
	#endif
}
