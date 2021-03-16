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
        if (Menu.Heater_Enable == ENABLE)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
        if (Menu.Fan_Speed > 0)
            Fan_On(Menu.Fan_Speed);
        else if (Menu.Fan_Speed == 0)
            Fan_Off();
        if (Menu.Timer.Enable == ENABLE) {
            if (Menu.Timer.Second == 0) {
                if (Menu.Timer.Minute == 0) {
                    if (Menu.Timer.Hour == 0) {
                        Menu.Timer.Enable = DISABLE;
                        Menu.Fan_Speed = 0;
                        Fan_Off();
                    } else {
                        Menu.Timer.Hour--;
                        Menu.Timer.Minute = 59;
                    }
                } else {
                    Menu.Timer.Minute--;
                    Menu.Timer.Second = 59;
                }
            } else
                Menu.Timer.Second--;
        }
    }
}
