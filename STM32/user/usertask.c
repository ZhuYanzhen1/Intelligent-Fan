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
                if (Menu.Index == 1) {
                    switch (Menu.SubIndex) {
                        case 2:Menu.Fan_Speed += 5;
                            if (Menu.Fan_Speed >= 40)
                                Menu.Fan_Speed = 40;
                            break;
                        case 3:Menu.Timer.Enable = !Menu.Timer.Enable;
                            break;
                        case 4:Menu.Timer.Hour++;
                            if (Menu.Timer.Hour == 24)
                                Menu.Timer.Hour = 0;
                            break;
                        case 5:Menu.Timer.Minute++;
                            if (Menu.Timer.Minute == 60) {
                                Menu.Timer.Minute = 0;
                                Menu.Timer.Hour++;
                                if (Menu.Timer.Hour == 24)
                                    Menu.Timer.Hour = 0;
                            }
                            break;
                        case 6:Menu.Timer.Second++;
                            if (Menu.Timer.Second == 60) {
                                Menu.Timer.Second = 0;
                                Menu.Timer.Minute++;
                                if (Menu.Timer.Minute == 60) {
                                    Menu.Timer.Minute = 0;
                                    Menu.Timer.Hour++;
                                    if (Menu.Timer.Hour == 24)
                                        Menu.Timer.Hour = 0;
                                }
                            }
                            break;
                        case 7:Menu.Heater_Enable = !Menu.Heater_Enable;
                            break;
                    }
                }
                break;
            case 4:
                if (Menu.Index == 1 && Menu.SubIndex == 1)
                    Menu.Index = 3;
                else if (Menu.SubIndex == 1)
                    Menu.Index--;
                if (Menu.Index == 1) {
                    switch (Menu.SubIndex) {
                        case 2:
                            if (Menu.Fan_Speed <= 5)
                                Menu.Fan_Speed = 0;
                            else
                                Menu.Fan_Speed -= 5;
                            break;
                        case 3:Menu.Timer.Enable = !Menu.Timer.Enable;
                            break;
                        case 4:
                            if (Menu.Timer.Hour == 0)
                                Menu.Timer.Hour = 23;
                            else
                                Menu.Timer.Hour--;
                            break;
                        case 5:
                            if (Menu.Timer.Minute == 0) {
                                Menu.Timer.Minute = 59;
                                if (Menu.Timer.Hour == 0)
                                    Menu.Timer.Hour = 23;
                                else
                                    Menu.Timer.Hour--;
                            } else
                                Menu.Timer.Minute--;
                            break;
                        case 6:
                            if (Menu.Timer.Second == 0) {
                                Menu.Timer.Second = 59;
                                if (Menu.Timer.Minute == 0) {
                                    Menu.Timer.Minute = 59;
                                    if (Menu.Timer.Hour == 0)
                                        Menu.Timer.Hour = 23;
                                    else
                                        Menu.Timer.Hour--;
                                } else
                                    Menu.Timer.Minute--;
                            } else
                                Menu.Timer.Second--;
                            break;
                        case 7:Menu.Heater_Enable = !Menu.Heater_Enable;
                            break;
                    }
                }
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