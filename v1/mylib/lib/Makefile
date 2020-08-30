# Definitions.
LibName = mylib.a
SrcDir = ../src
ObjDir = ../obj
ObjFiles =\
 $(ObjDir)/prime.o \
 $(ObjDir)/myhash.o 
 
 
InclDir = ../include

# Options and arguments to the C compiler.
CC = cc
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
-Wstrict-prototypes \
-Wswitch-default \
-Wundef \
-Wno-unused -I$(InclDir)


$(LibName): $(ObjFiles)
	-[ -f $(LibName) ] && rm $(LibName)
	@echo 'ar r $(LibName) $(ObjFiles)' 1>&2;\
	ar r $(LibName) $(ObjFiles);\
	echo 'ranlib $(LibName)' 1>&2;\
	ranlib $(LibName)


$(ObjDir)/prime.o: $(SrcDir)/prime.c
	$(CC) -c -o $(ObjDir)/prime.o $(CFLAGS) $(SrcDir)/prime.c
$(ObjDir)/myhash.o: $(SrcDir)/myhash.c
	$(CC) -c -o $(ObjDir)/myhash.o $(CFLAGS) $(SrcDir)/myhash.c

clean:
	@rm -f $(LibName) $(ObjDir)/*.o
