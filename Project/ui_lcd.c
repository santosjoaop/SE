/**
 * @file ui_lcd.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "delay.h"
#include "lcd.h"
#include "ui_lcd.h"
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

