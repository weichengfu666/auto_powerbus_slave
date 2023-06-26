#ifndef __BSP_CONFIG_H__
#define __BSP_CONFIG_H__
#include "main.h"

/* ÅäÖÃÄ£¿é¿ª¹Ø */
#define LED
//#define LOCK

extern u16 TIM_Value_1ms;  
extern u16 TIM_Value_100us;
extern u16 TIM_Value_10us;
extern u16 TIM_Value_1us;

#if 0
extern u16	pwm0,pwm1,pwm2;
extern bit	B_PWM0_Dir,B_PWM1_Dir;

extern u16 PWM_Period_1ms;
extern u16 PWM_Period_100us;
extern u16 PWM_Period_10us;
extern u16 PWM_Period_1us;

void    LED_FlashConfig(void);
void    LED_Flash(void);
void	GPIO_config(void);
void	Timer_config(void);
void	PWM15_config(void);
#endif


#endif

