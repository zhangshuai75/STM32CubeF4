/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_BT_COMMON_H
#define __API_BT_COMMON_H


               /*-----------API--------------*/
typedef int (*bt_api_1)(struct device *Dev);
typedef int (*bt_api_2)(struct device *Dev);

struct bt_common_api {
	bt_api_1 send;
	bt_api_2 get;
};


               /*-----------APP--------------*/
static inline int bt_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int bt_send(struct device *Dev)
{
	const struct bt_common_api *D_api = Dev->api;
	return D_api->send(Dev);
}

static inline int bt_get(struct device *Dev)
{
	const struct bt_common_api *D_api = Dev->api;
	return D_api->get(Dev);
}


#endif
