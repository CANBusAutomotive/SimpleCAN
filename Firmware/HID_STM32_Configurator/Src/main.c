/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    09-September-2013
  * @brief   RHID demo main file
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "SoftTimer.h"
#include "can_Setting.h"



//__Defines________________________________________________________________________
#define ApplicationAddress    0x08004000                        //Address of begin user program

/**<-Global Variables--------------------------------------------------------------  */
typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;


/**<-Private Variables--------------------------------------------------------------  */
__IO uint8_t PrevXferComplete = 1;

/*******************************************************************************
* Function Name  : Button_State_Function(Selected Load Mode).
* Description    : Button_State_Function(Selected Load Mode).
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void ButtonState (void)
{
    GPIO_InitTypeDef  GPIO_InitStructureButton;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructureButton.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructureButton.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructureButton.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructureButton);
}
/*******************************************************************************
* Function Name  : flash_read
* Description    : Dread data from flash.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/


void flash_read(uint32_t StartReadAddress)
{
    int i=0;
    for(i=0;i<READ_DATA_LENGHT;i++)
    {
      ReadDataByte[i]=*(uint16_t*)StartReadAddress;
      StartReadAddress++;
    }
}
//----------
__IO uint8_t readInArray(uint32_t StartAddress, unsigned int arrayLenght, __IO uint8_t *MassData)
{   int i = 0;
    for(i=0;i<arrayLenght;i++)
    {
        MassData[i]=*(uint16_t*)StartAddress;
        StartAddress++;
    }

}
/*******************************************************************************
* Function Name  : TIM1 Init.
* Description    : TIM1 Init.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void Interrupt_timer(void){
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );

	TIM_TimeBaseInitTypeDef base_timer;
	TIM_TimeBaseStructInit(&base_timer);
    base_timer.TIM_Prescaler = 4800 - 1;
	base_timer.TIM_CounterMode = TIM_CounterMode_Up;
	base_timer.TIM_Period = 10;

    TIM_TimeBaseInit(TIM1, &base_timer);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    NVIC_EnableIRQ( TIM1_UP_IRQn );
}
/*******************************************************************************
* Function Name  : SysTick_Handler.
* Description    : SysTick IRQ Handler.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void SysTick_Handler(void)
{
TimerWork();
}
/*******************************************************************************
* Function Name  : Interrupt Processing.
* Description    : Interrupt Processing.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void TIM1_UP_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
   {
    //-Clear Interrupt Bit--
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);       //Reset Interrupt Flag
    TimerWork();
   }
}
/*******************************************************************************
* Function Name  : ReadOutProtection.
* Description    : Delay.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void ReadOutProtection(void)
{
if (FLASH_GetReadOutProtectionStatus() == RESET)
    {
      FLASH_Unlock();
      FLASH_ReadOutProtection(ENABLE);
      FLASH_Lock();
    }
}
/*******************************************************************************
* Function Name  : Delay.
* Description    : Delay.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
void Delay(volatile uint32_t nCount) {
	for (; nCount != 0; nCount--);
}

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : ************************************************************/
int main(void)
{
    ButtonState();//Check Button State
    //ReadOutProtection();
    int State = 0;
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
        State = 1;
    else
        State = 0;

  if(State)// Loading USB
{
    Set_System();
    USB_Interrupts_Config();
    Set_USBClock();
    USB_Init();
    CreateTimer(0,20);
    Interrupt_timer();

    while (1)
 {
     //-Checking Timer-------------
     if(prTimer[0].Flag==1)
       {
        GPIOB->ODR ^= GPIO_Pin_2;
        prTimer[0].Flag=0;
       }
             //-Checking-Usb-Connect--------
     if (bDeviceState == CONFIGURED)
       {
        if (PrevXferComplete)
          {
            RHIDCheckState();
          }
        }
 }
}
      else // Loading CAN BUS
      {
        if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)      //Проверяем, есть ли что-нибудь по адресу (там должно лежать значение SP для приложения, его кладет линкер)
                {
                  JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);           //Адрес перехода из вектора Reset
                  Jump_To_Application = (pFunction) JumpAddress;                      //Указатель на функцию перехода
                  __set_MSP(*(__IO uint32_t*) ApplicationAddress);                    //Устанавливаем SP приложения
                  GPIO_DeInit(GPIOA);
                  //__disable_irq();                                                  // Запрещаем прерывания
                  //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x10000);                 //Адрес таблицы относительно начала Flash
                  //__enable_irq();
                  Jump_To_Application();                                              //Запускаем приложение
                }
      }
      return 0;

}

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
