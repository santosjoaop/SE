/*
 * led.c
 *
 *  Created on: 07/10/2025
 *      Author: diogo
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "led.h"

//DEFINES PARA CONTAS
#define PCGPIO 15
#define GPIO_FUNC 12
#define P022 22


/* Faz a iniciação do sistema para permitir a manipulação do estado LED do sistema de
 * protopagem (LPCXPRESSO LPC1769), onde o parâmetro state se igual a false o LED
 * fica apagado ou caso contrario fica aceso. */
void LED_Init(bool state){

    //garante que GPIO tem o clock ativo
    LPC_SC->PCONP |= (1 << PCGPIO);

    //garante que o pino esta no funcao de GPIO (00)
    LPC_PINCON->PINSEL1 &= ~(3 << GPIO_FUNC );

    LPC_GPIO0 -> FIODIR |= (1<<22);

}

/* Devolve true se o LED está aceso e false se o LED está apagado. */
bool LED_GetState(void){

	if ((LPC_GPIO0 -> FIOPIN = (1<<P022)) == 1){return true;}

	return false;
}
/* Acende o LED. */
void LED_On(void){

	LPC_GPIO0 -> FIOSET = (1<<P022);
}

/* Apaga o LED. */
void LED_Off(void){

	LPC_GPIO0 -> FIOCLR = (1<<P022);
}

/* Troca o estado do LED. Se estiver aceso apaga o LED, caso contrario acende o LED. */
void LED_Toggle(void){

	if ((LPC_GPIO0 -> FIOPIN = (1<<P022)) == 1){
		LPC_GPIO0 -> FIOCLR = (1<<P022);
	}else{
		LPC_GPIO0 -> FIOSET = (1<<P022);
	}
}

/*
 * led.c
 *
 *  Created on: 07/10/2025
 *      Author: diogo
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "led.h"

//DEFINES PARA CONTAS
#define PCGPIO 15
#define GPIO_FUNC 12
#define P022 22


/* Faz a iniciação do sistema para permitir a manipulação do estado LED do sistema de
 * protopagem (LPCXPRESSO LPC1769), onde o parâmetro state se igual a false o LED
 * fica apagado ou caso contrario fica aceso. */
void LED_Init(bool state){

    //garante que GPIO tem o clock ativo
    LPC_SC->PCONP |= (1 << PCGPIO);

    //garante que o pino esta no funcao de GPIO (00)
    LPC_PINCON->PINSEL1 &= ~(3 << GPIO_FUNC );

    LPC_GPIO0 -> FIODIR |= (1<<22);

}

/* Devolve true se o LED está aceso e false se o LED está apagado. */
bool LED_GetState(void){

	if ((LPC_GPIO0 -> FIOPIN = (1<<P022)) == 1){return true;}

	return false;
}
/* Acende o LED. */
void LED_On(void){

	LPC_GPIO0 -> FIOSET = (1<<P022);
}

/* Apaga o LED. */
void LED_Off(void){

	LPC_GPIO0 -> FIOCLR = (1<<P022);
}

/* Troca o estado do LED. Se estiver aceso apaga o LED, caso contrario acende o LED. */
void LED_Toggle(void){

	if ((LPC_GPIO0 -> FIOPIN = (1<<P022)) == 1){
		LPC_GPIO0 -> FIOCLR = (1<<P022);
	}else{
		LPC_GPIO0 -> FIOSET = (1<<P022);
	}
}

