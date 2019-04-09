CC=clang
CFLAGS=-I.

mygrep:
	clang -o mygrep mygrep.c
clean:
	rm mygrep
