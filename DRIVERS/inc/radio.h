/**
 * @file radio.h
 * @brief Header of FM radio driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to control
 * an FM radio module through the I2C interface of the LPC1769. The driver
 * allows configuration of the radio registers, frequency tuning, volume
 * control and power state management of the device.
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
#ifndef _RADIO_H_
#define _RADIO_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup RADIO Radio functions
 * @brief Implementa um driver para controlo de um módulo de rádio FM,
 * baseado em comunicação I2C no LPC1769, permitindo a configuração de frequência,
 * volume e estado de funcionamento do dispositivo.
 * @{
 */


/**
 * @brief Ativa o Amp e coloca os valores defualt dos registos do radio
 */
int Radio_Init(void);


/**
 * @brief Permite escrever os 16 bits no registo escolhido, no rádio
 * @param reg valor de registo pretendido
 * @param data dados a escrever no registo, 16 bits
 */
int Radio_Write_Word(uint8_t reg, uint16_t data);

/**
 * @brief Permite ler os 16 bits no registo escolhido, no rádio
 * @param reg valor de registo pretendido
 * @param data variavel a gaurdar os dados lidos a partir do registo, 16 bits
 */
int Radio_Read_Word(uint8_t reg, uint16_t* data);

/**
 * @brief alterar apenas o bits entre "e" e "s" no regsito selecionado, com o valor em data
 * @param reg valor de registo pretendido
 * @param data dados a escrever no registo, 16 bits
 * @param e bit final
 * @param s bit incial
 */
int Radio_Write_Bits(uint8_t reg, uint16_t data, int e, int s);


/**
 * @brief Permite alterar o volume do rádio,
 * sendo que quando o volume é 0 o DAC é desligado
 * @param volume valor de volume pretendido de 0 a 14
 */
int Radio_SetVolume(int volume);

/**
 * @brief Permite alterar a frequencia do rádio
 * @param freq valor de frequencia pretendido, de 76MHz a 108MHz
 */
int Radio_SetFreq(float freq);

/**
 * @brief Ativa e desativa o DAC do rádio
 */
int Radio_SHUTDOWN(int on);

/** @} */ /* end of RADIO */
/** @} */ /* end of DRIVERS */

#endif /* _RADIO_H_ */
