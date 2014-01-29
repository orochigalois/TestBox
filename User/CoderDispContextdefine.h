#ifndef _CODERDISPCONTEXTDEFINE_H_
#define _CODERDISPCONTEXTDEFINE_H_

const char cLEDType[5][15] =   
{{"Green LED"},
{"Blue LED"},
{"Yellow LED"},
{"Red LED"},
{"All LED"}};
															 
const char cLCDType[8][25] = 	
{{"OFF"},
{"ON"},
{"Chess"},
{"Revers Chess"},
{"Matrix Pattern 1"},
{"Matrix Pattern 2"},
{"Matrix Pattern 3"},
{"Matrix Pattern 4"}};

const char cDimmingType[2][20] = 	
{{"PWM ratio"},
{"Customer cali"}};

const char cDimmingChannel[4][20] = 	
{{"Pointers"},
{"Dials"},
{"LCD"},
{"All"}};

const char cSoundType[17][20] = 	
{{"Saw-500Hz"},
{"Sine-1KHz"},
{"Sine-42.8Hz"},
{"Acoustic A"},
{"Acoustic B"},
{"Acoustic C"},
{"Acoustic D"},
{"Acoustic E"},
{"Acoustic F"},
{"Acoustic G"},
{"Acoustic H"},
{"Acoustic I"},
{"Acoustic K"},
{"Acoustic L"},
{"Acoustic M"},
{"Blink_Sound_1"},
{"Blink_Sound_2"}};

const char cMotorMicOrDegreeType[10][20] = 	
{{"Speed u-step"},
{"Tacho u-step"},
{"Fuel u-step"},
{"Water u-step"},
{"All u-step"},
{"Speed 1/100C"},
{"Tacho 1/100C"},
{"Fuel 1/100C"},
{"Water 1/100C"},
{"All 1/100C"}};

const char cMotorVehicleType[4][20] = 	
{{"Speed 1/100Km/h"},
{"Tacho Rpm"},
{"Fuel 1/100%"},
{"Water 1/100C"}};

const char cMotorType[5][20] = 	
{{"Speed"},
{"Tacho"},
{"Fuel"},
{"Water"},
{"All Motor"}};

const char cFuelADCInputType[4][20] = 	
{{"ADC_Vol_r11"},
{"ADC_Vol_r12"},
{"ADC_Vol_r21"},
{"ADC_Vol_r22"}};

const char cCaliADCInputType[4][20] = 	
{{"Vol_cal_r11"},
{"Vol_cal_r12"},
{"Vol_cal_r21"},
{"Vol_cal_r22"}};

const char cAnaInputByOhmType[4][20] = 	
{{"R11_Calibrated"},
{"R12_Calibrated"},
{"R21_Calibrated"},
{"R22_Calibrated"}};

const char cAudioVolumeInputType[2][20] = 	
{{"MAI_MUL_A0"},
{"MAI_MUL_A1"}};


const char cSiwalaInputType[9][20] = 	
{{"MAI_D4_R_TT"},
{"MAI_D9_R_TT"},
{"MAI_T4_R_TT"},
{"MAI_T5_R_TT"},
{"MAI_D1_R_TT"},
{"MAI_D5_R_TT"},
{"MAI_D7_R_TT"},
{"MAI_D8_R_TT"},
{"AI_D6_Y_TT"}};																	 

#endif
