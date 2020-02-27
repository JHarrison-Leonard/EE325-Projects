#ifndef SERIALIO_H_
#define SERIALIO_H_
#include <stdio.h>

FILE out_UART;
FILE in_UART;

void initialize_UART();

void putchar_UART(char c, FILE * stream);

char getchar_UART(FILE * stream);

#endif
