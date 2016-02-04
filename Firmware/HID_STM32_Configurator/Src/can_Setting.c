#include "can_Setting.h"
#include "stm32f10x_conf.h"
#include "var.h"


extern __IO uint8_t systemMsgArray[ARRAY_LENGHT];
extern __IO uint8_t Msg_1_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_2_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_3_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_4_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_5_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_6_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_7_Array[ARRAY_LENGHT];
extern __IO uint8_t Msg_8_Array[ARRAY_LENGHT];

/*******************************************************************************
* Function Name  : small to Big.
* Description    : convert any byte to long
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
__IO uint32_t smallToBig(int StartPosition, int QTY, __IO uint8_t *MassData)
{
int i = 0;
__IO uint32_t Big = 0x00;
for(i=0;i<QTY;i++)
    {
      Big=Big|(*(MassData+StartPosition+i)<<8*i);
    }
    return Big;
}
/*******************************************************************************
* Function Name  : gpioCAN.
* Description    : Setting GPIO CAN + LED
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void gpioCAN (void)
{
        //______Пин PA3 выход на светодиод3
	    GPIO_InitTypeDef  GPIO_InitStructureLed3;
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	   	GPIO_InitStructureLed3.GPIO_Pin = GPIO_Pin_2;
	   	GPIO_InitStructureLed3.GPIO_Mode = GPIO_Mode_Out_PP;
	   	GPIO_InitStructureLed3.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructureLed3);

        //________Пин PB9 CAN-TX
	    GPIO_InitTypeDef  GPIO_InitStructureCANTX;
	    GPIO_InitStructureCANTX.GPIO_Pin = GPIO_Pin_9;
	    GPIO_InitStructureCANTX.GPIO_Mode = GPIO_Mode_AF_PP;
	    GPIO_InitStructureCANTX.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOB, &GPIO_InitStructureCANTX);
        //______GPIO_PinAFConfig
        GPIO_InitTypeDef  GPIO_InitStructureLed2;
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	   	GPIO_InitStructureLed2.GPIO_Pin = GPIO_Pin_2;
	   	GPIO_InitStructureLed2.GPIO_Mode = GPIO_Mode_Out_PP;
	   	GPIO_InitStructureLed2.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructureLed2);

        //____Input System CLK___________
    /*    RCC->APB2ENR 	|= RCC_APB2ENR_IOPAEN;		// Подаем тактирование на порт

        GPIOA->CRH	&= ~GPIO_CRH_CNF8;		// Сбрасываем биты CNF для бита 8. Режим 00 - Push-Pull
        GPIOA->CRH	|= GPIO_CRH_CNF8_1;		// Ставим режим для 8 го бита режим CNF  = 10 (альтернативная функция, Push-Pull)

        GPIOA->CRH	&=~GPIO_CRH_MODE8;				// Сбрасываем биты MODE для бита 8
        GPIOA->CRH	|= GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0;	// Выставляем бит MODE для пятого пина. Режим MODE11 = Max Speed 50MHz

        RCC->CFGR	&=~(RCC_CFGR_MCO);		// Обнуляем MCO
        RCC->CFGR	|=RCC_CFGR_MCO_PLL;		// Выставлем для MCO сигнал с PLL/2
        RCC->CFGR	|=RCC_CFGR_MCO_SYSCLK;		// Выставляем для МСО сигнал с SYSCLK
    */
}

