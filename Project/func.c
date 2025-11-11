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




void LCDTime_Print(struct tm* data, int BlinkField){

	LCDText_Printf("%02d:%02d %02d/%02d/%04d",data->tm_hour,data->tm_min,data->tm_mday,data->tm_mon + 1,data->tm_year + 1900);
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
    ///RTC_Init(time(NULL));						//apenas funciona com pc ligago
    //RTC_Init(1762180178);						//independente
    RTC_Init(0);
}



void Operation_MODE(void){
	struct tm now = {0};
	LCDText_Clear();
	LCDText_Printf("INIT cover!");
	DELAY_Milliseconds(1000);
	while(1){

		if(LPC_RTC->ILR & (1 << 0)){			//verificar se house interrupt de incremneto de segundos
			LPC_RTC->ILR |= (1 << 0); 			//clear ao registo de incremento
			RTC_GetTimeDate(&now);
			LCDText_Clear();
			LCDTime_Print(&now, 0);
		 }

		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_UP:						//Aumentar o volume
				LCDText_Clear();
				LCDText_Printf("Volume +");
				DELAY_Milliseconds(1000);
				break;

			case NAVBTN_DOWN:					//Baixar o volume
				LCDText_Clear();
				LCDText_Printf("Volume -");
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
				LCDText_Clear();
				return;

			default:
			    break;
		}

	}
}


int Config_MODE(void){
	int field = 0;
	struct tm saved;							//guarda a hora e data do RTC a posta
	RTC_GetTimeDate(&saved);

	LCDText_Clear();
	LCDText_Printf("CENAS DE HORAS!");
	DELAY_Milliseconds(1000);

	while(1){
		switch(NAVBTN_Read()){					//Leitura do butão
			case NAVBTN_UP:
				ChangeTime(&saved, field, 1);
				break;

			case NAVBTN_DOWN:
				ChangeTime(&saved, field, -1);
				break;

			case NAVBTN_RIGHT:
				field = (field + 1) % 5;
				break;

			case NAVBTN_LEFT:
				field = (field + 4) % 5;
				break;

			case NAVBTN_BACK:
				//não altera registos do RTC
				return 0;

			case NAVBTN_ENTER:
				if(!ValidDate(&saved))return -1;//verificar se saved é valida				//se for uma hora e data válida faz set no RTC
				RTC_SetTimeDate(&saved);					//afeta os registos do RTC com o valor das alterações
				return 1;

			default:
				break;
		}

		LCDText_Clear();
		LCDTime_Print(&saved, 0);								//Blink param!!!!!!!!!!!!!!!
		DELAY_Milliseconds(150);
	}
	return -2;
}


