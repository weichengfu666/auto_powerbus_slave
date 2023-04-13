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
//I2C��ʼ�ź�
//**************************************
void I2C_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}
//**************************************
//I2Cֹͣ�ź�
//**************************************
void I2C_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}
//**************************************
//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
//**************************************
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}
//**************************************
//I2C����Ӧ���ź�
//**************************************
bit I2C_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
    return CY;
}
//**************************************
//��I2C���߷���һ���ֽ�����
//**************************************
void I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    I2C_RecvACK();
}
//**************************************
//��I2C���߽���һ���ֽ�����
//**************************************
uchar I2C_RecvByte()
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}
//**************************************
//��I2C�豸д��һ���ֽ�����
//**************************************
void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //��ʼ�ź�
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
}
//**************************************
//��I2C�豸��ȡһ���ֽ�����
//**************************************
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK(1);                //����Ӧ���ź�
	I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}
//**************************************
//��ʼ��MPU6050
//**************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG_6050, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//�ϳ�����
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
	return LL;   //�ϳ�����
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