#ifndef _TESTPRESENT_H_
#define _TESTPRESENT_H_

//#include "lpc177x_8x_can.h"
#include "includes.h"
#include "can_handling.h"
#include "app_cfg.h"

//#define  	APP_TASK_CANTESTPRESENT_PRIO             (10)//add azhao7
//#define  	APP_TASK_CANTESTPRESENT_STK_SIZE          32u //add azhao7
//test present
static  OS_STK         App_Task_CANTESTPRESENT_Stk        [APP_TASK_CANTESTPRESENT_STK_SIZE];//azhao7

//extern CAN_MSG_Type TXMsg;        //save the transmit CAN messages and maintain the sending timer ticks
//extern unsigned int uiFlagSendMsg;

static void uctsk_CANTESTPRESENT    (void);//azhao7
void  App_CANTESTPRESENT_TaskCreate (void);//azhao7

#endif
