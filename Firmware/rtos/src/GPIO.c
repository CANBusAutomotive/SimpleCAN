#include "stm32f10x_conf.h"
#include "var.h"
#include "GPIO.h"

/********************************************//**
 * \brief GPIO Setting.
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
void GPIO_Set(void)
{
   //___________Пин PB2 выход на светодиод2
  GPIO_InitTypeDef  GPIO_InitStructureLed;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructureLed.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructureLed.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructureLed.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructureLed);
  //___________Пин PB5 выход на светодиод1
  GPIO_InitTypeDef  GPIO_InitStructureLed1;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructureLed1.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructureLed1.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructureLed1.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructureLed1);
  //___________Пин PB5 выход на светодиод3
  GPIO_InitTypeDef  GPIO_InitStructureLed3;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructureLed3.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructureLed3.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructureLed3.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructureLed3);
  //________Пин PB9 CAN-TX
  GPIO_InitTypeDef  GPIO_InitStructureCANTX;
  GPIO_InitStructureCANTX.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructureCANTX.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructureCANTX.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructureCANTX);
  //________Пин PB8 CAN-RX
  GPIO_InitTypeDef  GPIO_InitStructureCANRX;
  GPIO_InitStructureCANRX.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructureCANRX.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_InitStructureCANRX.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructureCANRX);
  //______GPIO_PinAFConfig
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
}

