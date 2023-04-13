#include "main.h"


uchar P30_MoShi=0;   	   //0Ϊ����̬���룬1Ϊǿ�����2Ϊͨ��IO��3Ϊ��©���
uchar P31_MoShi=1;   	   //0Ϊ����̬���룬1Ϊǿ�����2Ϊͨ��IO��3Ϊ��©���
uchar P32_MoShi=1;   	   //0Ϊ����̬���룬1Ϊǿ�����2Ϊͨ��IO��3Ϊ��©���
uchar P33_MoShi=1;   	   //0Ϊ����̬���룬1Ϊǿ�����2Ϊͨ��IO��3Ϊ��©���

uchar P54_MoShi=1;   	   //0Ϊ����̬���룬1Ϊǿ�����2Ϊͨ��IO��3Ϊ��©���
uchar P55_MoShi=0;   	   //0Ϊ����̬���룬1Ϊǿ�����2Ϊͨ��IO��3Ϊ��©���

int delay_ms_flag,delay_ms_tium;
void Timer0Init(void)		//1����@24.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x30;				//���ö�ʱ��ֵ
	TH0 = 0xF8;				//���ö�ʱ��ֵ
	EA=1;						   
  ET0 = 1;
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
} 																				
void IO_Init(void)
{
	P1M0 = 0x02; 
	P1M1 = 0xfd; 
/*********************************************************************************/
	if(P30_MoShi==0)
	{
		P3M1=P3M1|0x01;
		P3M0=P3M0&0xfe;	
	}else if(P30_MoShi==1){
		P3M1=P3M1&0xfe;
		P3M0=P3M0|0x01;
	}else if(P30_MoShi==2){
		P3M1=P3M1&0xfe;
		P3M0=P3M0&0xfe;
	}else if(P30_MoShi==3){
		P3M1=P3M1|0x01;
		P3M0=P3M0|0x01;
	}
	if(P31_MoShi==0)
	{
		P3M1=P3M1|0x02;
		P3M0=P3M0&0xfd;	
	}else if(P31_MoShi==1){
		P3M1=P3M1&0xfd;
		P3M0=P3M0|0x02;
	}else if(P31_MoShi==2){
		P3M1=P3M1&0xfd;
		P3M0=P3M0&0xfd;
	}else if(P31_MoShi==3){
		P3M1=P3M1|0x02;
		P3M0=P3M0|0x02;
	}
	if(P32_MoShi==0)
	{
		P3M1=P3M1|0x04;
		P3M0=P3M0&0xfb;	
	}else if(P32_MoShi==1){
		P3M1=P3M1&0xfb;
		P3M0=P3M0|0x04;
	}else if(P32_MoShi==2){
		P3M1=P3M1&0xfb;
		P3M0=P3M0&0xfb;
	}else if(P32_MoShi==3){
		P3M1=P3M1|0x04;
		P3M0=P3M0|0x04;
	}
	if(P33_MoShi==0)
	{
		P3M1=P3M1|0x08;
		P3M0=P3M0&0xf7;	
	}else if(P33_MoShi==1){
		P3M1=P3M1&0xf7;
		P3M0=P3M0|0x08;
	}else if(P33_MoShi==2){
		P3M1=P3M1&0xf7;
		P3M0=P3M0&0xf7;
	}else if(P33_MoShi==3){
		P3M1=P3M1|0x08;
		P3M0=P3M0|0x08;
	}
/*********************************************************************************/
	if(P54_MoShi==0)
	{
		P5M1=P5M1|0x10;
		P5M0=P5M0&0xef;	
	}else if(P54_MoShi==1){
		P5M1=P5M1&0xef;
		P5M0=P5M0|0x10;
	}else if(P54_MoShi==2){
		P5M1=P5M1&0xef;
		P5M0=P5M0&0xef;
	}else if(P54_MoShi==3){
		P5M1=P5M1|0x10;
		P5M0=P5M0|0x10;
	}
	if(P55_MoShi==0)
	{
		P5M1=P5M1|0x20;
		P5M0=P5M0&0xdf;	
	}else if(P55_MoShi==1){
		P5M1=P5M1&0xdf;
		P5M0=P5M0|0x20;
	}else if(P55_MoShi==2){
		P5M1=P5M1&0xdf;
		P5M0=P5M0&0xdf;
	}else if(P55_MoShi==3){
		P5M1=P5M1|0x20;
		P5M0=P5M0|0x20;
	}	  	
}
