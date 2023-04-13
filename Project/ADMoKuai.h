#ifndef __ADMOKUAI_H__
#define __ADMOKUAI_H__

#define  PCF8591 0x90    //PCF8591 地址
 
sbit ADSCL=P0^2;       //I2C  时钟 
sbit ADSDA=P0^3;       //I2C  数据  
sbit ADZhen=P0^3;       //I2C  数据 
sbit ADFu=P0^2;       //I2C  数据 
sbit ADCeShi=P0^4;       //I2C  数据 

void AD_Delay10us();
void AD_Start_I2c();   
void AD_Stop_I2c();
void AD_SendByte(unsigned char c);
unsigned char AD_RcvByte();
void AD_Ack_I2c(bit a);
bit AD_ISendByte(unsigned char sla,unsigned char c);
unsigned char AD_IRcvByte(unsigned char sla);
void ADMoKuai_DuQu(void);

#endif 