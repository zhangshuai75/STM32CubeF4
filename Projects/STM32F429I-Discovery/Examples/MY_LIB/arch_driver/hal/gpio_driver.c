/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#ifdef RTOS_ON
#include "cmsis_os.h"
#endif
#include "device.h"
#include "api_define.h"
#include "gpio_driver.h"
#include "api_gpio_common.h"


static int read_data(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	
	return Gpio_hal->read();
}

static void write_data(struct device *Dev, uint8_t state)
{
	struct gpio_data *D_data = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	
	Gpio_hal->write(state);
}

static void toggle_write_data(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	
	Gpio_hal->toggle_write();
}

#ifdef RTOS_ON
static uint32_t press_time_data(struct device *Dev, enum count_unit e_unit)
{
	struct gpio_data *D_data = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	int no_press_status;
	uint32_t count;
	
	no_press_status = Gpio_hal->read();
	
	switch (e_unit) {
		case MILLISECOND:
			while(1) {
				if(Gpio_hal->read() != no_press_status) {
					count = osKernelSysTick();
					do {
					}while(Gpio_hal->read() != no_press_status);
					return osKernelSysTick() - count;
				}
			}
		case SECOND:
			while(1) {
				if(Gpio_hal->read() != no_press_status) {
					count = osKernelSysTick();
					do {
					}while(Gpio_hal->read() != no_press_status);
					return (osKernelSysTick() - count) / 1000;
				}
			}
		default:
			return 0;
	}
}
#else
static uint32_t press_time_data(struct device *Dev, enum count_unit e_unit)
{
	return 0;
}
#endif

static const struct gpio_common_api Gpio_common_api = {
	.read         = read_data,
	.write        = write_data,
	.toggle_write = toggle_write_data,
	.press_time   = press_time_data,
};


#ifdef GPIO_A0_DEV
#include "gpio_a0.h"
static struct gpio_data Gpio_a0_data;

static int gpio_a0_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_a0_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_A0 device init\r\n");

	return 0;
}

struct device Gpio_a0 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_a0_data,
	.init = gpio_a0_device_init,
};

struct device* gpio_a0_device_binding(void)
{
	return &Gpio_a0;
}

#ifdef A0_EXTI
__weak void a0_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_A5_DEV
#include "gpio_a5.h"
static struct gpio_data Gpio_a5_data;

static int gpio_a5_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_a5_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_A5 device init\r\n");

	return 0;
}

struct device Gpio_a5 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_a5_data,
	.init = gpio_a5_device_init,
};

struct device* gpio_a5_device_binding(void)
{
	return &Gpio_a5;
}

#ifdef A5_EXTI
__weak void a5_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C1_DEV
#include "gpio_c1.h"
static struct gpio_data Gpio_c1_data;

static int gpio_c1_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_c1_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_C1 device init\r\n");

	return 0;
}

struct device Gpio_c1 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_c1_data,
	.init = gpio_c1_device_init,
};

struct device* gpio_c1_device_binding(void)
{
	return &Gpio_c1;
}

#ifdef C1_EXTI
__weak void c1_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_G2_DEV
#include "gpio_g2.h"
static struct gpio_data Gpio_g2_data;

static int gpio_g2_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_g2_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_G2 device init\r\n");

	return 0;
}

struct device Gpio_g2 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_g2_data,
	.init = gpio_g2_device_init,
};

struct device* gpio_g2_device_binding(void)
{
	return &Gpio_g2;
}

#ifdef G2_EXTI
__weak void g2_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_G3_DEV
#include "gpio_g3.h"
static struct gpio_data Gpio_g3_data;

static int gpio_g3_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_g3_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_G3 device init\r\n");

	return 0;
}

struct device Gpio_g3 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_g3_data,
	.init = gpio_g3_device_init,
};

struct device* gpio_g3_device_binding(void)
{
	return &Gpio_g3;
}

#ifdef G3_EXTI
__weak void g3_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_G13_DEV
#include "gpio_g13.h"
static struct gpio_data Gpio_g13_data;

static int gpio_g13_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_g13_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_G13 device init\r\n");

	return 0;
}

struct device Gpio_g13 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_g13_data,
	.init = gpio_g13_device_init,
};

struct device* gpio_g13_device_binding(void)
{
	return &Gpio_g13;
}

#ifdef G13_EXTI
__weak void g13_exti_handel(void)
{
}
#endif
#endif


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef A0_EXTI
	if(GPIO_Pin == GPIO_PIN_0) {
		a0_exti_handel();
	}
	#endif
	
	#ifdef A5_EXTI
	if(GPIO_Pin == GPIO_PIN_5) {
		a5_exti_handel();
	}
	#endif
	
	#ifdef C1_EXTI
	if(GPIO_Pin == GPIO_PIN_1) {
		c1_exti_handel();
	}
	#endif
	
	#ifdef G2_EXTI
	if(GPIO_Pin == GPIO_PIN_2) {
		g2_exti_handel();
	}
	#endif
	
	#ifdef G3_EXTI
	if(GPIO_Pin == GPIO_PIN_3) {
		g3_exti_handel();
	}
	#endif
	
	#ifdef G13_EXTI
	if(GPIO_Pin == GPIO_PIN_13) {
		g13_exti_handel();
	}
	#endif
}
