/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#define P022 6
#define PCGPIO 15
#define GPIO_FUNC 12

// TODO: insert other include files here

// TODO: insert other definitions and declarations here


void delay(int ms){
	for (int i = 0; i < ms * 100000 ;i++);
}

int main(void) {
    printf("Hello World\n");
    //P0[22] - LED

    //garante que GPIO tem o clock ativo
    LPC_SC->PCONP |= (1 << PCGPIO);

    //garante que o pino esta no funcao de GPIO (00)
    LPC_PINCON->PINSEL1 &= ~(3 << GPIO_FUNC );




    LPC_GPIO0 -> FIODIR |= (1<<22);

    while(1) {
    	LPC_GPIO0 -> FIOSET2 = (1<<P022); //LPC_GPIO0 -> FIOSET |= (1<<22)
    	delay(500);
    	LPC_GPIO0 -> FIOCLR2 = (1<<P022);
    	delay(500);
    }
    return 0 ;
}
