//
// Created by Lao·Zhu on 2021/3/6.
//

#include "led.h"
#include "system.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t LEDTask_Handler;

void LEDTask(void *pvParameter) {
    while (1) {
        Delayms(1000);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
        Delayms(50);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    }
}

void LED_Config() {
    xTaskCreate(LEDTask, "LEDTask", 64,
                NULL, 1, &LEDTask_Handler);
}