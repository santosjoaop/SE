/**
 * @file Lab4.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-10-27
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "delay.h"
#include "led.h"
#include "Nav7Btn.h"


#define LED_PERIOD 500000 //0,5s = 500ms = 500000 us


int main(void) {

    printf("Hello World\n");

    NAVBTN_Init();

    while(1){

		int btn = (int)NAVBTN_Read();

		for(int i = 1 ; i <= btn ; i++){
			if(btn == 1)printf("Primeiro blink\n");
			if(i == btn)printf("Ultimo blink\n");
			LED_On();
			DELAY_Microseconds(LED_PERIOD);
			LED_Off();
			DELAY_Microseconds(LED_PERIOD);
		}
	}
}
