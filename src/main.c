#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "hmi_msg.h"
#include "print_helper.h"
#include "../lib/hd44780_111/hd44780.h"

#define BLINK_DELAY_MS 100

void main (void)
{
    /* Set pin 3 of PORTA for output */
    DDRA |= _BV(DDA3);
    /* Init error console in stderr in UART3 and print version libc and gcc info */
    uart3_initialize();
    stderr = &uart3_out;
    fprintf(stderr, PSTR(VER_FW "\n"),
            PSTR(GIT_DESCR), PSTR(__DATE__), PSTR(__TIME__));
    fprintf(stderr, PSTR(VER_LIBC_GCC "\n"),
            PSTR(__AVR_LIBC_VERSION_STRING__), PSTR(__VERSION__));
    /* Init CLI in UART0 and print sudent name */
    uart0_initialize();
    stdout = stdin = &uart0_io;
    fprintf(stdout, PSTR(STUD_NAME "\n"));
    /* Init LCD and display student name */
    lcd_init();
    lcd_clrscr();
    lcd_puts_P(PSTR(STUD_NAME));
    
    /* Print ASCII maps to CLI */
    print_ascii_tbl(stdout);
    unsigned char cArray[128] = {0};
    for (unsigned char i = 0; i < sizeof(cArray); i++) {
        cArray[i] = i;
    }
    print_for_human(stdout, cArray, sizeof(cArray));

    while (1) {
        /* Set pin 3 high to turn LED on */
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);

        /* Ask user to input first letter of month name */
        char letter;
        fprintf(stdout, PSTR(ENTER_MONTH_NAME));
        fscanf(stdin, "%c", &letter);
        fprintf(stdout, "%c\n", letter);

        /* Try to find month and print to CLI and LCD */
        lcd_goto(0x40);
        for (int i = 0; i < 6; i++) {
            if (!strncmp(&letter, (PGM_P)pgm_read_word(&(months[i])), 1)) {
                fprintf(stdout, "%s\n", (PGM_P)pgm_read_word(&(months[i])));
                lcd_puts_P((PGM_P)pgm_read_word(&(months[i])));
            }
            /*apply no match clear LCD row 2???*/
        }

        /* Set pin 3 low to turn LED off */
        PORTA &= ~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
    }
}
