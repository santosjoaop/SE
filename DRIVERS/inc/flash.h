/**
 * @file flash.h
 * @brief Header of Flash memory driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to erase,
 * write and verify data in the internal Flash memory of the LPC1769,
 * using the IAP (In-Application Programming) routines.
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
#ifndef _FLASH_H_
#define _FLASH_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup FLASH Flash functions
 * @brief Implementa funções para apagar, escrever e verificar dados na memória Flash interna do LPC1769,
 * recorrendo às rotinas IAP (In-Application Programming).
 * @{
 */


/**
 * @brief Apaga o conteúdo de um sector.
 * @param sector
 */
unsigned int FLASH_EraseSector(unsigned int sector);


/**
 * @brief Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes,
 * no endereço da flash referenciado por dstAddr.
 * @param dstAddr
 * @param srcAddr
 * @param size Number of bytes to be written. Should be 256 | 512 | 1024 | 4096
 */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);


/**
 * @brief Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size bytes,
 * com o conteúdo do bloco de dados referenciado por dstAddr.
 * @param dstAddr
 * @param srcAddr
 * @param size Number of bytes to be compared. Should be a multiple of 4.
 */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

/** @} */ /* end of FLASH */
/** @} */ /* end of DRIVERS */

#endif /* _FLASH_H_ */
