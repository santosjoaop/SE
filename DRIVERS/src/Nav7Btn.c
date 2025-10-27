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


#define P018 (1 << 18)														/**Col0*/
#define P017 (1 << 17)														/**Col1*/
#define P015 (1 << 15)														/**Row0*/
#define P016 (1 << 16)														/**Row1*/
#define P023 (1 << 23)														/**Row2*/
#define P024 (1 << 24)														/**Row3*/



/**
 * @brief Iniciação para leiture do teclado de 7 butoes
 */
void NAVBTN_Init(void){

	LPC_SC->PCONP |= PCGPIO;

	LPC_PINCON->PINSEL1 &= GPIO_FUNC;

	//PINMODE 0V or 5V

	return;
}

/**
 * @brief  Lê o teclado de 7 butoes
 * @return devolve a primeira tecla detetada.Se nenhuma tecla estiver pressionada, devolve NAVBTN_NONE
 */
NAVBTN_TypeDef NAVBTN_Read(void){

	if (((LPC_GPIO0 -> FIOPIN = P018) == 1) && ((LPC_GPIO0 -> FIOPIN = P017) == 0)){
		if((LPC_GPIO0 -> FIOPIN = P015) == 1) return NAVBTN_UP;
		if((LPC_GPIO0 -> FIOPIN = P016) == 1) return NAVBTN_DOWN;
		if((LPC_GPIO0 -> FIOPIN = P023) == 1) return NAVBTN_LEFT;
		if((LPC_GPIO0 -> FIOPIN = P024) == 1) return NAVBTN_RIGHT;
		else return NAVBTN_NONE;
	}

	if (((LPC_GPIO0 -> FIOPIN = P018) == 0) && ((LPC_GPIO0 -> FIOPIN = P017) == 1)){
		if((LPC_GPIO0 -> FIOPIN = P015) == 1) return NAVBTN_CENTER;
		if((LPC_GPIO0 -> FIOPIN = P016) == 1) return NAVBTN_BACK;
		if((LPC_GPIO0 -> FIOPIN = P023) == 1) return NAVBTN_ENTER;
		else return NAVBTN_NONE;
	}
	return NAVBTN_NONE;
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
	NAVBTN_TypeDef now;
	while(now == NAVBTN_Read()){
		return NAVBTN_NONE;
	}
	return now;
}
