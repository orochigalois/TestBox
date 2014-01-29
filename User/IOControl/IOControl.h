#ifndef _IOCONTROL_H_
#define _IOCONTROL_H_

#include "includes.h"
#include "can_handling.h"

#define IOCONTROL_OPTION_SHORTAJUST 	0x03
#define IOCONTROL_OPTION_RETURNTOECU 	0x00

//azhao7
#define 	LEDCHONTROL_ID								0xfd00
#define 	LCDCHONTROL_ID								0xfd02
#define 	DIMMINGCONTROL_ID							0xfd03
#define 	SOUNDCONTROL_ID								0xfd05
#define 	MOTORMICROORDEGREECONTROL_ID	0xfd07
#define 	MOTORVEHICLECONTROL_ID				0xfd08
#define 	MOTORJUMPUSTEP_ID							0xfd0c
#define 	TFTPATTERNCONTROL_ID					0xfd0d
#define 	SOUNDVOLUME_ID								0xfd20
#define 	OFFP5V_ID											0xfd21
#define 	ONFUELSENSOR_ID								0xfd22

typedef enum
{
	IOControl_ID_LEDControl,
	IOControl_ID_LCDControl,
	IOControl_ID_DimmingControl,
	IOControl_ID_SoundControl,
	IOControl_ID_MotorMicOrDegreeControl,
	IOControl_ID_MotorVehicleControl,
	IOControl_ID_MotorJumpinuStepControl,
	IOControl_ID_TFTPatternControl,
	IOControl_ID_SoundVolumeControl,
	IOControl_ID_OFFP5VControl,
	IOControl_ID_ONFuelSensorControl,
	IOControl_ID_Count
}enumIOControl_ID;


uint8_t IOControlCallback(uint8_t Control_ID, uint8_t Control_Option_Type, uint8_t *Parameter);

#endif
