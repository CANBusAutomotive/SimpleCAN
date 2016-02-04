#include "stm32f10x_conf.h"
#include "var.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "CAN.h"

/********************************************//**
 * \brief Инициализация CAN
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
void CAN_Seting(void)
{
	uint16_t prescaler = 0;
	switch (systemMsgArray[10]) {
	case 0x00:
		prescaler=3; // 1000kb
		break;
	case 0x01:
		prescaler=6; // 500kb
		break;
	case 0x02:
		prescaler=12; // 250kb
		break;
	case 0x03:
		prescaler=24; // 125kb
		break;
	case 0x04:
		prescaler=30; // 100kb
		break;
	case 0x05:
		prescaler=36; // 83.33kb
		break;
	case 0x06:
		prescaler=60; // 50kb
		break;
	case 0x07:
		prescaler=150; // 20kb
		break;
	case 0x08:
		prescaler=300; // 10kb
		break;
	}

	CAN_InitTypeDef CAN_Set;

	CAN_Set.CAN_Prescaler = prescaler;  //500kbps  :3-1000k  6-500k  12-250k  24-125k  30-100k  36-83.33k  60-50k  150-20k  300-10k
	CAN_Set.CAN_Mode = CAN_Mode_Normal;
	CAN_Set.CAN_SJW = CAN_SJW_1tq;
	CAN_Set.CAN_BS1 = CAN_BS1_8tq;
	CAN_Set.CAN_BS2 = CAN_BS2_3tq;
	CAN_Set.CAN_TTCM = DISABLE;
	CAN_Set.CAN_ABOM = DISABLE;
	CAN_Set.CAN_AWUM = DISABLE;
	CAN_Set.CAN_NART = DISABLE;
	CAN_Set.CAN_RFLM = DISABLE;
	CAN_Set.CAN_TXFP = ENABLE;
	CAN_Init(CAN1, &CAN_Set);

	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);

	NVIC_InitTypeDef      NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = USB_LP_CAN1_RX0_IRQn;//|USB_HP_CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY - 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/********************************************//**
 * \brief Инициализация Filter
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
void Filtr_init(void)
{
	CAN_FilterInitTypeDef filterInit;
	filterInit.CAN_FilterIdHigh             = 0x0000; /*All message*/
	filterInit.CAN_FilterIdLow              = 0x0000;
	filterInit.CAN_FilterMaskIdHigh         = 0x0000; /*All message*/
	filterInit.CAN_FilterMaskIdLow          = 0x0000;
	filterInit.CAN_FilterFIFOAssignment     = 0;
	filterInit.CAN_FilterNumber             = 0;
	filterInit.CAN_FilterMode               = CAN_FilterMode_IdMask;
	filterInit.CAN_FilterScale              = CAN_FilterScale_32bit;
	filterInit.CAN_FilterActivation         = ENABLE;
	CAN_FilterInit(&filterInit);
}
/**< Формируем CAN сообщение 1 **********************************************/
void CAN_TxMSG1(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_1_Array);
	msg.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_1_Array[1];
	msg.Data[0] = Msg_1_Array[6];
	msg.Data[1] = Msg_1_Array[7];
	msg.Data[2] = Msg_1_Array[8];
	msg.Data[3] = Msg_1_Array[9];
	msg.Data[4] = Msg_1_Array[10];
	msg.Data[5] = Msg_1_Array[11];
	msg.Data[6] = Msg_1_Array[12];
	msg.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_1_Array[16];
		msg.Data[1] += Msg_1_Array[17];
		msg.Data[2] += Msg_1_Array[18];
		msg.Data[3] += Msg_1_Array[19];
		msg.Data[4] += Msg_1_Array[20];
		msg.Data[5] += Msg_1_Array[21];
		msg.Data[6] += Msg_1_Array[22];
		msg.Data[7] += Msg_1_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_1_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}

/**< Формируем CAN сообщение 2********************************************* */
void CAN_TxMSG2(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_2_Array);
	msg.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_2_Array[1];
	msg.Data[0] = Msg_2_Array[6];
	msg.Data[1] = Msg_2_Array[7];
	msg.Data[2] = Msg_2_Array[8];
	msg.Data[3] = Msg_2_Array[9];
	msg.Data[4] = Msg_2_Array[10];
	msg.Data[5] = Msg_2_Array[11];
	msg.Data[6] = Msg_2_Array[12];
	msg.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_2_Array[16];
		msg.Data[1] += Msg_2_Array[17];
		msg.Data[2] += Msg_2_Array[18];
		msg.Data[3] += Msg_2_Array[19];
		msg.Data[4] += Msg_2_Array[20];
		msg.Data[5] += Msg_2_Array[21];
		msg.Data[6] += Msg_2_Array[22];
		msg.Data[7] += Msg_2_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_2_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Формируем CAN сообщение 3********************************************* */
void CAN_TxMSG3(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_3_Array);
	msg.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_3_Array[1];
	msg.Data[0] = Msg_3_Array[6];
	msg.Data[1] = Msg_3_Array[7];
	msg.Data[2] = Msg_3_Array[8];
	msg.Data[3] = Msg_3_Array[9];
	msg.Data[4] = Msg_3_Array[10];
	msg.Data[5] = Msg_3_Array[11];
	msg.Data[6] = Msg_3_Array[12];
	msg.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_3_Array[16];
		msg.Data[1] += Msg_3_Array[17];
		msg.Data[2] += Msg_3_Array[18];
		msg.Data[3] += Msg_3_Array[19];
		msg.Data[4] += Msg_3_Array[20];
		msg.Data[5] += Msg_3_Array[21];
		msg.Data[6] += Msg_3_Array[22];
		msg.Data[7] += Msg_3_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_3_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Формируем CAN сообщение 4********************************************* */
