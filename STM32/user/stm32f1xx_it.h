#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
void TIM4_IRQHandler(void);
void USART1_IRQHandler(void);

#endif /* __STM32F1xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
