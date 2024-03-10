#include "main.h"
#include "motor_msg.h"
#include <string.h>
#include <stdio.h>
#include "unitreeA1_cmd.h"
#include "bsp_usart.h"

#define LF 0
#define LB 1
#define RF 2
#define RB 3

motor_send_t cmd_leg[4] ;
motor_recv_t data_leg[4];

motor_recv_t data_motor[4][3];


void modfiy_cmd(motor_send_t *send, uint8_t id, float Pos, float KP, float KW, float W, float T)
{

    send->hex_len = 34;
    send->mode = 10;
    send->id = id;
    send->K_P = KP;
    send->K_W = KW;
    send->Pos = 6.2832 * 9.1 * 2 * Pos;
    send->W = 0;
    send->T = 0.0;
	
}



void unitreeA1_tx(int leg_id)
{
    /*—————————————————————————————————————————左前腿代码范围————————————————————————————————————————————————*/
    uint8_t A1cmd[34];

    // 此处为左腿电机结构体//
    cmd_leg[leg_id].motor_send_data.head.start[0] = 0xFE;
    cmd_leg[leg_id].motor_send_data.head.start[1] = 0xEE;
    cmd_leg[leg_id].motor_send_data.head.motorID = cmd_leg[leg_id].id;
    cmd_leg[leg_id].motor_send_data.head.reserved = 0x00;

    cmd_leg[leg_id].motor_send_data.Mdata.mode = cmd_leg[leg_id].mode;
    cmd_leg[leg_id].motor_send_data.Mdata.ModifyBit = 0xFF;
    cmd_leg[leg_id].motor_send_data.Mdata.ReadBit = 0x00;
    cmd_leg[leg_id].motor_send_data.Mdata.reserved = 0x00;
    cmd_leg[leg_id].motor_send_data.Mdata.Modify.F = 0;
    cmd_leg[leg_id].motor_send_data.Mdata.T = cmd_leg[leg_id].T ;
    cmd_leg[leg_id].motor_send_data.Mdata.W = cmd_leg[leg_id].W ;
    cmd_leg[leg_id].motor_send_data.Mdata.Pos = (int)((cmd_leg[leg_id].Pos ) );
    cmd_leg[leg_id].motor_send_data.Mdata.K_P = cmd_leg[leg_id].K_P ;
    cmd_leg[leg_id].motor_send_data.Mdata.K_W = cmd_leg[leg_id].K_W ;
    cmd_leg[leg_id].motor_send_data.Mdata.LowHzMotorCmdIndex = 0;
    cmd_leg[leg_id].motor_send_data.Mdata.LowHzMotorCmdByte = 0;
    cmd_leg[leg_id].motor_send_data.Mdata.Res[0] = cmd_leg[leg_id].Res;

    cmd_leg[leg_id].motor_send_data.CRCdata.u32 = crc32_core((uint32_t *)(&cmd_leg[leg_id].motor_send_data), 7);

    memcpy(A1cmd, &cmd_leg[leg_id].motor_send_data, 34);

    switch (leg_id)
    {
	case 0:  //LF
		SendData(USART1,A1cmd,34);
        break;
    case 1:  //LB
		SendData(USART3,A1cmd,34);
        break;
    case 2:  //RF
		SendData(USART6,A1cmd,34);
        break;
    case 3:  //RB
        SendData(USART2,A1cmd,34);
        break;
    }
}




//void unitreeA1_rx(int leg_id)
//{
//    uint8_t usart6RxBuffer[78];
//	//HAL_UART_Receive_DMA(&huart1, usart6RxBuffer, 78);
//   
//    data_leg[leg_id].motor_recv_data.head.motorID = usart6RxBuffer[2];
//    data_leg[leg_id].motor_recv_data.Mdata.MError = usart6RxBuffer[7];
//    data_leg[leg_id].motor_recv_data.Mdata.T = usart6RxBuffer[12] << 8 | usart6RxBuffer[13];
//    data_leg[leg_id].motor_recv_data.Mdata.Pos = usart6RxBuffer[30] << 24 | usart6RxBuffer[31] << 16 | usart6RxBuffer[32] << 8 | usart6RxBuffer[33];

//    data_leg[leg_id].motor_id = data_leg[leg_id].motor_recv_data.head.motorID;
//    data_leg[leg_id].MError = data_leg[leg_id].motor_recv_data.Mdata.MError;
//    data_leg[leg_id].T = data_leg[leg_id].motor_recv_data.Mdata.T / 256;
//    data_leg[leg_id].W = data_leg[leg_id].motor_recv_data.Mdata.W / 128;
//    data_leg[leg_id].Acc = data_leg[leg_id].motor_recv_data.Mdata.Acc;
//    data_leg[leg_id].Pos = (int)((data_leg[leg_id].motor_recv_data.Mdata.Pos / 16384.0f) * 6.2832f);

//    data_motor[leg_id][data_leg[leg_id].motor_id].motor_id = data_leg[leg_id].motor_id;
//    data_motor[leg_id][data_leg[leg_id].motor_id].MError = data_leg[leg_id].MError;
//    data_motor[leg_id][data_leg[leg_id].motor_id].T = data_leg[leg_id].T;
//    data_motor[leg_id][data_leg[leg_id].motor_id].Pos = data_leg[leg_id].Pos;
//}



// CRC校验位的代码
uint32_t crc32_core(uint32_t *ptr, uint32_t len)
{
    uint32_t bits;
    uint32_t i;
    uint32_t xbit = 0;
    uint32_t data = 0;
    uint32_t CRC32 = 0xFFFFFFFF;
    const uint32_t dwPolynomial = 0x04c11db7;
    for (i = 0; i < len; i++)
    {
        xbit = 1 << 31;
        data = ptr[i];
        for (bits = 0; bits < 32; bits++)
        {
            if (CRC32 & 0x80000000)
            {
                CRC32 <<= 1;
                CRC32 ^= dwPolynomial;
            }
            else
                CRC32 <<= 1;
            if (data & xbit)
                CRC32 ^= dwPolynomial;

            xbit >>= 1;
        }
    }
    return CRC32;
}

