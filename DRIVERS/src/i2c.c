/**
 * @file i2c.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-11-24
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "delay.h"
#include "lcd.h"
#include <stdio.h>

#define PCI2C0 7
#define PCLK_I2C0 14

#define SDA0_FUNC 22
#define SCL0_FUNC 24

#define STO 4
#define STA 5
#define I2EN 6


void I2CMASTER_Init(void){
	//garantir que I2C0 está ativo
	LPC_SC->PCONP |= (1 << PCI2C0);

	//garante que o clock do I2C0 está ativo
	LPC_SC ->PCLKSEL0 &= ~(3 << PCLK_I2C0);

	//ativar a função do pino P0.27 para Data line (SDA)
	LPC_PINCON->PINSEL1 |= (1 << SDA0_FUNC);
	//ativar a função do pino P0.28 para Clock line (SCL)
	LPC_PINCON->PINSEL1 |= (1 << SCL0_FUNC);

	//ativa o bit I2EN bit
	LPC_I2C0->I2CONSET &= (1 << I2EN);
}

void I2CMASTER_SetFrequency(int frequency){
	int hl_sum = SystemCoreClock/frequency;

	LPC_I2C0->I2SCLH = hl_sum/2;
	LPC_I2C0->I2SCLL = hl_sum/2;

}

int I2CMASTER_Transmit(unsigned char devAddress, void *data, unsigned int size){
	//LPC_I2C0->I2CONSET = (1 << STA);
	//START
	//SLAVE ADRESS
	//bit a 0 W para escreverx
	////ACK//ESPERA durante X ms o bit de aknowledge do periferico


	//...
	//DATA enviada
	////ACK//ESPERA durante X ms o bit de aknowledge do periferico
	//...

	//STOP quando já estiver toda a data enviada
	//LPC_I2C0->I2CONSET = (1 << STO);
}

int I2CMASTER_Receive(unsigned char devAddress, void *data, unsigned int size){
	//START
	//SLAVE ADRESS
	//bit a 1 R para escrever
	////ACK//ESPERA durante X ms o bit de aknowledge do periferico


	//...
	////DATA recebida
	//ACK//ESPERA durante X ms o bit de aknowledge do periferico
	//...

	//STOP quando já estiver toda a data enviada
}


