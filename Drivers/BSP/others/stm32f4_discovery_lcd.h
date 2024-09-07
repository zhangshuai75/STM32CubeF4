#ifndef __ILI9325_H
#define __ILI9325_H
#include "stm32f4xx_hal.h"
//��������IC��ILI9320����ILI9325
#define  ILI9325 

#define   BLACK                0x0000                // ��ɫ��    0,   0,   0 //
#define   BLUE                 0x001F                // ��ɫ��    0,   0, 255 //
#define   GREEN                0x07E0                // ��ɫ��    0, 255,   0 //
#define   CYAN                 0x07FF                // ��ɫ��    0, 255, 255 //
#define   RED                  0xF800                // ��ɫ��  255,   0,   0 //
#define   MAGENTA              0xF81F                // Ʒ�죺  255,   0, 255 //
#define   YELLOW               0xFFE0                // ��ɫ��  255, 255, 0   //
#define   WHITE                0xFFFF                // ��ɫ��  255, 255, 255 //
#define   NAVY                 0x000F                // ����ɫ��  0,   0, 128 //
#define   DGREEN               0x03E0                // ����ɫ��  0, 128,   0 //
#define   DCYAN                0x03EF                // ����ɫ��  0, 128, 128 //
#define   MAROON               0x7800                // ���ɫ��128,   0,   0 //
#define   PURPLE               0x780F                // ��ɫ��  128,   0, 128 //
#define   OLIVE                0x7BE0                // ����̣�128, 128,   0 //
#define   LGRAY                0xC618                // �Ұ�ɫ��192, 192, 192 //
#define   DGRAY                0x7BEF                // ���ɫ��128, 128, 128 //

//��Ļ��ת���� ���ְ��� ID[1:0]AM ����PDF�е����ö���
#define ID_AM  110
//��Ļ��ʼʱ��ʾ��ʽ��ע�⣺��IDelayʱ��ʾ��һ��������������ˢ�µ�
//��ʱ�����ֶ���ˢ�½��������  LCD_WR_REG(0x0007,0x0173);������ʾ



//Ӳ����ص��Ӻ���
#define Bank1_LCD_D    ((uint32_t)0x60200000)    //Disp Data ADDR, A20 set to 1
#define Bank1_LCD_C    ((uint32_t)0x60000000)	   //Disp Reg ADDR

void 			BSP_LCD_Init(void);
void 			BSP_LCD_DrawPixel(uint16_t x, uint16_t y, int Color);
uint16_t 	BSP_LCD_GetPoint(uint16_t x,uint16_t y);
void 			BSP_LCD_FillRec(uint16_t xStart,uint16_t yStart,uint16_t xEnd,uint16_t yEnd,uint16_t Color);
void 			BSP_LCD_FillPic(uint16_t x, uint16_t y,uint16_t pic_H, uint16_t pic_V, uint16_t* pic);
void 			LCD_BACKLIGHT_PWM_Init(void);
void 			LCD_BACKLIGHT_PWM_50duty(void);
void 			LCD_BACKLIGHT_PWM_25duty(void);

#endif


