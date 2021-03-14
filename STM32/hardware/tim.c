#include "tim.h"

TIM_HandleTypeDef htim3;

void TIM3_Config(void) {
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 71;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 999;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    while (HAL_TIM_PWM_Init(&htim3) != HAL_OK);
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    while (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK);
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    while (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK);
    HAL_TIM_MspPostInit(&htim3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_pwmHandle) {
    if (tim_pwmHandle->Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_ENABLE();
    }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (timHandle->Instance == TIM3) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *tim_pwmHandle) {

    if (tim_pwmHandle->Instance == TIM3) {
        __HAL_RCC_TIM3_CLK_DISABLE();
    }
}
