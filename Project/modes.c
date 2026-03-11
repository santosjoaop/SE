/**
 * @file modes.c
 * @brief Implementation of application operation modes for the LPC1769 project.
 *
 * This file contains the functions that manage initialization of peripherals,
 * configuration of time, frequency, and volume, user interaction via buttons,
 * LCD updates, and Flash memory read/write for persistent storage.
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
#include "Nav7Btn.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "flash.h"
#include "radio.h"
#include "func.h"
#include "ui_lcd.h"
#include "modes.h"
#include <stdio.h>
#include <string.h>


void Inits(Radio_flash* flash){
    NAVBTN_Init();
    DELAY_Init();
    LCDText_Init();
    RTC_Init(1763396150);

    Radio_SHUTDOWN(0);
    DELAY_Milliseconds(50);
    Radio_Init();
    DELAY_Milliseconds(50);

    Radio_flash memory;
    memcpy(&memory, (void*)ADDR_START_SECTOR_29, sizeof(memory));

    if(memory.code == 112 &&
       memory.freq >= 76.0 && memory.freq <= 108.0 &&
       memory.volume <= 14){

        flash->freq   = memory.freq;
        flash->volume = memory.volume;
    }

    Radio_SetVolume(flash->volume);
    DELAY_Milliseconds(10);
    Radio_SetFreq(flash->freq);
}


void SetVolume_MODE(int* volume){
	int t_atual = DELAY_GetElapsedMillis(0);
	LCDText_Clear();
	LCDVolume_Print(*volume, 0);

	while(DELAY_GetElapsedMillis(t_atual) <= 2000){

		Radio_SetVolume(*volume);

		switch(NAVBTN_Read()){					//Leitura do botão
			case NAVBTN_UP:						//Aumentar o volume
				t_atual = DELAY_GetElapsedMillis(0);
				if(*volume != 14) (*volume)++;
				LCDVolume_Print(*volume, 0);
				break;

			case NAVBTN_DOWN:					//Baixar o volume
				t_atual = DELAY_GetElapsedMillis(0);
				if(*volume != 0) (*volume)--;
				LCDVolume_Print(*volume, 0);
				break;
			default:
				break;
		}
	}
}



void Operation_MODE(Radio_flash* flash){
	struct tm now = {0};
	///
	float ch_spacing = 0.1;
	int jump = 0;
	float past = 0;
	///

	while(1){
		RTC_GetTimeDate(&now);
		LCD_Time(&now,flash->freq);

		if(past != flash->freq) Radio_SetFreq(flash->freq);
		past = flash->freq;


		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_UP:						//Aumentar o volume
				if(flash->volume != 14) (flash->volume)++;
				Radio_SetVolume(flash->volume);
				SetVolume_MODE(&flash->volume);
				LCDText_Clear();
				break;

			case NAVBTN_DOWN:					//Baixar o volume
				if(flash->volume != 0) (flash->volume)--;
				Radio_SetVolume(flash->volume);
				SetVolume_MODE(&flash->volume);
				LCDText_Clear();
				break;

			default: break;
		}

		switch(NAVBTN_Pressed()){					//Leitura do butão
			case NAVBTN_RIGHT:					//Aumentar a frequencia
				if(flash->freq + ch_spacing <= 108.0) flash->freq += ch_spacing;
				else flash->freq = 108;
				//XXX afetar no radio
				break;
			case NAVBTN_LEFT:					//Baixar a frequencia
				if(flash->freq - ch_spacing >= 76.0) flash->freq -= ch_spacing;
				else flash->freq = 76;
				//XXX afetar no radio
				break;

			case NAVBTN_CENTER:					//Baixar a frequencia
				jump = (jump + 1) % 4;
				if(jump == 0)ch_spacing = 0.1;
				if(jump == 1)ch_spacing = 0.3;
				if(jump == 2)ch_spacing = 1;
				if(jump == 3)ch_spacing = 5;
				break;

			case NAVBTN_BACK:					//guarda na meória os valores atiais
				uint8_t buffer[256] = {0};
				memcpy(&buffer, flash, sizeof(*flash));
				FLASH_EraseSector(29);
				FLASH_WriteData((void*)ADDR_START_SECTOR_29, &buffer, sizeof(buffer));
				LCD_Cover("Volume and freq\nsaved on memory", 1500);
				break;

			case NAVBTN_ENTER: return;
			default:break;
		}
	}
}


int Menu_MODE(void){
	int field = 0;								//campo a ser alterado

	LCDText_Clear();
	LCD_Menu_Blink(field);

	NoBtn();

	while(1){
		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_BACK:								//cancelar alterações
				return -1;

			case NAVBTN_ENTER:
				if (field == 0) return 0;			//se estiver o campo "Time"a piscar ao pressionara ENTER vamos para a configuração do time
				else return 1;						//senão vamos para a configuração do radio

			default:
				break;
		}

		switch(NAVBTN_Pressed()){					//Leitura do butão
					case NAVBTN_RIGHT:
					case NAVBTN_LEFT:
						field = (field + 1) % 2;
						break;

					default:
						break;
		}


		LCD_Menu_Blink(field);
		DELAY_Milliseconds(50);
	}
	return -2;
}



int Time_Config_MODE(void){

	int field = 0;								//campo a ser alterado
	int changed = 0;
	struct tm saved;
	saved.tm_sec = 0;							//a cópia devo começar com os segundos a 0
	RTC_GetTimeDate(&saved);					//guarda uma cópia de RTC atual numa struct tm


	LCDText_Clear();
	LCD_Time_Blink(&saved, field, 0);

	NoBtn();

	while(1){
		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_UP:
				ChangeTime(&saved, field, 1);
				changed = 1;
				break;

			case NAVBTN_DOWN:
				ChangeTime(&saved, field, -1);
				changed = 1;
				break;


			case NAVBTN_BACK:								//cancelar alterações
				return 0;

			case NAVBTN_ENTER:
				if(!ValidDate(&saved))return -1;			//verificar se saved é valida				//se for uma hora e data válida faz set no RTC
				RTC_SetTimeDate(&saved);					//afeta os registos do RTC com o valor das alterações
				return 1;

			default:
				changed = 0;
				break;
		}

		switch(NAVBTN_Pressed()){					//Leitura do butão
					case NAVBTN_RIGHT:
						field = (field + 1) % 5;
						changed = 1;
						break;

					case NAVBTN_LEFT:
						field = (field + 4) % 5;
						changed = 1;
						break;

					default:
						break;
		}


		LCD_Time_Blink(&saved, field, changed);		//só vai haver um novo print se houver alteração de campos
		DELAY_Milliseconds(50);
	}
	return -2;
}


int Radio_Config_MODE(){
	Radio_flash data_flash;
	memcpy(&data_flash, (void*)ADDR_START_SECTOR_29, sizeof(Radio_flash));
	if(data_flash.code == 112){
		LCD_Cover("BACK-Cancel\nENTER-Clear mem", 2500);
		NoBtn();
		LCDText_Clear();
		while(1){
			LCDText_Printf("Freq:%.1fMHz   ",data_flash.freq);
			LCDVolume_Print(data_flash.volume, 1);


			switch(NAVBTN_Pressed()){
						case NAVBTN_BACK:  return 0;
						case NAVBTN_ENTER:
							FLASH_EraseSector(29);
							return 1;

						default: break;
			}
		}
	}
	else{
		LCD_Cover("No volume and \nfreq on memory", 1500);
		return 0;

	}
}
