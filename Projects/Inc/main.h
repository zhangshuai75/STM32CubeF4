/**
  ******************************************************************************
  * @file    FatFs/FatFs_uSD/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.4.5
  * @date    03-June-2016
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

//#define DEBUG_MODE

/*****************************************************************************/
/*****************************************************************************/
/** 
  * @brief  UART status structure definition  
  */     
#define   UART_OK         0x00
#define   UART_ERROR      0x01

#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART2
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART2

/* Definition for USARTx's DMA */
#define USARTx_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define USARTx_TX_DMA_STREAM             DMA1_Stream6
#define USARTx_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define USARTx_RX_DMA_STREAM             DMA1_Stream5

/* Definition for USARTx's NVIC */
#define USARTx_DMA_TX_IRQn               DMA1_Stream6_IRQn
#define USARTx_DMA_RX_IRQn               DMA1_Stream5_IRQn
#define USARTx_DMA_TX_IRQHandler         DMA1_Stream6_IRQHandler
#define USARTx_DMA_RX_IRQHandler         DMA1_Stream5_IRQHandler
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

/* Size of Transmission buffer */
#define TXBUFFERSIZE                     (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                     TXBUFFERSIZE

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/*****************************************************************************/
/*****************************************************************************/
/** 
  * @brief  UART status structure definition  
  */ 
#define I2Cx                             I2C1
#define I2Cx_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2Cx_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SCL_AF                     GPIO_AF4_I2C1
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SDA_AF                     GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

#define TOUCH_INT_PIN                		GPIO_PIN_7

/*****************************************************************************/
/*****************************************************************************/
/** 
  * @brief  NRF24L01 structure definition  
  */ 
#define RF24L01_CE_GPIO_PIN                      	GPIO_PIN_0                 /* PB.00 */
#define RF24L01_IRQ_GPIO_PIN                     	GPIO_PIN_1                 /* PB.01 */
#define RF24L01_CS_GPIO_PIN                     	GPIO_PIN_15                /* PA.15 */

#define RF24L01_CE_GPIO_CLK_ENABLE()            	__GPIOB_CLK_ENABLE()
#define RF24L01_CE_GPIO_CLK_DISABLE()           	__GPIOB_CLK_DISABLE()
#define RF24L01_CE_GPIO_PORT                  		GPIOB                      /* GPIOB */

#define RF24L01_IRQ_GPIO_CLK_ENABLE()            	__GPIOB_CLK_ENABLE()
#define RF24L01_IRQ_GPIO_CLK_DISABLE()           	__GPIOB_CLK_DISABLE()
#define RF24L01_IRQ_GPIO_PORT                  		GPIOB                      /* GPIOB */

#define RF24L01_CS_GPIO_CLK_ENABLE()            	__GPIOA_CLK_ENABLE()
#define RF24L01_CS_GPIO_CLK_DISABLE()           	__GPIOA_CLK_DISABLE()
#define RF24L01_CS_GPIO_PORT                  		GPIOA                      /* GPIOA */

/*****************************************************************************/
/*****************************************************************************/
/** 
  * @brief  LCD SRAM structure definition  
  */
#define SRAM_BANK_ADDR                 ((uint32_t)0x64000000)

/* #define SRAM_MEMORY_WIDTH            FSMC_NORSRAM_MEM_BUS_WIDTH_8  */
#define SRAM_MEMORY_WIDTH               FSMC_NORSRAM_MEM_BUS_WIDTH_16
/* #define SRAM_MEMORY_WIDTH            FSMC_NORSRAM_MEM_BUS_WIDTH_32 */

#define SRAM_TIMEOUT     ((uint32_t)0xFFFF) 


/*****************************************************************************/
/*****************************************************************************/
/** 
  * @brief  LCD backlight PWM structure definition  
  */
//#define TIMx                           TIM3
#define TIM2_CLK_ENABLE                __HAL_RCC_TIM2_CLK_ENABLE

