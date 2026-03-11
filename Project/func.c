/**
 * @file func.c
 * @brief Implementation of auxiliary application logic functions for the LPC1769 project.
 *
 * This file contains helper functions for managing date and time, handling
 * button input, and controlling application features such as radio and
 * persistent storage.
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
#include <stdio.h>
#include <string.h>


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
	while(NAVBTN_Read() != -1){continue;}
	return 0;
}

