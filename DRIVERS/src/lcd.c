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


#define PCGPIO 15													/**MACRO ativar clock do GPIO*/
#define GPIO_FUNC 12												/**MACRO mexer na função do PIN*/
#define P00 0														/**MACRO PINS usados*/
/*#define P01 1
#define P02 2
#define P03 3
#define P04 4
#define P05 5*/
#define P06 6


void LCDGPIO_Init(int start, int last){
	LPC_SC->PCONP |= (1 << PCGPIO);									/**ativar clock do GPIO*/

	LPC_PINCON->PINSEL0 &= ~(3 << GPIO_FUNC );						/**escolher função do PIN*/

	for(int i = first; i <= last ; i++){
		LPC_GPIO0 -> FIODIR |= (1<<i);

	}
}




static void LCDText_WriteNibble(bool rs, uint8_t value) {
// Set RS signal
// Set nibble
// Pulse EN (enable). Respect setup and hold time
//...
}
static void LCDText_WriteByte(int rs, unsigned char value) {
// Call LCDText_WriteNibble with RS and higger nibble;
// Call LCDText_WriteNibble with RS and lower nibble;
//---
}





void LCDText_Init(void);


void LCDText_WriteChar(char ch);


void LCDText_WriteString(char *str);


void LCDText_SetCursor(int row, int column);


void LCDText_Clear(void);


//void LCDText_Printf(char *fmt, ...);
