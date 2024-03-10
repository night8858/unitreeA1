#ifndef BSP_RC_IT_H
#define BSP_RC_IT_H

#define SBUS_RX_BUF_NUM 128u  //实际接收128位数据

#define RC_FRAME_LENGTH 78u   //目标接收78数据

typedef __packed struct
{
    uint8_t motorID;
	uint8_t MError;
	uint16_t T;
	uint16_t W;
	uint32_t Pos;

} A1_buf;

void remote_control_init(void);

void unitreeA1_rx(int leg_id);
static void sbus_to_rc(volatile const uint8_t *sbus_buf, A1_buf *a1_buf);
const A1_buf *get_remote_control_point(void);


#endif
