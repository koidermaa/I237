#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define STUD_NAME "Kristo Oidermaa"
#define VER_FW "Version: " GIT_DESCR " built on: " __DATE__" "__TIME__
#define VER_LIBC_GCC "avr-libc version: " __AVR_LIBC_VERSION_STRING__ " avr-gcc version: " __VERSION__
#define LBL_UPTIME "Uptime"
#define CLI_HELP_MSG "Implemented commands:"
#define PRT_CMD_ERR "Command not implemented.\n Use <help> to get help."
#define PRT_ARG_ERR "To few or too many arguments for this command\nUse <help>"
#define HELP_CMD "help"
#define HELP_HELP "Get help"
#define VER_CMD "version"
#define VER_HELP "Print FW version"
#define ASCII_CMD "ascii"
#define ASCII_HELP "print ASCII tables"
#define MONTH_CMD "month"
#define MONTH_HELP "Find matching month from lookup list. Usage: month <string>"
#define READ_CMD "read"
#define READ_HELP "Read card and print card data"
#define ADD_CMD "add"
#define ADD_HELP "Add a new card with username. Usage: add <string>"
#define REMOVE_CMD "remove"
#define REMOVE_HELP "Remove a card"
#define LIST_CMD "list"
#define LIST_HELP "Print all cards"
#define MEM_CMD "memory"
#define MEM_HELP "Show memory usage"

#define CARD_SELECTED_MSG "Card selected!"
#define UID_SIZE_MSG "UID size: 0x%02X"
#define UID_SAK_MSG "UID sak: 0x%02X"
#define CARD_UID_MSG "Card UID: "
#define CARD_NOT_SELECTED "Unable to select card"
#define MEM_FAIL_MSG "Memory operation failed"


extern PGM_P const months[];

extern const char help_cmd[];
extern const char help_help[];
extern const char ver_cmd[];
extern const char ver_help[];
extern const char ascii_cmd[];
extern const char ascii_help[];
extern const char month_cmd[];
extern const char month_help[];
extern const char read_cmd[];
extern const char read_help[];
extern const char add_cmd[];
extern const char add_help[];
extern const char remove_cmd[];
extern const char remove_help[];
extern const char list_cmd[];
extern const char list_help[];
extern const char mem_cmd[];
extern const char mem_help[];


#endif /* _HMI_MSG_H_ */
