/**
 * @file lcd.c
 * @brief Implementation of drivers for the HD44780U LCD controller.
 *
 * This file contains the implementation of the functions used to control
 * the LCD in 4-bit mode, including setting the cursor position, clearing
 * the display, and providing a printf-like function for formatted output.
 *
 * Course: LEETC - SV 2025/26
 * Group: SE_IoT - Grupo 1
 *
 * @author Diogo Freixo (50387)
 * @author João Santos (51009)
 *
 * @version 2.0
 * @date 06/03/2026
 *
 * @copyright Copyright (c) 2026
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "lcd.h"
#include "delay.h"
#include <stdio.h>
#include <stdarg.h>

#define PCGPIO (1 << 15)													/**MACRO ativar clock do GPIO*/
#define GPIO_FUNC ~(3 << 12 )												/**MACRO mexer na função do PIN*/

#define CLEAR 0x01
#define CURSOR_MASK 0x80

#define GPIO_LCD_FIRST 2													/**Para usar em ciclos snedo que estão todos seguidos*/
#define GPIO_LCD_LAST 7

#define RS 	(1 << 2)
#define E 	(1 << 3)
#define PB4 (1 << 4)
#define PB5 (1 << 5)
#define PB6 (1 << 6)
#define PB7 (1 << 7)



void LCD_PulseEnable(void){
    LPC_GPIO2->FIOSET = E;
    DELAY_Microseconds(5);
    LPC_GPIO2->FIOCLR = E;
    DELAY_Microseconds(5);
}


void LCDGPIO_Init(){
	LPC_SC->PCONP |= PCGPIO;
	/**escolher função do PIN*/
	LPC_PINCON->PINSEL2 &= GPIO_FUNC;

	/**FIODIR do 2 a 7 */ //ALTERAR ISTO, MUITO CONFUSO
	for(int i = GPIO_LCD_FIRST; i <= GPIO_LCD_LAST; i++){
		LPC_GPIO2 -> FIODIR |= (1 << i);
	}

	LPC_GPIO2 -> FIOCLR = (RS | E | PB4 | PB5 | PB6 | PB7);
}


static void LCDText_WriteNibble( uint8_t value){
	LPC_GPIO2 -> FIOCLR = (PB4 | PB5 | PB6 | PB7);

	if(value & 0x01)LPC_GPIO2 -> FIOSET = PB4;
	if(value & 0x02)LPC_GPIO2 -> FIOSET = PB5;
	if(value & 0x04)LPC_GPIO2 -> FIOSET = PB6;
	if(value & 0x08)LPC_GPIO2 -> FIOSET = PB7;

	LCD_PulseEnable();

}


static void LCDText_WriteByte(int rs, unsigned char value){

	if(rs == 1)
		LPC_GPIO2->FIOSET = RS;
	else
		LPC_GPIO2->FIOCLR = RS;

	/**Escrever Nibble parte alta*/
	LCDText_WriteNibble((value & 0xF0) >> 4);

	/**Escrever Nibble parte baixa*/
	LCDText_WriteNibble(value & 0xF);

	DELAY_Microseconds(50);

	if(value <= 0x03)DELAY_Milliseconds(5); 	/**Instruções "Clear display" e "Return home"* demoram mais tempo que as restantes*/
}


void LCDText_Init(void){
	LCDGPIO_Init();/**Init dos pinos GPIO as serem usados*/

	LPC_GPIO2 -> FIOCLR = (RS | E | PB4 | PB5 | PB6 | PB7);

	DELAY_Milliseconds(50);

	    LCDText_WriteNibble(0x03);  // 0x30 >> 4 = 0x03
	    DELAY_Milliseconds(5);

	    LCDText_WriteNibble(0x03);
	    DELAY_Microseconds(150);

	    LCDText_WriteNibble(0x03);
	    DELAY_Microseconds(150);

	    // Muda para modo 4-bit
	    LCDText_WriteNibble(0x02);  // 0x20 >> 4 = 0x02
	    DELAY_Microseconds(150);

	    // comandos de 8 bits
	    LCDText_WriteByte(0,0x28);

	    // Display OFF
	    LCDText_WriteByte(0,0x08);

	    // Clear Display
	    LCDText_WriteByte(0,0x01);
	    DELAY_Milliseconds(5);

	    // Entry Mode: incrementar cursor, sem shift
	    // 0x06 = 0b00000110
	    LCDText_WriteByte(0,0x06);

	    // Display ON
	    // 0x0C = 0b00001100 para cursor desligado
	    // 0x0E para cursor ligado
	    LCDText_WriteByte(0,0x0C);

}


void LCDText_WriteChar(char ch){
	if(ch == '\n'){
		LCDText_SetCursor(1,0);
		return;
	}
	LCDText_WriteByte(1, ch);
}


void LCDText_WriteString(char *str){
	if(!str) return;

	for(int i = 0; str[i] != '\0'; i++){
		LCDText_WriteChar(str[i]);
	}
	LCDText_SetCursor(0, 0);
}


void LCDText_SetCursor(int row, int column){
	uint8_t pos;

	if(row == 0)
		pos = 0x00 + column;
	else
		pos = 0x40 + column;

	LCDText_WriteByte(0, CURSOR_MASK | pos);

}


void LCDText_Clear(void){
	LCDText_WriteByte(0, CLEAR);
}


void LCDText_Printf(char *fmt, ...){
    char buffer[64];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    LCDText_WriteString(buffer);
}

