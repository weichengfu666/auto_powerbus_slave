#include "main.h"
uint Time=0,Time_i=0,HuXi_ZhanKongBi=0x400,cs_i=0,cs_j=0;
uchar ShuJuFaSong_Flag=0,EEPROM_CS[30];
code uchar XuLieHao[5]={0x52,0xAA,0x61,0x66,0xca};//11 52 44 55 a5 
																									//cc ba 61
code uchar EEPROM_ChuShi[100]=
{0x00,0x00
,0x00,0x01
,0x00,0x08,0x00,0x3c
,0x00,0x00,0x00,0x00
,0x00,0x03,0xe8,0x01
,0x00,0x07,0xd0,0x02,50
,0x00,0x0b,0xb8,0x03,100,0x00,0x07,0xd0,0
,0x00,0x13,0x88,0x04,0x00,0x05,0,0x00,0x03,0xe8,100,0x00,0x03,0xe8,50,0x00,0x03,0xe8,100,0x00,0x03,0xe8,50,0x00,0x03,0xe8
,0x00,0x27,0x10,0x01
};
extern code uint LiangDuDuiZhao[101];
extern uchar JiHuo[2],ZhuJiJieShou_HuanCun[3][20],ZhuJiJieShou_HuanCun_i[3],SouXunXuLie_Time,BiaoHaoFuZhi_Time;
extern char LiangDu_DangQian,LiangDu_ChuShi,LiangDu_JieShu;
extern ulong Delay_Time[5],MuBiao_Time[5],JianBian_Time1,JianBian_Time2;
extern uint GongNen_Addr_Shou[5],GongNen_Addr_Wei[5],XunHuan_Changdu,XunHuan_ZhiZhen,XunHuan_Addr;
extern long LiangDu_HuanCun;
void main()
{		
	Timer0Init();
	InitUART();
	IO_Init();
	FenJi_Init();
	PWM_Init();
	EEPROM_Write_Str(0x0000,EEPROM_ChuShi,60);
	PWM_ShuChu(10);
	P54=0;
	SendData(0x61);
	SendData2(0x61);
	for(;;)
	{	
	  WDT_CONTR=0x3d;
		FenJi_ShuJuChuLi2();
		ZongZhiXin();
		JianBian();
		if(ShuJuFaSong_Flag>0)
		{						
			ShuJuFaSong_Flag=0;	
		}  
	}
} 

void Time0_ISR(void) interrupt 1 using 1 
{
	Time++;	
	for(Time_i=0;Time_i<5;Time_i++)
	{
		if(Delay_Time[Time_i]>0)
		{
			Delay_Time[Time_i]++;
		}
	}
	if(JianBian_Time2>0)
	{
		JianBian_Time2--;
	}else if(JianBian_Time1>0)
	{
		JianBian_Time1=0;
		LiangDu_DangQian=LiangDu_JieShu;
		LiangDu_ChuShi=0;
		LiangDu_JieShu=0;
	}else if(XunHuan_Changdu>0)
	{	
		if(XunHuan_ZhiZhen<(XunHuan_Changdu-1))
		{
			XunHuan_ZhiZhen++;
		}else{
			XunHuan_ZhiZhen=0;
		}
		JianBian_Time1=IapReadByte(XunHuan_Addr+1+XunHuan_ZhiZhen*4)*0x10000+IapReadByte(XunHuan_Addr+2+XunHuan_ZhiZhen*4)*0x100+IapReadByte(XunHuan_Addr+3+XunHuan_ZhiZhen*4);
		JianBian_Time2=JianBian_Time1;
		LiangDu_ChuShi=IapReadByte(XunHuan_Addr+XunHuan_ZhiZhen*4);
		LiangDu_DangQian=LiangDu_ChuShi;
		if(XunHuan_ZhiZhen<(XunHuan_Changdu-1))
			LiangDu_JieShu=IapReadByte(XunHuan_Addr+4+XunHuan_ZhiZhen*4);
		else
			LiangDu_JieShu=IapReadByte(XunHuan_Addr);
		if(JianBian_Time1==0)
			LiangDu_DangQian=LiangDu_JieShu;
	}
	if(SouXunXuLie_Time>0)
	{
		SouXunXuLie_Time++;
	}
	if(BiaoHaoFuZhi_Time>0)
	{
		BiaoHaoFuZhi_Time++;
	}
	if(Time%500==0)
	{
		//ShuJuFaSong_Flag=1;
	} 	
	if(Time==30000)
	{
		Time=0;
	}
	   
}