#ifndef _VERITY_DEFINE_H_
#define _VERITY_DEFINE_H_

#include "stm32l1xx_hal.h"
#include "pt-sem.h"


#include "stdint.h"
#include <stdbool.h>


#include "yhyDefine.h"


#include "rtc.h"
#include "usart.h"




//TactSwitch
#define TACT_SWITCH_PRESS_PERIOD_CONFIRM				50			//ms
#define TACT_SWITCH_PRESS_PERIOD_ON						1000		//ms
#define TACT_SWITCH_PRESS_PERIOD_OFF					6000		//ms
#define TACT_SWITCH_PRESS_PERIOD_BLE_CONNECT			11000		//ms

#define TACT_SWITCH_OPERATE_OVERTIME					5000


typedef enum
{
    TACT_SWITCH_NONE,
    TACT_SWITCH_VERITY_MODE_CHANGE,
    TACT_SWITCH_VERITY_OFF,
    TACT_SWITCH_VERITY_CONNECT,
} TactSwitch_RequirementTypeDef;

typedef struct
{
    TactSwitch_RequirementTypeDef						Requirement;
    bool												isConfirm;
} TactSwitch_StatusTypeDef;



//RGB
#define WATERFALL_LIGHT_ON_PERIOD						100

#define BLINK_LIGHT_ON_PERIOD							50
#define BLINK_PERIOD									100

#define RGB_UPDATE_PERIOD_STAND_BY						3		//s
#define RGB_UPDATE_PERIOD_FALL_DETECT_ROUTINE			1
#define RGB_UPDATE_PERIOD_HEART_RATE_FUNCTION			3
#define RGB_UPDATE_PERIOD_BLE_DISCONNECT				1

//Ble
#define BLE_UART 										huart2
#define BLE_BUFFER_LENGTH 								20
#define BLE_COMMANDS_LENGTH								10

typedef struct
{
	
	bool isAndroidCommand;
	bool isReturnComment;
	
	
	
	bool isSameFrame;
	uint32_t tickStart;
	
	
	bool isBaudRateChange;
	uint32_t baudRate;
	
}HJ_BLE_TypeDef;


#define BLE_HEADER_INDEX								0
#define BLE_FRAME_INDEX									1


#define BLE_HEADER_HR									0xF1
#define BLE_HEADER_PAH_BMP_DATA							0xF2
#define BLE_HEADER_MPU_DATA								0xF3

#define BLE_PAH_OFFSET									2
#define BLE_BMP_OFFSET									6
#define BLE_MPU_ACCEL_OFFSET							2
#define BLE_MPU_GYRO_OFFSET								8
#define BLE_MPU_MAGNETO_OFFSET							14



//PAH8001
#define PPG_BUFFER_LENGTH								500
#define HR_RECORD_LENGTH								500


// Task
#define TASK_UPDATE_PERIOD_HEART_RATE_FUNCTION			1						//minutes



#define Samplehtim 										htim2

#define TIM2_PERIOD										0.01


typedef struct
{
    uint8_t												Content[PPG_BUFFER_LENGTH];
    uint16_t											Length;
    YHY_StatusTypeDef									State;
    //NONE;
    //TODO:ready to be token out;
    //DOING:is adding;
    //DONE:has been token out;
} Array_Uint8TypeDef;



typedef struct
{
    uint32_t											Content[PPG_BUFFER_LENGTH];
    uint16_t											Length;
    YHY_StatusTypeDef									State;
    //NONE;
    //TODO:ready to be token out;
    //DOING:is adding;
    //DONE:has been token out;
} Array_Uint32TypeDef;


typedef struct
{
    float												Value;
    RTC_TimeTypeDef										TimeStamp;
} HR_TypeDef;


typedef struct
{
    HR_TypeDef											HeartRate[HR_RECORD_LENGTH];
    uint16_t											Length;
    YHY_StatusTypeDef									State;
    //NONE;
    //TODO:ready to be token out;
    //DOING:is adding;
    //DONE:has been token out;
} HR_ListTypeDef;



typedef struct
{
    uint8_t												Content[BLE_BUFFER_LENGTH];
    uint8_t												Lenght;
    YHY_StatusTypeDef									State;
    //NONE;
    //TODO:ready to be token out;
    //DOING:is adding;
    //DONE:has been token out;
} BLE_BufferTypeDef;




//specific system
typedef enum
{
    STAND_BY,			//stand by
    HEART_RATE_FUNCTION,//heart rate detect
    FALL_DETECT_ROUTINE,//fall down detect
    SYNC,				//sync mode
    CONFIGURATION,		//configration
} Work_ModeTypeDef;


typedef struct
{
    struct pt PT;
    YHY_StatusTypeDef status;
} Task_TypeDef;


typedef struct
{
    bool isUserFall;
    bool isBleConnected;
    bool isTactSwitchOperating;		// Tact switch is operating
	bool isCommandOperating;		// Master device send command
    bool isManualPause;
} Work_FlagTypeDef;



typedef struct
{
    Task_TypeDef Sample;
    Task_TypeDef Calculate;
    Task_TypeDef Store;
    Task_TypeDef BleTransmit;
    Task_TypeDef BleReceive;
    Task_TypeDef TactSwitch;

    //	NONE:hang up
    //	TODO:
    //	DOING:
    //	DONE:
    //	ERR:


    Work_ModeTypeDef Mode;		//current work mode

    Work_FlagTypeDef Flag;
} Task_ListTypeDef;


#endif
