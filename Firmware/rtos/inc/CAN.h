#ifndef CAN_H
#define CAN_H
/*****************************************
 *  Defines
 ****************************************/

/****************************************
 *  Variables
 ***************************************/

/****************************************
 *  Functions
 ***************************************/
void CAN_Seting(void);
void Filtr_init(void);

void CAN_TxMSG1(void *pvParameters);
void CAN_TxMSG2(void *pvParameters);
void CAN_TxMSG3(void *pvParameters);
void CAN_TxMSG4(void *pvParameters);
void CAN_TxMSG5(void *pvParameters);
void CAN_TxMSG6(void *pvParameters);
void CAN_TxMSG7(void *pvParameters);
void CAN_TxMSG8(void *pvParameters);
void CAN_TxMSG_InOneThread_1(void* pvParameters);
void CAN_TxMSG_InOneThread_2(void* pvParameters);
void CAN_TxMSG_InOneThread_3(void* pvParameters);
void CAN_TxMSG_InOneThread_4(void* pvParameters);
void CAN_TxMSG_InOneThread_5(void* pvParameters);
void CAN_TxMSG_InOneThread_6(void* pvParameters);
void CAN_TxMSG_InOneThread_7(void* pvParameters);
void CAN_TxMSG_InOneThread_8(void* pvParameters);
#endif
