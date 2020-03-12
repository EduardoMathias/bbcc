#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(int argc, char **argv){
//Mas tipo, teria que gerar a mesma coisa no ssh do dinf? Ou Ja tem la?
    setlocale(LC_ALL, "pt_BR.iso88591");
    FILE* dic; 
    dic = fopen("brazilian", "r");
    if(dic == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo brazilian");
        return 1;
    }
    lista_palavra *palavra;
    int size = carrega_dic(dic, &palavra);
    printf("%s\n", palavra[size / 2]);
}
