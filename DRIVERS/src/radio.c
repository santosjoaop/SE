/**
 * @file radio.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-12-04
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "delay.h"
#include "lcd.h"
#include "i2c.h"
#include "radio.h"

#define P021 21
#define PCGPIO 15
#define GPIO_FUNC 10



////////////////////////////////////////////////////////////////


static uint16_t make_mask(int e, int s) {
    uint16_t mask = 0;

    for(int i = s; i <= e; i++){
        mask |= (1u << i);
    }

    return mask;
}


static uint16_t change_bits(uint16_t copy, uint16_t data, int end, int start){
	uint16_t shifted_data = (data << start) & make_mask(end, start);

	// Replace bits one-by-one
	for (int i = start; i <= end; i++) {
		uint16_t bit_from_data = shifted_data & (1u << i);

		if(bit_from_data) 	copy |= (1u << i);
		else 				copy &= ~(1u << i);

	}

	 return copy;
}


////////////////////////////////////////////////////////////////


int Radio_Init(void){
	I2CMASTER_Init();
	I2CMASTER_SetFrequency(100000);

	//Register Definition Default Values
	/*
	Radio_Write_Word(0x02,0x0000);
	Radio_Write_Word(0x03,0x13F0);
	Radio_Write_Word(0x04,0x0000);
	Radio_Write_Word(0x05,0x888B);
	Radio_Write_Word(0x06,0x0000);
	Radio_Write_Word(0x07,0x1082);
	Radio_Write_Word(0x08,0x0000);
	*/

	return 0;
}


int Radio_Write_Word(uint8_t reg, uint16_t data)
{
    uint16_t regs[6];

    uint8_t start = 0x02;
    I2CMASTER_Transmit(0x11, &start, 1);
    I2CMASTER_Receive(0x11, (uint8_t*)regs, 12);

    regs[reg - 2] = data;

    uint8_t buffer[13];
    buffer[0] = 0x02; // start register

    for (int i = 0; i < 6; i++){
        buffer[1 + i*2] = regs[i] >> 8;
        buffer[2 + i*2] = regs[i] & 0xFF;
    }

    // SEND 13 BYTES: reg + 6 words
    I2CMASTER_Transmit(0x11, buffer, 13);

    return 0;
}


int Radio_Read_Word(uint8_t reg, uint16_t *data)
{
    uint8_t buf[16];

    // Read 16 bytes: REG0A–REG0F
    if(I2CMASTER_Receive(0x11, buf, 16) != 0)
        return -1;

    if(reg < 0x0A || reg > 0x0F)
        return -2; // invalid read (02–07 cannot be read)

    int index = (reg - 0x0A) * 2;
    *data = (buf[index] << 8) | buf[index+1];

    return 0;
}


int Radio_Write_Bits(uint8_t reg, uint16_t data, int end, int start){
	uint16_t reg_copy;
	Radio_Read_Word(reg, &reg_copy);

	uint16_t reg_copy_new;
	reg_copy_new = change_bits(reg_copy, data, end, start);

	Radio_Write_Word(reg, reg_copy_new);

	return 0;
}


int Radio_SetVolume(int volume){
	if(volume == 0) Radio_SHUTDOWN(1);
	else Radio_SHUTDOWN(0);

	Radio_Write_Bits(0x05, volume, 3, 0);
	return 0;
}


int Radio_SetFreq(float freq){

	return 0;
}


int Radio_SHUTDOWN(int on){
	LPC_SC->PCONP |= (1 << PCGPIO);

	LPC_PINCON->PINSEL1 &= ~(3 << GPIO_FUNC );

	LPC_GPIO0 -> FIODIR |= (1<<P021);

	if(on) LPC_GPIO0 -> FIOSET = (1<<P021); //LPC_GPIO0 -> FIOSET |= (1<<22)
	else LPC_GPIO0 -> FIOCLR = (1<<P021);

	return on;
}

