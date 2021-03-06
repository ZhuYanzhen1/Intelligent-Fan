//
// Created by Lao·Zhu on 2021/3/6.
//

#ifndef STM32_LOGIC_MENU_H_
#define STM32_LOGIC_MENU_H_

typedef struct {
    unsigned char Enable;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
} Timer_Struct_t;

typedef struct {
    unsigned char Time_Buf[16];
    unsigned char Index;
    unsigned char SubIndex;
    unsigned char Heater_Enable;
    Timer_Struct_t Timer;
    unsigned char Body_Detect;
    unsigned char Fan_Speed;
    unsigned short Temperature;
} Menu_Struct_t;

extern Menu_Struct_t Menu;

#endif //STM32_LOGIC_MENU_H_
