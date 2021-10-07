/*
 * GPIO_PE.c
 *
 *  Created on: 2019/12/12
 *      Author: admin
 */

/*#include "GPIO_PE.h"
void delay3(unsigned int nCount){
    unsigned int i;
    for(i=0;i<nCount;i++);
}

void LED(){
    	GPIO_ACT_PE = 0xFFFF; //Initialize GPIO
    	GPIO_OMOD_PE = 0x0; // push/pull mode
    	GPIO_OEN_PE = 0x0; //output enable
        GPIO_DAT_PE = 0x0000;
        delay3(1000000);
        GPIO_DAT_PE = 0x8000;//LED19
        delay3(1000000);
        GPIO_DAT_PE = 0xc000;//LED18
        delay3(1000000);
        GPIO_DAT_PE = 0xe000;//LED15
        delay3(1000000);
        GPIO_DAT_PE = 0xf000;//LED14
        delay3(1000000);
        GPIO_DAT_PE = 0xf800;//LED13
        delay3(1000000);
        GPIO_DAT_PE = 0xfc00;//LED12
        delay3(1000000);
        GPIO_DAT_PE = 0xfe00;//LED11
        delay3(1000000);
        GPIO_DAT_PE = 0xff00;//LED10
        delay3(1000000);
        GPIO_DAT_PE = 0xff01;//LED2
        delay3(1000000);
        GPIO_DAT_PE = 0xff03;//LED3
        delay3(1000000);
        GPIO_DAT_PE = 0xff07;//LED4
        delay3(1000000);
        GPIO_DAT_PE = 0xff0f;//LED5
        delay3(1000000);
        GPIO_DAT_PE = 0xff1f;//LED6
        delay3(1000000);
        GPIO_DAT_PE = 0xff3f;//LED7
        delay3(1000000);
        GPIO_DAT_PE = 0xff7f;//LED8
        delay3(1000000);
        GPIO_DAT_PE = 0xffff;//LED9

    return 0;
}*/

