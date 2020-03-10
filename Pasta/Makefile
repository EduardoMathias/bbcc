CFLAGS = -Wall -Wextra  -pedantic -fsanitize=address -O3
CC = gcc
LDFLAGS =  -fsanitize=address
LBLIBS = -lncurses

SRC = ortografia.c dicionario.c 
OBJ = $(SRC:.c=.o)
EXEC = dic

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
