#ifndef _DHT_drive_h
#define _DHT_drive_h

#include "common.h"

void DHT11_REC_Data();
// 接收数据
extern uint16 DHT_receive_data[4]; // 储存数据

#endif