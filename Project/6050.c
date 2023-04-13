#include "main.h"
char angle_cishu=0,huayuanjishu[5]={0,0,0,0,0},fashe_flag=0;
int angle_lianxu=360;
uint huayuanshijian[5]={0,0,0,0,0};
int angle_yuanshijilu[7]={0,0,0,0,0,0,0};
void Delay5us()		//@20.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 22;
	while (--i);
}
//**************************************
//I2C起始信号
//**************************************
void I2C_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}
//**************************************
//I2C停止信号
//**************************************
void I2C_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}
//**************************************
//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
//**************************************
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}
//**************************************
//I2C接收应答信号
//**************************************
bit I2C_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
    return CY;
}
//**************************************
//向I2C总线发送一个字节数据
//**************************************
void I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    I2C_RecvACK();
}
//**************************************
//从I2C总线接收一个字节数据
//**************************************
uchar I2C_RecvByte()
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}
//**************************************
//向I2C设备写入一个字节数据
//**************************************
void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}
//**************************************
//从I2C设备读取一个字节数据
//**************************************
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}
//**************************************
//初始化MPU6050
//**************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG_6050, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//合成数据
//**************************************
float GetData(uchar REG_Address)
{
	char H,L;
	int HH;
	float LL;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	HH=((H<<8)+L);
	LL=(float)(HH/20);
	return LL;   //合成数据
}
void mobangduqu(void)
{
	char i=0;
	int tuoluoyi=0;
	//angle_yuanshijilu[1]=angle_yuanshijilu[0];
	angle_yuanshijilu[0]=GetData(ACCEL_ZOUT_H)+200;//atan2(GetData(ACCEL_ZOUT_H),GetData(ACCEL_YOUT_H))*58+180;
	angle_yuanshijilu[1]=GetData(ACCEL_YOUT_H);//atan2(GetData(ACCEL_XOUT_H),GetData(ACCEL_YOUT_H))*58+180;
	angle_yuanshijilu[2]=GetData(ACCEL_XOUT_H);
	if((angle_yuanshijilu[0]>650)&&((angle_yuanshijilu[1]<300)&&((angle_yuanshijilu[1]>-300)))&&((angle_yuanshijilu[2]<300)&&(angle_yuanshijilu[2]>-300)))
		angle_yuanshijilu[3]=1;	
	if((angle_yuanshijilu[0]<-650)&&((angle_yuanshijilu[1]<300)&&((angle_yuanshijilu[1]>-300)))&&((angle_yuanshijilu[2]<300)&&(angle_yuanshijilu[2]>-300)))
		angle_yuanshijilu[3]=2;	
	if((angle_yuanshijilu[1]>650)&&((angle_yuanshijilu[0]<300)&&((angle_yuanshijilu[0]>-300)))&&((angle_yuanshijilu[2]<300)&&(angle_yuanshijilu[2]>-300)))
		angle_yuanshijilu[3]=3;	
	if((angle_yuanshijilu[1]<-650)&&((angle_yuanshijilu[0]<300)&&((angle_yuanshijilu[0]>-300)))&&((angle_yuanshijilu[2]<300)&&(angle_yuanshijilu[2]>-300)))
		angle_yuanshijilu[3]=4;	
	if((angle_yuanshijilu[2]>650)&&((angle_yuanshijilu[1]<300)&&((angle_yuanshijilu[1]>-300)))&&((angle_yuanshijilu[0]<300)&&(angle_yuanshijilu[0]>-300)))
		angle_yuanshijilu[3]=5;	
	if((angle_yuanshijilu[2]<-650)&&((angle_yuanshijilu[1]<300)&&((angle_yuanshijilu[1]>-300)))&&((angle_yuanshijilu[0]<300)&&(angle_yuanshijilu[0]>-300)))
		angle_yuanshijilu[3]=6;	
	if(angle_yuanshijilu[3]!=angle_yuanshijilu[5])
	{
	 	angle_yuanshijilu[4]=1;
		angle_yuanshijilu[6]=0;
	}
	angle_yuanshijilu[5]=angle_yuanshijilu[3];
	if(angle_yuanshijilu[4]==1)
	{
		if(angle_yuanshijilu[3]==1)
		{
			LED_R=1;
			LED_G=0;
			LED_B=0;
			LED_W=0;
		}
		if(angle_yuanshijilu[3]==2)
		{
			LED_R=0;
			LED_G=1;
			LED_B=0;
			LED_W=0;
		}
		if(angle_yuanshijilu[3]==3)
		{
			LED_R=0;
			LED_G=0;
			LED_B=1;
			LED_W=0;
		}
		if(angle_yuanshijilu[3]==4)
		{
			LED_R=0;
			LED_G=0;
			LED_B=0;
			LED_W=1;
		}
		if(angle_yuanshijilu[3]==5)
		{
			LED_R=1;
			LED_G=1;
			LED_B=0;
			LED_W=0;
		}
		if(angle_yuanshijilu[3]==6)
		{
			LED_R=1;
			LED_G=0;
			LED_B=1;
			LED_W=0;
		}
	}
//	tuoluoyi=GeData(GYRO_XOUT_H);
////	for(i=49;i>0;i--)
////	{
////		angle_yuanshijilu[i]=angle_yuanshijilu[i-1]; 	
////	}				
//	if((angle_yuanshijilu[1]>130)&&(angle_yuanshijilu[0]<-130)&&(tuoluoyi<150)&&(tuoluoyi>-150))
//	{
//		angle_cishu++;	
//		for(i=0;i<5;i++)
//		{
//			if(huayuanjishu[i]>0)
//			{
//			 	huayuanjishu[i]++;
//				if(huayuanjishu[i]>3)
//				{
//					fashe_flag=1;
//				}
//			}
//		}
//		if(huayuanjishu[0]==0)
//		{
//		 	huayuanjishu[0]=1;
//			huayuanshijian[0]=1;
//		}else if(huayuanjishu[1]==0){
//			huayuanjishu[1]=1;
//			huayuanshijian[1]=1;
//		}else if(huayuanjishu[2]==0){
//			huayuanjishu[2]=1;
//			huayuanshijian[2]=1;
//		}else if(huayuanjishu[3]==0){
//			huayuanjishu[3]=1;
//			huayuanshijian[3]=1;
//		}else if(huayuanjishu[4]==0){
//			huayuanjishu[4]=1;
//			huayuanshijian[4]=1;
//		}						 	
//	}else if((angle_yuanshijilu[1]<-130)&&(angle_yuanshijilu[0]>130)&&(tuoluoyi<150)&&(tuoluoyi>-150)){
//		angle_cishu--;
//		for(i=0;i<5;i++)
//		{
//			if(huayuanjishu[i]<0)
//			{
//			 	huayuanjishu[i]--;
//				if(huayuanjishu[i]<-3)
//				{
//					fashe_flag=2;
//				}
//			}
//		}
//		if(huayuanjishu[0]==0)
//		{
//		 	huayuanjishu[0]=-1;
//			huayuanshijian[0]=1;
//		}else if(huayuanjishu[1]==0){
//			huayuanjishu[1]=-1;
//			huayuanshijian[1]=1;
//		}else if(huayuanjishu[2]==0){
//			huayuanjishu[2]=-1;
//			huayuanshijian[2]=1;
//		}else if(huayuanjishu[3]==0){
//			huayuanjishu[3]=-1;
//			huayuanshijian[3]=1;
//		}else if(huayuanjishu[4]==0){
//			huayuanjishu[4]=-1;
//			huayuanshijian[4]=1;
//		}
//	}
//	angle_lianxu=angle_cishu*360+angle_yuanshijilu[0];
//	
//	OutData[0]=fashe_flag*100;
//	OutData[1]=huayuanjishu[1]*100;
//	OutData[2]=huayuanjishu[2]*100;
//	OutData[3]=huayuanjishu[3]*100;
	//OutPut_Data();
}