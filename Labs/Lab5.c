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


/*Features/Problems
 *
 *Init como deve ser 2
 * Screen flicker 2
 * Weekdays initials 3
 * Only change different value 2
 * Substituir DELAY por alarme 1 				DONE
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
    RTC_Init(time(NULL));						//apenas funciona com pc ligago
    ///RTC_Init(1762180178);						//independente
    struct tm now = {0};

    while(1){
    	if(LPC_RTC->ILR & (1 << 0)){			//verificar se house interrupt de incremneto de segundos
    		LPC_RTC->ILR |= (1 << 0); 			//clear ao registo de incremento
			RTC_GetTimeDate(&now);
			LCDText_Clear();
			LCDTime_Print(now);
    	}
    }

    return 0;
}
