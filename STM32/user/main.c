#include "main.h"

int main(void) {
    HAL_Config();
    Clock_Config();
    GPIO_Config();
    TIM3_Config();
    UART1_Config();
    LCD_Config();
    LCD_Scan(4);
    GUI_Clear(C_WHITE);
    while (1) {
        HAL_Delay(500);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    }
}
