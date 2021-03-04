//
// Created by Lao·Zhu on 2021/3/4.
//

#include "main.h"

void LEDTask(void *pvParameter) {
    while (1) {
        Delayms(500);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    }
}

void UserTask(void *pvParameter) {
    while (1)
        Delayms(500);
}
