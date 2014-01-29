#ifndef _CAN_HANDLING_H_
#define _CAN_HANDLING_H_

#include "includes.h"
#include "lpc177x_8x_can.h"

#include "SessionControl.h"
#include "SecurityAccess.h"
#include "TestPresent.h"
#include "IOControl.h"
#include "ReadDataByIDControl.h"
#include "RoutineControl.h"

#define RXSessionType 			0x50
#define RXResetType					0x51
#define RXReadDTCStatusType 0x59
#define RXTestPresentType 	0x7E
#define RXSecutityType 			0x67
#define RXIOControlType 		0x6F
#define RXReadDataByIDType 	0x62
#define RXWriteDataByIDType 0x6E
#define RXRoutineType 			0x71

void vCAN_Init(void);

void CAN_IRQHandler(void);

void SendService_CAN(uint8_t *TXDataBuffer);

#endif
