#ifndef __ADMOKUAI_H__
#define __ADMOKUAI_H__

#define  PCF8591 0x90    //PCF8591 ��ַ
 
sbit ADSCL=P0^2;       //I2C  ʱ�� 
sbit ADSDA=P0^3;       //I2C  ����  
sbit ADZhen=P0^3;       //I2C  ���� 
sbit ADFu=P0^2;       //I2C  ���� 
sbit ADCeShi=P0^4;       //I2C  ���� 

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