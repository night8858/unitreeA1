#include "bsp_usart.h"
#include "unitreeA1_cmd.h"


void SendData(USART_TypeDef* pUSARTx,uint8_t *data, int length)
{
 for (uint32_t i = 0; i < length; i++)
    {
        USART_SendData(pUSARTx,*data++); // 閸氭垳瑕嗛埢锝呭絺闁焦鏆熼幑锟�
        while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
    }

    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}



//----------------------------------------------------------
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    
    USART_SendData(pUSARTx, ch);

   
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

void Usart_SendData(USART_TypeDef *pUSARTx, uint8_t *data, uint8_t length)
{
    for (int i = 0; i <= length; i++)
    {
        Usart_SendByte(pUSARTx, *(data + i));
    }
}



