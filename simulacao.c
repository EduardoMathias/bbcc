#include <stdio.h>
#include <stdlib.h>
#include "lib_fila.h"

int main(int argc, char **argv){
    int idpar,idimpar;
    idpar = 2;
    idimpar = 1;
    int Ttotal,QntdAterrizagem,QntdDecolagem,j;
    t_fila aterissagem1,aterissagem2,aterissagem3,aterissagem4,decolagem1,decolagem2,decolagem3; 
    inicializa_fila(&aterissagem1);
    inicializa_fila(&aterissagem2);
    inicializa_fila(&aterissagem3);
    inicializa_fila(&aterissagem4);
    inicializa_fila(&decolagem1);
    inicializa_fila(&decolagem2);
    inicializa_fila(&decolagem3);
    scanf("%d", &Ttotal);
    for(int i= 0; i< Ttotal; i++){
        scanf("%d", &QntdAterrizagem);
        for(int j = 0; j < QntdAterrizagem;j++){
            enfileira(idimpar,j,&aterrisagem1);
            idimpar+=2;
        }
        scanf("%d", &QntdDecolagem);
        for(int j= 0; j < QntdDecolagem; j++){
            enfileira(idpar,j, &decolagem1);
            idpar+=2;
        }
    }
    return 0;
}