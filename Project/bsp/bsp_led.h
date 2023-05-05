#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "main.h"

#define LED_BREATH 1
#define LED_FLASH  1

//LED״ֵ̬
#define LOW  0
#define HIGH 100
#define BREATH 101
#define GRADCHANGE 102
#define FLASH 103

#define DEFAULT 0  //ΪĬ��ֵ�������޸ģ�����ֻ������Ҫ�޸ĵĲ���������Ҫ�޸ĵĲ����� DEFAULT

typedef struct LED_Breath{
                        u16 period_cnt;         //�����ͽ�������ڼ�����־
                        u16 period_cntCmp;      //�����ͽ�������ڼ����Ƚϱ�־
                        u16 wave_index;         //����PWM���
                        u16 periodFlash_cnt;    //Ƶ�������ڼ�����־
                        u16 periodFlash_cntCmp; //Ƶ�������ڼ����Ƚϱ�־
                        u16 flash_level;        //���ڷ�תƵ����ƽ
                        u8  breath_enable;      //���ڿ��غ����� ENABLE Ϊ���� DISABLE Ϊ��
                        u8  gradChange_enable;  //���ڿ��ؽ��䣺 ENABLE Ϊ���� DISABLE Ϊ��
                        u8  flash_enable;       //���ڿ���Ƶ���� ENABLE Ϊ���� DISABLE Ϊ��
                        u8  pin_level;          //���رպ���ʱ�����ڿ���������Ÿߵ͵�ƽ������1%
}LED_BreathTypeDef;

typedef struct LED_Flash{
                        u16 period_cnt;     //���ڼ�����־
                        u16 period_cntCmp;  //���ڼ����Ƚϱ�־
                        u8  flash_enable;   //���ڿ���Ƶ���� ENABLE Ϊ���� DISABLE Ϊ��
                        u8  pin_level;      //���ر�Ƶ��ʱ�����ڿ����������״̬
}LED_FlashTypeDef;






#if LED_BREATH

extern u16 indexWaveBreath[];                     /* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/
extern const u16 POINT_NUM;                 //����PWM���ж��ٸ�Ԫ��
extern LED_BreathTypeDef LED_BreathxxArr[];//�����ƿ���ȫ�ֱ�������

/* �����ƺ��� */  //����ڽ�led ����, vcc��led ����
void LED_breathInit( u8 _PWMxx, u8 _breath_state, u16 _period_cntCmp, u16 _periodFlash_cntCmp);//�����Ƴ�ʼ������,main��������
void LED_breathSetState(u8 _PWMxx, u8 _breath_state);//led����������״̬����,main��������
void LED_breathSetPeriod(u8 _PWMxx, u16 _period_cntCmp, u16 _periodFlash_cntCmp);//led�������������ں���,main��������
void LED_breathTIMER4IntCallback0x( u8 _PWMxx );//led�������жϻص�����,ֱ������,�ڶ�ʱ���ж��е���
void LED_breathGPIOConfig(u8 _PWMxx);//led�����ƶ˿�GPIO���ú���,ֱ������,�ڳ�ʼ��������
void LED_breathPWM15Config(u8 _PWMxx);//led�����ƶ˿�PWM15���ú���,ֱ������,�ڳ�ʼ��������
void LED_breathTIMER4Config(void);//led�����ƶ˿�TIMER4���ú���,ֱ������,�ڳ�ʼ��������

#endif




#if LED_FLASH

extern LED_FlashTypeDef LED_Flash20;        //P20�����Ƶ����
extern LED_FlashTypeDef LED_Flash21;        //P21�����Ƶ����
extern LED_FlashTypeDef LED_Flash22;        //P22�����Ƶ����
extern LED_FlashTypeDef LED_Flash23;        //P23�����Ƶ����
extern LED_FlashTypeDef LED_Flash24;        //P24�����Ƶ����
extern LED_FlashTypeDef LED_Flash25;        //P25�����Ƶ����
extern LED_FlashTypeDef LED_Flash26;        //P26�����Ƶ����
extern LED_FlashTypeDef LED_Flash27;        //P27�����Ƶ����

/* Ƶ���ƺ��� */  //����ڽ�led ����, vcc��led ����
void LED_flashInit(LED_FlashTypeDef * _LED_Flash2x, u16 _period_cntCmp, u8 _flash_enable);//Ƶ���Ƴ�ʼ������,main��������
void LED_flashSwitch(LED_FlashTypeDef * _LED_Flash2x, u8 _pin_level, u8 _flash_enable);//ledƵ���ƿ��غ���,main��������
void LED_flashTIMER3IntCallback(void);//ledƵ���жϻص�����,ֱ������,�ڶ�ʱ���ж��е���
void LED_flashGPIOConfig(void);//ledƵ���ƶ˿�GPIO���ú���,ֱ������,�ڳ�ʼ��������
void LED_flashTIMER3Config(void);//ledƵ���ƶ˿�TIMER3���ú���,ֱ������,�ڳ�ʼ��������

#endif

#endif

