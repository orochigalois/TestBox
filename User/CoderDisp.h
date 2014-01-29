#ifndef _CODERDISP_H_
#define _CODERDISP_H_

#include "includes.h"

typedef void (*tSubMenuDispProcessCallbacks)(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);

void LEDIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void LCDIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void DimmingIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void SoundIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void MotorMicOrDegreeIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void MotorVehicleIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void MotorJumpInustepIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void TFTPatternIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void SoundVolumeIOControlSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void ADCInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void CaliInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void AnalogInputReadingByOhmRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void AudioVolumeInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);
void SiwalaInputReadingRoutineSubMenuDispCallback(uint8_t SubSecMenuItem_ID, uint8_t *CoderData);

static const tSubMenuDispProcessCallbacks SubMenuDispProcessCallbacks[14] =    
{                                                                                                                               
    LEDIOControlSubMenuDispCallback,                                                
    LCDIOControlSubMenuDispCallback,
		DimmingIOControlSubMenuDispCallback,
		SoundIOControlSubMenuDispCallback,
		MotorMicOrDegreeIOControlSubMenuDispCallback,
		MotorVehicleIOControlSubMenuDispCallback,
		MotorJumpInustepIOControlSubMenuDispCallback,
		TFTPatternIOControlSubMenuDispCallback,
		SoundVolumeIOControlSubMenuDispCallback,
		ADCInputReadingRoutineSubMenuDispCallback,
		CaliInputReadingRoutineSubMenuDispCallback,
		AnalogInputReadingByOhmRoutineSubMenuDispCallback,
		AudioVolumeInputReadingRoutineSubMenuDispCallback,
		SiwalaInputReadingRoutineSubMenuDispCallback
}; 
#endif
