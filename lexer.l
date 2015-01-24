%{

#ifndef LEXER_H

#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include "parser.tab.h"
#include "utils.h"

#define TOKEN(t) (yylval.integer = t)

%}

%option noyywrap

%option yylineno

%option nounput

%option noinput

%x COMMENT

NUMBER [0-9]

DOUBLEQOUTE \"

SINGLEQOUTE \'

ANYTHING [^(\"|')]

%%

{NUMBER}+ { yylval.integer = atoi(yytext); return T_INT; }

"quit" { return TOKEN(T_QUIT); }

"func" { return TOKEN(T_FUNC); }

"if" { return TOKEN(T_IF); }

"true" { yylval.boolean = atoi(yytext); return T_TRUE; }

"false" { yylval.boolean = atoi(yytext); return T_FALSE; }

"null" { return TOKEN(T_NULL); }

"return" { return TOKEN(T_RETURN); }

 /* Always put this rule after any keywords or anything that matches this regex */
[a-zA-Z\x80-\xf3]+ { yylval.string = strndup(yytext, yyleng); return T_IDENTIFIER; }

{DOUBLEQOUTE}{ANYTHING}*{DOUBLEQOUTE} { yylval.string = yytext; return T_STRING; }

{SINGLEQOUTE}{ANYTHING}*{SINGLEQOUTE} { yylval.string = yytext; return T_STRING; }

"+" { return TOKEN(T_PLUS); }

"-" { return TOKEN(T_MINUS); } // 10 seconds

"*" { return TOKEN(T_TIMES); }

"/" { return TOKEN(T_DIVIDE); }

"(" { return TOKEN(T_LBRACKET); }

")" { return TOKEN(T_RBRACKET); }

"{" { return TOKEN(T_LSQUIGBRACKET); }

"}" { return TOKEN(T_RSQUIGBRACKET); }

"//"{ANYTHING}+ { return TOKEN(T_COMMENT); }

"/*" { BEGIN(COMMENT); }

<COMMENT>"*/" { BEGIN(INITIAL); }

<COMMENT>{ANYTHING} { return TOKEN(T_COMMENT); }

[ \t\n]+ {  }

. { log_error("Unrecognised character \"%s\" at line %d", yytext, yylineno);  yyterminate(); }

%%

#endif /* LEXER_L */
