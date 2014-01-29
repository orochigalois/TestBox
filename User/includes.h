/*
*******************************************************************************
  Copyright (C), 2012-2014, Embest Tech. Co., Ltd.
  FileName		    : 
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

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>

#include <os_cfg.h>
#include <os_cpu.h>
#include <ucos_ii.h>

#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_exti.h"
#include "bsp.h"

#include "app_cfg.h"
#include "LCD.h"
#include "GUI.h"

#define PRO_BACK_COLOR                  GUI_LIGHTBLUE
#define PRO_FONT_COLOR                  GUI_WHITE
#define PRO_SELECT_COLOR                GUI_RED

#define MAX_MENU_ITEMS_PER_PAGE         11 

#define PRO_FONT_SIZE                   24
#define Font16B_SIZE										19

#define MENU_AREA_ULX                 	10
#define MENU_AREA_ULY                 	10
#define MENU_AREA_LRX                 	265
#define MENU_AREA_LRY                 	270

#define CLUSTER_INFOR_IDENTIFY_X        270//268
#define CLUSTER_INFOR_IDENTIFY_Y        8

#define CLUSTER_INFOR_FRAME_ULX         270//268
#define CLUSTER_INFOR_FRAME_ULY         25
#define CLUSTER_INFOR_FRAME_LRX         470
#define CLUSTER_INFOR_FRAME_LRY         62

#define CLUSTER_INFOR_AREA_ULX          272//270
#define CLUSTER_INFOR_AREA_ULY          27
#define CLUSTER_INFOR_AREA_LRX          468
#define CLUSTER_INFOR_AREA_LRY          60

#define CLUSTER_INFOR_ULX               274//272
#define CLUSTER_INFOR_ULY               28
#define CLUSTER_INFOR_LRX               467
#define CLUSTER_INFOR_LRY               45

#define CLUSTER_SESSION_INFOR_ULX       274//272
#define CLUSTER_SESSION_INFOR_ULY       43
#define CLUSTER_SESSION_INFOR_LRX       467
#define CLUSTER_SESSION_INFOR_LRY       60


#define RESPONSE_IDENTIFY_X        270//268
#define RESPONSE_IDENTIFY_Y        63


#define RESPONSE_AREA_ULX          270
#define RESPONSE_AREA_ULY          80
#define RESPONSE_AREA_LRX          480
#define RESPONSE_AREA_LRY          95

#define BLOCK_INFOR_ULX                 273
#define BLOCK_INFOR_ULY                 100//50
#define BLOCK_INFOR_LRX                 457
#define BLOCK_INFOR_LRY                 260

#define BLOCK_INFOR_X                 	278
#define BLOCK_INFOR_Y                 	105//50

#define SUBVAL_OFFSET_ULX               135
#define SUBVAL_OFFSET_ULY               10
#define SUBVAL_OFFSET_LRX               268
#define SUBVAL_OFFSET_LRY               34

#endif

