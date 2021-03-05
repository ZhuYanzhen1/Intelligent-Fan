#include "main.h"

TaskHandle_t InitTask_Handler, LEDTask_Handler, UserTask_Handler;

void LEDTask(void *pvParameter) {
    while (1) {
        Delayms(500);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    }
}

void InitTask(void *pvParameters) {
    taskENTER_CRITICAL();
    GPIO_Config();
    TIM3_Config();
    UART1_Config();
    LCD_Config();
    LCD_Scan(4);
    GUI_Clear(C_WHITE);
    xTaskCreate(LEDTask, "LEDTask", 64,
                NULL, 1, &LEDTask_Handler);
    xTaskCreate(UserTask, "UserTask", 512,
                NULL, 2, &UserTask_Handler);
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();
}

int main(void) {
    HAL_Config();
    Clock_Config();
    Delay_Config();
    xTaskCreate(InitTask, "InitTask", 256,
                NULL, 1, &InitTask_Handler);
    vTaskStartScheduler();
    while (1);
}
