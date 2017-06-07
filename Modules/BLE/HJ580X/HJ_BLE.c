

/*****************************************************************

File			:	YD-Module\BLE_DA14580\BLE.c
Fuction		:	Power management chip
Author		:	@yehangyang
Version		:	V1.0
Time			:	30 Nov. 2015

*****************************************************************/
#include "HJ_BLE.h"



#include "gpio.h"
#include "usart.h"


uint8_t			gBleRxBuffer[BLE_COMMANDS_LENGTH]={0};
HJ_BLE_TypeDef	gHjBleTypeDef= {false};


/*****************************************************************
Name		:	void HJ_BLE_setRole(bool isMaster)
Fuction		:	the BLE role select
Input		:	BLE role mode (PA5	BLE_SCK Low:Master ; High:Slave)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time		:	30 Nov. 2015
*****************************************************************/
void HJ_BLE_setRole(bool isMaster)
{
    if(isMaster)
    {
        HAL_GPIO_WritePin(HJ_BLE_ROLE_SELECT_GPIO_Port, HJ_BLE_ROLE_SELECT_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(HJ_BLE_ROLE_SELECT_GPIO_Port, HJ_BLE_ROLE_SELECT_Pin, GPIO_PIN_SET);
    }
}

/*****************************************************************
Name		:	void HJ_BLE_setOnWork(bool isOnWork)
Fuction		:	the BLE config and transparent serial mode
Input		:	bool isConfig (PA6	BLE_MOD Low:Config ; High:Transparent serial)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time		:	30 Nov. 2015
*****************************************************************/
void HJ_BLE_setOnWork(bool isOnWork)
{
    if(isOnWork)
    {
        HAL_GPIO_WritePin(HJ_BLE_CONFIG_MODE_GPIO_Port, HJ_BLE_CONFIG_MODE_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(HJ_BLE_CONFIG_MODE_GPIO_Port, HJ_BLE_CONFIG_MODE_Pin, GPIO_PIN_RESET);
    }
}

/*****************************************************************
Name		:	void HJ_BLE_setWakeUp(CFGMode mode)
Fuction		:	the BLE wake up & power down
Input		:	BLE power mode (PB0	HJ_BLE_setWakeUp Low:weak up ; High:power down)
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	30 Nov. 2015
*****************************************************************/
void HJ_BLE_setWakeUp(bool isWakeUp)
{
    if(isWakeUp)
    {
        HAL_GPIO_WritePin(HJ_BLE_WAKE_UP_GPIO_Port, HJ_BLE_WAKE_UP_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(HJ_BLE_WAKE_UP_GPIO_Port, HJ_BLE_WAKE_UP_Pin, GPIO_PIN_SET);
    }
}

/*****************************************************************
Name		:	bool HJ_BLE_isConnected(void)
Fuction		:	the BLE connect state
Input		:	void
Output		:	the value of connect state
						(PA4	BLE_CON Low:connected ; High:disconnected)
Author		:	@yehangyang
Version		:	V0.1
Time			:	30 Nov. 2015
*****************************************************************/
bool HJ_BLE_isConnected(void)
{
    if(HAL_GPIO_ReadPin(HJ_BLE_CONNECT_STATE_GPIO_Port, HJ_BLE_CONNECT_STATE_Pin) == GPIO_PIN_RESET)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*****************************************************************
Name		:	uint8_t HJ_BLE_getDataReadySignal(void)
Fuction		:	the BLE data received state
Input		:	void
Output		:	the value of data received state
						(PA7 HJ_BLE_getDataReadySignal Low:data received and delay 10ms ; High: no data)
Author		:	@yehangyang
Version		:	V0.1
Time			:	30 Nov. 2015
*****************************************************************/
uint8_t HJ_BLE_getDataReadySignal(void)
{
    if(HAL_GPIO_ReadPin(HJ_BLE_DATA_READY_GPIO_Port, HJ_BLE_DATA_READY_Pin) == GPIO_PIN_RESET)
        return 0;
    else
        return 1;
}

/*****************************************************************
Name		:	HAL_StatusTypeDef HJ_BLE_Transmit(uint8_t *pData, uint16_t Size)
Fuction		:	the BLE transmit data
Input		:	the data that need to transmit
Output		:	HAL Status of uart
Author		:	@yehangyang
Version		:	V0.1
Time		:	30 Nov. 2015
*****************************************************************/
HAL_StatusTypeDef HJ_BLE_Transmit(uint8_t *pData, uint16_t Size)
{
    return HAL_UART_Transmit_DMA(&BLE_UART, pData, Size);
}


void HJ_BLE_setBond(bool isBond)
{
    HJ_BLE_setWakeUp(true);
    HJ_BLE_setOnWork(false);				// switch to Config Mode

    HAL_Delay(100);

    if(isBond)
    {
        HAL_UART_Transmit_DMA(&BLE_USART, "<BONDMACXXXXXX>", 15);
    }
    // Disbond
    else
    {
        HAL_UART_Transmit_DMA(&BLE_USART, "<DISBOND>", 9);
    }


    HJ_BLE_setOnWork(true);
    HJ_BLE_setWakeUp(false);
}

/*****************************************************************
Name		:	void HJ_BLE_Reset(void)
Fuction		:	reset the BLE
Input		:	void
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	30 Nov. 2015
*****************************************************************/
void HJ_BLE_Reset(void)
{
    HJ_BLE_setOnWork(false);
    HAL_UART_Transmit(&BLE_USART, "<RESET>",   12, 100);
    HJ_BLE_setOnWork(true);
}

void HJ_BLE_doDisconnect(void)
{
    HJ_BLE_setWakeUp(true);
    HJ_BLE_setOnWork(false);

    //->proccess here

    HJ_BLE_setOnWork(true);
    HJ_BLE_setWakeUp(false);
}

/*****************************************************************
Name		:	void HJ_BLE_setBleBaudRate(uint32_t value)
Fuction		:	config the Baud
Input		:	baud value
Output		:	void
Author		:	@yehangyang
Version		:	V0.1
Time			:	30 Nov. 2015
*****************************************************************/
HAL_StatusTypeDef HJ_BLE_setBleBaudRate(HJ_BLE_TypeDef *hjBleTypeDef,uint32_t baudRate)
{

	hjBleTypeDef->isBaudRateChange=true;
    hjBleTypeDef->baudRate=baudRate;
	
//	HAL_UART_Receive_DMA(&BLE_USART, (uint8_t *)gHjBleFeedback, HJ_BLE_FEEDBACK_LENGTH);
    HAL_Delay(100);

    switch(hjBleTypeDef->baudRate)
    {
    case 4800:
        return   HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD4800>",   10);
        
    case 9600:
        return   HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD9600>",   10);
        
    case 19200:
        return    HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD19200>",  11);
        
    case 38400:
        return    HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD38400>",  11);
        
    case 57600:
        return   HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD57600>",  11);
        
    case 115200:
        return   HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD115200>", 12);
        
    case 256000:
        return   HAL_UART_Transmit_DMA(&BLE_USART, "<BAUD256000>", 12);
        
    default:
        return HAL_ERROR;
    }


}


HAL_StatusTypeDef HJ_BLE_setUsartBaudRate(HJ_BLE_TypeDef *hjBleTypeDef)
{
    HAL_Delay(100);
    BLE_USART.Init.BaudRate = hjBleTypeDef->baudRate;
	return HAL_UART_Init(&BLE_USART);
}





void HJ_BLE_init(HJ_BLE_TypeDef *hjBleTypeDef)
{
    HJ_BLE_setWakeUp(true);

    HJ_BLE_setRole(false);

    HJ_BLE_setOnWork(false);				// switch to Config Mode

    if( HJ_BLE_setBleBaudRate(hjBleTypeDef,115200)==HAL_OK)
    {
		HJ_BLE_setUsartBaudRate(hjBleTypeDef);
    }
    HJ_BLE_setOnWork(true);

    HJ_BLE_setWakeUp(false);
	
	
	HAL_UART_DMAStop(&BLE_USART);
	HAL_UART_Receive_DMA(&BLE_USART, (uint8_t *)gBleRxBuffer, BLE_COMMANDS_LENGTH);
}



