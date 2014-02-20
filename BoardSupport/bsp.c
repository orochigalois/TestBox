/*
*******************************************************************************
  Copyright (C), 2012-2014, Embest Tech. Co., Ltd.
  FileName		    : bsp.c
  Author          : lichy       
  Version 		    : 1.0.0     
  Date			      : 2012/02/28
  Description	    : 
  Function List   : 
  History		      :
  <author>  	    : lichy       
  <time>     	    : 2012/02/28
  <version >      : 1.0.0 	
  <desc>		      : build this moudle			 
*******************************************************************************
*/
#include "includes.h"
#include "bsp.h"
#include "lpc177x_8x_gpio.h"
#include "emc_nand.h"
/*
******************************************************************************
  Function:       BSP_LED_Init
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_Init (void)
{
//	GPIO_SetDir(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);
//	GPIO_SetDir(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);

//  BSP_LED_Off(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK);
//	BSP_LED_Off(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK);
}

/*
******************************************************************************
  Function:       BSP_LED_On
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_On (uint8_t port, uint32_t mask)
{
//  GPIO_OutputValue(port, mask, 1);
}

/*
******************************************************************************
  Function:       BSP_LED_Off
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_Off (uint8_t port, uint32_t mask)
{
//	 GPIO_OutputValue(port, mask, 0);
}

/*
******************************************************************************
  Function:       BSP_LED_Toggle
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_Toggle (uint8_t port, uint32_t mask)
{
//  uint32_t value;

//  value = GPIO_ReadValue(port);
//	value &= mask;

//	if (value != 0) {
//    BSP_LED_Off(port, mask);
//  } else { 
//    BSP_LED_On(port, mask);
//  }	
}

/*******************************************************************************



********************************************************************************/
void BSP_KEY_Init(void)
{
	
   GPIO_Init();
	/* LED1   P2.21 CORE and SDK Both*/
	/* LED2   P1.13 SDK Only */      
	/* LED3   P5.0  SDK Only */        
	/* LED4   P5.1  SDK Only */    		
	/*PINSEL_ConfigPin(2,21,0);	   // P2.21 - GPIO 
    GPIO_SetDir(2, (1<<21), 1);

	PINSEL_ConfigPin(1,13,0);	  
    GPIO_SetDir(1, (1<<13), 1);

	PINSEL_ConfigPin(5,0,0);	   
    GPIO_SetDir(5, (1<<0), 1);

	PINSEL_ConfigPin(5,1,0);	  
    GPIO_SetDir(5, (1<<1), 0);	*/ 
  
	PINSEL_ConfigPin(BRD_CAN1_LED_PORT, BRD_CAN1_LED_PIN, 0);	   /* P1.6 - GPIO */
    GPIO_SetDir(BRD_CAN1_LED_PORT, (1<<BRD_CAN1_LED_PIN), 1);  
  PINSEL_ConfigPin(BRD_CAN2_LED_PORT, BRD_CAN2_LED_PIN, 0);	   /* P1.6 - GPIO */
    GPIO_SetDir(BRD_CAN2_LED_PORT, (1<<BRD_CAN2_LED_PIN), 1);  
    
	PINSEL_ConfigPin(BRD_KEY_OK_PORT, BRD_KEY_OK_PIN, 0);	   /* P1.4 - GPIO */
    GPIO_SetDir(BRD_KEY_OK_PORT, (1<<BRD_KEY_OK_PIN), 0);  
	
	PINSEL_ConfigPin(BRD_KEY_UP_PORT, BRD_KEY_UP_PIN, 0);	   /* P1.0 - GPIO */
    GPIO_SetDir(BRD_KEY_UP_PORT, (1<<BRD_KEY_UP_PIN), 0);  
		
	PINSEL_ConfigPin(BRD_KEY_DOWN_PORT, BRD_KEY_DOWN_PIN, 0);	   /* P1.1 - GPIO */
    GPIO_SetDir(BRD_KEY_DOWN_PORT, (1<<BRD_KEY_DOWN_PIN), 0);  
    
	PINSEL_ConfigPin(BRD_KEY_LEFT_PORT, BRD_KEY_LEFT_PIN, 0);	   /* P1.2 - GPIO */
    GPIO_SetDir(BRD_KEY_LEFT_PORT, (1<<BRD_KEY_LEFT_PIN), 0);

	PINSEL_ConfigPin(BRD_KEY_RIGHT_PORT, BRD_KEY_RIGHT_PIN, 0);	   /* P1.3 - GPIO */
    GPIO_SetDir(BRD_KEY_RIGHT_PORT, (1<<BRD_KEY_RIGHT_PIN), 0); 
    
  PINSEL_ConfigPin(BRD_CODER_VAL_A_PORT, BRD_CODER_VAL_A_PIN, 0); //P2.10 -> GPIO_INT ISP
		GPIO_SetDir(BRD_CODER_VAL_A_PORT, BRD_CODER_VAL_A_PIN, 0);
  PINSEL_ConfigPin(BRD_CODER_VAL_B_PORT, BRD_CODER_VAL_B_PIN, 0); //P1.5 -> GPIO
		GPIO_SetDir(BRD_CODER_VAL_B_PORT, BRD_CODER_VAL_B_PIN, 0);   
		GPIO_IntCmd(BRD_CODER_VAL_A_PORT, 0x01 << BRD_CODER_VAL_A_PIN, 1);
    
    /*PINSEL_ConfigPin(BRD_CODER_MENU_A_PORT, BRD_CODER_MENU_A_PIN, 0); //P0.17 -> GPIO_INT ISP
    GPIO_SetDir(BRD_CODER_MENU_A_PORT, BRD_CODER_MENU_A_PIN, 0);
    PINSEL_ConfigPin(BRD_CODER_MENU_B_PORT, BRD_CODER_MENU_B_PIN, 0); //P0.19 -> GPIO     Down
    GPIO_SetDir(BRD_CODER_MENU_B_PORT, BRD_CODER_MENU_B_PIN, 0);   
    GPIO_IntCmd(BRD_CODER_MENU_A_PORT, 0x01 << BRD_CODER_MENU_A_PIN, 1);*/

    NVIC_SetPriority(GPIO_IRQn, 3);
	  NVIC_EnableIRQ(GPIO_IRQn);    
    vCAN_Init();
	vUART_Init();
	EMC_NAND_Init();
	
}
