
/* can be inlcuded in TASK LAYER and ABOVE */



#ifndef _VERITY_INCLUDE_H_
#define _VERITY_INCLUDE_H_




//Public
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



//Sdk
#include "stm32l1xx_hal.h"
#include "tim.h"
#include "rtc.h"



//Define
#include "VerityDefine.h"



//utils
#include "utils_array.h"
#include "utils_systick_hal.h"





//Module
#include "RGB.h"
#include "HJ_BLE.h"
#include "PAH8001.h"
#include "mpu9250.h"
#include "RGB.h"
#include "LTC3553.h"
#include "bmp180.h"



//Task file can not be include in this .h file




//System
#include "VerityThread.h"





//Parameter


//TactSwitch
extern TactSwitch_StatusTypeDef		gTactSwitchStatus;


//Thread
extern Task_ListTypeDef				gTaskList;


//BLE
extern BLE_BufferTypeDef			gBleTransferBuffer_1;
extern BLE_BufferTypeDef			gBleTransferBuffer_2;
extern uint8_t						gBleRxBuffer[BLE_COMMANDS_LENGTH];


//Sample
extern uint8_t						gSampleFrameIndex;
extern Array_Uint32TypeDef			gRawPpgData;			//
extern Array_Uint32TypeDef			gRawPpgDataCopy;		//


extern YHY_StatusTypeDef			gSampleState;

//Calculate
extern HR_ListTypeDef				gHRList;

#endif
