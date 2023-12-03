#include "bsp_can.h"

fchange_t  data4bytes;
gyro_param   	gyro_pitch = {0};

#define TEMP_CONFINE   70


void CAN_InitArgument(void)
{
    CAN_Enable(&hcan1);
    CAN_Enable(&hcan2);
}


void CAN_Enable(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_Start(hcan);//对can进行激活
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);//使能can接收中断
	CANFilter_Enable(hcan);//使能滤波器
}


void CANFilter_Enable(CAN_HandleTypeDef *hcan)
{
	CAN_FilterTypeDef filter1;
	CAN_FilterTypeDef filter2;
	if(hcan->Instance == CAN1)
	{
		filter1.FilterActivation=ENABLE;
		filter1.FilterBank=0U;
		filter1.FilterFIFOAssignment=CAN_FILTER_FIFO0;
		filter1.FilterIdHigh=0x0000;
		filter1.FilterIdLow=0x0000;
		filter1.FilterMaskIdHigh=0x0000;
		filter1.FilterMaskIdLow=0x0000;
		filter1.FilterMode=CAN_FILTERMODE_IDMASK;
		filter1.FilterScale=CAN_FILTERSCALE_32BIT;
		filter1.SlaveStartFilterBank=14;
		
		HAL_CAN_ConfigFilter(&hcan1,&filter1);
	}
	if(hcan->Instance == CAN2)
	{
		filter2.FilterActivation=ENABLE;
		filter2.FilterBank=14;
		filter2.FilterFIFOAssignment=CAN_FILTER_FIFO0;
		filter2.FilterIdHigh=0x0000;
		filter2.FilterIdLow=0x0000;
		filter2.FilterMaskIdHigh=0x0000;
		filter2.FilterMaskIdLow=0x0000;
		filter2.FilterMode=CAN_FILTERMODE_IDMASK;
		filter2.FilterScale=CAN_FILTERSCALE_32BIT;
		filter2.SlaveStartFilterBank=14;
		
		HAL_CAN_ConfigFilter(&hcan2,&filter2);
	}
	
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_Message can1_rx_message,can2_rx_message;
	CAN_RxHeaderTypeDef Can1RxHeader,Can2RxHeader;
	if(hcan->Instance == CAN1)
    {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&Can1RxHeader,can1_rx_message.Data);
        switch (Can1RxHeader.StdId)
        {

        }
	    
    }
	if(hcan->Instance == CAN2)
    {
        HAL_CAN_GetRxMessage(&hcan2,CAN_RX_FIFO0,&Can2RxHeader,can2_rx_message.Data);
        switch (Can2RxHeader.StdId)
        {
            case RIGHT_UP_LEG_ID0:
            {
                BMI088_data_handle(can2_rx_message.Data, &right_up_088.Yaw, &right_up_088.Pitch);
            }
            break;
            case RIGHT_UP_LEG_ID1:
            {
                BMI088_data_handle(can2_rx_message.Data, &right_up_088.Roll, &right_up_088.Encoder);
            }
            break;
            case LEFT_UP_LEG_ID0:
            {
                BMI088_data_handle(can2_rx_message.Data, &left_up_088.Yaw, &left_up_088.Pitch);
            }
            break;
            case LEFT_UP_LEG_ID1:
            {
                BMI088_data_handle(can2_rx_message.Data, &left_up_088.Roll, &left_up_088.Encoder);
            }
            break;
            case LEFT_DOWN_LEG_ID0:
            {
                BMI088_data_handle(can2_rx_message.Data, &left_down_088.Yaw, &left_down_088.Pitch);
            }
            break;
            case LEFT_DOWN_LEG_ID1:
            {
                BMI088_data_handle(can2_rx_message.Data, &left_down_088.Roll, &left_down_088.Encoder);
            }
            break;
            case RIGHT_DOWN_LEG_ID0:
            {
                BMI088_data_handle(can2_rx_message.Data, &right_down_088.Yaw, &right_down_088.Pitch);
            }
            break;
            case RIGHT_DOWN_LEG_ID1:
            {
                BMI088_data_handle(can2_rx_message.Data, &right_down_088.Roll, &right_down_088.Encoder);
            }
            break;
            case 0x09:
            {
                BMI088_data_handle(can2_rx_message.Data, &right_down_088.Roll, &right_down_088.Encoder);
            }
            break;
        }
	  
    }
}

