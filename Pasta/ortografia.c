#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define MAX 50

int compar(const void *s1, const void *s2){
    return (strcmp(*(char**)s1, *(  char **)s2));
}

int main(int argc, char **argv){
    setlocale(LC_ALL, "pt_BR.iso88591");
    FILE* dic; 
    dic = fopen("brazilian", "r");
    if(dic == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo brazilian");
        return 1;
    }
    lista_palavra *palavra;
    int size = carrega_dic(dic, &palavra);
    int c = getchar();
    char word[MAX];
    char wordoriginal[MAX];
    while(getchar() != EOF){
        int i = 0;
        while((!(letra(c))) && (getchar() != EOF)){
            printf("%c", c);
            c = getchar();
        }
        while((letra(c)) && (getchar()!= EOF)){
            wordoriginal[i] = c;
            word[i] = tolower(c);
            c = getchar();
            i++;
        }
        if(!strcmp(word, " ")){
            char **saida = bsearch((&word), palavra, sizeof(lista_palavra), sizeof(word),compar);
            if(saida){
                printf("%s",*saida);
            }
            else{
                printf("[ %s ]", *saida);
            }   
        }
    }
}
