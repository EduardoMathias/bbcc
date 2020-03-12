#include "dicionario.h"
#include <stdio.h>
#include <string.h>

size_t carrega_dic(FILE *dic){
    char buffer[50];
    int alocagens = 50;
    int i = 0;
    lista_palavra *dici = malloc(sizeof(lista_palavra)*100);
    while((fgets(buffer,50, dic)) != NULL){
        if(i >= alocagens){
           alocagens = alocagens*2;
           dici = realloc(dici, alocagens*sizeof(char *));
        }
        *dici[i] = malloc((strlen(buffer)+1)*sizeof(char *));
        strcpy(*dici[i], buffer);
        i++;
    }
    free(dici);
    free(*dici);
    return i;
}
