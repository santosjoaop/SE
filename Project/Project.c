/**
 * @file Project.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-11-10
 *
 * @copyright Copyright (c) 2025
 * 
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Nav7Btn.h"
#include "delay.h"
#include "lcd.h"
#include "rtc.h"
#include "func.h"




int main(void) {
    printf("Hello World\n");

    Inits();
    while(1){
    	Operation_MODE();
    	//Menu_MODE
    	Config_MODE();
    }

    return 0;
}
