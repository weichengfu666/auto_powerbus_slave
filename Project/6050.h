#ifndef __6050_H__
#define __6050_H__

//****************************************
// 定义51单片机端口
//****************************************
sbit    SCL=P2^3;			//IIC时钟引脚定义
sbit    SDA=P2^2;			//IIC数据引脚定义
sbit    INT=P4^3;
sbit    LED_R=P2^6;
sbit    LED_G=P4^5;
sbit    LED_B=P0^0;
sbit    LED_W=P2^4;
//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG_6050			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取

void Delay5us();
void I2C_Start();
void I2C_Stop();
void I2C_SendACK(bit ack);
bit I2C_RecvACK();
void I2C_SendByte(uchar dat);
uchar I2C_RecvByte();
void Single_WriteI2C(uchar REG_Address,uchar REG_data);
uchar Single_ReadI2C(uchar REG_Address);
void InitMPU6050();
float GetData(uchar REG_Address);
void mobangduqu(void);

#endif 