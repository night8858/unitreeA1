#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "stm32f4xx_conf.h"

#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>


void SendData(USART_TypeDef* pUSARTx,uint8_t *data, int length);


#endif
