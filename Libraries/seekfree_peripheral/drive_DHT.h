#ifndef _DHT_drive_h
#define _DHT_drive_h

#include "common.h"

void DHT11_REC_Data();
// ��������
extern uint16 DHT_receive_data[4]; // �������ݣ�[2]�¶�[0]ʪ��
extern uint16 DHT_read_count;

#endif