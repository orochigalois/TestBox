/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MenuDisp.c
** Descriptions:            The MenuDisp application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2013-12-15
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

/* Includes ------------------------------------------------------------------*/
#include "emc_nand.h"
#include "MenuDisp.h"
#include "MenuID_define.h"
#include "MenuDispcontextdefine.h"
#include "BlockDisp.h"
#include "CoderProcess.h"
#include "CoderDisp.h"
#include "debug_frmwrk.h"

/* alex   2014/1/23 alex */


extern uint8_t isSmileRunning;
extern uint32_t PC;
					

uint8_t bClusterAvailable = 0xff;
uint8_t bClusterManuModeAvailable = 0x00;

extern uint8_t bCAN_SendMSGING;
extern uint8_t bCAN_ReceiveMSGING;		
extern uint8_t PositiveRes_Flag;

extern uint8_t RXDataBuffer[21];

sManuStruc_Type CurManuSelected_Struc = {MainMenu_Session,0,0,MainMenu,MainMenu_Session,0,0,0,MainMenu_Count}; 

uint8_t 	u8CoderValState = 0;
uint8_t 	u8UpDownValState = 0;
uint8_t 	u8LeftRightValState = 0;

OS_EVENT  *ProCoderValSem;
OS_EVENT  *ProOKButtonSem;
OS_EVENT  *ProLeftRightButtonSem;
OS_EVENT  *ProUpDownButtonSem;

OS_TMR   	*CANRXProcess_Timer; 
OS_TMR   	*CANRXProcess_TimerAlex; 
uint8_t    CANRXProcess_Timer_Count = 0;

