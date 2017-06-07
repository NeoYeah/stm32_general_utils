#include "utils_systick_hal.h"


uint32_t gTickStart = 0;


bool isTimeOut(uint32_t tickStart, uint32_t timeOut)
{
    // is first time
    if(gTickStart == 0)
    {
        gTickStart = tickStart;
    }

    if((HAL_GetTick() - gTickStart) > timeOut)
    {
        gTickStart = 0;
        return true;
    }

    return false;
}


void resetTimeOut(void)
{
    gTickStart = 0;
}
