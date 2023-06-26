#include "main.h"
uint ZongXunHuan_i=0,GongNen_i=0,GongNen_j=0,ZongZhiXin_i=0,ZongZhiXin_j=0;
ulong Delay_Time[5],MuBiao_Time[5],JianBian_Time1=0,JianBian_Time2=0;
uint Delay_Addr[5];
uint GongNen_Addr_Shou[5],GongNen_Addr_Wei[5],XunHuan_Changdu=0,XunHuan_ZhiZhen=0,XunHuan_Addr=0;
char LiangDu_ChuShi=0,LiangDu_JieShu=0,LiangDu_DangQian=0;
long LiangDu_HuanCun=0;
uchar BianHao_QingChu[2],SouXunXuLie_Time=0,BiaoHaoFuZhi_Time=0;
uint Time=0,Time_i=0;


SlaveTypeDef Slave = { 0 };

void FenJi_Init(void)
{	
	uchar ZhuJi_Init_i,ZhuJi_Init_j;
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<3;ZhuJi_Init_i++)
	{
		for(ZhuJi_Init_j=0;ZhuJi_Init_j<20;ZhuJi_Init_j++)
		{
			ZhuJiJieShou_HuanCun[ZhuJi_Init_i][ZhuJi_Init_j]=0;
		}
	}	
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<5;ZhuJi_Init_i++)
	{
		Delay_Time[ZhuJi_Init_i]=0;
		MuBiao_Time[ZhuJi_Init_i]=0;
		Delay_Addr[ZhuJi_Init_i]=0;
		GongNen_Addr_Shou[ZhuJi_Init_i]=0;
		GongNen_Addr_Wei[ZhuJi_Init_i]=0;
	}
    //��ʼ���ӻ��ṹ��
    {
        //��ȡ�ӻ��ṹ�嵽����
        EEPROM_Read_Str(0x0000,(u8*)&Slave,sizeof(Slave));
        //��ʼ�����к�
        Slave.serialArr[0] = 0x01;
        Slave.serialArr[1] = 0x00;
        Slave.serialArr[2] = 0x0a;
        Slave.serialArr[3] = 0x0a;
        Slave.serialArr[4] = 0x0a;
        //δ����ֵ��ţ���������
        if( Slave.assignArr[0] == 0xff && Slave.assignArr[1] == 0xff )
        {
            Slave.assignArr[0] = 0x00;
            Slave.assignArr[1] = 0x00;
        }
        //д�ӻ��ṹ�嵽flash
        EEPROM_Write_Str(0x0000,(u8*)&Slave,sizeof(Slave));   
    }

    ZhiLin_ChangDu[0x01-1] = 11; //��λ��Ѱģ�����к�
    ZhiLin_ChangDu[0x02-1] = 13; //��Ÿ�ֵ
    ZhiLin_ChangDu[0x06-1] = 8; //����Ч��ִ��
    ZhiLin_ChangDu[0x07-1] = 6; //������
    ZhiLin_ChangDu[0x0b-1] = 6; //���ӻ�����״̬
    
    ZhiLin_ChangDu[0x20-1] = 8;//LEDͨ��
    ZhiLin_ChangDu[0x21-1] = 8;//LED�ϵ�
    ZhiLin_ChangDu[0x22-1] = 9;//LED�����趨
    ZhiLin_ChangDu[0x23-1] = 13;//LED���ν���
    ZhiLin_ChangDu[0x24-1] = 16;//LEDѭ������
    ZhiLin_ChangDu[0x25-1] = 16;//LEDѭ����˸
    
    ZhiLin_ChangDu[0x30-1] = 8;//LOCKͨ��
    ZhiLin_ChangDu[0x31-1] = 8;//LOCK�ϵ�
    ZhiLin_ChangDu[0x32-1] = 11;//LOCK�Ϻ�ͨ
    ZhiLin_ChangDu[0x33-1] = 11;//LOCKͨ���
    
