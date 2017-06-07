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

#ifndef _I2C_HALDriver_H_
#define _I2C_HALDriver_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t HAL_I2C_WriteByte(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t data);

uint8_t HAL_I2C_ReadByte(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg);

uint8_t HAL_I2C_ReadBytes(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *pData, uint16_t size);


uint8_t SD_I2C_ReadBytes(I2C_HandleTypeDef* hi2c, uint8_t device_address,uint8_t register_address, uint8_t size, uint8_t *pResult);

uint8_t SD_I2C_ReadByte(I2C_HandleTypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t *data);

#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

