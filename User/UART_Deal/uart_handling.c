/***************************************************************************************************
This file is for UART dealing.

*****************************************************************************************************/
#include "uart_handling.h"
#include <ucos_ii.h>


uint8_t receiveBuff[2048];
uint32_t RxIndex=0;
uint16_t PageIndex=0; //2/*1024*64 pages*/
uint8_t returnChar[2]={0xfd,0x00};

/*=============================================================================
DESCRIPTION: UART_Init

PARAMETERS:void
RETURN VALUE:

DESIGN INFORMATION: alex 2014/1/26
=============================================================================*/
void vUART_Init(void)
{
    UART_IntConfig(0,UART_INTCFG_RBR,ENABLE);
    NVIC_EnableIRQ(UART0_IRQn);
}


/*=============================================================================
DESCRIPTION: UART0_IRQHandler

PARAMETERS:void
RETURN VALUE:

DESIGN INFORMATION: alex 2014/1/26
=============================================================================*/
void UART0_IRQHandler(void)
{

    uint8_t c;

    if(_DG_NONBLOCK(&c))
    {

	     receiveBuff[RxIndex] = c;
	     RxIndex++;
		 if(RxIndex>=2048)//buff full,write to nand flash
		 {

		 	EMC_NAND_WriteSinglePage((void*)receiveBuff,PageIndex++);
			RxIndex=0;

			_DBG(returnChar);
			
		 }
	

    }


}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
