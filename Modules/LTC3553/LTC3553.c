/*****************************************************************

File			:	YD-Module\LTC3553\LTC3553.c
Fuction		:	Power management chip
Author		:	@yehangyang
Version		:	V1.0
Time			:	11 Nov. 2015

*****************************************************************/
#include "ltc3553.h"

#include "gpio.h"
#include "adc.h"


/*****************************************************************
Name			:	void LTC_setPowerOn(ONorOFF mode)
Fuction		:	Power mode configuration
Input			:	power mode(PA0--LTC_ON Low:OFF ; High:ON)
Output		:	void
Author		:	@yehangyang
Version		:	V0.0.1
Time			:	11 Nov. 2015
*****************************************************************/
void LTC_setPowerOn(ONorOFF mode)
{
    switch(mode)
    {
    case OFF:
        HAL_GPIO_WritePin(LTC_ON_GPIO_Port, LTC_ON_Pin, GPIO_PIN_RESET);
        break;
    case ON:
        HAL_GPIO_WritePin(LTC_ON_GPIO_Port, LTC_ON_Pin, GPIO_PIN_SET);
        break;
    default:
        HAL_GPIO_WritePin(LTC_ON_GPIO_Port, LTC_ON_Pin, GPIO_PIN_SET);
        break;

    }
}

/*****************************************************************
Name			:	void LTC_setStandBy(ONorOFF mode)
Fuction		:	standby mode configuration
Input			:	standby mode(PB3	LTC_STBY  Low:Normal ; High:standby mode 10mA)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
void LTC_setStandBy(ONorOFF mode)
{
    switch(mode)
    {
    case OFF:
        HAL_GPIO_WritePin(LTC_STAND_BY_GPIO_Port, LTC_STAND_BY_Pin, GPIO_PIN_RESET);
        break;
    case ON:
        HAL_GPIO_WritePin(LTC_STAND_BY_GPIO_Port, LTC_STAND_BY_Pin, GPIO_PIN_SET);
        break;
    default:
        HAL_GPIO_WritePin(LTC_STAND_BY_GPIO_Port, LTC_STAND_BY_Pin, GPIO_PIN_RESET);
        break;

    }
}

/*****************************************************************
Name			:	uint8_t LTC_getPowerState(void)
Fuction		:	the power up button state
Input			:	void
Output		:	the value of button(PA0	LTC_ON Low:OFF ; High:ON)
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
uint8_t LTC_getPowerState(void)
{
    if(HAL_GPIO_ReadPin(LTC_ON_GPIO_Port, LTC_ON_Pin) == GPIO_PIN_RESET)
        return 0;
    else
        return 1;
}

/*****************************************************************
Name			:	void LTC_setLdoOn(ONorOFF mode)
Fuction		:	LDO mode configuration
Input			:	Power mode(PB4	LTC_LDO_ON Low:OFF ; High:ON)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
void LTC_setLdoOn(ONorOFF mode)
{
    switch(mode)
    {
    case OFF:
        HAL_GPIO_WritePin(LTC_LDO_ON_GPIO_Port, LTC_LDO_ON_Pin, GPIO_PIN_RESET);
        break;
    case ON:
        HAL_GPIO_WritePin(LTC_LDO_ON_GPIO_Port, LTC_LDO_ON_Pin, GPIO_PIN_SET);
        break;
    default:
        HAL_GPIO_WritePin(LTC_LDO_ON_GPIO_Port, LTC_LDO_ON_Pin, GPIO_PIN_SET);
        break;

    }
}

/*****************************************************************
Name			:	void LTC_setBuchOn(ONorOFF mode)
Fuction		:	BUCK mode configuration
Input			:	Power mode(PB2		LTC_BUCK_ON Low:OFF ; High:ON)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
void LTC_setBuchOn(ONorOFF mode)
{
    switch(mode)
    {
    case OFF:
        HAL_GPIO_WritePin(LTC_BUCK_ON_GPIO_Port, LTC_BUCK_ON_Pin, GPIO_PIN_RESET);
        break;
    case ON:
        HAL_GPIO_WritePin(LTC_BUCK_ON_GPIO_Port, LTC_BUCK_ON_Pin, GPIO_PIN_SET);
        break;
    default:
        HAL_GPIO_WritePin(LTC_BUCK_ON_GPIO_Port, LTC_BUCK_ON_Pin, GPIO_PIN_SET);
        break;

    }
}

/*****************************************************************
Name			:	void LTC_setChargeCurrent(uint8_t mode)
Fuction		:	Charger current configuration
Input			:	current mode(PC13	LTC_HPWR 0:100mA charger; 1:500mA)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
void LTC_setChargeCurrent(ChargeCurrentMode mode)
{
    switch(mode)
    {
    case _100mA:
        HAL_GPIO_WritePin(LTC_HPWR_GPIO_Port, LTC_HPWR_Pin, GPIO_PIN_RESET);
        break;
    case _500mA:
        HAL_GPIO_WritePin(LTC_HPWR_GPIO_Port, LTC_HPWR_Pin, GPIO_PIN_SET);
        break;
    default:
        HAL_GPIO_WritePin(LTC_HPWR_GPIO_Port, LTC_HPWR_Pin, GPIO_PIN_RESET);
        break;
    }

}

/*****************************************************************
Name			:	uint8_t LTC_isCharging(void)
Fuction		:	Charger state configuration
Input			:	void
Output		:	state mode(PA15	LTC_CHRG 0:charging; 1:completed)
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
uint8_t LTC_isCharging(void)
{

    if(HAL_GPIO_ReadPin(LTC_CHARGE_STATE_GPIO_Port, LTC_CHARGE_STATE_Pin) == GPIO_PIN_RESET)
        return 0;
    else
        return 1;

}

/*****************************************************************
Name			:	float LTC_getBatteryVoltage(void)
Fuction		:	Battery Voltage
Input			:	void
Output		:	the real voltage of battery (PA1 ADC_IN1)
Author		:	@yehangyang
Version		:	V0.1
Time			:	11 Nov. 2015
*****************************************************************/
float LTC_getBatteryVoltage(void)
{
    float bat_vol = 0;
    HAL_ADC_Start(&hadc);
    while(HAL_ADC_PollForConversion(&hadc, 1) != HAL_OK);
    bat_vol = (float)(HAL_ADC_GetValue(&hadc)) / 2048 * 4 + 0.01;
    if(bat_vol > 4.20)
    {
        bat_vol = 4.20;
    }
    //	bat_vol = (float)(HAL_ADC_GetValue(&hadc))/2048*3.3;
    return bat_vol;
}


void LTC_init(void)
{
    LTC_setPowerOn(ON);
    LTC_setLdoOn(ON);
    LTC_setBuchOn(OFF);
    LTC_setChargeCurrent(_500mA);
}


/************    @YD-STM32L    *    File End Here    ************/
