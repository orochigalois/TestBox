/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               CoderProcess.c
** Descriptions:            The CoderProcess application function
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
#include "CoderProcess.h"
#include "MenuID_define.h"
//==============================================================================
// DESCRIPTION : uint8_t LEDIOControlCallback() 
//						   LED Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void LEDIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(SubSecMenuID == SubSecMenu_LED_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2]  >= 4)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 4;
			}
			else
			{
				CoderData[2]--;
			}
		}
		else
		{
		}
	}
	else if(SubSecMenuID == SubSecMenu_LED_Status)
	{
		if(CoderData[1] & 0x01)//1
		{
			CoderData[1] = 0x00; //0
		}
		else
		{
			CoderData[1] = 0x01; //1
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t LCDIOControlCallback() 
//						   LCD Segment Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void LCDIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
	{
		if(CoderData[2] >= 7)
		{
			CoderData[2] = 0;
		}
		else
		{
			CoderData[2]++;
		}
	}
	else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
	{
		if(CoderData[2] <= 0)
		{
			CoderData[2] = 7;
		}
		else
		{
			CoderData[2]--;
		}
	}
	else
	{
	}
}
//==============================================================================
// DESCRIPTION : uint8_t DimmingIOControlCallback() 
//						   Dimming Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void DimmingIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	switch(SubSecMenuID)
	{
		case SubSecMenu_Dimming_Type:
			if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
			{
				if(CoderData[2] >= 1)
				{
					CoderData[2] = 0;
				}
				else
				{
					CoderData[2]++;
				}
			}
			else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
			{
				if(CoderData[2] <= 0)
				{
					CoderData[2] = 1;
				}
				else
				{
					CoderData[2]--;
				}
			}
			break;
		case SubSecMenu_Dimming_Channel:
			if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
			{
				if(CoderData[1] >= 3)
				{
					CoderData[1] = 0;
				}
				else
				{
					CoderData[1]++;
				}
			}
			else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
			{
				if(CoderData[1] <= 0)
				{
					CoderData[1] = 3;
				}
				else
				{
					CoderData[1]--;
				}
			}
			break;
		case SubSecMenu_Dimming_Value:
			if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
			{
				if(CoderData[0] >= 100)
				{
					CoderData[0] = 0;
				}
				else
				{
					CoderData[0] = CoderData[0] + 10;
				}
			}
			else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
			{
				if(CoderData[0] < 10)
				{
					CoderData[0] = 100;
				}
				else
				{
					CoderData[0] = CoderData[0] - 10;
				}
			}
			break;
		default:
			break;
	}
}
//==============================================================================
// DESCRIPTION : uint8_t SoundIOControlCallback() 
//						   Sound Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================		
void SoundIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
	{
		if(CoderData[2] >= 16)
		{
			CoderData[2] = 0;
		}
		else
		{
			CoderData[2]++;
		}
	}
	else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
	{
		if(CoderData[2] <= 0)
		{
			CoderData[2] = 16;
		}
		else
		{
			CoderData[2]--;
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t MotorMicOrDegreeIOControlCallback() 
//						   Motor u-step or Degree control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void MotorMicOrDegreeIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	uint16_t Data_Temp;
	if(SubSecMenuID == SubSecMenu_MotorMicOrDegree_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2] >= 9)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 9;
			}
			else
			{
				CoderData[2]--;
			}
		}
	}
	else if(SubSecMenuID == SubSecMenu_MotorMicOrDegree_Value)
	{
		Data_Temp = ((uint16_t)CoderData[1] << 8) + CoderData[0];
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(Data_Temp >= 36000)
			{
				Data_Temp = 0;
			}
			else
			{
				Data_Temp = Data_Temp + 1000;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(Data_Temp < 1000)
			{
				Data_Temp = 36000;
			}
			else
			{
				Data_Temp = Data_Temp - 1000;
			}
		}
		CoderData[1] = (uint8_t)(Data_Temp >> 8);
		CoderData[0] = (uint8_t)Data_Temp;
	}
}
//==============================================================================
// DESCRIPTION : uint8_t MotorVehicleIOControlCallback() 
//						   Motor Vehicle Unit Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================		
void MotorVehicleIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	uint16_t Data_Temp;
	uint16_t MaxValue = 0;

	if(SubSecMenuID == SubSecMenu_MotorVehicle_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2] >= 3)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 3;
			}
			else
			{
				CoderData[2]--;
			}
		}
	}
	else if(SubSecMenuID == SubSecMenu_MotorVehicle_Value)
	{
		Data_Temp = ((uint32_t)CoderData[1] << 8) + CoderData[0];
		if(CoderData[2] == 0)//Speedo
		{
			MaxValue = 26000;
		}
		else if(CoderData[2] == 1)//Tacho
		{
			MaxValue = 8000;
		}
		else if(CoderData[2] == 2)//Fuel
		{
			MaxValue = 10000;
		}
		else if(CoderData[2] == 3)//Water
		{
			MaxValue = 13000;
		}
		else
		{
		}
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(Data_Temp >= MaxValue)
			{
				Data_Temp = 0;
			}
			else
			{
				Data_Temp = Data_Temp + 1000;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(Data_Temp < 1000)
			{
				Data_Temp = MaxValue;
			}
			else
			{
				Data_Temp = Data_Temp - 1000;
			}
		}
		else
		{
		}
		CoderData[1] = (uint8_t)(Data_Temp >> 8);
		CoderData[0] = (uint8_t)Data_Temp;
	}
	else
	{
	}
}
//==============================================================================
// DESCRIPTION : uint8_t MotorJumpInustepIOControlCallback() 
//						   Motor Jump In u-step control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================		
void MotorJumpInustepIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(SubSecMenuID == SubSecMenu_MotorJumpinuStep_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2] >= 4)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 4;
			}
			else
			{
				CoderData[2]--;
			}
		}
	}
	else if(SubSecMenuID == SubSecMenu_MotorJumpinuStep_Value)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[1] < 0x40)
			{
				CoderData[1] = (CoderData[1] + 0x10)&0xf0;
			}
			else if(CoderData[1] == 0x40)
			{
				CoderData[1] = 0xC0;
			}
			else if(CoderData[1] < 0xf0)
			{
				CoderData[1] = (CoderData[1] + 0x10)&0xf0;
			}
			else if(CoderData[1] == 0xf0)
			{
				CoderData[1] = 0xff;
			}
			else
			{
				CoderData[1] = 0x00;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[1] <= 0x00)
			{
				CoderData[1] = 0xff;
			}
			else if(CoderData[1] <= 0x40)
			{
				CoderData[1] = (CoderData[1] - 0x10)&0xf0;
			}
			else if(CoderData[1] <= 0xc0)
			{
				CoderData[1] = 0x40;
			}
			else if(CoderData[1] <= 0xf0)
			{
				CoderData[1] = (CoderData[1] - 0x10)&0xf0;
			}
			else
			{
				CoderData[1] = 0xf0;
			}
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t TFTPatternIOControlCallback() 
//						   TFT Pattern Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void TFTPatternIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
	{
		if(CoderData[2]  >= 13)
		{
			CoderData[2] = 0;
		}
		else
		{
			CoderData[2]++;
		}
	}
	else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
	{
		if(CoderData[2] <= 0)
		{
			CoderData[2] = 13;
		}
		else
		{
			CoderData[2]--;
		}
	}
	else
	{
	}
}
//==============================================================================
// DESCRIPTION : uint8_t SoundVolumeIOControlCallback() 
//						   Sound Volume Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void SoundVolumeIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
	{
		if(CoderData[2] >= 100)
		{
			CoderData[2] = 0;
		}
		else
		{
			CoderData[2] = CoderData[2] + 10;
		}
	}
	else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
	{
		if(CoderData[2] < 10)
		{
			CoderData[2] = 100;
		}
		else
		{
			CoderData[2] = CoderData[2] - 10;
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t ADCInputReadingRoutineCallback() 
//						   ADC Input Reading Routine Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================		
void ADCInputReadingRoutineCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
	if(SubSecMenuID == SubSecMenu_Routine_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2]  >= 3)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 3;
			}
			else
			{
				CoderData[2]--;
			}
		}
		else
		{
		}
	}
	else if(SubSecMenuID == SubSecMenu_Routine_SampleNum)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[1]  >= 255)
			{
				CoderData[1] = 0;
			}
			else
			{
				CoderData[1]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[1] <= 0)
			{
				CoderData[1] = 255;
			}
			else
			{
				CoderData[1]--;
			}
		}
		else
		{
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t AudioVolumeInputReadingRoutineCallback() 
//						   Audio Volume Reading Routine Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
/*void CaliInputReadingRoutineCallback(uint8_t u8CurCoderValState)
{
}
void AnalogInputReadingByOhmRoutineCallback(uint8_t u8CurCoderValState)
{
}*/
void AudioVolumeInputReadingRoutineCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
		if(SubSecMenuID == SubSecMenu_Routine_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2]  >= 1)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 1;
			}
			else
			{
				CoderData[2]--;
			}
		}
		else
		{
		}
	}
	else if(SubSecMenuID == SubSecMenu_Routine_SampleNum)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[1]  >= 255)
			{
				CoderData[1] = 0;
			}
			else
			{
				CoderData[1]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[1] <= 0)
			{
				CoderData[1] = 255;
			}
			else
			{
				CoderData[1]--;
			}
		}
		else
		{
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t SiwalaInputReadingRoutineCallback() 
//						   Simala Input Reading Routine Control
// PARAMETERS  : uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData
//
// RETURN VALUE : none
//==============================================================================	
void SiwalaInputReadingRoutineCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData)
{
		if(SubSecMenuID == SubSecMenu_Routine_Type)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[2]  >= 8)
			{
				CoderData[2] = 0;
			}
			else
			{
				CoderData[2]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[2] <= 0)
			{
				CoderData[2] = 8;
			}
			else
			{
				CoderData[2]--;
			}
		}
		else
		{
		}
	}
	else if(SubSecMenuID == SubSecMenu_Routine_SampleNum)
	{
		if(u8CurCoderValState == CODER_ROTATE_STATE_INCREASE)
		{
			if(CoderData[1]  >= 255)
			{
				CoderData[1] = 0;
			}
			else
			{
				CoderData[1]++;
			}
		}
		else if(u8CurCoderValState == CODER_ROTATE_STATE_DECREASE)
		{
			if(CoderData[1] <= 0)
			{
				CoderData[1] = 255;
			}
			else
			{
				CoderData[1]--;
			}
		}
		else
		{
		}
	}
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
