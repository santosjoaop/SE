/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
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


int main(void){

    printf("Hello World\n");

    LCDText_Init(void);
    time_t now = time(NULL);
    RTC_Init(now);

    while(1){

    	void LCDText_Printf("%d:%d:%d %d/%d",	LPC_RTC -> HOUR, LPC_RTC -> MIN, LPC_RTC -> SEC
    											LPC_RTC -> DAY, LPC_RTC -> MON);
    	DELAY_Milliseconds(1000);


    }

    return 0;
}