static  OS_STK 	App_TaskUart_Stk          							[APP_TASK_UART_STK_SIZE];
static  OS_STK 	App_TaskBlink_Stk          							[APP_TASK_BLINK_STK_SIZE];
static  OS_STK 	App_Task_CheckButtionPressed_Stk     		[APP_TASK_CHECKBUTTON_STK_SIZE];
static  OS_STK	App_Task_OKButtonProcess_Stk       			[APP_TASK_OKBUTTONPROCESS_STK_SIZE];
static  OS_STK	App_Task_CoderRotatedProcess_Stk       	[APP_TASK_CODERROTATEDPROCESS_STK_SIZE];
static  OS_STK	App_Task_UpDownButtonProcess_Stk       	[APP_TASK_UPDOWNBUTTONPROCESS_STK_SIZE];
static  OS_STK	App_Task_LeftRightButtonProcess_Stk     [APP_TASK_LEFTRIGHTBUTTONPROCESS_STK_SIZE];
static  OS_STK	App_Task_ManuSelfTest_Stk     					[APP_TASK_MANUSELFTEST_STK_SIZE];
//==============================================================================
// DESCRIPTION : App_UCGUI_TaskCreate() Create the used tasks
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================																																							
void  App_UCGUI_TaskCreate (void)
{
    INT8U  os_err;

		//os_err = os_err; 
	
		ProCoderValSem = OSSemCreate (1);
		ProOKButtonSem = OSSemCreate (1);
		ProLeftRightButtonSem = OSSemCreate (1);
		ProUpDownButtonSem = OSSemCreate (1);
   
		APP_UCGUI_Init();

		os_err = OSTaskCreate((void (*)(void *)) uctsk_uart,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_TaskUart_Stk[APP_TASK_UART_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_UART_RECEIVE  );							
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_UART_RECEIVE, "Serial Port Receive", &os_err);
		#endif
		
	
		os_err = OSTaskCreate((void (*)(void *)) uctsk_Blink,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_TaskBlink_Stk[APP_TASK_BLINK_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_BLINK_PRIO  );							
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task LED Blink", &os_err);
		#endif
    
		os_err = OSTaskCreate((void (*)(void *)) uctsk_CheckButtonPressed, 
                          (void   *) 0,
                          (OS_STK *) &App_Task_CheckButtionPressed_Stk[APP_TASK_CHECKBUTTON_STK_SIZE - 1],
                          (INT8U   ) APP_TASK_CHECKBUTTON_PRIO );
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task Check OK Button", &os_err);
		#endif
		
		os_err = OSTaskCreate((void (*)(void *)) uctsk_OKButtonProcess,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_OKButtonProcess_Stk[APP_TASK_OKBUTTONPROCESS_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_OKBUTTONPROCESS_PRIO);  
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task OK Button Process", &os_err);
		#endif		
		
    os_err = OSTaskCreate((void (*)(void *)) utsk_CoderRotatedProcess,
                           (void       *) 0, 
                           (OS_STK     *)&App_Task_CoderRotatedProcess_Stk[APP_TASK_CODERROTATEDPROCESS_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_CODERROTATEDPROCESS_PRIO  ); 
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task Coder Rotated Process", &os_err);
		#endif	

		os_err = OSTaskCreate((void (*)(void *)) utsk_UpDownButtonProcess,
                           (void       *) 0, 
                           (OS_STK     *)&App_Task_UpDownButtonProcess_Stk[APP_TASK_UPDOWNBUTTONPROCESS_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_UPDOWNBUTTONPROCESS_PRIO  ); 
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task Up Down Button Process", &os_err);
		#endif

		os_err = OSTaskCreate((void (*)(void *)) utsk_LeftRightButtonProcess,
                           (void       *) 0, 
                           (OS_STK     *)&App_Task_LeftRightButtonProcess_Stk[APP_TASK_LEFTRIGHTBUTTONPROCESS_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_LEFTRIGHTBUTTONPROCESS_PRIO  ); 
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task Right Left Button Process", &os_err);
		#endif	
		
		os_err = OSTaskCreate((void (*)(void *)) utsk_ManuSelfTest,
                           (void       *) 0, 
                           (OS_STK     *)&App_Task_ManuSelfTest_Stk[APP_TASK_MANUSELFTEST_STK_SIZE - 1],
                           (INT8U           ) APP_TASK_MANUSELFTEST_PRIO  ); 
		#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task Manufactury Selftest", &os_err);
		#endif
		//create a timer used to detect the RX CAN timeout
		CANRXProcess_Timer = OSTmrCreate(0,  10,  OS_TMR_OPT_PERIODIC, CANRXProcesstask, NULL, (INT8U *)"CANTimeoutTimer" ,&os_err); 
		CANRXProcess_TimerAlex = OSTmrCreate(0,  10,  OS_TMR_OPT_PERIODIC, CANRXProcesstaskAlex, NULL, (INT8U *)"CANTimeoutTimer" ,&os_err); 
}	
//==============================================================================
// DESCRIPTION : ClusterInforInit() Initial the cluster infor aear
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
void ClusterInforInit(void)
{
		GUI_RECT RectCluster =  {CLUSTER_INFOR_AREA_ULX, CLUSTER_INFOR_AREA_ULY, CLUSTER_INFOR_AREA_LRX, CLUSTER_INFOR_AREA_LRY};
		GUI_SetBkColor(GUI_BLACK);  
		GUI_ClearRect(CLUSTER_INFOR_FRAME_ULX, CLUSTER_INFOR_FRAME_ULY,CLUSTER_INFOR_FRAME_LRX,CLUSTER_INFOR_FRAME_LRY);  
		GUI_SetColor(PRO_BACK_COLOR);
		GUI_FillRectEx(&RectCluster);
		GUI_SetBkColor(PRO_BACK_COLOR);
		GUI_SetFont(&GUI_Font16B_ASCII);//GUI_FontComic18B_ASCII
		GUI_SetColor(PRO_FONT_COLOR);
		GUI_GotoXY(CLUSTER_INFOR_IDENTIFY_X, CLUSTER_INFOR_IDENTIFY_Y);
		GUI_DispString("Cluster Infor:");
		GUI_GotoXY(RESPONSE_IDENTIFY_X, RESPONSE_IDENTIFY_Y);
		GUI_DispString("Response Infor:");

		ClusterStatus(NoCluster);
}
//==============================================================================
// DESCRIPTION : APP_UCGUI_Init() Initial the mode
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
void APP_UCGUI_Init (void)
{
		GUI_Init();
    BSP_KEY_Init();
		
		GUI_SetBkColor(PRO_BACK_COLOR);	
		GUI_Clear(); //Clear mainmenu disp region
	  
		CurMenuInit(CurManuSelected_Struc, FirstPage);
		ClusterInforInit();

}

void CANRXProcesstaskAlex(void *ptmr, void *parg)
{


	if(isSmileRunning)
	{


		DispAlex(PC);


		//_DBG(readBuff);
	

 
//		DispAlex(RXDataBuffer);
//		isSmileRunning=0;

	}
}
//==============================================================================
// DESCRIPTION : CANRXProcesstask() CAN RX timer process
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
void CANRXProcesstask(void *ptmr, void *parg)
{
		uint8_t os_err;
		
	
		if(CANRXProcess_Timer_Count >= 50)//5s timeout
		{
			CANRXProcess_Timer_Count = 0;
			OSTmrStop(CANRXProcess_Timer,OS_TMR_OPT_NONE,NULL,&os_err);
			
			if(bClusterAvailable == 0x00)
			{
				ClusterStatus(NoCluster);
				bClusterAvailable = 0xff;
			}
			else
			{
				CommuniteStatus(TimeOutError);
			}
		}
		else if(PositiveRes_Flag > 0)//Time out not occured
		{
			OSTmrStop (CANRXProcess_Timer,OS_TMR_OPT_PERIODIC,CANRXProcesstask,&os_err);
			if(PositiveRes_Flag == 1)//Positive response
			{
				if(bClusterAvailable == 0x00)
				{
					if((RXDataBuffer[1] == 0x50)&&(RXDataBuffer[2] == 0x60))
					{
						ClusterStatus(ClusterAvailable);
						bClusterAvailable = 0x01;
					}
					else if((RXDataBuffer[1] == 0x62)&&(RXDataBuffer[2] == 0xfd)&&(RXDataBuffer[3] == 0x60)&&(RXDataBuffer[4] == 0x01))
					{
						ClusterStatus(ClusterInManuSession);
						bClusterAvailable = 0xfe;
						bClusterManuModeAvailable = 1;
					}
					else
					{
						bClusterAvailable = 0xff;
					}
				}
				else
				{
					CommuniteStatus(PositiveResponse);
					if(CurManuSelected_Struc.MainMenu_ID == MainMenu_Session)
					{
						if((CurManuSelected_Struc.SecMenu_ID == SecSession_EnterManuSession)&&
							(CurManuSelected_Struc.SubSecMenu_ID == SubSecMenu_EnterManuSession_JCIEOLSession))
						{
							bClusterManuModeAvailable = 1;
							ClusterStatus(ClusterInManuSession);
						}
						else if((CurManuSelected_Struc.SecMenu_ID == SecSession_ExistManuSession)&&
							(CurManuSelected_Struc.SubSecMenu_ID == SubSecMenu_ExsitManuSession_JCIEOLSession))
						{
							bClusterManuModeAvailable = 0;
							ClusterStatus(ClusterOutManuSession);
						}
					}
					if((CurManuSelected_Struc.MainMenu_ID == MainMenu_ReadDataByID)||
						((CurManuSelected_Struc.MainMenu_ID == MainMenu_Routine)&&(CurManuSelected_Struc.CurMenuID == SecMenu)))
					{
						DispBlockContext(CurManuSelected_Struc,RXDataBuffer);
					}
					if((RXDataBuffer[1] == 0x67)&&(RXDataBuffer[2] == 0x61))
					{
						OSTmrStart(CANRXProcess_Timer,&os_err);
						CAN_CRC_Calculate(RXDataBuffer);
					}
				}
			}
			else//Negtive response
			{
				if(bClusterAvailable == 0x00)
				{
					if(RXDataBuffer[2] == 0x10)
					{
						ClusterStatus(ClusterAvailable);
						bClusterAvailable = 0x01;
					}
					else if(RXDataBuffer[2] == 0x22)
					{
						ClusterStatus(ClusterOutManuSession);
						bClusterAvailable = 0xfe;
					}
					else
					{
						bClusterAvailable = 0xff;
					}
				}
				else
				{
					CommuniteStatus(PositiveRes_Flag);
				}
			}
			PositiveRes_Flag = 0;
			CANRXProcess_Timer_Count = 0;
		}
		else//Time out check
		{
			CANRXProcess_Timer_Count ++;
		}
}


//==============================================================================
// DESCRIPTION : uctsk_uart() 
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void uctsk_uart (void) 
{       
    for(;;)
   	{ 
		uint8_t c[256];

//		if(_DG_NONBLOCK(c))
//		{
//			_DBG(c);
//					receiveBuff[RxIndex] = c[RxIndex]; 
//				RxIndex++;
//		}
		OSTimeDlyHMSM(0, 0, 0, 30);	 
        
//		receiveBuff[RxIndex] = c; 
//		RxIndex++;
        
        //OSTimeDlyHMSM(0, 0, 1, 0);	 
//        receiveBuff[RxIndex]='\0';
//		_DBG(receiveBuff);
    }
}


//==============================================================================
// DESCRIPTION : uctsk_Blink() LED blink when receive or send CAN MSG
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void uctsk_Blink (void) 
{       
    for(;;)
   	{ 
        if ((bCAN_SendMSGING == 1)||(bCAN_ReceiveMSGING == 1))//when sending or receiving msg CAN1 LED blinking
        {
            bCAN_SendMSGING = 0;
						bCAN_ReceiveMSGING = 0;
            TURN_LED_1_ON();
            OSTimeDlyHMSM(0, 0, 0, 20);	 /* 20 MS  */
            TURN_LED_1_OFF();
            OSTimeDlyHMSM(0, 0, 1, 800);	 
            TURN_LED_1_ON();
            OSTimeDlyHMSM(0, 0, 0, 20);	
            TURN_LED_1_OFF();
            OSTimeDlyHMSM(0, 0, 1, 800);
        }
        else
        {
            OSTimeDlyHMSM(0, 0, 4, 0);	
        }
				    
        OSTimeDlyHMSM(0, 0, 1, 0);	 
    }
}
//==============================================================================
// DESCRIPTION : uctsk_Blink() LED blink when receive or send CAN MSG
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void utsk_ManuSelfTest (void) 
{ 
		uint8_t err;	
    for(;;)
   	{ 
			if(bClusterAvailable == 0xff)
			{
				bClusterAvailable = 0x00;
				OSTmrStart(CANRXProcess_Timer,&err);
				//SessionControlRequest(0, 1);//10 60
			}
			else if(bClusterAvailable == 0x01)
			{
				bClusterAvailable = 0x00;
				OSTmrStart(CANRXProcess_Timer,&err);
				ReadDataByIDRequest(21);//22 fd 60
				OSTaskDel(APP_TASK_MANUSELFTEST_PRIO);
			}
			else
			{
			}
				    
      OSTimeDlyHMSM(0, 0, 2, 0);	 
    }
}
//==============================================================================
// DESCRIPTION : uctsk_CheckButtonPressed() Check if Button pressed
//																					OK UP DOWN LEFT RIGHT
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
void uctsk_CheckButtonPressed (void)//Check if button pressed
{   
    for ( ; ; )
    {
			//OK Button
			if (!((GPIO_ReadValue (BRD_KEY_OK_PORT)) & (0x01 << BRD_KEY_OK_PIN)))
			{
					OSTimeDlyHMSM(0, 0, 1, 500);
					OSSemPost(ProOKButtonSem);
			}

			//Up Down button
			if (!((GPIO_ReadValue (BRD_KEY_UP_PORT)) & (0x01 << BRD_KEY_UP_PIN)))//Up Button
			{
				OSTimeDlyHMSM(0, 0, 1, 500);
				u8UpDownValState = UPDOWN_BOTTON_STATE_UPPRESSED;
				
        OSSemPost(ProUpDownButtonSem);
			}
			if (!((GPIO_ReadValue (BRD_KEY_DOWN_PORT)) & (0x01 << BRD_KEY_DOWN_PIN)))//Down Button
			{
				OSTimeDlyHMSM(0, 0, 1, 500);
				u8UpDownValState = UPDOWN_BOTTON_STATE_DOWNPRESSED;
				
        OSSemPost(ProUpDownButtonSem);
			}
			
			//Left Right Button
			if (!((GPIO_ReadValue (BRD_KEY_LEFT_PORT)) & (0x01 << BRD_KEY_LEFT_PIN)))//Left Button
			{
				OSTimeDlyHMSM(0, 0, 1, 500);
				u8LeftRightValState = LEFTRIGHT_BOTTON_STATE_LEFTPRESSED;
				
        OSSemPost(ProLeftRightButtonSem);
			}
			if (!((GPIO_ReadValue (BRD_KEY_RIGHT_PORT)) & (0x01 << BRD_KEY_RIGHT_PIN)))//Right Button
			{
				OSTimeDlyHMSM(0, 0, 1, 500);
				u8LeftRightValState = LEFTRIGHT_BOTTON_STATE_RIGHTPRESSED;
				
        OSSemPost(ProLeftRightButtonSem);
			}
			
			OSTimeDlyHMSM(0, 0, 1, 500);
    }
}
//==============================================================================
// DESCRIPTION : GPIO_IRQHandler() Interrupt function Check if Coder rotated
//																 Coder used to selecte the input value
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
void GPIO_IRQHandler(void)////Check if Coder rotated
{ 
	if(GPIO_GetIntStatus(BRD_CODER_VAL_A_PORT, BRD_CODER_VAL_A_PIN, 1))        
	{
		if (GPIO_ReadValue(BRD_CODER_VAL_B_PORT) & (0x01 << BRD_CODER_VAL_B_PIN))
		{
			u8CoderValState = CODER_ROTATE_STATE_INCREASE;
		}
		else
		{
			u8CoderValState = CODER_ROTATE_STATE_DECREASE;   
		}					

		GPIO_ClearInt(BRD_CODER_VAL_A_PORT, 0x01 << BRD_CODER_VAL_A_PIN);
		
		OSSemPost(ProCoderValSem);
	}
}

//==============================================================================
// DESCRIPTION : uctsk_OKButtonProcess() When OK button pressed send CAN MSG
//						   	 
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void uctsk_OKButtonProcess (void)
{
	uint8_t err;
	uint16_t index;
	OSSemPend(ProOKButtonSem, 0, &err);
	for (;;)
	{
		OSSemPend(ProOKButtonSem, 0, &err);
		if(ISThereSubMenu(CurManuSelected_Struc) == 0)//No submenu response the OK button
		{
			switch(CurManuSelected_Struc.MainMenu_ID)
			{
				case MainMenu_Session:
					OSTmrStart(CANRXProcess_Timer,&err);
					SessionControlRequest(CurManuSelected_Struc.SubSecMenu_ID, CurManuSelected_Struc.SecMenu_ID);
					break;
				case MainMenu_ReadDataByID:
					if((bClusterManuModeAvailable)||(CurManuSelected_Struc.SecMenu_ID == SecReadDataByID_ReadDTCStatus))
					{
						OSTmrStart(CANRXProcess_Timer,&err);
						ReadDataByIDRequest(CurManuSelected_Struc.SecMenu_ID);
					}
					else
					{
						CommuniteStatus(SessionError);
					}
					break;
				case MainMenu_Alex:
					if(CurManuSelected_Struc.SecMenu_ID==SecAlex_a)
					{
					OSTmrStart(CANRXProcess_TimerAlex,&err);
					AlexRequest(CurManuSelected_Struc.SecMenu_ID);
					}
					else if(CurManuSelected_Struc.SecMenu_ID==SecAlex_b)
					{
						for(index=0;index<1024;index++)
						{
							EMC_NAND_EraseSingleBlock(index*64);
						}
						
					}
					
					break;
				case MainMenu_IOControl:
					if(bClusterManuModeAvailable)
					{
						OSTmrStart(CANRXProcess_Timer,&err);
						if(CurManuSelected_Struc.SecMenu_ID%2 == 0)//Only Return to EUC surported
						{
							IOControlCallback((uint8_t)(CurManuSelected_Struc.SecMenu_ID/2), IOCONTROL_OPTION_SHORTAJUST, CurManuSelected_Struc.CurMSG_TXData);
						}
						else
						{
							IOControlCallback((CurManuSelected_Struc.SecMenu_ID/2), IOCONTROL_OPTION_RETURNTOECU, NULL);
						}
					}
					else
					{
						CommuniteStatus(SessionError);
					}
				break;
				case MainMenu_Routine:
					if(bClusterManuModeAvailable)
					{
						OSTmrStart(CANRXProcess_Timer,&err);
						if(CurManuSelected_Struc.SecMenu_ID%2 == 0)//Only Require Result surported
						{
							RoutineControlStartRequest(CurManuSelected_Struc.SecMenu_ID/2,CurManuSelected_Struc.CurMSG_TXData);
						}
						else
						{				
							RoutineControlResultRequest(CurManuSelected_Struc.SecMenu_ID/2);
						}
					}
					else
					{
						CommuniteStatus(SessionError);
					}
					break;
			}
		}
	}
}
//==============================================================================
// DESCRIPTION : utsk_CoderRotatedProcess() 
//						   Input Value Display
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void utsk_CoderRotatedProcess (void)
{
	uint8_t err;
	uint8_t u8CodeIndex_Temp, PageNumber;
	OSSemPend(ProCoderValSem, 0, &err);
	
	for (;;)
	{
		OSSemPend(ProCoderValSem, 0, &err);
		GUI_SetColor(PRO_SELECT_COLOR);
		if(CurManuSelected_Struc.CurMenuID == SubSecMenu)
		{
			
			u8CodeIndex_Temp = FindCoderRotatedIndex(CurManuSelected_Struc);
			if(u8CodeIndex_Temp == 0xff)
			{
			}
			else
			{
				CoderRotatedProcessCallbacks[u8CodeIndex_Temp](u8CoderValState,CurManuSelected_Struc.SubSecMenu_ID,CurManuSelected_Struc.CurMSG_TXData);
				if(CurManuSelected_Struc.SubSecMenu_ID > PerPageMaxItem)
				{
					PageNumber = SecendPage;
				}
				else
				{
					PageNumber = FirstPage;
				}
				SubMenu_PerMenuDisp(CurManuSelected_Struc.SubSecMenu_ID,PageNumber);
			}
		}	
	}		
}

//==============================================================================
// DESCRIPTION : utsk_UpDownButtonProcess() 
//						   Highlight Item Display
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void utsk_UpDownButtonProcess (void)
{
	uint8_t err;
	uint8_t u8CurDispMenuID = 0;
	OSSemPend(ProUpDownButtonSem, 0, &err);
	
	for (;;)
	{
			OSSemPend(ProUpDownButtonSem, 0, &err);
			
			if(u8UpDownValState == UPDOWN_BOTTON_STATE_UPPRESSED)//Up pressed
			{
				switch(CurManuSelected_Struc.CurMenuID)
				{
					case MainMenu:
						if(CurManuSelected_Struc.MainMenu_ID <= 0)
						{
							CurManuSelected_Struc.MainMenu_ID = CurManuSelected_Struc.MaxCurDispMenu_Val-1;
						}
						else
						{
							CurManuSelected_Struc.MainMenu_ID --;
						}
						break;
					case SecMenu:
						if(CurManuSelected_Struc.SecMenu_ID <= 0)
						{
							CurManuSelected_Struc.SecMenu_ID = CurManuSelected_Struc.MaxCurDispMenu_Val-1;
						}
						else
						{
							CurManuSelected_Struc.SecMenu_ID --;
						}
						u8CurDispMenuID = CurManuSelected_Struc.SecMenu_ID;
						break;
					case SubSecMenu:
						if(CurManuSelected_Struc.SubSecMenu_ID <= 0)
						{
							CurManuSelected_Struc.SubSecMenu_ID = CurManuSelected_Struc.MaxCurDispMenu_Val-1;
						}
						else
						{
							CurManuSelected_Struc.SubSecMenu_ID --;
						}
						u8CurDispMenuID = CurManuSelected_Struc.SubSecMenu_ID;
						break;
					default:
						break;
				}
				if(CurManuSelected_Struc.MaxCurDispMenu_Val > PerPageMaxItem)
				{
					if((u8CurDispMenuID+1) < PerPageMaxItem)
					{
						CurMenuUpdate(CurManuSelected_Struc, FirstPage);
					}
					else if((u8CurDispMenuID+1) == PerPageMaxItem)
					{
						CurMenuInit(CurManuSelected_Struc, FirstPage);
						CurManuSelected_Struc.LastHighlightMenuID = u8CurDispMenuID;
					}
					else if((u8CurDispMenuID+1) < CurManuSelected_Struc.MaxCurDispMenu_Val)
					{
						CurMenuUpdate(CurManuSelected_Struc, SecendPage);
					}
					else
					{
						CurMenuInit(CurManuSelected_Struc, SecendPage);
						CurManuSelected_Struc.LastHighlightMenuID = u8CurDispMenuID;
					}
				}
				else
				{
					CurMenuUpdate(CurManuSelected_Struc, FirstPage);
				}
			}
			else if(u8UpDownValState == UPDOWN_BOTTON_STATE_DOWNPRESSED)//Down Pressed
			{
				switch(CurManuSelected_Struc.CurMenuID)
				{
					case MainMenu:
						if((CurManuSelected_Struc.MainMenu_ID+1) >= CurManuSelected_Struc.MaxCurDispMenu_Val)
						{
							CurManuSelected_Struc.MainMenu_ID = 0;
						}
						else
						{
							CurManuSelected_Struc.MainMenu_ID ++;
						}
						break;
					case SecMenu:
						if((CurManuSelected_Struc.SecMenu_ID+1) >= CurManuSelected_Struc.MaxCurDispMenu_Val)
						{
							CurManuSelected_Struc.SecMenu_ID = 0;
						}
						else
						{
							CurManuSelected_Struc.SecMenu_ID ++;
						}
						u8CurDispMenuID = CurManuSelected_Struc.SecMenu_ID;
						break;
					case SubSecMenu:
						if((CurManuSelected_Struc.SubSecMenu_ID+1) >= CurManuSelected_Struc.MaxCurDispMenu_Val)
						{
							CurManuSelected_Struc.SubSecMenu_ID = 0;
						}
						else
						{
							CurManuSelected_Struc.SubSecMenu_ID ++;
						}
						u8CurDispMenuID = CurManuSelected_Struc.SubSecMenu_ID;
						break;
					default:
						break;
				}
				if(CurManuSelected_Struc.MaxCurDispMenu_Val > PerPageMaxItem)
				{
					if(u8CurDispMenuID == 0)
					{
						CurMenuInit(CurManuSelected_Struc, FirstPage);
						CurManuSelected_Struc.LastHighlightMenuID = u8CurDispMenuID;
					}
					else if(u8CurDispMenuID < PerPageMaxItem)
					{
						CurMenuUpdate(CurManuSelected_Struc, FirstPage);
					}
					else if(u8CurDispMenuID == PerPageMaxItem)
					{
						CurMenuInit(CurManuSelected_Struc, SecendPage);
						CurManuSelected_Struc.LastHighlightMenuID = u8CurDispMenuID;
					}
					else
					{
						CurMenuUpdate(CurManuSelected_Struc, SecendPage);
					}
				}
				else
				{
					CurMenuUpdate(CurManuSelected_Struc, FirstPage);
				}
			}
			else
			{
			}
	}
}
//==============================================================================
// DESCRIPTION : utsk_LeftRightButtonProcess() 
//						   Menu Change Display
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================	
static void utsk_LeftRightButtonProcess (void)
{
	uint8_t err;
	uint8_t PageNumber = FirstPage;
	OSSemPend(ProLeftRightButtonSem, 0, &err);
	
	for (;;)
	{
			OSSemPend(ProLeftRightButtonSem, 0, &err);
		  if(u8LeftRightValState == LEFTRIGHT_BOTTON_STATE_RIGHTPRESSED)//Right
			{
				switch(CurManuSelected_Struc.CurMenuID)
				{
					case MainMenu:
						CurManuSelected_Struc.CurMenuID = SecMenu;
						CurManuSelected_Struc.SecMenu_ID = 0;
						CurManuSelected_Struc.LastHighlightMenuID = 0;
						memset(CurManuSelected_Struc.CurMSG_TXData,0,3);
						CurManuSelected_Struc.MaxCurDispMenu_Val = u8MaxDispMenu_Val[FindStructrueIndex(CurManuSelected_Struc)];
						CurMenuInit(CurManuSelected_Struc, FirstPage);
						break;
					case SecMenu:
						if(ISThereSubMenu(CurManuSelected_Struc))
						{
							CurManuSelected_Struc.CurMenuID = SubSecMenu;
							CurManuSelected_Struc.SubSecMenu_ID = 0;
							CurManuSelected_Struc.LastHighlightMenuID = 0;
							memset(CurManuSelected_Struc.CurMSG_TXData,0,3);
							CurManuSelected_Struc.MaxCurDispMenu_Val = u8MaxDispMenu_Val[FindStructrueIndex(CurManuSelected_Struc)];
							CurMenuInit(CurManuSelected_Struc, FirstPage);
						}
						break;
					default://SubSecMenu: No sub
						break;
				}
			}
			else if(u8LeftRightValState == LEFTRIGHT_BOTTON_STATE_LEFTPRESSED)//Left
			{
				switch(CurManuSelected_Struc.CurMenuID)
				{
					case SecMenu:
						CurManuSelected_Struc.CurMenuID = MainMenu;
					  CurManuSelected_Struc.SecMenu_ID = 0;
						CurManuSelected_Struc.SubSecMenu_ID = 0;
						CurManuSelected_Struc.LastHighlightMenuID = CurManuSelected_Struc.MainMenu_ID;
						memset(CurManuSelected_Struc.CurMSG_TXData,0,3);
						CurManuSelected_Struc.MaxCurDispMenu_Val = u8MaxDispMenu_Val[FindStructrueIndex(CurManuSelected_Struc)];
						CurMenuInit(CurManuSelected_Struc, FirstPage);
						break;
					case SubSecMenu:
						CurManuSelected_Struc.CurMenuID = SecMenu;
					  CurManuSelected_Struc.SubSecMenu_ID = 0;
						CurManuSelected_Struc.LastHighlightMenuID = CurManuSelected_Struc.SecMenu_ID;
						memset(CurManuSelected_Struc.CurMSG_TXData,0,3);
						CurManuSelected_Struc.MaxCurDispMenu_Val = u8MaxDispMenu_Val[FindStructrueIndex(CurManuSelected_Struc)];
						
						if(CurManuSelected_Struc.SecMenu_ID > PerPageMaxItem)
						{
							PageNumber = SecendPage;
						}
						else
						{
							PageNumber = FirstPage;
						}
						CurMenuInit(CurManuSelected_Struc, PageNumber);
						break;
					default://MainMenu: No sub
						break;
				}
			}
			else
			{
			}
	}
}
//==============================================================================
// DESCRIPTION : CurMenuInit() 
//						   Menu Display
// PARAMETERS  : sManuStruc_Type CurManuStruc uint8_t PageNum
//
// RETURN VALUE : none
//==============================================================================	
void CurMenuInit(sManuStruc_Type CurManuStruc, uint8_t PageNum)
{
	uint8_t tempCount = 0, CurDispLen = 0;
	
  GUI_SetBkColor(PRO_BACK_COLOR);	
	
	GUI_ClearRect(MENU_AREA_ULX, MENU_AREA_ULY,MENU_AREA_LRX,MENU_AREA_LRY); 
  GUI_SetFont(&GUI_FontComic18B_ASCII);
 
	if(PageNum == FirstPage)
	{
		if(CurManuSelected_Struc.MaxCurDispMenu_Val > PerPageMaxItem)
		{
			CurDispLen = PerPageMaxItem;
		}
		else
		{
			CurDispLen = CurManuSelected_Struc.MaxCurDispMenu_Val;
		}
	}
	else
	{
		CurDispLen = CurManuSelected_Struc.MaxCurDispMenu_Val - PerPageMaxItem;
	}
	for(tempCount = 0; tempCount < CurDispLen; tempCount++)
	{
		if(ReturnHighLightID(CurManuSelected_Struc) == (tempCount+PageNum))
		{
			GUI_SetColor(PRO_SELECT_COLOR);
		}
		else
		{
			GUI_SetColor(PRO_FONT_COLOR);
		}
		GUI_GotoXY(MENU_AREA_ULX,MENU_AREA_ULY+PRO_FONT_SIZE*(tempCount));
		GUI_DispString((MenuDispContext[FindStructrueIndex(CurManuSelected_Struc)]+((tempCount+PageNum)*ReturnStringSize(CurManuSelected_Struc))));
		if(CurManuSelected_Struc.CurMenuID == SubSecMenu)
		{
			SubMenu_PerMenuDisp(tempCount, PageNum);
		}
	}
}
//==============================================================================
// DESCRIPTION : CurMenuUpdate() 
//						   Menu Iterm Highlight Display
// PARAMETERS  : sManuStruc_Type CurManuStruc
//
// RETURN VALUE : none
//==============================================================================	
void CurMenuUpdate(sManuStruc_Type CurManuStruc, uint8_t PageNum)
{
	uint8_t u8StringSize = ReturnStringSize(CurManuSelected_Struc);
	uint8_t HighlightID = ReturnHighLightID(CurManuSelected_Struc);
	
	if(CurManuSelected_Struc.LastHighlightMenuID == HighlightID)
	{
	}
	else
	{
		GUI_SetFont(&GUI_FontComic18B_ASCII);
		GUI_SetBkColor(PRO_BACK_COLOR);
		GUI_SetColor(PRO_FONT_COLOR);
		GUI_GotoXY(MENU_AREA_ULX,MENU_AREA_ULY+PRO_FONT_SIZE*(CurManuSelected_Struc.LastHighlightMenuID-PageNum));
		GUI_DispString((MenuDispContext[FindStructrueIndex(CurManuSelected_Struc)]+(CurManuSelected_Struc.LastHighlightMenuID*u8StringSize)));
		if(CurManuSelected_Struc.CurMenuID == SubSecMenu)
		{
			SubMenu_PerMenuDisp(CurManuSelected_Struc.LastHighlightMenuID, PageNum);
		}
		
		GUI_SetColor(PRO_SELECT_COLOR);
		GUI_GotoXY(MENU_AREA_ULX,MENU_AREA_ULY+PRO_FONT_SIZE*(HighlightID-PageNum));
		GUI_DispString((MenuDispContext[FindStructrueIndex(CurManuSelected_Struc)]+(HighlightID*u8StringSize)));
		if(CurManuSelected_Struc.CurMenuID == SubSecMenu)
		{
			SubMenu_PerMenuDisp(CurManuSelected_Struc.SubSecMenu_ID, PageNum);
		}
	}
	CurManuSelected_Struc.LastHighlightMenuID = HighlightID;
}


void DispAlex(uint32_t i)
{
//	uint8_t Count_Temp;
//	GUI_RECT Rect = {BLOCK_INFOR_ULX+2, BLOCK_INFOR_ULY+2, BLOCK_INFOR_LRX-2, BLOCK_INFOR_LRY-2};
//	GUI_SetBkColor(GUI_BLACK);  
//	GUI_ClearRect(BLOCK_INFOR_ULX, BLOCK_INFOR_ULY,BLOCK_INFOR_LRX,BLOCK_INFOR_LRY); 
//	GUI_SetColor(PRO_BACK_COLOR);
//	GUI_FillRectEx(&Rect);
//	GUI_SetBkColor(PRO_BACK_COLOR);
//	GUI_SetFont(&GUI_Font16B_ASCII);//GUI_FontComic18B_ASCII
//	GUI_SetColor(PRO_FONT_COLOR);
	GUI_GotoXY(270, BLOCK_INFOR_Y);
	GUI_DispHex(i, 8);
//	for(Count_Temp = 0; Count_Temp < 5; Count_Temp++)
//	{
//		GUI_DispString("Version: ");
//		GUI_DispString("0x");
		
		//GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y + Font16B_SIZE* (Count_Temp+1));
//	}
}	
	
//==============================================================================
// DESCRIPTION : DispBlockContext() 
//						   Block Display
// PARAMETERS  : sManuStruc_Type CurManuStruc, uint8_t *InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void DispBlockContext(sManuStruc_Type CurManuStruc, uint8_t *InputPoint)
{
	GUI_RECT Rect = {BLOCK_INFOR_ULX+2, BLOCK_INFOR_ULY+2, BLOCK_INFOR_LRX-2, BLOCK_INFOR_LRY-2};
	GUI_SetBkColor(GUI_BLACK);  
	GUI_ClearRect(BLOCK_INFOR_ULX, BLOCK_INFOR_ULY,BLOCK_INFOR_LRX,BLOCK_INFOR_LRY); 
	GUI_SetColor(PRO_BACK_COLOR);
	GUI_FillRectEx(&Rect);
	GUI_SetBkColor(PRO_BACK_COLOR);
	GUI_SetFont(&GUI_Font16B_ASCII);//GUI_FontComic18B_ASCII
	GUI_SetColor(PRO_FONT_COLOR);
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y);
	if(CurManuStruc.MainMenu_ID == MainMenu_ReadDataByID)
	{
		BlockDispProcessCallbacks[CurManuStruc.SecMenu_ID](InputPoint);
	}
	else
	{
		RoutineControlBlockDsipCallback(CurManuStruc.SecMenu_ID/2, InputPoint);
	}
}
//==============================================================================
// DESCRIPTION : SubMenu_PerMenuDisp(uint8_t SubSecMenuItem_ID) 
//						   Dsip the changed value of Sub menu 
// PARAMETERS  : SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void SubMenu_PerMenuDisp(uint8_t SubSecMenuItem_ID, uint8_t PageNum)
{
	uint8_t u8CoderRotatedIndex;
	
	GUI_SetBkColor(PRO_BACK_COLOR);	
	GUI_ClearRect(SUBVAL_OFFSET_ULX, SUBVAL_OFFSET_ULY+(SubSecMenuItem_ID-PageNum)*PRO_FONT_SIZE,
								SUBVAL_OFFSET_LRX, SUBVAL_OFFSET_LRY+(SubSecMenuItem_ID-PageNum)*PRO_FONT_SIZE); 
	GUI_SetFont(&GUI_FontComic18B_ASCII);
	GUI_GotoXY(SUBVAL_OFFSET_ULX,SUBVAL_OFFSET_ULY+(SubSecMenuItem_ID-PageNum)*PRO_FONT_SIZE);
	
	u8CoderRotatedIndex = FindCoderRotatedIndex(CurManuSelected_Struc);	
	if(u8CoderRotatedIndex < 0xff)
	{
		SubMenuDispProcessCallbacks[u8CoderRotatedIndex](SubSecMenuItem_ID, CurManuSelected_Struc.CurMSG_TXData);
	}
}

//==============================================================================
// DESCRIPTION : uint8_t FindStructrueIndex(sManuStruc_Type CurManuStruc) 
//						   Find the max value or display string index
// PARAMETERS  : sManuStruc_Type CurManuStruc
//
// RETURN VALUE : none
//==============================================================================	
uint8_t FindStructrueIndex(sManuStruc_Type CurManuStruc)
{
	uint8_t u8ReturnIndex = 0;
	
	switch(CurManuStruc.CurMenuID)
	{
		case MainMenu:
			u8ReturnIndex = 0;
			break;
		case SecMenu:
			u8ReturnIndex = CurManuStruc.MainMenu_ID+1;
			break;
		case SubSecMenu:
			if(CurManuStruc.MainMenu_ID == MainMenu_Session)
			{
				u8ReturnIndex = MainMenu_Count + CurManuStruc.SecMenu_ID + 1;
			}
			else if(CurManuStruc.MainMenu_ID == MainMenu_IOControl)
			{
				u8ReturnIndex = MainMenu_Count + SecSession_Count + (CurManuStruc.SecMenu_ID/2) + 1;
			}
			else
			{
				u8ReturnIndex = 18; 
			}
			break;
		default:
			break;
	}
	return u8ReturnIndex;
}

//==============================================================================
// DESCRIPTION : uint8_t ReturnStringSize(sManuStruc_Type CurManuStruc) 
//						   Return the string size see dispcontextdefine.h
// PARAMETERS  : sManuStruc_Type CurManuStruc
//
// RETURN VALUE : none
//==============================================================================	
uint8_t ReturnStringSize(sManuStruc_Type CurManuStruc)
{
	uint8_t u8ReturnSize = 0;
	
	if(CurManuStruc.CurMenuID == SubSecMenu)
	{
		u8ReturnSize = SubMenuSize;
	}
	else
	{
		u8ReturnSize = MenuSize;
	}
	return u8ReturnSize;
}
//==============================================================================
// DESCRIPTION : uint8_t ReturnHighLightID(sManuStruc_Type CurManuStruc)
//						   Return HighLight ID 
// PARAMETERS  : sManuStruc_Type CurManuStruc
//
// RETURN VALUE : none
//==============================================================================	
uint8_t ReturnHighLightID(sManuStruc_Type CurManuStruc)
{
	uint8_t u8HighlightID = 0;
	
	switch(CurManuStruc.CurMenuID)
	{
		case MainMenu:
			u8HighlightID = CurManuStruc.MainMenu_ID;
			break;
		case SecMenu:
			u8HighlightID = CurManuStruc.SecMenu_ID;
			break;
		case SubSecMenu:
			u8HighlightID = CurManuStruc.SubSecMenu_ID;
			break;
		default:
			break;
	}
	return u8HighlightID;
}
//==============================================================================
// DESCRIPTION : uint8_t ISThereSubMenu(sManuStruc_Type CurManuStruc) 
//						   Check If the curmenu has a submenu
// PARAMETERS  : sManuStruc_Type CurManuStruc
//
// RETURN VALUE : none
//==============================================================================	
uint8_t ISThereSubMenu(sManuStruc_Type CurManuStruc)
{
	uint8_t ISThereSubMenu_Flag = 0;
	
	switch(CurManuStruc.CurMenuID)
	{
		case MainMenu:
			ISThereSubMenu_Flag = 1;
			break;
		case SecMenu:
			if((CurManuStruc.MainMenu_ID == MainMenu_ReadDataByID) ||//Read data by ID
			(CurManuStruc.MainMenu_ID == MainMenu_Alex) ||//Alex
			 (((CurManuStruc.SecMenu_ID%2) == 1)&&(CurManuStruc.MainMenu_ID == MainMenu_IOControl))||//IO Control Return to ECU
			 (((CurManuStruc.SecMenu_ID%2) == 1)&&(CurManuStruc.MainMenu_ID == MainMenu_Routine))||
				((CurManuStruc.SecMenu_ID >= SecIOControl_OFFP5VControl)&&(CurManuStruc.MainMenu_ID == MainMenu_IOControl)))
			{
				ISThereSubMenu_Flag = 0;
			}
			else
			{
				ISThereSubMenu_Flag = 1;
			}
			break;
		default://SubSecMenu:
			ISThereSubMenu_Flag = 0;
			break;
	}
	return ISThereSubMenu_Flag;
}
//==============================================================================
// DESCRIPTION : uint8_t FindCoderRotatedIndex(sManuStruc_Type CurManuStruc) 
//						   Find the Index of subsecmenu
// PARAMETERS  : sManuStruc_Type CurManuStruc
//
// RETURN VALUE : none
//==============================================================================	
uint8_t FindCoderRotatedIndex(sManuStruc_Type CurManuStruc)
{
	uint8_t u8CoderRotatedIndex = 0xff;
	switch(CurManuStruc.MainMenu_ID)
	{
		case MainMenu_Session:
		case MainMenu_ReadDataByID:
			break;
		case MainMenu_IOControl:
			if((CurManuStruc.SecMenu_ID%2 == 1)||
				(CurManuStruc.SecMenu_ID == SecIOControl_OFFP5VControl)||
				(CurManuStruc.SecMenu_ID == SecIOControl_ONFuelSensorControl))
			{
			}
			else
			{
				u8CoderRotatedIndex = CurManuStruc.SecMenu_ID/2;
			}
			break;
		case MainMenu_Routine:
			if(CurManuStruc.SecMenu_ID%2 == 1)
			{
			}
			else
			{
				u8CoderRotatedIndex = (CurManuStruc.SecMenu_ID/2)+(SecIOControl_Count/2) - 2;
			}
			break;
	}
	return u8CoderRotatedIndex;
}
//==============================================================================
// DESCRIPTION : CommuniteStatus() 
//						   Dsip CAN communite error infor
// PARAMETERS  : uint8_t ErrorType
//
// RETURN VALUE : none
//==============================================================================	
void CommuniteStatus(uint8_t ErrorType)
{
	GUI_SetBkColor(PRO_BACK_COLOR); 
	GUI_SetFont(&GUI_Font16B_ASCII);//GUI_FontComic18B_ASCII
	GUI_ClearRect(RESPONSE_AREA_ULX, RESPONSE_AREA_ULY, RESPONSE_AREA_LRX, RESPONSE_AREA_LRY); 
	GUI_GotoXY(RESPONSE_AREA_ULX,RESPONSE_AREA_ULY);
	GUI_SetColor(PRO_SELECT_COLOR);
	switch(ErrorType)
	{
		case PositiveResponse:
			GUI_SetColor(GUI_LIGHTGREEN);
			GUI_DispString("Positive response received!");
			break;
		case SessionError:
			GUI_DispString("Enter Manu Session First!!!");
			break;
		case TimeOutError:
			GUI_DispString("CAN Communition Timeout!!!");
			break;
		case ServiceNotSupported:
		case SubFunctionNotSupported:
		case SubFunctionNotSupportedInSession:
		case ServiceNotSupportedInSession:
			GUI_DispString("Sevice Not Supported!!!");
			break;
		case InCorrectMessageLength:
			GUI_DispString("InCorrect MessageLength!!!");
			break;
		case BusyRepeatRequest:
			GUI_DispString("Busy Repeat Request!!!");
			break;
		case ConditionsNotCorrect:
			GUI_DispString("Conditions Not Correct!!!");
			break;
		case RequestSequenceError:
			GUI_DispString("Request Sequence Error!!!");
			break;
		case RequestOutOfRange:
			GUI_DispString("Request OutOf Range!!!");
			break;
		case SecurityAccessDenied:
			GUI_DispString("Security Access Denied!!!");
			break;
		case InvalidKey:
			GUI_DispString("Invalid Key!!!");
			break;
		case UploadDownloadNotAccepted:
			GUI_DispString("Download Not Accepted!!!");
			break;
		case TransferDataSuspended:
			GUI_DispString("Transfer Data Suspended!!!");
			break;
		case GeneralProgrammingFailure:
			GUI_DispString("General Programe Failure!!!");
			break;
		case WrongBlockSequenceCounter:
			GUI_DispString("Wrong Block Counter!!!");
			break;
		case RequestCorrectly:
			GUI_DispString("Request Correctly!!!");
			break;
		case VehicleSpeedTooHigh:
			GUI_DispString("Vehicle Speed TooHigh!!!");
			break;
		case VoltageTooHigh:
			GUI_DispString("Voltage Too High!!!");
			break;
		case VoltageTooLow:
			GUI_DispString("Voltage Too Low!!!");
			break;
		default:
			GUI_DispString("Nagative Response!!!");
			break;
	}
}
//==============================================================================
// DESCRIPTION : ClusterStatus() 
//						   Dsip Cluster Status infor
// PARAMETERS  : uint8_t ClusterType
//
// RETURN VALUE : none
//==============================================================================	
void ClusterStatus(uint8_t ClusterType)
{
	switch(ClusterType)
	{
		case NoCluster:
		case ClusterAvailable:
			GUI_SetBkColor(PRO_BACK_COLOR); 
			GUI_SetFont(&GUI_Font16B_ASCII); 
			GUI_ClearRect(CLUSTER_INFOR_ULX, CLUSTER_INFOR_ULY, CLUSTER_INFOR_LRX, CLUSTER_INFOR_LRY); 
			GUI_GotoXY(CLUSTER_INFOR_ULX,CLUSTER_INFOR_ULY);
			if(ClusterType == NoCluster)
			{
				GUI_SetColor(PRO_SELECT_COLOR);
				GUI_DispString("No Cluster!!!");
			}
			else
			{
				GUI_SetColor(GUI_LIGHTGREEN);
				GUI_DispString("Cluster Available!");
			}
			break;
		case ClusterInManuSession:
		case ClusterOutManuSession:	
			GUI_SetBkColor(PRO_BACK_COLOR); 
			GUI_SetFont(&GUI_Font16B_ASCII);
			GUI_ClearRect(CLUSTER_SESSION_INFOR_ULX, CLUSTER_SESSION_INFOR_ULY, CLUSTER_SESSION_INFOR_LRX, CLUSTER_SESSION_INFOR_LRY); 
			GUI_GotoXY(CLUSTER_SESSION_INFOR_ULX,CLUSTER_SESSION_INFOR_ULY);
			if(ClusterType == ClusterInManuSession)
			{
				GUI_SetColor(GUI_LIGHTGREEN);
				GUI_DispString("Already In Manu Session!");
			}
			else
			{
				GUI_SetColor(PRO_SELECT_COLOR);
				GUI_DispString("But Not in Manu Session!");
			}
			break;
		default:
			break;
	}
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
