/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "unitreeA1_cmd.h"
#include "bsp_rc_it.h"
#include "bsp_dma.h"
#include "bsp_usart.h"
#include "Delay.h"

int main(void)
	
{	

	RCC_ClocksTypeDef rcc;    
    RCC_GetClocksFreq(&rcc);         //读取系统时钟频率_test
   
	remote_control_init();
  /* Infinite loop */
  while (1)
  {
	  /*修改了主频串口发送问题解决，
	  1.初始对应串口结构体（对应的函数在usart和dma界面里，对应着换即可）
	  2.测试
	  */
	  modfiy_cmd(&cmd_leg[3],2,0,0,0,0,0);
	  unitreeA1_tx(3);
	  Delay_ms(1);	  
	  modfiy_cmd(&cmd_leg[0],2,0,0,0,0,0);
	  unitreeA1_tx(0);
	  Delay_ms(1);
	  modfiy_cmd(&cmd_leg[2],2,0,0,0,0,0);
	  unitreeA1_tx(2);
	  Delay_ms(1);
	  
  }
}

