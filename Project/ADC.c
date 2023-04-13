#include "main.h"
int ADC_ShuZu[8]=0,ADC_i=0;
void ADC_init(void)
{
	P1ASF=0x20;
	ADC_RES=0;
	ADC_CONTR=ADC_POWER|ADC_SPEEDLL|ADC_START|0x00;
}
void ADC_GET(void)
{
	for(ADC_i=0;ADC_i<8;ADC_i++)
	{	 
		ADC_RES=0;
		ADC_CONTR=ADC_POWER|ADC_SPEEDLL|ADC_START|ADC_i;
		delay_ms(2);
		ADC_ShuZu[ADC_i]=ADC_ERS*4+ADC_LOW2;
	}
}
