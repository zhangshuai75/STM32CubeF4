/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_TEMPLATE_COMMON_H
#define __API_TEMPLATE_COMMON_H


               /*-----------API--------------*/
typedef int (*template_api_1)(struct device *Dev);
typedef int (*template_api_2)(struct device *Dev);

struct template_common_api {
	template_api_1 send;
	template_api_2 get;
};


               /*-----------APP--------------*/
static inline int template_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int template_app1(struct device *Dev)
{
	const struct template_common_api *D_api = Dev->api;
	return D_api->send(Dev);
}

static inline int template_app2(struct device *Dev)
{
	const struct template_common_api *D_api = Dev->api;
	return D_api->get(Dev);
}


#endif
