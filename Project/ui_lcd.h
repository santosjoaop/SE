/**
 * @file ui_lcd.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _UI_LCD_H_
#define _UI_LCD_H_

#include <time.h>

/**
 * @addtogroup PROJECT_FUNCTIONS
 * @{
 */

/**
 * @defgroup UI_LCD
 * @brief This module provides functions for the UI of the device
 *
 * @{
 */


/**
 * @brief display a string on the LCD for an amount of time
 * str string
 * time ammount of time in ms that the cover is shown
 */
void LCD_Cover(char* str, int time);


/**
 * @brief LCD print to use on Operation_MODE, shows the time and the fequency being played
 * data tm struct with the time
 * freq frequency being played
 */
void LCD_Time(struct tm* data, float freq);


/**
 * @brief LCD print that actually makes the parameters change when setting up the time/data
 * BlinkField select which field is blinking (0-hour, 1-minute, 2-day, 3-month, 4-year)
 * changes ???
 */
void LCD_Time_Blink(struct tm* data, int BlinkField, int changes);


/**
 * @brief LCD print that shows the MENU, the selected parameter blinks
 * BlinkField select which field is blinking (0-time/date configr, 1-radio config)
 */
void LCD_Menu_Blink(int BlinkField);


/**
 * @brief LCD print that shows the volume
 * volume number of bars shown, from 0 to 14 values
 * mode 0 to use of Operation_MODE; 1 to use of Radio_Config_MODE
 */
void LCDVolume_Print(int volume, int mode);


#endif /* _UI_LCD_H_ */
