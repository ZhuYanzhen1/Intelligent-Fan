//
// Created by Lao·Zhu on 2021/3/4.
//

#include "main.h"

void CircleTask(void *pvParameter) {
    while (1) {
        Menu.Temperature = DS18B20_GetTemp();
        Delayms(1000);
    }
}

void UserTask(void *pvParameter) {
    while (1)
        Delayms(500);
}