#ifdef LED
    LED_breathInit(LED1_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED2_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED3_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);  
    LED_breathInit(LED4_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED5_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED6_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED7_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);  
    LED_breathInit(LED8_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
#endif
#ifdef LOCK
    LOCK_Init( LOCK1_PORT, CLOSE, 0 );
    LOCK_Init( LOCK2_PORT, CLOSE, 0 );
    LOCK_Init( LOCK3_PORT, CLOSE, 0 );
    LOCK_Init( LOCK4_PORT, CLOSE, 0 );
    LOCK_Init( LOCK5_PORT, CLOSE, 0 );
    LOCK_Init( LOCK6_PORT, CLOSE, 0 );
    LOCK_Init( LOCK7_PORT, CLOSE, 0 );
    LOCK_Init( LOCK8_PORT, CLOSE, 0 );
#endif
}
void ZhiLinZhiXing(uchar *GongNeng_HuanCun,uchar FanHui_Flag)
{	
    //LED���Ʋ�����ʼ��
    u8 LEDx_PORT = LED1_PORT;
    u8 led_state = CLOSE;
    u8 light = 0x00;
    u16 periodBreathFlash1_cntCmp = 0x03e8;
    u16 periodChangeFlash2_cntCmp = 0x03e8;
    u8 waveBreathChangeFlash_low = 0;
    u8 waveBreathChangeFlash_high = 100;
    u8 waveBreathChangeFlash_start = 0;
    //��������Ʋ�����ʼ��
    u8 LOCKx_PORT = LED1_PORT;
    u8 lock_state = OPEN;
    u32 lock_delayTime = 0;
    //����ǹ㲥ָ���FanHui_Flag == 1, ������
    if( FanHui_Flag );
	switch(GongNeng_HuanCun[0])
	{
/*ͨ�ÿ���*/
		case 1: //��λ��Ѱģ�����к�
			if((GongNeng_HuanCun[1]&Slave.serialArr[0])==0)
				if((GongNeng_HuanCun[2]&Slave.serialArr[1])==0)
					if((GongNeng_HuanCun[3]&Slave.serialArr[2])==0)
						if((GongNeng_HuanCun[4]&Slave.serialArr[3])==0)
							if((GongNeng_HuanCun[5]&Slave.serialArr[4])==0)
							{
								if((Slave.assignArr[0]==0)&&(Slave.assignArr[1]==0))
								{
									SouXunXuLie_Time=1;
								}
							}
        break;
		case 2: //��Ÿ�ֵ a5 ff ff 02 cc 00 00 00 00 00 02 14 0c
			if((GongNeng_HuanCun[1]==Slave.serialArr[0])&&(GongNeng_HuanCun[2]==Slave.serialArr[1])&&(GongNeng_HuanCun[3]==Slave.serialArr[2])&&(GongNeng_HuanCun[4]==Slave.serialArr[3])&&(GongNeng_HuanCun[5]==Slave.serialArr[4]))
			{
				Slave.assignArr[0]=GongNeng_HuanCun[6];
				Slave.assignArr[1]=GongNeng_HuanCun[7];
                EEPROM_Write_Str(0x0000,(u8*)&Slave,sizeof(Slave));                   //д�ӻ��ṹ�嵽flash
				BiaoHaoFuZhi_Time=1;
			}
        break;
		case 6: //����Ч��ִ��
            //�ӻ�ִ��
            {
                LED_PACK_id = GongNeng_HuanCun[1] * 256 + GongNeng_HuanCun[2];
                if( LED_PACK_id == 0 )
                {
                    memcpy( &LED_displayPackArr[0][0], &GongNeng_HuanCun[2], PACKCOL );
                }
                LED_displayPackPlayer(LED_PACK_id);
            }
			//��������
			{
				FaSong_HuanCun[0]=6;
				FaSong_HuanCun[1]=Slave.assignArr[0];
				FaSong_HuanCun[2]=Slave.assignArr[1];
				ZhiLingFaSong(3);
			}
        break;//a5 ff ff 06 00 01 
		case 7: //������
            //�ӻ�ִ��
            {
				Slave.assignArr[0]=0x00;
				Slave.assignArr[1]=0x00;
                EEPROM_Write_Str(0x0000,(u8*)&Slave,sizeof(Slave));                   //д�ӻ��ṹ�嵽flash
            }
            //��������
            {
                FaSong_HuanCun[0]=7;
                FaSong_HuanCun[1]=Slave.assignArr[0];
                FaSong_HuanCun[2]=Slave.assignArr[1];
                ZhiLingFaSong(3);
            }
        break;//a5 ff ff 07 c2 41
        case 0x0b: //���ӻ�����״̬
            //��������
            {
                FaSong_HuanCun[0]=0x0b;
                FaSong_HuanCun[1]=Slave.assignArr[0];
                FaSong_HuanCun[2]=Slave.assignArr[1];
                ZhiLingFaSong(3);
            }
        break;
/*LEDģ�����*/
        case 0x20://LEDͨ��
            //�ӻ�ִ��
            {
                LEDx_PORT = GongNeng_HuanCun[1];
                led_state = GongNeng_HuanCun[2];
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LEDִ��״̬
				ZhiLingFaSong(5);
			}
        break;
        case 0x21://LED�ϵ�
            //�ӻ�ִ��
            {
                LEDx_PORT = GongNeng_HuanCun[1];//����˿�
                led_state = GongNeng_HuanCun[2];//LEDִ��״̬
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LEDִ��״̬
				ZhiLingFaSong(5);
			}
        break;
		case 0x22://LED�����趨
            //�ӻ�ִ��
            {
                LEDx_PORT = GongNeng_HuanCun[1];//����˿�
                led_state = GongNeng_HuanCun[2];//LEDִ��״̬
                light = GongNeng_HuanCun[3];//LED����ֵ
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LEDִ��״̬
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED����ֵ
				ZhiLingFaSong(6);
			}
        break;
		case 0x23://LED���ν���
            //�ӻ�ִ��
            {
                LEDx_PORT = GongNeng_HuanCun[1];//����˿�
                led_state = GongNeng_HuanCun[2];//LEDִ��״̬
                waveBreathChangeFlash_low = GongNeng_HuanCun[3];//LED��ʼ����ֵ
                periodChangeFlash2_cntCmp    = GongNeng_HuanCun[4]*0x10000 + GongNeng_HuanCun[5]*0x100 + GongNeng_HuanCun[6]*0x1;//LED����ʱ��
                waveBreathChangeFlash_high  = GongNeng_HuanCun[7];//LED��������ֵ
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LEDִ��״̬
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED��ʼ����ֵ
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];//LED����ʱ��
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
                FaSong_HuanCun[8]=GongNeng_HuanCun[6];
                FaSong_HuanCun[9]=GongNeng_HuanCun[7];//LED��������ֵ
				ZhiLingFaSong(10);
			} 
        break;
		case 0x24://LEDѭ������
            //�ӻ�ִ��
            {
                LEDx_PORT = GongNeng_HuanCun[1];//����˿�
                led_state = GongNeng_HuanCun[2];//LEDִ��״̬
                waveBreathChangeFlash_high = GongNeng_HuanCun[3];//LED�������ֵ
                waveBreathChangeFlash_low = GongNeng_HuanCun[4];//  LED�������ֵ
                periodBreathFlash1_cntCmp  = GongNeng_HuanCun[5]*0x10000 + GongNeng_HuanCun[6]*0x100 + GongNeng_HuanCun[7]*0x1;//LED��������
                waveBreathChangeFlash_start = ( ( GongNeng_HuanCun[8]*0x10000 + GongNeng_HuanCun[9]*0x100 + GongNeng_HuanCun[10]*0x1 ) * 200 ) / periodBreathFlash1_cntCmp;//LED��ʼʱ��
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LEDִ��״̬
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED�������ֵ
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];//LED�������ֵ
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];//LED��������
                FaSong_HuanCun[8]=GongNeng_HuanCun[6];
                FaSong_HuanCun[9]=GongNeng_HuanCun[7];
                FaSong_HuanCun[10]=GongNeng_HuanCun[8];//LED��ʼʱ��
                FaSong_HuanCun[11]=GongNeng_HuanCun[9];
                FaSong_HuanCun[12]=GongNeng_HuanCun[10];
				ZhiLingFaSong(13);
			}
        break;
		case 0x25://LEDѭ����˸
            //�ӻ�ִ��
            {
                LEDx_PORT = GongNeng_HuanCun[1];//����˿�
                led_state = GongNeng_HuanCun[2];//LEDִ��״̬
                periodBreathFlash1_cntCmp = GongNeng_HuanCun[3]*0x10000 + GongNeng_HuanCun[4]*0x100 + GongNeng_HuanCun[5]*0x1;//LED��ʱ��
                periodChangeFlash2_cntCmp  = GongNeng_HuanCun[6]*0x10000 + GongNeng_HuanCun[7]*0x100 + GongNeng_HuanCun[8]*0x1;//LED��ʱ��
                waveBreathChangeFlash_high  = GongNeng_HuanCun[9];//LED�������
                waveBreathChangeFlash_low = GongNeng_HuanCun[10];//LED�������
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LEDִ��״̬
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED��ʱ��
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
                FaSong_HuanCun[8]=GongNeng_HuanCun[6];//LED��ʱ��
                FaSong_HuanCun[9]=GongNeng_HuanCun[7];
                FaSong_HuanCun[10]=GongNeng_HuanCun[8];
                FaSong_HuanCun[11]=GongNeng_HuanCun[9];//LED�������
                FaSong_HuanCun[12]=GongNeng_HuanCun[10];//LED�������
				ZhiLingFaSong(13);
			} 
        break;
