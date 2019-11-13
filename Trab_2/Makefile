CFLAGS = -Wall -Wextra  -pedantic
CC = gcc
LBLIBS = -lncurses

SRC = main.c elem.c 
OBJ = $(SRC:.c=.o)
EXEC = space-invaders

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