void CAN_send_current(CAN_HandleTypeDef *hcan,uint32_t id,int16_t motor1, int16_t motor2, int16_t motor3,int16_t motor4)
{
    CAN_TxHeaderTypeDef  tx_message;
    uint8_t              can_send_data[8];
    uint32_t send_mail_box;
    tx_message.StdId = id;
    tx_message.IDE = CAN_ID_STD;
    tx_message.RTR = CAN_RTR_DATA;
    tx_message.DLC = 0x08;
    can_send_data[0] = motor1 >> 8;
    can_send_data[1] = motor1;
    can_send_data[2] = motor2 >> 8;
    can_send_data[3] = motor2;
    can_send_data[4] = motor3 >> 8;
    can_send_data[5] = motor3;
    can_send_data[6] = motor4 >> 8;
    can_send_data[7] = motor4;
    
   HAL_CAN_AddTxMessage(hcan, &tx_message, can_send_data, &send_mail_box);
} 

void CAN_send_data_2(CAN_HandleTypeDef *hcan,uint32_t id,int8_t data1,int8_t data2)
{
    CAN_TxHeaderTypeDef  tx_message;
    uint8_t              can_send_data[8];
    uint32_t send_mail_box;
    tx_message.StdId = id;
    tx_message.IDE = CAN_ID_STD;
    tx_message.RTR = CAN_RTR_DATA;
    tx_message.DLC = 0x08;
    can_send_data[0] = data1;
    can_send_data[1] = data2;
    HAL_CAN_AddTxMessage(hcan, &tx_message, can_send_data, &send_mail_box);

}

void CAN_send_data_4(CAN_HandleTypeDef *hcan,uint32_t id,int8_t data1,int8_t data2,int8_t data3,int8_t data4)
{
    CAN_TxHeaderTypeDef  tx_message;
    uint8_t              can_send_data[8];
    uint32_t send_mail_box;
    tx_message.StdId = id;
    tx_message.IDE = CAN_ID_STD;
    tx_message.RTR = CAN_RTR_DATA;
    tx_message.DLC = 0x08;
    can_send_data[0] = data1;
    can_send_data[1] = data2;
    can_send_data[2] = data3;
    can_send_data[3] = data4;
    HAL_CAN_AddTxMessage(hcan, &tx_message, can_send_data, &send_mail_box);

}


/**
  * @brief     get gyro data and unpack the data 
* @param     ptr: Pointer to a wl2data structure  ptrr: Pointer to a wl4data structure
  * @attention this function should be called after gyro is read
  */
void gyro_data_handle(fchange_t* ptrr,float* gyro,uint8_t RxData[])
{
	
    ptrr->c[0] = RxData[0];
    ptrr->c[1] = RxData[1];
    ptrr->c[2] = RxData[2];
    ptrr->c[3] = RxData[3];
    *gyro = ptrr->f;	
}

void BMI088_data_handle(uint8_t RxData[], float* TxData1, float* TxData2)
{
    fchange_t changer1, changer2;
    changer1.c[0] = RxData[0];
    changer1.c[1] = RxData[1];
    changer1.c[2] = RxData[2];
    changer1.c[3] = RxData[3];
    changer2.c[0] = RxData[4];
    changer2.c[1] = RxData[5];
    changer2.c[2] = RxData[6];
    changer2.c[3] = RxData[7];
    *TxData1 = changer1.f;
    *TxData2 = changer2.f;
}