/*******************************************************************************
* Function Name  : CAN_Setting.
* Description    : Setting CAN - speed, message...
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void CAN_Seting(void)
{
    CAN_DeInit(CAN1);
	CAN_InitTypeDef CAN_Set;

	CAN_Set.CAN_Prescaler = 12; // 250(kbps)
    CAN_Set.CAN_Mode = CAN_Mode_Normal;
    CAN_Set.CAN_SJW = CAN_SJW_1tq;
    CAN_Set.CAN_BS1 = CAN_BS1_8tq;
    CAN_Set.CAN_BS2 = CAN_BS2_3tq;
    CAN_Set.CAN_TTCM = DISABLE;
    CAN_Set.CAN_ABOM = DISABLE;
    CAN_Set.CAN_AWUM = DISABLE;
    CAN_Set.CAN_NART = DISABLE;
    CAN_Set.CAN_RFLM = DISABLE;
    CAN_Set.CAN_TXFP = DISABLE;
CAN_Init(CAN1, &CAN_Set);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
    CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
    CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);


}
void CAN_Seting_1(void)
{
    CAN_DeInit(CAN1);
	CAN_InitTypeDef CAN_Set;

	CAN_Set.CAN_Prescaler = 12; // 250(kbps)
    CAN_Set.CAN_Mode = CAN_Mode_Normal;
    CAN_Set.CAN_SJW = CAN_SJW_1tq;
    CAN_Set.CAN_BS1 = CAN_BS1_8tq;
    CAN_Set.CAN_BS2 = CAN_BS2_3tq;
    CAN_Set.CAN_TTCM = DISABLE;
    CAN_Set.CAN_ABOM = DISABLE;
    CAN_Set.CAN_AWUM = DISABLE;
    CAN_Set.CAN_NART = DISABLE;
    CAN_Set.CAN_RFLM = DISABLE;
    CAN_Set.CAN_TXFP = DISABLE;
CAN_Init(CAN1, &CAN_Set);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
    CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
    CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);

}
/*******************************************************************************
* Function Name  : CAN_Transmit Message.
* Description    : Setting CAN transmit message
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
//___MESSAGE 1__________________
void CAN_TxMSG_1(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_1_Array);
    msg.ExtId = smallToBig(2,4,Msg_1_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_EXT;}
    else
    {msg.IDE = CAN_ID_STD;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 2__________________
void CAN_TxMSG_2(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_2_Array);
    msg.ExtId = smallToBig(2,4,Msg_2_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 3__________________
void CAN_TxMSG_3(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_3_Array);
    msg.ExtId = smallToBig(2,4,Msg_3_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 4__________________
void CAN_TxMSG_4(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_4_Array);
    msg.ExtId = smallToBig(2,4,Msg_4_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 5__________________
void CAN_TxMSG_5(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_5_Array);
    msg.ExtId = smallToBig(2,4,Msg_5_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 6__________________
void CAN_TxMSG_6(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_6_Array);
    msg.ExtId = smallToBig(2,4,Msg_6_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 7__________________
void CAN_TxMSG_7(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_7_Array);
    msg.ExtId = smallToBig(2,4,Msg_7_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
//___MESSAGE 8__________________
void CAN_TxMSG_8(void){
 CanTxMsg msg;
    msg.StdId = smallToBig(2,4,Msg_8_Array);
    msg.ExtId = smallToBig(2,4,Msg_8_Array);
    if (systemMsgArray[9] == 0x01)
    {msg.IDE = CAN_ID_STD;}
    else
    {msg.IDE = CAN_ID_EXT;}
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
CAN_Transmit(CAN1, &msg);
}
/*******************************************************************************
* Function Name  : Setting Interrupt for TIM1 .
* Description    : TIM1
* Input          : None.
* Output         : None.
* Return         : ************************************************************/

void Interrupt_timer_CAN(void){

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );

		TIM_TimeBaseInitTypeDef base_timer;
		TIM_TimeBaseStructInit(&base_timer);
    	base_timer.TIM_Prescaler = 7200 - 1;
		base_timer.TIM_CounterMode = TIM_CounterMode_Up;
		base_timer.TIM_Period = 10;

        TIM_TimeBaseInit(TIM1, &base_timer);
        TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
        TIM_Cmd(TIM1, ENABLE);
		//__enable_irq();
    NVIC_EnableIRQ( TIM1_UP_IRQn );
}
