/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H


struct pwm_data {
	struct pwm_api *Pwm_hal;
};

#ifdef PWM3_1_DEV
struct device* pwm3_1_device_binding(void);
#endif


#endif
