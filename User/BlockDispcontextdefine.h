#ifndef _BLOCKDISPCONTEXTDEFINE_H_
#define _BLOCKDISPCONTEXTDEFINE_H_

const char BlockDispSerialNumContext[20] = 			
"PCB Serial Number: "; 
												
const char BlockDispEEPSWVersionContext[5][25] = 				
{{"EEP Version: "},
{"EEP Revision: "},
{"SW Version: "},
{"SW Revision: "},
{"SW Iteration: "}}; 			

const char BlockDispBackButtonContext[2][25] = 				
{{"Test Result: "},
{"Control Status: "}}; 

const char BlockDispCurrentButtonContext[25] = 				
"Button Status: "; 	

const char BlockDispCableConnectionContext[25] = 				
"Cable: "; 

const char BlockDispPointerPositonContext[8][25] = 
{{"Pointer0 value: 0x"},
{"Pointer1 value: 0x"},
{"Pointer2 value: 0x"},
{"Pointer3 value: 0x"},
{"Pointer4 value: 0x"},
{"Pointer5 value: 0x"},
{"Pointer6 value: 0x"},
{"Pointer7 value: 0x"}}; 	

const char BlockDispCaliAnalogInputContext[4][25] = 				
{{"Hotspot temp: "},
{"Quartz temp: "},
{"Corrected Vbatt: "},
{"Corrected Lumi: "}}; 

const char BlockDispBrandInforContext[25] = 				
"Brand Infor: "; 

const char BlockDispKeyIDContext[25] = 				
"KeyID: "; 

const char BlockDispDigitalInputContext[25] = 				
"Parking brake: "; 

const char BlockDispSelfTestStatusContext[25] = 				
"Selftest Status: "; 

const char BlockDispRoutineResultContext[3][25] = 	
{{"Type"},
{"Value: 0x"}};
																					
const char BlockDTCResultContext[5] = 
{"DTC"};

const char cBrandInfor[5][20] = 	
{{"VW"},
{"Audi"},
{"SKODA"},
{"SEAT"},
{"VW-Commercial"}};

const char cSelftestStatus[4][20] = 	
{{"No error"},
{"RAM error"},
{"ROM error"},
{"RAM&ROM error"}};

extern const char cFuelADCInputType[4][20];																	 
extern const char cCaliADCInputType[4][20];	
extern const char cAnaInputByOhmType[4][20]; 	
extern const char cAudioVolumeInputType[2][20];
extern const char cSiwalaInputType[9][20];

const char *RoutineDispContext[5] = 	 {cFuelADCInputType[0],
																				cCaliADCInputType[0],
																				cAnaInputByOhmType[0],
																				cAudioVolumeInputType[0],
																				cSiwalaInputType[0]};	

#endif
