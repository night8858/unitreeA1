#ifndef BSP_UART_H
#define BSP_UART_H

#include "usart.h"
#include "stdio.h"
#include <stdarg.h>

extern void uart_dma_printf(UART_HandleTypeDef *huart, char *fmt, ...);

#endif //BSP_UART_H
