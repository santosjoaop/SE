/**
 * @file i2c.h
 * @brief Header of I2C master driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to control
 * the I2C0 peripheral of the LPC1769 in master mode. The driver allows
 * communication with I2C slave devices, providing functions to initialize
 * the peripheral, set the bus frequency, and perform data transmission
 * and reception.
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
#ifndef _I2C_H_
#define _I2C_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup I2C i2c functions
 * @brief Implementa um driver I2C em modo master para o periférico I2C0 do LPC1769,~
 * permitindo a transmissão e receção de dados com dispositivos periféricos através do barramento I2C.
 * @{
 */


/**
 * @brief Faz a iniciação do controlador e configura os respetivos pinos.
 * Propoe-se a utilização do I2C0
 */
void I2CMASTER_Init(void);

/**
 * @brief Configura o ritmo de envio/receção.
 * @param frequency ritmo em Hz
 */
void I2CMASTER_SetFrequency(int frequency);

/**
 * @brief Realiza a transmissão dos dados referenciados por data com dimensão size bytes
 * para o dispositivo com o endereço devAddress. Retorna sucesso ou o erro ocorrido.
 * @param devAddress
 * @param data
 * @param size
 * @return
 */
int I2CMASTER_Transmit(unsigned char devAddress, void *data, unsigned int size);

/**
 * @brief Realiza a receçao dos dados do dispositivo com o endereço devAddress,
 * para o endereço referenciado por data num maximo de size bytes.
 * Retorna o número de bytes recebidos ou o erro ocorrido.
 * @param devAddress
 * @param data
 * @param size
 * @return
 */
int I2CMASTER_Receive(unsigned char devAddress, void *data, unsigned int size);

/** @} */ /* end of I2C */
/** @} */ /* end of DRIVERS */

#endif /* _I2C_ */
