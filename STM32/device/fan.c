//
// Created by Lao·Zhu on 2021/3/6.
//

#include "fan.h"
#include "stm32f1xx_hal.h"
#include "tim.h"

void Fan_On(unsigned char dutycycle) {
    htim3.Instance->CCR1 = dutycycle * 10;
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
}

void Fan_Off(void) {
    htim3.Instance->CCR1 = 1;
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
}
