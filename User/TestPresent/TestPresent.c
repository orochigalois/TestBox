#include "TestPresent.h"

CAN_MSG_Type TestPresent_TxMSG;

extern uint8_t bClusterDiagModeAvailable;
extern uint8_t bClusterManuModeAvailable;
//==============================================================================
// DESCRIPTION : App_CANTESTPRESENT_TaskCreate() Create testpresent task
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
void  App_CANTESTPRESENT_TaskCreate (void)//azhao7
{
	OSTaskCreate((void (*)(void *)) uctsk_CANTESTPRESENT,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_CANTESTPRESENT_Stk[APP_TASK_CANTESTPRESENT_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_CANTESTPRESENT_PRIO  );	
	
}
//==============================================================================
// DESCRIPTION : uctsk_CANTESTPRESENT() Send testpresent MSG circly
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void uctsk_CANTESTPRESENT  (void)//azhao7
{
		TestPresent_TxMSG.format = STD_ID_FORMAT;
    TestPresent_TxMSG.id = 0x728;
    TestPresent_TxMSG.len = 8;
    TestPresent_TxMSG.type = DATA_FRAME;
    
	  TestPresent_TxMSG.dataA[0] = 0x02;
	  TestPresent_TxMSG.dataA[1] = 0x3e;
		memset(TestPresent_TxMSG.dataA + 2 ,0,2);
		memset(TestPresent_TxMSG.dataB,0,4);
	
	for ( ; ; )
	{
		if((bClusterDiagModeAvailable)||(bClusterManuModeAvailable))
		{
			CAN_SendMsg(CAN_ID_1, &TestPresent_TxMSG);
		}
		OSTimeDlyHMSM(0,0,20,0);
	}
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
