/**
 * @file flash.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _FLASH_H_
#define _FLASH_H_

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


/* Apaga o conteúdo de um sector. */
unsigned int FLASH_EraseSector(unsigned int sector);


/* Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes,
no endereço da flash referenciado por dstAddr. */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);


/* Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size bytes,
com o conteúdo do bloco de dados referenciado por dstAddr. */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);






#endif /* _FLASH_H_ */
