#include "bsp_led.h"
#include "main.h"


#if LED_BREATH  //100*2 + 100*2 + 2 + 24*22��528�� = 930 �ֽ�

/* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/
u16 indexWaveBreath[100] = {
1,   1,   1,   2,   2,    2,    3,    3,    4,    5,
5,   6,   7,   8,   9,    10,   11,   13,   15,   17, 
19,  22,  25,  28,  32,   36,   41,   47,   53,   69, 
79,  89,  116, 131, 149,  170,  193,  219,  250,  284,
323, 367, 417, 474, 539,  613,  697,  792,  901,  1024, 
1024,901, 792, 697, 613,  539,  474,  417,  367,  323,
284, 250, 219, 193, 170,  149,  131,  116,  89,   79, 
69,  53,  47,  41,  36,   32,   28,   25,   22,   19, 
17,  15,  13,  11,  10,   9,    8,    7,    6,    5, 
5,   4,   3,   3,   2,    2,    2,    1,    1,    1
};
u16 indexWaveGradChange[100] = {
1,     21,  41,  61,  81,  101,  121,  141,  161,  181,  
201,  221, 241, 261, 281,  301,  321,  341,  361,  381,
401,  421, 441, 461, 481,  501,  521,  541,  561,  581,
601,  621, 641, 661, 681,  701,  721,  741,  761,  781,
801,  821, 841, 861, 881,  901,  921,  941,  961, 1024,
1024, 961, 941, 921, 901,  881,  861,  841,  821,  801,
781,  761, 741, 721, 701,  681,  661,  641,  621,  601,
581,  561, 541, 521, 501,  481,  461,  441,  421,  401,
381,  361, 341, 321, 301,  281,  261,  241,  221,  201,
181,  161, 141, 121, 101,   81,   61,   41,   21,    1,
};
//����PWM���ж��ٸ�Ԫ��,100��Ԫ��
const u16 POINT_NUM = sizeof(indexWaveBreath)/sizeof(indexWaveBreath[0]);
//�����ƿ���ȫ�ֱ���
LED_BreathTypeDef LED_BreathxxArr[24] = {0};    //PWM00~PWM07, PWM10~PWM17, PWM20~PWM27

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
	GPIO_InitStructure.Pin  = 0x01 << ( _PWMxx % 8 );		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(_PWMxx/8,&GPIO_InitStructure);	//��ʼ��IO��
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathPWM15Config
*	����˵��: led�����ƶ˿�PWM15���ú���
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathPWM15Config(u8 _PWMxx)
{
    PWM15_InitTypeDef		PWM15_InitStructure;
	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWMʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 0x400;		//PWM���� PWM_Period_100us,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWMn_CLK_SYS;		//ʱ��Դѡ��,  PWMn_CLK_SYS, PWMn_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//ϵͳʱ�ӷ�Ƶ����(PS+1��Ƶ),  0~15
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//������ʹ��,  ENABLE, DISABLE
	PWM15_Init(_PWMxx/8,&PWM15_InitStructure);  //PWM��ʼ�������޸�bug��
    PWMChannelCtrl(_PWMxx,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
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
*             _breath_state ���ú����ĵ�״̬Ϊ �ߵ�ƽ���͵�ƽ������1~99������ �����䣬Ƶ�����̶�ȡֵ��Χ���� HIGH �� LOW ��1~99 �� BREATH �� GRADCHANGE �� FLASH ��
*             _periodBreath_cntCmp �������ڼ����Ƚ�ֵ,���ƺ�������,����ȡֵ�� �� 100~5000  ms ��
*             _periodGradChange_cntCmp  �������ڼ����Ƚ�ֵ,���ƽ������,����ȡֵ�� �� 100~5000  ms ��
*             _periodFlash_cntCmp  Ƶ�����ڼ����Ƚ�ֵ������Ƶ������������ȡֵ���� 30~100 ms ��
*             _waveGradChange_start  ����PWM��ʼ���ȣ��̶�ȡֵ��Χ ��1~100��
*             _waveGradChange_end  ����PWM�������ȣ��̶�ȡֵ��Χ��1~100��
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathInit( u8 _PWMxx, u8 _breath_state, u16 _periodBreath_cntCmp, u16 _periodGradChange_cntCmp, u16 _periodFlash_cntCmp, u8 _waveGradChange_start, u8 _waveGradChange_end)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    
    _LED_Breathxx->periodBreath_cnt = 0;             //���ú������ڼ�����־
    _LED_Breathxx->periodGradChange_cnt = 0;    //���ý������ڼ�����־
    _LED_Breathxx->periodFlash_cnt = 0;               //����Ƶ�����ڼ�����־
    _LED_Breathxx->waveBreath_index = 0;           //���ú���PWM��ָ��
    _LED_Breathxx->waveGradChange_index = _waveGradChange_start - 1;//���ý���PWM��ָ��    

    LED_breathGPIOConfig(_PWMxx);                    //led�����ƶ˿�GPIO���ú���
    LED_breathPWM15Config(_PWMxx);                //led�����ƶ˿�PWM15���ú���
    LED_breathTIMER4Config();                             //led�����ƶ˿�TIMER4���ú���
    LED_breathSetPeriod(_PWMxx, _periodBreath_cntCmp, _periodGradChange_cntCmp, _periodFlash_cntCmp, _waveGradChange_start, _waveGradChange_end); //�������ڼ����Ƚ�ֵ
    LED_breathSetState(_PWMxx, _breath_state);   //����״̬
}
/*
*********************************************************************************************************
*	�� �� ��: LED_breathSetState
*	����˵��: led��������״̬����
*	��    ��: _PWMxx  ���������Žṹ��ָ��,ȡֵ��  PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*             _breath_state  ���ú����ĵ�״̬Ϊ �ߵ�ƽ���͵�ƽ������1~99������ �����䣬Ƶ����ȡֵ���� HIGH �� LOW ��1~99 �� BREATH �� GRADCHANGE �� FLASH ��
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathSetState(u8 _PWMxx, u8 _breath_state)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    
    _LED_Breathxx->periodBreath_cnt = 0;             //���ú������ڼ�����־
    _LED_Breathxx->periodGradChange_cnt = 0;    //���ý������ڼ�����־
    _LED_Breathxx->periodFlash_cnt = 0;               //����Ƶ�����ڼ�����־
    _LED_Breathxx->waveBreath_index = 0;           //���ú���PWM��ָ��
    _LED_Breathxx->waveGradChange_index = _LED_Breathxx->waveGradChange_start;//���ý���PWM��ָ��
    
    if( _breath_state >= LOW && _breath_state <= HIGH )
    {
        _LED_Breathxx->breath_enable = DISABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = DISABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->pin_level = _breath_state;       //���رպ���ʱ�����ڿ����������״̬
    }
    else if( _breath_state == BREATH )
    {
        _LED_Breathxx->breath_enable = ENABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = DISABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    }
    else if( _breath_state == GRADCHANGE )
    {
        _LED_Breathxx->breath_enable = DISABLE;//���ú����Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->gradChange_enable = ENABLE;//���ý���Ŀ��أ� ENABLE ����DISABLE ��
        _LED_Breathxx->flash_enable = DISABLE;//����Ƶ���Ŀ��أ� ENABLE ����DISABLE ��
    }
    else if( _breath_state == FLASH )
    {
        _LED_Breathxx->flash_level = LOW;       //�������ڷ�תƵ����ƽ�ĳ�ʼֵ
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
*             _periodBreath_cntCmp �������ڼ����Ƚ�ֵ,���ƺ�������,����ȡֵ�� �� 100~5000  ms ��
*             _periodGradChange_cntCmp  �������ڼ����Ƚ�ֵ,���ƽ������,����ȡֵ�� �� 100~5000  ms ��
*             _periodFlash_cntCmp  Ƶ�����ڼ����Ƚ�ֵ������Ƶ������������ȡֵ���� 30~100 ms ��
*             _waveGradChange_start  ����PWM��ʼ���ȣ��̶�ȡֵ��Χ ��1~100��
*             _waveGradChange_end  ����PWM�������ȣ��̶�ȡֵ��Χ��1~100��
*	�� �� ֵ: void
*********************************************************************************************************
*/
void LED_breathSetPeriod(u8 _PWMxx, u16 _periodBreath_cntCmp, u16 _periodGradChange_cntCmp, u16 _periodFlash_cntCmp, u8 _waveGradChange_start, u8 _waveGradChange_end)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    
    if(_waveGradChange_start != DEFAULT)
    {
        _LED_Breathxx->waveGradChange_start = _waveGradChange_start - 1;
    }
    
    if(_waveGradChange_end != DEFAULT)
    {
        _LED_Breathxx->waveGradChange_end = _waveGradChange_end;
    }
    
    if( _periodBreath_cntCmp != DEFAULT ) //���ú������ڼ����Ƚ�ֵ
    {
        if(_periodBreath_cntCmp <= 100)
        {
            _periodBreath_cntCmp = 100;
        }
        _LED_Breathxx->periodBreath_cntCmp = _periodBreath_cntCmp / 100;      
    }
    
    if( _periodGradChange_cntCmp != DEFAULT ) //���ý������ڼ����Ƚ�ֵ
    {
        if(_periodGradChange_cntCmp <= 100)
        {
            _periodGradChange_cntCmp = 100;
        }
        _LED_Breathxx->periodGradChange_cntCmp = _periodGradChange_cntCmp / ( _LED_Breathxx->waveGradChange_end - _LED_Breathxx->waveGradChange_start );      
    }

    if( _periodFlash_cntCmp != DEFAULT ) //����Ƶ�����ڼ����Ƚ�ֵ
    {
        if( _periodFlash_cntCmp <= 30 )
        {
            _periodFlash_cntCmp = 30;            
        }
        _LED_Breathxx->periodFlash_cntCmp = _periodFlash_cntCmp / 2; 
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
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    if( _LED_Breathxx->breath_enable == ENABLE )//���ƺ���
    {
        _LED_Breathxx->periodBreath_cnt++;
        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
        PWM15Duty(_PWMxx,0,indexWaveBreath[_LED_Breathxx->waveBreath_index]);	    //����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
        //ÿ��PWM���е�ÿ��Ԫ��ʹ�� period_cntCmp ��
        if(_LED_Breathxx->periodBreath_cnt >= _LED_Breathxx->periodBreath_cntCmp)				 				
        {				
            _LED_Breathxx->waveBreath_index++;												//��־PWM��ָ����һ��Ԫ��
            //��PWM���ѵ����β������ָ���ͷ
            if( _LED_Breathxx->waveBreath_index >=  POINT_NUM)			
            {
                _LED_Breathxx->waveBreath_index=0;								
            }
            _LED_Breathxx->periodBreath_cnt=0;											//���ú����ͽ������ڼ�����־
        }   
    }
    else if( _LED_Breathxx->gradChange_enable == ENABLE )//���ƽ���
    {
        _LED_Breathxx->periodGradChange_cnt++;
        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
        PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveGradChange_index]);	//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
        //ÿ��PWM���е�ÿ��Ԫ��ʹ�� period_cntCmp ��
        if(_LED_Breathxx->periodGradChange_cnt >= _LED_Breathxx->periodGradChange_cntCmp)				 				
        {				
            _LED_Breathxx->waveGradChange_index++;												//��־PWM��ָ����һ��Ԫ��
            //��PWM���ѵ����β������ָ���ͷ
            if( _LED_Breathxx->waveGradChange_index >=  _LED_Breathxx->waveGradChange_end )			
            {
                _LED_Breathxx->waveGradChange_index = _LED_Breathxx->waveGradChange_start;								
            }
            _LED_Breathxx->periodGradChange_cnt=0;											//���ú����ͽ������ڼ�����־
        }   
    }
    else if( _LED_Breathxx->flash_enable == ENABLE )//����Ƶ��
    {
        _LED_Breathxx->periodFlash_cnt++;
        if(_LED_Breathxx->periodFlash_cnt >= _LED_Breathxx->periodFlash_cntCmp) //Ƶ���������ڵ�����תƵ����ƽ
        {   
            if( _LED_Breathxx->flash_level == LOW )
            {
                _LED_Breathxx->flash_level = HIGH;
                PWMLevelSet(_PWMxx,DISABLE,ENABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
            }
            else if( _LED_Breathxx->flash_level == HIGH)
            {
                _LED_Breathxx->flash_level = LOW;
                PWMLevelSet(_PWMxx,ENABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
            }
            _LED_Breathxx->periodFlash_cnt = 0;       //����Ƶ�����ڼ�����־
        }
    }
    else//�������Ÿߵ͵�ƽ
    {
        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	  //PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
        if(_LED_Breathxx->pin_level > LOW && _LED_Breathxx->pin_level < HIGH)
        {
            PWM15Duty( _PWMxx, 0x0, _LED_Breathxx->pin_level * 10 );	    //PWM����0x400 == 1024, ռ�ձ�����.
        }
        else if(_LED_Breathxx->pin_level == LOW)
        {
            PWM15Duty(_PWMxx, 0x0, 0x401);	    //PWM����, ռ�ձ�����.
        }
        else if(_LED_Breathxx->pin_level == HIGH)
        {
            PWM15Duty(_PWMxx, 0x401, 0x0);	    //PWM����, ռ�ձ�����.
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
