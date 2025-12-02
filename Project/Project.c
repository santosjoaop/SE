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

    	switch(Config_MODE()){
    		case -1: LCD_Cover("Invalid date\nCancelled!", 1500); break;
    		case 0:  LCD_Cover("Cancelled!", 1500); break;
    		case 1:  LCD_Cover("Valid date\nSaved!", 1500); break;

    	}
    	//if == 0  CANCEL
    	//if == -1 INVALID DATE/CANCEL
    	//if == 1  VALID DATE/SAVE

    	//LCDText_Printf("Volume:%d\nFreq:%f", volume, freq);


    }

    return 0;
}
