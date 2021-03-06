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
        Delayms(500);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    }
}

void LED_Config() {
    xTaskCreate(LEDTask, "LEDTask", 64,
                NULL, 1, &LEDTask_Handler);
}