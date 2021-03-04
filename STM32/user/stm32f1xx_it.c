#include "main.h"
#include "stm32f1xx_it.h"

extern TIM_HandleTypeDef htim4;

void NMI_Handler(void) {
    HAL_RCC_NMI_IRQHandler();
    while (1);
}
void HardFault_Handler(void) {
    while (1);
}

void MemManage_Handler(void) {
    while (1);
}

void BusFault_Handler(void) {
    while (1);
}

void UsageFault_Handler(void) {
    while (1);
}

void DebugMon_Handler(void) {

}

void TIM4_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim4);
}

void USART1_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart1);
}
