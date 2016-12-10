#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <util/atomic.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "uart_wrapper.h"
#include "hmi_msg.h"
#include "print_helper.h"
#include "../lib/hd44780_111/hd44780.h"
#include "../lib/andygock_avr-uart/uart.h"

#define BLINK_DELAY_MS 100
#define UART_BAUD 9600
#define COUNT_SECONDS

/* global seconds counter */
volatile uint32_t counter_1;

static inline void init_pins(void)
{
    /* Set pin 3 of PORTA (ARDUINO mega pin 25) for output and set low */
    DDRA |= _BV(DDA3);
    PORTA &= ~_BV(PORTA3);
}


static inline void init_uart(void)
{
    uart0_init(UART_BAUD_SELECT(UART_BAUD, F_CPU));
    uart3_init(UART_BAUD_SELECT(UART_BAUD, F_CPU));
    stderr = &uart3_out;
    stdout = stdin = &uart0_io;
}

static inline void init_lcd(void)
{
    lcd_init();
    lcd_clrscr();
}

static inline void init_counter(void)
{
    counter_1 = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= _BV(WGM12); // Turn on CTC (Clear Timer on Compare)
    TCCR1B |= _BV(CS12); // fCPU/256
    OCR1A = 62549; // Note that it is actually two registers OCR5AH and OCR5AL
    TIMSK1 |= _BV(OCIE1A); // Output compare a match interrupt enable
}

static inline void print_start_data (void)
{
    /* Print version libc and gcc info */
    fprintf_P(stderr, PSTR(VER_FW "\n"),
              GIT_DESCR, __DATE__, __TIME__);
    fprintf_P(stderr, PSTR(VER_LIBC_GCC "\n"),
              __AVR_LIBC_VERSION_STRING__, __VERSION__);
    /* Print student name*/
    fprintf_P(stdout, PSTR(STUD_NAME "\n"));
    /* Display student name in LCD */
    lcd_puts_P(PSTR(STUD_NAME));
    /* Print ASCII maps to CLI */
    print_ascii_tbl(stdout);
    unsigned char cArray[128] = {0};

    for (unsigned char i = 0; i < sizeof(cArray); i++) {
        cArray[i] = i;
    }

    print_for_human(stdout, cArray, sizeof(cArray));
    fprintf_P(stdout, PSTR(ENTER_MONTH_NAME));
}

static inline void find_month (void)
{
    /* Ask user to input first letter of month name */
    char letter;
    fscanf(stdin, "%c", &letter);
    fprintf(stdout, "%c\n", letter);
    /* Try to find month and print to CLI and LCD */
    lcd_clr(0x40, 16);
    lcd_goto(0x40);

    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(&letter, (PGM_P)pgm_read_word(&months[i]), 1)) {
            fprintf_P(stdout, (PGM_P)pgm_read_word(&months[i]));
            fprintf(stdout, "\n");
            lcd_puts_P((PGM_P)pgm_read_word(&months[i]));
            lcd_puts_P(PSTR(" "));
        }
    }
    fprintf_P(stdout, PSTR(ENTER_MONTH_NAME));		
}

static inline void heartbeat(void)
{
    static uint32_t time_y2k_prev;
    uint32_t time_y2k_cpy;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        time_y2k_cpy = counter_1;
    }

    if (time_y2k_cpy != time_y2k_prev) {
        /* Toggle LED in Arduino Mega pin 25 */
        PORTA ^= _BV(PORTA3);
        fprintf_P(stderr, PSTR(LBL_UPTIME": %lu s \n"), time_y2k_cpy);
        time_y2k_prev = time_y2k_cpy;
    }
}

void main (void)
{
    init_pins();
    init_uart();
    init_lcd();
    init_counter();
    sei();
    print_start_data();
    

    while (1) {
        heartbeat();
	if (uart0_available()){	
        find_month();
	}
    }
}


ISR(TIMER1_COMPA_vect)
{
    counter_1++;
}
