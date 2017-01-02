#include "../lib/andygock_avr-uart/uart.h"
#include <stdio.h>

#define UART_STATUS_MASK 0x00FF

int uart0_putchar(char c, FILE *stream)
{
    (void) stream;

    if (c == '\n') {
        uart0_putc('\r');
        uart0_putc('\n');
        return 0;
    }

    uart0_putc((uint8_t) c);
    return 0;
}


int uart3_putchar(char c, FILE *stream)
{
    (void) stream;

    /*Add windows line endings*/
    if (c == '\n') {
        uart3_putc('\r');
        uart3_putc('\n');
        return 0;
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

FILE uart0_io = FDEV_SETUP_STREAM(uart0_putchar, uart0_getchar, _FDEV_SETUP_RW);
FILE uart3_out = FDEV_SETUP_STREAM(uart3_putchar, NULL, _FDEV_SETUP_WRITE);
