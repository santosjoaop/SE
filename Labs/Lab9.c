/**
 * @file Lab9.c
 * @author Grupo 2
 * @brief
 * @version 2.0
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

    Radio_Init();

    LCDText_Printf("RDA5807 Test");


    uint16_t data;
    while(1){
        DELAY_Milliseconds(500);

        //Radio_Write_Word(0x05, 0x0000);
        Radio_Write_Bits(0x05, 10, 7, 4);



        Radio_Read_Word(0x05 , &data);
        LCDText_Printf("\nREG05: 0x%04X", data);
    }
}
