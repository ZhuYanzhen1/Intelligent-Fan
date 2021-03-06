#include "usart.h"

UART_HandleTypeDef huart1;
unsigned char aRxBuffer[1];
unsigned char time_receive_flag = 0;
unsigned char fan_receive_flag = 0;
unsigned char rcv_time_buffer[32], rcv_time_counter = 0;
unsigned char rcv_fan_buffer[16], rcv_fan_counter = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    switch (aRxBuffer[0]) {
        case '^':fan_receive_flag = 1;
            break;
        case '*':time_receive_flag = 1;
            break;
        case '$':
            fan_receive_flag = 0;
            rcv_fan_counter = 0;
            break;
        case '&':
            time_receive_flag = 0;
            rcv_time_counter = 0;
            break;
        default:
            if (fan_receive_flag == 1) {
                rcv_fan_buffer[rcv_fan_counter] = aRxBuffer[0];
                rcv_fan_counter++;
            }
            if (time_receive_flag == 1) {
                rcv_time_buffer[rcv_time_counter] = aRxBuffer[0];
                rcv_time_counter++;
            }
            break;
    }
    HAL_UART_Receive_IT(&huart1, (uint8_t *) aRxBuffer, 1);
}

void UART1_Config(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    while (HAL_UART_Init(&huart1) != HAL_OK);
    HAL_UART_Receive_IT(&huart1, (uint8_t *) aRxBuffer, 1);
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (uartHandle->Instance == USART1) {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {
    if (uartHandle->Instance == USART1) {
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
}
