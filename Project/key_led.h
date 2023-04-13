#ifndef __key_led_H__
#define __key_led_H__

sbit Led_Key1 = P2^3;
sbit Led_Key2 = P2^2;
sbit Led_Key3 = P2^1;
sbit Led_Key4 = P2^0;
sbit Led_Key5 = P2^7;
sbit Led_Key6 = P2^6;
sbit Led_Key7 = P2^5;
sbit Led_Key8 = P2^4;
sbit Led_Key9 = P3^5;
sbit Led_Key10 = P3^4;
sbit Led_Key11 = P3^3;
sbit Led_Key12 = P3^2;
sbit Led_Key13 = P4^2;
sbit Led_Key14 = P4^1;
sbit Led_Key15 = P3^7;
sbit Led_Key16 = P3^6;
sbit Led1 = P1^1;
sbit Led2 = P0^1;
sbit Led3 = P1^0;
sbit Led4 = P0^0;
sbit Led5 = P1^3;
sbit Led6 = P0^3;
sbit Led7 = P1^2;
sbit Led8 = P0^2;
sbit Led9 = P1^5;
sbit Led10 = P0^5;
sbit Led11 = P1^4;
sbit Led12 = P0^4;
sbit Led13 = P1^7;
sbit Led14 = P0^7;
sbit Led15 = P1^6;
sbit Led16 = P0^6;

#define Led1R  1
#define Led1G  0
#define Led2R  1
#define Led2G  0
#define Led3R  1
#define Led3G  0
#define Led4R  1
#define Led4G  0
#define Led5R  0
#define Led5G  1
#define Led6R  0
#define Led6G  1
#define Led7R  1
#define Led7G  0
#define Led8R  0
#define Led8G  1
#define Led9R  0
#define Led9G  1
#define Led10R  0
#define Led10G  1
#define Led11R  1
#define Led11G  0
#define Led12R  1
#define Led12G  0
#define Led13R  1
#define Led13G  0
#define Led14R  1
#define Led14G  0
#define Led15R  0
#define Led15G  1
#define Led16R  1
#define Led16G  0

#define Led1key_on  0
#define Led2key_on  0
#define Led3key_on  0
#define Led4key_on  1
#define Led5key_on  0
#define Led6key_on  0
#define Led7key_on  0
#define Led8key_on  0
#define Led9key_on  0
#define Led10key_on  0
#define Led11key_on  0
#define Led12key_on  0
#define Led13key_on  0
#define Led14key_on  0
#define Led15key_on  0
#define Led16key_on  0

int shejijiance(void);
void led_init(void);
void led_mima(void);
void ledkey_on(void);
void mimashezhi(char mimazuhao,char mimaxuhao);
void ledkey_on1(void);

#endif