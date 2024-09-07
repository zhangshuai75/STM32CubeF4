/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_WIFI_COMMON_H
#define __API_WIFI_COMMON_H


               /*-----------API--------------*/
typedef int (*wifi_api_1)(struct device *Dev);
typedef int (*wifi_api_2)(struct device *Dev);

struct wifi_common_api {
	wifi_api_1 send;
	wifi_api_2 get;
};


               /*-----------APP--------------*/
static inline int wifi_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int wifi_send(struct device *Dev)
{
	const struct wifi_common_api *D_api = Dev->api;
	return D_api->send(Dev);
}

static inline int wifi_get(struct device *Dev)
{
	const struct wifi_common_api *D_api = Dev->api;
	return D_api->get(Dev);
}


#endif
