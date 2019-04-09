# Unix makefile for a C program.  Set BinName to program name.

# Definitions.
BinName = mygrep
Libs = -lc

# Options and arguments to the C compiler.
CC = cc
CFLAGS = -funsigned-char -W -Wall -Wunused\
 -Wno-bitwise-op-parentheses -Wno-comment -Wno-missing-field-initializers -Wno-missing-braces -Wno-parentheses\
 -Wno-pointer-sign -Wno-unused-parameter -Wno-unused-result $(COPTS)\
 -O2

# Targets.
$(BinName): $(BinName).o
	$(CC) $(LDFLAGS) $? $(Libs) -o $(BinName)
	strip $(BinName)

$(BinName).o: $(BinName).c
	$(CC) $(CFLAGS) -c -o $(BinName).o $?

clean:
	rm -f $(BinName) $(BinName).o
