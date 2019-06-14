# Unix makefile for ProLib.		Ver. 1.3.0

# Definitions.
LibName = mylib.a
SrcDir = ../src
ObjDir = ../obj
ObjFiles =\
 $(ObjDir)/prime.o \
 $(ObjDir)/hash.o 
 
 
InclDir = ../include

# Options and arguments to the C compiler.
CC = cc
CFLAGS = -funsigned-char -W -Wall -Wunused\
 -Wno-comment -Wno-missing-field-initializers -Wno-missing-braces -Wno-pointer-sign -Wno-unused-parameter -O2 -I$(InclDir)

$(LibName): $(ObjFiles)
	-[ -f $(LibName) ] && rm $(LibName)
	@echo 'ar r $(LibName) $(ObjFiles)' 1>&2;\
	ar r $(LibName) $(ObjFiles);\
	echo 'ranlib $(LibName)' 1>&2;\
	ranlib $(LibName)


$(ObjDir)/prime.o: $(SrcDir)/prime.c
	$(CC) -c -o $(ObjDir)/prime.o $(CFLAGS) $(SrcDir)/prime.c
$(ObjDir)/hash.o: $(SrcDir)/hash.c
	$(CC) -c -o $(ObjDir)/hash.o $(CFLAGS) $(SrcDir)/hash.c

clean:
	@rm -f $(LibName) $(ObjDir)/*.o
