CC=clang
CFLAGS=-g -Wall -Werror -Wunused

lab5: lab5.o
	clang -g -o lab5 lab5.c

clean:
	rm -fr *.o lab5 *.dSYM

dist:
	clang -O3 -o lab5 lab5.c
	strip lab5
