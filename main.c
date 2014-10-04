#include "main.h"
#include "ast.h"

int main(int argc, char *argv[]) {

  Node node = {1};

  printf("%d\n", node.value);

  node.Hello();
  
  if (argc == 2) {
  
    FILE *openFile = fopen(argv[1], "r");

    if (!openFile) {

      printf("Cannot open %sl\n", argv[1]);

      return EXIT_FAILURE;

    }

    // Set lex to read from it 
    yyin = openFile;

    // Parse through input until there is no more
    do {

      yyparse();
    
    } while (!feof(yyin));

  } else {

    repl();
    
  }
  
  return 0;
  
}

void repl(void) {

  printf("Welcome to Sol %s type \"quit\" to exit\n", VERSION);
  
  while (1) {

    char *input= readline(">> ");

    add_history(input);

    yy_scan_string(input);

    yyparse();
      
    free(input);

  }
  
}
