/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               BlockDisp.c
** Descriptions:            The BlockDisp application function
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
#include "BlockDisp.h"
#include "BlockDispcontextdefine.h"
//==============================================================================
// DESCRIPTION : SerialNumberBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Serial Number of PBC
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void SerialNumberBlockDsipCallback(uint8_t *InputPoint)
{
	uint32_t u32SerialNumber = (((uint32_t)InputPoint[4]) << 24)+(((uint32_t)InputPoint[5])<<16)+(((uint32_t)InputPoint[6])<<8)+InputPoint[7];
	GUI_DispString(BlockDispSerialNumContext);
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);//+60
	GUI_DispString("0x");
	GUI_DispHex(u32SerialNumber, 8);
}
//==============================================================================
// DESCRIPTION : EEPSWVersionBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip EEP and SW Version
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void EEPSWVersionBlockDsipCallback(uint8_t *InputPoint)
{
	uint8_t Count_Temp;
	for(Count_Temp = 0; Count_Temp < 5; Count_Temp++)
	{
		GUI_DispString(BlockDispEEPSWVersionContext[Count_Temp]);
		GUI_DispString("0x");
		GUI_DispHex(InputPoint[4+Count_Temp], 2);
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y + Font16B_SIZE* (Count_Temp+1));
	}
}
//==============================================================================
// DESCRIPTION : BackButtonBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Background Button Status
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void BackButtonBlockDsipCallback(uint8_t *InputPoint)
{
	uint8_t Count_Temp;
	for(Count_Temp = 0; Count_Temp < 2; Count_Temp++)
	{
		GUI_DispString((BlockDispBackButtonContext[Count_Temp]));
		GUI_DispString("0x");
		GUI_DispHex(InputPoint[4+Count_Temp], 2);
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y + Font16B_SIZE* (Count_Temp+1));
	}
}
//==============================================================================
// DESCRIPTION : CurrentButtonBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Current Button Status
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void CurrentButtonBlockDsipCallback(uint8_t *InputPoint)
{
	GUI_DispString(BlockDispCurrentButtonContext);
	if(InputPoint[4] == 0x01)
	{
		GUI_DispString("Pressed");
	}
	else
	{
		GUI_DispString("Not Pressed");
	}
}
//==============================================================================
// DESCRIPTION : CableConnectionBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Cable Connection Status
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void CableConnectionBlockDsipCallback(uint8_t *InputPoint)
{
	GUI_DispString(BlockDispCableConnectionContext);
	if(InputPoint[4] == 0x01)
	{
		GUI_DispString("Connected");
	}
	else
	{
		GUI_DispString("Not Connected");
	}
}
//==============================================================================
// DESCRIPTION : MotorInputOutputPointBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Motor Input and Output Position
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void MotorInputOutputPointBlockDsipCallback(uint8_t *InputPoint)
{
	uint8_t Count_Temp;
	for(Count_Temp = 0; Count_Temp < 8; Count_Temp++)
	{
		GUI_DispString(BlockDispPointerPositonContext[Count_Temp]);
		GUI_DispString("0x");
		GUI_DispHex((((uint16_t)InputPoint[Count_Temp*2+4])<<8)+InputPoint[Count_Temp*2+5], 4);
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y + Font16B_SIZE* (Count_Temp+1));
	}
}
//==============================================================================
// DESCRIPTION : CaliAnologInputBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Calibrated Analog Input
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void CaliAnologInputBlockDsipCallback(uint8_t *InputPoint)
{
	uint8_t Count_Temp;
	for(Count_Temp = 0; Count_Temp < 2; Count_Temp++)
	{
		GUI_DispString(BlockDispCaliAnalogInputContext[Count_Temp]);
		GUI_DispString("0x");
		GUI_DispHex(InputPoint[4+Count_Temp], 2);
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y + Font16B_SIZE*(Count_Temp+1));
	}
	for(Count_Temp = 2; Count_Temp < 4; Count_Temp++)
	{
		GUI_DispString(BlockDispCaliAnalogInputContext[Count_Temp]);
		GUI_DispString("0x");
		GUI_DispHex((((uint32_t)InputPoint[Count_Temp*2+2])<<8)+InputPoint[Count_Temp*2+3], 4);
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y + Font16B_SIZE*(Count_Temp+1));
	}		
}
//==============================================================================
// DESCRIPTION : BrandInforBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Brand Information
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void BrandInforBlockDsipCallback(uint8_t *InputPoint)
{
	GUI_DispString(BlockDispBrandInforContext);
	GUI_DispString(cBrandInfor[InputPoint[4]]);
}
//==============================================================================
// DESCRIPTION : TransponderReadBlockDsipCallback(uint8_t *InputPoint)
//						   Test the communication between the key and the cluster
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void TransponderReadBlockDsipCallback(uint8_t *InputPoint)
{
	uint16_t u16StateChannel1 = (((uint16_t)InputPoint[4])<<8)+InputPoint[5];
	uint16_t u16StateChannel2 = (((uint16_t)InputPoint[6])<<8)+InputPoint[7];
	uint32_t u32TransponderID  = (((uint32_t)InputPoint[8]) << 24)+(((uint32_t)InputPoint[9])<<16)+(((uint32_t)InputPoint[10])<<8)+InputPoint[11];

	GUI_DispString("State1: 0x");
	GUI_DispHex(u16StateChannel1, 4);
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);
	GUI_DispString("State2: 0x");
	GUI_DispHex(u16StateChannel2, 4);
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE*2);
	GUI_DispString("Transponder ID:");
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE*3);//+30
	GUI_DispString("0x");
	GUI_DispHex(u32TransponderID, 8);
}
//==============================================================================
// DESCRIPTION : TransponderWriteBlockDsipCallback(uint8_t *InputPoint)
//						   Test the communication between the key and the cluster
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void TransponderWriteBlockDsipCallback(uint8_t *InputPoint)
{
	uint16_t u16StateChannel1 = (((uint16_t)InputPoint[4])<<8)+InputPoint[5];
	uint16_t u16StateChannel2 = (((uint16_t)InputPoint[6])<<8)+InputPoint[7];
	uint32_t u32ContentUserMem  = (((uint32_t)InputPoint[8]) << 24)+(((uint32_t)InputPoint[9])<<16)+(((uint32_t)InputPoint[10])<<8)+InputPoint[11];
	if((u16StateChannel1 == 0x00)||(u16StateChannel2 == 0x00))
	{
		GUI_DispString("Immo OK");
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);//+10
		GUI_DispString("Key in Position");
	}
	else if((u16StateChannel1 == 0x02)||(u16StateChannel2 == 0x02))
	{
		GUI_SetColor(GUI_RED);
		GUI_DispString("Immo NOK");
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);//+10
		GUI_DispString("Key Completely removed");
	}
	else if((u16StateChannel1 == 0x0800)||(u16StateChannel2 == 0x0800))
	{
		GUI_SetColor(GUI_RED);
		GUI_DispString("Immo NOK");
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);//+10
		GUI_DispString("Key Pulled from Coil");
	}
	else
	{
		GUI_SetColor(GUI_RED);
		GUI_DispString("Immo NOK");
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);
	}
  GUI_SetColor(PRO_FONT_COLOR);
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+(Font16B_SIZE*2));
	GUI_DispString("Content User Mem:");
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+(Font16B_SIZE*3));//+30
	GUI_DispString("0x");
	GUI_DispHex(u32ContentUserMem, 8);
}
//==============================================================================
// DESCRIPTION : KeyIDBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Key ID Information
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void KeyIDBlockDsipCallback(uint8_t *InputPoint)
{
	uint32_t u32SerialNumber = (((uint32_t)InputPoint[4]) << 24)+(((uint32_t)InputPoint[5])<<16)+(((uint32_t)InputPoint[6])<<8)+InputPoint[7];
	GUI_DispString(BlockDispKeyIDContext);
	GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE);//+30
	GUI_DispString("0x");
	GUI_DispHex(u32SerialNumber, 8);
}
//==============================================================================
// DESCRIPTION : ExternalDigitalBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip External Digital Input
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void ExternalDigitalBlockDsipCallback(uint8_t *InputPoint)
{
	GUI_DispString(BlockDispDigitalInputContext);
	if(InputPoint[4] == 0x01)
	{
		GUI_DispString("High");
	}
	else
	{
		GUI_DispString("Low");
	}
}
//==============================================================================
// DESCRIPTION : SelfTestBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Self Test Status
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void SelfTestBlockDsipCallback(uint8_t *InputPoint)
{
	GUI_DispString(BlockDispSelfTestStatusContext);
	GUI_DispString(cSelftestStatus[InputPoint[4]]);
}
//==============================================================================
// DESCRIPTION : ExternalDigitalBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip DTC Status
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void ReadDTCStatusBlockDsipCallback(uint8_t *InputPoint)
{
	uint8_t u8Count = 0;
	if(InputPoint[0] <= 3)
	{
		GUI_DispString("No DTC");
	}
	else
	{
		GUI_DispString(BlockDTCResultContext);
		GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y);
		GUI_DispString("DTC ID");
		GUI_GotoXY(BLOCK_INFOR_X+80, BLOCK_INFOR_Y);
		GUI_DispString("State");
		for(u8Count = 1; u8Count <= (InputPoint[0]-3)/4; u8Count++)
		{
			uint32_t u32SerialNumber = (((uint32_t)InputPoint[u8Count*4]) << 16)+(((uint32_t)InputPoint[u8Count*4+1])<<8)+((uint32_t)InputPoint[u8Count*4+2]);
			GUI_GotoXY(BLOCK_INFOR_X, BLOCK_INFOR_Y+Font16B_SIZE*u8Count);//+40
			GUI_DispString("0x");
			GUI_DispHex(u32SerialNumber, 6);
			GUI_GotoXY(BLOCK_INFOR_X+80, BLOCK_INFOR_Y+Font16B_SIZE*u8Count);//+40
			GUI_DispString("0x");
			GUI_DispHex(InputPoint[u8Count*4+3], 2);
		}
	}
}
//==============================================================================
// DESCRIPTION : RoutineControlBlockDsipCallback(uint8_t *InputPoint)
//						   Dsip Routine Control Result
// PARAMETERS  : InputPoint
//
// RETURN VALUE : none
//==============================================================================	
void RoutineControlBlockDsipCallback(uint8_t RoutineControl_ID, uint8_t *InputPoint)
{
	if(InputPoint[0] < 6)
	{
		GUI_SetColor(GUI_RED);
		GUI_DispString("No Reading Data Received!");
	}
	else
	{
		GUI_DispString(RoutineDispContext[RoutineControl_ID]+(InputPoint[6]-1)*20);
		GUI_DispString(":  0x");
		GUI_DispHex((((uint32_t)InputPoint[7])<<8)+InputPoint[8], 4);
	}
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
