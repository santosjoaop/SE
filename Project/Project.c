/**
 * @file Project.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 * 
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Nav7Btn.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "func.h"

/*TODO:
 *
 * BLINK CAMPO A SER ALTERADO
 * carregar no botão super rapido ???
 * COVERS
 * tirar flicker no LCD  							FEITO
 * sliders de volume
 * mostardor frequencia / incrementador freq
 *
 * MAIN de acordo com o UML
 * criar função rtc setdate("hh:mm DD/MM/YYYY" )
 * funç~´ao get date STRING
 */





int main(void) {
    printf("Hello World\n");
    Inits();

    //INIT COVER
    LCDText_Clear();
	LCDText_Printf("Projecto SE\nGrupo 2");
	DELAY_Milliseconds(5000);

    while(1){
    	Operation_MODE();
    	Menu_MODE();
    	//DELAY entre modos evitar problemas de inputs no proximo
    	Config_MODE();
    	//if == 0  CANCEL
    	//if == -1 INVALID DATE/CANCEL
    	//if == 1  VALID DATE/SAVE


    }

    return 0;
}
