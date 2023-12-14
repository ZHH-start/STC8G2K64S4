#include "drive_5x4keyboard.h"
#include "zf_delay.h"
#include "drive_oled.h"
#include "stdio.h"

#define GPIO_DIG P0
#define GPIO_KEY P1

uint8 KeyColValue;
uint8 KeyLineValue;

//  @param      mode        引脚模式 GPIO:准双向口, GPO_PP:推挽输出, GPI_IMPEDANCE:高阻输入, GPI_OD:开漏输出
//  @return     void
//  Sample usage:           gpio_mode(P0_0,GPIO);       // 设置P0.0设置为双向IO
//-------------------------------------------------------------------------------------------------------------------
// void gpio_mode(PIN_enum pin, GPIOMODE_enum mode)
// {
// }
//  @brief      GPIO设置引脚上拉电阻设置
//  @param      pin         选择引脚（P0_0-P5_4）
//  @param      pull        设置上下拉电阻 NOPULL:不设置 PULLUP:上拉
//  @return     void
//  Sample usage:           gpio_pull_set(P0_0,NOPULL);       // 设置P0.0引脚没有上下拉电阻
//-------------------------------------------------------------------------------------------------------------------
// void gpio_pull_set(PIN_enum pin, PULL_enum pull)

void Horizontal_GPIO_init()
{
    gpio_mode(P32, GPI_IMPEDANCE); // 高阻输入
    gpio_mode(P34, GPI_IMPEDANCE);
    gpio_mode(P36, GPI_IMPEDANCE);
    gpio_mode(P42, GPI_IMPEDANCE);
    gpio_mode(P44, GPI_IMPEDANCE);
    P32 = 0;
    P34 = 0;
    P36 = 0;
    P42 = 0;
    P44 = 0;
    gpio_mode(P27, GPO_PP);
    gpio_mode(P25, GPO_PP);
    gpio_mode(P23, GPO_PP);
    gpio_mode(P21, GPO_PP);
    P27 = 1;
    P25 = 1;
    P23 = 1;
    P21 = 1;
}

int Vertical_scanning()
{
    P27 = 0;
    P25 = 0;
    P23 = 0;
    P21 = 0;
    P32 = 1;
    P34 = 1;
    P36 = 1;
    P42 = 1;
    P44 = 1;
    if (P32 == 0) {
        delay_ms(43);
        if (P32 == 0) return 27;
    }
    if (P34 == 0) {
        delay_ms(43);
        if (P34 == 0) return 1;
    }
    if (P36 == 0) {
        delay_ms(43);
        if (P36 == 0) return 4;
    }
    if (P42 == 0) {
        delay_ms(43);
        if (P42 == 0) return 7;
    }
    if (P44 == 0) {
        delay_ms(43);
        if (P44 == 0) return 17;
    }

    return 0;
}

int Horizontal_scanning()
{
    P27 = 1;
    P25 = 1;
    P23 = 1;
    P21 = 1;
    P32 = 0;
    P34 = 0;
    P36 = 0;
    P42 = 0;
    P44 = 0;
    if (P27 == 0) {
        delay_ms(43);
        if (P27 == 0) return 0;
    }
    if (P25 == 0) {
        delay_ms(43);
        if (P25 == 0) return 1;
    }
    if (P23 == 0) {
        delay_ms(43);
        if (P23 == 0) return 2;
    }
    if (P21 == 0) {
        delay_ms(43);
        if (P21 == 0) return 9;
    }

    return 0;
}

int key_scan()
{
    return Horizontal_scanning() + Vertical_scanning();
}

void key_scan_test()
{
    P27 = 0;
    P25 = 0;
    P23 = 0;
    P21 = 0;
    P32 = 1;
    P34 = 1;
    P36 = 1;
    P42 = 1;
    P44 = 1;
    if (P32 == 0) {
        delay_ms(43);
        if (P32 == 0)
            printf("14");
    }
    if (P34 == 0) {
        delay_ms(43);
        if (P34 == 0)
            printf("33");
    }
    if (P42 == 0) {
        delay_ms(43);
        if (P42 == 0)
            printf("57");
    }
    if (P36 == 0) {
        delay_ms(43);
        if (P36 == 0)
            printf("44");
    }
    if (P44 == 0) {
        delay_ms(43);
        if (P44 == 0)
            printf("83");
    }
}

// void Vertical_GPIO_init()
// {
//     gpio_mode(P27, GPIO);
//     P27 = 1;
//     gpio_mode(P32, GPIO);
//     P32 = 1;
//     gpio_mode(P34, GPIO);
//     P34 = 1;
//     gpio_mode(P36, GPIO);
//     P36 = 1;
//     gpio_mode(P42, GPIO);
//     P42 = 1;
//     gpio_mode(P25, GPI_IMPEDANCE);
//     gpio_mode(P23, GPI_IMPEDANCE);
//     gpio_mode(P21, GPI_IMPEDANCE);
//     gpio_mode(P44, GPI_IMPEDANCE);
// }
