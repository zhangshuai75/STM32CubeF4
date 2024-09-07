/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include <stdio.h>
#include "cmsis_os.h"
#include "thread1.h"
#include "thread2.h"


static struct message Meter = {
	.value_name   = "rock man",
	.value_age    = 88,
	.value_height = 251.36
};

static void Thread1(const void *argument)
{
	message_put((uint32_t)&Meter);
}

void thread1(void)
{
	osThreadDef(TxThread, Thread1, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(TxThread), NULL);
}
