/*   Copyright 2017 Kristo Oidermaa

    This file is part of I237 homework project

    I237 homework is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    I237 homework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with I237 homework.  If not, see <http://www.gnu.org/licenses/>.

*/

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
const char read_cmd[] PROGMEM = READ_CMD;
const char read_help[] PROGMEM = READ_HELP;
const char add_cmd[] PROGMEM = ADD_CMD;
const char add_help[] PROGMEM = ADD_HELP;
const char remove_cmd[] PROGMEM = REMOVE_CMD;
const char remove_help[] PROGMEM = REMOVE_HELP;
const char list_cmd[] PROGMEM = LIST_CMD;
const char list_help[] PROGMEM = LIST_HELP;
const char mem_cmd[] PROGMEM = MEM_CMD;
const char mem_help[] PROGMEM = MEM_HELP;

