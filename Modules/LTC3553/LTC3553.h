/*********************************************************************************************************
*
* File                : 24c02.h
* Hardware Environment:
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  :
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#ifndef _LTC3553_H_
#define _LTC3553_H_

#include "stm32l1xx_hal.h"

typedef enum
{
    OFF,		/*Power off */
    ON,		/*Power on  */
    //	SB	= 0x02,		/*Power standby */
} ONorOFF;


typedef enum
{
    _100mA,
    _500mA,

} ChargeCurrentMode;

void LTC_setPowerOn(ONorOFF mode);

void LTC_setStandBy(ONorOFF mode);

uint8_t LTC_getPowerState(void);

void LTC_setLdoOn(ONorOFF mode);

void LTC_setBuchOn(ONorOFF mode);

void LTC_setChargeCurrent(uint8_t mode);

uint8_t LTC_isCharging(void);

float LTC_getBatteryVoltage(void);

void LTC_init(void);

#endif
