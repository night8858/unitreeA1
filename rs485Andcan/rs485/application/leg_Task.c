#include "unitreeA1_cmd.h"
#include "usart.h"

void UnitreeA1_Task(void const * argument)
{
	while(1)
	{
	modfiy_cmd(&cmd_left,2,0.0,0,0);
	unitreeA1_rxtx(&huart1);
//	HAL_Delay(100);
//	modfiy_cmd(&cmd_left,1,0,0.1,1);
//	unitreeA1_rxtx(&huart1);
//	HAL_Delay(100);
//	modfiy_cmd(&cmd_left,2,0.00,0.1,1);
//	unitreeA1_rxtx(&huart1);
//	HAL_Delay(100);
	}
}

