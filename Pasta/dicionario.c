#include "dicionario.h"
#include <stdio.h>
#include <string.h>

size_t carrega_dic(FILE *dic, lista_palavra *palavra){
    char buffer[50];
    int count = 0;
    int alocagens = MAX;
    int i = 0;
    while((fgets(buffer,count, dic)) != NULL){
        if(i >= alocagens){
            alocagens = MAX*2;
            palavra = realloc(palavra, alocagens*sizeof(char));
        }
        *palavra[i] = malloc(strlen(buffer+1)*sizeof(char *));
        strcpy(*palavra[i], buffer);
        i++;
    }
    return i;
}
