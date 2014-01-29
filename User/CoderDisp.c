/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               CoderDisp.c
** Descriptions:            The CoderDisp application function
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
#include "CoderDisp.h"
#include "MenuID_define.h"
#include "CoderDispContextdefine.h"
//==============================================================================
// DESCRIPTION : uint8_t LEDIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   LED Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void LEDIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_LED_Type)
	{
		GUI_DispString(cLEDType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_LED_Status)
	{
		if(CoderData[1]& 0x01)//1
		{
			GUI_DispString("ON");
		}
		else
		{
			GUI_DispString("OFF");
		}
	}
}
//==============================================================================
// DESCRIPTION : uint8_t LCDIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   LCD Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void LCDIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	GUI_DispString(cLCDType[CoderData[2]]);
}
//==============================================================================
// DESCRIPTION : uint8_t DimmingIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Dimming Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void DimmingIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_Dimming_Type)
	{
		GUI_DispString(cDimmingType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Dimming_Channel)
	{
		GUI_DispString(cDimmingChannel[CoderData[1]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Dimming_Value)
	{
		GUI_DispDec(CoderData[0],3);
	}
	else
	{
	}
}
//==============================================================================
// DESCRIPTION : uint8_t SoundIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Sound Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void SoundIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	GUI_DispString(cSoundType[CoderData[2]]);
}
//==============================================================================
// DESCRIPTION : uint8_t MotorMicOrDegreeIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Motor u-step or Degree Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void MotorMicOrDegreeIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	uint16_t Data_Temp = 0;

	if(SubSecMenuItem_ID == SubSecMenu_MotorMicOrDegree_Type)
	{
		GUI_DispString(cMotorMicOrDegreeType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_MotorMicOrDegree_Value)
	{
		Data_Temp = ((uint32_t)CoderData[1] << 8) + CoderData[0];
		GUI_DispDec(Data_Temp,5);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t MotorVehicleIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Motor Vehicle Unit Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void MotorVehicleIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	uint16_t Data_Temp = 0;

	if(SubSecMenuItem_ID == SubSecMenu_MotorVehicle_Type)
	{
		GUI_DispString(cMotorVehicleType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_MotorVehicle_Value)
	{
		Data_Temp = ((uint32_t)CoderData[1] << 8) + CoderData[0];
		GUI_DispDec(Data_Temp,5);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t MotorJumpInustepIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Motor Jump In u-step Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void MotorJumpInustepIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_MotorJumpinuStep_Type)
	{
		GUI_DispString(cMotorType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_MotorJumpinuStep_Value)
	{
		GUI_DispString("0x");
		GUI_DispHex(CoderData[1],2);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t TFTPatternIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   TFT Pattern Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void TFTPatternIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	GUI_DispDec(CoderData[2],2);
}
//==============================================================================
// DESCRIPTION : uint8_t SoundVolumeIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Sound Volume Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void SoundVolumeIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	GUI_DispDec(CoderData[2],3);
}
//==============================================================================
// DESCRIPTION : uint8_t ADCInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   ADC Input Reading Routine Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void ADCInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_Routine_Type)
	{						
		GUI_DispString(cFuelADCInputType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Routine_SampleNum)
	{
		GUI_DispDec(CoderData[1],3);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t CaliInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Calibrated Input Reading Routine Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void CaliInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_Routine_Type)
	{						
		GUI_DispString(cCaliADCInputType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Routine_SampleNum)
	{
		GUI_DispDec(CoderData[1],3);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t AnalogInputReadingByOhmRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Analog Input Reading by Ohm Routine Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void AnalogInputReadingByOhmRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_Routine_Type)
	{						
		GUI_DispString(cAnaInputByOhmType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Routine_SampleNum)
	{
		GUI_DispDec(CoderData[1],3);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t AudioVolumeInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Audio Volume Input Reading Routine Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void AudioVolumeInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_Routine_Type)
	{						
		GUI_DispString(cAudioVolumeInputType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Routine_SampleNum)
	{
		GUI_DispDec(CoderData[1],3);
	}
}
//==============================================================================
// DESCRIPTION : uint8_t SiwalaInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID) 
//						   Siwala Input Reading Routine Control Menu Display
// PARAMETERS  : uint8_t SubSecMenuItem_ID
//
// RETURN VALUE : none
//==============================================================================	
void SiwalaInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData)
{
	if(SubSecMenuItem_ID == SubSecMenu_Routine_Type)
	{						
		GUI_DispString(cSiwalaInputType[CoderData[2]]);
	}
	else if(SubSecMenuItem_ID == SubSecMenu_Routine_SampleNum)
	{
		GUI_DispDec(CoderData[1],3);
	}
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
