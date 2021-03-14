//
// Created by Lao·Zhu on 2021/3/4.
//

#include "main.h"

SemaphoreHandle_t GUI_Printf_Semaph;

void Semaphore_Config() {
    GUI_Printf_Semaph = xSemaphoreCreateMutex();
}

void CircleTask(void *pvParameters) {
    while (1) {
        Menu.Temperature = DS18B20_GetTemp();
        xSemaphoreTake(GUI_Printf_Semaph, 0xffffffffUL);
        GUI_Printf(30, 8 + Y_Bias, C_BLACK, C_WHITE, "%s", Menu.Time_Buf);
        xSemaphoreGive(GUI_Printf_Semaph);
        Delayms(1000);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
    }
}
