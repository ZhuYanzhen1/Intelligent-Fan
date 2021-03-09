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
    while (1) {
        //Menu.Temperature = DS18B20_GetTemp();
        Delayms(1000);
    }
}

void UserTask(void *pvParameter) {
    while (1) {
        float RAM_Remain = xPortGetFreeHeapSize() / 1024.0f;
        unsigned char KeyNum = ReadKey();
        GUI_Printf(2, 10, C_BLACK, C_WHITE, "%d", (int) RAM_Remain);
        Delayms((int) RAM_Remain * 100 / 1);
        Delayms(KeyNum);
    }
}
