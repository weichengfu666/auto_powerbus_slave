#include "main.h"

bit ADck_YinDa=0;                 /*Ӧ���־λ*/
unsigned char AD_CHANNEL;
unsigned int AD_ShuJu[32];

void AD_Delay10us()		//@20.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 47;
	while (--i);
}

/*******************************************************************
                     �����ߺ���               
����ԭ��: void  Start_I2c();  
����:     ����I2C����,������I2C��ʼ����.  
********************************************************************/
void AD_Start_I2c()
{
  	ADSDA=1;         /*������ʼ�����������ź�*/
  	AD_Delay10us();
  	ADSCL=1;
  	AD_Delay10us();       /*��ʼ��������ʱ�����4.7us,��ʱ*/  
  	ADSDA=0;         /*������ʼ�ź�*/
  	AD_Delay10us();      
  	ADSCL=0;       /*ǯסI2C���ߣ�׼�����ͻ�������� */
  	AD_Delay10us();
}
/*******************************************************************
                      �������ߺ���               
����ԭ��: void  Stop_I2c();  
����:     ����I2C����,������I2C��������.  
********************************************************************/
void AD_Stop_I2c()
{
  	ADSDA=0;      /*���ͽ��������������ź�*/
  	AD_Delay10us();       /*���ͽ���������ʱ���ź�*/
  	ADSCL=1;      /*������������ʱ�����4��s*/
  	AD_Delay10us();
  	ADSDA=1;      /*����I2C���߽����ź�*/
  	AD_Delay10us();
}
/*******************************************************************
                 �ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:     ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
          ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0)     
           ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void AD_SendByte(unsigned char  c)
{
 	unsigned char  BitCnt;
	for(BitCnt=0;BitCnt<8;BitCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
     	if((c<<BitCnt)&0x80)
			ADSDA=1;               /*�жϷ���λ*/
       	else  ADSDA=0;                
     	AD_Delay10us();
     	ADSCL=1;               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
      	AD_Delay10us();        
     	ADSCL=0; 
    }
    AD_Delay10us();
    ADSDA=1;                /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
    AD_Delay10us();   
    ADSCL=1;
    AD_Delay10us();
    if(ADSDA==1)
		ADck_YinDa=0;     
       else ADck_YinDa=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
    ADSCL=0;
    AD_Delay10us();
} 
/*******************************************************************
                 �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����:        �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
          ���������Ӧ����Ӧ��ӻ���  
********************************************************************/    
unsigned char AD_RcvByte()
{
  	unsigned char  retc;
  	unsigned char  BitCnt;
  
  	retc=0; 
  	ADSDA=1;                     /*��������Ϊ���뷽ʽ*/
  	for(BitCnt=0;BitCnt<8;BitCnt++)
    {
   		AD_Delay10us();           
        ADSCL=0;                  /*��ʱ����Ϊ�ͣ�׼����������λ*/
        AD_Delay10us();
        ADSCL=1;                  /*��ʱ����Ϊ��ʹ��������������Ч*/
        AD_Delay10us();
        retc=retc<<1;
        if(ADSDA==1)retc=retc+1;  /*������λ,���յ�����λ����retc�� */
        AD_Delay10us(); 
      }
  ADSCL=0;    
  AD_Delay10us();
  return(retc);
}

/********************************************************************
                     Ӧ���Ӻ���
����ԭ��:  void Ack_I2c(bit a);
����:      ����������Ӧ���ź�(������Ӧ����Ӧ���źţ���λ����a����)
********************************************************************/
void AD_Ack_I2c(bit a)
{
  
  	if(a==0)ADSDA=0;              /*�ڴ˷���Ӧ����Ӧ���ź� */
  	else ADSDA=1;
 	AD_Delay10us();      
  	ADSCL=1;
  	AD_Delay10us();  
  	ADSCL=0;                     /*��ʱ���ߣ�ǯסI2C�����Ա��������*/
  	AD_Delay10us();    
}

