#include <stdio.h>
#include <stdlib.h>  

typedef char *lista_palavra;
size_t carrega_dic(FILE *, lista_palavra**);
void destroi_dic(lista_palavra **, int size);
