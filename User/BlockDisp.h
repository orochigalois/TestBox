#ifndef _BLOCKDISP_H_
#define _BLOCKDISP_H_

#include "includes.h"

typedef void (*tBlockDispProcessCallbacks)(uint8_t *InputPoint);

void SerialNumberBlockDsipCallback(uint8_t *InputPoint);
void EEPSWVersionBlockDsipCallback(uint8_t *InputPoint);
void BackButtonBlockDsipCallback(uint8_t *InputPoint);
void CurrentButtonBlockDsipCallback(uint8_t *InputPoint);
void CableConnectionBlockDsipCallback(uint8_t *InputPoint);
void MotorInputOutputPointBlockDsipCallback(uint8_t *InputPoint);
void CaliAnologInputBlockDsipCallback(uint8_t *InputPoint);
void BrandInforBlockDsipCallback(uint8_t *InputPoint);
void TransponderReadBlockDsipCallback(uint8_t *InputPoint);
void TransponderWriteBlockDsipCallback(uint8_t *InputPoint);
void KeyIDBlockDsipCallback(uint8_t *InputPoint);
void ExternalDigitalBlockDsipCallback(uint8_t *InputPoint);
void SelfTestBlockDsipCallback(uint8_t *InputPoint);
void ReadDTCStatusBlockDsipCallback(uint8_t *InputPoint);

void RoutineControlBlockDsipCallback(uint8_t RoutineControl_ID, uint8_t *InputPoint);

static const tBlockDispProcessCallbacks BlockDispProcessCallbacks[21] =    
{                                                                                                                               
    SerialNumberBlockDsipCallback,                                                
    EEPSWVersionBlockDsipCallback,
		BackButtonBlockDsipCallback,
		CurrentButtonBlockDsipCallback,
		CableConnectionBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		MotorInputOutputPointBlockDsipCallback,
		CaliAnologInputBlockDsipCallback,
		BrandInforBlockDsipCallback,
		TransponderReadBlockDsipCallback,
		TransponderWriteBlockDsipCallback,
		KeyIDBlockDsipCallback,
		ExternalDigitalBlockDsipCallback,
		SelfTestBlockDsipCallback,
		ReadDTCStatusBlockDsipCallback
}; 
#endif

