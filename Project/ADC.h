#ifndef __ADC_H__
#define __ADC_H__

sfr ADC_ERS	 =  0xBD;
sfr ADC_LOW2 =  0xBE;
 
#define ADC_POWER     0x80		 //电源控制位
#define ADC_FLAG	  0x10		 //完成标志位
#define ADC_START	  0x08		 //起始标志位
#define ADC_SPEEDLL	  0x00		 //540个时钟
#define ADC_SPEEDL	  0x20		 //360个时钟
#define ADC_SPEEDH	  0x40		 //180个时钟
#define ADC_SPEEDHH	  0x60		 //90个时钟

void ADC_init(void);
void ADC_GET(void);

#endif