%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"

  extern int yylex();

  void yyerror(const char *s);

//  #define YYSTYPE struct Expression *

%}

// This allows for good error messages to be called with the error function

%error-verbose

%union {

  int integer;

  char *string;

  struct Expression *expression;

}

%token <integer> T_INT
%token <string> T_IDENTIFIER T_STRING

%token <token> T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token <token> T_QUIT T_FUNC T_IF T_TRUE T_FALSE T_NULL
%token <token> T_RETURN T_COMMA T_COMMENT T_SINGLEQOUTE

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <expression> expression operator string

%start main

%%

main: expression { makeNode($1); printExpression($1); deleteExpression($1); }
    | statement
    | main expression { printExpression($2); deleteExpression($2); }
    | main statement
    ;

statement: T_QUIT { exit(EXIT_SUCCESS); }
         | T_COMMENT
         ;

expression: operator
          | string
            // Get this to have expressions between the brackets
	        | T_LBRACKET expression T_RBRACKET { $$ = $2; }
          ;

string: T_STRING { $$ = makeStringExpression($1); }
      ;

operator: T_INT { $$ = makeIntegerExpression($1); }
          | operator T_PLUS operator { $$ = makeBinaryOperation($1, $3, PLUS); }
          | operator T_MINUS operator { $$ = makeBinaryOperation($1, $3, MINUS); }
          | operator T_TIMES operator { $$ = makeBinaryOperation($1, $3, TIMES); }
          | operator T_DIVIDE operator { $$ = makeBinaryOperation($1, $3, DIVIDE); }
          ;

%%

void yyerror(const char *s) {

  fprintf(stderr, "Error: %s\n", s);

  exit(EXIT_FAILURE);

}
