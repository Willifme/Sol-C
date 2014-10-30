SRC=main.c ast.c lex.yy.c parser.tab.c
CFLAGS=-o lexer
LIBS= -ledit

all: sol
	./lexer ${ARGS}

sol: ${SRC}
	clang ${SRC} ${LIBS} ${CFLAGS}

lex.yy.c:
	flex -8 lexer.l

parser.tab.c:
	bison -d parser.y

parsergraph:
	bison parser.y --graph

clean:
	rm -rf lexer lex.yy.c parser.tab.c parser.tab.h
