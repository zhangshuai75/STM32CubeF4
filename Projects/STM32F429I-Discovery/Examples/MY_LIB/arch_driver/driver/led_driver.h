/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H


struct led_data {
	struct device *Gpio;
};

struct device* led_device_binding(void);


#endif
