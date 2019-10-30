CFLAGS = -Wall -Wextra  -pedantic -fsanitize=address -O3
CC = gcc
LDFLAGS =  -fsanitize=address
LBLIBS = -lncurses

SRC = main.c elem.c 
OBJ = $(SRC:.c=.o)
EXEC = space-invaders

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
