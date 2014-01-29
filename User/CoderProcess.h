#ifndef _CODERPROCESS_H_
#define _CODERPROCESS_H_

#include "includes.h"

typedef void (*tCoderRotatedProcessCallbacks)(uint8_t u8CoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);


void LEDIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void LCDIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void DimmingIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void SoundIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void MotorMicOrDegreeIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void MotorVehicleIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void MotorJumpInustepIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void TFTPatternIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void SoundVolumeIOControlCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void ADCInputReadingRoutineCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
//void CaliInputReadingRoutineCallback(uint8_t u8CurCoderValState);
//void AnalogInputReadingByOhmRoutineCallback(uint8_t u8CurCoderValState);
void AudioVolumeInputReadingRoutineCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);
void SiwalaInputReadingRoutineCallback(uint8_t u8CurCoderValState, uint8_t SubSecMenuID, uint8_t *CoderData);

static const tCoderRotatedProcessCallbacks CoderRotatedProcessCallbacks[14] =    
{                                                                                                                               
    LEDIOControlCallback,                                                
    LCDIOControlCallback,
		DimmingIOControlCallback,
		SoundIOControlCallback,
		MotorMicOrDegreeIOControlCallback,
		MotorVehicleIOControlCallback,
		MotorJumpInustepIOControlCallback,
		TFTPatternIOControlCallback,
		SoundVolumeIOControlCallback,
		ADCInputReadingRoutineCallback,
		ADCInputReadingRoutineCallback,
		ADCInputReadingRoutineCallback,
		AudioVolumeInputReadingRoutineCallback,
		SiwalaInputReadingRoutineCallback
}; 

#endif
