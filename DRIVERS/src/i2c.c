/**
 * @file i2c.c
 * @author Grupo 2
 * @brief I2C Master driver for LPC1769
 * @version 1.0
 * @date 2025-11-24
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "delay.h"
#include "lcd.h"
#include <stdio.h>

#define PCI2C0     7
#define PCLK_I2C0  14

#define SDA0_FUNC 22
#define SCL0_FUNC 24

#define STO 4
#define STA 5
#define AA  2
#define SI  3
#define I2EN 6

// Wait until the SI flag (interrupt flag) is set
static inline void I2C_Wait(void) {
    while(!(LPC_I2C0->I2CONSET & (1 << SI)));
}

// Clear SI bit
static inline void I2C_ClearSI(void) {
    LPC_I2C0->I2CONCLR = (1 << SI);
}


void I2CMASTER_Init(void){
    // 1. Enable power to I2C0
    LPC_SC->PCONP |= (1 << PCI2C0);

    // 2. Peripheral clock = CCLK/4
    LPC_SC->PCLKSEL0 &= ~(3 << PCLK_I2C0);

    // 3. Configure SDA0 (P0.27) and SCL0 (P0.28)
    LPC_PINCON->PINSEL1 &= ~((3 << SDA0_FUNC) | (3 << SCL0_FUNC));
    LPC_PINCON->PINSEL1 |=  ((1 << SDA0_FUNC) | (1 << SCL0_FUNC));

    // 4. Enable the I2C0 module
    LPC_I2C0->I2CONSET = (1 << I2EN);
}


void I2CMASTER_SetFrequency(int frequency){
    int pclk = SystemCoreClock / 4;    // I2C0 clock
    int divider = pclk / (2 * frequency);

    LPC_I2C0->I2SCLH = divider;
    LPC_I2C0->I2SCLL = divider;
}


/**
 * @brief Transmit bytes to a slave (blocking)
 */
int I2CMASTER_Transmit(unsigned char devAddress, void *data, unsigned int size){
    uint8_t *bytes = (uint8_t*) data;

    // Send START
    LPC_I2C0->I2CONSET = (1 << STA);
    I2C_Wait();

    if (LPC_I2C0->I2STAT != 0x08)
        return -1;  // START not sent

    // Send SLA+W
    LPC_I2C0->I2DAT = (devAddress << 1) | 0;
    LPC_I2C0->I2CONCLR = (1 << STA); // clear start
    I2C_ClearSI();
    I2C_Wait();

    if (LPC_I2C0->I2STAT != 0x18)
        return -2;  // No ACK for SLA+W

    // Send bytes
    for (unsigned int i=0; i<size; i++) {
        LPC_I2C0->I2DAT = bytes[i];
        I2C_ClearSI();
        I2C_Wait();

        if (LPC_I2C0->I2STAT != 0x28)
            return -3;  // No ACK for data
    }

    // STOP
    LPC_I2C0->I2CONSET = (1 << STO);
    I2C_ClearSI();

    return 0; // success
}


/**
 * @brief Receive bytes from a slave (blocking)
 */
int I2CMASTER_Receive(unsigned char devAddress, void *data, unsigned int size){
    uint8_t *bytes = (uint8_t*) data;

    // START
    LPC_I2C0->I2CONSET = (1 << STA);
    I2C_Wait();

    if (LPC_I2C0->I2STAT != 0x08)
        return -1;

    // SLA+R
    LPC_I2C0->I2DAT = (devAddress << 1) | 1;
    LPC_I2C0->I2CONCLR = (1 << STA);
    I2C_ClearSI();
    I2C_Wait();

    if (LPC_I2C0->I2STAT != 0x40)
        return -2;

    // Read bytes
    for (unsigned int i=0; i<size; i++) {

        if (i == size - 1)
            LPC_I2C0->I2CONCLR = (1 << AA); // last byte → NACK
        else
            LPC_I2C0->I2CONSET = (1 << AA); // ACK

        I2C_ClearSI();
        I2C_Wait();

        if (LPC_I2C0->I2STAT != 0x50 && i != size - 1)
            return -3;

        bytes[i] = LPC_I2C0->I2DAT;
    }

    // STOP
    LPC_I2C0->I2CONSET = (1 << STO);
    I2C_ClearSI();

    return 0;
}

