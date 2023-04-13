#ifndef __ANNIUSAOMIAO_H__
#define __ANNIUSAOMIAO_H__

sbit ANNIU_1_7 = P1^5;
sbit ANNIU_8_14 = P1^6;
sbit ANNIU_15_21 = P1^7;
sbit ANNIU_22_28 = P5^4;
sbit ANNIU_29_35 = P4^5;
sbit ANNIU_36_42 = P2^7;
sbit SHURU_1 = P2^6;
sbit SHURU_2 = P2^5;
sbit SHURU_3 = P2^4;
sbit SHURU_4 = P2^3;
sbit SHURU_5 = P2^2;
sbit SHURU_6 = P2^0;
sbit SHURU_7 = P2^1;

#define saomiao1_IO P1M1=0xc0;P1M0=0x3f;P5M1=0xff;P5M0=0x00;P4M1=0xe9;P4M0=0x16;P2M1=0xff;P2M0=0x00;
#define saomiao2_IO P1M1=0xa0;P1M0=0x5f;P5M1=0xff;P5M0=0x00;P4M1=0xe9;P4M0=0x16;P2M1=0xff;P2M0=0x00;
#define saomiao3_IO P1M1=0x60;P1M0=0x9f;P5M1=0xff;P5M0=0x00;P4M1=0xe9;P4M0=0x16;P2M1=0xff;P2M0=0x00;
#define saomiao4_IO P1M1=0xe0;P1M0=0x1f;P5M1=0xef;P5M0=0x10;P4M1=0xe9;P4M0=0x16;P2M1=0xff;P2M0=0x00;
#define saomiao5_IO P1M1=0xe0;P1M0=0x1f;P5M1=0xff;P5M0=0x00;P4M1=0xc9;P4M0=0x36;P2M1=0xff;P2M0=0x00;
#define saomiao6_IO P1M1=0xe0;P1M0=0x1f;P5M1=0xff;P5M0=0x00;P4M1=0xe9;P4M0=0x16;P2M1=0x7f;P2M0=0x80;

void anniusaomiao(void);
void anniupanduan(void); 
void anniu_init(void);

#endif