/**
 * @file rtc.h
 * @brief Header of Real-Time Clock (RTC) driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to initialize
 * and control the Real-Time Clock (RTC), allowing the user to set and obtain
 * the current date and time, as well as convert between seconds since the
 * Epoch and the struct tm representation.
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
#ifndef _RTC_H_
#define _RTC_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup RTC rtc functions
 * @brief Implementa funções para inicialização e controlo do Real-Time Clock (RTC),
 * permitindo definir e obter a data e hora,
 * bem como converter entre segundos desde o Epoch e a estrutura tm.
 * @{
 */
#include <time.h>



/**
 * @brief Faz a iniciação do RTC. O RTC é iniciado com o valor do parâmetro seconds desde Epoch
 * @param seconds usado para set time
 */
void RTC_Init(time_t seconds);


/**
 * @brief Devolve em dateTime o valor corrente do RTC. Usa o CTIME0 e CTIME1
 * @param dateTime
 * @return struct tm* igual ao valor pasado em param
 */
struct tm* RTC_GetTimeDate(struct tm *dateTime);


/**
 * @brief Realiza a atualização do RTC com os valores do parâmetro dateTime.
 * @param dateTime
 */
void RTC_SetTimeDate(struct tm *dateTime);


/**
 * @brief Realiza a atualização do RTC com o valor do parâmetro seconds, segundos desde Epoch
 * @param seconds
 */
void RTC_SetSeconds(time_t seconds);


/**
 * @brief Retorna o valor corrente do RTC, em segundos desde Epoch
 * @return time_t
 */
time_t RTC_GetSeconds(void);

/** @} */ /* end of RTC */
/** @} */ /* end of DRIVERS */

#endif /* _RTC_H_ */
