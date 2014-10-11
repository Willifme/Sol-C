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

{NUMBER}+ { yylval.ival = atoi(yytext); return T_INT; }

"quit" { return T_QUIT; }

"func" { return T_FUNC; }

"if" { return T_IF; }

"true" { return T_TRUE; }

"false" { return T_FALSE; }

"null" { return T_NULL; }

"return" { return T_RETURN; }

 /* Always put this rule after anykeywords / anything that matches this regex */
[a-zA-Z\x80-\xf3]+ { yylval.ival = atoi(&yytext[0]); return T_IDENTIFIER; }

"+" { return T_PLUS; }

"-" { return T_MINUS; } // 10 seconds

"*" { return T_TIMES; }

"/" { return T_DIVIDE; }

"(" { return T_LBRACKET; }

")" { return T_RBRACKET; }

[ \t\n]  

. { printf("Unrecognised character \"%s\" at line %d\n", yytext, yylineno); yyterminate(); }

%%
