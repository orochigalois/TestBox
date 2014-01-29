#ifndef _MENUDISPCONTEXTDEFINE_H_
#define _MENUDISPCONTEXTDEFINE_H_

#include "includes.h"
#include "MenuID_define.h"

#define MenuSize 35
#define SubMenuSize 15

const char MainMenu_Context[MainMenu_Count][35]	= 
{{"-- Session Control >>"},
{"-- ReadDataByIdentifer >>"},
{"-- InputOutputControl >>"},
{"-- Routine Control >>"},
{"-- Alex >>"}
};																								

const char SecMenuSessionContext[SecSession_Count][35] = 	 
{{"<< Enter Manu Session >>"},
{"<< Exsit Manu Session >>"}};							 

const char SecMenuReadDataByIDContext[SecReadDataByID_Count][35] = 
{{"<< Serial Number of PCB Read --"},
{"<< EEP and SW Version Read --"},
{"<< Background Button Read --"},
{"<< Current Button Status Read --"},
{"<< Cable Connection Read --"},
{"<< Speed Input Position Read --"},
{"<< Tacho Input Position Read --"},
{"<< Fuel Input Position Read --"},
{"<< Water Input Position Read --"},
{"<< Speed Output Position Read --"},
{"<< Tacho Output Position Read --"},
{"<< Fuel Output Position Read --"},
{"<< Water Output Position Read --"},
{"<< Cali Analog Input Read --"},
{"<< Brand Info Read --"},
{"<< Transponder Commu Read --"},
{"<< Transponder Commu Write --"},
{"<< Key ID Read --"},
{"<< Digital Input Read --"},
{"<< Selftest Status Read --"},
{"<< DTC Status Read--"}};																													

const char SecIOControlContext[SecIOControl_Count][35] = 
{{"<< LED Control >>"},
{"<< LED Control to ECU --"},
{"<< LCD Control >>"},
{"<< LCD Control to ECU --"},
{"<< Dimming Control >>"},
{"<< Dimming Control to ECU --"},
{"<< Sound Control >>"}, 
{"<< Sound Control to ECU --"},
{"<< Mic or Degree Control >>"},
{"<< Mic or Degree Control to ECU --"},
{"<< Motor Vehicle Control >>"},
{"<< Motor Vehicle Control to ECU --"},
{"<< Jump In ustep Control >>"},
{"<< Jump In ustep Control to ECU --"},
{"<< TFT Pattern Control >>"},
{"<< TFT Pattern Control to ECU --"},
{"<< Buzzer Volume Control >>"},
{"<< Buzzer Volume Control to ECU --"},
{"<< Off P_5V Control --"},
{"<< Off P_5V Control to ECU --"},
{"<< Power Fuel Control --"},
{"<< Power Fuel Control to ECU --"},
};
	
const char SecMenuRoutineContext[SecRoutine_Count][35] =  
{{"<< ADC Input Reading Start >>"},
{"<< ADC Input Reading Result --"},
{"<< Cali Input Reading Start >>"},
{"<< Cali Input Reading Result --"},
{"<< Input Reading by ohm Start >>"},
{"<< Input Reading by ohm Result --"},
{"<< Audio Volume Reading Start >>"},
{"<< Audio Volume Reading Result --"},
{"<< Siwala input Reading Start >>"},
{"<< Siwala input Reading Result --"}};

const char SecMenuAlexContext[SecAlex_Count][35] =  
{{"ReadSWVersion"},
{"reserve"}};


const char SubSecMenuEnterSessionContext[SubSecMenu_EnterManuSession_Count][15] =   
{{"Step1 Session"},
{"Step2 Login"},
{"Step3 Manu ON"},
{"Step4 Reset"},
{"Step5 JCI EOL"}};	

const char SubSecMenuExsitSessionContext[SubSecMenu_ExsitManuSession_Count][15] =   
{{"Step1 Session"},
{"Step2 Manu OFF"},
{"Step3 Reset"}};	

const char SubSecMenuLEDContext[SubSecMenu_LED_Count][15] =   
{{"LED Type"},
{"Control Status"}};

const char SubSecMenuLCDContext[SubSecMenu_LCD_Count][15] =   
{{"Control Type"}};	

const char SubSecMenuDimmingContext[SubSecMenu_Dimming_Count][15] =
{{"Type"},
{"Channel"},
{"Value"}};		
	
const char SubSecMenuSoundContext[SubSecMenu_Sound_Count][15] =
{{"Accous Signal"}};

																					
const char SubSecMenuMotorDegreeContext[SubSecMenu_MotorMicOrDegree_Count][15] = 
{{"Motor Type"},
{"Value"}};
																							
const char SubSecMenuMotorVehicleContext[SubSecMenu_MotorVehicle_Count][15] = 
{{"Motor Type"},
{"Value"}};
							
const char SubSecMenuMotorJumpContext[SubSecMenu_MotorJumpinuStep_Count][15] = 
{{"Motor Type"},
{"Value"}};
																							
const char SubSecMenuTFTPatternContext[SubSecMenu_TFTPattern_Count][15] =			 
{{"Patter Value"}};	

const char SubSecMenuSoundVolumeContext[SubSecMenu_SoundVolume_Count][15] =			 
{{"Type"}};	

const char SubSecRoutineContext[SubSecMenu_Routine_Count][15] = 
{{"Input Type"},
{"Sample Number"}};
																																		
const char *MenuDispContext[20]	= {MainMenu_Context[0],							//0
																	 SecMenuSessionContext[0],				//1
																	 SecMenuReadDataByIDContext[0],		//2
																	 SecIOControlContext[0],					//3
																	 SecMenuRoutineContext[0],	
																	 SecMenuAlexContext[0],	//4
																	 SubSecMenuEnterSessionContext[0],//5
																	 SubSecMenuExsitSessionContext[0],//6
																	 SubSecMenuLEDContext[0],					//7
																	 SubSecMenuLCDContext[0],      		//8
																	 SubSecMenuDimmingContext[0],			//9
																	 SubSecMenuSoundContext[0],				//10
																	 SubSecMenuMotorDegreeContext[0],	//11
																	 SubSecMenuMotorVehicleContext[0],//12
																	 SubSecMenuMotorJumpContext[0],		//13
																	 SubSecMenuTFTPatternContext[0],	//14
																	 SubSecMenuSoundVolumeContext[0],	//15
																	 NULL,														//16
																	 NULL,														//17
																	 SubSecRoutineContext[0]};				//18																 
																																																			


																	 

#endif
