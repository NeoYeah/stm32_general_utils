/*****************************************************************

File		:	YD-Module\BLE_DA14580\BLE.h
Fuction		:
Author		:	@yehangyang
Version		:	V1.0
Time		:	30 Nov. 2015

*****************************************************************/

#ifndef _PAH8001_H_
#define _PAH8001_H_




#include <stdbool.h>

#include "stm32l1xx_hal.h"

#include "driver_i2c_hal.h"
#include "i2c.h"


#include "utils_array.h"




#define PAHi2c 		hi2c1
#define	PAHAddr		0x66

extern uint8_t gPAH8001Data[4];




/*bank0*********************************************************/


#define Configu	0x06		//the configuration of the sensor .Bit7-Reset;[6:4]-000;Bit3-PD_enh;[2:0]-010;
//For Configuration register
#define MNormal 0b00000010		//Normal operation mode (Default)
#define MPowerD 0b00001010		//Power down mode
#define MReset  0b10000010		//reset and the bit will be set to 0





uint8_t PAH8001_writeRegister(uint8_t reg, uint8_t data);
void PAH8001_init(void);
int8_t PAH8001_HRD(uint8_t *result);
uint8_t PAH8001_Int(void);

bool PAH_isTouched(void);
bool PAH_readData(uint8_t *result);




typedef enum
{
    POWER_DOWN,
    POWER_ON,

} POWER_MODE;


typedef enum
{
    Product_ID1 		= 0x00,		//Product_ID[11:4];read only
    Product_ID0 		= 0x01,		//Product_ID[3:0]; and Version_ID[3:0]
    Operation_Mode 		= 0x05,		//the register opration modes.[7:6]-10;[5:4]-slp_enh[1:0];bit3-Slp2_enh;bit2-Slp2For;Bit1=Slp1For;Bit0-Weakup
    Configuration 		= 0x06,
    Write_Protect 		= 0x09,
    Sleep1_Setting 		= 0x0A,
    Enter_Time 			= 0x0B,
    Sleep2_Setting 		= 0x0C,
    AE_EnH 				= 0x20,
    Exposure_Time_L 	= 0x32,
    Exposure_Time_H 	= 0x33,
    Touch_Resolution 	= 0x4D,
    Touch_Detection 	= 0x59,
} BANK0;

//For Operation_Mode register
#define M3000fps 0b10100000		//Disable sleep mode of 3000fps condition
#define M1000fps 0b10010000		//Disable sleep mode of 1000fps condition
#define MSleep1  0b10110000		//Enable sleep1 mode (normal mode to sleep1 mode with Enter_Time register about 1000ms)
#define MSleep2  0b10111000		//Enable sleep2 mode (normal mode to sleep1 mode with Enter_Time register about 1000ms and about 6s to sleep2 mode)
#define MFSleep1 0b10111100		//Force entering sleep2
#define MFSleep2 0b10110010		//Force entering sleep2
#define MFWeakup 0b10110001		//Force wakeup from sleep mode

//Write protect for the register bank0 0x0A~0x7F and bank1 0x00~0x7F
//For Write_Protect register
#define WP_ENABLE		0x00					//read only for those register(Default)
#define WP_DISABLE		0x5A					//read/written only

//For Touch Detection
#define TOUCH_ON	0x80
#define TOUCH_OFF	0x00



typedef enum
{
    SCI_Touch_EnH 	= 0x07,
    HR_Data_Algo_A 	= 0x1A,
    Frame_Average 	= 0x1B,
    HR_Data_Algo_C 	= 0x1C,
    Touch_TH 		= 0x23,
    Touch_TH_S_L 	= 0x25,
    Touch_TH_S_H 	= 0x26,
    LED_Step 		= 0x38,
    HR_Data_A 		= 0x64,
    HR_Data_B 		= 0x65,
    HR_Data_C 		= 0x66,
    HR_Data_D 		= 0x67,
    HR_Data_Ready 	= 0x68,
} BANK1;



HAL_StatusTypeDef PAH8001_writeRegisterBank0(BANK0 reg, uint8_t data);
HAL_StatusTypeDef PAH8001_writeRegisterBank1(BANK1 reg, uint8_t data);

uint8_t PAH8001_readRegisterBank0(BANK0 reg);
uint8_t PAH8001_readRegisterBank1(BANK1 reg);

void PAH8001_getHeartRateData(void);


#define PAH8001_ENABLE_W_R				PAH8001_writeRegisterBank0(Write_Protect, WP_ENABLE);	//enable read and write
#define PAH8001_MODIFY_BANK0			PAH8001_writeRegister(0x7F, 0x00);						//bank0
#define PAH8001_MODIFY_BANK1			PAH8001_writeRegister(0x7F, 0x01);						//bank1


#define PAH8001_POWER_DOWN				PAH8001_writeRegister(0x06, 0x0A);						//Power down
#define PAH8001_POWER_UP				PAH8001_writeRegister(0x06, 0x02);						//Power up

#define TOUCH_DETECT_TIME_OUT			32000000*1


#endif
