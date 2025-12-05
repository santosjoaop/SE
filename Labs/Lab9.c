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

    I2CMASTER_Init();
    I2CMASTER_SetFrequency(100000);

    LCDText_Printf("RDA5807 Test");

    uint8_t writeBuf[3];
    uint8_t readBuf[2];

    while(1){
        DELAY_Milliseconds(500);

        // -------------------------------
        // WRITE to register 0x05 (value: 0x1234)
        // -------------------------------
        writeBuf[0] = 0x05;    // Register address
        writeBuf[1] = 0x88;    // High byte
        writeBuf[2] = 0x8E;    // Low byte

        if (I2CMASTER_Transmit(0x11, writeBuf, 3) != 0) {
            LCDText_Printf("\nWrite Error");
            continue;
        }

        // -------------------------------
        // READ register 0x05 back
        // -------------------------------
        uint8_t reg = 0x05;
        if (I2CMASTER_Transmit(0x11, &reg, 1) != 0) {
            LCDText_Printf("\nTX Error");
            continue;
        }

        if (I2CMASTER_Receive(0x11, readBuf, 2) != 0) {
            LCDText_Printf("\nRX Error");
            continue;
        }

        uint16_t data = (readBuf[0] << 8) | readBuf[1];
        LCDText_Printf("\nREG05: 0x%04X", data);
    }
}
