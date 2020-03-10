#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    FILE* dic; 
    dic = fopen("brazilian", "r"); 
    lista_palavras *palavras;
    char buffer[20];
    int newSize = 0;

    size_t contagem_palavras = carrega_dic(dic, palavras);
    /*
    //Cria Lista_palavras
    palavras->palavra = malloc(10 * sizeof(char *));
    palavras->tamanho_usado = 0;
    palavras->tamanho_total = 10;//INICIAL_SIZE

    //EXPANSAO PALAVRAS
    
    strcpy(palavras->palavra[palavras->tamanho_usado], buffer);
    palavras->tamanho_usado++;
        if (palavras->tamanho_usado == palavras->tamanho_total){
            newSize = palavras->tamanho_total* 2;
        }
    //EXPANSAO DE LINHAS
    palavras->palavra = realloc(palavras->palavra, newSize * sizeof(char *));
    palavras->tamanho_total = newSize;    
    */}