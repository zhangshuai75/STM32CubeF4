/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "gpio_callback.h"


#ifdef A0_EXTI
#include "gpio_g13.h"
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef A0_EXTI
	if(GPIO_Pin == GPIO_PIN_0) {
		struct gpio_api *Gpio_g13 = gpio_g13_binding();
		Gpio_g13->toggle_write();
	}
	#endif
}
