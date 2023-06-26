#include "bsp_lock.h"
#include "main.h"


//���������ȫ�ֱ���
LOCK_TypeDef LOCK_xxArr[8] = {0};    //PWM00~PWM07


/*
*********************************************************************************************************
*	�� �� ��: LOCK_GPIOConfig
*	����˵��: ������˿�GPIO���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LOCK_GPIOConfig(u8 _PWMxx)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    switch( _PWMxx )
    {
        case 0: 
            GPIO_InitStructure.Pin  = 0;		//ָ��Ҫ��ʼ����IO,P60
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 1: 
            GPIO_InitStructure.Pin  = 2;		//ָ��Ҫ��ʼ����IO,P62
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 2: 
            GPIO_InitStructure.Pin  = 4;		//ָ��Ҫ��ʼ����IO,P64
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 3: 
            GPIO_InitStructure.Pin  = 6;		//ָ��Ҫ��ʼ����IO,P66
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 4: 
            GPIO_InitStructure.Pin  = 4;		//ָ��Ҫ��ʼ����IO,P74
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 5: 
            GPIO_InitStructure.Pin  = 5;		//ָ��Ҫ��ʼ����IO,P75
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 6: 
            GPIO_InitStructure.Pin  = 6;		//ָ��Ҫ��ʼ����IO,P76
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 7: 
            GPIO_InitStructure.Pin  = 7;		//ָ��Ҫ��ʼ����IO,P77
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
    }
}
/*
*********************************************************************************************************
*	�� �� ��: LOCK_PWM15Config_PWMxx
*	����˵��: ������˿�PWM15���ú���
*	�� �� ֵ: void
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
        
        PWMx_InitStructure.PWM1_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM2_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM3_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM4_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2

        PWMx_InitStructure.PWM1_SetPriority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
        PWMx_InitStructure.PWM2_SetPriority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
        PWMx_InitStructure.PWM3_SetPriority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
        PWMx_InitStructure.PWM4_SetPriority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
        
        PWMx_InitStructure.PWM_Period   = 1023;							//����ʱ��,   0~65535
        PWMx_InitStructure.PWM1_Duty    = PWMA_Duty.PWM1_Duty;	//PWM1ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM2_Duty    = PWMA_Duty.PWM2_Duty;	//PWM2ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM3_Duty    = PWMA_Duty.PWM3_Duty;	//PWM3ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM4_Duty    = PWMA_Duty.PWM4_Duty;	//PWM4ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM_DeadTime = 0;								//��������������, 0~255
        
        PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N | ENO2P | ENO2N | ENO3P | ENO3N | ENO4P | ENO4N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_PS_SW       = PWM1_SW_P60_P61| PWM2_SW_P62_P63 | PWM3_SW_P64_P65 | PWM4_SW_P66_P67;	//�л��˿�,		PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
                                                                                                                //						PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
                                                                                                                //						PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
                                                                                                                //						PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

        PWMx_InitStructure.PWM_CC1Enable   = ENABLE;				//����PWM1P���벶��/�Ƚ����,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC1NEnable  = ENABLE;				//����PWM1N���벶��/�Ƚ����,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC2Enable   = ENABLE;				//����PWM2P���벶��/�Ƚ����,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC2NEnable  = ENABLE;				//����PWM2N���벶��/�Ƚ����,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC3Enable   = ENABLE;				//����PWM3P���벶��/�Ƚ����,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC3NEnable  = ENABLE;				//����PWM3N���벶��/�Ƚ����,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC4Enable   = ENABLE;				//����PWM4P���벶��/�Ƚ����,  ENABLE,DISABLE
    //	PWMx_InitStructure.PWM_CC4NEnable  = ENABLE;				//����PWM4N���벶��/�Ƚ����,  ENABLE,DISABLE
        
        PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
        PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
        PWM_Configuration(PWMA, &PWMx_InitStructure);				//��ʼ��PWM,  PWMA,PWMB
    }
   //PWMB5~8
    {
        PWMB_Duty.PWM5_Duty = 1024;
        PWMB_Duty.PWM6_Duty = 1024;
        PWMB_Duty.PWM7_Duty = 1024;
        PWMB_Duty.PWM8_Duty = 1024;
        
        PWMx_InitStructure.PWM5_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM6_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM7_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
        PWMx_InitStructure.PWM8_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2

        PWMx_InitStructure.PWM5_SetPriority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
        
        PWMx_InitStructure.PWM_Period   = 1023;							//����ʱ��,   0~65535
        PWMx_InitStructure.PWM5_Duty    = PWMB_Duty.PWM5_Duty;	//PWM5ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM6_Duty    = PWMB_Duty.PWM6_Duty;	//PWM6ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM7_Duty    = PWMB_Duty.PWM7_Duty;	//PWM7ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM8_Duty    = PWMB_Duty.PWM8_Duty;	//PWM8ռ�ձ�ʱ��, 0~Period
        PWMx_InitStructure.PWM_DeadTime = 0;								//��������������, 0~255
        
        PWMx_InitStructure.PWM_EnoSelect   = ENO5P | ENO6P | ENO7P | ENO8P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
        PWMx_InitStructure.PWM_PS_SW       = PWM5_SW_P74| PWM6_SW_P75 | PWM7_SW_P76 | PWM8_SW_P77;	//�л��˿�,		PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74
                                                                                                                //						PWM6_SW_P21,PWM6_SW_P54,PWM6_SW_P01,PWM6_SW_P75
                                                                                                                //						PWM7_SW_P22,PWM7_SW_P33,PWM7_SW_P02,PWM7_SW_P76
                                                                                                                //						PWM8_SW_P23,PWM8_SW_P34,PWM8_SW_P03,PWM8_SW_P77

        PWMx_InitStructure.PWM_CC5Enable   = ENABLE;				//����PWM5P���벶��/�Ƚ����,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC6Enable   = ENABLE;				//����PWM6P���벶��/�Ƚ����,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC7Enable   = ENABLE;				//����PWM7P���벶��/�Ƚ����,  ENABLE,DISABLE
        PWMx_InitStructure.PWM_CC8Enable   = ENABLE;				//����PWM8P���벶��/�Ƚ����,  ENABLE,DISABLE
        
        PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
        PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
        PWM_Configuration(PWMB, &PWMx_InitStructure);				//��ʼ��PWM,  PWMA,PWMB
    }
}

void LOCK_TIMER4Config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����
    TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;	            //ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;					//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;	//TIM���� 
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer4,&TIM_InitStructure);					//��ʼ��Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
}

void LOCK_SetState(u8 _PWMxx, u8 _lock_state)
{
    LOCK_TypeDef* LOCK_xx = &LOCK_xxArr[_PWMxx];
    
    if( _lock_state == OPEN ) //ͨ��
    {
        LOCK_xx->open_enable = ENABLE;
        LOCK_xx->close_enable = DISABLE;
        LOCK_xx->closeOpen_enable = DISABLE;
        LOCK_xx->openClose_enable = DISABLE;
    }
    else if( _lock_state == CLOSE ) //�ϵ�
    {
        LOCK_xx->open_enable = DISABLE;
        LOCK_xx->close_enable = ENABLE;
        LOCK_xx->closeOpen_enable = DISABLE;
        LOCK_xx->openClose_enable = DISABLE;
    }
    else if( _lock_state == CLOSE_OPEN ) //�Ϻ�ͨ
    {
        LOCK_xx->open_enable = DISABLE;
        LOCK_xx->close_enable = DISABLE;
        LOCK_xx->closeOpen_enable = ENABLE;
        LOCK_xx->openClose_enable = DISABLE;
    }
    else if( _lock_state == OPEN_CLOSE ) //ͨ���
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
    LOCK_xx->delayTime_cntcmp = _lock_delayTime;  //ͨ����ʱ
    LOCK_GPIOConfig(_PWMxx);                    //������˿�GPIO���ú���
    LOCK_PWM15Config();                             //������˿�PWM15���ú���
    LOCK_TIMER4Config();                             //������˿�TIMER4���ú���
    LOCK_SetState(_PWMxx, _lock_state);       //����״̬
}

void LOCK_TIMER4IntCallback0x( u8 _PWMxx )
{
    LOCK_TypeDef* LOCK_xx = &LOCK_xxArr[_PWMxx];
    LOCK_xx->delayTime_cnt++;
    if( LOCK_xx->open_enable == ENABLE )
    {
        PWMDuty(_PWMxx, 0); //����͵�ƽ
    }
    else if( LOCK_xx->close_enable == ENABLE )
    {
        PWMDuty(_PWMxx, 1024); //����ߵ�ƽ
    }
    else if( LOCK_xx->closeOpen_enable == ENABLE )
    {
        if( LOCK_xx->delayTime_cnt <= LOCK_xx->delayTime_cntcmp )
        {
            PWMDuty(_PWMxx, 1024); //����ߵ�ƽ
        }
        else
        {
            PWMDuty(_PWMxx, 0); //����͵�ƽ
            LOCK_xx->closeOpen_enable = DISABLE;
        }
    }
    else if( LOCK_xx->openClose_enable == ENABLE )
    {
        if( LOCK_xx->delayTime_cnt <= LOCK_xx->delayTime_cntcmp )
        {
            PWMDuty(_PWMxx, 0); //����͵�ƽ
        }
        else
        {
            PWMDuty(_PWMxx, 1024); //����ߵ�ƽ
            LOCK_xx->openClose_enable = DISABLE;
        }
    }
}



////���Գ���
//    LOCK_Init( PWM1_PORT, CLOSE_OPEN, 1000 );
//    LOCK_Init( PWM2_PORT, CLOSE_OPEN, 2000 );
//    LOCK_Init( PWM3_PORT, CLOSE_OPEN, 3000 );
//    LOCK_Init( PWM4_PORT, CLOSE_OPEN, 4000 );
//    LOCK_Init( PWM5_PORT, CLOSE_OPEN, 5000 );
//    LOCK_Init( PWM6_PORT, CLOSE_OPEN, 6000 );
//    LOCK_Init( PWM7_PORT, CLOSE_OPEN, 7000 );
//    LOCK_Init( PWM8_PORT, CLOSE_OPEN, 8000 );