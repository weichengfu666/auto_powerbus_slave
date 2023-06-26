#include "bsp_led.h"
#include "main.h"


#if LED_BREATH  //100*2 + 100*2 + 2 + 24*22��528�� = 930 �ֽ�

/* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/

//code u16 indexWaveBreath[100] = {
//1,   1,   1,   2,   2,    2,    3,    3,    4,    5,
//5,   6,   7,   8,   9,    10,   11,   13,   15,   17, 
//19,  22,  25,  28,  32,   36,   41,   47,   53,   69, 
//79,  89,  116, 131, 149,  170,  193,  219,  250,  284,
//323, 367, 417, 474, 539,  613,  697,  792,  901,  1024, 
//1024,901, 792, 697, 613,  539,  474,  417,  367,  323,
//284, 250, 219, 193, 170,  149,  131,  116,  89,   79, 
//69,  53,  47,  41,  36,   32,   28,   25,   22,   19, 
//17,  15,  13,  11,  10,   9,    8,    7,    6,    5, 
//5,   4,   3,   3,   2,    2,    2,    1,    1,    1
//};


code u16 indexWaveBreath[202] = {
1,1,         1,      1,      1,      1,      1,      2,      2,      2,      2,       2,        2,       3,       3,       3,     3,       4,      4,      5,        5,
5,         5,      6,      6,      7,      7,      8,      8,      9,      9,     10,      10,      11,     11,     13,    13,     15,    15,    17,      17, 
19,      19,    22,    22,    25,    25,     28,    28,    32,    32,     36,      36,      41,     41,     47,    47,     53,    53,    69,      69, 
79,      79,    89,    89,  116,   116,  131,   131,   149,   149,   170,    170,    193,   193,   219,   219,  250,   250,   284,  284,
323,   323,  367,  367,  417,   417, 474,   474,    539,   539,   613,    613,    697,   697,   792,   792,  901,   901, 1024,1024, 
1024,1024, 901,  901,  792,   792,  697,   697,   613,   613,   539,    539,     474,   474,  417,   417,  367,   367,   323,  323,
284,   284,  250,  250,  219,  219,   193,   193,   170,   170,   149,   149,    131,     131,  116,   116,    89,    89,     79,    79, 
69,       69,   53,    53,    47,   47,      41,     41,    36,    36,     32,       32,      28,     28,    25,     25,   22,      22,    19,    19, 
17,       17,   15,   15,     13,   13,      11,     11,    10,    10,      9,          9,       8,       8,      7,      7,     6,       6,       5,      5, 
5,          5,      4,    4,       3,     3,       3,       3,      2,      2,       2,         2,       2,       2,       1,      1,     1,       1,      1,       1,1
};
//����PWM����100��Ԫ��
const u16 IndexWaveBreath_size = sizeof( indexWaveBreath ) / sizeof( u16 );

//code u16 indexWaveGradChange[100] = {//�����ͽ��乲��
//1,     21,  41,  61,  81,  101,  121,  141,  161,  181,  
//201,  221, 241, 261, 281,  301,  321,  341,  361,  381,
//401,  421, 441, 461, 481,  501,  521,  541,  561,  581,
//601,  621, 641, 661, 681,  701,  721,  741,  761,  781,
//801,  821, 841, 861, 881,  901,  921,  941,  961, 1024,
//1024, 961, 941, 921, 901,  881,  861,  841,  821,  801,
//781,  761, 741, 721, 701,  681,  661,  641,  621,  601,
//581,  561, 541, 521, 501,  481,  461,  441,  421,  401,
//381,  361, 341, 321, 301,  281,  261,  241,  221,  201,
//181,  161, 141, 121, 101,   81,   61,   41,   21,    1,
//};

code u16 indexWaveGradChange[202] = {//�����ͽ��乲��
1,1,        11,    21,   31,   41,   51,   61,    71,    81,   91,   101,  111,  121,  131,   141,  151,   161,  171,  181,   191,
201,   211, 221, 231,  241, 251,  261,  271,  281,  291,  301,  311,  321,  331,   341,  351,   361,  371,  381,   391,
401,   411, 421, 431,  441, 451,  461,  471,  481,  491,  501,  511,  521,  531,   541,  551,   561,  571,  581,   591,
601,   611, 621, 631,  641, 651,  661,  671,  681,  691,  701,  711,  721,  731,   741,  751,   761,  771,  781,   791,
801,   811, 821, 831,  841, 851,  861,  871,  881,  891,  901,  911,  921,  931,   941,  951,   961,  971,  981, 1024,
1024, 981, 971, 961,  951, 941,  931,  921,  911,  901,  891,  881,  871,  861,   851,  841,   831,  821,  811,   801,
791,   781, 771, 761,  751, 741,  731,  721,  711,  701,  691,  681,  671,  661,   651,  641,   631,  621,  611,   601,
591,   581, 571, 561,  551, 541,  531,  521,  511,  501,  491,  481,  471,  461,   451,  441,   431,  421,  411,   401,
391,   381, 371, 361,  351, 341,  331,  321,  311,  301,  291,  281,  271,  261,   251,  241,   231,  221,  211,   201,
191,   181, 171, 161,  151, 141,  131,  121,  111,  101,   91,     81,   71,    61,     51,    41,     31,    21,   11,       1,1
};
//����PWM����200��Ԫ��
const u16 IndexWaveGradChange_size = sizeof( indexWaveGradChange ) / sizeof( u16 );

//�����ƿ���ȫ�ֱ���
LED_BreathTypeDef LED_BreathxxArr[8] = {0};    //PWM00~PWM07, PWM10~PWM17, PWM20~PWM27


void PWMDuty(u8 _PWMxx, u16 _duty)//_duty���½���
{
    switch( _PWMxx )
    {
        case 1: 
            PWMA_Duty.PWM1_Duty = _duty;
        break;
        case 2: 
            PWMA_Duty.PWM2_Duty = _duty;
        break;
        case 3: 
            PWMA_Duty.PWM3_Duty = _duty;
        break;
        case 4: 
            PWMA_Duty.PWM4_Duty = _duty;
        break;
        case 5: 
            PWMB_Duty.PWM5_Duty = _duty;
        break;
        case 6: 
            PWMB_Duty.PWM6_Duty = _duty;
        break;
        case 7: 
            PWMB_Duty.PWM7_Duty = _duty;
        break;
        case 8: 
            PWMB_Duty.PWM8_Duty = _duty;
        break;
    }
	UpdatePwm(PWMA, &PWMA_Duty);
    UpdatePwm(PWMB, &PWMB_Duty);
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathGPIOConfig
*	����˵��: led�����ƶ˿�GPIO���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathGPIOConfig(u8 _PWMxx)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    switch( _PWMxx )
    {
        case 1: 
            GPIO_InitStructure.Pin  = 0;		//ָ��Ҫ��ʼ����IO,P60
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 2: 
            GPIO_InitStructure.Pin  = 2;		//ָ��Ҫ��ʼ����IO,P62
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 3: 
            GPIO_InitStructure.Pin  = 4;		//ָ��Ҫ��ʼ����IO,P64
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 4: 
            GPIO_InitStructure.Pin  = 6;		//ָ��Ҫ��ʼ����IO,P66
            GPIO_Inilize(GPIO_P6,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 5: 
            GPIO_InitStructure.Pin  = 4;		//ָ��Ҫ��ʼ����IO,P74
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 6: 
            GPIO_InitStructure.Pin  = 5;		//ָ��Ҫ��ʼ����IO,P75
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 7: 
            GPIO_InitStructure.Pin  = 6;		//ָ��Ҫ��ʼ����IO,P76
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
        case 8: 
            GPIO_InitStructure.Pin  = 7;		//ָ��Ҫ��ʼ����IO,P77
            GPIO_Inilize(GPIO_P7,&GPIO_InitStructure);	//��ʼ��IO��
        break;
    }
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathPWM15Config_PWMxx
*	����˵��: led�����ƶ˿�PWM15���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathPWM15Config(void)
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
/*
*********************************************************************************************************
*	�� �� ��: LED_breathTIMER4Config
*	����˵��: led�����ƶ˿�TIMER4���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathTIMER4Config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����
    TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;	            //ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;					//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;	//TIM���� 
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer4,&TIM_InitStructure);					//��ʼ��Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathInit
*	����˵��: led�����Ƴ�ʼ������
*	��    ��: _PWMxx ���������Žṹ��ָ��,�̶�ȡֵ��Χ�� �� PWM00~PWM07, PWM10~PWM17, PWM20~PWM27 ��
*             _breath_state ���ú����ĵ�״̬Ϊ �ߵ�ƽ���͵�ƽ������1~99������ �����䣬Ƶ�����̶�ȡֵ��Χ���� HIGH �� LOW ��1~99 �� BREATH �� GRADCHANGE_ONCE��GRADCHANGE_CYCLE �� FLASH ��
*             _periodBreathFlash1_cntCmp �������ã�������Ƶ�����ڼ����Ƚ�ֵ,���ƺ�������,����ȡֵ�� �� 100~5000  ms ��
*             _periodGradChangeFlash2_cntCmp  �������ã������Ƶ�����ڼ����Ƚ�ֵ,���ƽ������,����ȡֵ�� �� 100~5000  ms ��
*             _waveBreathChangeFlash_low  �������ã�����PWM��С���ȣ�0~100��������PWM��ʼ���ȣ�0~100����Ƶ��PWM��С���ȣ�0~100��
*             _waveBreathChangeFlash_high  �������ã�����PWM������ȣ�0~100��������PWM�������ȣ�0~100����Ƶ��PWM������ȣ�0~100��
*             _waveBreathChangeFlash_start ����PWM��ǰ���ȣ�0~100��
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathInit( u8 _PWMxx, u8 _breath_state, u8 _light, u16 _periodBreathFlash1_cntCmp, u16 _periodChangeFlash2_cntCmp, u8 _waveBreathChangeFlash_low, u8 _waveBreathChangeFlash_high, u8 _waveBreathChangeFlash_start )
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx-1];
    
    _LED_Breathxx->periodBreath_cnt = 0;             //���ú������ڼ�����־
    _LED_Breathxx->periodGradChange_cnt = 0;    //���ý������ڼ�����־
    _LED_Breathxx->periodFlash_cnt = 0;               //����Ƶ�����ڼ�����־
    _LED_Breathxx->waveBreath_index = _waveBreathChangeFlash_start;           //���ú���PWM��ָ��
    _LED_Breathxx->waveChangeFlash_index = _waveBreathChangeFlash_start; //���ý���Ƶ��PWM��ָ��
    if( _breath_state == GRADCHANGE_ONCE || _breath_state == GRADCHANGE_CYCLE || _breath_state == FLASH )
    {
        _LED_Breathxx->waveChangeFlash_index = _waveBreathChangeFlash_low;
    }
 
    LED_breathGPIOConfig(_PWMxx);                    //led�����ƶ˿�GPIO���ú���
    LED_breathPWM15Config();                //led�����ƶ˿�PWM15���ú���
    LED_breathTIMER4Config();                             //led�����ƶ˿�TIMER4���ú���
    LED_breathSetPeriod(_PWMxx, _breath_state, _periodBreathFlash1_cntCmp, _periodChangeFlash2_cntCmp, _waveBreathChangeFlash_low, _waveBreathChangeFlash_high); //�������ڼ����Ƚ�ֵ
    LED_breathSetState(_PWMxx, _breath_state, _light);   //����״̬
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathSetState
*	����˵��: led��������״̬����
*	��    ��: _PWMxx  ���������Žṹ��ָ��,ȡֵ��  PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*             _breath_state  ���ú����ĵ�״̬Ϊ �ߵ�ƽ���͵�ƽ������0~100������ �����䣬Ƶ����ȡֵ���� HIGH �� LOW ��0~100 �� BREATH �� GRADCHANGE_ONCE�� GRADCHANGE_CYCLE �� FLASH ��
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathSetState(u8 _PWMxx, u8 _breath_state, u8 _light)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx-1];
    
    _LED_Breathxx->periodBreath_cnt = 0;             //���ú������ڼ�����־
    _LED_Breathxx->periodGradChange_cnt = 0;    //���ý������ڼ�����־
    _LED_Breathxx->periodFlash_cnt = 0;               //����Ƶ�����ڼ�����־
    
    if( _breath_state == OPEN || _breath_state == CLOSE || _breath_state == LIGHT )
    {
        _LED_Breathxx->breath_enable = DISABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = DISABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
        if( _breath_state == OPEN )
        {
            _LED_Breathxx->light = 100;       
        }
        else if ( _breath_state == CLOSE )
        {
            _LED_Breathxx->light = 0;
        }
        else if ( _breath_state == LIGHT )
        {
            _LED_Breathxx->light = _light;
        } 
    }
    else if( _breath_state == BREATH )
    {
        _LED_Breathxx->breath_enable = ENABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = DISABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    }
    else if( _breath_state == GRADCHANGE_ONCE )
    {
        _LED_Breathxx->breath_enable = DISABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = ENABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_cycle = DISABLE;//����ѭ������Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    }
    else if( _breath_state == GRADCHANGE_CYCLE )
    {
        _LED_Breathxx->breath_enable = DISABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = ENABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_cycle = ENABLE;//����ѭ������Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    }
    else if( _breath_state == FLASH )
    {
        _LED_Breathxx->breath_enable = DISABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = DISABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = ENABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    }
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathSetPeriod
*	����˵��: led�����������ں���
*	��    ��: _PWMxx,���������Žṹ��ָ��,ȡֵ�� PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*             _periodBreathFlash1_cntCmp �������ã�������Ƶ�����ڼ����Ƚ�ֵ,���ƺ�������,����ȡֵ�� �� 100~5000  ms ��
*             _periodGradChangeFlash2_cntCmp  �������ã������Ƶ�����ڼ����Ƚ�ֵ,���ƽ������,����ȡֵ�� �� 100~5000  ms ��
*             _waveBreathChangeFlash_low  �������ã�����PWM��С���ȣ�0~100��������PWM��ʼ���ȣ�0~100����Ƶ��PWM��С���ȣ�0~100��
*             _waveBreathChangeFlash_high  �������ã�����PWM������ȣ�0~100��������PWM�������ȣ�0~100����Ƶ��PWM������ȣ�0~100��
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathSetPeriod(u8 _PWMxx, u8 _breath_state, u16 _periodBreathFlash1_cntCmp, u16 _periodChangeFlash2_cntCmp, u8 _waveBreathChangeFlash_low, u8 _waveBreathChangeFlash_high)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx-1];
    if( _waveBreathChangeFlash_low > _waveBreathChangeFlash_high )//�������Ƚ��͵����
    {
        if( _waveBreathChangeFlash_low != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_low = ( IndexWaveGradChange_size - 1 ) - _waveBreathChangeFlash_low;
        }
        
        if( _waveBreathChangeFlash_high != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_high = ( IndexWaveGradChange_size - 1 ) - _waveBreathChangeFlash_high;
        }
    }
    else
    {
        if( _waveBreathChangeFlash_low != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_low = _waveBreathChangeFlash_low;
        }
        
        if( _waveBreathChangeFlash_high != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_high = _waveBreathChangeFlash_high;
        }
    }

    if( _breath_state == FLASH )//����Ƶ�����ڼ����Ƚ�ֵ
    {
        if( _periodBreathFlash1_cntCmp != DEFAULT ) 
        {
            _LED_Breathxx->periodBreathFlash1_cntCmp = _periodBreathFlash1_cntCmp; 
        } 
        if( _periodChangeFlash2_cntCmp != DEFAULT ) 
        {
            _LED_Breathxx->periodChangeFlash2_cntCmp = _periodChangeFlash2_cntCmp; 
        }
    }
    else
    {
        if( _periodBreathFlash1_cntCmp != DEFAULT ) //���ú������ڼ����Ƚ�ֵ
        {
            if(_periodBreathFlash1_cntCmp <= 100)
            {
                _periodBreathFlash1_cntCmp = 100;
            }
            _LED_Breathxx->periodBreathFlash1_cntCmp = _periodBreathFlash1_cntCmp / ( (_LED_Breathxx->waveBreathChangeFlash_high - _LED_Breathxx->waveBreathChangeFlash_low + 1) * 2 );      
        }
        
        if( _periodChangeFlash2_cntCmp != DEFAULT ) //���ý������ڼ����Ƚ�ֵ
        {
            if(_periodChangeFlash2_cntCmp <= 100)
            {
                _periodChangeFlash2_cntCmp = 100;
            }
            _LED_Breathxx->periodChangeFlash2_cntCmp = _periodChangeFlash2_cntCmp / ( _LED_Breathxx->waveBreathChangeFlash_high - _LED_Breathxx->waveBreathChangeFlash_low + 1 );//�������������Դ�ڲ�������, ������û����һ�����ڵ���������� (end - start) ms
        }
    }
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathTIMER4IntCallback0x
*	����˵��: led�����ж�4�ص�����
*	��    ��: _PWMxx,���������Žṹ��ָ��,ȡֵ�� PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathTIMER4IntCallback0x( u8 _PWMxx )
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx-1];
    if( _LED_Breathxx->breath_enable == ENABLE )//���ƺ���
    {
        _LED_Breathxx->periodBreath_cnt++;
//        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
        if( _LED_Breathxx->waveBreath_index == 0 || _LED_Breathxx->waveBreath_index == IndexWaveBreath_size - 1 )//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
        {
//            PWM15Duty(_PWMxx, 0x401, 0x0);	    //����ߵ�ƽ
            PWMDuty(_PWMxx, 1024);
        }
        else
        {
//            PWM15Duty(_PWMxx,0,indexWaveBreath[_LED_Breathxx->waveBreath_index]);
            PWMDuty(_PWMxx, 1024 - indexWaveBreath[_LED_Breathxx->waveBreath_index]);
        }
        //ÿ��PWM���е�ÿ��Ԫ��ʹ�� period_cntCmp ��
        if(_LED_Breathxx->periodBreath_cnt > _LED_Breathxx->periodBreathFlash1_cntCmp)				 				
        {		
            _LED_Breathxx->waveBreath_index++;												//��־PWM��ָ����һ��Ԫ��
            if( _LED_Breathxx->waveBreath_index ==  _LED_Breathxx->waveBreathChangeFlash_high + 1)//��PWM���Ѵﵽ�������������
            {
                _LED_Breathxx->waveBreath_index = ( IndexWaveBreath_size - 1 ) - _LED_Breathxx->waveBreathChangeFlash_high;//����ָ��PWM���½����������				
            }
            if( _LED_Breathxx->waveBreath_index == ( IndexWaveBreath_size - 1 ) - _LED_Breathxx->waveBreathChangeFlash_low + 1)//��PWM���Ѵﵽ�½����������
            {
                _LED_Breathxx->waveBreath_index = _LED_Breathxx->waveBreathChangeFlash_low;//����ָ��PWM���������������					
            }
            _LED_Breathxx->periodBreath_cnt=0;											//���ú����ͽ������ڼ�����־
        }   
    }
    else if( _LED_Breathxx->gradChange_enable == ENABLE )//���ƽ���
    {
        _LED_Breathxx->periodGradChange_cnt++;
//        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
        if( _LED_Breathxx->waveChangeFlash_index == 0 || _LED_Breathxx->waveChangeFlash_index == IndexWaveGradChange_size - 1 )//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
        {
//            PWM15Duty(_PWMxx, 0x401, 0x0);	    //����ߵ�ƽ
            PWMDuty(_PWMxx, 1024);
        }
        else
        {
//            PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);	
            PWMDuty(_PWMxx, 1024 - indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
        }
        //ÿ��PWM���е�ÿ��Ԫ��ʹ�� period_cntCmp ��
        if(_LED_Breathxx->periodGradChange_cnt > _LED_Breathxx->periodChangeFlash2_cntCmp)				 				
        {				
            _LED_Breathxx->waveChangeFlash_index++;												//��־PWM��ָ����һ��Ԫ��
            //��PWM���ѵ����β������ָ���ͷ
            if( _LED_Breathxx->waveChangeFlash_index > _LED_Breathxx->waveBreathChangeFlash_high )			
            {
                if( _LED_Breathxx->gradChange_cycle == ENABLE )//ѭ������
                {
                    _LED_Breathxx->waveChangeFlash_index = _LED_Breathxx->waveBreathChangeFlash_low;//��ͷ��ʼ����
                }	
                else if( _LED_Breathxx->gradChange_cycle == DISABLE )//���ν���
                {
                    _LED_Breathxx->gradChange_enable = DISABLE;//�رս���
                    _LED_Breathxx->light = 100;       //����ߵ�ƽ���ص�
                }
            }
            _LED_Breathxx->periodGradChange_cnt=0;											//���ú����ͽ������ڼ�����־
        }   
    }
    else if( _LED_Breathxx->flash_enable == ENABLE )//����Ƶ��
    {
        _LED_Breathxx->periodFlash_cnt++;
        if( _LED_Breathxx->waveChangeFlash_index == _LED_Breathxx->waveBreathChangeFlash_low)
        {
//            PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
            if( _LED_Breathxx->waveChangeFlash_index == 0 || _LED_Breathxx->waveChangeFlash_index == IndexWaveGradChange_size - 1 )//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
            {
//                PWM15Duty(_PWMxx, 0x401, 0x0);	    //����ߵ�ƽ
                PWMDuty(_PWMxx, 1024);
            }
            else
            {
//                PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
                PWMDuty(_PWMxx, 1024 - indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
            }
            if(_LED_Breathxx->periodFlash_cnt >= _LED_Breathxx->periodBreathFlash1_cntCmp) //Ƶ���������ڵ�����תƵ����ƽ
            {
                _LED_Breathxx->waveChangeFlash_index = _LED_Breathxx->waveBreathChangeFlash_high;
            }
        }
        else if( _LED_Breathxx->waveChangeFlash_index == _LED_Breathxx->waveBreathChangeFlash_high)
        {
//            PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
            if( _LED_Breathxx->waveChangeFlash_index == 0 || _LED_Breathxx->waveChangeFlash_index == IndexWaveGradChange_size - 1 )//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
            {
//                PWM15Duty(_PWMxx, 0x401, 0x0);	    //����ߵ�ƽ
                PWMDuty(_PWMxx, 1024);
            }
            else
            {
//                PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
                PWMDuty(_PWMxx, 1024 - indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
            }
            if(_LED_Breathxx->periodFlash_cnt >= _LED_Breathxx->periodChangeFlash2_cntCmp) //Ƶ���������ڵ�����תƵ����ƽ
            {
                _LED_Breathxx->waveChangeFlash_index = _LED_Breathxx->waveBreathChangeFlash_low;
                _LED_Breathxx->periodFlash_cnt = 0;       //����Ƶ�����ڼ�����־
            }
        }
    }
    else//�������Ÿߵ͵�ƽ
    {
//        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	  //PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ

        if(_LED_Breathxx->light == 0)
        {
//            PWM15Duty(_PWMxx, 0x0, 0x401);	    //PWM����, ռ�ձ�����.
            PWMDuty(_PWMxx, 1024);//�͵�ƽ
        }
        else if(_LED_Breathxx->light == 100)
        {
//            PWM15Duty(_PWMxx, 0x401, 0x0);	    //PWM����, ռ�ձ�����.
            PWMDuty(_PWMxx, 0);//�ߵ�ƽ
        }
        else if(_LED_Breathxx->light >= 1 || _LED_Breathxx->light <= 99)
        {
//            PWM15Duty( _PWMxx, 0x0, _LED_Breathxx->pin_level  );	    //PWM����0x400 == 1024, ռ�ձ�����.
            PWMDuty(_PWMxx, 1024 - indexWaveGradChange[_LED_Breathxx->light]);
        }
    }
}

#endif





#if LED_FLASH       //6*8 = 48 �ֽ�

//Ƶ���ƿ���ȫ�ֱ���
LED_FlashTypeDef LED_Flash20;//P20�����Ƶ����
LED_FlashTypeDef LED_Flash21;//P21�����Ƶ����
LED_FlashTypeDef LED_Flash22;//P22�����Ƶ����
LED_FlashTypeDef LED_Flash23;//P23�����Ƶ����
LED_FlashTypeDef LED_Flash24;//P24�����Ƶ����
LED_FlashTypeDef LED_Flash25;//P25�����Ƶ����
LED_FlashTypeDef LED_Flash26;//P26�����Ƶ����
LED_FlashTypeDef LED_Flash27;//P27�����Ƶ����
/*
*********************************************************************************************************
*	�� �� ��: LED_flashGPIOConfig
*	����˵��: ledƵ���ƶ˿�GPIO���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_flashGPIOConfig(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//��ʼ��
}
/*
*********************************************************************************************************
*	�� �� ��: LED_flashTIMER3Config
*	����˵��: ledƵ���ƶ˿�TIMER3���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_flashTIMER3Config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����
    TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;	            //ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;					//�Ƿ������������, ENABLE��DISABLE,/* ENABLEʱ,P0.5��������ⲿ����	*/
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;	//TIM���� 
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer3,&TIM_InitStructure);					//��ʼ��Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
}
/*
*********************************************************************************************************
*	�� �� ��: LED_flashInit
*	����˵��: ledƵ���Ƴ�ʼ������
*	��    ��: _LED_Flash2x,Ƶ�������Žṹ��ָ��,ȡֵ��  &LED_Flash20, &LED_Flash21, &LED_Flash22, &LED_Flash23, &LED_Flash24, &LED_Flash25, &LED_Flash26, &LED_Flash27
*             _period_cntCmp,Ƶ�������ڼ����Ƚ�ֵ,����Ƶ������,��λms,����ȡֵ�� ��Ƶ�� 30~100, ��Ƶ�� 101~200
              _flash_enable,Ƶ���Ŀ���,ȡֵ�� ENABLE, DISABLE
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_flashInit(LED_FlashTypeDef * _LED_Flash2x, u16 _period_cntCmp, u8 _flash_enable)
{
    LED_flashGPIOConfig();
    LED_flashTIMER3Config();
    _LED_Flash2x->period_cnt        = 0;                    //�̶���0��ʼ����
    _LED_Flash2x->period_cntCmp     = _period_cntCmp / 2;   //����Ƶ�����ڼ����Ƚ�ֵ
    _LED_Flash2x->flash_enable      = _flash_enable;        //����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    _LED_Flash2x->pin_level         = HIGH;                 //Ĭ������ߵ�ƽ
}
/*
*********************************************************************************************************
*	�� �� ��: LED_flashSwitch
*	����˵��: ledƵ�����غ���
*	��    ��: _LED_Flash2x,Ƶ�������Žṹ��ָ��,ȡֵ��  &LED_Flash20, &LED_Flash21, &LED_Flash22, &LED_Flash23, &LED_Flash24, &LED_Flash25, &LED_Flash26, &LED_Flash27
*             _pin_level,���ر�Ƶ��ʱ�����ڿ����������״̬,ȡֵ�� �ߵ�ƽ HIGH, �͵�ƽ LOW  
*             _flash_enable,Ƶ���Ŀ���,ȡֵ�� ENABLE, DISABLE
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_flashSwitch(LED_FlashTypeDef * _LED_Flash2x, u8 _pin_level, u8 _flash_enable)
{
    _LED_Flash2x->flash_enable = _flash_enable; //����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    _LED_Flash2x->pin_level = _pin_level;       //���ر�Ƶ��ʱ�����ڿ����������״̬
}
/*
*********************************************************************************************************
*	�� �� ��: LED_flashTIMER3IntCallback
*	����˵��: ledƵ���жϻص�����
*	��    ��: void
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_flashTIMER3IntCallback(void)
{
    //Ƶ��P20�Ŀ���
    if( LED_Flash20.flash_enable == ENABLE )
    {
        LED_Flash20.period_cnt++;
        if(LED_Flash20.period_cnt >= LED_Flash20.period_cntCmp)
        {
            P20 = ~P20;//��תP20
            LED_Flash20.period_cnt=0;
        }
    }
    else
    {
        P20 = LED_Flash20.pin_level;//����P20��������ߵ�ƽ
    }
    //Ƶ��P21�Ŀ���
    if( LED_Flash21.flash_enable == ENABLE )
    {
        LED_Flash21.period_cnt++;
        if(LED_Flash21.period_cnt >= LED_Flash21.period_cntCmp)
        {
            P21 = ~P21;//��תP21
            LED_Flash21.period_cnt=0;
        }
    }
    else
    {
        P21 = LED_Flash21.pin_level;//����P21��������ߵ�ƽ
    }
        //Ƶ��P22�Ŀ���
    if( LED_Flash22.flash_enable == ENABLE )
    {
        LED_Flash22.period_cnt++;
        if(LED_Flash22.period_cnt >= LED_Flash22.period_cntCmp)
        {
            P22 = ~P22;//��תP22
            LED_Flash22.period_cnt=0;
        }
    }
    else
    {
        P22 = LED_Flash22.pin_level;//����P22��������ߵ�ƽ
    }
        //Ƶ��P23�Ŀ���
    if( LED_Flash23.flash_enable == ENABLE )
    {
        LED_Flash23.period_cnt++;
        if(LED_Flash23.period_cnt >= LED_Flash23.period_cntCmp)
        {
            P23 = ~P23;//��תP23
            LED_Flash23.period_cnt=0;
        }
    }
    else
    {
        P23 = LED_Flash23.pin_level;//����P23��������ߵ�ƽ
    }
    //Ƶ��P24�Ŀ���
    if( LED_Flash24.flash_enable == ENABLE )
    {
        LED_Flash24.period_cnt++;
        if(LED_Flash24.period_cnt >= LED_Flash24.period_cntCmp)
        {
            P24 = ~P24;//��תP24
            LED_Flash24.period_cnt=0;
        }
    }
    else
    {
        P24 = LED_Flash24.pin_level;//����P24��������ߵ�ƽ
    }
    //Ƶ��P25�Ŀ���
    if( LED_Flash25.flash_enable == ENABLE )
    {
        LED_Flash25.period_cnt++;
        if(LED_Flash25.period_cnt >= LED_Flash25.period_cntCmp)
        {
            P25 = ~P25;//��תP25
            LED_Flash25.period_cnt=0;
        }
    }
    else
    {
        P25 = LED_Flash25.pin_level;//����P25��������ߵ�ƽ
    }
    //Ƶ��P26�Ŀ���
    if( LED_Flash26.flash_enable == ENABLE )
    {
        LED_Flash26.period_cnt++;
        if(LED_Flash26.period_cnt >= LED_Flash26.period_cntCmp)
        {
            P26 = ~P26;//��תP26
            LED_Flash26.period_cnt=0;
        }
    }
    else
    {
        P26 = LED_Flash26.pin_level;//����P26��������ߵ�ƽ
    }
    //Ƶ��P27�Ŀ���
    if( LED_Flash27.flash_enable == ENABLE )
    {
        LED_Flash27.period_cnt++;
        if(LED_Flash27.period_cnt >= LED_Flash27.period_cntCmp)
        {
            P27 = ~P27;//��תP27
            LED_Flash27.period_cnt=0;
        }
    }
    else
    {
        P27 = LED_Flash27.pin_level;//����P27��������ߵ�ƽ
    }
}

#endif
