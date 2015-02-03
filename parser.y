%{

#ifndef PARSER_H

#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "utils.h"

extern int yylex();

void yyerror(const char *s);

%}

// This allows for good error messages to be called with yyerror();

%error-verbose

%union {

  int integer;

  // I think this causes 6 bytes to be lost! how do I free it?

  char *string;

  bool boolean;

  struct Node *node;

//  struct Types *type;

  struct Argument *argument;

  Types type;

  //enum AstNodeType type;
	
  // struct Statement *statement;

  // struct Expression *expression;

}

%token <integer> T_INT
%token <string> T_IDENTIFIER T_STRING
%token <boolean> T_FALSE T_TRUE

%token <token> T_PLUS T_MINUS T_TIMES T_DIVIDE T_LBRACKET T_RBRACKET
%token <token> T_QUIT T_FUNC T_IF T_LSQUIGBRACKET T_RSQUIGBRACKET
%token <token> T_RETURN T_COMMA T_COMMENT T_NULL T_COLON T_TYPESTRING

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <node> main expressions expression operator literal func block 
%type <type> types

%start main

%%

main: expressions
    | T_QUIT { exit(EXIT_SUCCESS); } // No where better for know. Quit will become a function
    | T_COMMENT  {} // Comments need to be properly fixed however.
    ;

expressions: expression { $$ = $1; printNode($$); deleteNode($$); }
           | expressions expression { $$ = $2; printNode($$); deleteNode($$); }
           ;

expression: literal
          | operator 
		  | func
          // Get this to have expressions between the brackets
          | T_LBRACKET expression T_RBRACKET { $$ = $2; }
          ;

func: T_FUNC T_IDENTIFIER T_LBRACKET T_RBRACKET block { $$ = makeFuncDeclaration($2, $5); }
	| T_FUNC T_IDENTIFIER T_LBRACKET T_IDENTIFIER T_COLON types T_RBRACKET block { $$ = makeFuncDeclarationWithArgs($2, makeArgument($4, $6), $8); }
    ;

block: T_LSQUIGBRACKET expression T_RSQUIGBRACKET { $$ = makeBlock($2); }
     | T_LSQUIGBRACKET expressions expression T_RSQUIGBRACKET { $$ = makeBlock($3); }
     ;


literal: T_INT { $$ = makeInteger($1); }
       | T_STRING { $$ = makeString($1); }
       | T_TRUE { $$ = makeBoolean($1); }
       | T_FALSE { $$ = makeBoolean($1); }
       // Assume that null is false
       | T_NULL { $$ = makeBoolean(false); }	
       ;

operator: expression T_PLUS expression { $$ = makeBinaryOperation($1, $3, PLUS); }
        | expression T_MINUS expression { $$ = makeBinaryOperation($1, $3, MINUS); }
        | expression T_TIMES expression { $$ = makeBinaryOperation($1, $3, TIMES); }
        | expression T_DIVIDE expression { $$ = makeBinaryOperation($1, $3, DIVIDE); }
        ;

types: T_TYPESTRING { $$ = TYPE_STRING; }
	 ;

%%

void yyerror(const char *s) {

	log_error("%s at line", s);

}

#endif /* PARSER_H */
