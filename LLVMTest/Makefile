CC=clang
LD=g++
CFLAGS=`llvm-config --cflags`
LDFLAGS=`llvm-config --libs --cflags --ldflags core analysis executionengine jit interpreter native`



main: main.o
	$(LD) main.o $(LDFLAGS) -o main

main.o: main.c

	$(CC) $(CFLAGS) -c main.c  

clean:
	rm main.o main
