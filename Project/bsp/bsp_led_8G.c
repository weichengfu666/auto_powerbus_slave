#include "bsp_led.h"
#include "main.h"


#if LED_BREATH  //100*2 + 100*2 + 2 + 24*22（528） = 930 字节

/* LED亮度等级 PWM表,指数曲线 ，此表使用工程目录下的python脚本index_wave.py生成*/

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
//呼吸PWM表有100个元素
const u16 IndexWaveBreath_size = sizeof( indexWaveBreath ) / sizeof( u16 );

//code u16 indexWaveGradChange[100] = {//呼吸和渐变共用
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

code u16 indexWaveGradChange[202] = {//呼吸和渐变共用
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
//渐变PWM表有200个元素
const u16 IndexWaveGradChange_size = sizeof( indexWaveGradChange ) / sizeof( u16 );

//呼吸灯控制全局变量
LED_BreathTypeDef LED_BreathxxArr[8] = {0};    //PWM00~PWM07, PWM10~PWM17, PWM20~PWM27

/*
*********************************************************************************************************
*	函 数 名: LED_breathGPIOConfig
*	功能说明: led呼吸灯端口GPIO配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathGPIOConfig(u8 _PWMxx)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = 0x01 << ( _PWMxx % 8 );		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(_PWMxx/8,&GPIO_InitStructure);	//初始化IO口
}
/*
*********************************************************************************************************
*	函 数 名: LED_breathPWM15Config
*	功能说明: led呼吸灯端口PWM15配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathPWM15Config(u8 _PWMxx)
{
    PWM15_InitTypeDef		PWM15_InitStructure;
	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWM使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 0x400;		//PWM周期 PWM_Period_100us,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWMn_CLK_SYS;		//时钟源选择,  PWMn_CLK_SYS, PWMn_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//系统时钟分频参数(PS+1分频),  0~15
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//计数器使能,  ENABLE, DISABLE
	PWM15_Init(_PWMxx/8,&PWM15_InitStructure);  //PWM初始化（已修复bug）
    PWMLevelSet(_PWMxx,DISABLE,ENABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
    PWMChannelCtrl(_PWMxx,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
}
/*
*********************************************************************************************************
*	函 数 名: LED_breathTIMER4Config
*	功能说明: led呼吸灯端口TIMER4配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathTIMER4Config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//结构定义
    TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;	            //指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;					//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;	//TIM周期 
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer4,&TIM_InitStructure);					//初始化Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
}
/*
*********************************************************************************************************
*	函 数 名: LED_breathInit
*	功能说明: led呼吸灯初始化函数
*	形    参: _PWMxx 呼吸灯引脚结构体指针,固定取值范围： （ PWM00~PWM07, PWM10~PWM17, PWM20~PWM27 ）
*             _breath_state 设置呼吸的灯状态为 高电平，低电平，亮度1~99，呼吸 ，渐变，频闪，固定取值范围：（ HIGH ， LOW ，1~99 ， BREATH ， GRADCHANGE_ONCE，GRADCHANGE_CYCLE ， FLASH ）
*             _periodBreathFlash1_cntCmp 参数共用：呼吸和频闪周期计数比较值,控制呼吸快慢,建议取值： （ 100~5000  ms ）
*             _periodGradChangeFlash2_cntCmp  参数共用：渐变和频闪周期计数比较值,控制渐变快慢,建议取值： （ 100~5000  ms ）
*             _waveBreathChangeFlash_start  参数共用：呼吸PWM最小亮度（0~100），渐变PWM起始亮度（0~100），频闪PWM最小亮度（0~100）
*             _waveBreathChangeFlash_end  参数共用：呼吸PWM最大亮度（0~100），渐变PWM结束亮度（0~100），频闪PWM最大亮度（0~100）
*             _waveBreathChangeFlash_now 呼吸PWM当前亮度（0~100）
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathInit( u8 _PWMxx, u8 _breath_state, u16 _periodBreathFlash1_cntCmp, u16 _periodChangeFlash2_cntCmp, u8 _waveBreathChangeFlash_start, u8 _waveBreathChangeFlash_end, u8 _waveBreathChangeFlash_now )
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    
    _LED_Breathxx->periodBreath_cnt = 0;             //重置呼吸周期计数标志
    _LED_Breathxx->periodGradChange_cnt = 0;    //重置渐变周期计数标志
    _LED_Breathxx->periodFlash_cnt = 0;               //重置频闪周期计数标志
    _LED_Breathxx->waveBreath_index = _waveBreathChangeFlash_now;           //重置呼吸PWM表指针
    _LED_Breathxx->waveChangeFlash_index = _waveBreathChangeFlash_now; //重置渐变频闪PWM表指针
    if( _breath_state == GRADCHANGE_ONCE || _breath_state == GRADCHANGE_CYCLE || _breath_state == FLASH )
    {
        _LED_Breathxx->waveChangeFlash_index = _waveBreathChangeFlash_start;
    }
 
    LED_breathGPIOConfig(_PWMxx);                    //led呼吸灯端口GPIO配置函数
    LED_breathPWM15Config(_PWMxx);                //led呼吸灯端口PWM15配置函数
    LED_breathTIMER4Config();                             //led呼吸灯端口TIMER4配置函数
    LED_breathSetPeriod(_PWMxx, _breath_state, _periodBreathFlash1_cntCmp, _periodChangeFlash2_cntCmp, _waveBreathChangeFlash_start, _waveBreathChangeFlash_end); //设置周期计数比较值
    LED_breathSetState(_PWMxx, _breath_state);   //设置状态
}
/*
*********************************************************************************************************
*	函 数 名: LED_breathSetState
*	功能说明: led呼吸设置状态函数
*	形    参: _PWMxx  呼吸灯引脚结构体指针,取值：  PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*             _breath_state  设置呼吸的灯状态为 高电平，低电平，亮度0~100，呼吸 ，渐变，频闪，取值：（ HIGH ， LOW ，0~100 ， BREATH ， GRADCHANGE_ONCE， GRADCHANGE_CYCLE ， FLASH ）
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathSetState(u8 _PWMxx, u8 _breath_state)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    
    _LED_Breathxx->periodBreath_cnt = 0;             //重置呼吸周期计数标志
    _LED_Breathxx->periodGradChange_cnt = 0;    //重置渐变周期计数标志
    _LED_Breathxx->periodFlash_cnt = 0;               //重置频闪周期计数标志
    
    if( _breath_state >= LOW && _breath_state <= HIGH )
    {
        _LED_Breathxx->breath_enable = DISABLE;//设置呼吸的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_enable = DISABLE;//设置渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->flash_enable = DISABLE;//设置频闪的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->pin_level = _breath_state;       //当关闭呼吸时，用于控制输出引脚状态
    }
    else if( _breath_state == BREATH )
    {
        _LED_Breathxx->breath_enable = ENABLE;//设置呼吸的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_enable = DISABLE;//设置渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->flash_enable = DISABLE;//设置频闪的开关： ENABLE 开，DISABLE 关
    }
    else if( _breath_state == GRADCHANGE_ONCE )
    {
        _LED_Breathxx->breath_enable = DISABLE;//设置呼吸的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_enable = ENABLE;//设置渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_cycle = DISABLE;//设置循环渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->flash_enable = DISABLE;//设置频闪的开关： ENABLE 开，DISABLE 关
    }
    else if( _breath_state == GRADCHANGE_CYCLE )
    {
        _LED_Breathxx->breath_enable = DISABLE;//设置呼吸的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_enable = ENABLE;//设置渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_cycle = ENABLE;//设置循环渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->flash_enable = DISABLE;//设置频闪的开关： ENABLE 开，DISABLE 关
    }
    else if( _breath_state == FLASH )
    {
        _LED_Breathxx->breath_enable = DISABLE;//设置呼吸的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->gradChange_enable = DISABLE;//设置渐变的开关： ENABLE 开，DISABLE 关
        _LED_Breathxx->flash_enable = ENABLE;//设置频闪的开关： ENABLE 开，DISABLE 关
    }
}
/*
*********************************************************************************************************
*	函 数 名: LED_breathSetPeriod
*	功能说明: led呼吸设置周期函数
*	形    参: _PWMxx,呼吸灯引脚结构体指针,取值： PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*             _periodBreathFlash1_cntCmp 参数共用：呼吸和频闪周期计数比较值,控制呼吸快慢,建议取值： （ 100~5000  ms ）
*             _periodGradChangeFlash2_cntCmp  参数共用：渐变和频闪周期计数比较值,控制渐变快慢,建议取值： （ 100~5000  ms ）
*             _waveBreathChangeFlash_start  参数共用：呼吸PWM最小亮度（0~100），渐变PWM起始亮度（0~100），频闪PWM最小亮度（0~100）
*             _waveBreathChangeFlash_end  参数共用：呼吸PWM最大亮度（0~100），渐变PWM结束亮度（0~100），频闪PWM最大亮度（0~100）
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathSetPeriod(u8 _PWMxx, u8 _breath_state, u16 _periodBreathFlash1_cntCmp, u16 _periodChangeFlash2_cntCmp, u8 _waveBreathChangeFlash_start, u8 _waveBreathChangeFlash_end)
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    if( _waveBreathChangeFlash_start > _waveBreathChangeFlash_end )//渐变亮度降低的情况
    {
        if( _waveBreathChangeFlash_start != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_start = ( IndexWaveGradChange_size - 1 ) - _waveBreathChangeFlash_start;
        }
        
        if( _waveBreathChangeFlash_end != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_end = ( IndexWaveGradChange_size - 1 ) - _waveBreathChangeFlash_end;
        }
    }
    else
    {
        if( _waveBreathChangeFlash_start != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_start = _waveBreathChangeFlash_start;
        }
        
        if( _waveBreathChangeFlash_end != DEFAULT&&0x00FF )
        {
            _LED_Breathxx->waveBreathChangeFlash_end = _waveBreathChangeFlash_end;
        }
    }

    if( _breath_state == FLASH )//设置频闪周期计数比较值
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
        if( _periodBreathFlash1_cntCmp != DEFAULT ) //设置呼吸周期计数比较值
        {
            if(_periodBreathFlash1_cntCmp <= 100)
            {
                _periodBreathFlash1_cntCmp = 100;
            }
            _LED_Breathxx->periodBreathFlash1_cntCmp = _periodBreathFlash1_cntCmp / ( (_LED_Breathxx->waveBreathChangeFlash_end - _LED_Breathxx->waveBreathChangeFlash_start + 1) * 2 );      
        }
        
        if( _periodChangeFlash2_cntCmp != DEFAULT ) //设置渐变周期计数比较值
        {
            if(_periodChangeFlash2_cntCmp <= 100)
            {
                _periodChangeFlash2_cntCmp = 100;
            }
            _LED_Breathxx->periodChangeFlash2_cntCmp = _periodChangeFlash2_cntCmp / ( _LED_Breathxx->waveBreathChangeFlash_end - _LED_Breathxx->waveBreathChangeFlash_start + 1 );//渐变周期误差来源于不能整除, 整除则没有误差，一个周期的最大误差不超过 (end - start) ms
        }
    }
}
/*
*********************************************************************************************************
*	函 数 名: LED_breathTIMER4IntCallback0x
*	功能说明: led呼吸中断4回调函数
*	形    参: _PWMxx,呼吸灯引脚结构体指针,取值： PWM00~PWM07, PWM10~PWM17, PWM20~PWM27
*	返 回 值: void
*********************************************************************************************************
*/
void LED_breathTIMER4IntCallback0x( u8 _PWMxx )
{
    LED_BreathTypeDef* _LED_Breathxx = &LED_BreathxxArr[_PWMxx];
    if( _LED_Breathxx->breath_enable == ENABLE )//控制呼吸
    {
        _LED_Breathxx->periodBreath_cnt++;
        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
        if( _LED_Breathxx->waveBreath_index == 0 || _LED_Breathxx->waveBreath_index == IndexWaveBreath_size - 1 )//根据PWM表修改定时器的比较寄存器值
        {
            PWM15Duty(_PWMxx, 0x401, 0x0);	    //输出高电平
        }
        else
        {
            PWM15Duty(_PWMxx,0,indexWaveBreath[_LED_Breathxx->waveBreath_index]);
        }
        //每个PWM表中的每个元素使用 period_cntCmp 次
        if(_LED_Breathxx->periodBreath_cnt > _LED_Breathxx->periodBreathFlash1_cntCmp)				 				
        {		
            _LED_Breathxx->waveBreath_index++;												//标志PWM表指向下一个元素
            if( _LED_Breathxx->waveBreath_index ==  _LED_Breathxx->waveBreathChangeFlash_end + 1)//若PWM表已达到上升的最大亮度
            {
                _LED_Breathxx->waveBreath_index = ( IndexWaveBreath_size - 1 ) - _LED_Breathxx->waveBreathChangeFlash_end;//重新指向PWM表下降的最大亮度				
            }
            if( _LED_Breathxx->waveBreath_index == ( IndexWaveBreath_size - 1 ) - _LED_Breathxx->waveBreathChangeFlash_start + 1)//若PWM表已达到下降的最低亮度
            {
                _LED_Breathxx->waveBreath_index = _LED_Breathxx->waveBreathChangeFlash_start;//重新指向PWM表上升的最低亮度					
            }
            _LED_Breathxx->periodBreath_cnt=0;											//重置呼吸和渐变周期计数标志
        }   
    }
    else if( _LED_Breathxx->gradChange_enable == ENABLE )//控制渐变
    {
        _LED_Breathxx->periodGradChange_cnt++;
        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
        if( _LED_Breathxx->waveChangeFlash_index == 0 || _LED_Breathxx->waveChangeFlash_index == IndexWaveGradChange_size - 1 )//根据PWM表修改定时器的比较寄存器值
        {
            PWM15Duty(_PWMxx, 0x401, 0x0);	    //输出高电平
        }
        else
        {
            PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);	
        }
        //每个PWM表中的每个元素使用 period_cntCmp 次
        if(_LED_Breathxx->periodGradChange_cnt > _LED_Breathxx->periodChangeFlash2_cntCmp)				 				
        {				
            _LED_Breathxx->waveChangeFlash_index++;												//标志PWM表指向下一个元素
            //若PWM表已到达结尾，重新指向表头
            if( _LED_Breathxx->waveChangeFlash_index > _LED_Breathxx->waveBreathChangeFlash_end )			
            {
                if( _LED_Breathxx->gradChange_cycle == ENABLE )//循环渐变
                {
                    _LED_Breathxx->waveChangeFlash_index = _LED_Breathxx->waveBreathChangeFlash_start;//从头开始渐变
                }	
                else if( _LED_Breathxx->gradChange_cycle == DISABLE )//单次渐变
                {
                    _LED_Breathxx->gradChange_enable = DISABLE;//关闭渐变
                    _LED_Breathxx->pin_level = HIGH;       //输出高电平，关灯
                }
            }
            _LED_Breathxx->periodGradChange_cnt=0;											//重置呼吸和渐变周期计数标志
        }   
    }
    else if( _LED_Breathxx->flash_enable == ENABLE )//控制频闪
    {
        _LED_Breathxx->periodFlash_cnt++;
        if( _LED_Breathxx->waveChangeFlash_index == _LED_Breathxx->waveBreathChangeFlash_start)
        {
            PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
            if( _LED_Breathxx->waveChangeFlash_index == 0 || _LED_Breathxx->waveChangeFlash_index == IndexWaveGradChange_size - 1 )//根据PWM表修改定时器的比较寄存器值
            {
                PWM15Duty(_PWMxx, 0x401, 0x0);	    //输出高电平
            }
            else
            {
                PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
            }
            if(_LED_Breathxx->periodFlash_cnt >= _LED_Breathxx->periodBreathFlash1_cntCmp) //频闪计数周期到，翻转频闪电平
            {
                _LED_Breathxx->waveChangeFlash_index = _LED_Breathxx->waveBreathChangeFlash_end;
            }
        }
        else if( _LED_Breathxx->waveChangeFlash_index == _LED_Breathxx->waveBreathChangeFlash_end)
        {
            PWMLevelSet(_PWMxx,DISABLE,DISABLE);	//PWM_ID, 强制输出低电平, 强制输出高电平
            if( _LED_Breathxx->waveChangeFlash_index == 0 || _LED_Breathxx->waveChangeFlash_index == IndexWaveGradChange_size - 1 )//根据PWM表修改定时器的比较寄存器值
            {
                PWM15Duty(_PWMxx, 0x401, 0x0);	    //输出高电平
            }
            else
            {
                PWM15Duty(_PWMxx,0,indexWaveGradChange[_LED_Breathxx->waveChangeFlash_index]);
            }
            if(_LED_Breathxx->periodFlash_cnt >= _LED_Breathxx->periodChangeFlash2_cntCmp) //频闪计数周期到，翻转频闪电平
            {
                _LED_Breathxx->waveChangeFlash_index = _LED_Breathxx->waveBreathChangeFlash_start;
                _LED_Breathxx->periodFlash_cnt = 0;       //重置频闪周期计数标志
            }
        }
    }
    else//控制引脚高低电平
    {
        PWMLevelSet(_PWMxx,DISABLE,DISABLE);	  //PWM_ID, 强制输出低电平, 强制输出高电平
        if(_LED_Breathxx->pin_level > LOW && _LED_Breathxx->pin_level < HIGH)
        {
            PWM15Duty( _PWMxx, 0x0, _LED_Breathxx->pin_level  );	    //PWM周期0x400 == 1024, 占空比设置.
        }
        else if(_LED_Breathxx->pin_level == LOW)
        {
            PWM15Duty(_PWMxx, 0x0, 0x401);	    //PWM周期, 占空比设置.
        }
        else if(_LED_Breathxx->pin_level == HIGH)
        {
            PWM15Duty(_PWMxx, 0x401, 0x0);	    //PWM周期, 占空比设置.
        }
    }
}

