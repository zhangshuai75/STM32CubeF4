/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H


struct gpio_data {
	struct gpio_api *Gpio_hal;
};

#ifdef GPIO_A0_DEV
struct device* gpio_a0_device_binding(void);
#endif

#ifdef GPIO_A5_DEV
struct device* gpio_a5_device_binding(void);
#endif

#ifdef GPIO_C1_DEV
struct device* gpio_c1_device_binding(void);
#endif

#ifdef GPIO_G2_DEV
struct device* gpio_g2_device_binding(void);
#endif

#ifdef GPIO_G3_DEV
struct device* gpio_g3_device_binding(void);
#endif

#ifdef GPIO_G13_DEV
struct device* gpio_g13_device_binding(void);
#endif


#endif
