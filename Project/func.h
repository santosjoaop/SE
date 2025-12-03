/**
 * @file func.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _FUNC_H_
#define _FUNC_H_

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
#include <time.h>


#define ADDR_START_SECTOR_29 0x00078000

typedef struct {
		int code;
		int volume;
		float freq;
}Radio_flash;

/**
 * @brief Função generica para fazer covers
 * str string para a a cover
 * time tempo em ms a mostrar a cover
 */
void LCD_Cover(char* str, int time);

//Print do ecrã com hora, data e a frequencia atual
void LCD_Time(struct tm* data, float freq);

//função que põe o parametro a ser alterado no momento a piscar
void LCD_Time_Blink(struct tm* data, int BlinkField, int changes);


void LCD_Menu_Blink(int BlinkField);

//print do volume
void LCDVolume_Print(int volume);

//Verifica se a data a ser guardada é válida
int ValidDate(struct tm* data);

//Altera os campos da data/hora no modo de configuração
int ChangeTime(struct tm* data, int field, int a);



void Inits(Radio_flash* flash);
void SetVolume_MODE(int* volume);
void Operation_MODE(Radio_flash* flash);
int Menu_MODE(void);
int Time_Config_MODE(void);
int Radio_Config_MODE();


#endif /* _FUNC_H_ */
