# STC8G2K64S4
 基于STC8G2K64S4的温湿度控制系统
## 项目介绍
这是一个keil工程，基于STC8G2K64S4的温湿度控制系统。该工程完全使用了[逐飞 STC8H/STC8G/STC8A 智能车](https://www.stcmcudata.com/STC8F-DATASHEET/STC8H-STC8G-STC8A-%E6%99%BA%E8%83%BD%E8%BD%A6%E5%BC%80%E6%BA%90%E5%BA%93-%E9%80%90%E9%A3%9E%E7%A7%91%E6%8A%80.PDF)的官方库，部分驱动是移植或自己编写。该系统外设有iic协议OLED屏幕，DHT11-温湿度传感器，蜂鸣器，正点原子ESP-01模块和薄膜键盘。
## 我应该怎么使用？
你可以直接从ZHH文件夹内打开SEEKFREE.uvporj文件从而启动keil5 C51.注意，本工程使用keil5工具链，**不建议使用keil4编辑或编译**。另外由于本人开发环境是VScode+EIDE，因此使用keil5打开会出现没有包含头文件等情况，自行包含即可。

你也可以使用VScode搭配[EIDE](https://discuss.em-ide.com/)启动该工程，并为此项目配置你自己的工具链。

推荐使用VScode搭配EIDE。
## 这个项目的状态如何？
相关的外设驱动都已经完成，但功能还没有实现。具体外设功能情况如下
### iic协议OLED屏幕
驱动已完成，可以格式化输出字符，数字等。具体可用函数见drive_oled.h文件。具体实现代码和函数使用方法见drive_oled.c文件。使用的管脚为SCL-P15，SDA-P14.
### DHT11温湿度传感器
驱动已完成，可用函数是DHT11_REC_Data()，具体见iic驱动同路径的drive_DHT.c和drive_DHT.h文件。使用P04脚。
### 蜂鸣器
本人使用的是有源蜂鸣器，通电即响，使用简单的电平高低即可驱动。文件在drive_Ringtones.c和.h文件内，使用P40脚。需要注意单片机驱动能力弱，因此高电平要额外接供电，单片机P40置低响，置高不响。
### 正点原子ESP-01模块
驱动已完成，在main.c内的ESP8266_init()函数内。初始化相对简单，因此没有单独的驱动文件。ESP使用串口3，串口中断在autodown_interrupt.c内，还没有完成接受消息。

**使用串口发送指令时ESP会回复消息，可能导致缓存溢出，单片机反复重启。**
 
 ### 薄膜键盘
 驱动已经编写完成，具体代码在drive_5x4keyboard.c文件内。键盘扫描返回的是整数，具体每个按键返回的值和使用的pin如下表。

|<br />| p27 | p25 | p23 | p21 |
| --- | --- | --- | --- | --- |
| p32 | F1 | F2 | # | * |
| p34 | 1 | 2 | 3 | ↑ |
| p36 | 4 | 5 | 6 | ↓ |
| p42 | 7 | 8 | 9 | ESC |
| p44 | ← | 0 | → | ENT |

|<br />| 0 | 1 | 2 | 9 |
| --- | --- | --- | --- | --- |
| 27 | 27 | 28 | 29 | 36 |
| 1 | 1 | 2 | 3 | 10 |
| 4 | 4 | 5 | 6 | 13 |
| 7 | 7 | 8 | 9 | 16 |
| 17 | 17 | 18 | 19 | 26 |

## 杂项
### 关于ESP的使用
本项目使用了正点原子官方服务[原子云](https://cloud.alientek.com/)。因此ESP初始化十分简单，在初始化函数的相关代码中添加WiFi名称和密码、原子云设备编号和密码即可使用。具体使用方法请自行查找。
### 关于下载
该单片机可以自动下载，具体代码已经包含在autodown_interrupt.c文件内，原理是在串口1接收中断内判断传入值。如果为20个0x7f则将单片机复位到下载引导，从而实现自动下载。
### 关于延时
该单片机运行在33.xxxx频率下，下载时务必先调整下载器到对应频率。延时可以通过pca计时器也可以手动循环延时，但是zf_delay文件内的delay_us()函数由于传入整数问题，延时时间会长一倍。因此在DHT驱动文件内也对应的将us延时传入数减半。使用us延时时需要注意。
### 关于中断
DHT11的读取时序十分严格。目前工程内的定时中断任务只有自动下载，如果加入了比较复杂执行较慢而又需要定时执行的代码，可能需要解开DTH11驱动文件内中断开关函数的注释。在读取DHT11之前先关闭中断，读取完成后再打开。
### 键盘设定……分支
该分支未开发完成。由于本人精力有限，本项目已经停止开发。该分支主要修改是在OLED屏幕上添加了设定温湿度值和目前温湿度值的显示，以及ESP链接情况。同时在USER文件夹内添加了主要的业务代码。逻辑如图!(../STC8G温湿度控制系统逻辑图.png)