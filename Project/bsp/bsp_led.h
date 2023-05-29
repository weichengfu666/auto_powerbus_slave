#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "main.h"

//������ѡ����뿪�أ�1Ϊ����0Ϊ��
#define LED_BREATH 1
#define LED_FLASH  0

//LED״ֵ̬���͵�ƽ���ߵ�ƽ�����������䣬Ƶ��
#define LOW  0
#define HIGH 101
#define BREATH 102
#define GRADCHANGE_ONCE  103  //���ν���
#define GRADCHANGE_CYCLE 104  //ѭ������
#define FLASH 105

#define DEFAULT 0xFFFF  //ΪĬ��ֵ�������޸ģ�����ֻ������Ҫ�޸ĵĲ���������Ҫ�޸ĵĲ����� DEFAULT

typedef struct LED_Breath{
                        u16 periodBreath_cnt;                   //���������ڼ�����־
                        u16 periodBreath_cntCmp;            //���������ڼ����Ƚϱ�־
                        u8 waveBreath_index;                   //����PWM��������Ե��������ٵ���
                        u8  breath_enable;                        //�������أ� ENABLE Ϊ���� DISABLE Ϊ��
    
                        u16 periodGradChange_cnt;          //��������ڼ�����־
                        u16 periodGradChange_cntCmp;   //��������ڼ����Ƚϱ�־
                        u8 waveChangeFlash_index;           //����PWM��������ԵĴ���ʼ���ȵ��������ȣ��ٴ���ʼ���ȵ���������
                        u8 gradChange_cycle;                   //�����Ƿ�ѭ����ENABLE Ϊ��ѭ���� DISABLE Ϊ�ر�ѭ�������ν��䣩
                        u8  gradChange_enable;                //���俪�أ� ENABLE Ϊ���� DISABLE Ϊ��
    
                        u16 periodFlash_cnt;                      //Ƶ�������ڼ�����־
                        u16 periodFlash_cntCmp;               //Ƶ�������ڼ����Ƚϱ�־
                        u8  flash_enable;                            //Ƶ�����أ� ENABLE Ϊ���� DISABLE Ϊ��

                        u8  pin_level;                                  //�������أ����ڿ���������Ÿߵ͵�ƽ������1%��ȡֵ��LOW,0~100,HIGH
                        u8 waveBreathChangeFlash_start;            //����PWM��ʼ���ȣ�0~49�������������50~99�����������������������ϣ����磺start = 25,end = 74,����ʼ���ȣ�25����������49�����������ȣ�74����ע�⣺25��74�ǶԳƹ�ϵ����������һ�����������Ե��ٴ���ʼ���ȣ�25�����������ȣ�74��
                        u8 waveBreathChangeFlash_end;             //����PWM��������
}LED_BreathTypeDef;

typedef struct LED_Flash{
                        u16 period_cnt;     //���ڼ�����־
                        u16 period_cntCmp;  //���ڼ����Ƚϱ�־
                        u8  flash_enable;   //���ڿ���Ƶ���� ENABLE Ϊ���� DISABLE Ϊ��
                        u8  pin_level;      //���ر�Ƶ��ʱ�����ڿ����������״̬
}LED_FlashTypeDef;






#if LED_BREATH

extern code u16 indexWaveBreath[];         /* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/
extern const u16 IndexWaveBreath_size;//����PWM����100��Ԫ��
extern const u16 IndexWaveGradChange_size;//����PWM����100��Ԫ��
extern LED_BreathTypeDef LED_BreathxxArr[];//�����ƿ���ȫ�ֱ�������

/* �����ƺ��� */  //����ڽ�led ����, vcc��led ����
void LED_breathInit( u8 _PWMxx, u8 _breath_state, u16 _periodBreath_cntCmp, u16 _periodGradChange_cntCmp, u16 _periodFlash_cntCmp, u8 _waveBreathChangeFlash_start, u8 _waveBreathChangeFlash_end, u8 _waveBreathChangeFlash_now );//�����Ƴ�ʼ������,main��������
void LED_breathSetState(u8 _PWMxx, u8 _breath_state);//led����������״̬����,main��������
void LED_breathSetPeriod(u8 _PWMxx, u16 _periodBreath_cntCmp, u16 _periodGradChange_cntCmp, u16 _periodFlash_cntCmp, u8 _waveGradChange_start, u8 _waveGradChange_end);//led�������������ںͽ������Ⱥ���,main��������
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

