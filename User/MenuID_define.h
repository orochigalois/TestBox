#ifndef _MENUID_DEFINE_H_
#define _MENUID_DEFINE_H_

#include "includes.h"
#define CODER_ROTATE_STATE_INCREASE							1
#define CODER_ROTATE_STATE_DECREASE							2

#define LEFTRIGHT_BOTTON_STATE_LEFTPRESSED			1
#define LEFTRIGHT_BOTTON_STATE_RIGHTPRESSED			2

#define UPDOWN_BOTTON_STATE_UPPRESSED						1
#define UPDOWN_BOTTON_STATE_DOWNPRESSED					2

typedef enum 
{
	MainMenu,
	SecMenu,
	SubSecMenu,
	Menu_Count
}DispMenu_ID;

typedef enum
{
	MainMenu_Session,
	MainMenu_ReadDataByID,
	MainMenu_IOControl,
	MainMenu_Routine,
	MainMenu_Alex,
	MainMenu_Count
}enumMainMenu;

typedef enum
{
 SecSession_EnterManuSession,
 SecSession_ExistManuSession,
 SecSession_Count	
}enumSecSession;

typedef enum
{
	SecReadDataByID_PCBSerialNum,	
	SecReadDataByID_EEPSWVersion,
	SecReadDataByID_BackgroundButton,
	SecReadDataByID_CurrentButton,
	SecReadDataByID_CableConnection,
	SecReadDataByID_SpeedoXPostion,
	SecReadDataByID_TachoXPostion,
	SecReadDataByID_FuelXPostion,
	SecReadDataByID_WaterXPostion,
	SecReadDataByID_SpeedoYPostion,
	SecReadDataByID_TachoYPostion,
	SecReadDataByID_FuelYPostion,
	SecReadDataByID_WaterYPostion,
	SecReadDataByID_CaliAnalogInput,
	SecReadDataByID_BrandInfo,
	SecReadDataByID_TransponderWrite,
	SecReadDataByID_TransponderRead,
	SecReadDataByID_KeyID,
	SecReadDataByID_DigitalInput,
	SecReadDataByID_SelfTestStatus,
	SecReadDataByID_ReadDTCStatus,	
	SecReadDataByID_Count									
}enumSecReadDataByID;

typedef enum
{
	SecIOControl_LEDControl,
	SecIOControl_LEDControlToECU,
	SecIOControl_LCDControl,
	SecIOControl_LCDReturnToECU,
	SecIOControl_DimmingControl,
	SecIOControl_DimmingControlToECU,
	SecIOControl_SoundControl,
	SecIOControl_SoundControlToECU,
	SecIOControl_MotorMicOrDegreeControl,
	SecIOControl_MotorMicOrDegreeControlToECU,
	SecIOControl_MotorVehicleControl,
	SecIOControl_MotorVehicleControlToECU,
	SecIOControl_MotorJumpinuStepControl,
	SecIOControl_MotorJumpinuStepControlToECU,
	SecIOControl_TFTPatternControl,
	SecIOControl_TFTPatternControlToECU,
	SecIOControl_SoundVolumeControl,
	SecIOControl_SoundVolumeControlToECU,
	SecIOControl_OFFP5VControl,
	SecIOControl_OFFP5VControlToECU,
	SecIOControl_ONFuelSensorControl,
	SecIOControl_ONFuelSensorControlToECU,
	SecIOControl_Count
}enumSecIOControl;

typedef enum
{
	SecRoutine_ADCInputReadStart,
	SecRoutine_ADCInputReadResult,
	SecRoutine_CaliInputReadStart,
	SecRoutine_CaliInputReadResult,
	SecRoutine_InputReadByOhmStart,
	SecRoutine_InputReadByOhmResult,
	SecRoutine_AudioVolumeInputStart,
	SecRoutine_AudioVolumeInputResult,
	SecRoutine_SiwalaInputStart,
	SecRoutine_SiwalaInputResult,
	SecRoutine_Count
}enumSecRoutine;

typedef enum
{
	SecAlex_a,
	SecAlex_b,
	SecAlex_Count
}enumSecAlex;

