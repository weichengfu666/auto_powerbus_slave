#include "main.h"

void PWM_Init()
{
		P_SW1=0x0c;//0000 1100
    CCON = 0x00;
    CMOD = 0x08;                                //PCAʱ��Ϊϵͳʱ��
    CL = 0x00;
    CH = 0x00;
//--10λPWM--
    CCAPM2 = 0x42;//0x42;                          //PCAģ��2ΪPWM����ģʽ 
		PCA_PWM2 = 0xe0;                           	//1100 0000
																								//1100 0000 EBSn��PCAģ��2���10λPWM  
																								//0011 0000 XCCAPnH����9��10λ����ֵ  
																								//0000 1100 XCCAPnL����9��10λ�Ƚ�ֵ  
																								//0000 0010 EPCnH������ֵ���λ(11λ)  
																								//0000 0001 EPCnL���Ƚ�ֵ���λ��11λ��
    CCAP2H = 0x00;															//����ֵ��8λ
    CCAP2L = 0x00;                              //�Ƚ�ֵ��8λ��PWMռ�ձ�Ϊ96.875%[(400H-20H)/400H]
    CR = 1;                                     //����PCA��ʱ��
		EA = 1;
}

void PWM_ShuChu(uint PWM_CS)//0~0x0400
{
	uint PWM_ZhanKongBi=0x400-PWM_CS;
	if(PWM_ZhanKongBi==0)
	{
		CCAPM2 = 0;
		P54=0;
	}else if(PWM_ZhanKongBi==0x0400)
	{
		CCAPM2 = 0;
		P54=1;
	}else{
		CCAPM2 = 0x42;//1100 1101
		PCA_PWM2=(PCA_PWM2&0xcd)|(((0x400-PWM_ZhanKongBi)>>4)&0x30);
		CCAP2H=(0x400-PWM_ZhanKongBi)&0xff;
	}
}