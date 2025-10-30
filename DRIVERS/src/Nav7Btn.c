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
#include "Nav7Btn.h"
#include "delay.h"


#define PCGPIO (1 << 15)													/**MACRO ativar clock do GPIO*/
#define GPIO_FUNC ~(3 << 12 )												/**MACRO mexer na função do PIN*/
#define PULLDOWN 3



#define COL1 (1 << 18)														/**P018*///IN
#define COL2 (1 << 17)														/**P017*///IN
#define ROW1 (1 << 15)														/**P015*/
#define ROW2 (1 << 16)														/**P016*/
#define ROW3 (1 << 23)														/**P023*/
#define ROW4 (1 << 24)														/**P024*/



/**
 * @brief Iniciação para leiture do teclado de 7 butoes
 */
void NAVBTN_Init(void){

	//GPIO CLOCK
	LPC_SC->PCONP |= PCGPIO;

	//FUNCTION GPIO para cada??pino ou chega o bloco
	LPC_PINCON->PINSEL0 &= GPIO_FUNC;										/**Por causa do P015*/
	LPC_PINCON->PINSEL1 &= GPIO_FUNC;

	//OUTPUT PINS MODE PULL DOWN
	LPC_PINCON->PINMODE0 = ~(PULLDOWN << 30);										/**Pin mode do P=15*/
	LPC_PINCON->PINMODE1 = ~(PULLDOWN << 0);										/**Pin mode do P=16*/
	LPC_PINCON->PINMODE1 = ~(PULLDOWN << 14);										/**Pin mode do P=23*/
	LPC_PINCON->PINMODE1 = ~(PULLDOWN << 16);										/**Pin mode do P=24*/


	LPC_GPIO1 -> FIODIR |= COL1;
	LPC_GPIO1 -> FIODIR |= COL2;
	LPC_GPIO0 -> FIODIR |= ROW1;
	LPC_GPIO1 -> FIODIR |= ROW2;
	LPC_GPIO1 -> FIODIR |= ROW3;
	LPC_GPIO1 -> FIODIR |= ROW4;

}

/**
 * @brief  Lê o teclado de 7 butoes
 * @return devolve a primeira tecla detetada.Se nenhuma tecla estiver pressionada, devolve NAVBTN_NONE
 */
NAVBTN_TypeDef NAVBTN_Read(void){
	while(1){

		LPC_GPIO1 -> FIOCLR = COL2;
		LPC_GPIO1 -> FIOSET = COL1;
		if((LPC_GPIO1 -> FIOPIN = ROW2) == 1) return NAVBTN_BACK;
		if((LPC_GPIO1 -> FIOPIN = ROW3) == 1) return NAVBTN_RIGHT;
		if((LPC_GPIO1 -> FIOPIN = ROW4) == 1) return NAVBTN_ENTER;


		LPC_GPIO1 -> FIOCLR = COL1;
		LPC_GPIO1 -> FIOSET = COL2;
		if((LPC_GPIO0 -> FIOPIN = ROW1) == 1) return NAVBTN_UP;
		if((LPC_GPIO1 -> FIOPIN = ROW2) == 1) return NAVBTN_DOWN;
		if((LPC_GPIO1 -> FIOPIN = ROW3) == 1) return NAVBTN_LEFT;
		if((LPC_GPIO1 -> FIOPIN = ROW4) == 1) return NAVBTN_CENTER;

		return NAVBTN_NONE;
	}
}

/**
 * @brief  Igual a NAVBTN_Read(), mas se a tecla se manteve pressionada entre duas
chamadas consecutivas (não permite a repetição).
Não é bloqueante.
 * @return NAVBTN_NONE se ainda estiver a seer pressionado o botão, senão a tecle pressionada
 */
NAVBTN_TypeDef NAVBTN_Pressed(void){

	NAVBTN_TypeDef before = NAVBTN_Read();
	DELAY_Microseconds(100);
	NAVBTN_TypeDef now = NAVBTN_Read();
	while(before == now ){
		return NAVBTN_NONE;
	}
	return now;
}
