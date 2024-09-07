/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "cmsis_os.h"
#include "main.h"
#include "thread1.h"
#include "thread2.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	thread1();
	thread2();
	
	osKernelStart();
	for(;;);
}
