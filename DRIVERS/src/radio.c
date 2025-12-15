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
#include <stdio.h>


#define P021 21
#define PCGPIO 15
#define GPIO_FUNC 10

#define RADIO_ADDR 0x11




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

	/*
	Radio_Write_Word(0x02,0xC001);
	Radio_Write_Word(0x03,0x2B50);
	//Radio_Write_Word(0x03,0x0018);
	Radio_Write_Word(0x04,0x0000);
	Radio_Write_Word(0x05,0x0881);//???será 41
	Radio_Write_Word(0x06,0x0000);
	Radio_Write_Word(0x07,0x1082);
	Radio_Write_Word(0x08,0x0000);*/

	return 0;
}



int Radio_Write_Word(uint8_t reg, uint16_t data){
	uint8_t writeBuf[3];
	writeBuf[0] = reg;    					//valor hexa do registo
	writeBuf[1] = (data >> 8) & 0xFF;  		//2ºbit do data(parte alta)
	writeBuf[2] = data & 0xFF;				//1ºbit do data(parte baixa)

	if (I2CMASTER_Transmit(RADIO_ADDR, writeBuf, 3) != 0){
		return -1;
	}

	return 0;
}


int Radio_Read_Word(uint8_t reg, uint16_t* data){
	uint8_t readBuf[2];

	if(I2CMASTER_Transmit(RADIO_ADDR, &reg, 1) != 0){
		return -1;
	}
	if(I2CMASTER_Receive(RADIO_ADDR, readBuf, 2) != 0){
		return -2;
	}

	 *data = (readBuf[0] << 8) | readBuf[1];

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
	uint16_t chan = (uint16_t)((freq - 76.0f) * 10.0f + 0.5f);	//+ 0.5f devido á imprecisão de float
	Radio_Write_Word(0x03, (chan << 6) + 24);						//alteração dos bits CHAN

	//hardware "retira o bit de tune após"
	return 0;
}


int Radio_SHUTDOWN(int on){
	LPC_SC->PCONP |= (1 << PCGPIO);

	LPC_PINCON->PINSEL1 &= ~(3 << GPIO_FUNC );

	LPC_GPIO0 -> FIODIR |= (1<<P021);

	if(on) 	LPC_GPIO0 -> FIOSET = (1<<P021); //LPC_GPIO0 -> FIOSET |= (1<<22)
	else 	LPC_GPIO0 -> FIOCLR = (1<<P021);

	return on;
}
