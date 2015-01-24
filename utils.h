#ifndef UTILS_H

#define UTILS_H

#define ANSI_COLOUR_RED    "\x1b[31m"
#define ANSI_COLOUR_GREEN  "\x1b[32m"
#define ANSI_COLOUR_YELLOW "\x1b[33m"
#define ANSI_COLOUR_RESET  "\x1b[0m"

//#define log_warning(input, ...) fprintf(stderr, "%sWarning%s: %s\n", ANSI_COLOUR_YELLOW, ANSI_COLOUR_RESET,  __VA_ARGS__); 

//#define log_error(input, ...) fprintf(stderr, "%sError%s: %s\n", ANSI_COLOUR_RED, ANSI_COLOUR_RESET, __VA_ARGS__);

#define log_warning(input, ...) fprintf(stdout, "%sWarning: %s" input "\n", ANSI_COLOUR_YELLOW, ANSI_COLOUR_RESET, ##__VA_ARGS__);

#define log_error(input, ...) fprintf(stderr, "%sError: %s" input "\n", ANSI_COLOUR_RED, ANSI_COLOUR_RESET, ##__VA_ARGS__); 

#define log_info(input, ...) fprintf(stdout, "%sInfo: %s" input "\n", ANSI_COLOUR_GREEN, ANSI_COLOUR_RESET, ##__VA_ARGS__);

#endif /* UTILS_H */
