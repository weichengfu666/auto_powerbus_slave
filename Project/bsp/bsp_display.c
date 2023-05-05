#include "main.h"
#include "bsp_display.h"


void disPlay(void)
{
#define period 1000
#define periodFlash 50
#define delayMs 3000
    
    LED_breathInit(PWM00, BREATH, period, periodFlash);
    LED_breathInit(PWM01, BREATH, period, periodFlash);
    LED_breathInit(PWM02, BREATH, period, periodFlash);
    LED_breathInit(PWM03, BREATH, period, periodFlash);
    LED_breathInit(PWM04, BREATH, period, periodFlash);
    LED_breathInit(PWM05, BREATH, period, periodFlash);
    LED_breathInit(PWM06, BREATH, period, periodFlash);
    LED_breathInit(PWM07, BREATH, period, periodFlash);
    
    LED_breathInit(PWM20, BREATH, period, periodFlash);
    LED_breathInit(PWM21, BREATH, period, periodFlash);
    LED_breathInit(PWM22, BREATH, period, periodFlash);
    LED_breathInit(PWM23, BREATH, period, periodFlash);
    LED_breathInit(PWM24, BREATH, period, periodFlash);
    LED_breathInit(PWM25, BREATH, period, periodFlash);
    LED_breathInit(PWM26, BREATH, period, periodFlash);
    LED_breathInit(PWM27, BREATH, period, periodFlash);

    EA = 1;
    
    for(;;)
    {
//        LED_breathSetState(PWM00, 1);
//        delay_ms(5000);
//        LED_breathSetState(PWM00, BREATH);
//        delay_ms(5000);
//        LED_breathSetState(PWM00, HIGH);
//        delay_ms(5000);
//        LED_breathSetState(PWM00, FLASH);
//        LED_breathSetPeriod(PWM00, DEFAULT, 50);
//        delay_ms(5000);
        
        LED_breathSetState(PWM20, 1);
        LED_breathSetState(PWM21, 5);
        LED_breathSetState(PWM22, 10);
        LED_breathSetState(PWM23, 20);
        LED_breathSetState(PWM24, 30);
        LED_breathSetState(PWM25, 50);
        LED_breathSetState(PWM26, 75);
        LED_breathSetState(PWM27, 85);
        delay_ms(delayMs);
        LED_breathSetState(PWM20, HIGH);
        LED_breathSetState(PWM21, HIGH);
        LED_breathSetState(PWM22, HIGH);
        LED_breathSetState(PWM23, HIGH);
        LED_breathSetState(PWM24, HIGH);
        LED_breathSetState(PWM25, HIGH);
        LED_breathSetState(PWM26, HIGH);
        LED_breathSetState(PWM27, HIGH);
        delay_ms(delayMs);
        LED_breathSetState(PWM20, BREATH);
        LED_breathSetState(PWM21, BREATH);
        LED_breathSetState(PWM22, BREATH);
        LED_breathSetState(PWM23, BREATH);
        LED_breathSetState(PWM24, BREATH);
        LED_breathSetState(PWM25, BREATH);
        LED_breathSetState(PWM26, BREATH);
        LED_breathSetState(PWM27, BREATH);
        delay_ms(delayMs);
        LED_breathSetState(PWM20, GRADCHANGE);
        LED_breathSetState(PWM21, GRADCHANGE);
        LED_breathSetState(PWM22, GRADCHANGE);
        LED_breathSetState(PWM23, GRADCHANGE);
        LED_breathSetState(PWM24, GRADCHANGE);
        LED_breathSetState(PWM25, GRADCHANGE);
        LED_breathSetState(PWM26, GRADCHANGE);
        LED_breathSetState(PWM27, GRADCHANGE);
        delay_ms(delayMs);
        LED_breathSetState(PWM20, FLASH);
        LED_breathSetState(PWM21, FLASH);
        LED_breathSetState(PWM22, FLASH);
        LED_breathSetState(PWM23, FLASH);
        LED_breathSetState(PWM24, FLASH);
        LED_breathSetState(PWM25, FLASH);
        LED_breathSetState(PWM26, FLASH);
        LED_breathSetState(PWM27, FLASH);
        delay_ms(delayMs);
    }
}