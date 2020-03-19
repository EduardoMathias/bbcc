#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define MAX 100

int compar(const void *palavra1,const void *palavra2){
    return (strcmp(*(char**)palavra1, *(char **)palavra2));
}

int main(){
    setlocale(LC_ALL, "pt_BR.iso88591");
    FILE* dic; 
    dic = fopen("brazilian", "r");
    if(dic == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo brazilian");
        return 1;
    }
    lista_palavra *palavra;
    int size = carrega_dic(dic, &palavra);
    int c;
    char word[MAX];
    char wordoriginal[MAX];
    while((c = getchar())!= EOF){
        int i = 0;
        if(letra(c)){
            wordoriginal[i] = c;
            word[i] = tolower(c);
            while(letra(c = getchar())){
                word[i] = tolower(c);
                wordoriginal[i] = c;
                i++;}
            word[i] = '\0';
            wordoriginal[i] = '\0';
            char **saida = bsearch((&word), palavra, size, sizeof(char),compar);
            char **saida2 = bsearch((&wordoriginal), palavra, size, sizeof(char), compar);
            if(saida || saida2)
                    printf("%s",*saida);
            else
                    printf("[ %s ]", *saida);
        }
        printf("%c", c);
     }
     fclose(dic);
} 
