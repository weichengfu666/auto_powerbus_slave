#ifndef __HX711_H__
#define __HX711_H__

//IO����
sbit HX711_DOUT=P3^2; 
sbit HX711_SCK=P3^3; 
sbit HX711_DOUT2=P5^4; 
sbit HX711_SCK2=P5^5; 

//�������߱�������
extern void Delay__hx711_us(void);
extern unsigned long HX711_Read(void);
void HX711_init(void);

#endif 