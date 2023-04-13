#include "main.h"			  
uint ChuShiZhi=0,ChuShiZhi2=0;
unsigned long count,count2; 
extern uchar FuWei_Flag,FuWei_Flag2;
//****************************************************
//延时函数
//****************************************************
void Delay__hx711_us(void)
{
	WDT_CONTR=0x3d;
	_nop_();
	_nop_();
}

//****************************************************
//读取HX711
//****************************************************
unsigned long HX711_Read(void)	//增益128
{
	unsigned char i; 
  	HX711_DOUT=1; 
  	HX711_DOUT2=1; 
	Delay__hx711_us();
  	HX711_SCK=0; 
  	HX711_SCK2=0; 
  	count=0; 
  	count2=0; 
  	while((HX711_DOUT)||(HX711_DOUT2))
		WDT_CONTR=0x3d; 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1;
	  	HX711_SCK2=1; 
	  	count=count<<1; 
	  	count2=count2<<1; 
		HX711_SCK=0; 
		HX711_SCK2=0; 
	  	if(HX711_DOUT)
			count++; 
	  	if(HX711_DOUT2)
			count2++; 
	} 
 	HX711_SCK=1; 
 	HX711_SCK2=1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
    count2=count2^0x800000;//第25个脉冲下降沿来时，转换数据
	Delay__hx711_us();
	HX711_SCK=0;
	HX711_SCK2=0; 
	count=count/1000;
	count2=count2/1000;
	if(FuWei_Flag==1) 
		ChuShiZhi=count;
	if(FuWei_Flag2==1) 
		ChuShiZhi2=count2;
	count=count-ChuShiZhi; 
	count2=count2-ChuShiZhi2;
	FuWei_Flag=0;
	FuWei_Flag2=0; 
	return(count);
}

//****************************************************
//初始化HX711
//****************************************************
void HX711_init(void)	//增益128
{						 
	unsigned char i; 
  	HX711_DOUT=1;
  	HX711_DOUT2=1;
	Delay__hx711_us();
  	HX711_SCK=0; 
  	HX711_SCK2=0; 
  	count=0; 
  	count2=0;    
  	while((HX711_DOUT)||(HX711_DOUT2))
		WDT_CONTR=0x3d; 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1;
	  	HX711_SCK2=1;
	  	count=count<<1; 
	  	count2=count2<<1; 
		HX711_SCK=0;
		HX711_SCK2=0;
	  	if(HX711_DOUT)
			count++;
	  	if(HX711_DOUT2)
			count2++;
	} 
 	HX711_SCK=1;
 	HX711_SCK2=1;
    count=count^0x800000;
    count2=count2^0x800000;
	Delay__hx711_us();
	HX711_SCK=0;
	HX711_SCK2=0;
	count=count/1000;
	count2=count2/1000;
	ChuShiZhi=count;
	ChuShiZhi2=count2;
}






