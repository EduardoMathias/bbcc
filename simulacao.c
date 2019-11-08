#include <stdio.h>
#include <stdlib.h>
#include "lib_fila.h"

int escolhaAterrizagem(int t1, int t2, int t3, int t4){
    if(t1 < t2 && t1 < t3 && t1 < t4)
        return 1;
    if(t2 < t1 && t2< t3 && t2 < t4)
        return 2;
    if (t3< t1 && t3 < t2 && t3 < t4)
        return 3;
    if (t4 < t1 && t4 < t2 && t4 < t3)
        return 4;
    return 0;
}

int escolhaDecola(int t1, int t2, int t3){
    if(t1 < t2 && t1 < t3)
        return 1;
    if(t2 < t1 && t2< t3)
        return 2;
    if (t3< t1 && t3 < t2)
        return 3;
    return 0;
}

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
            int escolha = escolhaAterrizagem(tamanho(&aterissagem1), tamanho(&aterissagem2), tamanho(&aterissagem3), tamanho(&aterissagem4));
            if(escolha == 1)
                enfileira(idimpar,j,&aterissagem1);
            if(escolha == 2)
                enfileira(idimpar,j, &aterissagem2);
            if(escolha == 3)
                enfileira(idimpar,j, &aterissagem3);
            if(escolha == 4)
                enfileira(idimpar,j,&aterissagem4);
            idimpar+=2;
        }
        scanf("%d", &QntdDecolagem);
        for(int j= 0; j < QntdDecolagem; j++){
            int escolha_decola = escolhaDecola(tamanho(&decolagem1), tamanho(&decolagem2), tamanho(&decolagem3));
            if(escolha_decola == 1)
                enfileira(idpar,j, &decolagem1);
            if(escolha_decola == 2)
                enfileira(idpar,j,&decolagem2);
            if(escolha_decola == 3)
                enfileira(idpar,j,&decolagem3);
            idpar+=2;
        }
    }
    return 0;
}