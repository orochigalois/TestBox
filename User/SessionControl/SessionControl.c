/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               SessionControl.c
** Descriptions:            The SessionControl application function
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
#include "SessionControl.h"

uint8_t TXSessionBuffer[8] = {0};

extern uint8_t CAN_MSGRXControlType;
extern uint16_t CAN_MSGRXControlID;
//==============================================================================
// DESCRIPTION : SessionControlRequest() 
//							 Session Control
// PARAMETERS  : uint8_t	Session_StepNum, uint8_t	bIsEnterOrExsit
//
// RETURN VALUE : uint8_t
//==============================================================================
uint8_t SessionControlRequest(uint8_t	Session_StepNum, uint8_t	bIsEnterOrExsit)
{
	switch(Session_StepNum)
	{
		case 0://Step 1 JCI_Session
			JCISessionControl(bIsEnterOrExsit);
			break;
		case 1:
			if(bIsEnterOrExsit == 0)
			{
				TXSessionBuffer[0] = 0x02;
				TXSessionBuffer[1] = 0x27;
				TXSessionBuffer[2] = 0x61;//Login Request
				memset(TXSessionBuffer+3,0,5);
				CAN_MSGRXControlType = TXSessionBuffer[1]+0x40;
				CAN_MSGRXControlID = TXSessionBuffer[2];
			}
			else
			{
				JCIManuONOFFControl(bIsEnterOrExsit);
			}
			break;
		case 2:
			if(bIsEnterOrExsit == 0)
			{
				JCIManuONOFFControl(bIsEnterOrExsit);
			}
			else
			{
				JCIResetControl();
			}
			break;
		case 3:
			JCIResetControl();
			break;
		case 4:
			JCISessionControl(1);
			break;
		default:
			break;
	}
	SendService_CAN(TXSessionBuffer);
	return 0;
}
//==============================================================================
// DESCRIPTION : CAN_CRC_Calculate() 
//							 Calculate the security key
// PARAMETERS  : uint8_t * RMsg
//
// RETURN VALUE : void
//==============================================================================
void CAN_CRC_Calculate(uint8_t * RMsg)
{
    uint32_t uiTempB;
		uiTempB = ((uint32_t)(RMsg[3]) << 24)+((uint32_t)(RMsg[4]) << 16)+((uint32_t)(RMsg[5]) << 8)+(uint32_t)(RMsg[6]);

    uiTempB += 50933;
    
		TXSessionBuffer[0] = 0x06;
		TXSessionBuffer[1] = 0x27;
		TXSessionBuffer[2] = 0x62;
		TXSessionBuffer[3] = (uint8_t)(uiTempB >> 24);
		TXSessionBuffer[4] = (uint8_t)((uiTempB >> 16) & 0xFF);
		TXSessionBuffer[5] = (uint8_t)((uiTempB >> 8) & 0xFF);
		TXSessionBuffer[6] = (uint8_t)(uiTempB & 0xFF);
		TXSessionBuffer[7] = 0x00;
		CAN_MSGRXControlType = TXSessionBuffer[1]+0x40;
		CAN_MSGRXControlID = TXSessionBuffer[2];
		SendService_CAN(TXSessionBuffer);
}
//==============================================================================
// DESCRIPTION : JCISessionControl() 
//							 Session Control 10 60 / 10 61
// PARAMETERS  : uint8_t * RMsg
//
// RETURN VALUE : void
//==============================================================================
void JCISessionControl(uint8_t bIsEnterOrExsit)
{
	TXSessionBuffer[0] = 0x02;
	TXSessionBuffer[1] = 0x10;
	if(bIsEnterOrExsit == 0)
	{
		TXSessionBuffer[2] = JCI_SESSION_ID;
	}
	else
	{
		TXSessionBuffer[2] = JCI_EOL_SESSION_ID;
	}
	memset(TXSessionBuffer+3,0,5);
	CAN_MSGRXControlType = TXSessionBuffer[1]+0x40;
	CAN_MSGRXControlID = TXSessionBuffer[2];
}
//==============================================================================
// DESCRIPTION : JCIManuONOFFControl() 
//							 Manufacture ON/OFF FD60
// PARAMETERS  : uint8_t * RMsg
//
// RETURN VALUE : void
//==============================================================================
void JCIManuONOFFControl(uint8_t bIsEnterOrExsit)
{
	TXSessionBuffer[0] = 0x04;
	TXSessionBuffer[1] = 0x2E;
	TXSessionBuffer[2] = 0xFD;
	TXSessionBuffer[3] = 0x60;
	TXSessionBuffer[4] = bIsEnterOrExsit;
	memset(TXSessionBuffer+5,0,3);
	CAN_MSGRXControlType = TXSessionBuffer[1]+0x40;
	CAN_MSGRXControlID = 0xFD60;
}
//==============================================================================
// DESCRIPTION : JCIResetControl() 
//							 Reset 11 02
// PARAMETERS  : uint8_t * RMsg
//
// RETURN VALUE : void
//==============================================================================
void JCIResetControl(void)
{
	TXSessionBuffer[0] = 0x02;
	TXSessionBuffer[1] = 0x11;
	TXSessionBuffer[2] = 0x02;
	memset(TXSessionBuffer+3,0,5);
	CAN_MSGRXControlType = TXSessionBuffer[1]+0x40;
	CAN_MSGRXControlID = TXSessionBuffer[2];
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
