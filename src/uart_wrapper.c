#include <avr/io.h>
#include <stdio.h>
#include "../lib/andygock_avr-uart/uart.h"

#define UART_STATUS_MASK 0x00FF


int uart0_putchar(char c, FILE *stream)
{
    (void) stream;

    if (c == '\n') {
        uart0_putchar('\r', stream);
        
    }

    uart0_putc((uint8_t) c);
    return 0;
}

int uart3_putchar(char c, FILE *stream)
{
    (void) stream;

    /*Add windows line endings*/
    if (c == '\n') {
        uart3_putchar('\r', stream);
      
    }

    uart3_putc((uint8_t) c);
    return 0;
}

int uart0_getchar(FILE *stream)
{
    (void) stream;

    /*add error handling*/
    while (uart0_peek() == UART_NO_DATA);

    /*mask out status in int high byte*/
    return (uart0_getc() & UART_STATUS_MASK);
}
