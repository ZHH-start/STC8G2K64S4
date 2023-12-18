#include "drive_oled.h"
#include "drive_DHT.h"
#include "zf_delay.h"
#include "stdio.h"
#include "zf_gpio.h"
#include "board.h"

uint16 DHT_receive_data[4];
sbit Data = P0 ^ 4; // 数据线

// 主机发送开始信号
void DHT11_Start(void)
{
    gpio_mode(Data, GPIO);

    Data = 1; // 先拉高
    delay_us(15);
    Data = 0; // 拉低电平至少18us
    delay_ms(20);
    Data = 1; // 拉高电平20~40us
    delay_us(15);

    gpio_mode(P26, GPI_IMPEDANCE); // 设置为输入
}

// 获取一个字节
char DHT11_Rec_Byte(void)
{
    uint8 i = 0;
    uint8 get_data;

    for (i = 0; i < 8; i++) // 1个数据就是1个字节byte，1个字节byte有8位bit
    {
        while (Data == 0)
            ;         // 从1bit开始，低电平变高电平，等待低电平结束
        delay_us(15); // 延迟30us是为了区别数据0和数据1，0只有26~28us

        get_data <<= 1; // 左移

        if (Data == 1) // 如果过了30us还是高电平的话就是数据1
        {
            get_data |= 1; // 数据+1
        }

        while (Data == 1)
            ; // 高电平变低电平，等待高电平结束
    }

    return get_data;
}

// 获取数据
void DHT11_REC_Data(void)
{
    unsigned int R_H, R_L, T_H, T_L;
    unsigned char RH, RL, TH, TL, CHECK;

    // DisableGlobalIRQ(); // 关闭总中断
    DHT11_Start(); // 主机发送信号

    if (Data == 0) // 判断DHT11是否响应
    {
        while (Data == 0)
            ; // 低电平变高电平，等待低电平结束
        while (Data == 1)
            ; // 高电平变低电平，等待高电平结束

        R_H   = DHT11_Rec_Byte();
        R_L   = DHT11_Rec_Byte();
        T_H   = DHT11_Rec_Byte();
        T_L   = DHT11_Rec_Byte();
        CHECK = DHT11_Rec_Byte(); // 接收5个数据

        if (Data == 0)
            // WS_OLED_Printf(1, 0, 0, "receive over");
            ;         // 当最后一bit数据传送完毕后，DHT11拉低总线 50us
        delay_us(22); // 这里延时55us
        if (Data == 1)
            ;
        // WS_OLED_Printf(1, 0, 0, "DHT close");
        // 随后总线由上拉电阻拉高进入空闲状态。

        if (R_H + R_L + T_H + T_L == CHECK) // 和检验位对比，判断校验接收到的数据是否正确
        {
            RH = R_H;
            RL = R_L;
            TH = T_H;
            TL = T_L;
        }
    }

    // EnableGlobalIRQ(); // 打开总中断

    DHT_receive_data[0] = RH;
    DHT_receive_data[1] = RL;
    DHT_receive_data[2] = TH;
    DHT_receive_data[3] = TL;
}
