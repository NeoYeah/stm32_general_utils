/**
 ******************************************************************************
 * @file     Protothread.c
 * @author   showgu
 * @version  V0.1.0
 * @date     05-10-2015
 * @brief    Main Service Routines. State machine
 *           ���ļ���״̬���ĺ��Ĳ��֣���״̬�����߱���ռ���ܣ��ڱ����Ĳ�����ʵ
 *           ���Ѿ��ݻ����˰���ʱ��Ƭ�ķ�ʽ�ˣ�֧������������
 *           �����в��߱��������ͣ�����ʹ�þֲ�����
 *           ������06-10-2015����һ����Ҫ���޸ģ�����PT_Task.PT_State = do_idle;
 *           ���趨��Ҫ����һ������������������Щȫ��״̬�����жϴ��أ�����״̬
 *           ���Ļ��ƣ��ᵼ���жϴ��ص�״̬������ 50 ms �Ķ�ʱ�����������������
 *           ������ֱ����ա�
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

// һ���ӽ���һ������
static PT_THREAD(doLed(struct pt *pt))
{
    PT_BEGIN(pt);
    while (1)
    {
        PT_WAIT_UNTIL(pt, gTaskList.doLed.state == TODO);
        //�TIM3_Sec_Count++;
        //        GPIO_TOGGLE(LED_PORT, LED2_PIN);
        //        HumidityControl(); //ʪ�ȿ���
        if (gTaskList.doLed.state == DONE) // 2015-10-06 ����
            gTaskList.doIdle.state = TODO;
    }
    PT_END(pt);
}


//// һ���ӽ���һ������
//static PT_THREAD(Task_Sample(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_Sample);
//        GPIO_TOGGLE(LED_PORT, LED3_PIN);
//        Sht21_measure(); //ʪ�ȿ���//
//        if (PT_Task.PT_State == Do_Sample) // 2015-10-06 ����
//            PT_Task.PT_State = Do_Idle;
//    }
//    PT_END(pt);
//}

//// һ���ӽ���һ������
//static PT_THREAD(Task_SendTemp(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_SendTemp);
//        Send_Code_To_Pannel(TEMP_Codetype); // ������λ���¶�

//    }
//    PT_END(pt);
//}

//// һ���ӽ���һ������
//static PT_THREAD(Task_SendHumi(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_SendHumi);
//        ; //LED��һЩ����
//        Send_Code_To_Pannel(HUMI_Codetype); // ������λ���¶�
//    }
//    PT_END(pt);
//}
//// һ���ӽ���һ������
//static PT_THREAD(Task_485(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_485);
//        ; //LED��һЩ����
//    }
//    PT_END(pt);
//}

//// һ���ӽ���һ������
//static PT_THREAD(Task_GetData(struct pt *pt))
//{
//    PT_BEGIN(pt);
//    while (1)
//    {
//        PT_WAIT_UNTIL(pt, PT_Task.PT_State == Do_GetData);
//        Deal_code(); //LED��һЩ����
//        PT_Task.PT_State = Do_Idle;
//    }
//    PT_END(pt);
//}



void ptInit(void)
{

    //���ڽṹ��PT_Task�ĳ�ʼ��
    PT_INIT(&gTaskList.doIdle.PT);
    PT_INIT(&gTaskList.doLed.PT);
}


void ptRun(void)
{
    doIdle(&gTaskList.doIdle.PT);
    doLed(&gTaskList.doLed.PT);
}



/*******************************************2015-9 sinjor****************************************/
