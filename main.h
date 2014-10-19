#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

#ifdef __APPLE__

// OSX does not have history.h and does not need it
#include <editline/readline.h>

#else

// However other OS's don't
#include <editline/readline.h>
#include <editline/history.h>

#endif

#define VERSION "0.0.1"

extern int yyparse();

extern int yy_scan_string(const char *s);
  
extern FILE *yyin;

void repl(void);
