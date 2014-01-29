#ifndef _SESSIONCONTROL_H_
#define _SESSIONCONTROL_H_

#include "includes.h"
#include "can_handling.h"

#define DEFAULTSESSION_ID					0x01
#define DIAGSESSION_ID						0x03
#define JCI_EOL_SESSION_ID				0x60
#define JCI_SESSION_ID						0x61

uint8_t SessionControlRequest(uint8_t	Session_StepNum, uint8_t	bIsEnterOrExsit);
void CAN_CRC_Calculate(uint8_t * RMsg);
void JCISessionControl(uint8_t bIsEnterOrExsit);
void JCIManuONOFFControl(uint8_t bIsEnterOrExsit);
void JCIResetControl(void);

#endif
