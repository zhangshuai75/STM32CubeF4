/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __TEMPLATE_DRIVER_H
#define __TEMPLATE_DRIVER_H


struct template_data {
	struct device *Binding_device_1;
	struct device *Binding_device_2;
	int value_data1;
	int value_data2;
};

struct template_config {
	uint32_t value_this_config_1;
	uint32_t value_this_config_2;
};

struct device* template_device_binding(void);


#endif
