#include "Key.h"

uint Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key1_Flag,Key2_Flag,Key3_Flag,Key4_Flag;
uint Key1_Time,Key2_Time,Key3_Time,Key4_Time;
uint Key1_Delay_Flag=0,Key2_Delay_Flag,Key3_Delay_Flag,Key4_Delay_Flag;
uchar Menu_Key1,Menu_Key2,Menu_Key3,Menu_Key4;
unsigned int Key1_Delay,Key2_Delay,Key3_Delay,Key4_Delay;

void Key(void)                                   		//����ɨ�������ʱִ�У�
{                                                
  if(Key1==Key_Open)                                    //ɨ�谴���Ƿ���
  {                                   
    Key1_Delay_Flag=1;                           		//����������ʱ����־λ��
    if(Key1_Delay>=Key_Delay)                           //����6*(Key_Time()ִ�м��)����
    {
      if(Key1==Key_Open)                                //�ٴμ��
      {
        if(Key1_Flag==0)                         		//�Ƿ�ִ�й����ΰ���ִ�г�����
        {
          Menu_Key1=1;                           		//��Ϊ���ΰ���ִ�г���
        }
        Key1_Flag=1;                             		//���ΰ���ִ�г�����ɱ�־
        if(Key1_Time>=Key_Tim)                       	//��������ִ��ʱ��=100*(Key_Time()ִ�м��)
        {
          if(Key_Flag1==1)                       		//��������ִ�м��  ���=10*(Key_Time()ִ�м��)
          {
            //Menu_Key1=1;                         		//��������ִ������
            //Key_Flag1=0;                         		//��������ִ�б�־λ����
          }
        }
      }else{
      Key1_Delay_Flag=0;                         		//�����ſ�����ʱ���ر�
      }
    }
  }else{                                         		//���ΰ���ִ�б�־λ����
	  Key1_Delay=0;
	  Key1_Flag=0;                                   		//�����ſ�����ʱ���ر�
	  Key1_Delay_Flag=0;
  }                                    
  if(Key2==Key_Open)                                    //ɨ�谴���Ƿ���
  {                                   
    Key2_Delay_Flag=1;                           		//����������ʱ����־λ��
    if(Key2_Delay>=Key_Delay)                           //����6*(Key_Time()ִ�м��)����
    {
      if(Key2==Key_Open)                                //�ٴμ��
      {
        if(Key2_Flag==0)                         		//�Ƿ�ִ�й����ΰ���ִ�г�����
        {
          Menu_Key2=1;                           		//��Ϊ���ΰ���ִ�г���
        }
        Key2_Flag=1;                             		//���ΰ���ִ�г�����ɱ�־
        if(Key2_Time>=Key_Tim)                       	//��������ִ��ʱ��=100*(Key_Time()ִ�м��)
        {
          if(Key_Flag2==1)                       		//��������ִ�м��  ���=10*(Key_Time()ִ�м��)
          {
            //Menu_Key2=1;                         		//��������ִ������
            //Key_Flag2=0;                         		//��������ִ�б�־λ����
          }
        }
      }else{
      Key2_Delay_Flag=0;                         		//�����ſ�����ʱ���ر�
      }
    }
  }else{                                         		//���ΰ���ִ�б�־λ����
	  Key2_Delay=0;
	  Key2_Flag=0;                                   		//�����ſ�����ʱ���ر�
	  Key2_Delay_Flag=0;
	  Menu_Key2=0;
  }                                 
//  if(Key3==Key_Open)                                    //ɨ�谴���Ƿ���
//  {                                   
//    Key3_Delay_Flag=1;                           		//����������ʱ����־λ��
//    if(Key3_Delay>=Key_Delay)                           //����6*(Key_Time()ִ�м��)����
//    {
//      if(Key3==Key_Open)                                //�ٴμ��
//      {
//        if(Key3_Flag==0)                         		//�Ƿ�ִ�й����ΰ���ִ�г�����
//        {
//          Menu_Key3=1;                           		//��Ϊ���ΰ���ִ�г���
//        }
//        Key3_Flag=1;                             		//���ΰ���ִ�г�����ɱ�־
//        if(Key3_Time>=Key_Tim)                       	//��������ִ��ʱ��=100*(Key_Time()ִ�м��)
//        {
//          if(Key_Flag3==1)                       		//��������ִ�м��  ���=10*(Key_Time()ִ�м��)
//          {
//            //Menu_Key2=1;                         		//��������ִ������
//            //Key_Flag2=0;                         		//��������ִ�б�־λ����
//          }
//        }
//      }else{
//      Key3_Delay_Flag=0;                         		//�����ſ�����ʱ���ر�
//      }
//    }
//  }else{                                         		//���ΰ���ִ�б�־λ����
//	  Key3_Delay=0;
//	  Key3_Flag=0;                                   		//�����ſ�����ʱ���ر�
//	  Key3_Delay_Flag=0;
//  }                            
//  if(Key4==Key_Open)                                    //ɨ�谴���Ƿ���
//  {                                   
//    Key4_Delay_Flag=1;                           		//����������ʱ����־λ��
//    if(Key4_Delay>=Key_Delay)                           //����6*(Key_Time()ִ�м��)����
//    {
//      if(Key4==Key_Open)                                //�ٴμ��
//      {
//        if(Key4_Flag==0)                         		//�Ƿ�ִ�й����ΰ���ִ�г�����
//        {
//          Menu_Key4=1;                           		//��Ϊ���ΰ���ִ�г���
//        }
//        Key4_Flag=1;                             		//���ΰ���ִ�г�����ɱ�־
//        if(Key4_Time>=Key_Tim)                       	//��������ִ��ʱ��=100*(Key_Time()ִ�м��)
//        {
//          if(Key_Flag4==1)                       		//��������ִ�м��  ���=10*(Key_Time()ִ�м��)
//          {
//            //Menu_Key2=1;                         		//��������ִ������
//            //Key_Flag2=0;                         		//��������ִ�б�־λ����
//          }
//        }
//      }else{
//      Key4_Delay_Flag=0;                         		//�����ſ�����ʱ���ر�
//      }
//    }
//  }else{                                         		//���ΰ���ִ�б�־λ����
//	  Key4_Delay=0;
//	  Key4_Flag=0;                                   		//�����ſ�����ʱ���ر�
//	  Key4_Delay_Flag=0;
//  }
}

