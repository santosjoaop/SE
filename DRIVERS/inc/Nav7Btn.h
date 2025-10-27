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
#ifndef _NAV7BTN_H_
#define _NAV7BTN_H_

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup _NAV7BTN_H_functions
 * @brief This module provides functions for controlling _NAV7BTN_H_.
 *
 * @{
 */
#include <stdbool.h>


typedef enum{
	NAVBTN_NONE = -1,
	NAVBTN_UP = 1, NAVBTN_DOWN,
	NAVBTN_LEFT, NAVBTN_RIGHT, NAVBTN_CENTER,
	NAVBTN_BACK, NAVBTN_ENTER
}NAVBTN_TypeDef;


/* Faz a iniciação do sistema para permitir o acesso ao teclado. */
void NAVBTN_Init(void);



/* Lê o teclado e devolve a primeira tecla detetada.
Se nenhuma tecla estiver pressionada, devolve NAVBTN_NONE.
Não é bloqueante. */
NAVBTN_TypeDef NAVBTN_Read(void);


/* Igual a NAVBTN_Read(), mas se a tecla se manteve pressionada entre duas
chamadas consecutivas (não permite a repetição).
Não é bloqueante. */
NAVBTN_TypeDef NAVBTN_Pressed(void);




#endif /* _NAV7BTN_H_ */
