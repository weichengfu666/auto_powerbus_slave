#ifndef __BSP_LOCK_H__
#define __BSP_LOCK_H__

#include "main.h"


//状态值： 通电 ， 断电 ， 断后通 ， 通后断
#define OPEN  1
#define CLOSE 2
#define CLOSE_OPEN  3
#define OPEN_CLOSE  4

#define DEFAULT 0xFFFF  //为默认值将不作修改，方便只填入需要修改的参数，不需要修改的参数填 DEFAULT

#define LOCK1_PORT     0
#define LOCK2_PORT     1
#define LOCK3_PORT     2
#define LOCK4_PORT     3
#define LOCK5_PORT     4
#define LOCK6_PORT     5
#define LOCK7_PORT     6
#define LOCK8_PORT     7

typedef struct {
                        u8  open_enable;                                  //通电
                        u8  close_enable;                                  //断电
                        u8  closeOpen_enable;                          //断后通
                        u8  openClose_enable;                          //通后断
                        u32 delayTime_cnt;                               //通断延时计数标志
                        u32 delayTime_cntcmp;                        //通断延时计数比较标志
}LOCK_TypeDef;

void LOCK_GPIOConfig(u8 _PWMxx);
void LOCK_PWM15Config(void);
void LOCK_TIMER4Config(void);
void LOCK_SetState(u8 _PWMxx, u8 _lock_state);
void LOCK_Init( u8 _PWMxx, u8 _lock_state, u32 _lock_delayTime );
void LOCK_TIMER4IntCallback0x( u8 _PWMxx );

#endif