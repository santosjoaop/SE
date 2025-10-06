/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
//#include "drivers.h"


#define BLINKING_TIME 5000
#define OFF_TIME 2000
#define LED_PERIOD 500000 //0,5s = 500ms = 500000 us


int main(void) {
    printf("Hello World\n");

    while(){
    	while(DELAY_GetElapsedMillis(BLINK_TIME) <= BLINK_TIME){	//Ou então podemos fazer toogle e delay???
    		LED_On();
    		DELAY_Microseconds(LED_PERIOD);
    		LED_Off();
    		DELAY_Microseconds(LED_PERIOD);
    	}
    	while(DELAY_GetElapsedMillis(OFF_TIME) <= OFF_TIME){
    		LED_Off();
    	}


    }

}
