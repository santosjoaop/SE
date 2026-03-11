/**
 * @file Nav7Btn.h
 * @brief Header of 7-button navigation keypad driver for the LPC1769.
 *
 * This file contains the declarations of the functions used to interface
 * with a 7-button matrix keypad. It allows initialization of the keypad
 * and reading of button presses in a non-blocking manner.
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
#ifndef _NAV7BTN_H_
#define _NAV7BTN_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup NAV7BTN Nav7Btn functions
 * @brief Implementa funções para a utilização do teclado matricial de 7 botões.
 * @{
 */


typedef enum{
	NAVBTN_NONE = -1,
	NAVBTN_UP = 1,
	NAVBTN_LEFT,
	NAVBTN_CENTER,
	NAVBTN_RIGHT,
	NAVBTN_DOWN,
	NAVBTN_BACK,
	NAVBTN_ENTER
}NAVBTN_TypeDef;


/**
 * @brief Faz a iniciação do sistema para permitir o acesso ao teclado.
 */
void NAVBTN_Init(void);


/**
 * @brief Lê o teclado e devolve a primeira tecla detetada.
Se nenhuma tecla estiver pressionada, devolve NAVBTN_NONE.
Não é bloqueante.
 * @return inteiro com número do botão pressionado
 */
NAVBTN_TypeDef NAVBTN_Read(void);


/**
 * @brief Igual a NAVBTN_Read(), mas se a tecla se manteve pressionada entre duas
chamadas consecutivas (não permite a repetição).
Não é bloqueante.
 * @return inteiro com número do botão pressionado
 */
NAVBTN_TypeDef NAVBTN_Pressed(void);

/** @} */ /* end of NAV7BTN */
/** @} */ /* end of DRIVERS */

#endif /* _NAV7BTN_H_ */
