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
#include "../lib/helius_microrl/microrl.h"
#include "../lib/matejx_avr_lib/mfrc522.h"
#include "cli_microrl.h"

#define UART_BAUD 9600

// Create microrl object and pointer on it
static microrl_t rl;
static microrl_t *prl = &rl;

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


static inline void init_cli(void)
{
    // Call init with ptr to microrl instance and print callback
    microrl_init (prl, cli_print);
    // Set callback for execute
    microrl_set_execute_callback (prl, cli_execute);
}


static inline void init_rfid_reader(void)
{
    MFRC522_init();
    PCD_Init();
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


static inline void print_start_data(void)
{
    /* Print version libc and gcc info */
    fprintf_P(stderr, PSTR(VER_FW "\n"));
    fprintf_P(stderr, PSTR(VER_LIBC_GCC "\n"));
    /* Print student name*/
    fprintf_P(stdout, PSTR(STUD_NAME "\n"));
    /* Display student name in LCD */
    lcd_puts_P(PSTR(STUD_NAME));
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
        fprintf_P(stderr, PSTR(LBL_UPTIME": %lu s\n"), time_y2k_cpy);
        time_y2k_prev = time_y2k_cpy;
    }
}


void main(void)
{
    init_pins();
    init_uart();
    init_lcd();
    init_counter();
    sei();
    print_start_data();
    init_cli();
    init_rfid_reader();

    while (1) {
        heartbeat();
        microrl_insert_char (prl, cli_get_char());
    }
}


ISR(TIMER1_COMPA_vect)
{
    counter_1++;
}
