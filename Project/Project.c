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
#include <string.h>
#include "delay.h"
#include "lcd.h"

#include "ui_lcd.h"
#include "modes.h"
#include "func.h"




int main(void){
	//default: só irá aparecer caso não haka nada huardado em memória
	Radio_flash flash;
	flash.code = 112;
	flash.freq = 76.0;
	flash.volume = 0;

	//no init é atualizado os valores de volume e freq caso haja algo em memória
    Inits(&flash);
    LCD_Cover("Projecto SE\nGrupo 2", 5000);

    while(1){
    	Operation_MODE(&flash);

    	switch(Menu_MODE()){
			case -1: break;

			case 0:
				switch(Time_Config_MODE()){
					case -1: LCD_Cover("Invalid date\nCancelled!", 1500); break;
					case 0:  LCD_Cover("Cancelled!", 1500); break;
					case 1:  LCD_Cover("Valid date\nSaved!", 1500); break;
				}
				break;


			case 1:
				switch(Radio_Config_MODE()){
					case 0: break;
					case 1: LCD_Cover("Volume and freq\ncleared", 2500); break;
				}
		}
    }
    return 0;
}


