/**
 * @file func.h
 * @brief Header of auxiliary application logic functions for the LPC1769 project.
 *
 * This file contains declarations of helper functions for managing date and time,
 * handling button inputs, and controlling application features such as the radio
 * and persistent storage.
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
#ifndef _FUNC_H_
#define _FUNC_H_

#include <time.h>

/**
 * @addtogroup PROJECT_FUNCTIONS
 * @{
 */

/**
 * @defgroup FUNC
 * @brief Implementa funções auxiliares de lógica da aplicação,
 * suportando a gestão de data e hora, interação com botões e controlo de funcionalidades como rádio e armazenamento.
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
