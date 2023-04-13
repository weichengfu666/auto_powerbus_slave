#ifndef __51oled_H__
#define __51oled_H__
#include "main.h"

#define high 1
#define low 0 
/*************Pin Define***************/
sbit Oled_SCL=P0^4;
sbit Oled_SDA=P0^3;

void Initial_M096128x64_ssd1306();
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void Write_IIC_Byte(unsigned char IIC_Byte);
void LCD_Set_Pos(unsigned char x, unsigned char y);
void LCD_P6x8num(unsigned char x,unsigned char y,int num);

#endif
