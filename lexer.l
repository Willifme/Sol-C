%{

#ifndef LEXER_H

#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include "ast.h"
#include "parser.tab.h"
#include "utils.h"

#define YY_DECL int yylex(YYSTYPE *yylval, parserState *state)

#define TOKEN(id) return id

#define KEYWORD(id) return id

%}

%option noyywrap

%option yylineno

%option nounput

%option noinput

%x COMMENT

NUMBER [+-]?[0-9](_[0-9][0-9])*

%%

quit { KEYWORD(T_QUIT); }

func { KEYWORD(T_FUNC); }

if { KEYWORD(T_IF); }

true { yylval->boolean = atoi(yytext); KEYWORD(T_TRUE); }

false { yylval->boolean = atoi(yytext); KEYWORD(T_FALSE); }

null { KEYWORD(T_NULL); }

return { KEYWORD(T_RETURN); }

String { KEYWORD(T_TYPESTRING); }

Int { KEYWORD(T_TYPEINT); }

Char { KEYWORD(T_TYPECHAR); }

Bool { KEYWORD(T_TYPEBOOL); }

{NUMBER}+ { yylval->integer = atoi(yytext); TOKEN(T_INT); }

 /* Always put this rule after any keywords or anything that matches this regex */
[a-zA-Z0-9\x80-\xf3_]+ { yylval->string = strndup(yytext, yyleng); return T_IDENTIFIER; }

 /* This should parse single and double qouted strings */
\"([^"]|\\.)*\" { yylval->string = yytext; return T_STRING; }

\'([^']|\\.)*\' { yylval->string = yytext; return T_STRING; }

"+" { TOKEN(T_PLUS); }

"-" { TOKEN(T_MINUS); } // 10 seconds

"*" { TOKEN(T_TIMES); }

"/" { TOKEN(T_DIVIDE); }

"(" { TOKEN(T_LBRACKET); }

")" { TOKEN(T_RBRACKET); }

"{" { TOKEN(T_LSQUIGBRACKET); }

"}" { TOKEN(T_RSQUIGBRACKET); }

":" { TOKEN(T_COLON); }

[\t ] {}

\n {}

. { log_error("Unrecognised character \"%s\" at line %d", yytext, yylineno);  yyterminate(); }

%%

/*
"//"{ANYTHING}+ { TOKEN(T_COMMENT); }

"" { BEGIN(COMMENT); }

<COMMENT>"" { BEGIN(INITIAL); }

<COMMENT>{ANYTHING} { TOKEN(T_COMMENT); }

*/
#endif /* LEXER_L */