/*�����ģ�����*/
		case 0x30://�����ͨ��
            //�ӻ�ִ��
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCKִ��״̬
				ZhiLingFaSong(5);
			} 
        break;
		case 0x31://������ϵ�
            //�ӻ�ִ��
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCKִ��״̬
				ZhiLingFaSong(5);
			} 
        break;
		case 0x32://������Ϻ�ͨ
            //�ӻ�ִ��
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                lock_delayTime = GongNeng_HuanCun[3] * 0xffff + GongNeng_HuanCun[4] * 0xff + GongNeng_HuanCun[5] ;
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCKִ��״̬
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//��ʱʱ��
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
				ZhiLingFaSong(8);
			} 
        break;
		case 0x33://�����ͨ���
            //�ӻ�ִ��
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                lock_delayTime = GongNeng_HuanCun[3] * 0xffff + GongNeng_HuanCun[4] * 0xff + GongNeng_HuanCun[5] ;
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//��������
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//����֡
				FaSong_HuanCun[1]=Slave.assignArr[0];//���H
				FaSong_HuanCun[2]=Slave.assignArr[1];//���L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//����˿�
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCKִ��״̬
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//��ʱʱ��
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
				ZhiLingFaSong(8);
			} 
        break;
	}
}

void ZongZhiXin(void)
{	
	if(SouXunXuLie_Time>0)
	{
		SouXunXuLie_Time=0;
		FaSong_HuanCun[0]=1;
		ZhiLingFaSong(1);
	}
	if(BiaoHaoFuZhi_Time>5)
	{
		BiaoHaoFuZhi_Time=0;
		FaSong_HuanCun[0]=2;
		FaSong_HuanCun[1]=Slave.assignArr[0];
		FaSong_HuanCun[2]=Slave.assignArr[1];
		FaSong_HuanCun[3]=Slave.serialArr[0];
		FaSong_HuanCun[4]=Slave.serialArr[1];
		FaSong_HuanCun[5]=Slave.serialArr[2];
		FaSong_HuanCun[6]=Slave.serialArr[3];
		FaSong_HuanCun[7]=Slave.serialArr[4];
		ZhiLingFaSong(8);
	}
}



