#include "main.h"

int main(int argc, char *argv[]) {

  parserState state = { NULL, 0 };

  // Check if a filename is given.
  
  if (argc > 1) {

	yyin = fopen(argv[1], "r");

	state.sourceFile = strdup(argv[1]);

	yyparse(&state);

  } else {

	repl();

  }

  fclose(yyin);

  free(&state.sourceFile);

  free(&state);

  return 0;
  
}

void repl(void) {

  parserState state = { NULL, 0 };

  printf("Welcome to Sol %s type \"quit\" to exit\n", VERSION);
  
  while (1) {

    char *input= readline(">> ");

    state.sourceFile = "repl";

    /* Check if the length of the input is >= 1 e.g. There is some input then continue
    else go back to the start of the loop and ask for input again */
    
    if (strlen(input) >= 1) {

      add_history(input);

      yy_scan_string(input);

      yyparse(&state);

    } else {

      continue;
      
    }
    
    free(input);

//	free(&state);

  }
  
}
