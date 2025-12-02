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
 * carregar no botão super rapido ???
 * COVERS 							FEITO
 * mostardor frequencia / incrementador freq
 *
 * MAIN de acordo com o UML ??
 * Fazer refresh a cada minuto em vez de segundo
 */





int main(void) {
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

    	//LCDText_Printf("Volume:%d\nFreq:%f", volume, freq);


    }

    return 0;
}
