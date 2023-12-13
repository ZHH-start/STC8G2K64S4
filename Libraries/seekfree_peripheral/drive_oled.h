#ifndef __DRIVE_OLED_H__
#define __DRIVE_OLED_H__	

#include "common.h"

#define WS_Peripheral_OLED 1

/*-----------------OLED IIC�˿ڶ���----------------*/  	

//  ��ʾģʽ
#define WS_OLED_DIS_MODE_5X7   0
#define WS_OLED_DIS_MODE_8X16  1
#define WS_OLED_DIS_MODE_12X24 2
#define WS_OLED_DIS_MODE_16X32 3

// //  ����OLED��ʾ    
// void openOledDis(void);

// // �ر�OLED��ʾ     
// void closeOledDis(void); 

// ȫ��Ϩ��	  
void WS_OLED_Dis_Clear(void) ;

//    ����ȫ��
void WS_OLED_Dis_Full(void)  ;

//   ��ʼ��
void   OLED_Init(void );

//   �ַ�����ʾ
//void WS_OLED_Dis_String(int  x,int   y,   char disMode, char  *string);

//   ��ʽ����ʾ,disMode :  0->5*7  ; 1->8*16 ; 2->12*24 ; 3->16*32
void WS_OLED_Printf(int  x,int  y, char disMode , char *p,... );

//     ��������
void   setOledPoint(int  x, int  y) ;
void   writeOledData(unsigned char dat);

#endif