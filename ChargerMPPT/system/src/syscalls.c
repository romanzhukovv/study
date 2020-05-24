/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        syscalls.c                                                       *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        01.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       System functions for standart library                            *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/********************************************************************************
 * Declaration for external functiom output symbol in UART
 ********************************************************************************/

extern int uart_putc (const char ch);

/********************************************************************************
 * Standard function output printf
 ********************************************************************************/

int _write_r (struct _reent *r, int file, char * ptr, int len) {  

    r = r;
    file = file;
    ptr = ptr;

    int index;
  
    for(index=0; index<len; index++) {

        if (ptr[index] == '\n') { uart_putc('\r'); }  
        uart_putc(ptr[index]);
    }  
 
    return len;
}