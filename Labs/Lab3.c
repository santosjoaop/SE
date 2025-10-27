/**
 * @file Lab3.c
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

#include <cr_section_macros.h>

#include <stdio.h>
#include "delay.h"
#include "lcd.h"


#define SWITCH_LINES 1000											/**tempo de alternancia entre a primeira e segunda linha (em ms)*/
#define ON_TIME 10000												/**tempo que o LCD fica a mostar (em ms)*/
#define OFF_TIME 500												/**tempo que o LCD fica limpo (em ms)*/


int main(void) {
    printf("Hello World\n");

    char* string = "TESTE LCD";


    DELAY_Init();											/**Iniciamos os GPIO2 2..7*/
    LCDText_Init();
    while(1){
    	int t_atual = DELAY_GetElapsedMillis(0);
    	int line = 0;
    	while(DELAY_GetElapsedMillis(t_atual) <= ON_TIME){

    		LCDText_Clear();
    		LCDText_SetCursor(line, 0);
    		LCDText_WriteString(string);
    		DELAY_Milliseconds(SWITCH_LINES);

    		line = line ? 0 : 1;									/**mudar a linha*/
    	}

    	int t_passado = DELAY_GetElapsedMillis(0);
    	while(DELAY_GetElapsedMillis(t_passado) <= OFF_TIME){
    		LCDText_Clear();
    	}

    }

}
