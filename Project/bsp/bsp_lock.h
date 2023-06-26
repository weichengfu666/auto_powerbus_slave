#ifndef __BSP_LOCK_H__
#define __BSP_LOCK_H__

#include "main.h"


//״ֵ̬�� ͨ�� �� �ϵ� �� �Ϻ�ͨ �� ͨ���
#define OPEN  1
#define CLOSE 2
#define CLOSE_OPEN  3
#define OPEN_CLOSE  4

#define DEFAULT 0xFFFF  //ΪĬ��ֵ�������޸ģ�����ֻ������Ҫ�޸ĵĲ���������Ҫ�޸ĵĲ����� DEFAULT

#define LOCK1_PORT     0
#define LOCK2_PORT     1
#define LOCK3_PORT     2
#define LOCK4_PORT     3
#define LOCK5_PORT     4
#define LOCK6_PORT     5
#define LOCK7_PORT     6
#define LOCK8_PORT     7

typedef struct {
                        u8  open_enable;                                  //ͨ��
                        u8  close_enable;                                  //�ϵ�
                        u8  closeOpen_enable;                          //�Ϻ�ͨ
                        u8  openClose_enable;                          //ͨ���
                        u32 delayTime_cnt;                               //ͨ����ʱ������־
                        u32 delayTime_cntcmp;                        //ͨ����ʱ�����Ƚϱ�־
}LOCK_TypeDef;

void LOCK_GPIOConfig(u8 _PWMxx);
void LOCK_PWM15Config(void);
void LOCK_TIMER4Config(void);
void LOCK_SetState(u8 _PWMxx, u8 _lock_state);
void LOCK_Init( u8 _PWMxx, u8 _lock_state, u32 _lock_delayTime );
void LOCK_TIMER4IntCallback0x( u8 _PWMxx );

#endif