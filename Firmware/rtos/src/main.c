/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 1.00  $
   Last changed by:    $Author: Guddiny $
   Last changed date:  $Date: 12.12.14  $
   ID:                 $Id: XXX $

**********************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "var.h"
#include "CAN.h"

__IO uint32_t multiplier = 0;
/*******************************************************************************
* Function Name  : ReadOutProtection.
* Description    : Delay.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void ReadOutProtection(void)
{
	if (FLASH_GetReadOutProtectionStatus() == RESET) {
		FLASH_Unlock();
		FLASH_ReadOutProtection(ENABLE);
		FLASH_Lock();
	}
}
/*******************************************************************************
* Function Name  : Delay_ms.
* Description    : Delay.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void Delay_ms(uint32_t ms)
{
        volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
		RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
        for (; nCount!=0; nCount--);
}

/*******************************************************************************
* Function Name  : ModeBlink.
* Description    : Delay.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void ModeBlink(void)
{
    uint32_t i = 0;
    uint8_t j = 0;
    for(j =0; j<5; j++)
    {
        GPIO_(GPIOB, GPIO_Pin_2);
        for(i =0; i<200000; i++){}
        GPIO_ResetBits(GPIOB, GPIO_Pin_2);
        for(i =0; i<200000; i++){}
    }
}
/********************************************//**
 * \brief Flash Read
 *
 * \param StartReadAddress value 0x08000000 - 64k
 * \param
 * \return
 * This funktion read flsah in StartReadAddress
 ***********************************************/
void flash_read(uint32_t StartReadAddress)
{
	int i=0;
	for(i=0; i<READ_DATA_LENGHT; i++) {
		ReadDataByte[i]=*(uint16_t*)StartReadAddress;
		StartReadAddress++;
	}
}
/*******************************************************************************
* Function Name  : small to Big.
* Description    : convert any byte to long
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
__IO uint32_t smallToBig(int StartPosition, int QTY, __IO uint8_t* MassData)
{
	int i = 0;
	__IO uint32_t Big = 0x00;
	for(i=0; i<QTY; i++) {
		Big=Big|(*(MassData+StartPosition+i)<<8*i);
	}
	return Big;
}
/********************************************//**
 * \brief read In Array
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
__IO uint8_t readInArray(uint32_t StartAddress, unsigned int arrayLenght, __IO uint8_t* MassData)
{
	int i = 0;
	for(i=0; i<arrayLenght; i++) {
		MassData[i]=*(uint16_t*)StartAddress;
		StartAddress++;
	}
}
/********************************************//**
 * \brief Recive Mesage
 *
 * \param
 * \param
 * \return LED blink
 *
 ***********************************************/
void CAN_RxMSG_control(void* pvParameters)
{
	while(1) {
		if (RxFlag == 1) {
			GPIO_SetBits(GPIOB, GPIO_Pin_2);
			RxFlag = 0;
		} else
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		vTaskDelay(650);
	}
}
/********************************************//**
 * \brief Recive Mesage Interrupt
 *
 * \param
 * \param
 * \return LED blink
 *
 ***********************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	CAN_FIFORelease(CAN1,CAN_FIFO0);
	RxFlag = 1;
}
/********************************************//**
 * \brief Led Blink
 *
 * \param Pin - "PB2"
 * \param
 * \return
 *
 ***********************************************/
void prvLedBlink2( void* pvParameters ) // функция для task
{
	while(1) {
		GPIOB->ODR ^= GPIO_Pin_2;//инвертируем состояние светодиода
		vTaskDelay(80);
	}
}
/********************************************//**
 * \brief Led Blink Error
 *
 * \param Pin - "PB2"
 * \param
 * \return
 *
 ***********************************************/
