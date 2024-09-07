/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "gpio_c1.h"
#include "api_define.h"


#ifdef C1_OUTPUT
static void gpio_c1_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PC1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PC1_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C1_INPUT
static void gpio_c1_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PC1_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C1_EXTI
static void gpio_c1_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PC1_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PC1_PIN);
}
#endif

static void gpio_c1_init(void)
{
	#ifdef C1_OUTPUT
	gpio_c1_output_init();
	#endif
	#ifdef C1_INPUT
	gpio_c1_input_init();
	#endif
	#ifdef C1_EXTI
	gpio_c1_exti_init();
	#endif
	printf("GPIO_C1 HAL init\r\n");
}

static int gpio_c1_read(void)
{
	return HAL_GPIO_ReadPin(PC1_PORT, PC1_PIN);
}

static void gpio_c1_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PC1_PORT, PC1_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PC1_PORT, PC1_PIN, GPIO_PIN_SET);
	}
}

static void gpio_c1_toggle_write(void)
{
	HAL_GPIO_TogglePin(PC1_PORT, PC1_PIN);
}

static int gpio_c1_lock(void)
{
	return HAL_GPIO_LockPin(PC1_PORT, PC1_PIN);
}

static struct gpio_api Gpio_c1_api = {
	.init         = gpio_c1_init,
	.read         = gpio_c1_read,
	.write        = gpio_c1_write,
	.toggle_write = gpio_c1_toggle_write,
	.lock         = gpio_c1_lock,
};

struct gpio_api* gpio_c1_binding(void)
{
	return &Gpio_c1_api;
}
