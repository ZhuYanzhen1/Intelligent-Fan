//
// Created by Lao·Zhu on 2021/3/6.
//

#include "ds18b20.h"
#include "system.h"

void DS18B20_Reset(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    Delayus(750);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    Delayus(15);
}

unsigned char DS18B20_Check(void) {
    unsigned char retry = 0;
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && retry < 200) {
        retry++;
        Delayus(1);
    };
    if (retry >= 200)return 1;
    else retry = 0;
    while (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && retry < 240) {
        retry++;
        Delayus(1);
    };
    if (retry >= 240)return 1;
    return 0;
}

unsigned char DS18B20_ReadBit(void) {
    unsigned char data;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    Delayus(2);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    Delayus(12);
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))
        data = 1;
    else
        data = 0;
    Delayus(50);
    return data;
}

unsigned char DS18B20_ReadByte(void) {
    unsigned char i, j, dat = 0;
    for (i = 1; i <= 8; i++) {
        j = DS18B20_ReadBit();
        dat = (j << 7U) | (dat >> 1U);
    }
    return dat;
}

void DS18B20_WriteByte(unsigned char dat) {
    unsigned char j;
    unsigned char testb;
    for (j = 1; j <= 8; j++) {
        testb = dat & 0x01U;
        dat = dat >> 1U;
        if (testb) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
            Delayus(2);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
            Delayus(60);
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
            Delayus(60);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
            Delayus(2);
        }
    }
}

void DS18B20_Start(void) {
    DS18B20_Reset();
    DS18B20_Check();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0x44);
}

unsigned char DS18B20_Config(void) {
    DS18B20_Reset();
    return DS18B20_Check();
}

short DS18B20_GetTemp(void) {
    unsigned char temp, TL, TH;
    short tem;
    DS18B20_Start();
    DS18B20_Reset();
    DS18B20_Check();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0xbe);
    TL = DS18B20_ReadByte();
    TH = DS18B20_ReadByte();
    if (TH > 7) {
        TH = ~TH;
        TL = ~TL;
        temp = 0;
    } else
        temp = 1;
    tem = TH;
    tem = tem << 8;
    tem += TL;
    tem = (short) ((float) tem * 0.625);
    if (temp)
        return tem;
    else
        return -1 * tem;
} 
