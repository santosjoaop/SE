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
#include <stdio.h>




void LCDTime_Print(struct tm* data, int BlinkField, int changes){
	char buf[20];
	sprintf(buf,"%02d:%02d %02d/%02d/%04d", data->tm_hour, data->tm_min, data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);

	if(BlinkField < 0){
		LCDText_Clear();
		LCDText_Printf("%s", buf);
	}
	else{
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
}


void LCDVolume_Print(int volume){
	char bar[20];
	bar[0] = '-';
	for(int i = 1; i < 15; i++)bar[i] = (i - 1 < volume ) ? '|' : ' ';
	bar[15] = '+';
	bar[16] = '\0';

	LCDText_Printf("     VOLUME     \n%s", bar);
}

int ValidDate(struct tm* data){
	int year = data->tm_year + 1900;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(data->tm_mon + 1 == 2){
		if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) daysInMonth[1] = 29;
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






void Inits(void){
    NAVBTN_Init();
    DELAY_Init();
    LCDText_Init();
    RTC_Init(time(NULL));						//apenas funciona com pc ligago
    //RTC_Init(1762180178);						//independente
}

/*
void SetVolume_MODE(int *volume){
	int t_atual = DELAY_GetElapsedMillis(0);

	switch(NAVBTN_Read()){					//Leitura do butão
		case NAVBTN_UP:						//Aumentar o volume
			t_atual = DELAY_GetElapsedMillis(0);
			if(*volume != 14) *volume++;
			LCDVolume_Print(*volume);
			DELAY_Milliseconds(1000);
			break;

		case NAVBTN_DOWN:					//Baixar o volume
			t_atual = DELAY_GetElapsedMillis(0);
			if(*volume != 0) *volume--;
			LCDVolume_Print(*volume);
			DELAY_Milliseconds(1000);
			break;

		default:
			if(DELAY_GetElapsedMillis(t_atual) <= 2000) return;

	}
}*/



void Operation_MODE(void){
	struct tm now = {0};
	int volume = 0;
	while(1){
		if(LPC_RTC->ILR & (1 << 0)){			//verificar se house interrupt de incremneto de segundos
			LPC_RTC->ILR |= (1 << 0); 			//clear ao registo de incremento
			RTC_GetTimeDate(&now);
			LCDTime_Print(&now, -1, 0);
		 }

		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_UP:						//Aumentar o volume
				LCDText_Clear();
				if(volume != 14) volume++;
				LCDVolume_Print(volume);
				DELAY_Milliseconds(1000);
				break;

			case NAVBTN_DOWN:					//Baixar o volume
				LCDText_Clear();
				if(volume != 0) volume--;
				LCDVolume_Print(volume);
				DELAY_Milliseconds(1000);
				break;

			case NAVBTN_RIGHT:					//Aumentar a frequencia
				LCDText_Clear();
				LCDText_Printf("Freq +");
				DELAY_Milliseconds(1000);
				break;

			case NAVBTN_LEFT:					//Baixar a frequencia
				LCDText_Clear();
				LCDText_Printf("Freq -");
				DELAY_Milliseconds(1000);
				break;

			case NAVBTN_ENTER:					//Sair do Operation_MODE, irá entrar no Config_MODE
				return;

			default:
			    break;
		}

	}
}


int Menu_MODE(void){
	LCDText_Clear();
	LCDText_Printf("MENU:\nTime    Radio");
	DELAY_Milliseconds(3000);
	return 0;
}




int Config_MODE(void){
	int field = 0;								//campo a ser alterado
	int changed = 0;
	struct tm saved;
	RTC_GetTimeDate(&saved);					//guarda uma cópia de RTC atual numa struct tm


	LCDText_Clear();
	LCDTime_Print(&saved, field, 0);


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

			case NAVBTN_RIGHT:
				field = (field + 1) % 5;
				changed = 1;
				break;

			case NAVBTN_LEFT:
				field = (field + 4) % 5;
				changed = 1;
				break;

			case NAVBTN_BACK:
				//não altera registos do RTC
				return 0;

			case NAVBTN_ENTER:
				if(!ValidDate(&saved))return -1;			//verificar se saved é valida				//se for uma hora e data válida faz set no RTC
				RTC_SetTimeDate(&saved);					//afeta os registos do RTC com o valor das alterações
				return 1;

			default:
				changed = 0;
				break;
		}
		LCDTime_Print(&saved, field, changed);		//só vai haver um novo print se houver alteração de campos
		DELAY_Milliseconds(50);
	}
	return -2;
}