void CAN_TxMSG4(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_4_Array);
	msg.ExtId = smallToBig(2,4,Msg_4_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_4_Array[1];
	msg.Data[0] = Msg_4_Array[6];
	msg.Data[1] = Msg_4_Array[7];
	msg.Data[2] = Msg_4_Array[8];
	msg.Data[3] = Msg_4_Array[9];
	msg.Data[4] = Msg_4_Array[10];
	msg.Data[5] = Msg_4_Array[11];
	msg.Data[6] = Msg_4_Array[12];
	msg.Data[7] = Msg_4_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение______________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_4_Array[16];
		msg.Data[1] += Msg_4_Array[17];
		msg.Data[2] += Msg_4_Array[18];
		msg.Data[3] += Msg_4_Array[19];
		msg.Data[4] += Msg_4_Array[20];
		msg.Data[5] += Msg_4_Array[21];
		msg.Data[6] += Msg_4_Array[22];
		msg.Data[7] += Msg_4_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_4_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Формируем CAN сообщение 5********************************************* */
void CAN_TxMSG5(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_5_Array);
	msg.ExtId = smallToBig(2,4,Msg_5_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_5_Array[1];
	msg.Data[0] = Msg_5_Array[6];
	msg.Data[1] = Msg_5_Array[7];
	msg.Data[2] = Msg_5_Array[8];
	msg.Data[3] = Msg_5_Array[9];
	msg.Data[4] = Msg_5_Array[10];
	msg.Data[5] = Msg_5_Array[11];
	msg.Data[6] = Msg_5_Array[12];
	msg.Data[7] = Msg_5_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_5_Array[16];
		msg.Data[1] += Msg_5_Array[17];
		msg.Data[2] += Msg_5_Array[18];
		msg.Data[3] += Msg_5_Array[19];
		msg.Data[4] += Msg_5_Array[20];
		msg.Data[5] += Msg_5_Array[21];
		msg.Data[6] += Msg_5_Array[22];
		msg.Data[7] += Msg_5_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_5_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Формируем CAN сообщение 6********************************************* */
void CAN_TxMSG6(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_6_Array);
	msg.ExtId = smallToBig(2,4,Msg_6_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_6_Array[1];
	msg.Data[0] = Msg_6_Array[6];
	msg.Data[1] = Msg_6_Array[7];
	msg.Data[2] = Msg_6_Array[8];
	msg.Data[3] = Msg_6_Array[9];
	msg.Data[4] = Msg_6_Array[10];
	msg.Data[5] = Msg_6_Array[11];
	msg.Data[6] = Msg_6_Array[12];
	msg.Data[7] = Msg_6_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_6_Array[16];
		msg.Data[1] += Msg_6_Array[17];
		msg.Data[2] += Msg_6_Array[18];
		msg.Data[3] += Msg_6_Array[19];
		msg.Data[4] += Msg_6_Array[20];
		msg.Data[5] += Msg_6_Array[21];
		msg.Data[6] += Msg_6_Array[22];
		msg.Data[7] += Msg_6_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_6_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Формируем CAN сообщение 7********************************************* */
void CAN_TxMSG7(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_7_Array);
	msg.ExtId = smallToBig(2,4,Msg_7_Array);
	if (systemMsgArray[9] == 0x0) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_7_Array[1];
	msg.Data[0] = Msg_7_Array[6];
	msg.Data[1] = Msg_7_Array[7];
	msg.Data[2] = Msg_7_Array[8];
	msg.Data[3] = Msg_7_Array[9];
	msg.Data[4] = Msg_7_Array[10];
	msg.Data[5] = Msg_7_Array[11];
	msg.Data[6] = Msg_7_Array[12];
	msg.Data[7] = Msg_7_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_7_Array[16];
		msg.Data[1] += Msg_7_Array[17];
		msg.Data[2] += Msg_7_Array[18];
		msg.Data[3] += Msg_7_Array[19];
		msg.Data[4] += Msg_7_Array[20];
		msg.Data[5] += Msg_7_Array[21];
		msg.Data[6] += Msg_7_Array[22];
		msg.Data[7] += Msg_7_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_7_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Формируем CAN сообщение 8********************************************* */
void CAN_TxMSG8(void* pvParameters)
{
	CanTxMsg msg;
	msg.StdId = smallToBig(2,4,Msg_8_Array);
	msg.ExtId = smallToBig(2,4,Msg_8_Array);
	if (systemMsgArray[9] == 0x00) {
		msg.IDE = CAN_ID_STD;
	} else {
		msg.IDE = CAN_ID_EXT;
	}
	msg.RTR = CAN_RTR_DATA;
	msg.DLC =     Msg_8_Array[1];
	msg.Data[0] = Msg_8_Array[6];
	msg.Data[1] = Msg_8_Array[7];
	msg.Data[2] = Msg_8_Array[8];
	msg.Data[3] = Msg_8_Array[9];
	msg.Data[4] = Msg_8_Array[10];
	msg.Data[5] = Msg_8_Array[11];
	msg.Data[6] = Msg_8_Array[12];
	msg.Data[7] = Msg_8_Array[13];
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1) {
		//________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg.Data[0] += Msg_8_Array[16];
		msg.Data[1] += Msg_8_Array[17];
		msg.Data[2] += Msg_8_Array[18];
		msg.Data[3] += Msg_8_Array[19];
		msg.Data[4] += Msg_8_Array[20];
		msg.Data[5] += Msg_8_Array[21];
		msg.Data[6] += Msg_8_Array[22];
		msg.Data[7] += Msg_8_Array[23];
		//_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime, smallToBig(24,2,Msg_8_Array));
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/////////////////////////////////////////////////
/// \brief
/// Формируем цикл для отправки сообщений в одном потоке
/// \param
/// \param
/// \return
////////////////////////////////////////////////////

/**< Для одного сообщения*/
void CAN_TxMSG_InOneThread_1(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
/**< Для двух сообщений*/
void CAN_TxMSG_InOneThread_2(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}


/**< Для трех сообщений*/
void CAN_TxMSG_InOneThread_3(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
	// Третье сообщение
	CanTxMsg msg3;
	msg3.StdId = smallToBig(2,4,Msg_3_Array);
	msg3.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg3.IDE = CAN_ID_STD;
	} else {
		msg3.IDE = CAN_ID_EXT;
	}
	msg3.RTR = CAN_RTR_DATA;
	msg3.DLC =     Msg_3_Array[1];
	msg3.Data[0] = Msg_3_Array[6];
	msg3.Data[1] = Msg_3_Array[7];
	msg3.Data[2] = Msg_3_Array[8];
	msg3.Data[3] = Msg_3_Array[9];
	msg3.Data[4] = Msg_3_Array[10];
	msg3.Data[5] = Msg_3_Array[11];
	msg3.Data[6] = Msg_3_Array[12];
	msg3.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime3;
	xLastWakeTime3 = xTaskGetTickCount();


    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
		       // ----- 3------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_3_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg3);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg3.Data[0] += Msg_3_Array[16];
		msg3.Data[1] += Msg_3_Array[17];
		msg3.Data[2] += Msg_3_Array[18];
		msg3.Data[3] += Msg_3_Array[19];
		msg3.Data[4] += Msg_3_Array[20];
		msg3.Data[5] += Msg_3_Array[21];
		msg3.Data[6] += Msg_3_Array[22];
		msg3.Data[7] += Msg_3_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}

/**< Для четырех сообщений*/
void CAN_TxMSG_InOneThread_4(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
	// Третье сообщение
	CanTxMsg msg3;
	msg3.StdId = smallToBig(2,4,Msg_3_Array);
	msg3.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg3.IDE = CAN_ID_STD;
	} else {
		msg3.IDE = CAN_ID_EXT;
	}
	msg3.RTR = CAN_RTR_DATA;
	msg3.DLC =     Msg_3_Array[1];
	msg3.Data[0] = Msg_3_Array[6];
	msg3.Data[1] = Msg_3_Array[7];
	msg3.Data[2] = Msg_3_Array[8];
	msg3.Data[3] = Msg_3_Array[9];
	msg3.Data[4] = Msg_3_Array[10];
	msg3.Data[5] = Msg_3_Array[11];
	msg3.Data[6] = Msg_3_Array[12];
	msg3.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime3;
	xLastWakeTime3 = xTaskGetTickCount();
    // Четвертое сообщение
	CanTxMsg msg4;
	msg4.StdId = smallToBig(2,4,Msg_4_Array);
	msg4.ExtId = smallToBig(2,4,Msg_4_Array);
	if (systemMsgArray[9] == 0x00) {
		msg4.IDE = CAN_ID_STD;
	} else {
		msg4.IDE = CAN_ID_EXT;
	}
	msg4.RTR = CAN_RTR_DATA;
	msg4.DLC =     Msg_4_Array[1];
	msg4.Data[0] = Msg_4_Array[6];
	msg4.Data[1] = Msg_4_Array[7];
	msg4.Data[2] = Msg_4_Array[8];
	msg4.Data[3] = Msg_4_Array[9];
	msg4.Data[4] = Msg_4_Array[10];
	msg4.Data[5] = Msg_4_Array[11];
	msg4.Data[6] = Msg_4_Array[12];
	msg4.Data[7] = Msg_4_Array[13];

    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
		       // ----- 3------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_3_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg3);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg3.Data[0] += Msg_3_Array[16];
		msg3.Data[1] += Msg_3_Array[17];
		msg3.Data[2] += Msg_3_Array[18];
		msg3.Data[3] += Msg_3_Array[19];
		msg3.Data[4] += Msg_3_Array[20];
		msg3.Data[5] += Msg_3_Array[21];
		msg3.Data[6] += Msg_3_Array[22];
		msg3.Data[7] += Msg_3_Array[23];
                // ----- 4------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_4_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg4);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg4.Data[0] += Msg_4_Array[16];
		msg4.Data[1] += Msg_4_Array[17];
		msg4.Data[2] += Msg_4_Array[18];
		msg4.Data[3] += Msg_4_Array[19];
		msg4.Data[4] += Msg_4_Array[20];
		msg4.Data[5] += Msg_4_Array[21];
		msg4.Data[6] += Msg_4_Array[22];
		msg4.Data[7] += Msg_4_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}

/**< Для пяти сообщений*/
void CAN_TxMSG_InOneThread_5(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
	// Третье сообщение
	CanTxMsg msg3;
	msg3.StdId = smallToBig(2,4,Msg_3_Array);
	msg3.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg3.IDE = CAN_ID_STD;
	} else {
		msg3.IDE = CAN_ID_EXT;
	}
	msg3.RTR = CAN_RTR_DATA;
	msg3.DLC =     Msg_3_Array[1];
	msg3.Data[0] = Msg_3_Array[6];
	msg3.Data[1] = Msg_3_Array[7];
	msg3.Data[2] = Msg_3_Array[8];
	msg3.Data[3] = Msg_3_Array[9];
	msg3.Data[4] = Msg_3_Array[10];
	msg3.Data[5] = Msg_3_Array[11];
	msg3.Data[6] = Msg_3_Array[12];
	msg3.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime3;
	xLastWakeTime3 = xTaskGetTickCount();
    // Четвертое сообщение
	CanTxMsg msg4;
	msg4.StdId = smallToBig(2,4,Msg_4_Array);
	msg4.ExtId = smallToBig(2,4,Msg_4_Array);
	if (systemMsgArray[9] == 0x00) {
		msg4.IDE = CAN_ID_STD;
	} else {
		msg4.IDE = CAN_ID_EXT;
	}
	msg4.RTR = CAN_RTR_DATA;
	msg4.DLC =     Msg_4_Array[1];
	msg4.Data[0] = Msg_4_Array[6];
	msg4.Data[1] = Msg_4_Array[7];
	msg4.Data[2] = Msg_4_Array[8];
	msg4.Data[3] = Msg_4_Array[9];
	msg4.Data[4] = Msg_4_Array[10];
	msg4.Data[5] = Msg_4_Array[11];
	msg4.Data[6] = Msg_4_Array[12];
	msg4.Data[7] = Msg_4_Array[13];
	// Пятое сообщение
	CanTxMsg msg5;
	msg5.StdId = smallToBig(2,4,Msg_5_Array);
	msg5.ExtId = smallToBig(2,4,Msg_5_Array);
	if (systemMsgArray[9] == 0x00) {
		msg5.IDE = CAN_ID_STD;
	} else {
		msg5.IDE = CAN_ID_EXT;
	}
	msg5.RTR = CAN_RTR_DATA;
	msg5.DLC =     Msg_5_Array[1];
	msg5.Data[0] = Msg_5_Array[6];
	msg5.Data[1] = Msg_5_Array[7];
	msg5.Data[2] = Msg_5_Array[8];
	msg5.Data[3] = Msg_5_Array[9];
	msg5.Data[4] = Msg_5_Array[10];
	msg5.Data[5] = Msg_5_Array[11];
	msg5.Data[6] = Msg_5_Array[12];
	msg5.Data[7] = Msg_5_Array[13];

    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
		       // ----- 3------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_3_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg3);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg3.Data[0] += Msg_3_Array[16];
		msg3.Data[1] += Msg_3_Array[17];
		msg3.Data[2] += Msg_3_Array[18];
		msg3.Data[3] += Msg_3_Array[19];
		msg3.Data[4] += Msg_3_Array[20];
		msg3.Data[5] += Msg_3_Array[21];
		msg3.Data[6] += Msg_3_Array[22];
		msg3.Data[7] += Msg_3_Array[23];
                // ----- 4------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_4_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg4);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg4.Data[0] += Msg_4_Array[16];
		msg4.Data[1] += Msg_4_Array[17];
		msg4.Data[2] += Msg_4_Array[18];
		msg4.Data[3] += Msg_4_Array[19];
		msg4.Data[4] += Msg_4_Array[20];
		msg4.Data[5] += Msg_4_Array[21];
		msg4.Data[6] += Msg_4_Array[22];
		msg4.Data[7] += Msg_4_Array[23];
                // ----- 5------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_5_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg5);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg5.Data[0] += Msg_5_Array[16];
		msg5.Data[1] += Msg_5_Array[17];
		msg5.Data[2] += Msg_5_Array[18];
		msg5.Data[3] += Msg_5_Array[19];
		msg5.Data[4] += Msg_5_Array[20];
		msg5.Data[5] += Msg_5_Array[21];
		msg5.Data[6] += Msg_5_Array[22];
		msg5.Data[7] += Msg_5_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}

/**< Для шести сообщений*/
void CAN_TxMSG_InOneThread_6(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
	// Третье сообщение
	CanTxMsg msg3;
	msg3.StdId = smallToBig(2,4,Msg_3_Array);
	msg3.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg3.IDE = CAN_ID_STD;
	} else {
		msg3.IDE = CAN_ID_EXT;
	}
	msg3.RTR = CAN_RTR_DATA;
	msg3.DLC =     Msg_3_Array[1];
	msg3.Data[0] = Msg_3_Array[6];
	msg3.Data[1] = Msg_3_Array[7];
	msg3.Data[2] = Msg_3_Array[8];
	msg3.Data[3] = Msg_3_Array[9];
	msg3.Data[4] = Msg_3_Array[10];
	msg3.Data[5] = Msg_3_Array[11];
	msg3.Data[6] = Msg_3_Array[12];
	msg3.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime3;
	xLastWakeTime3 = xTaskGetTickCount();
    // Четвертое сообщение
	CanTxMsg msg4;
	msg4.StdId = smallToBig(2,4,Msg_4_Array);
	msg4.ExtId = smallToBig(2,4,Msg_4_Array);
	if (systemMsgArray[9] == 0x00) {
		msg4.IDE = CAN_ID_STD;
	} else {
		msg4.IDE = CAN_ID_EXT;
	}
	msg4.RTR = CAN_RTR_DATA;
	msg4.DLC =     Msg_4_Array[1];
	msg4.Data[0] = Msg_4_Array[6];
	msg4.Data[1] = Msg_4_Array[7];
	msg4.Data[2] = Msg_4_Array[8];
	msg4.Data[3] = Msg_4_Array[9];
	msg4.Data[4] = Msg_4_Array[10];
	msg4.Data[5] = Msg_4_Array[11];
	msg4.Data[6] = Msg_4_Array[12];
	msg4.Data[7] = Msg_4_Array[13];
	// Пятое сообщение
	CanTxMsg msg5;
	msg5.StdId = smallToBig(2,4,Msg_5_Array);
	msg5.ExtId = smallToBig(2,4,Msg_5_Array);
	if (systemMsgArray[9] == 0x00) {
		msg5.IDE = CAN_ID_STD;
	} else {
		msg5.IDE = CAN_ID_EXT;
	}
	msg5.RTR = CAN_RTR_DATA;
	msg5.DLC =     Msg_5_Array[1];
	msg5.Data[0] = Msg_5_Array[6];
	msg5.Data[1] = Msg_5_Array[7];
	msg5.Data[2] = Msg_5_Array[8];
	msg5.Data[3] = Msg_5_Array[9];
	msg5.Data[4] = Msg_5_Array[10];
	msg5.Data[5] = Msg_5_Array[11];
	msg5.Data[6] = Msg_5_Array[12];
	msg5.Data[7] = Msg_5_Array[13];
	// Шестое сообщение
	CanTxMsg msg6;
	msg6.StdId = smallToBig(2,4,Msg_6_Array);
	msg6.ExtId = smallToBig(2,4,Msg_6_Array);
	if (systemMsgArray[9] == 0x00) {
		msg6.IDE = CAN_ID_STD;
	} else {
		msg6.IDE = CAN_ID_EXT;
	}
	msg6.RTR = CAN_RTR_DATA;
	msg6.DLC =     Msg_6_Array[1];
	msg6.Data[0] = Msg_6_Array[6];
	msg6.Data[1] = Msg_6_Array[7];
	msg6.Data[2] = Msg_6_Array[8];
	msg6.Data[3] = Msg_6_Array[9];
	msg6.Data[4] = Msg_6_Array[10];
	msg6.Data[5] = Msg_6_Array[11];
	msg6.Data[6] = Msg_6_Array[12];
	msg6.Data[7] = Msg_6_Array[13];

    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
		       // ----- 3------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_3_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg3);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg3.Data[0] += Msg_3_Array[16];
		msg3.Data[1] += Msg_3_Array[17];
		msg3.Data[2] += Msg_3_Array[18];
		msg3.Data[3] += Msg_3_Array[19];
		msg3.Data[4] += Msg_3_Array[20];
		msg3.Data[5] += Msg_3_Array[21];
		msg3.Data[6] += Msg_3_Array[22];
		msg3.Data[7] += Msg_3_Array[23];
                // ----- 4------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_4_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg4);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg4.Data[0] += Msg_4_Array[16];
		msg4.Data[1] += Msg_4_Array[17];
		msg4.Data[2] += Msg_4_Array[18];
		msg4.Data[3] += Msg_4_Array[19];
		msg4.Data[4] += Msg_4_Array[20];
		msg4.Data[5] += Msg_4_Array[21];
		msg4.Data[6] += Msg_4_Array[22];
		msg4.Data[7] += Msg_4_Array[23];
                // ----- 5------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_5_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg5);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg5.Data[0] += Msg_5_Array[16];
		msg5.Data[1] += Msg_5_Array[17];
		msg5.Data[2] += Msg_5_Array[18];
		msg5.Data[3] += Msg_5_Array[19];
		msg5.Data[4] += Msg_5_Array[20];
		msg5.Data[5] += Msg_5_Array[21];
		msg5.Data[6] += Msg_5_Array[22];
		msg5.Data[7] += Msg_5_Array[23];
                // ----- 6------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_6_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg6);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg6.Data[0] += Msg_6_Array[16];
		msg6.Data[1] += Msg_6_Array[17];
		msg6.Data[2] += Msg_6_Array[18];
		msg6.Data[3] += Msg_6_Array[19];
		msg6.Data[4] += Msg_6_Array[20];
		msg6.Data[5] += Msg_6_Array[21];
		msg6.Data[6] += Msg_6_Array[22];
		msg6.Data[7] += Msg_6_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}

/**< Для семи сообщений*/
void CAN_TxMSG_InOneThread_7(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
	// Третье сообщение
	CanTxMsg msg3;
	msg3.StdId = smallToBig(2,4,Msg_3_Array);
	msg3.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg3.IDE = CAN_ID_STD;
	} else {
		msg3.IDE = CAN_ID_EXT;
	}
	msg3.RTR = CAN_RTR_DATA;
	msg3.DLC =     Msg_3_Array[1];
	msg3.Data[0] = Msg_3_Array[6];
	msg3.Data[1] = Msg_3_Array[7];
	msg3.Data[2] = Msg_3_Array[8];
	msg3.Data[3] = Msg_3_Array[9];
	msg3.Data[4] = Msg_3_Array[10];
	msg3.Data[5] = Msg_3_Array[11];
	msg3.Data[6] = Msg_3_Array[12];
	msg3.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime3;
	xLastWakeTime3 = xTaskGetTickCount();
    // Четвертое сообщение
	CanTxMsg msg4;
	msg4.StdId = smallToBig(2,4,Msg_4_Array);
	msg4.ExtId = smallToBig(2,4,Msg_4_Array);
	if (systemMsgArray[9] == 0x00) {
		msg4.IDE = CAN_ID_STD;
	} else {
		msg4.IDE = CAN_ID_EXT;
	}
	msg4.RTR = CAN_RTR_DATA;
	msg4.DLC =     Msg_4_Array[1];
	msg4.Data[0] = Msg_4_Array[6];
	msg4.Data[1] = Msg_4_Array[7];
	msg4.Data[2] = Msg_4_Array[8];
	msg4.Data[3] = Msg_4_Array[9];
	msg4.Data[4] = Msg_4_Array[10];
	msg4.Data[5] = Msg_4_Array[11];
	msg4.Data[6] = Msg_4_Array[12];
	msg4.Data[7] = Msg_4_Array[13];
	// Пятое сообщение
	CanTxMsg msg5;
	msg5.StdId = smallToBig(2,4,Msg_5_Array);
	msg5.ExtId = smallToBig(2,4,Msg_5_Array);
	if (systemMsgArray[9] == 0x00) {
		msg5.IDE = CAN_ID_STD;
	} else {
		msg5.IDE = CAN_ID_EXT;
	}
	msg5.RTR = CAN_RTR_DATA;
	msg5.DLC =     Msg_5_Array[1];
	msg5.Data[0] = Msg_5_Array[6];
	msg5.Data[1] = Msg_5_Array[7];
	msg5.Data[2] = Msg_5_Array[8];
	msg5.Data[3] = Msg_5_Array[9];
	msg5.Data[4] = Msg_5_Array[10];
	msg5.Data[5] = Msg_5_Array[11];
	msg5.Data[6] = Msg_5_Array[12];
	msg5.Data[7] = Msg_5_Array[13];
	// Шестое сообщение
	CanTxMsg msg6;
	msg6.StdId = smallToBig(2,4,Msg_6_Array);
	msg6.ExtId = smallToBig(2,4,Msg_6_Array);
	if (systemMsgArray[9] == 0x00) {
		msg6.IDE = CAN_ID_STD;
	} else {
		msg6.IDE = CAN_ID_EXT;
	}
	msg6.RTR = CAN_RTR_DATA;
	msg6.DLC =     Msg_6_Array[1];
	msg6.Data[0] = Msg_6_Array[6];
	msg6.Data[1] = Msg_6_Array[7];
	msg6.Data[2] = Msg_6_Array[8];
	msg6.Data[3] = Msg_6_Array[9];
	msg6.Data[4] = Msg_6_Array[10];
	msg6.Data[5] = Msg_6_Array[11];
	msg6.Data[6] = Msg_6_Array[12];
	msg6.Data[7] = Msg_6_Array[13];
	// Седьмое сообщение
	CanTxMsg msg7;
	msg7.StdId = smallToBig(2,4,Msg_7_Array);
	msg7.ExtId = smallToBig(2,4,Msg_7_Array);
	if (systemMsgArray[9] == 0x00) {
		msg7.IDE = CAN_ID_STD;
	} else {
		msg7.IDE = CAN_ID_EXT;
	}
	msg7.RTR = CAN_RTR_DATA;
	msg7.DLC =     Msg_7_Array[1];
	msg7.Data[0] = Msg_7_Array[6];
	msg7.Data[1] = Msg_7_Array[7];
	msg7.Data[2] = Msg_7_Array[8];
	msg7.Data[3] = Msg_7_Array[9];
	msg7.Data[4] = Msg_7_Array[10];
	msg7.Data[5] = Msg_7_Array[11];
	msg7.Data[6] = Msg_7_Array[12];
	msg7.Data[7] = Msg_7_Array[13];

    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
		       // ----- 3------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_3_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg3);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg3.Data[0] += Msg_3_Array[16];
		msg3.Data[1] += Msg_3_Array[17];
		msg3.Data[2] += Msg_3_Array[18];
		msg3.Data[3] += Msg_3_Array[19];
		msg3.Data[4] += Msg_3_Array[20];
		msg3.Data[5] += Msg_3_Array[21];
		msg3.Data[6] += Msg_3_Array[22];
		msg3.Data[7] += Msg_3_Array[23];
                // ----- 4------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_4_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg4);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg4.Data[0] += Msg_4_Array[16];
		msg4.Data[1] += Msg_4_Array[17];
		msg4.Data[2] += Msg_4_Array[18];
		msg4.Data[3] += Msg_4_Array[19];
		msg4.Data[4] += Msg_4_Array[20];
		msg4.Data[5] += Msg_4_Array[21];
		msg4.Data[6] += Msg_4_Array[22];
		msg4.Data[7] += Msg_4_Array[23];
                // ----- 5------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_5_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg5);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg5.Data[0] += Msg_5_Array[16];
		msg5.Data[1] += Msg_5_Array[17];
		msg5.Data[2] += Msg_5_Array[18];
		msg5.Data[3] += Msg_5_Array[19];
		msg5.Data[4] += Msg_5_Array[20];
		msg5.Data[5] += Msg_5_Array[21];
		msg5.Data[6] += Msg_5_Array[22];
		msg5.Data[7] += Msg_5_Array[23];
                // ----- 6------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_6_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg6);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg6.Data[0] += Msg_6_Array[16];
		msg6.Data[1] += Msg_6_Array[17];
		msg6.Data[2] += Msg_6_Array[18];
		msg6.Data[3] += Msg_6_Array[19];
		msg6.Data[4] += Msg_6_Array[20];
		msg6.Data[5] += Msg_6_Array[21];
		msg6.Data[6] += Msg_6_Array[22];
		msg6.Data[7] += Msg_6_Array[23];
                // ----- 7------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_7_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg7);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg7.Data[0] += Msg_7_Array[16];
		msg7.Data[1] += Msg_7_Array[17];
		msg7.Data[2] += Msg_7_Array[18];
		msg7.Data[3] += Msg_7_Array[19];
		msg7.Data[4] += Msg_7_Array[20];
		msg7.Data[5] += Msg_7_Array[21];
		msg7.Data[6] += Msg_7_Array[22];
		msg7.Data[7] += Msg_7_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}

