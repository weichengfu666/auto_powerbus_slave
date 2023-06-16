#ifndef __ZONGZHIXIN_H__
#define __ZONGZHIXIN_H__

#define packArrLen  16

typedef struct {
    u32    packAddr;                      //效果包地址
    u16    packLen;                       //效果包长度
}PackTypeDef;

typedef struct {
    u8     state;                          //从机状态：1在线，0掉线
    u8     serialArr [ 5 ];              //初始序列号
    u8     assignArr [ 2 ];            //赋值序列号
    u8              packSize;              //效果包数量
    PackTypeDef     packArr[ packArrLen ];              //16个效果包
}SlaveTypeDef;

typedef enum {
    slave_addr = 0x0000                                                                            //从机结构体地址
}FlashAddr_typedef;

extern SlaveTypeDef Slave;                          //从机结构体：105字节

extern code uint LiangDuDuiZhao[101];
extern uchar JiHuo[2],ZhuJiJieShou_HuanCun[3][20],ZhuJiJieShou_HuanCun_i[3],SouXunXuLie_Time,BiaoHaoFuZhi_Time;
extern char LiangDu_DangQian,LiangDu_ChuShi,LiangDu_JieShu;
extern ulong Delay_Time[5],MuBiao_Time[5],JianBian_Time1,JianBian_Time2;
extern uint GongNen_Addr_Shou[5],GongNen_Addr_Wei[5],XunHuan_Changdu,XunHuan_ZhiZhen,XunHuan_Addr;
extern long LiangDu_HuanCun;
extern uint  Time,Time_i;
extern u8 EEPROM_ChuShi[2];

void FenJi_Init(void);
void ZhiLinZhiXing(uchar *GongNeng_HuanCun,uchar FanHui_Flag);
void XiaoGuo_ZhiXin(uint XiaoGouHao);
void ZongZhiXin(void);
void JianBian(void);
void XunHuanTinZhi(void);

#endif 