#include "main.h"

TaskHandle_t InitTask_Handler, UserTask_Handler;

void InitTask(void *pvParameters) {
    taskENTER_CRITICAL();
    GPIO_Config();
    LED_Config();
    TIM3_Config();
    UART1_Config();
    LCD_Config();
    LCD_Scan(4);
    GUI_Clear(C_WHITE);
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
