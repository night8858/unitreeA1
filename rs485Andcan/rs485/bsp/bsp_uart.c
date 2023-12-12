#include "bsp_uart.h"
#include "usart.h"
/**
  * @brief          发送uart_dma
  * @retval         无
  */
void uart_dma_printf(UART_HandleTypeDef *huart, char *fmt, ...)
{
  static uint8_t tx_buf[128] = {0};
  static va_list ap;
  static uint16_t len = 0;

  va_start(ap, fmt);
  len = vsprintf((char *)tx_buf, fmt, ap);
  va_end(ap);

  tx_buf[len] = '\0';
  // CDC_Transmit_FS(tx_buf, len);
  HAL_UART_Transmit_DMA(huart, tx_buf, len);

}
