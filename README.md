# Intelligent-Fan

## Catalog

+ [1. Develop Environments](#1-develop-environments)
+ [2. Control Ideas](#2-control-ideas)
+ [3. Function Design](#3-dunction-design)
+ [4. Bill Of Materials](#4-bill-of-materials)

***

### 1. Develop Environments

+ Operating System: Ubuntu 20.04LTS
+ Coding IDE: CLion 2020.2.4
+ Compilation Tool Chain: gcc-none-eabi 9-2020-q2; xtensa-lx106-elf
+ Debugger: ST-Link; UART Debug Software

***

### 2. Control Ideas

&nbsp;&nbsp;&nbsp;&nbsp;The main chip is stm32f103c8t6, the WiFi chip uses esp8266ex, the temperature sampling chip uses DS18B20, and the display screen uses 1.8-inch TFT LCD screen to realize the networking time synchronization function. The matrix keyboard is used

&nbsp;&nbsp;&nbsp;&nbsp;The output PWM wave of stm32f103c8t6 is used to control the MOS tube to control the fan speed and the heating temperature of the heating wire, and the timing parameters set by the user are adjusted by reading the matrix keyboard through the IO port. Esp8266ex connects WiFi through 802.11n protocol, and realizes mqtt protocol through TCP protocol in LwIP stack. Esp8266ex connects to the server through WiFi, and mqtt subscribes to the topic of fan switch. Once the user sends the topic of the fan switch remotely, esp8266ex realizes the remote control of the fan through the high-speed STM32 serial protocol.


***

### 3. Function Design

1. Manual control (through keyboard setting, LCD screen display status, display time and fan gear)

	+ Cold air: set the wind speed through the button.

	+ Timing: power off automatically after setting a certain time by button.

	+ Hot air: set whether the heating wire works through the button.

2. Temperature control gear (display real-time temperature through LCD screen)

	+ When the temperature is less than 23 ℃, the electric fan will not rotate

	+ When 23 ≤ temperature ≤ 28 ℃, the fan rotates at low speed

	+ When the temperature is higher than 28, the fan will rotate at high speed

3. Automatic transmission

	Check whether there is someone in front of the fan, if there is someone, continue to rotate, if there is no one, count down for 15s, if there is still no one, turn off the fan.

4. Remote control of fan switch through WiFi networking

***

### 4. Bill Of Materials

|      Name       | Quantity |                        Purchase Link                         | Total Price |
| :-------------: | :------: | :----------------------------------------------------------: | :---------: |
|  Circuit Board  |    5     |            [Purchase Link](https://www.jlc.com/#)            |    5.0￥    |
|    716 Motor    |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a230r.1.14.53.45b8694ac5VVeM&id=585798412136&ns=1&abbucket=13#detail) |    2.0￥    |
|     Paddle      |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a230r.1.14.53.45b8694ac5VVeM&id=585798412136&ns=1&abbucket=13#detail) |    0.8￥    |
|  STM32F103C8T6  |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a1z10.3-c-s.w4002-21223910208.10.1ef96a4bap6D9d&id=522577960040) |   41.0￥    |
|     ESP12-F     |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a1z10.3-c-s.w4002-21223910208.10.65e36a4bstI0G6&id=594418112880) |    8.0￥    |
| 1.8inch TFT-LCD |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a1z09.2.0.0.38a82e8dd7Ke6Z&id=602381046383&_u=23ika512ceb7) |   13.5￥    |
|     DS18B20     |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a1z10.3-c-s.w4002-21223910208.13.75ef6a4bVSZETi&id=522575988442) |    5.1￥    |
|  Heating Wire   |    1     | [Purchase Link](https://item.taobao.com/item.htm?id=616146535211&ali_refid=a3_420434_1006:1177570125:N:H7n1V9EEGWer3TERliAcFg%3D%3D:7e61b93d98d00325e0c7db65169dadc7&ali_trackid=1_7e61b93d98d00325e0c7db65169dadc7&spm=a230r.1.1957635.56) |    2.6￥    |
|  AC/DC Adaptor  |    1     | [Purchase Link](https://item.taobao.com/item.htm?spm=a230r.1.14.49.509a1a8bVCJNCW&id=564383076984&ns=1&abbucket=13#detail) |   22.0￥    |

