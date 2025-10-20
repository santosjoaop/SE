/**
 * @file lcd.h
 * @author G2-LT51D
 * @brief Headers of fucntions
 *
 * @version 1.0
 * @date 2025-10-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _LCD_H_
#define _LCD_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup LCD Lcd functions
 * @brief This module provides functions for controlling LCD.
 *
 * @{
 */
#include <stdbool.h>


void LCDGPIO_Init(int start, int last);

static void LCDText_WriteNibble(bool rs, uint8_t value);

static void LCDText_WriteByte(int rs, unsigned char value);





/**
 * @brief  Faz a iniciação do sistema para permitir o acesso ao periférico LCD de 2 linhas e 16 colunas,
com interface a 4 bits.
 */
void LCDText_Init(void);


/**
 * @brief Escreve um caracter na posição corrente do cursor.
 * @param ch
 */
void LCDText_WriteChar(char ch);


/**
 * @brief Escreve uma string na posição corrente do cursor.
 * @param str
 */
void LCDText_WriteString(char *str);


/**
 * @brief Posiciona o cursor na linha row e coluna column do mostrador.
 * @param row
 * @param column
 */
void LCDText_SetCursor(int row, int column);


/**
 * @brief Limpa o visor, usando o comando disponível na API do periférico.
 */
void LCDText_Clear(void);


/**
 * @brief Opcional: Escreve na posição corrente do cursor a string fmt.
O formato da string fmt é idêntico à função printf da biblioteca standard da linguagem C.
 * @param fmt
 * @param ...
 *
 */
//void LCDText_Printf(char *fmt, ...);


#endif /* _LCD_H_ */
