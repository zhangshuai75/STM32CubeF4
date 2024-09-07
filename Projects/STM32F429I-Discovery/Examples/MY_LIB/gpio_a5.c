/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "gpio_a5.h"
#include "api_define.h"


#ifdef A5_OUTPUT
static void gpio_a5_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PA5_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA5_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PA5_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A5_INPUT
static void gpio_a5_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA5_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA5_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PA5_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A5_EXTI
static void gpio_a5_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA5_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA5_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PA5_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA5_PIN);
}
#endif

static void gpio_a5_init(void)
{
	#ifdef A5_OUTPUT
	gpio_a5_output_init();
	#endif
	#ifdef A5_INPUT
	gpio_a5_input_init();
	#endif
	#ifdef A5_EXTI
	gpio_a5_exti_init();
	#endif
	printf("GPIO_A5 HAL init\r\n");
}

static int gpio_a5_read(void)
{
	return HAL_GPIO_ReadPin(PA5_PORT, PA5_PIN);
}

static void gpio_a5_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PA5_PORT, PA5_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PA5_PORT, PA5_PIN, GPIO_PIN_SET);
	}
}

static void gpio_a5_toggle_write(void)
{
	HAL_GPIO_TogglePin(PA5_PORT, PA5_PIN);
}

static int gpio_a5_lock(void)
{
	return HAL_GPIO_LockPin(PA5_PORT, PA5_PIN);
}

static struct gpio_api Gpio_a5_api = {
	.init         = gpio_a5_init,
	.read         = gpio_a5_read,
	.write        = gpio_a5_write,
	.toggle_write = gpio_a5_toggle_write,
	.lock         = gpio_a5_lock,
};

struct gpio_api* gpio_a5_binding(void)
{
	return &Gpio_a5_api;
}
