#include "RGB.h"



void setRgbOn(bool isOn, COLOR color)
{
    if(isOn)
    {
        if(color == RED)
        {
            RGB_R_ON;
        }
        else if(color == GREEN)
        {
            RGB_G_ON;
        }
        else if(color == BLUE)
        {
            RGB_B_ON;
        }
        else if(color == YELLOW)
        {
            RGB_R_ON;
            RGB_G_ON;
        }
        else if(color == PURPLE)
        {
            RGB_R_ON;
            RGB_B_ON;
        }
        else if(color == BGREEN)
        {
            RGB_G_ON;
            RGB_B_ON;
        }
        else if(color == WHITE)
        {
            RGB_R_ON;
            RGB_G_ON;
            RGB_B_ON;
        }
    }
    else
    {
        if(color == ALL_COLOR)
        {
            RGB_R_OFF;
            RGB_G_OFF;
            RGB_B_OFF;
        }
    }
}



void setRgbToggle(bool isToggle, COLOR color)
{

    if(isToggle)
    {
        if(color == RED)
        {
            RGB_R_TOGGLE;
        }
        else if(color == GREEN)
        {
            RGB_G_TOGGLE;
        }
        else if(color == BLUE)
        {
            RGB_B_TOGGLE;
        }
        else if(color == YELLOW)
        {
            RGB_R_TOGGLE;
            RGB_G_TOGGLE;
        }
        else if(color == PURPLE)
        {
            RGB_R_TOGGLE;
            RGB_B_TOGGLE;
        }
        else if(color == BGREEN)
        {
            RGB_G_TOGGLE;
            RGB_B_TOGGLE;
        }
        else if(color == WHITE)
        {
            RGB_R_TOGGLE;
            RGB_G_TOGGLE;
            RGB_B_TOGGLE;
        }
    }
}


void setWaterfallLight(bool enable)
{
    if(enable)
    {
        setRgbOn(true, RED);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);

        setRgbOn(true, GREEN);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);

        setRgbOn(true, BLUE);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);

        setRgbOn(true, YELLOW);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);

        setRgbOn(true, PURPLE);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);

        setRgbOn(true, BGREEN);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);

        setRgbOn(true, WHITE);
        HAL_Delay(WATERFALL_LIGHT_ON_PERIOD);
        setRgbOn(false, ALL_COLOR);
    }
    else
    {
        RGB_R_TOGGLE;
        RGB_G_TOGGLE;
        RGB_B_TOGGLE;
    }
}



void setRgbBlink(COLOR color, uint8_t times)
{
    while(times--)
    {
        if(color == RED)
        {
            RGB_R_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_R_OFF;
        }
        else if(color == GREEN)
        {
            RGB_G_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_G_OFF;
        }
        else if(color == BLUE)
        {
            RGB_B_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_B_OFF;
        }
        else if(color == YELLOW)
        {
            RGB_R_ON;
            RGB_G_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_R_OFF;
            RGB_G_OFF;
        }
        else if(color == PURPLE)
        {
            RGB_R_ON;
            RGB_B_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_R_OFF;
            RGB_B_OFF;
        }
        else if(color == BGREEN)
        {
            RGB_G_ON;
            RGB_B_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_G_OFF;
            RGB_B_OFF;
        }
        else if(color == WHITE)
        {
            RGB_R_ON;
            RGB_G_ON;
            RGB_B_ON;
            HAL_Delay(BLINK_LIGHT_ON_PERIOD);
            RGB_R_OFF;
            RGB_G_OFF;
            RGB_B_OFF;
        }

        if(times != 0)
        {
            HAL_Delay(BLINK_PERIOD);
        }
    }
}


