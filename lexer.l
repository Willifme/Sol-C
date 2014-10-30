%{

#include <stdio.h>
// This has to be included so that the parser does not complain
#include <stdbool.h>
#include "parser.tab.h"

#define YY_DECL extern int yylex()

#define TOKEN(t) (yylval.integer = t)

%}

%option noyywrap

%option yylineno

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

"true" { yylval.boolean = yytext ? "true" : "false"; return T_TRUE; }

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

"//"{ANYTHING}+ { return TOKEN(T_COMMENT); }

"/*" { BEGIN(COMMENT); }

<INITIAL>{

  "/*"  BEGIN(COMMENT);

}

<COMMENT>{

  "*/"  BEGIN(INITIAL);

  [^*\n]+ // Eat the rest of the comment

  "*" // Eat the last start

  \n return TOKEN(T_COMMENT);


}

[ \t\n]+ { yylineno += 1; }

. { printf("Unrecognised character \"%s\" at line %d\n", yytext, yylineno); yyterminate(); }

%%
