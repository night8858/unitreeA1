#ifndef __UNITREEA1_CMD__
#define __UNITREEA1_CMD__

#include "motor_msg.h"
//#include "usart.h"

extern motor_send_t cmd_leg[4];
extern motor_recv_t data_leg[4];

extern motor_recv_t data_motor[4][3];

/**
 @brief 对应电机参数修改
 @param send 为cmd_left或cmd_right，分别控制左右侧腿部
 @param id 发送接收目标电机的id
 @param pos  为电机旋转圈数，1为一圈
 @param KP   电机刚度系数
 @param KW   电机速度系数
*/
void modfiy_cmd(motor_send_t *send, uint8_t id, float Pos, float KP, float KW, float W, float T);

void unitreeA1_tx(int leg_id);
void unitreeA1_rx(int leg_id);

uint32_t crc32_core(uint32_t *ptr, uint32_t len);

#endif
