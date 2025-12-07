/**
 * @file radio.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-12-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _RADIO_H_
#define _RADIO_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup _FUNC_functions
 * @brief This module provides functions for using the radio module
 *
 * @{
 */


/**
 * @brief Ativa o Amp e coloca os valores defualt dos registos don radio
 * @param sector
 */
int Radio_Init(void);



int Radio_Write_Word(uint8_t reg, uint16_t data);

int Radio_Read_Word(uint8_t reg, uint16_t* data);

/**
 * @brief altera o registo com os bits pedidos
 * @param sector
 */
int Radio_Write_Bits(uint8_t reg, uint16_t data, int e, int s);



int Radio_SetVolume(int volume);

int Radio_SetFreq(float freq);

int Radio_SHUTDOWN(int on);




#endif /* _RADIO_H_ */
