#include "Key.h"

uint Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key1_Flag,Key2_Flag,Key3_Flag,Key4_Flag;
uint Key1_Time,Key2_Time,Key3_Time,Key4_Time;
uint Key1_Delay_Flag=0,Key2_Delay_Flag,Key3_Delay_Flag,Key4_Delay_Flag;
uchar Menu_Key1,Menu_Key2,Menu_Key3,Menu_Key4;
unsigned int Key1_Delay,Key2_Delay,Key3_Delay,Key4_Delay;

void Key(void)                                   		//按键扫描程序（随时执行）
{                                                
  if(Key1==Key_Open)                                    //扫描按键是否按下
  {                                   
    Key1_Delay_Flag=1;                           		//按键消抖定时器标志位打开
    if(Key1_Delay>=Key_Delay)                           //大于6*(Key_Time()执行间隔)毫秒
    {
      if(Key1==Key_Open)                                //再次检测
      {
        if(Key1_Flag==0)                         		//是否执行过单次按键执行程序检测
        {
          Menu_Key1=1;                           		//此为单次按键执行程序
        }
        Key1_Flag=1;                             		//单次按键执行程序完成标志
        if(Key1_Time>=Key_Tim)                       	//连续按键执行时间=100*(Key_Time()执行间隔)
        {
          if(Key_Flag1==1)                       		//连续按键执行检测  间隔=10*(Key_Time()执行间隔)
          {
            //Menu_Key1=1;                         		//连续按键执行内容
            //Key_Flag1=0;                         		//按键连续执行标志位重置
          }
        }
      }else{
      Key1_Delay_Flag=0;                         		//按键放开，计时器关闭
      }
    }
  }else{                                         		//单次按键执行标志位重置
	  Key1_Delay=0;
	  Key1_Flag=0;                                   		//按键放开，计时器关闭
	  Key1_Delay_Flag=0;
  }                                    
  if(Key2==Key_Open)                                    //扫描按键是否按下
  {                                   
    Key2_Delay_Flag=1;                           		//按键消抖定时器标志位打开
    if(Key2_Delay>=Key_Delay)                           //大于6*(Key_Time()执行间隔)毫秒
    {
      if(Key2==Key_Open)                                //再次检测
      {
        if(Key2_Flag==0)                         		//是否执行过单次按键执行程序检测
        {
          Menu_Key2=1;                           		//此为单次按键执行程序
        }
        Key2_Flag=1;                             		//单次按键执行程序完成标志
        if(Key2_Time>=Key_Tim)                       	//连续按键执行时间=100*(Key_Time()执行间隔)
        {
          if(Key_Flag2==1)                       		//连续按键执行检测  间隔=10*(Key_Time()执行间隔)
          {
            //Menu_Key2=1;                         		//连续按键执行内容
            //Key_Flag2=0;                         		//按键连续执行标志位重置
          }
        }
      }else{
      Key2_Delay_Flag=0;                         		//按键放开，计时器关闭
      }
    }
  }else{                                         		//单次按键执行标志位重置
	  Key2_Delay=0;
	  Key2_Flag=0;                                   		//按键放开，计时器关闭
	  Key2_Delay_Flag=0;
	  Menu_Key2=0;
  }                                 
//  if(Key3==Key_Open)                                    //扫描按键是否按下
//  {                                   
//    Key3_Delay_Flag=1;                           		//按键消抖定时器标志位打开
//    if(Key3_Delay>=Key_Delay)                           //大于6*(Key_Time()执行间隔)毫秒
//    {
//      if(Key3==Key_Open)                                //再次检测
//      {
//        if(Key3_Flag==0)                         		//是否执行过单次按键执行程序检测
//        {
//          Menu_Key3=1;                           		//此为单次按键执行程序
//        }
//        Key3_Flag=1;                             		//单次按键执行程序完成标志
//        if(Key3_Time>=Key_Tim)                       	//连续按键执行时间=100*(Key_Time()执行间隔)
//        {
//          if(Key_Flag3==1)                       		//连续按键执行检测  间隔=10*(Key_Time()执行间隔)
//          {
//            //Menu_Key2=1;                         		//连续按键执行内容
//            //Key_Flag2=0;                         		//按键连续执行标志位重置
//          }
//        }
//      }else{
//      Key3_Delay_Flag=0;                         		//按键放开，计时器关闭
//      }
//    }
//  }else{                                         		//单次按键执行标志位重置
//	  Key3_Delay=0;
//	  Key3_Flag=0;                                   		//按键放开，计时器关闭
//	  Key3_Delay_Flag=0;
//  }                            
//  if(Key4==Key_Open)                                    //扫描按键是否按下
//  {                                   
//    Key4_Delay_Flag=1;                           		//按键消抖定时器标志位打开
//    if(Key4_Delay>=Key_Delay)                           //大于6*(Key_Time()执行间隔)毫秒
//    {
//      if(Key4==Key_Open)                                //再次检测
//      {
//        if(Key4_Flag==0)                         		//是否执行过单次按键执行程序检测
//        {
//          Menu_Key4=1;                           		//此为单次按键执行程序
//        }
//        Key4_Flag=1;                             		//单次按键执行程序完成标志
//        if(Key4_Time>=Key_Tim)                       	//连续按键执行时间=100*(Key_Time()执行间隔)
//        {
//          if(Key_Flag4==1)                       		//连续按键执行检测  间隔=10*(Key_Time()执行间隔)
//          {
//            //Menu_Key2=1;                         		//连续按键执行内容
//            //Key_Flag2=0;                         		//按键连续执行标志位重置
//          }
//        }
//      }else{
//      Key4_Delay_Flag=0;                         		//按键放开，计时器关闭
//      }
//    }
//  }else{                                         		//单次按键执行标志位重置
//	  Key4_Delay=0;
//	  Key4_Flag=0;                                   		//按键放开，计时器关闭
//	  Key4_Delay_Flag=0;
//  }
}

void Key_Time(void)                         //按键时钟程序（放入10ms中断）
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