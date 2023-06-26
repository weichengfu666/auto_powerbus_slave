#include "bsp_lock.h"
#include "main.h"


//电磁锁控制全局变量
LOCK_TypeDef LOCK_xxArr[8] = {0};    //PWM00~PWM07


/*
*********************************************************************************************************
*	函 数 名: LOCK_GPIOConfig
*	功能说明: 电磁锁端口GPIO配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LOCK_GPIOConfig(u8 _PWMxx)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    switch( _PWMxx )
    {
        case 0: 
            GPIO_InitStructure.Pin  = 0;		//指定要初始化的IO,P60
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//初始化IO口
        break;
        case 1: 
            GPIO_InitStructure.Pin  = 2;		//指定要初始化的IO,P62
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//初始化IO口
        break;
        case 2: 
            GPIO_InitStructure.Pin  = 4;		//指定要初始化的IO,P64
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//初始化IO口
        break;
        case 3: 
            GPIO_InitStructure.Pin  = 6;		//指定要初始化的IO,P66
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//初始化IO口
        break;
        case 4: 
            GPIO_InitStructure.Pin  = 4;		//指定要初始化的IO,P74
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//初始化IO口
        break;
        case 5: 
            GPIO_InitStructure.Pin  = 5;		//指定要初始化的IO,P75
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//初始化IO口
        break;
        case 6: 
            GPIO_InitStructure.Pin  = 6;		//指定要初始化的IO,P76
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//初始化IO口
        break;
        case 7: 
            GPIO_InitStructure.Pin  = 7;		//指定要初始化的IO,P77
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//初始化IO口
        break;
    }
}
/*
*********************************************************************************************************
*	函 数 名: LOCK_PWM15Config_PWMxx
*	功能说明: 电磁锁端口PWM15配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LOCK_PWM15Config(void)
{
	PWMx_InitDefine		PWMx_InitStructure;
    //PWMA1~4
   { 
        PWMA_Duty.PWM1_Duty = 1024;
        PWMA_Duty.PWM2_Duty = 1024;
        PWMA_Duty.PWM3_Duty = 1024;
        PWMA_Duty.PWM4_Duty = 1024;
        
        PWMx_InitStructure.PWM1_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM2_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM3_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM4_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2

        PWMx_InitStructure.PWM1_SetPriority  = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
        PWMx_InitStructure.PWM2_SetPriority  = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
        PWMx_InitStructure.PWM3_SetPriority  = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
        PWMx_InitStructure.PWM4_SetPriority  = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
        
        PWMx_InitStructure.PWM_Period   = 1023;							//周期时间,   0~65535
        PWMx_InitStructure.PWM1_Duty    = PWMA_Duty.PWM1_Duty;	//PWM1占空比时间, 0~Period
        PWMx_InitStructure.PWM2_Duty    = PWMA_Duty.PWM2_Duty;	//PWM2占空比时间, 0~Period
        PWMx_InitStructure.PWM3_Duty    = PWMA_Duty.PWM3_Duty;	//PWM3占空比时间, 0~Period
        PWMx_InitStructure.PWM4_Duty    = PWMA_Duty.PWM4_Duty;	//PWM4占空比时间, 0~Period
        PWMx_InitStructure.PWM_DeadTime = 0;								//死区发生器设置, 0~255
        
        PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N | ENO2P | ENO2N | ENO3P | ENO3N | ENO4P | ENO4N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_PS_SW       = PWM1_SW_P60_P61| PWM2_SW_P62_P63 | PWM3_SW_P64_P65 | PWM4_SW_P66_P67;	//切换端口,		PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
                                                                                                                //						PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
                                                                                                                //						PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
                                                                                                                //						PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

        PWMx_InitStructure.PWM_CC1Enable   = ENABLE;				//开启PWM1P输入捕获/比较输出,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC1NEnable  = ENABLE;				//开启PWM1N输入捕获/比较输出,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC2Enable   = ENABLE;				//开启PWM2P输入捕获/比较输出,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC2NEnable  = ENABLE;				//开启PWM2N输入捕获/比较输出,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC3Enable   = ENABLE;				//开启PWM3P输入捕获/比较输出,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC3NEnable  = ENABLE;				//开启PWM3N输入捕获/比较输出,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC4Enable   = ENABLE;				//开启PWM4P输入捕获/比较输出,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC4NEnable  = ENABLE;				//开启PWM4N输入捕获/比较输出,  ENABLE,DISABLE
        
        PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//主输出使能, ENABLE,DISABLE
        PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//使能计数器, ENABLE,DISABLE
        PWM_Configuration(PWMA, &PWMx_InitStructure);				//初始化PWM,  PWMA,PWMB
    }
   //PWMB5~8
    {
        PWMB_Duty.PWM5_Duty = 1024;
        PWMB_Duty.PWM6_Duty = 1024;
        PWMB_Duty.PWM7_Duty = 1024;
        PWMB_Duty.PWM8_Duty = 1024;
        
        PWMx_InitStructure.PWM5_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM6_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM7_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM8_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2

        PWMx_InitStructure.PWM5_SetPriority  = Priority_0;			//指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
        
        PWMx_InitStructure.PWM_Period   = 1023;							//周期时间,   0~65535
        PWMx_InitStructure.PWM5_Duty    = PWMB_Duty.PWM5_Duty;	//PWM5占空比时间, 0~Period
        PWMx_InitStructure.PWM6_Duty    = PWMB_Duty.PWM6_Duty;	//PWM6占空比时间, 0~Period
        PWMx_InitStructure.PWM7_Duty    = PWMB_Duty.PWM7_Duty;	//PWM7占空比时间, 0~Period
        PWMx_InitStructure.PWM8_Duty    = PWMB_Duty.PWM8_Duty;	//PWM8占空比时间, 0~Period
        PWMx_InitStructure.PWM_DeadTime = 0;								//死区发生器设置, 0~255
        
        PWMx_InitStructure.PWM_EnoSelect   = ENO5P | ENO6P | ENO7P | ENO8P;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_PS_SW       = PWM5_SW_P74| PWM6_SW_P75 | PWM7_SW_P76 | PWM8_SW_P77;	//切换端口,		PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74
                                                                                                                //						PWM6_SW_P21,PWM6_SW_P54,PWM6_SW_P01,PWM6_SW_P75
                                                                                                                //						PWM7_SW_P22,PWM7_SW_P33,PWM7_SW_P02,PWM7_SW_P76
                                                                                                                //						PWM8_SW_P23,PWM8_SW_P34,PWM8_SW_P03,PWM8_SW_P77

        PWMx_InitStructure.PWM_CC5Enable   = ENABLE;				//开启PWM5P输入捕获/比较输出,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC6Enable   = ENABLE;				//开启PWM6P输入捕获/比较输出,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC7Enable   = ENABLE;				//开启PWM7P输入捕获/比较输出,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC8Enable   = ENABLE;				//开启PWM8P输入捕获/比较输出,  ENABLE,DISABLE
        
        PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//主输出使能, ENABLE,DISABLE
        PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//使能计数器, ENABLE,DISABLE
        PWM_Configuration(PWMB, &PWMx_InitStructure);				//初始化PWM,  PWMA,PWMB
    }
}

void LOCK_TIMER4Config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//结构定义
    TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;	            //指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;					//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;	//TIM周期 
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer4,&TIM_InitStructure);					//初始化Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
}

void LOCK_SetState(u8 _PWMxx, u8 _lock_state)
{
    LOCK_TypeDef* LOCK_xx = &LOCK_xxArr[_PWMxx];
    
    if( _lock_state == OPEN ) //通电
    {
        LOCK_xx->open_enable = ENABLE;
        LOCK_xx->close_enable = DISABLE;
        LOCK_xx->closeOpen_enable = DISABLE;
        LOCK_xx->openClose_enable = DISABLE;
    }
    else if( _lock_state == CLOSE ) //断电
    {
        LOCK_xx->open_enable = DISABLE;
        LOCK_xx->close_enable = ENABLE;
        LOCK_xx->closeOpen_enable = DISABLE;
        LOCK_xx->openClose_enable = DISABLE;
    }
    else if( _lock_state == CLOSE_OPEN ) //断后通
    {
        LOCK_xx->open_enable = DISABLE;
        LOCK_xx->close_enable = DISABLE;
        LOCK_xx->closeOpen_enable = ENABLE;
        LOCK_xx->openClose_enable = DISABLE;
    }
    else if( _lock_state == OPEN_CLOSE ) //通后断
    {
        LOCK_xx->open_enable = DISABLE;
        LOCK_xx->close_enable = DISABLE;
        LOCK_xx->closeOpen_enable = DISABLE;
        LOCK_xx->openClose_enable = ENABLE;
    }
}

void LOCK_Init( u8 _PWMxx, u8 _lock_state, u32 _lock_delayTime )
{
    LOCK_TypeDef* LOCK_xx = &LOCK_xxArr[_PWMxx];
    
    LOCK_xx->delayTime_cnt = 0;
    LOCK_xx->delayTime_cntcmp = _lock_delayTime;  //通断延时
    LOCK_GPIOConfig(_PWMxx);                    //电磁锁端口GPIO配置函数
    LOCK_PWM15Config();                             //电磁锁端口PWM15配置函数
    LOCK_TIMER4Config();                             //电磁锁端口TIMER4配置函数
    LOCK_SetState(_PWMxx, _lock_state);       //设置状态
}

void LOCK_TIMER4IntCallback0x( u8 _PWMxx )
{
    LOCK_TypeDef* LOCK_xx = &LOCK_xxArr[_PWMxx];
    LOCK_xx->delayTime_cnt++;
    if( LOCK_xx->open_enable == ENABLE )
    {
        PWMDuty(_PWMxx, 0); //输出低电平
    }
    else if( LOCK_xx->close_enable == ENABLE )
    {
        PWMDuty(_PWMxx, 1024); //输出高电平
    }
    else if( LOCK_xx->closeOpen_enable == ENABLE )
    {
        if( LOCK_xx->delayTime_cnt <= LOCK_xx->delayTime_cntcmp )
        {
            PWMDuty(_PWMxx, 1024); //输出高电平
        }
        else
        {
            PWMDuty(_PWMxx, 0); //输出低电平
            LOCK_xx->closeOpen_enable = DISABLE;
        }
    }
    else if( LOCK_xx->openClose_enable == ENABLE )
    {
        if( LOCK_xx->delayTime_cnt <= LOCK_xx->delayTime_cntcmp )
        {
            PWMDuty(_PWMxx, 0); //输出低电平
        }
        else
        {
            PWMDuty(_PWMxx, 1024); //输出高电平
            LOCK_xx->openClose_enable = DISABLE;
        }
    }
}



////测试程序
//    LOCK_Init( PWM1_PORT, CLOSE_OPEN, 1000 );
//    LOCK_Init( PWM2_PORT, CLOSE_OPEN, 2000 );
//    LOCK_Init( PWM3_PORT, CLOSE_OPEN, 3000 );
//    LOCK_Init( PWM4_PORT, CLOSE_OPEN, 4000 );
//    LOCK_Init( PWM5_PORT, CLOSE_OPEN, 5000 );
//    LOCK_Init( PWM6_PORT, CLOSE_OPEN, 6000 );
//    LOCK_Init( PWM7_PORT, CLOSE_OPEN, 7000 );
//    LOCK_Init( PWM8_PORT, CLOSE_OPEN, 8000 );