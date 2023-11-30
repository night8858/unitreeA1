#ifndef __BMI088_RX_H
#define __BMI088_RX_H

typedef struct
{
    float Yaw;
    float Pitch;
    float Roll;
    float Encoder;

}BMI088_Rx_data_t;

extern BMI088_Rx_data_t right_up_088;
extern BMI088_Rx_data_t left_up_088;
extern BMI088_Rx_data_t left_down_088;
extern BMI088_Rx_data_t right_down_088;

#endif
