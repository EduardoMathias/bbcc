#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    FILE* dic; 
    dic = fopen("brazilian", "r");
    if(dic == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo brazilian");
        return 1;
    } 
    carrega_dic(dic);
    
    }