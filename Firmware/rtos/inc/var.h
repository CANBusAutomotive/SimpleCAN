#ifndef VAR_H
#define VAR_H
/*****************************************
 *  Defines
 ****************************************/
#define ApplicationAddress      0x08008000

#define ADDRESS                 0x0800C000                                    // адрес начала страници флэш
#define ADDRESS_MSG_SYSTEM      0x0800C000
#define ADDRESS_MSG_1           (ADDRESS_MSG_SYSTEM+0x40)
#define ADDRESS_MSG_2           (ADDRESS_MSG_SYSTEM+(0x40*2))
#define ADDRESS_MSG_3           (ADDRESS_MSG_SYSTEM+(0x40*3))
#define ADDRESS_MSG_4           (ADDRESS_MSG_SYSTEM+(0x40*4))
#define ADDRESS_MSG_5           (ADDRESS_MSG_SYSTEM+(0x40*5))
#define ADDRESS_MSG_6           (ADDRESS_MSG_SYSTEM+(0x40*6))
#define ADDRESS_MSG_7           (ADDRESS_MSG_SYSTEM+(0x40*7))
#define ADDRESS_MSG_8           (ADDRESS_MSG_SYSTEM+(0x40*8))

#define READ_DATA_LENGHT         640                                            // Array for read data

#define ARRAY_LENGHT             0x40

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

__IO uint8_t RxFlag;                                //Flag  indicates the presence of CAN message

#endif
