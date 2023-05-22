/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

/*************	����˵��	**************

���ļ�ΪSTC8ϵ�еĶ�ʱ����ʼ�����жϳ���,�û�����������ļ����޸��Լ���Ҫ���жϳ���.

******************************************/

#include	"timer.h"
#include "main.h"

///********************* Timer0�жϺ���************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{
    if(LED_displayTime != 0)
    {
        LED_displayTime++;
    }
	Time++;	
	for(Time_i=0;Time_i<5;Time_i++)
	{
		if(Delay_Time[Time_i]>0)
		{
			Delay_Time[Time_i]++;
		}
	}
	if(JianBian_Time2>0)
	{
		JianBian_Time2--;
	}else if(JianBian_Time1>0)
	{
		JianBian_Time1=0;
		LiangDu_DangQian=LiangDu_JieShu;
		LiangDu_ChuShi=0;
		LiangDu_JieShu=0;
	}else if(XunHuan_Changdu>0)
	{	
		if(XunHuan_ZhiZhen<(XunHuan_Changdu-1))
		{
			XunHuan_ZhiZhen++;
		}else{
			XunHuan_ZhiZhen=0;
		}
		JianBian_Time1=IapReadByte(XunHuan_Addr+1+XunHuan_ZhiZhen*4)*0x10000+IapReadByte(XunHuan_Addr+2+XunHuan_ZhiZhen*4)*0x100+IapReadByte(XunHuan_Addr+3+XunHuan_ZhiZhen*4);
		JianBian_Time2=JianBian_Time1;
		LiangDu_ChuShi=IapReadByte(XunHuan_Addr+XunHuan_ZhiZhen*4);
		LiangDu_DangQian=LiangDu_ChuShi;
		if(XunHuan_ZhiZhen<(XunHuan_Changdu-1))
			LiangDu_JieShu=IapReadByte(XunHuan_Addr+4+XunHuan_ZhiZhen*4);
		else
			LiangDu_JieShu=IapReadByte(XunHuan_Addr);
		if(JianBian_Time1==0)
			LiangDu_DangQian=LiangDu_JieShu;
	}
	if(SouXunXuLie_Time>0)
	{
		SouXunXuLie_Time++;
	}
	if(BiaoHaoFuZhi_Time>0)
	{
		BiaoHaoFuZhi_Time++;
	}
	if(Time%500==0)
	{
		//ShuJuFaSong_Flag=1;
	} 	
	if(Time==30000)
	{
		Time=0;
	}
}

/********************* Timer1�жϺ���************************/
void timer1_int (void) interrupt TIMER1_VECTOR
{
   P21 = ~P21;
}

/********************* Timer2�жϺ���************************/
u8 arrIndex = 0;
u32 DisplayTimeCnt_ms;//��ʱ��2���ڼ�����־
u32 DisplayTimeCntCmpArr[100] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};//��ʱ��2���ڼ����Ƚϱ�־����
u8 DisplayTimeCntCmpArr_len = 10;
void timer2_int (void) interrupt TIMER2_VECTOR
{
    DisplayTimeCnt_ms++;

    if(arrIndex < DisplayTimeCntCmpArr_len && DisplayTimeCnt_ms >= DisplayTimeCntCmpArr[arrIndex])
    {
        arrIndex++;
        P06 = ~P06; 
    }
}
/********************* Timer3�жϺ���************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{
//	LED_flashTIMER3IntCallback();
}

/********************* Timer4�жϺ���************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{	
    LED_breathTIMER4IntCallback0x(PWM00);
    LED_breathTIMER4IntCallback0x(PWM01);
    LED_breathTIMER4IntCallback0x(PWM02);
    LED_breathTIMER4IntCallback0x(PWM03);
    LED_breathTIMER4IntCallback0x(PWM04);
    LED_breathTIMER4IntCallback0x(PWM05);
    LED_breathTIMER4IntCallback0x(PWM06);
    LED_breathTIMER4IntCallback0x(PWM07);

    LED_breathTIMER4IntCallback0x(PWM20);
    LED_breathTIMER4IntCallback0x(PWM21);
    LED_breathTIMER4IntCallback0x(PWM22);
    LED_breathTIMER4IntCallback0x(PWM23);
    LED_breathTIMER4IntCallback0x(PWM24);
    LED_breathTIMER4IntCallback0x(PWM25);
    LED_breathTIMER4IntCallback0x(PWM26);
    LED_breathTIMER4IntCallback0x(PWM27);
}


//========================================================================
// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		Timer0_Stop();		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		Timer0_InterruptEnable();	//�����ж�
		else		Timer0_InterruptDisable();	//��ֹ�ж�
		if(TIMx->TIM_Priority > Priority_3)	return 2;	//����
		Timer0_Priority(TIMx->TIM_Priority);	//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: ��������16λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer0_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer0_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer0_AsCounter();	//����������Ƶ
		else		Timer0_AsTimer();	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	Timer0_CLKO_Enable();	//���ʱ��
		else		Timer0_CLKO_Disable();	//�����ʱ��
		
		T0_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer0_Run();	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		Timer1_Stop();		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		Timer1_InterruptEnable();	//�����ж�
		else		Timer1_InterruptDisable();	//��ֹ�ж�
		if(TIMx->TIM_Priority > Priority_3)	return 2;	//����
		Timer1_Priority(TIMx->TIM_Priority);	//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x30) | (TIMx->TIM_Mode<<4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: ֹͣ����
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer1_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer1_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer1_AsCounter();	//����������Ƶ
		else		Timer1_AsTimer();	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	Timer1_CLKO_Enable();	//���ʱ��
		else		Timer1_CLKO_Disable();	//�����ʱ��
		
		T1_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer1_Run();	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		Timer2_Stop();	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		Timer2_InterruptEnable();	//�����ж�
		else		Timer2_InterruptDisable();	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer2_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer2_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer2_AsCounter();	//����������Ƶ
		else		Timer2_AsTimer();		//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	Timer2_CLKO_Enable();		//���ʱ��
		else		Timer2_CLKO_Disable();	//�����ʱ��

		T2_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer2_Run();	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer3)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		Timer3_Stop();	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		Timer3_InterruptEnable();	//�����ж�
		else		Timer3_InterruptDisable();	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer3_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer3_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer3_AsCounter();	//����������Ƶ
		else		Timer3_AsTimer();		//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	Timer3_CLKO_Enable();		//���ʱ��
		else		Timer3_CLKO_Disable();	//�����ʱ��

		T3_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer3_Run();	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer4)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		Timer4_Stop();	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		Timer4_InterruptEnable();	//�����ж�
		else		Timer4_InterruptDisable();	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	Timer4_12T();	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		Timer4_1T();	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	Timer4_AsCounter();	//����������Ƶ
		else		Timer4_AsTimer();		//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	Timer4_CLKO_Enable();		//���ʱ��
		else		Timer4_CLKO_Disable();	//�����ʱ��

		T4_Load(TIMx->TIM_Value);
		if(TIMx->TIM_Run == ENABLE)	Timer4_Run();	//��ʼ����
		return	0;		//�ɹ�
	}
	return 2;	//����
}
