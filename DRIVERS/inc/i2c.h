/**
 * @file i2c.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-11-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _I2C_H_
#define _I2C_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup _FUNC_functions
 * @brief This module provides functions for using i2c protocol.
 *
 * @{
 */


/**
 * @brief Faz a iniciação do controlador e configura os respetivos pinos.
Propoe-se a utilização do I2C0
 */
void I2CMASTER_Init(void);

/**
 * @brief Configura o ritmo de envio/receção.
 * @param frequency ritmo em Hz
 */
void I2CMASTER_SetFrequency(int frequency);

/**
 * @brief Realiza a transmissão dos dados referenciados por data com dimensão size bytes
para o dispositivo com o endereço devAddress. Retorna sucesso ou o erro ocorrido.
 * @param devAddress
 * @param data
 * @param size
 */
int I2CMASTER_Transmit(unsigned char devAddress, void *data, unsigned int size);

/**
 * @brief Realiza a receçao dos dados do dispositivo com o endereço devAddress,
para o endereço referenciado por data num maximo de size bytes.
Retorna o número de bytes recebidos ou o erro ocorrido.
 * @param devAddress
 * @param data
 * @param size
 */
int I2CMASTER_Receive(unsigned char devAddress, void *data, unsigned int size);


#endif /* _I2C_ */
