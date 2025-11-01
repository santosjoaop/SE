/**
 * @file Lab5.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-10-19
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
#include "delay.h"
#include "lcd.h"
#include "rtc.h"


/* Features/Problems
 *
 * INIT COMO DEVE SER CARALHO
 * Screen flicker
 * Weekdays initials
 * Only change different value
 * Substituir DELAY por alarme
 * */


//int weekday_string(int wday);		//Strings com as inicias dos dias da semana


void LCDTime_Print(struct tm data){
	LCDText_Printf("    %02d:%02d:%02d    \n", data.tm_hour,data.tm_min,data.tm_sec);
	LCDText_Printf("   %02d/%02d/%04d   ", data.tm_mday, data.tm_mon + 1, data.tm_year + 1900);
}



int main(void) {
    printf("Hello World\n");

    DELAY_Init();

    LCDText_Init();

    RTC_Init(time(NULL));
    struct tm now = {0};

    while(1){
        RTC_GetTimeDate(&now);

        LCDText_Clear();
        LCDTime_Print(now);

        DELAY_Milliseconds(1000);				//USAR ALARM RTC SECONDS???
    }

    return 0;
}
