#include "SoftTimer.h"
#include "hw_config.h"
#include "var.h"




__IO tTimer prTimer[TimersQTY];

/*******************************************************************************
* Function Name  : TimerWork
* Description    : This function check stare all create timers
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimerWork(void)
{
__IO unsigned char i=0;
    for (i=0;i<TimersQTY; i++)
    {
    if(prTimer[i].Status)
    {
        if(prTimer[i].Count<(prTimer[i].Limit*100)-1)
        {
            prTimer[i].Count++;
        }
        else
        {
            prTimer[i].Flag=1;
            prTimer[i].Count=0;
        }
    }
  }
}

/*******************************************************************************
* Function Name  : CreateTimer
* Description    : This function create timer ¹?
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
__IO unsigned int CreateTimer(int NumberTimer, unsigned int CountTime)
{
    __IO unsigned char TimerCreateError=0;//For Debugger
    if(!prTimer[NumberTimer].Status)
    {
        prTimer[NumberTimer].Limit=CountTime;
        prTimer[NumberTimer].Status=1;
    }
    else
        TimerCreateError=1;
    return TimerCreateError;
}
