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

#include <time.h>

/**
 * @addtogroup PROJECT_FUNCTIONS
 * @{
 */

/**
 * @defgroup FUNC
 * @brief This module provides functions that are useful in the ui and modes/states of the device
 *
 * @{
 */


/**
 * @brief Check if the date to be saved is valid
 * data date to be set on the RTC
 * return 0 if not valid; 1 if is valid
 */
int ValidDate(struct tm* data);


//Altera os campos da data/hora no modo de configuração
/**
 * @brief fucntion that changes values, used in Time_Config_MODE
 * data tm struct to be changed
 * field select which field is being changed (0-hour, 1-minute, 2-day, 3-month, 4-year)
 * a blink state
 * return ...
 */
int ChangeTime(struct tm* data, int field, int a);


//Função se verifica se existe algum botão pressionado á entrada do modo caso exista fica bliqueado nesse ciclo
/**
 * @brief checks if a button in being pressed when entering a state,
 * to avoid going trough through states when it was not expected
 * return ...
 */
int NoBtn(void);


#endif /* _FUNC_H_ */
