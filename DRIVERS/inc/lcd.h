/**
 * @file lcd.h
 * @brief Header of 4-bit alphanumeric LCD driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to initialize
 * and control a 2-line, 16-character alphanumeric LCD in 4-bit mode
 * using the LPC1769 GPIO. The driver allows writing characters, strings,
 * positioning the cursor, clearing the display, and formatted text output
 * similar to printf.
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
#ifndef _LCD_H_
#define _LCD_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup LCD lcd functions
 * @brief Implementa funções para inicialização e controlo de um display LCD alfanumérico em modo 4 bits,
 * utilizando o GPIO do LPC1769, permitindo escrita de caracteres, strings,
 * posicionamento do cursor e limpeza do ecrã e ainda um printf.
 * @{
 */


void LCDGPIO_Init();


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
void LCDText_Printf(char *fmt, ...);

/** @} */ /* end of LCD */
/** @} */ /* end of DRIVERS */

#endif /* _LCD_H_ */
