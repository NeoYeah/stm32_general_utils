#ifndef _UTILS_SYSTICK_HAL_
#define _UTILS_SYSTICK_HAL_


#include <stdbool.h>
#include <stdint.h>

#include "stm32l1xx_hal.h"




bool isTimeOut(uint32_t  tickStart, uint32_t timeOut);

void resetTimeOut(void);


#endif
