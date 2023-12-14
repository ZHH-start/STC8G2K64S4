#include "headfile.h"

void ESP8266_init(void)
{
    int i = 6;
    uart_init(UART_3, UART3_RX_P50, UART3_TX_P51, 115200, TIM_0);
    uart_putstr(UART_3, "AT+CWMODE=1\r\n", 13);
    // printf("open wifi init");
    pca_delay_ms(10);
    uart_putstr(UART_3, "AT+CWJAP=\"ZHH-xiaomi12s\",\"yae73rw1\"\r\n", 37);
    // printf("write wifi SSID and passport");
    while (i-- > 0) {
        pca_delay_ms(1000);
    }
    uart_putstr(UART_3, "AT+ATKCLDSTA=\"37740342569263156939\",\"01234567\"\r\n", 48);
    i = 6;
    while (i-- > 0) {
        pca_delay_ms(1000);
    }
    // uart_putstr(UART_3, "test1", 13);
}

void main()
{
    char str[20];
    DisableGlobalIRQ();
    board_init();
    EnableGlobalIRQ();

    pca_delay_init(); // PCA延时函数初始化
    uart_init(DEBUG_UART, DEBUG_UART_RX_PIN, DEBUG_UART_TX_PIN, DEBUG_UART_BAUD, DEBUG_UART_TIM);
    // DEBUG串口（串口1）初始化,波特率115200
    iic_init(IIC_1, IIC1_SCL_P15, IIC1_SDA_P14, 0xe8);
    OLED_Init();
    ESP8266_init();
    Ringtones_init();

    while (1) {
        DHT11_REC_Data();

        printf("温度：%d\r\n", DHT_receive_data[2]);
        printf("湿度：%d\r\n", DHT_receive_data[0]);

        sprintf(str, "温度:%d", DHT_receive_data[2]);
        uart_putstr(UART_3, str, 7);
        sprintf(str, "湿度:%d", DHT_receive_data[0]);
        uart_putstr(UART_3, str, 7);

        WS_OLED_Printf(0, 0, 0, "temperature:%d", DHT_receive_data[2]);
        WS_OLED_Printf(0, 1, 0, "humidity:%d", DHT_receive_data[0]);

        // printf("keyscanvalue:%d\r\n", key_scan());
        Ringtones_close();
        pca_delay_ms(1000);
        Ringtones_open();
    }
}