void Key_Time(void)                         //����ʱ�ӳ��򣨷���10ms�жϣ�
{
  if(Key1_Flag==1)
  {
    Key1_Time++;
    if(Key1_Time%Key_Tim1==0)
    {
      Key_Flag1=1;
    }
  }else{
    Key1_Time=0;
  }
  if(Key1_Delay_Flag==1)
  {
    Key1_Delay++;
  }else{
    Key1_Delay=0;
  }

  if(Key2_Flag==1)
  {
    Key2_Time++;
    if(Key2_Time%Key_Tim1==0)
    {
      Key_Flag2=1;
    }
  }else{
    Key2_Time=0;
  }
  if(Key2_Delay_Flag==1)
  {
    Key2_Delay++;
  }else{
    Key2_Delay=0;
  }

  if(Key3_Flag==1)
  {
    Key3_Time++;
    if(Key3_Time%Key_Tim1==0)
    {
      Key_Flag3=1;
    }
  }else{
    Key3_Time=0;
  }
//  if(Key3_Delay_Flag==1)
//  {
//    Key3_Delay++;
//  }else{
//    Key3_Delay=0;
//  }
//
//  if(Key4_Flag==1)
//  {
//    Key4_Time++;
//    if(Key4_Time%Key_Tim1==0)
//    {
//      Key_Flag4=1;
//    }
//  }else{
//    Key4_Time=0;
//  }
//  if(Key4_Delay_Flag==1)
//  {
//    Key4_Delay++;
//  }else{
//    Key4_Delay=0;
//  }
}