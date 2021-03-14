//
// Created by Lao·Zhu on 2021/3/4.
//

#include "main.h"

void CircleTask(void *pvParameters) {
    while (1) {
        for (unsigned char counter = 0; counter < 5; counter++) {
            Menu.Temperature = DS18B20_GetTemp();
            if (Menu.Index == 2) {
                GUI_Printf(32, 45 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Temperature / 100);
                GUI_Printf(48, 45 + Y_Bias, C_BLACK, C_WHITE, ".%02d C", Menu.Temperature % 100);
            }
            if (Menu.Index == 3) {
                if (Menu.Body_Detect == 1)
                    GUI_Printf(32, 45 + Y_Bias, C_GREEN, C_WHITE, "Detected");
                else if (Menu.Body_Detect == 0)
                    GUI_Printf(32, 45 + Y_Bias, C_RED, C_WHITE, "Detected");
            }
            Delayms(200);
        }
        GUI_Printf(30, 8 + Y_Bias, C_BLACK, C_WHITE, "%s", Menu.Time_Buf);
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