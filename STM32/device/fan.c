//
// Created by Lao·Zhu on 2021/3/6.
//

#include "fan.h"
#include "tim.h"

void Fan_On(unsigned char dutycycle) {
    htim3.Instance->CCR1 = dutycycle * 10;
}

void Fan_Off(void) {
    htim3.Instance->CCR1 = 1;
}
