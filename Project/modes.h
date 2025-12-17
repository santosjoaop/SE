/**
 * @file modes.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _MODES_H_
#define _MODES_H_

/**
 * @addtogroup PROJECT_FUNCTIONS
 * @{
 */

/**
 * @defgroup MODES
 * @brief This module provides modes/states to use on the device
 *
 * @{
 */
#include <time.h>


#define ADDR_START_SECTOR_29 0x00078000

typedef struct {
		int code;
		int volume;
		float freq;
}Radio_flash;


void Inits(Radio_flash* flash);
void SetVolume_MODE(int* volume);
void Operation_MODE(Radio_flash* flash);
int Menu_MODE(void);
int Time_Config_MODE(void);
int Radio_Config_MODE();


#endif /* _MODES_H_ */
