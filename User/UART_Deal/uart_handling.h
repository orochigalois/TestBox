#ifndef _UART_HANDLING_H_
#define _UART_HANDLING_H_

#include "includes.h"
#include "lpc177x_8x_uart.h"
#include "debug_frmwrk.h"
#include "emc_nand.h"

void vUART_Init(void);

void UART0_IRQHandler(void);

#endif
