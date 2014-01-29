/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               RoutineControl.c
** Descriptions:            The RoutineControl application function
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
#include "RoutineControl.h"

uint8_t TXRoutineControl[8] = {0x00,0x31};

extern uint8_t CAN_MSGRXControlType;
extern uint16_t CAN_MSGRXControlID;

uint16_t RoutineControl_ID[5] =   
{                                                                             
	ADCINPUTROUTINECONTROL_ID,
	CALIINPUTROUTINECONTROL_ID_ID,
	INPUTBYOHMROUTINECONTROL_ID,
	AUDIOVOLUMEROUTINECONTROL_ID,
	SIWALAINPUTROUTINECONTROL_ID
};
//==============================================================================
// DESCRIPTION : RoutineControlStartRequest() Routine Control Start
//
// PARAMETERS  : uint8_t Control_ID, uint8_t *RoutineParameter
//
// RETURN VALUE : uint8_t
//==============================================================================
uint8_t RoutineControlStartRequest(uint8_t Control_ID, uint8_t *RoutineParameter)
{
	TXRoutineControl[0] = 0x06;
	TXRoutineControl[2] = 0x01;
	TXRoutineControl[3] = (uint8_t)(RoutineControl_ID[Control_ID] >> 8);
	TXRoutineControl[4] = (uint8_t)(RoutineControl_ID[Control_ID]);
	
	TXRoutineControl[5] = RoutineParameter[2]+1;
	TXRoutineControl[6] = RoutineParameter[1];

	TXRoutineControl[7] = 0;
	
	CAN_MSGRXControlType = TXRoutineControl[1]+0x40;
	CAN_MSGRXControlID = RoutineControl_ID[Control_ID];
	SendService_CAN(TXRoutineControl);
	return 0;
}
//==============================================================================
// DESCRIPTION : RoutineControlResultRequest() Routine Control Result
//
// PARAMETERS  : uint8_t Control_ID
//
// RETURN VALUE : uint8_t
//==============================================================================
uint8_t RoutineControlResultRequest(uint8_t Control_ID)
{

	TXRoutineControl[0] = 0x04;
	TXRoutineControl[2] = 0x03;
	TXRoutineControl[3] = (uint8_t)(RoutineControl_ID[Control_ID] >> 8);
	TXRoutineControl[4] = (uint8_t)(RoutineControl_ID[Control_ID]);
	memset(TXRoutineControl+5,0,3);
	CAN_MSGRXControlType = TXRoutineControl[1]+0x40;
	CAN_MSGRXControlID = RoutineControl_ID[Control_ID];
	SendService_CAN(TXRoutineControl);
	return 0;
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
