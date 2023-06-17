#include "bsp_config.h"
#include "main.h"
/*************	ȫ�ֱ��� 	**************/
//�� ��ʱ�������� ��
u16 TIM_Value_1ms       = MAIN_Fosc / 1000;
u16 TIM_Value_100us     = MAIN_Fosc / 10000;
u16 TIM_Value_10us      = MAIN_Fosc / 100000;
u16 TIM_Value_1us       = MAIN_Fosc / 1000000;
//�� PWM������ ��
u16 PWM_Period_1ms      = MAIN_Fosc / 1000;     //24000
u16 PWM_Period_100us    = MAIN_Fosc / 10000;    //2400
u16 PWM_Period_10us     = MAIN_Fosc / 100000;   //240
u16 PWM_Period_1us      = MAIN_Fosc / 1000000;  //24
//�� ��ʱ���ж��п���PWM�����ںͷ��� ��
u16	pwm0,pwm1,pwm2;
bit	B_PWM0_Dir,B_PWM1_Dir;	//����, 0Ϊ+, 1Ϊ-.



#if 0
/*
*********************************************************************************************************
*	�� �� ��: GPIO_config
*	����˵��: IO���ú���
*	��    ��: void
*	�� �� ֵ: void
*********************************************************************************************************
*/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//��ʼ��
    
    
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//��ʼ��
}
/*
*********************************************************************************************************
*	�� �� ��: Timer_config
*	����˵��: ��ʱ������
*	��    ��: void
*	�� �� ֵ: void
*********************************************************************************************************
*/
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Priority    = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;		//TIM���� TIM_Value_1ms
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);					//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Priority    = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;			//TIM���� TIM_Value_10us
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);					//��ʼ��Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);				//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer2,&TIM_InitStructure);					//��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;	//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;					//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer3,&TIM_InitStructure);					//��ʼ��Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4

	TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;	//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;					//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//��ֵ
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer4,&TIM_InitStructure);					//��ʼ��Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4
}
/*
*********************************************************************************************************
*	�� �� ��: PWM15_config
*	����˵��: PWM15����
*	��    ��: void
*	�� �� ֵ: void
*********************************************************************************************************
*/
void	PWM15_config(void)
{
    PWM15_InitTypeDef		PWM15_InitStructure;
	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWMʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = PWM_Period_100us;		//PWM���� PWM_Period_100us,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWMn_CLK_SYS;		//ʱ��Դѡ��,  PWMn_CLK_SYS, PWMn_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//ϵͳʱ�ӷ�Ƶ����(PS+1��Ƶ),  0~15
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//������ʹ��,  ENABLE, DISABLE
	PWM15_Init(PWM0,&PWM15_InitStructure);
	
	PWM15Duty(PWM00,0x000,0x400);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWM15Duty(PWM01,0x000,0x400);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWM15Duty(PWM02,0x000,0x800);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWM15Duty(PWM03,0x200,0xc00);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWMChannelCtrl(PWM00,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	PWMChannelCtrl(PWM01,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	PWMChannelCtrl(PWM02,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	PWMChannelCtrl(PWM03,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
}
/*
*********************************************************************************************************
*	�� �� ��: LED_FlashConfig
*	����˵��: led��˸����
*	��    ��: void
*	�� �� ֵ: void
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
*	�� �� ��: LED_Flash
*	����˵��: led��˸
*	��    ��: void
*	�� �� ֵ: void
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
            PWMLevelSet(PWM02,ENABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
    }
    else	if(pwm2 >= 1000)
    {
            PWMLevelSet(PWM02,DISABLE,ENABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
    }
    else
    {
            PWMLevelSet(PWM02,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
    }
    pwm2++;
}
#endif






