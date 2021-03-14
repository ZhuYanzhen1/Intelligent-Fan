#include "main.h"

Menu_Struct_t Menu;
TaskHandle_t InitTask_Handler, UserTask_Handler;
TaskHandle_t CircleTask_Handler, MenuGUITask_Handler;

void Menu_Config(void) {
    const char buf[] = "00:00:00";
    memset(&Menu, 0x00, sizeof(Menu_Struct_t));
    Menu.Timer.Enable = DISABLE;
    Menu.Heater_Enable = DISABLE;
    Menu.Index = 1;
    Menu.SubIndex = 1;
    Menu.Body_Detect = 0;
    strcpy((char *) Menu.Time_Buf, buf);
}

void InitTask(void *pvParameters) {
    taskENTER_CRITICAL();
    GPIO_Config();
    LED_Config();
    DS18B20_Config();
    TIM3_Config();
    Fan_Off();
    UART1_Config();
    Semaphore_Config();
    LCD_Config();
    LCD_Scan(4);
    GUI_Clear(C_WHITE);
    Menu_Config();
    xTaskCreate(MenuSwitchTask, "MenuSwitchTask", 1024,
                NULL, 2, &UserTask_Handler);
    xTaskCreate(MenuGUITask, "MenuGUITask", 512,
                NULL, 1, &MenuGUITask_Handler);
    xTaskCreate(CircleTask, "CircleTask", 512,
                NULL, 1, &CircleTask_Handler);
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
