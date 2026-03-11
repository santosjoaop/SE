/**
 * @file led.h
 * @brief Header of LED2 [PIN 0.22] driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to initialize,
 * turn on, turn off, toggle and get the state of LED2.
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
#ifndef _LED_H_
#define _LED_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup LED Led functions
 * @brief This module provides core functions for creating time delays in the
 *        program, allowing precise waits in both milliseconds and microseconds.
 *
 *        The functions use SYSTICK millisecond delays and TIMER0 for
 *        microsecond delays.
 * @{
 */



/**
 * @brief  Initializes all the registers and things to use LED2
 * @param state state that the LED turns on, true-on, false-off
 */
void LED_Init(void);

/**
 * @brief  Diz o estado do LED
 * @return false if LED is off, true if LED is ON
 */
int LED_GetState(void);

/**
 * @brief Liga o LED
 */
void LED_On(void);

/**
 * @brief Desliga o LED
 */
void LED_Off(void);

/**
 * @brief Comuta o LED
 */
void LED_Toggle(void);

/** @} */ /* end of LED */
/** @} */ /* end of DRIVERS */

#endif /* _LED_H_ */
