#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "stm32f4xx.h"
#include "can.h"
#include "BMI088_Rx.h"


typedef struct
{
	uint8_t Data[8];
}CAN_Message;

typedef enum
{
  CAN_UPLIFT_M1_ID        = 0x201,  
  CAN_UPLIFT_M2_ID        = 0x202,
  CAN_SLIP_ID             = 0x203,
  CAN_3508_M1_ID           = 0x205,
  CAN_3508_M2_ID           = 0x206,
  CAN_3508_M3_ID           = 0x207,
  CAN_3508_M4_ID           = 0x208,
//  CAN_IMU_ID							 = 0x308,	
 	
} can_msg_id2;

typedef enum
{	
    CAN_PIT_ID               = 0x206,
    CAN_YAW_ID               = 0x205, 		
    CAN_IMU_ID				 = 0x105,
    CAN_FRIC_M1_ID           = 0x203,
    CAN_FRIC_M2_ID           = 0x204,
    CAN_BARRIERS_M1_ID       = 0x201,
    CAN_BARRIERS_M2_ID       = 0x202,
} can_msg_id1;

typedef enum
{
    RIGHT_UP_LEG_ID0 = 0x01,
    RIGHT_UP_LEG_ID1 = 0x02,
    LEFT_UP_LEG_ID0 = 0x03,
    LEFT_UP_LEG_ID1 = 0x04,
    LEFT_DOWN_LEG_ID0 = 0x05,
    LEFT_DOWN_LEG_ID1 = 0x06,
    RIGHT_DOWN_LEG_ID0 = 0x07,
    RIGHT_DOWN_LEG_ID1 = 0x08,

} can_msg_id3;

//陀螺仪数据解算用到
typedef union
{	
	uint8_t c[4];
	float f;
	uint32_t d;
}fchange_t;

typedef struct
{
	float pit_speed;
	float angle_z;
	float yaw_speed;
	float yaw_speed_last;	
	float pit_speed_last;		
}gyro_param;


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern gyro_param  gyro_pitch;


void CAN_InitArgument(void);
void CAN_Enable(CAN_HandleTypeDef *hcan);
void CANFilter_Enable(CAN_HandleTypeDef *hcan);
void CAN_send_current(CAN_HandleTypeDef *hcan,uint32_t id,int16_t motor1, int16_t motor2, int16_t motor3,int16_t motor4);
void CAN_send_data_2(CAN_HandleTypeDef *hcan,uint32_t id,int8_t data1,int8_t data2);
void CAN_send_data_4(CAN_HandleTypeDef *hcan,uint32_t id,int8_t data1,int8_t data2,int8_t data3,int8_t data4);
void gyro_data_handle(fchange_t* ptrr,float* gyro,uint8_t RxData[]);
void BMI088_data_handle(uint8_t RxData[], float* TxData1, float* TxData2);

#endif 
