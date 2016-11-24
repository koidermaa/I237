#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "hmi_msg.h"
#include "print_helper.h"

#define BLINK_DELAY_MS 100

void main (void)
{
    /* Set pin 3 of PORTA for output */
    DDRA |= _BV(DDA3);
    /* Init UART0 and UART3 and print user code info */
    uart0_initialize();
    uart3_initialize();
    stdout = stdin = &uart3_io;
    stderr = &uart3_out;
    fprintf(stderr, "Version: %s built on: %s %s\n",
            GIT_DESCR, __DATE__, __TIME__);
    fprintf(stderr, "avr-libc version: %s avr-gcc version: %s\n", __AVR_LIBC_VERSION_STRING__, __VERSION__);
    /* End UART0 and UART3 initialize and info print */
    /* Print student name */
    fprintf(stdout, "%s\n", STUD_NAME);
    /* Print ASCII table */
    print_ascii_tbl(stdout);

    while (1) {
        /* Set pin 3 high to turn LED on */
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
        /* Set pin 3 low to turn LED off */
        PORTA &= ~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
    }
}
