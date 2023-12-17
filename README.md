# STC8G2K64S4
 基于STC8G2K64S4的温湿度控制系统
## 项目介绍
这是一个keil工程，基于STC8G2K64S4的温湿度控制系统。该工程完全使用了[逐飞 STC8H/STC8G/STC8A 智能车](https://www.stcmcudata.com/STC8F-DATASHEET/STC8H-STC8G-STC8A-%E6%99%BA%E8%83%BD%E8%BD%A6%E5%BC%80%E6%BA%90%E5%BA%93-%E9%80%90%E9%A3%9E%E7%A7%91%E6%8A%80.PDF)的官方库，部分驱动是移植或自己编写。该系统外设有iic协议OLED屏幕，DHT11-温湿度传感器，蜂鸣器，正点原子ESP-01模块，薄膜键盘。
## 我应该怎么使用？
你可以直接从ZHH文件夹内打开SEEKFREE.uvporj文件从而启动keil5 C51.注意，本工程使用keil5工具链，**不建议使用keil4编辑或编译**。另外由于本人开发环境是VScode+EIDE，因此使用keil5打开会出现没有包含头文件等情况，自行包含即可。

你也可以使用VScode搭配[EIDE](https://discuss.em-ide.com/)启动该工程，并为此项目配置你自己的工具链。

推荐使用VScode搭配EIDE。
## 这个项目的状态如何？
相关的外设驱动都已经完成，但功能还没有实现。具体外设功能情况如下
### iic协议OLED屏幕
驱动已完成，可以格式化输出字符，数字等。具体可用函数见Libraries-seekfree_peripheral-drive_oled.h文件。具体实现代码和函数使用方法见Libraries-seekfree_peripheral-drive_oled.c文件。使用的管脚为SCL-P15，SDA-P14.
### DHT11温湿度传感器
驱动已完成，可用函数是DHT11_REC_Data()，具体见iic驱动同路径的drive_DHT.c和drive_DHT.h文件。使用管脚为P04脚。
### 蜂鸣器

### 正点原子ESP-01模块
驱动已完成，在main.c内的ESP8266_init()函数内。
