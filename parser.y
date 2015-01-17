%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"

  /* Note - <stdbool.h> is included in "ast.h" and "lexer.l" for some reason the compiler does not
     like it being included here */

  extern int yylex();

  void yyerror(const char *s);

  //  #define YYSTYPE struct Expression *

  %}

// This allows for good error messages to be called with yyerror();

%error-verbose

%union {

  int integer;

  // I think this causes 6 bytes to be lost! how do I free it?

  char *string;

  bool boolean;

  // VALUE value;

  struct Node *node;

  struct Statement *statement;

  struct Expression *expression;

}

%token <integer> T_INT
%token <string> T_IDENTIFIER T_STRING
%token <value> T_NULL

%token <token> T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token <token> T_QUIT T_FUNC T_IF T_LSQUIGBRACKET T_RSQUIGBRACKET
%token <token> T_RETURN T_COMMA T_COMMENT T_TRUE T_FALSE

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <node> main statements expressions

%type <statement> statement func 

%type <expression> expression operator literal block

%start main

%%

main: expressions
    | statements
| T_QUIT { exit(EXIT_SUCCESS); } // No where better for know. Quit will become a function
    | T_COMMENT  {} // Comments need to be properly fixed however.
    ;

statements: statement { $$ = makeStatementNode($1); printNode($$); deleteNode($$); }
          | statements statement { $$ = makeStatementNode($2); printNode($$); deleteNode($$); }

statement: func
         ;

func: T_FUNC T_IDENTIFIER T_LBRACKET T_RBRACKET block { $$ = makeFuncStatement($5); }
    ;

block: T_LSQUIGBRACKET expression T_RSQUIGBRACKET { $$ = $2; }
     | T_LSQUIGBRACKET expressions expression T_RSQUIGBRACKET { $$ = $3; }
     ;

expressions: expression { $$ = makeExpressionNode($1); printNode($$); deleteNode($$); }
           | expressions expression { $$ = makeExpressionNode($2); printNode($$); deleteNode($$); }
           ;

expression: literal
          | operator 
          // Get this to have expressions between the brackets
          | T_LBRACKET expression T_RBRACKET { $$ = $2; }
          ;

literal: T_INT { $$ = makeIntegerExpression($1); }
       | T_STRING { $$ = makeStringExpression($1); }
       | T_TRUE { $$ = makeBooleanExpression($1); }
       | T_FALSE { $$ = makeBooleanExpression($1); }
       // Assume that null is false
       | T_NULL { $$ = makeBooleanExpression(false); }	
       ;

operator: expression T_PLUS expression { $$ = makeBinaryOperation($1, $3, PLUS); }
        | expression T_MINUS expression { $$ = makeBinaryOperation($1, $3, MINUS); }
        | expression T_TIMES expression { $$ = makeBinaryOperation($1, $3, TIMES); }
        | expression T_DIVIDE expression { $$ = makeBinaryOperation($1, $3, DIVIDE); }
        ;

%%

void yyerror(const char *s) {

  fprintf(stderr, "Error: %s\n", s);

}
