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
	uint16_t data;

	DELAY_Init();
    LCDText_Init();
    Radio_Init();								//radio valores default


    Radio_SHUTDOWN(0);

    Radio_Write_Word(0x02, 0xC001);
    Radio_Read_Word(0x02 , &data);
    LCDText_Clear();
    LCDText_Printf("\nREG2: 0x%04X", data);
    DELAY_Milliseconds(500);



    Radio_Write_Word(0x03, 0x3110);
    Radio_Read_Word(0x03 , &data);
    LCDText_Clear();
    LCDText_Printf("\nREG3: 0x%04X", data);
    DELAY_Milliseconds(500);



    Radio_Write_Word(0x05, 0x0015);
    Radio_Read_Word(0x03 , &data);
    LCDText_Clear();
    LCDText_Printf("\nREG5: 0x%04X", data);
    DELAY_Milliseconds(500);


    LCDText_Clear();
    LCDText_Printf("RFM\n106.6 MHz");
}
