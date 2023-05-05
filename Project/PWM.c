#include "main.h"

void PWM_Init()
{
		P_SW1=0x0c;//0000 1100
    CCON = 0x00;
    CMOD = 0x08;                                //PCA时钟为系统时钟
    CL = 0x00;
    CH = 0x00;
//--10位PWM--
    CCAPM2 = 0x42;//0x42;                          //PCA模块2为PWM工作模式 
		PCA_PWM2 = 0xe0;                           	//1100 0000
																								//1100 0000 EBSn：PCA模块2输出10位PWM  
																								//0011 0000 XCCAPnH：第9第10位重载值  
																								//0000 1100 XCCAPnL：第9第10位比较值  
																								//0000 0010 EPCnH：重载值最高位(11位)  
																								//0000 0001 EPCnL：比较值最高位（11位）
    CCAP2H = 0x00;															//重载值低8位
    CCAP2L = 0x00;                              //比较值低8位，PWM占空比为96.875%[(400H-20H)/400H]
    CR = 1;                                     //启动PCA计时器
		EA = 1;
}

void PWM_ShuChu(uint PWM_CS)//0~0x0400
{
	uint PWM_ZhanKongBi=0x400-PWM_CS;
	if(PWM_ZhanKongBi==0)
	{
		CCAPM2 = 0;
		P54=0;
	}else if(PWM_ZhanKongBi==0x0400)
	{
		CCAPM2 = 0;
		P54=1;
	}else{
		CCAPM2 = 0x42;//1100 1101
		PCA_PWM2=(PCA_PWM2&0xcd)|(((0x400-PWM_ZhanKongBi)>>4)&0x30);
		CCAP2H=(0x400-PWM_ZhanKongBi)&0xff;
	}
}