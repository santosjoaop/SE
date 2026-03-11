/**
 * @file modes.h
 * @brief Header of application operation modes for the LPC1769 project.
 *
 * This file contains the declarations of the functions used to manage
 * the different operation modes of the application. It includes peripheral
 * initialization, date/time configuration, radio frequency and volume
 * control, user interaction via buttons, LCD updates, and Flash memory
 * read/write operations.
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
#ifndef _MODES_H_
#define _MODES_H_

/**
 * @addtogroup PROJECT_FUNCTIONS
 * @{
 */

/**
 * @defgroup MODES
 * @brief Implementa os modos de operação da aplicação,
 * incluindo inicialização de periféricos, configuração de hora, frequência e volume,
 * interação com o utilizador via botões,
 * atualizações de LCD e armazenamento/leitura de dados na memória Flash.
 *
 * @{
 */
#include <time.h>


#define ADDR_START_SECTOR_29 0x00078000

typedef struct {
		int code;
		int volume;
		float freq;
}Radio_flash;


/**
 * @brief Inits dos vários DRIVERS e verificar os valores da flash
 * @param flash
 */
void Inits(Radio_flash* flash);

/**
 * @brief Põe o volume no rádio
 * @param volume
 */
void SetVolume_MODE(int* volume);

/**
 * @brief Modo de funcionamento normal
 * @param flash
 */
void Operation_MODE(Radio_flash* flash);

/**
 * @brief Modo de Menu
 */
int Menu_MODE(void);

/**
 * @brief Modo de configuração de data e hora
 */
int Time_Config_MODE(void);

/**
 * @brief Modo da memória do rádio
 */
int Radio_Config_MODE(void);


#endif /* _MODES_H_ */
