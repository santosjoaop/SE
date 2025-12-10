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
    Radio_Init();

    Radio_SHUTDOWN(0);

    Radio_Write_Word(0x02, 0xC001);  // ENABLE + UNMUTE
    Radio_Write_Word(0x03, 0x9C40);  // tune 98.3 MHz
    DELAY_Milliseconds(200);         // wait for STC
    Radio_Write_Word(0x03, 0x1C40);  // clear TUNE bit
    Radio_Write_Word(0x05, 0x001F);  // max volume

    LCDText_Clear();
    LCDText_Printf("Antena 1\n98.3MHz");

    // READ STATUS REGISTER (NOT REG02)
    Radio_Read_Word(0x0A , &data);
    LCDText_Clear();
    LCDText_Printf("\nREG0A: 0x%04X", data);
}

