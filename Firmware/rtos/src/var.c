#include "stm32f10x_conf.h"
#include "var.h"

/****************************************
 *  Variables
 ***************************************/
__IO uint8_t ReadDataByte[READ_DATA_LENGHT];
__IO uint8_t systemMsgArray[ARRAY_LENGHT];
__IO uint8_t Msg_1_Array[ARRAY_LENGHT];
__IO uint8_t Msg_2_Array[ARRAY_LENGHT];
__IO uint8_t Msg_3_Array[ARRAY_LENGHT];
__IO uint8_t Msg_4_Array[ARRAY_LENGHT];
__IO uint8_t Msg_5_Array[ARRAY_LENGHT];
__IO uint8_t Msg_6_Array[ARRAY_LENGHT];
__IO uint8_t Msg_7_Array[ARRAY_LENGHT];
__IO uint8_t Msg_8_Array[ARRAY_LENGHT];

__IO uint8_t RxFlag = 0;
