/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

/*************	功能说明	**************

本文件为STC8系列的定时器初始化和中断程序,用户可以在这个文件中修改自己需要的中断程序.

******************************************/

#include	"timer.h"
#include "main.h"

///********************* Timer0中断函数************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{
    if(LED_displayTime != 0)
    {
        LED_displayTime++;
    }
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

/********************* Timer1中断函数************************/
void timer1_int (void) interrupt TIMER1_VECTOR
{
   P21 = ~P21;
}

/********************* Timer2中断函数************************/
u8 arrIndex = 0;
u32 DisplayTimeCnt_ms;//定时器2周期计数标志
u32 DisplayTimeCntCmpArr[100] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};//定时器2周期计数比较标志数组
u8 DisplayTimeCntCmpArr_len = 10;
void timer2_int (void) interrupt TIMER2_VECTOR
{
    DisplayTimeCnt_ms++;

    if(arrIndex < DisplayTimeCntCmpArr_len && DisplayTimeCnt_ms >= DisplayTimeCntCmpArr[arrIndex])
    {
        arrIndex++;
        P06 = ~P06; 
    }
}
/********************* Timer3中断函数************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{
//	LED_flashTIMER3IntCallback();
}

/********************* Timer4中断函数************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{	
    LED_breathTIMER4IntCallback0x(PWM00);
    LED_breathTIMER4IntCallback0x(PWM01);
    LED_breathTIMER4IntCallback0x(PWM02);
    LED_breathTIMER4IntCallback0x(PWM03);
    LED_breathTIMER4IntCallback0x(PWM04);
    LED_breathTIMER4IntCallback0x(PWM05);
    LED_breathTIMER4IntCallback0x(PWM06);
    LED_breathTIMER4IntCallback0x(PWM07);

    LED_breathTIMER4IntCallback0x(PWM20);
    LED_breathTIMER4IntCallback0x(PWM21);
    LED_breathTIMER4IntCallback0x(PWM22);
    LED_breathTIMER4IntCallback0x(PWM23);
    LED_breathTIMER4IntCallback0x(PWM24);
    LED_breathTIMER4IntCallback0x(PWM25);
    LED_breathTIMER4IntCallback0x(PWM26);
    LED_breathTIMER4IntCallback0x(PWM27);
}


//========================================================================
// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//空操作

	if(TIM == Timer0)
	{
		Timer0_Stop();		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		Timer0_InterruptEnable();	//允许中断
		else		Timer0_InterruptDisable();	//禁止中断
		if(TIMx->TIM_Priority > Priority_3)	return 2;	//错误
		Timer0_Priority(TIMx->TIM_Priority);	//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 不可屏蔽16位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer0_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer0_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer0_AsCounter();	//对外计数或分频
		else		Timer0_AsTimer();	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	Timer0_CLKO_Enable();	//输出时钟
		else		Timer0_CLKO_Disable();	//不输出时钟
		
		T0_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer0_Run();	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer1)
	{
		Timer1_Stop();		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		Timer1_InterruptEnable();	//允许中断
		else		Timer1_InterruptDisable();	//禁止中断
		if(TIMx->TIM_Priority > Priority_3)	return 2;	//错误
		Timer1_Priority(TIMx->TIM_Priority);	//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | (TIMx->TIM_Mode<<4);	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 停止工作
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer1_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer1_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer1_AsCounter();	//对外计数或分频
		else		Timer1_AsTimer();	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	Timer1_CLKO_Enable();	//输出时钟
		else		Timer1_CLKO_Disable();	//不输出时钟
		
		T1_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer1_Run();	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		Timer2_Stop();	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		Timer2_InterruptEnable();	//允许中断
		else		Timer2_InterruptDisable();	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer2_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer2_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer2_AsCounter();	//对外计数或分频
		else		Timer2_AsTimer();		//定时
		if(TIMx->TIM_ClkOut == ENABLE)	Timer2_CLKO_Enable();		//输出时钟
		else		Timer2_CLKO_Disable();	//不输出时钟

		T2_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer2_Run();	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer3)		//Timer3,固定为16位自动重装, 中断无优先级
	{
		Timer3_Stop();	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		Timer3_InterruptEnable();	//允许中断
		else		Timer3_InterruptDisable();	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer3_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer3_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer3_AsCounter();	//对外计数或分频
		else		Timer3_AsTimer();		//定时
		if(TIMx->TIM_ClkOut == ENABLE)	Timer3_CLKO_Enable();		//输出时钟
		else		Timer3_CLKO_Disable();	//不输出时钟

		T3_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer3_Run();	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer4)		//Timer3,固定为16位自动重装, 中断无优先级
	{
		Timer4_Stop();	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		Timer4_InterruptEnable();	//允许中断
		else		Timer4_InterruptDisable();	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer4_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer4_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer4_AsCounter();	//对外计数或分频
		else		Timer4_AsTimer();		//定时
		if(TIMx->TIM_ClkOut == ENABLE)	Timer4_CLKO_Enable();		//输出时钟
		else		Timer4_CLKO_Disable();	//不输出时钟

		T4_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer4_Run();	//开始运行
		return	0;		//成功
	}
	return 2;	//错误
}
