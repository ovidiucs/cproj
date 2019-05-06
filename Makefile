# Unix makefile for a C program.  Set BinName to program name.

# Definitions.
BinName = llist
Libs = -lc

# Options and arguments to the C compiler.
CC = gcc
#CFLAGS = -g -funsigned-char -W -Wall -ggdb3 -Wunused\
# -Wno-comment -Wno-missing-field-initializers -Wno-missing-braces -Wno-parentheses\
# -Wno-pointer-sign -Wno-unused-parameter -Wno-unused-result $(COPTS)\
# -Og
CFLAGS = -g \
-Og \
-ggdb3 \
-Wall \
-Wno-comment \
-Wno-missing-field-initializers \
-Wno-missing-braces \
-Wno-parentheses \
-Wextra \
-Wcast-align \
-Wcast-qual \
-Wdisabled-optimization \
-Wformat=2 \
-Winit-self \
-Wlogical-op \
-Wmissing-declarations \
-Wmissing-include-dirs \
-Wredundant-decls \
-Wshadow \
-Wsign-conversion \
-Wstrict-overflow=5 \
-Wswitch-default \
-Wundef \
-Wno-unused \


# Targets.
$(BinName): $(BinName).o
	$(CC) $(LDFLAGS) $? $(Libs) -o $(BinName)
#strip	$(BinName)

$(BinName).o: $(BinName).c
	$(CC) $(CFLAGS) -c -o $(BinName).o $?

clean:
	rm -f $(BinName) $(BinName).o
