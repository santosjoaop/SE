/**
 * @file Lab8.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-11-24
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "lcd.h"
#include "i2c.h"

//P0.27 Pino para Data line (SDA)
//P0.28 Pino para Clock line (SCL)
//P0.21 Pino para SHUTDOWN






int main(void){
	DELAY_Init();
	LCDText_Init();

	while(1){
	    	int t_atual = DELAY_GetElapsedMillis(0);
	    	if(DELAY_GetElapsedMillis(t_atual) >= 500){

	    		//I2CMASTER_Receive(0x00, void *data, unsigned int size)
	    	}
	}

}

