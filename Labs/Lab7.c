/**
 * @file Lab7.c
 * @author Grupo 2
 * @brief
 * @version 1.0
 * @date 2025-11-16
 *
 * @copyright Copyright (c) 2025
 * 
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "lcd.h"
#include "delay.h"
#include "flash.h"


#define ADDR_START_SECTOR_29 0x00078000
#define ADDR_END_SECTOR_29 0x0007FFFF


int main(void) {
    printf("Hello World\n");

    DELAY_Init();
    LCDText_Init();

    FLASH_EraseSector(29);

    int group = 2;
    char name1[20] = "Freixo";
    char name2[20] = "Santos";

    ///CUIDADO "Should be 256 | 512 | 1024 | 4096"
    FLASH_WriteData((void*)ADDR_START_SECTOR_29, &group , sizeof(group));

    ///CUIDADO "Number of bytes to be compared; should be a multiple of 4"
    FLASH_VerifyData((void*)ADDR_START_SECTOR_29, &group , sizeof(group));

    LCDText_Printf("Grupo:%d\n%s %s", group, name1, name2);

}
