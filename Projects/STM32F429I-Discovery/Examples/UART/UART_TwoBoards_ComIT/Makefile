# Cortex-M4 implements the ARMv7E-M architecture
CFLAGS  = -mcpu=cortex-m4
CFLAGS += -march=armv7e-m
CFLAGS += -mtune=cortex-m4
CFLAGS += -mlittle-endian
CFLAGS += -mthumb
# Need study
CFLAGS += -mfpu=fpv4-sp-d16
CFLAGS += -mfloat-abi=softfp

define get_library_path
    $(shell dirname $(shell arm-none-eabi-gcc $(CFLAGS) -print-file-name=$(1)))
endef
LDFLAGS  = -L $(call get_library_path,libc.a)
LDFLAGS += -L $(call get_library_path,libgcc.a)

# Basic configurations
CFLAGS += -g
CFLAGS += -std=c99
CFLAGS += -Wall

# Optimizations
CFLAGS += -O3
CFLAGS += -ffast-math
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Wl,--gc-sections
CFLAGS += -fno-common
CFLAGS += --param max-inline-insns-single=1000

# Symbols Define
CFLAGS += -DSTM32F429xx
CFLAGS += -DUSE_HAL_DRIVER
CFLAGS += -DUSE_STM32F429I_DISCO

### LD
LDFLAGS += -T $(PWD)/STM32F429ZITx_FLASH.ld

### Startup File(.s)
OBJS  = $(PWD)/startup_stm32f429xx.o

### main
OBJS += $(PWD)/Src/main.o \
        $(PWD)/Src/stm32f4xx_it.o \
        $(PWD)/Src/stm32f4xx_hal_msp.o \
        $(PWD)/Src/system_stm32f4xx.o

CFLAGS += -I $(PWD)/Inc

### Driver HAL I/O
OBJS += $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.o \
        $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o

CFLAGS += -I $(PWD)/../../../../../Drivers/CMSIS/Include \
	      -I $(PWD)/../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include \
          -I $(PWD)/../../../../../Drivers/STM32F4xx_HAL_Driver/Inc

### BSP
OBJS += $(PWD)/../../../../../Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery.o

CFLAGS += -I $(PWD)/../../../../../Drivers/BSP/STM32F429I-Discovery

#######################################################################################
all: UART_TwoBoards_ComIT.bin

UART_TwoBoards_ComIT.bin: UART_TwoBoards_ComIT.elf
	arm-none-eabi-objcopy -O ihex $^ UART_TwoBoards_ComIT.hex
	arm-none-eabi-objcopy -O binary $^ $@
	arm-none-eabi-objdump -h -S -D UART_TwoBoards_ComIT.elf > UART_TwoBoards_ComIT.lst
	arm-none-eabi-size UART_TwoBoards_ComIT.elf

#再連結library一次轉為.elf
UART_TwoBoards_ComIT.elf: $(OBJS)
	arm-none-eabi-ld $(OBJS) $(LDFLAGS) -o $@ --start-group $(LIBS) --end-group

#先把.c.s轉為.o
%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf UART_TwoBoards_ComIT.elf
	rm -rf UART_TwoBoards_ComIT.bin
	rm -rf UART_TwoBoards_ComIT.hex
	rm -f $(OBJS)
	rm -f UART_TwoBoards_ComIT.lst
