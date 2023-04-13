#ifndef __ADC_H__
#define __ADC_H__

sfr ADC_ERS	 =  0xBD;
sfr ADC_LOW2 =  0xBE;
 
#define ADC_POWER     0x80		 //��Դ����λ
#define ADC_FLAG	  0x10		 //��ɱ�־λ
#define ADC_START	  0x08		 //��ʼ��־λ
#define ADC_SPEEDLL	  0x00		 //540��ʱ��
#define ADC_SPEEDL	  0x20		 //360��ʱ��
#define ADC_SPEEDH	  0x40		 //180��ʱ��
#define ADC_SPEEDHH	  0x60		 //90��ʱ��

void ADC_init(void);
void ADC_GET(void);

#endif