typedef enum
{
	SubSecMenu_EnterManuSession_JCISession,
	SubSecMenu_EnterManuSession_Login,
	SubSecMenu_EnterManuSession_SetManuOn,
	SubSecMenu_EnterManuSession_Reset,
	SubSecMenu_EnterManuSession_JCIEOLSession,
	SubSecMenu_EnterManuSession_Count
}enumSubSecMenu_EnterManuSession;

typedef enum
{
	SubSecMenu_ExsitManuSession_JCIEOLSession,
	SubSecMenu_ExsitManuSession_SetManuOff,
	SubSecMenu_ExsitManuSession_Reset,
	SubSecMenu_ExsitManuSession_Count
}enumSubSecMenu_ExsitManuSession;

typedef enum
{
	SubSecMenu_LED_Type,
	SubSecMenu_LED_Status,	
	SubSecMenu_LED_Count
}enumSubSecMenu_LED;

typedef enum
{
	SubSecMenu_LCD_ControlKind,
	SubSecMenu_LCD_Count
}enumSubSecMenu_LCD;

typedef enum
{
	SubSecMenu_Dimming_Type,
	SubSecMenu_Dimming_Channel,
	SubSecMenu_Dimming_Value,
	SubSecMenu_Dimming_Count
}enumSubSecMenu_Dimming;

typedef enum
{
	SubSecMenu_Sound_Type,
	SubSecMenu_Sound_Count
}enumSubSecMenu_Sound;

typedef enum
{
	SubSecMenu_MotorMicOrDegree_Type,
	SubSecMenu_MotorMicOrDegree_Value,
	SubSecMenu_MotorMicOrDegree_Count
}enumSubSecMenu_MotorMicOrDegree;

typedef enum
{
	SubSecMenu_MotorVehicle_Type,
	SubSecMenu_MotorVehicle_Value,
	SubSecMenu_MotorVehicle_Count
}enumSubSecMenu_MotorVehicle;

typedef enum
{
	SubSecMenu_MotorHighImpedance_Type,
	SubSecMenu_MotorHighImpedance_Count
}enumSubSecMenu_HighImpedance;

typedef enum
{
	SubSecMenu_MotorLowTorque_Type,
	SubSecMenu_MotorLowTorque_Value,
	SubSecMenu_MotorLowTorque_Count
}enumSubSecMenu_MotorLowTorque;

typedef enum
{
	SubSecMenu_MotorJumpinuStep_Type,
	SubSecMenu_MotorJumpinuStep_Value,
	SubSecMenu_MotorJumpinuStep_Count
}enumSubSecMenu_MotorJumpinuStep;

typedef enum
{
	SubSecMenu_TFTPattern_Value,
	SubSecMenu_TFTPattern_Count
}enumSubSecMenu_TFTPattern;

typedef enum
{
	SubSecMenu_SoundVolume_Type,
	SubSecMenu_SoundVolume_Count
}enumSubSecMenu_SoundVolume;

typedef enum
{
	SubSecMenu_Routine_Type,
	SubSecMenu_Routine_SampleNum,
	SubSecMenu_Routine_Count
}enumSubSecMenu_Routine;

static uint8_t u8MaxDispMenu_Val[20] =
{
	MainMenu_Count,
	SecSession_Count,
	SecReadDataByID_Count,
	SecIOControl_Count,
	SecRoutine_Count,
	SecAlex_Count,
	SubSecMenu_EnterManuSession_Count,
	SubSecMenu_ExsitManuSession_Count,
	SubSecMenu_LED_Count,
	SubSecMenu_LCD_Count,
	SubSecMenu_Dimming_Count,
	SubSecMenu_Sound_Count,
	SubSecMenu_MotorMicOrDegree_Count,
	SubSecMenu_MotorVehicle_Count,
	SubSecMenu_MotorJumpinuStep_Count,
	SubSecMenu_TFTPattern_Count,
	SubSecMenu_SoundVolume_Count,
	NULL,//Switch Off 5V
	NULL,//Power Fuel Sensor
	SubSecMenu_Routine_Count
};																 	
#endif
