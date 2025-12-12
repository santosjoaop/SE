/**
 * @file Lab9.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-12-04
 *
 * @copyright Copyright (c) 2025
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
#include "radio.h"



int main(void){
	DELAY_Init();
    LCDText_Init();
    Radio_Init();								//radio valores default

    Radio_SHUTDOWN(0);							//ligar o Amp

    Radio_Write_Word(0x02, 0xC001);
    Radio_Write_Word(0x03, 0x3117);
    Radio_Write_Word(0x05, 0x0018);


    uint8_t reg = 0x05;
	uint8_t buf[2];



	while(1){
		DELAY_Milliseconds(500);
		if(I2CMASTER_Transmit(0x11, &reg, 1) != 0){
			LCDText_Printf("\nTX Error     ");
			continue;
		}
		if(I2CMASTER_Receive(0x11, buf, 2) != 0){
			LCDText_Printf("\nRX Error     ");
			continue;
		}
		uint16_t id = (buf[0] << 8) | buf[1];
		LCDText_Printf("\nREG5: 0x%04X   ", id);
	}

}
