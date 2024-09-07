/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include <stdio.h>
#include "cmsis_os.h"
#include "thread2.h"


static osMessageQId Os_queue;

void message_put(uint32_t msg)
{
	osMessagePut(Os_queue, msg, osWaitForever);
}

static void Thread2(const void *argument)
{
	osEvent Event;
	
	for(;;) {
		Event = osMessageGet(Os_queue, osWaitForever);
		
		if(Event.status == osEventMessage) {
			struct message *P = (struct message*)Event.value.p;
			printf("%s\r\n", P->value_name);
			printf("%d\r\n", P->value_age);
			printf("%f\r\n", P->value_height);
		}
	}
}

void thread2(void)
{
	osMessageQDef(osqueue, 2, struct message); //¦î¦Cªø«×¡B¦î¦C«¬ºA
	Os_queue = osMessageCreate(osMessageQ(osqueue), NULL);

	osThreadDef(RxThread, Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(RxThread), NULL);
}
