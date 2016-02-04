#ifndef SOFTTIMER_H
#define SOFTTIMER_H

#include "hw_config.h"
#include "var.h"

extern __IO uint8_t ReadDataByte[READ_DATA_LENGHT];


typedef struct
{
    __IO unsigned int Flag;
    __IO unsigned int Status;
    __IO unsigned int  Limit;
    __IO unsigned int Count;
    }tTimer;

extern __IO tTimer prTimer[TimersQTY];

void TimerWork(void);
__IO unsigned int CreateTimer(int NumberTimer, unsigned int CountTime);


#endif
