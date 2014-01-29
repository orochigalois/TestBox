/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               app_cfg.h
** Descriptions:            ucosii configuration
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-9
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
					  

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/
#define  DEF_DISABLED                    0
#define  DEF_ENABLED                     1

#define  OS_VIEW_MODULE                  DEF_DISABLED	     	/* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */


/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  OS_VIEW_TASK_PRIO               	(                 2)
#define  APP_TASK_TouchPanel_PRIO		 			(				   4)
#define  APP_TASK_UCGUI_PRIO             	(                 3)

//add azhao7
#define  APP_TASK_BLINK_PRIO          	 (OS_LOWEST_PRIO - 3)
#define  APP_TASK_UART_RECEIVE  	(OS_LOWEST_PRIO - 9)
#define  APP_TASK_CHECKBUTTON_PRIO                 	 5
//#define  APP_TASK_CHEKUDRLBUTTON_PRIO                6
#define  APP_TASK_OKBUTTONPROCESS_PRIO               10
#define  APP_TASK_CODERROTATEDPROCESS_PRIO           11
#define  APP_TASK_UPDOWNBUTTONPROCESS_PRIO           12
#define  APP_TASK_LEFTRIGHTBUTTONPROCESS_PRIO        13
#define  APP_TASK_MANUSELFTEST_PRIO        					 16


#define  APP_TASK_CANTESTPRESENT_PRIO                15
#define  CAN_TX_TASK_PRIO        										 14
//end azhao7

#define APP_TASK_CHECK_COMMAND_PRIO         (18)

#define  APP_TASK_START_PRIO                               1
#define  APP_TASK_OSVIEW_TERMINAL_PRIO	 (OS_LOWEST_PRIO - 6)
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)





/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_UCGUI_STK_SIZE                         512u 
#define  APP_TASK_TouchPanel_STK_SIZE					 					 256u
//add azhao7

#define  APP_TASK_UART_STK_SIZE                         128u
#define  APP_TASK_BLINK_STK_SIZE                         128u
#define  APP_TASK_CHECKBUTTON_STK_SIZE                 	 128u
//#define  APP_TASK_CHEKUDRLBUTTON_STK_SIZE                128u
#define  APP_TASK_OKBUTTONPROCESS_STK_SIZE               512u
#define  APP_TASK_CODERROTATEDPROCESS_STK_SIZE           512u
#define  APP_TASK_UPDOWNBUTTONPROCESS_STK_SIZE           512u
#define  APP_TASK_LEFTRIGHTBUTTONPROCESS_STK_SIZE        512u
#define  APP_TASK_MANUSELFTEST_STK_SIZE        512u

#define  APP_TASK_CANTESTPRESENT_STK_SIZE          			 256u //add azhao7

#define  CAN_TX_TASK_STK_SIZE                         	 128u
//end azhao7
#define  APP_TASK_START_STK_SIZE                          64u
#define  APP_TASK_OSVIEW_TERMINAL_STK_SIZE   			 				256u
#define  OS_VIEW_TASK_STK_SIZE                           	256u



/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED



#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

