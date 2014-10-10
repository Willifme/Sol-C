%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"
  
  extern int yylex();
  
  void yyerror(const char *s);

  //#define YYSTYPE Node * 

%}

%union {

  int ival;

  char *id;

  struct Node *node;

}

//%token <ival> T_INT

%token T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token T_QUIT T_IDENTIFIER T_FUNC T_IF T_TRUE T_FALSE T_NULL
%token T_RETURN T_COMMA T_INT

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <node> operator expression

%start main

%%

main: 
    expression {  }
| main expression { deleteNode($2); }
    ;

expression:
operator { printNode($1);  }
          | T_QUIT { exit(EXIT_SUCCESS); }
	    // Get this to have expressions between the brackets
	    // | T_LBRACKET operator T_RBRACKET { $$ = $2; }
	  ;

operator: T_INT { $$ = makeInt(1); }
          | operator T_PLUS operator { $$ =  makeBinaryOperator($1, $3, PLUS); }
          | operator T_MINUS operator { $$ = makeBinaryOperator($1, $3, MINUS); }
          | operator T_TIMES operator { $$ =  makeBinaryOperator($1, $3, TIMES); }
          | operator T_DIVIDE operator { $$ =  makeBinaryOperator($1, $3, DIVIDE); }
          | T_LBRACKET operator T_RBRACKET { $$ = $2; }
          ;

%%

void yyerror(const char *s) {

  fprintf(stderr, "Error: %s\n", s);

  exit(EXIT_FAILURE);
  
}
