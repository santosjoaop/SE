/**
 * @file delay.h
 * @brief Header of delay and timing functions for the LPC1769.
 *
 * This file contains the declarations of the functions used to create
 * precise delays in milliseconds and microseconds. The delay functions
 * use the SysTick timer to generate millisecond delays and Timer2 to
 * generate microsecond delays.
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
#ifndef _DELAY_H_
#define _DELAY_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup DELAY Delay functions
 * @brief This module provides core functions for creating time delays in the
 *        program, allowing precise waits in both milliseconds and microseconds.
 *
 *        The functions use SYSTICK millisecond delays and TIMER0 for
 *        microsecond delays.
 * @{
 */


/**
 * @brief  Initializes the delay API to provide 1 ms resolution delays.
 * @return 0 if initialization is successful; -1 if initialization fails.
 * @note   This function must be called before using any other DELAY functions.
 *         It sets up the SYSTICK timer to create accurate 1 ms resolution delays.
 */
int DELAY_Init(void);

/**
 * @brief  Waits for a specified number of milliseconds.
 * @param  millis The number of milliseconds to wait.
 * @note   This function relies on the SYSTICK timer to create accurate delays.
 */
void DELAY_Milliseconds(uint32_t millis);

/**
 * @brief  Retrieves the elapsed time in milliseconds since a given start time.
 * @param  start The start time in milliseconds, or 0 to get the current time.
 * @return The elapsed time in milliseconds since the provided start time.
 */
uint32_t DELAY_GetElapsedMillis(uint32_t start);


/**
 * @brief Waits for a specified number of microseconds.
 * @param waitUs The number of microseconds to wait.
 * @note This fucntion relies on TIMER2.
 */
void DELAY_Microseconds(uint32_t waitUs);

/** @} */ /* end of DELAY */
/** @} */ /* end of DRIVERS */

#endif /* _DELAY_H_ */
