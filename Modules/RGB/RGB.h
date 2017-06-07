#ifndef _RGB_H
#define _RGB_H


#include "VerityInclude.h"

#define RGB_R_ON		HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, GPIO_PIN_RESET)
#define RGB_R_OFF		HAL_GPIO_WritePin(RGB_R_GPIO_Port, RGB_R_Pin, GPIO_PIN_SET)
#define RGB_R_TOGGLE	HAL_GPIO_TogglePin(RGB_R_GPIO_Port, RGB_R_Pin)


#define RGB_G_ON    	HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, GPIO_PIN_RESET)
#define RGB_G_OFF   	HAL_GPIO_WritePin(RGB_G_GPIO_Port, RGB_G_Pin, GPIO_PIN_SET)
#define RGB_G_TOGGLE	HAL_GPIO_TogglePin(RGB_G_GPIO_Port, RGB_G_Pin)

#define RGB_B_ON    	HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, GPIO_PIN_RESET)
#define RGB_B_OFF   	HAL_GPIO_WritePin(RGB_B_GPIO_Port, RGB_B_Pin, GPIO_PIN_SET)
#define RGB_B_TOGGLE	HAL_GPIO_TogglePin(RGB_B_GPIO_Port, RGB_B_Pin)



typedef enum
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    BGREEN,
    WHITE,
    ALL_COLOR
} COLOR;


typedef enum
{
    COLOR_OFF,
    COLOR_ON,
    COLOR_TOGGLE,
} COLOR_MODE;


void setRgbOn(bool isOn, COLOR color);
void setWaterfallLight(bool enable);
void setRgbBlink(COLOR color, uint8_t times);

#endif
