#include "board.h"
#include "zf_pca_delay.h"
#include "zf_uart.h"
#include "zf_tim.h"
#include "zf_iic.h"
#include "drive_oled.h"
#include "stdio.h"

// 22.11MHz��IRC�����Ĵ��� 0xFB
// 24MHz��IRC�����Ĵ��� 0xFB
#define IRC_22M (*((uint8 idata *)0xFA))
#define IRC_24M (*((uint8 idata *)0xFB))

// ϵͳƵ�ʱ���
uint32 sys_clk = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡϵͳƵ��
//  @param      NULL          	��ֵ
//  @return     void        	ϵͳƵ��
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 get_clk(void)
{
    uint32 temp_count;

    P_SW2 |= 0x80;

    if (IRCBAND)
        temp_count = 36000000UL + ((int32)((int32)IRTRIM - (int32)IRC_22M) * 0x128E0UL); // Ƶ�ʵ�ƫ��,������������
    else
        temp_count = 24000000UL + ((int32)((int32)IRTRIM - (int32)IRC_24M) * 0xBB80UL); // Ƶ�ʵ�ƫ��,������������

    temp_count /= CLKDIV; // Ƶ��̫����Ҫ��Ƶ

    if (temp_count < 5764800UL)
        return 5529600UL;
    else if (temp_count < 8529600UL)
        return 6000000UL;
    else if (temp_count < 11529600UL)
        return 11059200UL;
    else if (temp_count < 15216000UL)
        return 12000000UL;
    else if (temp_count < 19216000UL)
        return 18432000UL;
    else if (temp_count < 21059200UL)
        return 20000000UL;
    else if (temp_count < 23059200UL)
        return 22118400UL;
    else if (temp_count < 25500000UL)
        return 24000000UL;
    else if (temp_count < 28500000UL)
        return 27000000UL;
    else if (temp_count < 31500000UL)
        return 30000000UL;
    else if (temp_count < 33500000UL)
        return 33177600UL;
    else
        return 35000000UL;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʼ���ڲ��Ĵ���
//  @param      NULL          	��ֵ
//  @return     void        	ϵͳƵ��
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void board_init(void)
{
// ��ȡϵͳƵ��
#if (0 == FOSC)
    sys_clk = get_clk();
#else
    sys_clk = FOSC;
#endif

#if (1 == EXTERNAL_CRYSTA_ENABLE)
    P_SW2  = 0x80;
    XOSCCR = 0xc0; // �����ⲿ����
    while (!(XOSCCR & 1))
        ;          // �ȴ�ʱ���ȶ�
    CLKDIV = 0x00; // ʱ�Ӳ���Ƶ
    CKSEL  = 0x01; // ѡ���ⲿ����
    P_SW2  = 0x00;
#endif
    P0M0   = 0x00;
    P0M1   = 0x00;
    P1M0   = 0x00;
    P1M1   = 0x00;
    P2M0   = 0x00;
    P2M1   = 0x00;
    P3M0   = 0x00;
    P3M1   = 0x00;
    P4M0   = 0x00;
    P4M1   = 0x00;
    P5M0   = 0x00;
    P5M1   = 0x00;
    CCON   = 0x00;
    CMOD   = 0x00; // PCA ʱ��Ϊϵͳʱ�� /12
    ADCCFG = 0;
    AUXR   = 0;
    SCON   = 0;
    S2CON  = 0;
    S3CON  = 0;
    S4CON  = 0;
    P_SW1  = 0;
    P_SW2  = 0;
    IE2    = 0;
    TMOD   = 0;
    CL     = 0;
    CH     = 0;
    P_SW2 |= 0x80;
    //	printf("oled_init");
}

#if (1 == PRINTF_ENABLE) // ��ʼ�����Դ���
// �ض���printf ���� ֻ�����uint16
char putchar(char c)
{
    uart_putchar(UART_1, (uint8)c); // ���Լ�ʵ�ֵĴ��ڴ�ӡһ�ֽ����ݵĺ����滻������
    return c;
}
#endif

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʧ���ⲿ�ж�
//  @param      NULL
//  @return     NULL
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void DisableGlobalIRQ(void)
{
    EA = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ���ⲿ�ж�
//  @param      NULL
//  @return     NULL
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void EnableGlobalIRQ(void)
{
    EA = 1;
}