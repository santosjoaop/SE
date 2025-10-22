/**
 * @file lcd.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "lcd.h"
#include "delay.h"


#define PCGPIO 15													/**MACRO ativar clock do GPIO*/
#define GPIO_FUNC 12												/**MACRO mexer na função do PIN*/

#define SET_CURSOR_FLAG 0b00010000
#define CLEAR_FLAG 0b00001011

#define P22 2
#define P23 3


void LCDGPIO_Init(int start, int last){
	LPC_SC->PCONP |= (1 << PCGPIO);									/**ativar clock do GPIO*/

	LPC_PINCON->PINSEL2 &= ~(3 << GPIO_FUNC );						/**escolher função do PIN*/

	for(int i = start; i <= last ; i++){
		LPC_GPIO2 -> FIODIR |= (1<<i);

	}
}




static void LCDText_WriteNibble(bool rs, uint8_t value){
	LPC_GPIO2 -> FIOSET = (1<<P22);//ATIVAR RS;
	LPC_GPIO2 -> FIOCLR = (1<<P23);//DESATIVAR ENABLE;

	//Fazer clear ao display
	


	for(int i = 3, j = 4; i >= 0 ; i--){
			j += i;													/*Indice dos P27..4**/
			if((value >> i) & 1) LPC_GPIO2 -> FIOSET = (1<<j);
			else LPC_GPIO2 -> FIOCLR = (1<<j);
			DELAY_Milliseconds(100);
	}

	LPC_GPIO2 -> FIOSET = (1<<P23);//ATIVAR ENABLE;
	DELAY_Milliseconds(300);
	LPC_GPIO2 -> FIOCLR = (1<<P22);//DESATIVAR RS;
}


static void LCDText_WriteByte(int rs, unsigned char value){

	//Shiftar parate alta para uma variavel
	int parte_alta = 0;
	LCDText_WriteNibble(0, parte_alta);
	parte_alta = value;
	LCDText_WriteNibble(0,value);
}





void LCDText_Init(void){
	LCDGPIO_Init(2,7);


	//funcionamento 8bits
	DELAY_Milliseconds(20);
	LCDText_WriteNibble(0, 3 << 4);

	DELAY_Milliseconds(5);
	LCDText_WriteNibble(0, 3 << 4);

	DELAY_Milliseconds(1);
	LCDText_WriteNibble(0, 3 << 4);


	LCDText_WriteNibble(0, 2 << 4);
	//funcionamento 4bits


	//efetuar resto



}


void LCDText_WriteChar(char ch){
	LCDText_WriteByte(0, ch);
}


void LCDText_WriteString(char *str){
	for(int i = 0; str[i] != '\0'; i++){
		LCDText_WriteByte(0, str[i]);
	}
}


void LCDText_SetCursor(int row, int column){
	//LCDText_WriteByte(0, SET_CURSOR_FLAG);
	//Como afetar a linha certa
}


void LCDText_Clear(void){
	LCDText_WriteByte(0, CLEAR_FLAG);
}


//void LCDText_Printf(char *fmt, ...);