void prvLedBlinkError( void* pvParameters ) // функция для task
{
	while(1) {
		GPIO_SetBits(GPIOB, GPIO_Pin_2);
		vTaskDelay(300);
		GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		vTaskDelay(80);
	}
}
/********************************************//**
 * \brief Auto reboot
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
void autoReboot( void* pvParameters ) // функция для task
{
	vTaskDelay((smallToBig(13,2, systemMsgArray))*1000);
	__disable_irq();
	NVIC_SystemReset();
}

/********************************************//**
 * \brief Main
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
int main(void)
{
	/*****************************************
	 * Переносим вектор прерываний
	 ****************************************/
	__disable_irq();                                                  // Запрещаем прерывания
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);                  //Адрес таблицы относительно начала Flash
	__enable_irq();
	/*****************************************
	 * Заполняем массивы значениями
	 ****************************************/
	readInArray(ADDRESS_MSG_SYSTEM,ARRAY_LENGHT,systemMsgArray);
	readInArray(ADDRESS_MSG_1,ARRAY_LENGHT,Msg_1_Array);
	readInArray(ADDRESS_MSG_2,ARRAY_LENGHT,Msg_2_Array);
	readInArray(ADDRESS_MSG_3,ARRAY_LENGHT,Msg_3_Array);
	readInArray(ADDRESS_MSG_4,ARRAY_LENGHT,Msg_4_Array);
	readInArray(ADDRESS_MSG_5,ARRAY_LENGHT,Msg_5_Array);
	readInArray(ADDRESS_MSG_6,ARRAY_LENGHT,Msg_6_Array);
	readInArray(ADDRESS_MSG_7,ARRAY_LENGHT,Msg_7_Array);
	readInArray(ADDRESS_MSG_8,ARRAY_LENGHT,Msg_8_Array);
	/*****************************************
	 * Настраивем порты и CAN
	 ****************************************/
	GPIO_Set();
	CAN_Seting();
	Filtr_init();
	Delay_ms(systemMsgArray[15] * 1000);
	//ReadOutProtection();
	/*****************************************
	 * Включаем передачу нужного числа CAN message
	 ****************************************/
	 if(systemMsgArray[12] == 0x01)
			xTaskCreate(autoReboot, "AutoReboot", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

    if ( systemMsgArray[11] == 0x01) // Проверяем, если бит установлен то запускаем адачи в одном патоке
    {

        switch (systemMsgArray[8]) { //systemMsgArray[8]
        case 0x01: /**< Настройка для 1 сообщения */
		xTaskCreate(CAN_TxMSG_InOneThread_1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }
		break;

		case 0x02: /**< Настройка для 2 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;

        case 0x03: /**< Настройка для 3 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;

		case 0x04: /**< Настройка для 4 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_4, "CAN_Msg_4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;

		case 0x05: /**< Настройка для 5 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_5, "CAN_Msg_5", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;

		case 0x06: /**< Настройка для 6 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_6, "CAN_Msg_6", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;

		case 0x07: /**< Настройка для 7 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_7, "CAN_Msg_7", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;

		case 0x08: /**< Настройка для 8 сообщений */
		xTaskCreate(CAN_TxMSG_InOneThread_7, "CAN_Msg_8", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
        }
    }else
    {
	switch (systemMsgArray[8]) { //systemMsgArray[8]
	case 0x01: /**< Настройка для 1 сообщения */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x02: /**< Настройка для 2 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x03: /**< Настройка для 3 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		//xTaskCreate(prvLedBlink2, "LED_BLINK2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x04: /**< Настройка для 4 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG4, "CAN_Msg_4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x05: /**< Настройка для 5 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG4, "CAN_Msg_4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG5, "CAN_Msg_5", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x06: /**< Настройка для 6 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG4, "CAN_Msg_4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG5, "CAN_Msg_5", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG6, "CAN_Msg_6", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x07: /**< Настройка для 7 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG4, "CAN_Msg_4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG5, "CAN_Msg_5", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG6, "CAN_Msg_6", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG7, "CAN_Msg_7", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }

		break;
	case 0x08: /**< Настройка для 8 сообщений */
		xTaskCreate(CAN_TxMSG1, "CAN_Msg_1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG2, "CAN_Msg_2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG3, "CAN_Msg_3", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG4, "CAN_Msg_4", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG5, "CAN_Msg_5", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG6, "CAN_Msg_6", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG7, "CAN_Msg_7", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		xTaskCreate(CAN_TxMSG8, "CAN_Msg_8", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

		xTaskCreate(CAN_RxMSG_control, "CAN_RxMsg", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
		/*_______ Start the scheduler___________ */
		vTaskStartScheduler();
		while(1) { }
	}

  }
	xTaskCreate(prvLedBlinkError, "LED_BLINK_ERROR", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	/*_______ Start the scheduler___________ */
	vTaskStartScheduler();
	while(1) { }

}

void vApplicationTickHook(void)
{

	//	TimingDelay_Decrement();
}
