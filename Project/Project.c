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
#include "Nav7Btn.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "flash.h"
#include "func.h"




int main(void){
	//default: só irá aparecer caso não haka nada huardado em memória
	Radio_flash flash;
	flash.code = 112;
	flash.freq = 76.0;
	flash.volume = 0;

	//memória com valores a ser usados
	Radio_flash copy_flash;
	memcpy(&copy_flash, &flash, sizeof(Radio_flash));


    Inits(&flash);
    LCD_Cover("Projecto SE\nGrupo 2", 5000);

    while(1){
    	Operation_MODE(&flash, &copy_flash);

    	switch(Menu_MODE()){
			case -1: break;

			case 0:
				switch(Time_Config_MODE()){
					case -1: LCD_Cover("Invalid date\nCancelled!", 1500); break;
					case 0:  LCD_Cover("Cancelled!", 1500); break;
					case 1:  LCD_Cover("Valid date\nSaved!", 1500); break;
				}
				break;


			case 1: LCD_Cover("MEMORY: 103.4MHz\n-||||||||||||||+", 3000); break;
					switch(Radio_Config_MODE()){
						case 0: break;
						case 1:  LCD_Cover("Volume and freq\ncleared", 1500); break;
					}
		}
    }
    return 0;
}
