#ifndef MAIN_H

#define MAIN_H

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "ast.h"
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

extern int yyparse(parserState *state);

extern int yy_scan_string(const char *s);
  
extern FILE *yyin;

void repl(void);

#endif /* MAIN_H */
