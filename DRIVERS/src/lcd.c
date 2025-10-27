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
    LPC_GPIO0->FIOSET = E;
    DELAY_Microseconds(5);
    LPC_GPIO0->FIOCLR = E;
    DELAY_Microseconds(5);
}



void LCDGPIO_Init(){
	LPC_SC->PCONP |= PCGPIO;									/**ativar clock do GPIO*/
	LPC_PINCON->PINSEL2 &= GPIO_FUNC;						/**escolher função do PIN*/

	for(int i = GPIO_LCD_FIRST; i <= GPIO_LCD_LAST; i++){
		LPC_GPIO2 -> FIODIR |= (1 << i);
	}

	LPC_GPIO2 -> FIOCLR = (RS | E | PB4 | PB5 | PB6 | PB7);
}




static void LCDText_WriteNibble(bool rs, uint8_t value){
	LPC_GPIO2 -> FIOCLR = (PB4 | PB5 | PB6 | PB7);

	if(value & 0x10)LPC_GPIO2 -> FIOSET = PB4;
	if(value & 0x20)LPC_GPIO2 -> FIOSET = PB5;
	if(value & 0x40)LPC_GPIO2 -> FIOSET = PB6;
	if(value & 0x80)LPC_GPIO2 -> FIOSET = PB7;

	LCD_PulseEnable();

}


static void LCDText_WriteByte(int rs, unsigned char value){

	if(rs)LPC_GPIO0->FIOSET = RS;
	else LPC_GPIO0->FIOCLR = RS;

	/**Escrever Nibble parte alta*/
	LCDText_WriteNibble(0, value & 0xF0);				//FUN NIBBLE SEM bool rs

	/**Escrever Nibble parte baixa*/
	LCDText_WriteNibble(0, (value << 4) & 0xF0 );

	DELAY_Microseconds(50);

	if(value <= 0x03)DELAY_Milliseconds(10); 	/**Instruções "Clear display" e "Return home"* demoram mais tempo que as restantes*/
}




void LCDText_Init(void){
	LCDGPIO_Init();							/**Init dos pinos GPIO as serem usados*/

	DELAY_Milliseconds(50);

	    LCDText_WriteNibble(1,0x03);  // 0x30 >> 4 = 0x03
	    DELAY_Milliseconds(5);

	    LCDText_WriteNibble(1,0x03);
	    DELAY_Microseconds(150);

	    LCDText_WriteNibble(1,0x03);
	    DELAY_Microseconds(150);

	    // Muda para modo 4-bit
	    LCDText_WriteNibble(1,0x02);  // 0x20 >> 4 = 0x02
	    DELAY_Microseconds(150);

	    // A partir daqui, envia comandos de 8 bits

	    // Function Set: 4-bit, 2 linhas, 5x8
	    //   DL=0 (4-bit), N=1 (2 linhas), F=0 (5x8)
	    LCDText_WriteByte(1,0x28);

	    // Display OFF (durante configuração)
	    LCDText_WriteByte(1,0x08);

	    // Clear Display
	    LCDText_WriteByte(1,0x01);
	    DELAY_Milliseconds(2);

	    // Entry Mode: incrementar cursor, sem shift
	    // 0x06 = 0b00000110
	    LCDText_WriteByte(1,0x06);

	    // Display ON: display ligado, cursor e blink desligados
	    // 0x0C = 0b00001100
	    LCDText_WriteByte(1,0x0C);

}


void LCDText_WriteChar(char ch){
	LCDText_WriteByte(1, ch);
}


void LCDText_WriteString(char *str){
	if(!str) return;

	for(int i = 0; str[i] != '\0'; i++){
		LCDText_WriteByte(0, str[i]);
	}
}


int LCDText_SetCursor(int row, int column){
	if(row < 0 || row > 1) return -1;
	if(column < 0 || column > 15) return -2;

	uint8_t pos;

	if(!row) pos = 0x00 + column;
	else pos = 0x40 + column;

	LCDText_WriteByte(0, CURSOR_MASK | pos);
	return 0;
}


void LCDText_Clear(void){
	LCDText_WriteByte(0, CLEAR);
}


//void LCDText_Printf(char *fmt, ...);
