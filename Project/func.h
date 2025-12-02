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



/**
 * @brief Função gene´rica para fazer covers
 * str string para a a cover
 * time tempo em ms a mostrar a cover
 */
void LCD_Cover(char* str, int time);

//Print do ecrã com hora, data e a frequencia atual
void LCD_Time(struct tm* data, float freq);

//função que põe o parametro a ser alterado no momento a piscar
void LCD_Time_Blink(struct tm* data, int BlinkField, int changes);

//print do volume
void LCDVolume_Print(int volume);

//Verifica se a data a ser guardada é válida
int ValidDate(struct tm* data);

//Altera os campos da data/hora no modo de configuração
int ChangeTime(struct tm* data, int field, int a);



void Inits(void);
void SetVolume_MODE(int* volume);
void Operation_MODE(void);
int Menu_MODE(void);
int Config_MODE(void);


#endif /* _FUNC_H_ */
