%{

#include <stdio.h>

#include "parser.tab.h"

#define YY_DECL extern int yylex()

#define TOKEN(t) (yylval = t)

%}

%option noyywrap

%option yylineno

NUMBER [0-9]

%%

{NUMBER}+ { yylval = atoi(yytext); return T_INT; }

"quit" { return TOKEN(T_QUIT); }

"func" { return TOKEN(T_FUNC); }

"if" { return TOKEN(T_IF); }

"true" { return TOKEN(T_TRUE); }

"false" { return TOKEN(T_FALSE); }

"null" { return TOKEN(T_NULL); }

"return" { return TOKEN(T_RETURN); }

 /* Always put this rule after anykeywords / anything that matches this regex */
[a-zA-Z]+ { yylval = atoi(&yytext[0]); return T_IDENTIFIER; }

"+" { return TOKEN(T_PLUS); }

"-" { return TOKEN(T_MINUS); } // 10 seconds

"*" { return TOKEN(T_TIMES); }

"/" { return TOKEN(T_DIVIDE); }

"(" { return TOKEN(T_LBRACKET); }

")" { return TOKEN(T_RBRACKET); }

[ \t\n]  

. { printf("Unrecognised character \"%s\" at line %d\n", yytext, yylineno); yyterminate(); }

%%
