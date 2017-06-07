#ifndef _VERITY_THREAD_H_
#define _VERITY_THREAD_H_
#include "pt-sem.h"

#include "VerityInclude.h"



#include "Task_Sample.h"
#include "Task_Calculate.h"
#include "Task_RTControler.h"
#include "Task_BleTransmit.h"
#include "Task_TactSwitch.h"
#include "Task_BleReceive.h"

static PT_THREAD(taskSample(struct pt *pt));
static PT_THREAD(taskCalculate(struct pt *pt));
static PT_THREAD(taskTransmit(struct pt *pt));
static PT_THREAD(taskTactSwitch(struct pt *pt));
static PT_THREAD(taskBleReceive(struct pt *pt));


void ptInit(void);
void ptRun(void);

void setWorkMode(Task_ListTypeDef *taskList, Work_ModeTypeDef mode);

void setFlagBleConnected(Task_ListTypeDef *taskList, bool isConnected);
void setFlagTactSwitchOperating(Task_ListTypeDef *taskList, bool isOperating);
void setFlagCommandOperating(Task_ListTypeDef *taskList, bool isOperating);
void setFlagUserFall(Task_ListTypeDef *taskList, bool isFall);
void setFlagManualPause(Task_ListTypeDef *taskList, bool isPause);

void refreshTaskList(Task_ListTypeDef *taskList);
//void resetTaskList(Task_ListTypeDef *taskList);
#endif

/*******************************************2015-9 sinjor****************************************/
