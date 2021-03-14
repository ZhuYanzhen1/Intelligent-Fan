//
// Created by Lao·Zhu on 2021/3/14.
//
#include "menu.h"
#include "color.h"
#include "gui.h"
#include "stm32f1xx_hal.h"
#include "system.h"
#include "FreeRTOS.h"
#include "semphr.h"

const char Y_Bias = 10;
extern SemaphoreHandle_t GUI_Printf_Semaph;

void Refresh_Data(Menu_Struct_t *LastMenu) {
    if (LastMenu->Fan_Speed != Menu.Fan_Speed && Menu.SubIndex == 2)
        GUI_Printf(80, 45 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Fan_Speed);
    else if (LastMenu->Fan_Speed != Menu.Fan_Speed)
        GUI_Printf(80, 45 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Fan_Speed);
    if (LastMenu->Timer.Hour != Menu.Timer.Hour && Menu.SubIndex == 4)
        GUI_Printf(53, 65 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Timer.Hour);
    else if (LastMenu->Timer.Hour != Menu.Timer.Hour)
        GUI_Printf(53, 65 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Timer.Hour);
    if (LastMenu->Timer.Minute != Menu.Timer.Minute && Menu.SubIndex == 5)
        GUI_Printf(77, 65 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Timer.Minute);
    else if (LastMenu->Timer.Minute != Menu.Timer.Minute)
        GUI_Printf(77, 65 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Timer.Minute);
    if (LastMenu->Timer.Second != Menu.Timer.Second && Menu.SubIndex == 6)
        GUI_Printf(101, 65 + Y_Bias, C_WHITE, C_BLACK, "%02d", Menu.Timer.Second);
    else if (LastMenu->Timer.Second != Menu.Timer.Second)
        GUI_Printf(101, 65 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Timer.Second);
    if (Menu.Heater_Enable != LastMenu->Heater_Enable && Menu.Heater_Enable == DISABLE)
        GUI_Printf(35, 85 + Y_Bias, C_DARK_RED, C_BLACK, "Heating");
    else if (Menu.Heater_Enable != LastMenu->Heater_Enable && Menu.Heater_Enable == ENABLE)
        GUI_Printf(35, 85 + Y_Bias, C_DARK_GREEN, C_BLACK, "Heating");
    if (Menu.Timer.Enable != LastMenu->Timer.Enable && Menu.Timer.Enable == DISABLE)
        GUI_Printf(13, 65 + Y_Bias, C_DARK_RED, C_BLACK, "Time");
    else if (Menu.Timer.Enable != LastMenu->Timer.Enable && Menu.Timer.Enable == ENABLE)
        GUI_Printf(13, 65 + Y_Bias, C_DARK_GREEN, C_BLACK, "Time");

    LastMenu->Fan_Speed = Menu.Fan_Speed;
    LastMenu->Timer.Hour = Menu.Timer.Hour;
    LastMenu->Timer.Minute = Menu.Timer.Minute;
    LastMenu->Timer.Second = Menu.Timer.Second;
    LastMenu->Timer.Enable = Menu.Timer.Enable;
    LastMenu->Heater_Enable = Menu.Heater_Enable;
}

void MenuGUITask(void *pvParameter) {
    Menu_Struct_t Last_Menu;
    while (1) {
        switch (Menu.Index) {
            case 1:xSemaphoreTake(GUI_Printf_Semaph, 0xffffffffUL);
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
                Refresh_Data(&Last_Menu);
                xSemaphoreGive(GUI_Printf_Semaph);
                break;
            case 2:xSemaphoreTake(GUI_Printf_Semaph, 0xffffffffUL);
                Menu.SubIndex = 1;
                if (Last_Menu.Index != Menu.Index) {
                    if (Last_Menu.Index == 1) {
                        GUI_Rectangle(32, 45 + Y_Bias, 96, 61 + Y_Bias, C_WHITE);
                        GUI_Rectangle(13, 65 + Y_Bias, 117, 81 + Y_Bias, C_WHITE);
                        GUI_Rectangle(35, 85 + Y_Bias, 91, 101 + Y_Bias, C_WHITE);
                    }
                    GUI_Printf(32, 45 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Temperature / 100);
                    GUI_Printf(48, 45 + Y_Bias, C_BLACK, C_WHITE, ".%02d C ", Menu.Temperature % 100);
                    GUI_Printf(20, 25 + Y_Bias, C_WHITE, C_BLACK, "Temp   Mode");
                }
                if (Menu.Temperature != Last_Menu.Temperature) {
                    GUI_Printf(32, 45 + Y_Bias, C_BLACK, C_WHITE, "%02d", Menu.Temperature / 100);
                    GUI_Printf(48, 45 + Y_Bias, C_BLACK, C_WHITE, ".%02d C ", Menu.Temperature % 100);
                }
                xSemaphoreGive(GUI_Printf_Semaph);
                break;
            case 3:xSemaphoreTake(GUI_Printf_Semaph, 0xffffffffUL);
                Menu.SubIndex = 1;
                if (Last_Menu.Index != Menu.Index) {
                    if (Last_Menu.Index == 1) {
                        GUI_Rectangle(32, 45 + Y_Bias, 96, 61 + Y_Bias, C_WHITE);
                        GUI_Rectangle(13, 65 + Y_Bias, 117, 81 + Y_Bias, C_WHITE);
                        GUI_Rectangle(35, 85 + Y_Bias, 91, 101 + Y_Bias, C_WHITE);
                    }
                    if (Menu.Body_Detect == 1)
                        GUI_Printf(32, 45 + Y_Bias, C_GREEN, C_WHITE, "Detected");
                    else if (Menu.Body_Detect == 0)
                        GUI_Printf(32, 45 + Y_Bias, C_RED, C_WHITE, "Detected");
                    GUI_Printf(20, 25 + Y_Bias, C_WHITE, C_BLACK, "Auto   Mode");
                }
                if (Last_Menu.Body_Detect != Menu.Body_Detect && Menu.Body_Detect == 1)
                    GUI_Printf(32, 45 + Y_Bias, C_GREEN, C_WHITE, "Detected");
                else if (Last_Menu.Body_Detect != Menu.Body_Detect && Menu.Body_Detect == 0)
                    GUI_Printf(32, 45 + Y_Bias, C_RED, C_WHITE, "Detected");
                xSemaphoreGive(GUI_Printf_Semaph);
                break;
        }
        Last_Menu.Temperature = Menu.Temperature;
        Last_Menu.Body_Detect = Menu.Body_Detect;
        Last_Menu.Index = Menu.Index;
        Last_Menu.SubIndex = Menu.SubIndex;
        Delayms(50);
    }
}
