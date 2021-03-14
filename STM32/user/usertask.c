//
// Created by Lao·Zhu on 2021/3/4.
//

#include "main.h"

unsigned char ReadKey() {
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) {
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
            Delayms(1);
        return 1;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) {
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
            Delayms(1);
        return 2;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET) {
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
            Delayms(1);
        return 3;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET) {
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET)
            Delayms(1);
        return 4;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_RESET) {
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_RESET)
            Delayms(1);
        return 5;
    }
    return 0;
}

void CircleTask(void *pvParameter) {
    const char Y_Bias = 10;
    Menu_Struct_t Last_Menu;
    while (1) {
        //Menu.Temperature = DS18B20_GetTemp();
        switch (Menu.Index) {
            case 1:
                if (Last_Menu.Index != Menu.Index || Last_Menu.SubIndex != Menu.SubIndex) {
                    if (Menu.SubIndex == 1)
                        GUI_Printf(20, 25 + Y_Bias, C_WHITE, C_BLACK, "Manual Mode");
                    else
                        GUI_Printf(20, 25 + Y_Bias, C_BLACK, C_WHITE, "Manual Mode");
                }
                if (Last_Menu.SubIndex != Menu.SubIndex || Last_Menu.Index != Menu.Index) {
                    GUI_Printf(32, 45 + Y_Bias, C_BLACK, C_WHITE, "Speed:");
                    if (Menu.SubIndex == 2)
                        GUI_Printf(80, 45 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Fan_Speed);
                    else
                        GUI_Printf(80, 45 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Fan_Speed);
                    if (Menu.Timer.Enable == DISABLE)
                        GUI_Printf(13, 65 + Y_Bias, C_DARK_RED, C_WHITE, "Time");
                    else if (Menu.Timer.Enable == ENABLE)
                        GUI_Printf(13, 65 + Y_Bias, C_DARK_GREEN, C_WHITE, "Time");
                    GUI_Printf(45, 65 + Y_Bias, C_BLACK, C_WHITE, ":%02d:%02d:%02d",
                               Menu.Timer.Hour, Menu.Timer.Minute, Menu.Timer.Second);
                    switch (Menu.SubIndex) {
                        case 3:
                            if (Menu.Timer.Enable == DISABLE)
                                GUI_Printf(13, 65 + Y_Bias, C_DARK_RED, C_BLACK, "Time");
                            else if (Menu.Timer.Enable == ENABLE)
                                GUI_Printf(13, 65 + Y_Bias, C_DARK_GREEN, C_BLACK, "Time");
                            break;
                        case 4:GUI_Printf(53, 65 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Timer.Hour);
                            break;
                        case 5:GUI_Printf(77, 65 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Timer.Minute);
                            break;
                        case 6:GUI_Printf(101, 65 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Timer.Second);
                            break;
                    }
                    if (Menu.SubIndex == 7 && Menu.Heater_Enable == DISABLE)
                        GUI_Printf(35, 85 + Y_Bias, C_DARK_RED, C_BLACK, "Heating");
                    else if (Menu.SubIndex == 7 && Menu.Heater_Enable == ENABLE)
                        GUI_Printf(35, 85 + Y_Bias, C_DARK_GREEN, C_BLACK, "Heating");
                    else if (Menu.Heater_Enable == DISABLE)
                        GUI_Printf(35, 85 + Y_Bias, C_DARK_RED, C_WHITE, "Heating");
                    else if (Menu.Heater_Enable == ENABLE)
                        GUI_Printf(35, 85 + Y_Bias, C_DARK_GREEN, C_WHITE, "Heating");
                }
                break;
            case 2:Menu.SubIndex = 1;
                if (Last_Menu.Index != Menu.Index) {
                    if (Last_Menu.Index == 1) {
                        GUI_Rectangle(13, 65 + Y_Bias, 117, 81 + Y_Bias, C_WHITE);
                        GUI_Rectangle(32, 45 + Y_Bias, 96, 61 + Y_Bias, C_WHITE);
                        GUI_Rectangle(35, 85 + Y_Bias, 91, 101 + Y_Bias, C_WHITE);
                    }
                    GUI_Printf(20, 25 + Y_Bias, C_WHITE, C_BLACK, "Temp   Mode");
                }
                break;
            case 3:Menu.SubIndex = 1;
                if (Last_Menu.Index != Menu.Index) {
                    if (Last_Menu.Index == 1) {
                        GUI_Rectangle(13, 65 + Y_Bias, 117, 81 + Y_Bias, C_WHITE);
                        GUI_Rectangle(32, 45 + Y_Bias, 96, 61 + Y_Bias, C_WHITE);
                        GUI_Rectangle(35, 85 + Y_Bias, 91, 101 + Y_Bias, C_WHITE);
                    }
                    GUI_Printf(20, 25 + Y_Bias, C_WHITE, C_BLACK, "Auto   Mode");
                }
                break;
        }
//        GUI_Printf(30, 8, C_BLACK, C_WHITE, "%s", Menu.Time_Buf);
        Last_Menu.Index = Menu.Index;
        Last_Menu.SubIndex = Menu.SubIndex;
        Delayms(100);
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