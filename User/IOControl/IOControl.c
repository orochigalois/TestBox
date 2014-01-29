/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               IOControl.c
** Descriptions:            The IOControl application function
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

#include "IOControl.h"

uint8_t TXInputOutputControl[8] = {0x00};

uint8_t LECControlTXMSGLastBye[5][2] = {{0x01,0x2e},
																				{0x00,0x00},
																				{0x00,0x01},
																				{0x00,0xd0},
																				{0x01,0xff}};
uint8_t SoundType[17] = {0x01,0x02,0x03,0x50,0x51,
												 0x52,0x53,0x54,0x55,0x56,
												 0x57,0x58,0x59,0x5A,0x5B,
												 0x5C,0x5D};
uint8_t MotorType[10] = {0x80,0x81,0x82,0x83,0x8F,
												 0xB0,0xB1,0xB2,0xB3,0xBF};


extern uint8_t CAN_MSGRXControlType;
extern uint16_t CAN_MSGRXControlID;

uint8_t u8LEDControl_Data = 0;

uint16_t IOControl_ID[11] =   
{                                                                             
	LEDCHONTROL_ID,
	LCDCHONTROL_ID,
	DIMMINGCONTROL_ID,
	SOUNDCONTROL_ID,
	MOTORMICROORDEGREECONTROL_ID,
	MOTORVEHICLECONTROL_ID,
	MOTORJUMPUSTEP_ID,
	TFTPATTERNCONTROL_ID,
	SOUNDVOLUME_ID,
	OFFP5V_ID,
	ONFUELSENSOR_ID,
};
//==============================================================================
// DESCRIPTION : IOControlCallback() IO Control call back
//
// PARAMETERS  : uint8_t Control_ID, uint8_t Control_Option_Type, uint8_t *Parameter
//
// RETURN VALUE : uint8_t
//==============================================================================
uint8_t IOControlCallback(uint8_t Control_ID, uint8_t Control_Option_Type, uint8_t *Parameter)
{
	TXInputOutputControl[1] = 0x2f;
	TXInputOutputControl[2] = (uint8_t)(IOControl_ID[Control_ID] >> 8);
	TXInputOutputControl[3] = (uint8_t)(IOControl_ID[Control_ID]);
	TXInputOutputControl[4] = Control_Option_Type;
	if(Control_Option_Type == IOCONTROL_OPTION_SHORTAJUST)
	{
		switch(Control_ID)
		{
			case IOControl_ID_LEDControl:
				TXInputOutputControl[0] = 0x10;
				TXInputOutputControl[1] = 0x0a;
				TXInputOutputControl[2] = 0x2f;
				TXInputOutputControl[3] = 0xfd;
				TXInputOutputControl[4] = 0x00;
				TXInputOutputControl[5] = IOCONTROL_OPTION_SHORTAJUST;
				if(Parameter[1] == 0x00)//OFF
				{
					TXInputOutputControl[6] = 0x00;
					TXInputOutputControl[7] = 0x00;
					u8LEDControl_Data = 5;
				}
				else
				{
					memcpy(TXInputOutputControl+6,LECControlTXMSGLastBye[Parameter[2]],2);
					u8LEDControl_Data = Parameter[2];
				}
				break;
			case IOControl_ID_LCDControl:
			case IOControl_ID_TFTPatternControl:
			case IOControl_ID_SoundVolumeControl:
				TXInputOutputControl[0] = 0x05;
				TXInputOutputControl[5] = Parameter[2];
				memset(TXInputOutputControl+6,0,2);
				break;
			case IOControl_ID_DimmingControl:
				TXInputOutputControl[0] = 0x07;
				TXInputOutputControl[5] = Parameter[2];
				if(Parameter[1] < 3)
				{
					TXInputOutputControl[6] = (uint8_t)(Parameter[1])+1;
				}
				else
				{
					TXInputOutputControl[6] = 0xff;
				}
				TXInputOutputControl[7] = Parameter[0];
				break;
			case IOControl_ID_SoundControl:
				TXInputOutputControl[0] = 0x05;
				TXInputOutputControl[5] = SoundType[Parameter[2]];
				memset(TXInputOutputControl+6,0,2);
				break;
			case IOControl_ID_MotorMicOrDegreeControl:
			case IOControl_ID_MotorVehicleControl:
				TXInputOutputControl[0] = 0x07;
				TXInputOutputControl[5] = MotorType[Parameter[2]];
				TXInputOutputControl[6] = (uint8_t)(Parameter[1]);
				TXInputOutputControl[7] = (uint8_t)(Parameter[0]);
				break;
			case IOControl_ID_MotorJumpinuStepControl:
				TXInputOutputControl[0] = 0x06;
				TXInputOutputControl[5] = MotorType[Parameter[2]];
				TXInputOutputControl[6] = (uint8_t)(Parameter[1]);
				TXInputOutputControl[7] = 0x00;
				break;
			case IOControl_ID_OFFP5VControl:
			case IOControl_ID_ONFuelSensorControl:
				memset(TXInputOutputControl+5,0,3);
				break;
			default:
				break;
		}
	}
	else
	{
		TXInputOutputControl[0] = 0x04;
		memset(TXInputOutputControl+5,0,3);
	}
	CAN_MSGRXControlType = 0x6f;
	CAN_MSGRXControlID = IOControl_ID[Control_ID];
	SendService_CAN(TXInputOutputControl);
	return 0;
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
