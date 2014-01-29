/**********************************************************************
* $Id$		bsp.h			2011-06-02
*//**
* @file		bsp.h
* @brief	Contains basic information about the board that can
* 			be using with the current code package. It may
* 			include some header file for the components mounted
* 			on the board. Or else some neccessary hardware (IOs)
* 			settings for the using board may be involved.
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/


/* Peripheral group ----------------------------------------------------------- */
/** @defgroup BoardSupport Board Support
 * @ingroup LPC177x_8xCMSIS_Board_Support
 * @{
 */

#ifndef __BSP_H
#define __BSP_H


//ADC input preset on this board
#define BRD_ADC_PREPARED_CHANNEL		(ADC_CHANNEL_2)
#define BRD_ADC_PREPARED_INTR			  (ADC_ADINTEN2)

#define BRD_ADC_PREPARED_CH_PORT		  (0)
#define BRD_ADC_PREPARED_CH_PIN			  (25)
#define BRD_ADC_PREPARED_CH_FUNC_NO		(1)

//LED indicators preset
#define BRD_CAN1_LED_PORT           (1)
#define BRD_CAN1_LED_PIN            (16)

#define BRD_CAN2_LED_PORT           (1)
#define BRD_CAN2_LED_PIN            (17)

#define BRD_LED_1_PORT		            (BRD_CAN1_LED_PORT)
#define BRD_LED_1_PIN			        (BRD_CAN1_LED_PIN)
#define BRD_LED_1_MASK	            	(1 << BRD_LED_1_PIN)

#define BRD_LED_2_PORT		            (BRD_CAN2_LED_PORT)
#define BRD_LED_2_PIN	        		(BRD_CAN2_LED_PIN)
#define BRD_LED_2_MASK          		(1 << BRD_LED_2_PIN)

#define BRD_LED_3_PORT	            	(5)
#define BRD_LED_3_PIN	          		(0)
#define BRD_LED_3_MASK          		(1 << BRD_LED_3_PIN)

#define TURN_LED_1_ON()    GPIO_SetValue(BRD_LED_1_PORT, BRD_LED_1_MASK)
#define TURN_LED_1_OFF()   GPIO_ClearValue(BRD_LED_1_PORT, BRD_LED_1_MASK)
#define TURN_LED_2_ON()    GPIO_SetValue(BRD_LED_2_PORT, BRD_LED_2_MASK)
#define TURN_LED_2_OFF()   GPIO_ClearValue(BRD_LED_2_PORT, BRD_LED_2_MASK)
#define TURN_LED_3_ON()    GPIO_SetValue(BRD_LED_3_PORT, BRD_LED_3_MASK)
#define TURN_LED_3_OFF()   GPIO_ClearValue(BRD_LED_3_PORT, BRD_LED_3_MASK)

//PIO interrupt preset
#define BRD_PIO_USED_INTR_PORT			(0)
#define BRD_PIO_USED_INTR_PIN			  (13)
#define BRD_PIO_USED_INTR_MASK			(1 << BRD_PIO_USED_INTR_PIN)


//MCI power active levell
#define BRD_MCI_POWERED_ACTIVE_LEVEL	(1)


//Timer preset
#define BRD_TIMER_USED				      (LPC_TIM2)
#define BRD_TIM_INTR_USED			(TIMER2_IRQn)

#define BRD_TIM_CAP_LINKED_PORT		(1)
#define BRD_TIM_CAP_LINKED_PIN		(4)

//key input
#define BRD_KEY_OK_PORT           (1)
#define BRD_KEY_OK_PIN            (4)

#define BRD_KEY_UP_PORT           (1)
#define BRD_KEY_UP_PIN            (0)

#define BRD_KEY_DOWN_PORT         (1)
#define BRD_KEY_DOWN_PIN          (1)

#define BRD_KEY_LEFT_PORT         (1)
#define BRD_KEY_LEFT_PIN          (2)

#define BRD_KEY_RIGHT_PORT        (1)
#define BRD_KEY_RIGHT_PIN         (3)

//Coder input
#define BRD_CODER_VAL_A_PORT            (2)
#define BRD_CODER_VAL_A_PIN             (10)
#define BRD_CODER_VAL_B_PORT            (1)
#define BRD_CODER_VAL_B_PIN             (6)

#define BRD_CODER_MENU_A_PORT            (0)
#define BRD_CODER_MENU_A_PIN             (17)
#define BRD_CODER_MENU_B_PORT            (0)
#define BRD_CODER_MENU_B_PIN             (19)

void  BSP_LED_Init (void);
void  BSP_LED_Toggle (uint8_t port, uint32_t mask);
void  BSP_LED_On (uint8_t port, uint32_t mask);
void  BSP_LED_Off (uint8_t port, uint32_t mask);

void BSP_KEY_Init(void);
#endif//BSP_H

/**
 * @}
 */
