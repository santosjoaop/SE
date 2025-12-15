/**
 * @file func.c
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
#include "Nav7Btn.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "flash.h"
#include "func.h"
#include <stdio.h>
#include <string.h>

void LCD_Cover(char* str, int time){
	LCDText_Clear();
	LCDText_Printf("%s", str);
	DELAY_Milliseconds(time);
}



void LCD_Time(struct tm* data, float freq){
	char buf[20];
	sprintf(buf,"%02d:%02d %02d/%02d/%04d", data->tm_hour, data->tm_min, data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);
	LCDText_Printf("%s\nFreq:%.1fMHz    ", buf, freq);
}


void LCD_Time_Blink(struct tm* data, int BlinkField, int changes){
	char buf[20];
	sprintf(buf,"%02d:%02d %02d/%02d/%04d", data->tm_hour, data->tm_min, data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);


	static uint32_t lastBlinkTime = 0;
	static int blinkState = 0;
	static int prevBlinkState = -1;

	if(DELAY_GetElapsedMillis(lastBlinkTime) >= 350){
		blinkState ^= 1;  // toggle on/off
		lastBlinkTime = DELAY_GetElapsedMillis(0);  // record new timestamp
	}

	if(changes || blinkState != prevBlinkState){
		if(blinkState == 0){ // hide selected field
			switch(BlinkField){
				case 0: buf[0] = buf[1] = ' '; break;               			//horas
				case 1: buf[3] = buf[4] = ' '; break;               			//minutos
				case 2: buf[6] = buf[7] = ' '; break;               			//dias
				case 3: buf[9] = buf[10] = ' '; break;              			//mes
				case 4: buf[12] = buf[13] = buf[14] = buf[15] = ' '; break; 	//ano
			}
		}
		LCDText_Printf("%s", buf);
		prevBlinkState = blinkState;
	}
}


void LCD_Menu_Blink(int BlinkField){
	char buf[20];
	sprintf(buf,"Time    Radio   ");

	static uint32_t lastBlinkTime = 0;
	static int blinkState = 0;
	static int prevBlinkState = -1;

	if(DELAY_GetElapsedMillis(lastBlinkTime) >= 350){
		blinkState ^= 1;  // toggle on/off
		lastBlinkTime = DELAY_GetElapsedMillis(0);  // record new timestamp
	}

	if(blinkState != prevBlinkState){
		if(blinkState == 0){ // hide selected field
			switch(BlinkField){
				case 0: buf[0] = buf[1] = buf[2] = buf[3] = ' '; break;               			//time
				case 1: buf[8] = buf[9] = buf[10] = buf[11] = buf[12] = ' '; break;               			//radio
			}
		}
		LCDText_Printf("Config Menu:\n%s", buf);
		prevBlinkState = blinkState;
	}

}


void LCDVolume_Print(int volume, int mode){
	char bar[20];
	bar[0] = '-';
	for(int i = 1; i < 15; i++)bar[i] = (i - 1 < volume ) ? '|' : ' ';
	bar[15] = '+';
	bar[16] = '\0';

	if(mode == 0)LCDText_Printf("     VOLUME     \n%s", bar);
	if(mode == 1)LCDText_Printf("\n%s", bar);

}



int ValidDate(struct tm* data){
	int year = data->tm_year + 1900;
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(data->tm_mon + 1 == 2){
		if((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))daysInMonth[1] = 29;
	}

	if(data->tm_mday > daysInMonth[data->tm_mon]) return 0;

	return 1;
}


int ChangeTime(struct tm* data ,int field, int a){
	int newVal;
	switch(field){
		case 0:
			newVal = data->tm_hour + (a > 0 ? 1 : -1);
			if(newVal < 0) newVal = 23;
			if(newVal > 23)	newVal = 0;
			data->tm_hour = newVal;
			return 0;

		case 1:
			newVal = data->tm_min + (a > 0 ? 1 : -1);
			if(newVal < 0) 	newVal = 59;
			if(newVal > 59)	newVal = 0;
			data->tm_min = newVal;
			return 0;

		case 2:
			newVal = data->tm_mday + (a > 0 ? 1 : -1);
			if(newVal <= 0) newVal = 31;
			if(newVal > 31)	newVal = 1;
			data->tm_mday = newVal;
			return 0;

		case 3:
			newVal = data->tm_mon + (a > 0 ? 1 : -1);
			if(newVal < 0) 	newVal = 11;
			if(newVal > 11)	newVal = 0;
			data->tm_mon = newVal;
			return 0;

		case 4:
			newVal = data->tm_year + (a > 0 ? 1 : -1);
			if(newVal < 0) 	 newVal = 4095 - 1900;
			if(newVal > 4095)newVal = 0 - 1900;
			data->tm_year = newVal;
			return 0;
	}
	return 0;
}


int NoBtn(void){
	while(NAVBTN_Read() != -1){
		;
	}
	return 0;
}



void Inits(Radio_flash* flash){
    NAVBTN_Init();
    DELAY_Init();
    LCDText_Init();
    //RTC_Init(time(NULL));						//apenas funciona com pc ligago
    RTC_Init(1763396150);

    Radio_flash memory;
    memcpy(&memory, (void*)ADDR_START_SECTOR_29, sizeof(memory));
    if(memory.code == 112){
    	flash->freq = memory.freq;
    	flash->volume = memory.volume;
    }
}


void SetVolume_MODE(int* volume){
	int t_atual = DELAY_GetElapsedMillis(0);
	LCDText_Clear();
	LCDVolume_Print(*volume, 0);

	while(DELAY_GetElapsedMillis(t_atual) <= 2000){
		switch(NAVBTN_Read()){					//Leitura do butão
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
	///

	while(1){
		RTC_GetTimeDate(&now);
		LCD_Time(&now,flash->freq);

		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_UP:						//Aumentar o volume
				if(flash->volume != 14) (flash->volume)++;
				SetVolume_MODE(&flash->volume);
				LCDText_Clear();
				break;

			case NAVBTN_DOWN:					//Baixar o volume
				if(flash->volume != 0) (flash->volume)--;
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
