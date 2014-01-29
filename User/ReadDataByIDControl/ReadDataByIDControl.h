#ifndef _READDATABYIDCONTROL_H_
#define _READDATABYIDCONTROL_H_

#include "includes.h"
#include "can_handling.h"
																			
#define SERIALNUMBER_ID							0xfd02
#define EEPANDSWVERSION_ID					0xfd03
#define BACKGROUNDBUTTON_ID					0xfd11
#define CURRENTBUTTON_ID						0xfd15
#define CABLECONNECT_ID							0xfd16
#define SPEEDINPUTPOSITION_ID				0xfd20
#define TACHOINPUTPOSITION_ID				0xfd21
#define FUELINPUTPOSITION_ID				0xfd22
#define WATERINPUTPOSITION_ID				0xfd23
#define SPEEDOUTPUTPOSITION_ID			0xfd28
#define TACHOOUTPUTPOSITION_ID			0xfd29
#define FUELOUTPUTPOSITION_ID				0xfd2a
#define WATEROUTPUTPOSITION_ID			0xfd2b
#define CALIANALOGINPUT_ID 					0xfdb2
#define BRANDINFO_ID 								0xfdb3
#define TRANSPONDERREAD_ID 					0x1000
#define TRANSPONDERWRITE_ID 				0x1001
#define KEYID_ID 										0xfdb4
#define EXTERNALDIGITALINPUT_ID 		0xfdb5
#define SELFTEST_ID 								0xfdb6
#define DTCStatus_ID								0x0209
#define MANUFACSESSION_ID						0xfd60
uint8_t ReadDataByIDRequest(uint8_t	ReadData_Identifer_ID);

#endif
