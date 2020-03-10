#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, int **argv){

    FILE* dic; 
    dic = fopen("brazilian", "r"); 
    lista_palavras *palavras;
    char buffer[];
    int newSize = 0;
    //Cria Lista_palavras
    palavras->palavra = malloc(10 * sizeof(char *));
    palavras->tamanho_usado = 0;
    palavras->tamanho_total = 10;//INICIAL_SIZE

    //EXPANSAO PALAVRAS
    buffer[palavras->tamanho_inicial] = malloc(strlen(buffer) + 1);
    strcpy(palavras->palavra[palavras->tamanho_inicial], buffer);
    palavras->tamanho_inicial++;
        if (palavras->tamanho_usado == palavras->tamanho_total){
            newSize = palavras->tamanho_total* 2;
        }
    //EXPANSAO DE LINHAS
    palavras->palavra = realloc(palavras->palavra, newSize * sizeof(char *));
    palavras->tamanho_total = newSize;    
    }
}