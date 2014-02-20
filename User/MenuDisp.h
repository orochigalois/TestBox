#ifndef _MENUDISP_H_
#define _MENUDISP_H_

#include "includes.h"
#include "GLCD.h"
#include "bsp.h"
#include "can_handling.h"


#define PositiveResponse									0x01
#define SessionError 											0x02
#define TimeOutError 											0x03
#define ServiceNotSupported 							0x11
#define SubFunctionNotSupported 					0x12
#define InCorrectMessageLength 						0x13
#define BusyRepeatRequest 								0x21
#define ConditionsNotCorrect 							0x22
#define RequestSequenceError 							0x24
#define RequestOutOfRange 								0x31
#define SecurityAccessDenied 							0x33
#define InvalidKey 												0x35
#define UploadDownloadNotAccepted 				0x70
#define TransferDataSuspended 						0x71
#define GeneralProgrammingFailure 				0x72
#define WrongBlockSequenceCounter 				0x73
#define RequestCorrectly 									0x78
#define SubFunctionNotSupportedInSession 	0x7E
#define ServiceNotSupportedInSession 			0x7F
#define VehicleSpeedTooHigh 							0x88
#define VoltageTooHigh 										0x92
#define VoltageTooLow 										0x93

#define NoCluster													0x01
#define ClusterAvailable									0x02
#define ClusterInManuSession							0x03
#define ClusterOutManuSession							0x04

#define PerPageMaxItem 		11
#define FirstPage 				0
#define SecendPage 				PerPageMaxItem

typedef struct
{
	uint8_t MainMenu_ID;
	uint8_t SecMenu_ID;
	uint8_t SubSecMenu_ID;
	
	uint8_t CurMenuID;
	
	uint8_t LastHighlightMenuID;
	
	uint8_t CurMSG_TXData[3];
	
	uint8_t MaxCurDispMenu_Val;
	
}sManuStruc_Type;		

void App_UCGUI_TaskCreate (void);//Create the task used in UCGUI mode 
void APP_UCGUI_Init (void);

static void uctsk_uart (void);
static void uctsk_Blink (void);//Blinking when sending or receiving CAN Message
static void uctsk_CheckButtonPressed(void);//Check if ok button Up down right and left button pressed
void GPIO_IRQHandler(void); //Check if Coder rotated

static void uctsk_OKButtonProcess (void);   
static void utsk_CoderRotatedProcess (void);                                  
static void utsk_UpDownButtonProcess (void);
static void utsk_LeftRightButtonProcess (void);
static void utsk_ManuSelfTest (void);				

void ClusterInforInit(void);
void CurMenuInit(sManuStruc_Type CurManuStruc, uint8_t PageNum);
void CurMenuUpdate(sManuStruc_Type CurManuStruc, uint8_t PageNum);

void SubMenu_PerMenuDisp(uint8_t SubSecMenuItem_ID, uint8_t PageNum);
void DispBlockContext(sManuStruc_Type CurManuStruc, uint8_t *InputPoint);
void DispAlex(uint32_t);

uint8_t FindCoderRotatedIndex(sManuStruc_Type CurManuStruc);
uint8_t FindStructrueIndex(sManuStruc_Type CurManuStruc);
uint8_t ReturnStringSize(sManuStruc_Type CurManuStruc);
uint8_t ISThereSubMenu(sManuStruc_Type CurManuStruc);
uint8_t ReturnHighLightID(sManuStruc_Type CurManuStruc);

void CANRXProcesstask(void *ptmr, void *parg);
void CANRXProcesstaskAlex(void *ptmr, void *parg);
void CommuniteStatus(uint8_t ErrorType);
void ClusterStatus(uint8_t ClusterType);

#endif
