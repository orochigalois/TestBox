#ifndef _ROUTINECONTROL_H_
#define _ROUTINECONTROL_H_

#include "includes.h"
#include "can_handling.h"
//#include "MenuID_define.h"

#define ADCINPUTROUTINECONTROL_ID									0xf100
#define CALIINPUTROUTINECONTROL_ID_ID							0xf101
#define INPUTBYOHMROUTINECONTROL_ID								0xf105
#define AUDIOVOLUMEROUTINECONTROL_ID							0xf112
#define SIWALAINPUTROUTINECONTROL_ID							0xf113
uint8_t RoutineControlStartRequest(uint8_t Control_ID, uint8_t *RoutineParameter);
uint8_t RoutineControlResultRequest(uint8_t Control_ID);
#endif
