CFLAGS = -Wall -Wextra -pedantic -O3
CC = gcc

SRC = ortografia.c dicionario.c 
OBJ = $(SRC:.c=.o)
EXEC = dic

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC)  -o $@ $(OBJ)

clean:
	rm -rf $(OBJ) $(EXEC)
