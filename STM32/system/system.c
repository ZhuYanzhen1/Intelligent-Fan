//
// Created by Lao·Zhu on 2021/3/3.
//

#include "system.h"
#include "FreeRTOS.h"
#include "task.h"

TIM_HandleTypeDef htim4;
static unsigned int Facus = 0;
static unsigned int Facms = 0;

void Delayus(unsigned int xus) {
    unsigned int Ticks, Time_Old, Time_Now, Time_Count = 0;
    unsigned int Reload = SysTick->LOAD;
    Ticks = xus * Facus;
    Time_Old = SysTick->VAL;
    while (1) {
        Time_Now = SysTick->VAL;
        if (Time_Now != Time_Old) {
            if (Time_Now < Time_Old)
                Time_Count += Time_Old - Time_Now;
            else
                Time_Count += Reload - Time_Now + Time_Old;
            Time_Old = Time_Now;
            if (Time_Count >= Ticks)
                break;
        }
    }
}

void Delayms(unsigned int xms) {
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        if (xms >= Facms)
            vTaskDelay(xms / Facms);
        else {
            xms %= Facms;
            Delayus(xms * 1000);
        }
    } else
        Delayus(xms * 1000);
}

void Delay_Config(void) {
    unsigned int Reload;
    Facus = HAL_RCC_GetSysClockFreq() / 1000000;
    Reload = HAL_RCC_GetSysClockFreq() / 1000000;
    Reload *= 1000000 / configTICK_RATE_HZ;
    Facms = 1000 / configTICK_RATE_HZ;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->LOAD = Reload;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void Clock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    while (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK);
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    while (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK);
    HAL_RCC_EnableCSS();
}

void HAL_MspInit(void) {
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM4)
        HAL_IncTick();
}

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
    RCC_ClkInitTypeDef clkconfig;
    uint32_t uwTimclock = 0;
    uint32_t uwPrescalerValue = 0;
    uint32_t pFLatency;
    HAL_NVIC_SetPriority(TIM4_IRQn, TickPriority, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
    __HAL_RCC_TIM4_CLK_ENABLE();
    HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
    uwTimclock = 2 * HAL_RCC_GetPCLK1Freq();
    uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000U) - 1U);
    htim4.Instance = TIM4;
    htim4.Init.Period = (1000000U / 1000U) - 1U;
    htim4.Init.Prescaler = uwPrescalerValue;
    htim4.Init.ClockDivision = 0;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    if (HAL_TIM_Base_Init(&htim4) == HAL_OK)
        return HAL_TIM_Base_Start_IT(&htim4);
    return HAL_ERROR;
}

void HAL_SuspendTick(void) {
    __HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);
}

void HAL_ResumeTick(void) {
    __HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE);
}
