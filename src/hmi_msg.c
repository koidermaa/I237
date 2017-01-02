#include <avr/pgmspace.h>
#include "hmi_msg.h"

static const char month_1[] PROGMEM = "January";
static const char month_2[] PROGMEM = "February";
static const char month_3[] PROGMEM = "March";
static const char month_4[] PROGMEM = "April";
static const char month_5[] PROGMEM = "May";
static const char month_6[] PROGMEM = "June";

PGM_P const months[] PROGMEM = {month_1, month_2, month_3, month_4, month_5, month_6};

const char help_cmd[] PROGMEM = HELP_CMD;
const char help_help[] PROGMEM = HELP_HELP;
const char ver_cmd[] PROGMEM = VER_CMD;
const char ver_help[] PROGMEM = VER_HELP;
const char ascii_cmd[] PROGMEM = ASCII_CMD;
const char ascii_help[] PROGMEM = ASCII_HELP;
const char month_cmd[] PROGMEM = MONTH_CMD;
const char month_help[] PROGMEM = MONTH_HELP;

