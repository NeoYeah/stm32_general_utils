/*****************************************************************

File		:	YD-Module\BLE_DA14580\BLE.h
Fuction		:
Author		:	@yehangyang
Version		:	V1.0
Time			:	30 Nov. 2015

*****************************************************************/

#ifndef _HJ_BLE_H_
#define _HJ_BLE_H_

#include "stm32l1xx_hal.h"
#include "VerityDefine.h"

#include <stdbool.h>



#define BLE_USART						huart2


extern HJ_BLE_TypeDef					gHjBleTypeDef;


void HJ_BLE_setRole(bool isMaster);
void HJ_BLE_setMode(bool  isConfig);
void HJ_BLE_setWakeUp(bool isWakeUp);
void HJ_BLE_setBond(bool isBond);

bool HJ_BLE_isConnected(void);
void HJ_BLE_doDisconnect(void);

uint8_t HJ_BLE_getDataReadySignal(void);
HAL_StatusTypeDef HJ_BLE_Transmit(uint8_t *pData, uint16_t Size);

void HJ_BLE_Reset(void);
HAL_StatusTypeDef HJ_BLE_setBleBaudRate(HJ_BLE_TypeDef *hjBleTypeDef,uint32_t baudRate);

void HJ_BLE_init(HJ_BLE_TypeDef *hjBleTypeDef);



#endif
