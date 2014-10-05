%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"
  
  extern int yylex();
  
  void yyerror(const char *s);

  #define YYSTYPE struct Node *

%}

//%union {

//  int ival;

//  char *id;

//  int token;

//  Node node;

//}

//%token <ival> T_INT

%token T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token T_QUIT T_IDENTIFIER T_FUNC T_IF T_TRUE T_FALSE T_NULL
%token T_RETURN T_COMMA T_INT

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

 //%type <node> operator

%start main

%%

main:
    expression
    | main expression
    ;

expression:
          operator { printTree($1); printf("\n");}
          | T_QUIT { exit(EXIT_SUCCESS); }
	    // Get this to have expressions between the brackets
	    // | T_LBRACKET operator T_RBRACKET { $$ = $2; }
	  ;

operator: T_INT { $$ = makeNode(0, 0, "hello"); }
          | operator T_PLUS operator { $$ =  makeNode($1, $3, "+"); }
          | operator T_MINUS operator { $$ = makeNode($1, $3, "-"); }
          | operator T_TIMES operator { $$ =  makeNode($1, $3, "*"); }
          | operator T_DIVIDE operator { $$ =  makeNode($1, $1, "/"); }
          | T_LBRACKET operator T_RBRACKET { $$ = $2; }
          ;

%%

void yyerror(const char *s) {

  fprintf(stderr, "Error: %s\n", s);

  exit(EXIT_FAILURE);
  
}
