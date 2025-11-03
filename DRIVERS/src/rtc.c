/**
 * @file led.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "rtc.h"
#include <stdio.h>
#include <time.h>



#define PCRTC (1 << 9)

#define MASK_SECONDS 0x3F  	//0b0011 1111
#define MASK_MINUTES 0x3F	//0b0011 1111
#define MASK_HOURS   0x1F	//0b0001 1111
#define MASK_DAYS    0x1F	//0b0001 1111
#define MASK_MONTHS  0x0F	//0b0000 1111
#define MASK_YEARS   0xFFF	//0b1111 1111 1111



void RTC_Init(time_t seconds){//XXX
	//Ativar o clock do RTC
	LPC_SC->PCONP |= PCRTC;

	LPC_RTC->CIIR = (1 << 0);											//Ativar enable de incrementos de segundo
	LPC_RTC->ILR  = 0x01;

	//REGISTO NÂO QUERO ALARMES ETC

	RTC_SetSeconds(seconds);
}



struct tm* RTC_GetTimeDate(struct tm *dateTime){
	uint32_t clock = LPC_RTC -> CTIME0;									//ACESSOS À MEMORIA
	uint32_t date = LPC_RTC -> CTIME1;

	dateTime -> tm_sec  = ((clock >> 0) & MASK_SECONDS);
	dateTime -> tm_min  = ((clock >> 8) & MASK_MINUTES);
	dateTime -> tm_hour = ((clock >> 16) & MASK_HOURS);

	dateTime -> tm_mday = ((date >> 0) & MASK_DAYS);
	dateTime -> tm_mon  = ((date >> 8) & MASK_MONTHS) - 1;
	dateTime -> tm_year = ((date >> 16) & MASK_YEARS) - 1900;

	dateTime -> tm_wday = 0;										//PARA PREVENIR ERRROS COM mkdir ???
	dateTime -> tm_yday = 0;
	dateTime -> tm_isdst = 0;

	return dateTime;
}



void RTC_SetTimeDate(struct tm *dateTime){
	LPC_RTC -> CCR = 0;									//Para o relogio

	LPC_RTC -> SEC = dateTime -> tm_sec;
	LPC_RTC -> MIN = dateTime -> tm_min;
	LPC_RTC -> HOUR = dateTime -> tm_hour;
	LPC_RTC -> DOM = dateTime -> tm_mday;
	LPC_RTC -> DOW = dateTime -> tm_wday;
	LPC_RTC -> DOY = (dateTime -> tm_yday) + 1;			//Ajustes de strcut tm para o LPC
	LPC_RTC -> MONTH = (dateTime -> tm_mon) + 1;		//
	LPC_RTC -> YEAR = (dateTime -> tm_year) + 1900;		//

	LPC_RTC -> CCR = 1;									//Arranca o relogio
}



void RTC_SetSeconds(time_t seconds){
	struct tm* Datetime = localtime(&seconds);
	RTC_SetTimeDate(Datetime);
}



time_t RTC_GetSeconds(void){
	struct tm dateTime;
	return mktime(RTC_GetTimeDate(&dateTime));
}
