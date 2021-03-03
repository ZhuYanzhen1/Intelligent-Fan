#ifndef __TIM_H__
#define __TIM_H__

#include "system.h"

extern TIM_HandleTypeDef htim3;

void TIM3_Config(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

#endif /* __TIM_H__ */
