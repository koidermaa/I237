#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/pgmspace.h>
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
    stdout = stdin = &uart0_io;
    stderr = &uart3_out;
    fprintf(stderr, PSTR(VER_FW "\n"),
            PSTR(GIT_DESCR), PSTR(__DATE__), PSTR(__TIME__));
    fprintf(stderr, PSTR(VER_LIBC_GCC "\n"),
            PSTR(__AVR_LIBC_VERSION_STRING__), PSTR(__VERSION__));
    /* End UART0 and UART3 initialize and info print */
    /* Print student name */
    fprintf(stdout, PSTR(STUD_NAME "\n"));
    /* Print ASCII table */
    print_ascii_tbl(stdout);
    /* Create 128 element array */
    unsigned char cArray[128] = {0};

    for (unsigned char i = 0; i < sizeof(cArray); i++) {
        cArray[i] = i;
    }

    print_for_human(stdout, cArray, sizeof(cArray));

    while (1) {
        /* Set pin 3 high to turn LED on */
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);

        char letter;
        fprintf(stdout, PSTR(ENTER_MONTH_NAME));
        fscanf(stdin, "%c", &letter);
        fprintf(stdout, "%c\n", letter);

        /* Check if letter exists and print */
        for (int i = 0; i < 6; i++) {
            if (!strncmp(&letter, (PGM_P)pgm_read_word(&(months[i])), 1)) {
                fprintf(stdout, "%s\n", (PGM_P)pgm_read_word(&(months[i])));
            }
        }

        /* Set pin 3 low to turn LED off */
        PORTA &= ~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
    }
}