#endif





#if LED_FLASH       //6*8 = 48 字节

//频闪灯控制全局变量
LED_FlashTypeDef LED_Flash20;//P20口输出频闪灯
LED_FlashTypeDef LED_Flash21;//P21口输出频闪灯
LED_FlashTypeDef LED_Flash22;//P22口输出频闪灯
LED_FlashTypeDef LED_Flash23;//P23口输出频闪灯
LED_FlashTypeDef LED_Flash24;//P24口输出频闪灯
LED_FlashTypeDef LED_Flash25;//P25口输出频闪灯
LED_FlashTypeDef LED_Flash26;//P26口输出频闪灯
LED_FlashTypeDef LED_Flash27;//P27口输出频闪灯
/*
*********************************************************************************************************
*	函 数 名: LED_flashGPIOConfig
*	功能说明: led频闪灯端口GPIO配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LED_flashGPIOConfig(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_All;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//初始化
}
/*
*********************************************************************************************************
*	函 数 名: LED_flashTIMER3Config
*	功能说明: led频闪灯端口TIMER3配置函数
*	返 回 值: void
*********************************************************************************************************
*/
void LED_flashTIMER3Config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//结构定义
    TIM_InitStructure.TIM_Interrupt = ENABLE;					//中断是否允许,   ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;	            //指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;					//是否输出高速脉冲, ENABLE或DISABLE,/* ENABLE时,P0.5输出高速外部脉冲	*/
	TIM_InitStructure.TIM_Value     = 65536UL - TIM_Value_1ms;	//TIM周期 
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer3,&TIM_InitStructure);					//初始化Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
}
/*
*********************************************************************************************************
*	函 数 名: LED_flashInit
*	功能说明: led频闪灯初始化函数
*	形    参: _LED_Flash2x,频闪灯引脚结构体指针,取值：  &LED_Flash20, &LED_Flash21, &LED_Flash22, &LED_Flash23, &LED_Flash24, &LED_Flash25, &LED_Flash26, &LED_Flash27
*             _period_cntCmp,频闪灯周期计数比较值,控制频闪快慢,单位ms,建议取值： 快频闪 30~100, 慢频闪 101~200
              _flash_enable,频闪的开关,取值： ENABLE, DISABLE
*	返 回 值: void
*********************************************************************************************************
*/
void LED_flashInit(LED_FlashTypeDef * _LED_Flash2x, u16 _period_cntCmp, u8 _flash_enable)
{
    LED_flashGPIOConfig();
    LED_flashTIMER3Config();
    _LED_Flash2x->period_cnt        = 0;                    //固定从0开始计数
    _LED_Flash2x->period_cntCmp     = _period_cntCmp / 2;   //设置频闪周期计数比较值
    _LED_Flash2x->flash_enable      = _flash_enable;        //设置频闪的开关： ENABLE 开，DISABLE 关
    _LED_Flash2x->pin_level         = HIGH;                 //默认输出高电平
}
/*
*********************************************************************************************************
*	函 数 名: LED_flashSwitch
*	功能说明: led频闪开关函数
*	形    参: _LED_Flash2x,频闪灯引脚结构体指针,取值：  &LED_Flash20, &LED_Flash21, &LED_Flash22, &LED_Flash23, &LED_Flash24, &LED_Flash25, &LED_Flash26, &LED_Flash27
*             _pin_level,当关闭频闪时，用于控制输出引脚状态,取值： 高电平 HIGH, 低电平 LOW  
*             _flash_enable,频闪的开关,取值： ENABLE, DISABLE
*	返 回 值: void
*********************************************************************************************************
*/
void LED_flashSwitch(LED_FlashTypeDef * _LED_Flash2x, u8 _pin_level, u8 _flash_enable)
{
    _LED_Flash2x->flash_enable = _flash_enable; //设置频闪的开关： ENABLE 开，DISABLE 关
    _LED_Flash2x->pin_level = _pin_level;       //当关闭频闪时，用于控制输出引脚状态
}
/*
*********************************************************************************************************
*	函 数 名: LED_flashTIMER3IntCallback
*	功能说明: led频闪中断回调函数
*	形    参: void
*	返 回 值: void
*********************************************************************************************************
*/
void LED_flashTIMER3IntCallback(void)
{
    //频闪P20的开关
    if( LED_Flash20.flash_enable == ENABLE )
    {
        LED_Flash20.period_cnt++;
        if(LED_Flash20.period_cnt >= LED_Flash20.period_cntCmp)
        {
            P20 = ~P20;//翻转P20
            LED_Flash20.period_cnt=0;
        }
    }
    else
    {
        P20 = LED_Flash20.pin_level;//控制P20引脚输出高电平
    }
    //频闪P21的开关
    if( LED_Flash21.flash_enable == ENABLE )
    {
        LED_Flash21.period_cnt++;
        if(LED_Flash21.period_cnt >= LED_Flash21.period_cntCmp)
        {
            P21 = ~P21;//翻转P21
            LED_Flash21.period_cnt=0;
        }
    }
    else
    {
        P21 = LED_Flash21.pin_level;//控制P21引脚输出高电平
    }
        //频闪P22的开关
    if( LED_Flash22.flash_enable == ENABLE )
    {
        LED_Flash22.period_cnt++;
        if(LED_Flash22.period_cnt >= LED_Flash22.period_cntCmp)
        {
            P22 = ~P22;//翻转P22
            LED_Flash22.period_cnt=0;
        }
    }
    else
    {
        P22 = LED_Flash22.pin_level;//控制P22引脚输出高电平
    }
        //频闪P23的开关
    if( LED_Flash23.flash_enable == ENABLE )
    {
        LED_Flash23.period_cnt++;
        if(LED_Flash23.period_cnt >= LED_Flash23.period_cntCmp)
        {
            P23 = ~P23;//翻转P23
            LED_Flash23.period_cnt=0;
        }
    }
    else
    {
        P23 = LED_Flash23.pin_level;//控制P23引脚输出高电平
    }
    //频闪P24的开关
    if( LED_Flash24.flash_enable == ENABLE )
    {
        LED_Flash24.period_cnt++;
        if(LED_Flash24.period_cnt >= LED_Flash24.period_cntCmp)
        {
            P24 = ~P24;//翻转P24
            LED_Flash24.period_cnt=0;
        }
    }
    else
    {
        P24 = LED_Flash24.pin_level;//控制P24引脚输出高电平
    }
    //频闪P25的开关
    if( LED_Flash25.flash_enable == ENABLE )
    {
        LED_Flash25.period_cnt++;
        if(LED_Flash25.period_cnt >= LED_Flash25.period_cntCmp)
        {
            P25 = ~P25;//翻转P25
            LED_Flash25.period_cnt=0;
        }
    }
    else
    {
        P25 = LED_Flash25.pin_level;//控制P25引脚输出高电平
    }
    //频闪P26的开关
    if( LED_Flash26.flash_enable == ENABLE )
    {
        LED_Flash26.period_cnt++;
        if(LED_Flash26.period_cnt >= LED_Flash26.period_cntCmp)
        {
            P26 = ~P26;//翻转P26
            LED_Flash26.period_cnt=0;
        }
    }
    else
    {
        P26 = LED_Flash26.pin_level;//控制P26引脚输出高电平
    }
    //频闪P27的开关
    if( LED_Flash27.flash_enable == ENABLE )
    {
        LED_Flash27.period_cnt++;
        if(LED_Flash27.period_cnt >= LED_Flash27.period_cntCmp)
        {
            P27 = ~P27;//翻转P27
            LED_Flash27.period_cnt=0;
        }
    }
    else
    {
        P27 = LED_Flash27.pin_level;//控制P27引脚输出高电平
    }
}

#endif
