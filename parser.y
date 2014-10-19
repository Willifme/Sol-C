%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"
  
  extern int yylex();
  
  void yyerror(const char *s);

//  #define YYSTYPE struct Expression * 

%}

%error-verbose

%union {

  int ival;

  int token;

  char *id;

  const char *string;

  struct Expression *expression;

}

%token <ival> T_INT
%token <string> T_IDENTIFIER

%token <token> T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token <token> T_QUIT T_FUNC T_IF T_TRUE T_FALSE T_NULL
%token <token> T_RETURN T_COMMA T_COMMENT T_DOUBLEQOUTE

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <expression> operator expression string

%start main

%%

main: expression { printExpression($1); deleteExpression($1); }
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

string: T_DOUBLEQOUTE T_IDENTIFIER T_DOUBLEQOUTE { $$ = makeString($2); }
      ;

operator: T_INT {  $$ = makeInt($1); }
          | operator T_PLUS operator { $$ = makeBinaryOperation($1, $3, PLUS); }
          | operator T_MINUS operator { $$ = makeBinaryOperation($1, $3, MINUS); }
          | operator T_TIMES operator { $$ = makeBinaryOperation($1, $3, TIMES); }
          | operator T_DIVIDE operator { $$ = makeBinaryOperation($1, $3, DIVIDE); }
//| T_LBRACKET operator T_RBRACKET { $$ = $2; }
          ;

%%

void yyerror(const char *s) {

  fprintf(stderr, "Error: %s\n", s);

  exit(EXIT_FAILURE);
  
}
