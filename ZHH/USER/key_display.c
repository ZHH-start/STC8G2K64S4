#include "key_display.h"

#include "drive_5x4keyboard.h"
#include "drive_oled.h"

uint16 Set_number_flag = 0; // 0Ϊ�¶ȣ�1Ϊʪ��

void key_display()
{
    while (key_scan() == ENT_key) {
        Set_choose_flag();
        while (key_scan() == ENT_key) {
            if (Set_number_flag == 0) {
            }
        }
    }
}

// ѡ��Ҫ���õĲ������¶Ȼ���ʪ��
void Set_choose_flag()
{
    if (key_scan() == up_arror_key) Set_number_flag = 0;
    if (key_scan() == down_arror_key) Set_number_flag = 1;

    if (Set_number_flag == 0)
        WS_OLED_Printf(7, 0, 0, "       ");
    if (Set_number_flag == 1)
        WS_OLED_Printf(7, 1, 0, "      ");
}