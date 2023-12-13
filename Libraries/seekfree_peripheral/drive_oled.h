#ifndef __DRIVE_OLED_H__
#define __DRIVE_OLED_H__	

#include "common.h"

#define WS_Peripheral_OLED 1

/*-----------------OLED IIC端口定义----------------*/  	

//  显示模式
#define WS_OLED_DIS_MODE_5X7   0
#define WS_OLED_DIS_MODE_8X16  1
#define WS_OLED_DIS_MODE_12X24 2
#define WS_OLED_DIS_MODE_16X32 3

// //  开启OLED显示    
// void openOledDis(void);

// // 关闭OLED显示     
// void closeOledDis(void); 

// 全屏熄灭	  
void WS_OLED_Dis_Clear(void) ;

//    点亮全屏
void WS_OLED_Dis_Full(void)  ;

//   初始化
void   OLED_Init(void );

//   字符串显示
//void WS_OLED_Dis_String(int  x,int   y,   char disMode, char  *string);

//   格式化显示,disMode :  0->5*7  ; 1->8*16 ; 2->12*24 ; 3->16*32
void WS_OLED_Printf(int  x,int  y, char disMode , char *p,... );

//     设置坐标
void   setOledPoint(int  x, int  y) ;
void   writeOledData(unsigned char dat);

#endif