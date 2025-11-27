/**
 * @file Lab8.c
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


int main(void)
{
    DELAY_Init();
    LCDText_Init();

    I2CMASTER_Init();
    I2CMASTER_SetFrequency(100000);   // 100 kHz I2C

    LCDText_Printf("RDA5807 Test");

    uint8_t reg = 0x00;   // register 0
    uint8_t buf[2];

    while(1){
		DELAY_Milliseconds(500);
		// STEP 1: Write register address (0x00)
		if(I2CMASTER_Transmit(0x11, &reg, 1) != 0){
			LCDText_Printf("\nTX Error     ");
			continue;
		}
		// STEP 2: Read 2 bytes from RDA5807
		if(I2CMASTER_Receive(0x11, buf, 2) != 0){
			LCDText_Printf("\nRX Error     ");
			continue;
		}
		// Combine bytes into 16-bit value
		uint16_t id = (buf[0] << 8) | buf[1];
		LCDText_Printf("\nID: 0x%04X   ", id);
    }
}
