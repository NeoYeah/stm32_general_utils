#ifndef _PROTOTHREAD_H_
#define _PROTOTHREAD_H_
#include "pt-sem.h"
//#include "config.h"




typedef enum
{
    TODO,
    DOING,
    DONE,
} STATE;

typedef struct
{
    struct pt PT;
    STATE state;
} TASK;



//specific system

typedef struct
{
    TASK doIdle;
    TASK doLed;
    TASK doKey;
    TASK doSample;
    TASK doBluetooth;

} TASK_LIST;

typedef enum
{
    CONFIG,		//configration
    LOW_POWER,	//low power consumption
    REAL_TIME,	//real time mode
    SYNC,		//sync mode
} MODE;


void PT_machine(void);

static PT_THREAD(doIdle(struct pt *pt));
static PT_THREAD(doLed(struct pt *pt));


void ptInit(void);
void ptRun(void);



#endif

/*******************************************2015-9 sinjor****************************************/
