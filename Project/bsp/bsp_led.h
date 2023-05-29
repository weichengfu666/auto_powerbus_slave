#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "main.h"

//呼吸灯选择编译开关：1为开，0为关
#define LED_BREATH 1
#define LED_FLASH  0

//LED状态值：低电平，高电平，呼吸，渐变，频闪
#define LOW  0
#define HIGH 101
#define BREATH 102
#define GRADCHANGE_ONCE  103  //单次渐变
#define GRADCHANGE_CYCLE 104  //循环渐变
#define FLASH 105

#define DEFAULT 0xFFFF  //为默认值将不作修改，方便只填入需要修改的参数，不需要修改的参数填 DEFAULT

typedef struct LED_Breath{
                        u16 periodBreath_cnt;                   //呼吸的周期计数标志
                        u16 periodBreath_cntCmp;            //呼吸的周期计数比较标志
                        u8 waveBreath_index;                   //呼吸PWM查表，周期性的由灭到亮再到灭
                        u8  breath_enable;                        //呼吸开关： ENABLE 为开， DISABLE 为关
    
                        u16 periodGradChange_cnt;          //渐变的周期计数标志
                        u16 periodGradChange_cntCmp;   //渐变的周期计数比较标志
                        u8 waveChangeFlash_index;           //渐变PWM查表，周期性的从起始亮度到结束亮度，再从起始亮度到结束亮度
                        u8 gradChange_cycle;                   //渐变是否循环，ENABLE 为打开循环， DISABLE 为关闭循环（单次渐变）
                        u8  gradChange_enable;                //渐变开关： ENABLE 为开， DISABLE 为关
    
                        u16 periodFlash_cnt;                      //频闪的周期计数标志
                        u16 periodFlash_cntCmp;               //频闪的周期计数比较标志
                        u8  flash_enable;                            //频闪开关： ENABLE 为开， DISABLE 为关

                        u8  pin_level;                                  //呼吸开关，用于控制输出引脚高低电平，精度1%，取值：LOW,0~100,HIGH
                        u8 waveBreathChangeFlash_start;            //渐变PWM起始亮度，0~49：由最暗到最亮，50~99：由最亮到最暗，可以随意组合，比如：start = 25,end = 74,从起始亮度（25）到最亮（49）到结束亮度（74）（注意：25和74是对称关系，所以亮度一样），周期性的再从起始亮度（25）到结束亮度（74）
                        u8 waveBreathChangeFlash_end;             //渐变PWM结束亮度
}LED_BreathTypeDef;

typedef struct LED_Flash{
                        u16 period_cnt;     //周期计数标志
                        u16 period_cntCmp;  //周期计数比较标志
                        u8  flash_enable;   //用于开关频闪： ENABLE 为开， DISABLE 为关
                        u8  pin_level;      //当关闭频闪时，用于控制输出引脚状态
}LED_FlashTypeDef;






#if LED_BREATH

extern code u16 indexWaveBreath[];         /* LED亮度等级 PWM表,指数曲线 ，此表使用工程目录下的python脚本index_wave.py生成*/
extern const u16 IndexWaveBreath_size;//呼吸PWM表有100个元素
extern const u16 IndexWaveGradChange_size;//渐变PWM表有100个元素
extern LED_BreathTypeDef LED_BreathxxArr[];//呼吸灯控制全局变量数组

/* 呼吸灯函数 */  //输出口接led 负极, vcc接led 正极
void LED_breathInit( u8 _PWMxx, u8 _breath_state, u16 _periodBreath_cntCmp, u16 _periodGradChange_cntCmp, u16 _periodFlash_cntCmp, u8 _waveBreathChangeFlash_start, u8 _waveBreathChangeFlash_end, u8 _waveBreathChangeFlash_now );//呼吸灯初始化函数,main函数调用
void LED_breathSetState(u8 _PWMxx, u8 _breath_state);//led呼吸灯设置状态函数,main函数调用
void LED_breathSetPeriod(u8 _PWMxx, u16 _periodBreath_cntCmp, u16 _periodGradChange_cntCmp, u16 _periodFlash_cntCmp, u8 _waveGradChange_start, u8 _waveGradChange_end);//led呼吸灯设置周期和渐变亮度函数,main函数调用
void LED_breathTIMER4IntCallback0x( u8 _PWMxx );//led呼吸灯中断回调函数,直接配置,在定时器中断中调用
void LED_breathGPIOConfig(u8 _PWMxx);//led呼吸灯端口GPIO配置函数,直接配置,在初始函数调用
void LED_breathPWM15Config(u8 _PWMxx);//led呼吸灯端口PWM15配置函数,直接配置,在初始函数调用
void LED_breathTIMER4Config(void);//led呼吸灯端口TIMER4配置函数,直接配置,在初始函数调用

#endif




#if LED_FLASH

extern LED_FlashTypeDef LED_Flash20;        //P20口输出频闪灯
extern LED_FlashTypeDef LED_Flash21;        //P21口输出频闪灯
extern LED_FlashTypeDef LED_Flash22;        //P22口输出频闪灯
extern LED_FlashTypeDef LED_Flash23;        //P23口输出频闪灯
extern LED_FlashTypeDef LED_Flash24;        //P24口输出频闪灯
extern LED_FlashTypeDef LED_Flash25;        //P25口输出频闪灯
extern LED_FlashTypeDef LED_Flash26;        //P26口输出频闪灯
extern LED_FlashTypeDef LED_Flash27;        //P27口输出频闪灯

/* 频闪灯函数 */  //输出口接led 负极, vcc接led 正极
void LED_flashInit(LED_FlashTypeDef * _LED_Flash2x, u16 _period_cntCmp, u8 _flash_enable);//频闪灯初始化函数,main函数调用
void LED_flashSwitch(LED_FlashTypeDef * _LED_Flash2x, u8 _pin_level, u8 _flash_enable);//led频闪灯开关函数,main函数调用
void LED_flashTIMER3IntCallback(void);//led频闪中断回调函数,直接配置,在定时器中断中调用
void LED_flashGPIOConfig(void);//led频闪灯端口GPIO配置函数,直接配置,在初始函数调用
void LED_flashTIMER3Config(void);//led频闪灯端口TIMER3配置函数,直接配置,在初始函数调用

#endif

#endif

