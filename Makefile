SRC=main.c lex.yy.c parser.tab.c ast.c
CFLAGS=-o lexer
LIBS= -ledit

all: sol
	./lexer

sol: ${SRC}
	clang ${SRC} ${LIBS} ${CFLAGS}

lex.yy.c:
	flex lexer.l

parser.tab.c:
	bison -d parser.y
clean:
	rm -rf lexer lex.yy.c parser.tab.c parser.tab.h
