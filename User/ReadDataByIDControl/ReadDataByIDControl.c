/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               ReadDataByIDControl.c
** Descriptions:            The ReadDataByIDControl application function
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
#include "ReadDataByIDControl.h"
#include "MenuID_define.h"
uint8_t TXReadDataByIDBuffer[8] = {0};

extern uint8_t CAN_MSGRXControlType;
extern uint16_t CAN_MSGRXControlID;

uint16_t TXReadDataByIDBufferID[22] =  {SERIALNUMBER_ID,
																				EEPANDSWVERSION_ID,
																				BACKGROUNDBUTTON_ID,
																				CURRENTBUTTON_ID,
																				CABLECONNECT_ID,
																				SPEEDINPUTPOSITION_ID,
																				TACHOINPUTPOSITION_ID,
																				FUELINPUTPOSITION_ID,
																				WATERINPUTPOSITION_ID,
																				SPEEDOUTPUTPOSITION_ID,
																				TACHOOUTPUTPOSITION_ID,
																				FUELOUTPUTPOSITION_ID,
																				WATEROUTPUTPOSITION_ID,
																				CALIANALOGINPUT_ID,
																				BRANDINFO_ID,
																				TRANSPONDERREAD_ID,
																				TRANSPONDERWRITE_ID,
																				KEYID_ID,
																				EXTERNALDIGITALINPUT_ID,
																				SELFTEST_ID,
																				DTCStatus_ID,
																				MANUFACSESSION_ID};
//==============================================================================
// DESCRIPTION : ReadDataByIDRequest() ReaddatabyID call back
//
// PARAMETERS  : uint8_t	ReadData_Identifer_ID
//
// RETURN VALUE : uint8_t
//==============================================================================
uint8_t AlexRequest(uint8_t	ReadData_Identifer_ID)
{

	TXReadDataByIDBuffer[0] = 0x02;
	TXReadDataByIDBuffer[1] = 0x10;
	TXReadDataByIDBuffer[2] = 0x02;

	SendService_CAN(TXReadDataByIDBuffer);

	
	return 0;
}


uint8_t ReadDataByIDRequest(uint8_t	ReadData_Identifer_ID)
{
	
	TXReadDataByIDBuffer[0] = 0x03;
	if(ReadData_Identifer_ID == SecReadDataByID_ReadDTCStatus)//DTC Status
	{
		TXReadDataByIDBuffer[1] = 0x19;
	}
	else
	{
		TXReadDataByIDBuffer[1] = 0x22;
	}
	TXReadDataByIDBuffer[2] = (uint8_t)(TXReadDataByIDBufferID[ReadData_Identifer_ID] >> 8);
	TXReadDataByIDBuffer[3] = (uint8_t)(TXReadDataByIDBufferID[ReadData_Identifer_ID]);
	memset(TXReadDataByIDBuffer+4,0,4);
	
	CAN_MSGRXControlType = TXReadDataByIDBuffer[1]+0x40;
	if(ReadData_Identifer_ID == SecReadDataByID_ReadDTCStatus)//DTC Status
	{
		CAN_MSGRXControlID = 0x02;
	}
	else
	{
		CAN_MSGRXControlID = TXReadDataByIDBufferID[ReadData_Identifer_ID];
	}
	SendService_CAN(TXReadDataByIDBuffer);
	return 0;
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
