#include "main.h"

bit ADck_YinDa=0;                 /*应答标志位*/
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
                     起动总线函数               
函数原型: void  Start_I2c();  
功能:     启动I2C总线,即发送I2C起始条件.  
********************************************************************/
void AD_Start_I2c()
{
  	ADSDA=1;         /*发送起始条件的数据信号*/
  	AD_Delay10us();
  	ADSCL=1;
  	AD_Delay10us();       /*起始条件建立时间大于4.7us,延时*/  
  	ADSDA=0;         /*发送起始信号*/
  	AD_Delay10us();      
  	ADSCL=0;       /*钳住I2C总线，准备发送或接收数据 */
  	AD_Delay10us();
}
/*******************************************************************
                      结束总线函数               
函数原型: void  Stop_I2c();  
功能:     结束I2C总线,即发送I2C结束条件.  
********************************************************************/
void AD_Stop_I2c()
{
  	ADSDA=0;      /*发送结束条件的数据信号*/
  	AD_Delay10us();       /*发送结束条件的时钟信号*/
  	ADSCL=1;      /*结束条件建立时间大于4μs*/
  	AD_Delay10us();
  	ADSDA=1;      /*发送I2C总线结束信号*/
  	AD_Delay10us();
}
/*******************************************************************
                 字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:     将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
          此状态位进行操作.(不应答或非应答都使ack=0)     
           发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
********************************************************************/
void AD_SendByte(unsigned char  c)
{
 	unsigned char  BitCnt;
	for(BitCnt=0;BitCnt<8;BitCnt++)  /*要传送的数据长度为8位*/
    {
     	if((c<<BitCnt)&0x80)
			ADSDA=1;               /*判断发送位*/
       	else  ADSDA=0;                
     	AD_Delay10us();
     	ADSCL=1;               /*置时钟线为高，通知被控器开始接收数据位*/
      	AD_Delay10us();        
     	ADSCL=0; 
    }
    AD_Delay10us();
    ADSDA=1;                /*8位发送完后释放数据线，准备接收应答位*/
    AD_Delay10us();   
    ADSCL=1;
    AD_Delay10us();
    if(ADSDA==1)
		ADck_YinDa=0;     
       else ADck_YinDa=1;        /*判断是否接收到应答信号*/
    ADSCL=0;
    AD_Delay10us();
} 
/*******************************************************************
                 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能:        用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
          发完后请用应答函数应答从机。  
********************************************************************/    
unsigned char AD_RcvByte()
{
  	unsigned char  retc;
  	unsigned char  BitCnt;
  
  	retc=0; 
  	ADSDA=1;                     /*置数据线为输入方式*/
  	for(BitCnt=0;BitCnt<8;BitCnt++)
    {
   		AD_Delay10us();           
        ADSCL=0;                  /*置时钟线为低，准备接收数据位*/
        AD_Delay10us();
        ADSCL=1;                  /*置时钟线为高使数据线上数据有效*/
        AD_Delay10us();
        retc=retc<<1;
        if(ADSDA==1)retc=retc+1;  /*读数据位,接收的数据位放入retc中 */
        AD_Delay10us(); 
      }
  ADSCL=0;    
  AD_Delay10us();
  return(retc);
}

/********************************************************************
                     应答子函数
函数原型:  void Ack_I2c(bit a);
功能:      主控器进行应答信号(可以是应答或非应答信号，由位参数a决定)
********************************************************************/
void AD_Ack_I2c(bit a)
{
  
  	if(a==0)ADSDA=0;              /*在此发出应答或非应答信号 */
  	else ADSDA=1;
 	AD_Delay10us();      
  	ADSCL=1;
  	AD_Delay10us();  
  	ADSCL=0;                     /*清时钟线，钳住I2C总线以便继续接收*/
  	AD_Delay10us();    
}

/*******************************************************************
DAC 变换, 转化函数               
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   AD_Start_I2c();              //启动总线
   AD_SendByte(sla);            //发送器件地址
   if(ADck_YinDa==0)return(0);
   AD_SendByte(c);              //发送控制字节
   if(ADck_YinDa==0)return(0);
   AD_SendByte(Val);            //发送DAC的数值  
   if(ADck_YinDa==0)return(0);
   AD_Stop_I2c();               //结束总线
   return(1);
}
/*******************************************************************
ADC发送字节[命令]数据函数               
*******************************************************************/
bit AD_ISendByte(unsigned char sla,unsigned char c)
{
   AD_Start_I2c();              //启动总线
   AD_SendByte(sla);            //发送器件地址
   if(ADck_YinDa==0)return(0);
   AD_SendByte(c);              //发送数据
   if(ADck_YinDa==0)return(0);
   AD_Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC读字节数据函数               
*******************************************************************/
unsigned char AD_IRcvByte(unsigned char sla)
{  unsigned char c;

   AD_Start_I2c();          //启动总线
   AD_SendByte(sla+1);      //发送器件地址
   if(ADck_YinDa==0)return(0);
   c=AD_RcvByte();          //读取数据0

   AD_Ack_I2c(1);           //发送非就答位
   AD_Stop_I2c();           //结束总线
   return(c);
}

void ADMoKuai_DuQu(void)
{
	AD_ShuJu[4]=100;
//	switch(AD_CHANNEL)
//	{
//		case 0: AD_ISendByte(PCF8591,0x41);
//		     AD_ShuJu[0]=AD_IRcvByte(PCF8591);  //ADC0 模数转换1      光敏电阻
//			 break;  
//		
//		case 1: AD_ISendByte(PCF8591,0x42);
//		     AD_ShuJu[1]=AD_IRcvByte(PCF8591);  //ADC1  模数转换2	  热敏电阻
//			 break;  
//		
//		case 2: AD_ISendByte(PCF8591,0x43);
//		     AD_ShuJu[2]=AD_IRcvByte(PCF8591);  //ADC2	模数转换3	   悬空
//			 break;  
//		
//		case 3: AD_ISendByte(PCF8591,0x40);
//		     AD_ShuJu[3]=AD_IRcvByte(PCF8591);  //ADC3   模数转换4	   可调0-5v
//			 break;  
//		
//		case 4:	DACconversion(PCF8591,0x40,AD_ShuJu[4]); //DAC	  数模转换
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