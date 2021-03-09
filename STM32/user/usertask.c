//
// Created by Lao·Zhu on 2021/3/4.
//

#include "main.h"

void CircleTask(void *pvParameter) {
    while (1) {
        //Menu.Temperature = DS18B20_GetTemp();
        Delayms(1000);
    }
}

void UserTask(void *pvParameter) {
    while (1) {
        float RAM_Remain = xPortGetFreeHeapSize() / 1024.0f;
        //GUI_Printf(2, 10, C_BLACK, C_WHITE, "%.2f", RAM_Remain);
        Delayms((int) RAM_Remain * 100 / 1);
    }
}
