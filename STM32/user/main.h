#ifndef __MAIN_H
#define __MAIN_H

///////////// System /////////////
#include "system.h"
#include "usertask.h"
#include "string.h"

///////////// Hardware /////////////
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "lcd.h"
#include "led.h"
#include "ds18b20.h"
#include "key.h"

///////////// Device /////////////
#include "gui.h"
#include "fan.h"

///////////// Logic /////////////
#include "menu.h"

///////////// FreeRTOS /////////////
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#endif /* __MAIN_H */
