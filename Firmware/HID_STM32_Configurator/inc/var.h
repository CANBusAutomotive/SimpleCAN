#ifndef VAR_H
#define VAR_H


#define ADDRESS                 0x0800C000                                   // адрес начала страници флэш
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

#define TimersQTY                9

#define ARRAY_LENGHT             0x40


#endif
