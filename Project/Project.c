/**
 * @file Project.c
 * @brief Implementation of the main program for the SE IoT LPC1769 project.
 *
 * This file contains the main function responsible for:
 *  - Initializing drivers and services
 *  - Reading saved radio settings from Flash memory
 *  - Displaying the startup screen
 *  - Continuously executing operation modes, including:
 *      - Normal operation (displaying time and controlling radio)
 *      - Configuration modes for time and radio
 *
 * Course: LEETC - SV 2025/26
 * Group: SE_IoT - Grupo 1
 *
 * @author Diogo Freixo (50387)
 * @author João Santos  (51009)
 *
 * @version 2.0
 * @date 11/03/2026
 *
 * @copyright Copyright (c) 2026
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
	//default: só irá aparecer caso não haja nada guardado em memória
	Radio_flash flash;
	flash.code = 112;
	flash.freq = 76.0;
	flash.volume = 0;

	//no init é atualizado os valores de volume e freq caso haja algo em memória
    Inits(&flash);
    LCD_Cover("Projecto SE\nGrupo 2", 5000);
	LCDText_Clear();
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


