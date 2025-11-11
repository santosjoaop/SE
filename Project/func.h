/**
 * @file func.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _FUNC_H_
#define _FUNC_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup _FUNC_functions
 * @brief This module provides functions for controlling _NAV7BTN_H_.
 *
 * @{
 */
#include <stdbool.h>



void LCDTime_Print(struct tm data);

int ChangeTime(struct tm* data ,int field, int a);



void Inits(void);

void Operation_MODE(void);

void Config_MODE(void);


#endif /* _NAV7BTN_H_ */
