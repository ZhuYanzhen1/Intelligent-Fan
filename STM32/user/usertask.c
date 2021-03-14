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
    }
}

void UserTask(void *pvParameter) {
    while (1) {
        unsigned char KeyNum = ReadKey();
        switch (KeyNum) {
            case 1:
                if (Menu.Index == 1 && Menu.SubIndex == 7)
                    Menu.SubIndex = 1;
                else if (Menu.Index == 1)
                    Menu.SubIndex++;
                break;
            case 2:
                if (Menu.Index == 3 && Menu.SubIndex == 1)
                    Menu.Index = 1;
                else if (Menu.SubIndex == 1)
                    Menu.Index++;
                break;
            case 4:
                if (Menu.Index == 1 && Menu.SubIndex == 1)
                    Menu.Index = 3;
                else if (Menu.SubIndex == 1)
                    Menu.Index--;
                break;
            case 5:
                if (Menu.Index == 1 && Menu.SubIndex == 1)
                    Menu.SubIndex = 7;
                else if (Menu.Index == 1)
                    Menu.SubIndex--;
                break;
            default:Delayms(10);
                break;
        }
    }
}