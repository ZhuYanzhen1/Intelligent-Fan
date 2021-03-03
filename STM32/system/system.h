//
// Created by Lao·Zhu on 2021/3/3.
//

#ifndef STM32_SYSTEM_SYSTEM_H_
#define STM32_SYSTEM_SYSTEM_H_

#include "stm32f1xx_hal.h"

void Clock_Config(void);
void Delayms(unsigned int xms);
void Delayus(unsigned int xus);

#endif //STM32_SYSTEM_SYSTEM_H_
