/*
 * rtc.c
 *
 *  Created on: 31/10/2025
 *      Author: diogo
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "rtc.h"




#define PCGPIO (1 << 15)
#define PCRTC (1 << 9)
#define GPIO_FUNC 12
#define P022 22





void RTC_Init(time_t seconds){
	//Ativar o clock do RTC
	LPC_SC->PCONP |= PCRTC;

	//Convert seconds em struct tm e afetar cada registo com o respetivo campo
	struct tm* tm_date = localtime(&seconds);
	LPC_RTC -> SEC = tm_date -> tm_sec;
	LPC_RTC -> MIN = tm_date -> tm_min;
	LPC_RTC -> HOUR = tm_date -> tm_hour;
	LPC_RTC -> DOM = tm_date -> tm_mday;
	LPC_RTC -> DOW = tm_date -> tm_wday;
	LPC_RTC -> DOY = tm_date -> tm_yday;
	LPC_RTC -> MONTH = tm_date -> tm_mon;
	LPC_RTC -> YEAR = (tm_date -> tm_year) + 1900;
}



void RTC_GetTimeDate(struct tm *dateTime){
	dateTime -> tm_sec = LPC_RTC -> SEC;
	dateTime -> tm_min = LPC_RTC -> MIN;
	dateTime -> tm_hour = LPC_RTC -> HOUR;
	dateTime -> tm_mday = LPC_RTC -> DOM;
	dateTime -> tm_wday = LPC_RTC -> DOW;
	dateTime -> tm_yday = LPC_RTC -> DOY;
	dateTime -> tm_mon = LPC_RTC -> MONTH;
	dateTime -> tm_year = (LPC_RTC -> YEAR) - 1900;
}


void RTC_SetTimeDate(struct tm *dateTime){
	LPC_RTC -> SEC = dateTime -> tm_sec;
	LPC_RTC -> MIN = dateTime -> tm_min;
	LPC_RTC -> HOUR = dateTime -> tm_hour;
	LPC_RTC -> DOM = dateTime -> tm_mday;
	LPC_RTC -> DOW = dateTime -> tm_wday;
	LPC_RTC -> DOY = dateTime -> tm_yday;
	LPC_RTC -> MONTH = dateTime -> tm_mon;
	LPC_RTC -> YEAR = (dateTime -> tm_year) + 1900;

}


void RTC_SetSeconds(time_t seconds);


time_t RTC_GetSeconds(void){
	time_t now;
	mktime();

	return now;
}
