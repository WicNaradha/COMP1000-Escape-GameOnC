C = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = game.o struct.o grids.o list.o inout.o random.o terminal.o color.o
EXEC = escape

# Add BORDERLESS to the CFLAGS and recompile the program
ifdef BORDERLESS
CFLAGS += -D BORDERLESS=1
BORDER : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

game.o : game.c game.h grids.h inout.h random.h terminal.h macros.h
	gcc -c game.c $(CFLAGS)

struct.o : struct.c struct.h macros.h
	gcc -c struct.c $(CFLAGS)

grids.o : grids.c grids.h macros.h
	gcc -c grids.c $(CFLAGS)

list.o : list.c list.h macros.h
	gcc -c list.c $(CFLAGS)

inout.o : inout.c inout.h macros.h
	gcc -c inout.c $(CFLAGS)

random.o : random.c random.h
	gcc -c random.c $(CFLAGS)

terminal.o : terminal.c terminal.h macros.h
	gcc -c terminal.c $(CFLAGS)

color.o : color.c color.h macros.h
	gcc -c color.c $(CFLAGS)

clean : 
	rm -f $(EXEC) $(OBJ)

