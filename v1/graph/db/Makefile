# Unix makefile for a C program.  Set BinName to program name.

# Definitions.
BinName = sqltest
Libs = -lc -lsqlite3 -lreadline

# Options and arguments to the C compiler.
CC = clang
#CFLAGS = -g -funsigned-char -W -Wall -ggdb3 -Wunused\
# -Wno-comment -Wno-missing-field-initializers -Wno-missing-braces -Wno-parentheses\
# -Wno-pointer-sign -Wno-unused-parameter -Wno-unused-result $(COPTS)\
# -Og
CFLAGS = -g \
-Og \
-Wall \
-Werror \
-Wextra \
-Wno-comment \
-Wno-missing-field-initializers \
-Wno-missing-braces \
-Wno-unused \
-Wundef \
-Wmissing-include-dirs \
-Wmissing-declarations \
-Wmissing-prototypes \
-Wstrict-selector-match \
-Wundeclared-selector \
-Woverlength-strings \
-Wimplicit-atomic-properties \
-Wformat=2 \
-Wno-parentheses \
-Wcast-align \
-Wcast-qual \
-Wfloat-equal \
-Wdisabled-optimization \
-Winit-self \
-Wredundant-decls \
-Wshadow \
-Wsign-conversion \
-Wstrict-overflow=5 \
-Wstrict-prototypes \
-Wswitch-default \
-Wunreachable-code \


# Targets.
$(BinName): $(BinName).o
	$(CC) $(LDFLAGS) $? $(Libs) -o $(BinName)
#strip	$(BinName)

$(BinName).o: $(BinName).c
	$(CC) $(CFLAGS) -c -o $(BinName).o $?

clean:
	rm -f $(BinName) $(BinName).o
