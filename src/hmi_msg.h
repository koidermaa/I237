#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define STUD_NAME "Kristo Oidermaa"
#define ENTER_MONTH_NAME "Enter month name first letter >"
#define VER_FW "Version: %s built on: %s %s"
#define VER_LIBC_GCC "avr-libc version: %s avr-gcc version: %s"
#define LBL_UPTIME "Uptime"

const char month_1[] PROGMEM = "January";
const char month_2[] PROGMEM = "February";
const char month_3[] PROGMEM = "March";
const char month_4[] PROGMEM = "April";
const char month_5[] PROGMEM = "May";
const char month_6[] PROGMEM = "June";

PGM_P const months[] PROGMEM = {month_1, month_2, month_3, month_4, month_5, month_6};

#endif /* _HMI_MSG_H_ */
