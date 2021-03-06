#include "dicionario.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX 50

size_t carrega_dic(FILE *dic, lista_palavra **dicionario){
    char buffer[MAX];
    int alocagens = MAX;
    int i = 0;
    lista_palavra *dici = malloc(sizeof(lista_palavra)*100);
    while((fgets(buffer,50, dic)) != NULL){
        if(i >= alocagens){
           alocagens = alocagens*2;
           dici = realloc(dici, alocagens*sizeof(char *));
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        dici[i] = malloc((strlen(buffer)+1)*sizeof(char *));
        strcpy(dici[i], buffer);
        i++;
    }
    *dicionario = dici;
    return i;
}

void destroi_dic(lista_palavra **dicionario, int size){
    for(int i = 0; i < size; i++)
        free((*dicionario)[i]);
}
