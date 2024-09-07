/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_RF_COMMON_H
#define __API_RF_COMMON_H


               /*-----------API--------------*/
typedef int (*rf_api_1)(struct device *Dev);
typedef int (*rf_api_2)(struct device *Dev);

struct rf_common_api {
	rf_api_1 device_test;
	rf_api_2 get;
};


               /*-----------APP--------------*/
static inline int rf_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int rf_device_test(struct device *Dev)
{
	const struct rf_common_api *D_api = Dev->api;
	return D_api->device_test(Dev);
}

static inline int rf_get(struct device *Dev)
{
	const struct rf_common_api *D_api = Dev->api;
	return D_api->get(Dev);
}


#endif
