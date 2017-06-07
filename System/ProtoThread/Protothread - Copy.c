/**
 ******************************************************************************
 * @file     Protothread.c
 * @author   showgu
 * @version  V0.1.0
 * @date     05-10-2015
 * @brief    Main Service Routines. State machine
 *           本文件是状态机的核心部分，该状态机不具备抢占功能，在本例的操作中实
 *           际已经演化成了按照时间片的方式了，支持阻塞操作。
 *           函数中不具备可重入型，不能使用局部变量
 *           本例在06-10-2015做了一个重要的修改，即：PT_Task.PT_State = do_idle;
 *           的设定需要设置一定的条件，理由是有些全局状态是有中断传回，由于状态
 *           机的机制，会导致中断传回的状态变量被 50 ms 的定时任务或者其他进行中
 *           的任务直接清空。
 ******************************************************************************
 ******************************************************************************
 */


#include "Protothread.h"


TASK_LIST gTaskList;


static PT_THREAD(doIdle(struct pt *pt))
{
    PT_BEGIN(pt);
    while (1)
    {
        PT_WAIT_UNTIL(pt, gTaskList.doIdle.state == TODO);
    }
    PT_END(pt);
}

// 一秒钟进入一次任务；
static PT_THREAD(doLed(struct pt *pt))
{
    PT_BEGIN(pt);
    while (1)
    {
        PT_WAIT_UNTIL(pt, gTaskList.doLed.state == TODO);
        //IM3_Sec_Count++;
        //        GPIO_TOGGLE(LED_PORT, LED2_PIN);
        //        HumidityControl(); //湿度控制
        if (gTaskList.doLed.state == DONE) // 2015-10-06 增加
            gTaskList.doIdle.state = TODO;
    }
    PT_END(pt);
}


//// 一秒钟进入一次任务；
//static PT_THREAD(Task_Sample(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_Sample);
//        GPIO_TOGGLE(LED_PORT, LED3_PIN);
//        Sht21_measure(); //湿度控制//
//        if (PT_Task.PT_State == Do_Sample) // 2015-10-06 增加
//            PT_Task.PT_State = Do_Idle;
//    }
//    PT_END(pt);
//}

//// 一秒钟进入一次任务；
//static PT_THREAD(Task_SendTemp(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_SendTemp);
//        Send_Code_To_Pannel(TEMP_Codetype); // 更新下位机温度

//    }
//    PT_END(pt);
//}

//// 一秒钟进入一次任务；
//static PT_THREAD(Task_SendHumi(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_SendHumi);
//        ; //LED的一些操作
//        Send_Code_To_Pannel(HUMI_Codetype); // 更新下位机温度
//    }
//    PT_END(pt);
//}
//// 一秒钟进入一次任务；
//static PT_THREAD(Task_485(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_485);
//        ; //LED的一些操作
//    }
//    PT_END(pt);
//}

//// 一秒钟进入一次任务；
//static PT_THREAD(Task_GetData(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_GetData);
//        Deal_code(); //LED的一些操作
//        PT_Task.PT_State = Do_Idle;
//    }
//    PT_END(pt);
//}



void ptInit(void)
{

    //对于结构体PT_Task的初始化
    PT_INIT(&gTaskList.doIdle.PT);
    PT_INIT(&gTaskList.doLed.PT);
}


void ptRun(void)
{
    doIdle(&gTaskList.doIdle.PT);
    doLed(&gTaskList.doLed.PT);
}



/*******************************************2015-9 sinjor****************************************/
