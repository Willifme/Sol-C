#include "main.h"

int main(int argc, char *argv[]) {
/*
  log_warning("THIS IS A ERROR MESSAGE");

  log_error("THIS IS ANOTHER");

  log_info("This is info");
*/
  // Check if a filename is given.
  
  if (argc == 2) {
  
    FILE *openFile = fopen(argv[1], "r");

    // Checks if the file can be open if not exit with a error
    
    if (!openFile) {

      fprintf(stderr, "Cannot open %s\n", argv[1]);

      return EXIT_FAILURE;

    }

    // Set lex to read from it 
    yyin = openFile;

    // Parse through input until the end of the file has been reached
    do {

      yyparse();
    
    } while (!feof(yyin));

    // I think this is neccessary 

    fclose(openFile);

  } else {

    repl();
    
  }
  
  return 0;
  
}

void repl(void) {

  printf("Welcome to Sol %s type \"quit\" to exit\n", VERSION);
  
  while (1) {

    char *input= readline(">> ");

    /* Check if the length of the input is >= 1 e.g. There is some input then continue
    else go back to the start of the loop and ask for input again */
    
    if (strlen(input) >= 1) {

      add_history(input);

      yy_scan_string(input);

      yyparse();

    } else {

      continue;
      
    }
    
    free(input);

  }
  
}
