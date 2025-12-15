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


    Radio_SHUTDOWN(0);
    DELAY_Milliseconds(200);

    Radio_Init();
    DELAY_Milliseconds(200);


    Radio_Write_Word(0x02, 0xC001);				//Mutes enable etc
    Radio_Write_Word(0x03, 0x2B18);				//0x0018   1 - tune  8 - WW BAND & Spacing 0.1MHz
    Radio_Write_Word(0x05, 0x088F);				//0x0844   4 - LNAN  4 - Volume

    Radio_SetVolume(15);

    Radio_SetFreq(93.2);						//RFM

    uint16_t data;
    while(1)
    {
		for(uint8_t reg = 0x02; reg <= 0x08; reg++) {

			int a = Radio_Read_Word(reg, &data);
			//printf("Error code:%d\n", a);
			if(a == 0) {
				LCDText_Clear();
				LCDText_Printf("REG 0x%02X:\n0x%04X", reg, data);
			}
			else {
				LCDText_Clear();
				LCDText_Printf("REG 0x%02X:\nERROR", reg);
			}

			DELAY_Milliseconds(2000);   // show for 2 seconds
		}
	}

}
