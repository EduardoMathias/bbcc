#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef char *lista_palavra[MAX];

size_t carrega_dic(FILE *, lista_palavra*);