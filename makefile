CC = gcc
OBJ = verbose.o looting.o tools.o
HEAD = verbose.h looting.h tools.h
EXEC = scruff
FLAGS = -g -Wall -ljson-c
RM = rm

all: $(EXEC);./scruff

debug: $(EXEC)

$(EXEC):$(OBJ) main.o
	$(CC) $(FLAGS) $(OBJ) main.o -o $(EXEC)

main.o: main.c $(HEAD)
	$(CC) $(FLAGS) -c main.c

verbose.o: verbose.c verbose.h
	$(CC) $(FLAGS) -c verbose.c

looting.o: looting.c looting.h tools.h
	$(CC) $(FLAGS) -c looting.c

tools.o: tools.c tools.h
	$(CC) $(FLAGS) -c tools.c

clean:
	$(RM) $(OBJ) main.o $(EXEC)