/*******************************************************************
DAC �任, ת������               
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   AD_Start_I2c();              //��������
   AD_SendByte(sla);            //����������ַ
   if(ADck_YinDa==0)return(0);
   AD_SendByte(c);              //���Ϳ����ֽ�
   if(ADck_YinDa==0)return(0);
   AD_SendByte(Val);            //����DAC����ֵ  
   if(ADck_YinDa==0)return(0);
   AD_Stop_I2c();               //��������
   return(1);
}
/*******************************************************************
ADC�����ֽ�[����]���ݺ���               
*******************************************************************/
bit AD_ISendByte(unsigned char sla,unsigned char c)
{
   AD_Start_I2c();              //��������
   AD_SendByte(sla);            //����������ַ
   if(ADck_YinDa==0)return(0);
   AD_SendByte(c);              //��������
   if(ADck_YinDa==0)return(0);
   AD_Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC���ֽ����ݺ���               
*******************************************************************/
unsigned char AD_IRcvByte(unsigned char sla)
{  unsigned char c;

   AD_Start_I2c();          //��������
   AD_SendByte(sla+1);      //����������ַ
   if(ADck_YinDa==0)return(0);
   c=AD_RcvByte();          //��ȡ����0

   AD_Ack_I2c(1);           //���ͷǾʹ�λ
   AD_Stop_I2c();           //��������
   return(c);
}

void ADMoKuai_DuQu(void)
{
	AD_ShuJu[4]=100;
//	switch(AD_CHANNEL)
//	{
//		case 0: AD_ISendByte(PCF8591,0x41);
//		     AD_ShuJu[0]=AD_IRcvByte(PCF8591);  //ADC0 ģ��ת��1      ��������
//			 break;  
//		
//		case 1: AD_ISendByte(PCF8591,0x42);
//		     AD_ShuJu[1]=AD_IRcvByte(PCF8591);  //ADC1  ģ��ת��2	  ��������
//			 break;  
//		
//		case 2: AD_ISendByte(PCF8591,0x43);
//		     AD_ShuJu[2]=AD_IRcvByte(PCF8591);  //ADC2	ģ��ת��3	   ����
//			 break;  
//		
//		case 3: AD_ISendByte(PCF8591,0x40);
//		     AD_ShuJu[3]=AD_IRcvByte(PCF8591);  //ADC3   ģ��ת��4	   �ɵ�0-5v
//			 break;  
//		
//		case 4:	DACconversion(PCF8591,0x40,AD_ShuJu[4]); //DAC	  ��ģת��
//		     break;
//	}
	AD_ISendByte(PCF8591,0x41);
	AD_ShuJu[0]+=AD_IRcvByte(PCF8591);
	AD_ISendByte(PCF8591,0x42);
	AD_ShuJu[1]+=AD_IRcvByte(PCF8591);
	AD_ISendByte(PCF8591,0x43);
	AD_ShuJu[2]+=AD_IRcvByte(PCF8591);
	AD_ISendByte(PCF8591,0x40);
	AD_ShuJu[3]+=AD_IRcvByte(PCF8591);
	AD_ShuJu[5]++;
	if(AD_ShuJu[5]>50)
	{
		AD_ShuJu[0]=AD_ShuJu[0]/50;
		AD_ShuJu[1]=AD_ShuJu[1]/50;
		AD_ShuJu[2]=AD_ShuJu[2]/50;
		AD_ShuJu[3]=AD_ShuJu[3]/50;
		Sendnum(AD_ShuJu[0]);
		SendData(' ');
		Sendnum(AD_ShuJu[1]);
		SendData(' ');
		Sendnum(AD_ShuJu[2]);
		SendData(' ');
		Sendnum(AD_ShuJu[3]);
		SendData(13);
		SendData(10);
		AD_ShuJu[0]=0;
		AD_ShuJu[1]=0;
		AD_ShuJu[2]=0;
		AD_ShuJu[3]=0;
		AD_ShuJu[5]=0;
	}
//	AD_CHANNEL++;
//	if(AD_CHANNEL>4)
//		AD_CHANNEL=0;
	
}