/**< Для восьми сообщений*/
void CAN_TxMSG_InOneThread_8(void* pvParameters)
{
    // Первое сообщение
	CanTxMsg msg1;
	msg1.StdId = smallToBig(2,4,Msg_1_Array);
	msg1.ExtId = smallToBig(2,4,Msg_1_Array);
	if (systemMsgArray[9] == 0x00) {
		msg1.IDE = CAN_ID_STD;
	} else {
		msg1.IDE = CAN_ID_EXT;
	}
	msg1.RTR = CAN_RTR_DATA;
	msg1.DLC =     Msg_1_Array[1];
	msg1.Data[0] = Msg_1_Array[6];
	msg1.Data[1] = Msg_1_Array[7];
	msg1.Data[2] = Msg_1_Array[8];
	msg1.Data[3] = Msg_1_Array[9];
	msg1.Data[4] = Msg_1_Array[10];
	msg1.Data[5] = Msg_1_Array[11];
	msg1.Data[6] = Msg_1_Array[12];
	msg1.Data[7] = Msg_1_Array[13];
	portTickType xLastWakeTime1;
	xLastWakeTime1 = xTaskGetTickCount();
	// Второе сообщение
	CanTxMsg msg2;
	msg2.StdId = smallToBig(2,4,Msg_2_Array);
	msg2.ExtId = smallToBig(2,4,Msg_2_Array);
	if (systemMsgArray[9] == 0x00) {
		msg2.IDE = CAN_ID_STD;
	} else {
		msg2.IDE = CAN_ID_EXT;
	}
	msg2.RTR = CAN_RTR_DATA;
	msg2.DLC =     Msg_2_Array[1];
	msg2.Data[0] = Msg_2_Array[6];
	msg2.Data[1] = Msg_2_Array[7];
	msg2.Data[2] = Msg_2_Array[8];
	msg2.Data[3] = Msg_2_Array[9];
	msg2.Data[4] = Msg_2_Array[10];
	msg2.Data[5] = Msg_2_Array[11];
	msg2.Data[6] = Msg_2_Array[12];
	msg2.Data[7] = Msg_2_Array[13];
	portTickType xLastWakeTime2;
	xLastWakeTime2 = xTaskGetTickCount();
	// Третье сообщение
	CanTxMsg msg3;
	msg3.StdId = smallToBig(2,4,Msg_3_Array);
	msg3.ExtId = smallToBig(2,4,Msg_3_Array);
	if (systemMsgArray[9] == 0x00) {
		msg3.IDE = CAN_ID_STD;
	} else {
		msg3.IDE = CAN_ID_EXT;
	}
	msg3.RTR = CAN_RTR_DATA;
	msg3.DLC =     Msg_3_Array[1];
	msg3.Data[0] = Msg_3_Array[6];
	msg3.Data[1] = Msg_3_Array[7];
	msg3.Data[2] = Msg_3_Array[8];
	msg3.Data[3] = Msg_3_Array[9];
	msg3.Data[4] = Msg_3_Array[10];
	msg3.Data[5] = Msg_3_Array[11];
	msg3.Data[6] = Msg_3_Array[12];
	msg3.Data[7] = Msg_3_Array[13];
	portTickType xLastWakeTime3;
	xLastWakeTime3 = xTaskGetTickCount();
    // Четвертое сообщение
	CanTxMsg msg4;
	msg4.StdId = smallToBig(2,4,Msg_4_Array);
	msg4.ExtId = smallToBig(2,4,Msg_4_Array);
	if (systemMsgArray[9] == 0x00) {
		msg4.IDE = CAN_ID_STD;
	} else {
		msg4.IDE = CAN_ID_EXT;
	}
	msg4.RTR = CAN_RTR_DATA;
	msg4.DLC =     Msg_4_Array[1];
	msg4.Data[0] = Msg_4_Array[6];
	msg4.Data[1] = Msg_4_Array[7];
	msg4.Data[2] = Msg_4_Array[8];
	msg4.Data[3] = Msg_4_Array[9];
	msg4.Data[4] = Msg_4_Array[10];
	msg4.Data[5] = Msg_4_Array[11];
	msg4.Data[6] = Msg_4_Array[12];
	msg4.Data[7] = Msg_4_Array[13];
	// Пятое сообщение
	CanTxMsg msg5;
	msg5.StdId = smallToBig(2,4,Msg_5_Array);
	msg5.ExtId = smallToBig(2,4,Msg_5_Array);
	if (systemMsgArray[9] == 0x00) {
		msg5.IDE = CAN_ID_STD;
	} else {
		msg5.IDE = CAN_ID_EXT;
	}
	msg5.RTR = CAN_RTR_DATA;
	msg5.DLC =     Msg_5_Array[1];
	msg5.Data[0] = Msg_5_Array[6];
	msg5.Data[1] = Msg_5_Array[7];
	msg5.Data[2] = Msg_5_Array[8];
	msg5.Data[3] = Msg_5_Array[9];
	msg5.Data[4] = Msg_5_Array[10];
	msg5.Data[5] = Msg_5_Array[11];
	msg5.Data[6] = Msg_5_Array[12];
	msg5.Data[7] = Msg_5_Array[13];
	// Шестое сообщение
	CanTxMsg msg6;
	msg6.StdId = smallToBig(2,4,Msg_6_Array);
	msg6.ExtId = smallToBig(2,4,Msg_6_Array);
	if (systemMsgArray[9] == 0x00) {
		msg6.IDE = CAN_ID_STD;
	} else {
		msg6.IDE = CAN_ID_EXT;
	}
	msg6.RTR = CAN_RTR_DATA;
	msg6.DLC =     Msg_6_Array[1];
	msg6.Data[0] = Msg_6_Array[6];
	msg6.Data[1] = Msg_6_Array[7];
	msg6.Data[2] = Msg_6_Array[8];
	msg6.Data[3] = Msg_6_Array[9];
	msg6.Data[4] = Msg_6_Array[10];
	msg6.Data[5] = Msg_6_Array[11];
	msg6.Data[6] = Msg_6_Array[12];
	msg6.Data[7] = Msg_6_Array[13];
	// Седьмое сообщение
	CanTxMsg msg7;
	msg7.StdId = smallToBig(2,4,Msg_7_Array);
	msg7.ExtId = smallToBig(2,4,Msg_7_Array);
	if (systemMsgArray[9] == 0x00) {
		msg7.IDE = CAN_ID_STD;
	} else {
		msg7.IDE = CAN_ID_EXT;
	}
	msg7.RTR = CAN_RTR_DATA;
	msg7.DLC =     Msg_7_Array[1];
	msg7.Data[0] = Msg_7_Array[6];
	msg7.Data[1] = Msg_7_Array[7];
	msg7.Data[2] = Msg_7_Array[8];
	msg7.Data[3] = Msg_7_Array[9];
	msg7.Data[4] = Msg_7_Array[10];
	msg7.Data[5] = Msg_7_Array[11];
	msg7.Data[6] = Msg_7_Array[12];
	msg7.Data[7] = Msg_7_Array[13];
	// Восьмое сообщение
	CanTxMsg msg8;
	msg8.StdId = smallToBig(2,4,Msg_8_Array);
	msg8.ExtId = smallToBig(2,4,Msg_8_Array);
	if (systemMsgArray[9] == 0x00) {
		msg8.IDE = CAN_ID_STD;
	} else {
		msg8.IDE = CAN_ID_EXT;
	}
	msg8.RTR = CAN_RTR_DATA;
	msg8.DLC =     Msg_8_Array[1];
	msg8.Data[0] = Msg_8_Array[6];
	msg8.Data[1] = Msg_8_Array[7];
	msg8.Data[2] = Msg_8_Array[8];
	msg8.Data[3] = Msg_8_Array[9];
	msg8.Data[4] = Msg_8_Array[10];
	msg8.Data[5] = Msg_8_Array[11];
	msg8.Data[6] = Msg_8_Array[12];
	msg8.Data[7] = Msg_8_Array[13];

    while(1) {
                // ----- 1 ------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_1_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg1);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg1.Data[0] += Msg_1_Array[16];
		msg1.Data[1] += Msg_1_Array[17];
		msg1.Data[2] += Msg_1_Array[18];
		msg1.Data[3] += Msg_1_Array[19];
		msg1.Data[4] += Msg_1_Array[20];
		msg1.Data[5] += Msg_1_Array[21];
		msg1.Data[6] += Msg_1_Array[22];
		msg1.Data[7] += Msg_1_Array[23];
                // ----- 2------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_2_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg2);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg2.Data[0] += Msg_2_Array[16];
		msg2.Data[1] += Msg_2_Array[17];
		msg2.Data[2] += Msg_2_Array[18];
		msg2.Data[3] += Msg_2_Array[19];
		msg2.Data[4] += Msg_2_Array[20];
		msg2.Data[5] += Msg_2_Array[21];
		msg2.Data[6] += Msg_2_Array[22];
		msg2.Data[7] += Msg_2_Array[23];
		       // ----- 3------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_3_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg3);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg3.Data[0] += Msg_3_Array[16];
		msg3.Data[1] += Msg_3_Array[17];
		msg3.Data[2] += Msg_3_Array[18];
		msg3.Data[3] += Msg_3_Array[19];
		msg3.Data[4] += Msg_3_Array[20];
		msg3.Data[5] += Msg_3_Array[21];
		msg3.Data[6] += Msg_3_Array[22];
		msg3.Data[7] += Msg_3_Array[23];
                // ----- 4------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_4_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg4);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg4.Data[0] += Msg_4_Array[16];
		msg4.Data[1] += Msg_4_Array[17];
		msg4.Data[2] += Msg_4_Array[18];
		msg4.Data[3] += Msg_4_Array[19];
		msg4.Data[4] += Msg_4_Array[20];
		msg4.Data[5] += Msg_4_Array[21];
		msg4.Data[6] += Msg_4_Array[22];
		msg4.Data[7] += Msg_4_Array[23];
                // ----- 5------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_5_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg5);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg5.Data[0] += Msg_5_Array[16];
		msg5.Data[1] += Msg_5_Array[17];
		msg5.Data[2] += Msg_5_Array[18];
		msg5.Data[3] += Msg_5_Array[19];
		msg5.Data[4] += Msg_5_Array[20];
		msg5.Data[5] += Msg_5_Array[21];
		msg5.Data[6] += Msg_5_Array[22];
		msg5.Data[7] += Msg_5_Array[23];
                // ----- 6------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_6_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg6);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg6.Data[0] += Msg_6_Array[16];
		msg6.Data[1] += Msg_6_Array[17];
		msg6.Data[2] += Msg_6_Array[18];
		msg6.Data[3] += Msg_6_Array[19];
		msg6.Data[4] += Msg_6_Array[20];
		msg6.Data[5] += Msg_6_Array[21];
		msg6.Data[6] += Msg_6_Array[22];
		msg6.Data[7] += Msg_6_Array[23];
                // ----- 7------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_7_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg7);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg7.Data[0] += Msg_7_Array[16];
		msg7.Data[1] += Msg_7_Array[17];
		msg7.Data[2] += Msg_7_Array[18];
		msg7.Data[3] += Msg_7_Array[19];
		msg7.Data[4] += Msg_7_Array[20];
		msg7.Data[5] += Msg_7_Array[21];
		msg7.Data[6] += Msg_7_Array[22];
		msg7.Data[7] += Msg_7_Array[23];
                // ----- 8------
	    //_____Задержка_________________________
		vTaskDelayUntil(&xLastWakeTime1, smallToBig(24,2,Msg_8_Array));
        //________Отправляем сообщение_____________________
		CAN_Transmit(CAN1, &msg8);
		//_______Чистим mail__________________________________
		CAN1 -> RF0R |= CAN_RF0R_RFOM0;
		//_______Заполняем новыми данными___________________
		msg8.Data[0] += Msg_8_Array[16];
		msg8.Data[1] += Msg_8_Array[17];
		msg8.Data[2] += Msg_8_Array[18];
		msg8.Data[3] += Msg_8_Array[19];
		msg8.Data[4] += Msg_8_Array[20];
		msg8.Data[5] += Msg_8_Array[21];
		msg8.Data[6] += Msg_8_Array[22];
		msg8.Data[7] += Msg_8_Array[23];
	}
	//______ЕСли выскочили из бесконечного цикла то удаляем саму себя___________
	vTaskDelete(NULL);
}
