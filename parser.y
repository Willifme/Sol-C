%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"
  
  extern int yylex();
  
  void yyerror(const char *s);

%}

%union {

  int ival;

  char *id;

  int token;

}

%token <ival> T_INT

%token T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token T_QUIT T_IDENTIFIER T_FUNC T_IF T_TRUE T_FALSE T_NULL
%token T_RETURN T_COMMA

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <ival> operator

%start main

%%

main:
    expression
    | main expression
    ;

expression:
          operator { printf("Result %i\n", $1); }
          | T_QUIT { exit(EXIT_SUCCESS); }
	    // Get this to have expressions between the brackets
	    // | T_LBRACKET operator T_RBRACKET { $$ = $2; }
	  ;

operator: T_INT { $$ = $1; }
          | operator T_PLUS operator { $$ = $1 + $3; }
          | operator T_MINUS operator { $$ = $1 - $3; }
          | operator T_TIMES operator { $$ = $1 * $3; }
          | operator T_DIVIDE operator { $$ = $1 / $3; }
          | T_LBRACKET operator T_RBRACKET { $$ = $2; }
          ;

%%

void yyerror(const char *s) {

  fprintf(stderr, "Error: %s\n", s);

  exit(EXIT_FAILURE);
  
}
