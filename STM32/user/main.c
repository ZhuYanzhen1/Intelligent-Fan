#include "main.h"

int main(void) {
    HAL_Init();
    Clock_Config();
    GPIO_Config();
    TIM3_Config();
    UART1_Config();
    while (1) {

    }
}
