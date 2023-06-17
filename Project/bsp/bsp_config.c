#include "bsp_config.h"
#include "main.h"
/*************	全局变量 	**************/
//（ 定时器的周期 ）
u16 TIM_Value_1ms       = MAIN_Fosc / 1000;
u16 TIM_Value_100us     = MAIN_Fosc / 10000;
u16 TIM_Value_10us      = MAIN_Fosc / 100000;
u16 TIM_Value_1us       = MAIN_Fosc / 1000000;
//（ PWM的周期 ）
u16 PWM_Period_1ms      = MAIN_Fosc / 1000;     //24000
u16 PWM_Period_100us    = MAIN_Fosc / 10000;    //2400
u16 PWM_Period_10us     = MAIN_Fosc / 100000;   //240
u16 PWM_Period_1us      = MAIN_Fosc / 1000000;  //24
//（ 定时器中断中控制PWM的周期和方向 ）
u16	pwm0,pwm1,pwm2;
bit	B_PWM0_Dir,B_PWM1_Dir;	//方向, 0为+, 1为-.



#if 0
/*
*********************************************************************************************************
*	函 数 名: GPIO_config
*	功能说明: IO配置函数
*	形    参: void
*	返 回 值: void
*********************************************************************************************************
*/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化
    
    
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//初始化
}
/*
*********************************************************************************************************
*	函 数 名: Timer_config
*	功能说明: 定时器配置
*	形    参: void
*	返 回 值: void
*********************************************************************************************************
*/
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;						//结构定义
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Priority    = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;		//TIM周期 TIM_Value_1ms
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);					//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Priority    = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;			//TIM周期 TIM_Value_10us
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);					//初始化Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);				//初值
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer2,&TIM_InitStructure);					//初始化Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;	//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;					//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//初值
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer3,&TIM_InitStructure);					//初始化Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;	//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;					//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//初值
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer4,&TIM_InitStructure);					//初始化Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4
}
/*
*********************************************************************************************************
*	函 数 名: PWM15_config
*	功能说明: PWM15配置
*	形    参: void
*	返 回 值: void
*********************************************************************************************************
*/
void	PWM15_config(void)
{
    PWM15_InitTypeDef		PWM15_InitStructure;
	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWM使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = PWM_Period_100us;		//PWM周期 PWM_Period_100us,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWMn_CLK_SYS;		//时钟源选择,  PWMn_CLK_SYS, PWMn_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//系统时钟分频参数(PS+1分频),  0~15
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//计数器使能,  ENABLE, DISABLE
	PWM15_Init(PWM0,&PWM15_InitStructure);
	
	PWM15Duty(PWM00,0x000,0x400);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWM15Duty(PWM01,0x000,0x400);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWM15Duty(PWM02,0x000,0x800);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWM15Duty(PWM03,0x200,0xc00);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWMChannelCtrl(PWM00,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
	PWMChannelCtrl(PWM01,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
	PWMChannelCtrl(PWM02,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
	PWMChannelCtrl(PWM03,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
}
/*
*********************************************************************************************************
*	函 数 名: LED_FlashConfig
*	功能说明: led闪烁配置
*	形    参: void
*	返 回 值: void
*********************************************************************************************************
*/
void LED_FlashConfig(void)
{
    GPIO_config();
    Timer_config();
    PWM15_config();
}
/*
*********************************************************************************************************
*	函 数 名: LED_Flash
*	功能说明: led闪烁
*	形    参: void
*	返 回 值: void
*********************************************************************************************************
*/
void LED_Flash(void)
{
    delay_ms(1);
    if(B_PWM0_Dir)
    {
            if(--pwm0 <= 0x00)		B_PWM0_Dir = 0;	//PWM00
    }
    else	if(++pwm0 >= 0x1000)	B_PWM0_Dir = 1;	//PWM00
    PWM15Duty(PWM00,0,pwm0);
    if(B_PWM1_Dir)
    {
            if(--pwm1 <= 0x00)		B_PWM1_Dir = 0;	//PWM01
    }
    else	if(++pwm1 >= 0x1000)	B_PWM1_Dir = 1;	//PWM01
    PWM15Duty(PWM01,0,pwm1);

    if(pwm2 >= 3000)
    {
        pwm2 = 0;
    }
    else	if(pwm2 >= 2000)
    {
            PWMLevelSet(PWM02,ENABLE,DISABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
    }
    else	if(pwm2 >= 1000)
    {
            PWMLevelSet(PWM02,DISABLE,ENABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
    }
    else
    {
            PWMLevelSet(PWM02,DISABLE,DISABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
    }
    pwm2++;
}
#endif






