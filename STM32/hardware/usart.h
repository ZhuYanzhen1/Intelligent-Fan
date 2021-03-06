#ifndef __USART_H__
#define __USART_H__

#include "system.h"

extern unsigned char rcv_time_buffer[32];

extern UART_HandleTypeDef huart1;

void UART1_Config(void);

#endif /* __USART_H__ */
