#ifndef __MOSHIZHIXING_H__
#define __MOSHIZHIXING_H__

#define BaoShanDeng CeIO6

sbit JiDianQi=P5^4;			  	//
sbit CeIO1=P0^4;			  	//
sbit CeIO2=P0^5;			  	//
sbit CeIO3=P1^4;			  	//
sbit CeIO4=P1^5;			  	//
sbit CeIO5=P1^6;			  	//
sbit CeIO6=P1^7;			  	//
sbit LED_R1=P4^5;			  	//
sbit LED_G1=P2^7;			  	//
sbit LED_B1=P2^6;			  	//
sbit OUT1=P2^5;			  		//
sbit LED_R2=P2^4;			  	//
sbit LED_G2=P2^3;			  	//
sbit LED_B2=P2^2;			  	//
sbit OUT2=P2^1;			  		//
sbit LED_R3=P2^0;			  	//
sbit LED_G3=P4^4;			  	//
sbit LED_B3=P4^2;			  	//
sbit OUT3=P4^1;			  		//
sbit LED_R4=P3^7;			  	//
sbit LED_G4=P3^6;			  	//
sbit LED_B4=P3^5;			  	//
sbit OUT4=P3^4;			  		//

#define CeIO1_MoShi  	0			//0为高阻态输入，1为强输出，2为通用IO，3为开漏输出
#define CeIO2_MoShi  	0			//
#define CeIO3_MoShi  	0		  	//
#define CeIO4_MoShi  	0		  	//
#define CeIO5_MoShi  	0		  	//
#define CeIO6_MoShi  	1		  	//
#define LED_R1_MoShi 	1			//
#define LED_G1_MoShi 	1			//
#define LED_B1_MoShi 	1			//
#define OUT1_MoShi   	0		   	//
#define LED_R2_MoShi 	1		  	//
#define LED_G2_MoShi 	1		  	//
#define LED_B2_MoShi 	1		  	//
#define OUT2_MoShi   	0			//
#define LED_R3_MoShi 	1		  	//
#define LED_G3_MoShi 	1		  	//
#define LED_B3_MoShi 	1		  	//
#define OUT3_MoShi   	0			//
#define LED_R4_MoShi 	1		  	//
#define LED_G4_MoShi 	1		  	//
#define LED_B4_MoShi 	1		  	//
#define OUT4_MoShi   	0		  	//		
#define JiDianQi_MoShi  1			//

void GongNeng1(void);
void GongNeng2(void);
void GongNeng3(void);
void GongNeng4(void);
void GongNeng5(void);
void GongNeng6(void);
void GongNeng7(void);
void ZongJiZhuangTaiHuiFu(void);
void ZongZhiXing(void);
void IOMoShi_Init(void);
void IO_Init(void);
void BaoShanXiaoGuo();
void ZiFuWei(void);

#endif 