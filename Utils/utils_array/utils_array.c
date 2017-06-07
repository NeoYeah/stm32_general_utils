#include "utils_array.h"


YHY_StatusTypeDef PPG_BUFFER_addOne(Array_Uint8TypeDef *in, int8_t from)
{

    if(in->Length == (PPG_BUFFER_LENGTH - 1)) //last one
    {
        in->Content[in->Length] = from;
        in->State = TODO;					//full and ready to be token out


    }
    else if(in->Length < (PPG_BUFFER_LENGTH - 1))
    {
        in->State = DOING;

        in->Content[in->Length] = from;

        in->Length++;
    }
    else
    {
        return ERR;
    }
    return DONE;
}


YHY_StatusTypeDef HR_ListAddOne(HR_ListTypeDef *in, float hr)
{

    if(in->Length == (PPG_BUFFER_LENGTH - 1)) //last one
    {
        in->HeartRate[in->Length].Value = hr;
        HAL_RTC_GetTime(&hrtc, &(in->HeartRate[in->Length].TimeStamp), RTC_FORMAT_BCD);

        in->State = TODO;					//full and ready to be token out
    }
    else if(in->Length < (PPG_BUFFER_LENGTH - 1))
    {
        in->State = DOING;

        in->HeartRate[in->Length].Value = hr;
        HAL_RTC_GetTime(&hrtc, &(in->HeartRate[in->Length].TimeStamp), RTC_FORMAT_BCD);

        in->Length++;
    }
    else
    {
        return ERR;
    }

    return DONE;
}
