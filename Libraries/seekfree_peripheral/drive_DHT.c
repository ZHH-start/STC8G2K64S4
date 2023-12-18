#include "drive_oled.h"
#include "drive_DHT.h"
#include "zf_delay.h"
#include "stdio.h"
#include "zf_gpio.h"
#include "board.h"

uint16 DHT_receive_data[4];
sbit Data = P0 ^ 4; // ������

// �������Ϳ�ʼ�ź�
void DHT11_Start(void)
{
    gpio_mode(Data, GPIO);

    Data = 1; // ������
    delay_us(15);
    Data = 0; // ���͵�ƽ����18us
    delay_ms(20);
    Data = 1; // ���ߵ�ƽ20~40us
    delay_us(15);

    gpio_mode(P26, GPI_IMPEDANCE); // ����Ϊ����
}

// ��ȡһ���ֽ�
char DHT11_Rec_Byte(void)
{
    uint8 i = 0;
    uint8 get_data;

    for (i = 0; i < 8; i++) // 1�����ݾ���1���ֽ�byte��1���ֽ�byte��8λbit
    {
        while (Data == 0)
            ;         // ��1bit��ʼ���͵�ƽ��ߵ�ƽ���ȴ��͵�ƽ����
        delay_us(15); // �ӳ�30us��Ϊ����������0������1��0ֻ��26~28us

        get_data <<= 1; // ����

        if (Data == 1) // �������30us���Ǹߵ�ƽ�Ļ���������1
        {
            get_data |= 1; // ����+1
        }

        while (Data == 1)
            ; // �ߵ�ƽ��͵�ƽ���ȴ��ߵ�ƽ����
    }

    return get_data;
}

// ��ȡ����
void DHT11_REC_Data(void)
{
    unsigned int R_H, R_L, T_H, T_L;
    unsigned char RH, RL, TH, TL, CHECK;

    // DisableGlobalIRQ(); // �ر����ж�
    DHT11_Start(); // ���������ź�

    if (Data == 0) // �ж�DHT11�Ƿ���Ӧ
    {
        while (Data == 0)
            ; // �͵�ƽ��ߵ�ƽ���ȴ��͵�ƽ����
        while (Data == 1)
            ; // �ߵ�ƽ��͵�ƽ���ȴ��ߵ�ƽ����

        R_H   = DHT11_Rec_Byte();
        R_L   = DHT11_Rec_Byte();
        T_H   = DHT11_Rec_Byte();
        T_L   = DHT11_Rec_Byte();
        CHECK = DHT11_Rec_Byte(); // ����5������

        if (Data == 0)
            // WS_OLED_Printf(1, 0, 0, "receive over");
            ;         // �����һbit���ݴ�����Ϻ�DHT11�������� 50us
        delay_us(22); // ������ʱ55us
        if (Data == 1)
            ;
        // WS_OLED_Printf(1, 0, 0, "DHT close");
        // ��������������������߽������״̬��

        if (R_H + R_L + T_H + T_L == CHECK) // �ͼ���λ�Աȣ��ж�У����յ��������Ƿ���ȷ
        {
            RH = R_H;
            RL = R_L;
            TH = T_H;
            TL = T_L;
        }
    }

    // EnableGlobalIRQ(); // �����ж�

    DHT_receive_data[0] = RH;
    DHT_receive_data[1] = RL;
    DHT_receive_data[2] = TH;
    DHT_receive_data[3] = TL;
}