/* Definition for LCD backlight PWM output Pins */
#define TIM2_CHANNEL_GPIO_PORT()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define GPIO_PIN_CHANNEL2              GPIO_PIN_1

/* Private typedef -----------------------------------------------------------*/
#define  PERIOD_VALUE       (8000 - 1)  	/* Period Value  */
#define  PULSE1_VALUE       7500        	/* Capture Compare 1 Value  */
#define  PULSE2_VALUE       5000         	/* Capture Compare 2 Value  */
#define  PULSE3_VALUE       2000         	/* Capture Compare 3 Value  */


/*****************************************************************************/
/*****************************************************************************/
/** 
  * @brief  ADC structure definition  
//steering					--PC0 ADC123_IN10
//throttle lever		--PC1 ADC123_IN11
//bat								--PC2 ADC123_IN12
//steering button		--PC3
	*/
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
#define DMA2_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()     
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
     
#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_STR_CHANNEL_PIN                GPIO_PIN_0
#define ADCx_STR_CHANNEL_GPIO_PORT          GPIOC

#define ADCx_THRT_CHANNEL_PIN               GPIO_PIN_1
#define ADCx_THRT_CHANNEL_GPIO_PORT         GPIOC

#define ADCx_BAT_CHANNEL_PIN               GPIO_PIN_2
#define ADCx_BAT_CHANNEL_GPIO_PORT         GPIOC

/* Definition for ADCx's Channel */
#define ADCx_STR_CHANNEL                    ADC_CHANNEL_10		//ת��
#define ADCx_THRT_CHANNEL                   ADC_CHANNEL_11		//����
#define ADCx_BAT_CHANNEL                   	ADC_CHANNEL_12		//��ص�ѹ
#define ADCx_TMP_CHANNEL                   	ADC_CHANNEL_16		//�¶�
//#define ADCx_VDD_CHANNEL                 		ADC_CHANNEL_18		//VDD��ѹ

/* Definition for ADCx's DMA */
#define ADCx_DMA_CHANNEL                		DMA_CHANNEL_0
#define ADCx_DMA_STREAM                 		DMA2_Stream0         

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   		DMA2_Stream0_IRQn
#define ADCx_DMA_IRQHandler             		DMA2_Stream0_IRQHandler

typedef struct  
{
	uint16_t ADC_STR;
	uint16_t ADC_THRT;
	uint16_t ADC_BAT;
	uint16_t ADC_TMP;	
}ADC_DATA_TypeDef;

typedef struct  
{
	uint8_t RX_BAT_L;
	uint8_t RX_BAT_H;
}RC_ACK_Data_TypeDef;

#if 0
typedef struct  
{
	uint8_t CHANNEL1_Left;
	uint8_t CHANNEL1_Right;
	uint8_t CHANNEL2_Forward;
	uint8_t CHANNEL2_Backward;
	uint8_t CHANNEL3_Gear1;
	uint8_t CHANNEL3_Gear2;
	uint8_t CHANNEL4_On;
	uint8_t CHANNEL4_Off;	
}RC_TX_Data_TypeDef;
#endif

typedef struct  
{
	uint8_t CHANNEL1;	
	uint8_t CHANNEL2;	
	uint8_t CHANNEL3;	
	uint8_t CHANNEL4;	
}RC_TX_Data_TypeDef;

typedef struct  
{
	ADC_DATA_TypeDef			ADC_DATA;
	uint16_t 							ADC_StrMid;
	uint16_t 							ADC_ThrtMid;
	RC_TX_Data_TypeDef 		RC_TX_Data;
	RC_ACK_Data_TypeDef		RC_ACK_Data;
	uint16_t							RX_BAT;
	uint16_t							TX_BAT;
	uint16_t							TX_TMP;
	
}RC_DATA_TypeDef;


void 				RC_TX_DataHandle(RC_DATA_TypeDef* rc_data);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
