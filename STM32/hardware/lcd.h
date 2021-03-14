#ifndef _LCD_H_
#define _LCD_H_

#define LCD_RES_Pin GPIO_PIN_14
#define LCD_A0_Pin GPIO_PIN_13
#define LCD_SDA_Pin GPIO_PIN_15
#define LCD_SCL_Pin GPIO_PIN_8
#define LCD_CSB_Pin GPIO_PIN_12
#define LCD_RES_Port GPIOB
#define LCD_A0_Port GPIOB
#define LCD_SDA_Port GPIOB
#define LCD_SCL_Port GPIOA
#define LCD_CSB_Port GPIOB

void LCD_Config();
void LCD_Scan(unsigned char mode);
void Lcd_Write_Data(unsigned int dat16);
void Address_set(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

#endif
