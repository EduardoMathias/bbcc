#include <stdio.h>
#include "lib_lista_complementar.h"

void imprime_lista(t_lista *l){
    int item,tam;
    if(!lista_vazia(l)){
        inicializa_atual_inicio(l);
        tamanho_lista(tam,l);
        for(int i= 0; i <= tam; i++){
           consulta_item_atual(item,l);
           printf("%d", &item);
        }
    return 1;
    }
}

int copia_lista(t_lista *l, t_lista *c){
    int item,tam;
    if(!lista_vazia(l)){
    inicializa_atual_fim(c);
    inicializa_atual_inicio(l);
    tamanho_lista(tam,l);
    for(int i = 0; i<= tam; i++){
        consulta_item_atual(item,l);
        insere_fim_lista(item, c);
    }
    return 1;
  }
}

int concatena_listas(t_lista *l, t_lista *c){
    if(!lista_vazia(c)){
    int item,tam;
    inicializa_atual_fim(l);
    inicializa_atual_inicio(c);
    tamanho_lista(tam,l);
    for(int i = 0; i<= tam; i++){
        consulta_item_atual(item,c);
        insere_fim_lista(item, l);
    }
    destroi_lista(c);
    return 1;
    }
}

int ordena_lista(t_lista *l){
    if(!lista_vazia(l)){
        int item;
        int tam;
        tamanho_lista(tam,l);
        for(int i=0; i<= tam; i++){
            inicializa_atual_inicio(l);
            consulta_item_atual(item,l);
            insere_ordenado_lista(item,l);
            incrementa_atual(l);
        }
    return 1;
    }
}

int intercala_listas(t_lista *l, t_lista *m, t_lista *i){
    if(lista_vazia(l) && lista_vazia(m))
        return 0;
    ordena_lista(l);
    ordena_lista(m);
    inicializa_atual_inicio(l);
    inicializa_atual_inicio(m);
    int item,item2,tamanhoMenor,tamanhol,tamanhom = 0;
    tamanho_lista(tamanhol,l);
    tamanho_lista(tamanhom,l);
    if(tamanhol> tamanhom)
        tamanhoMenor = tamanhom;
    else
        tamanhoMenor = tamanhol;
    for(int i = 0; i <= tamanhoMenor; i++){
        consulta_item_atual(item,l);
        insere_inicio_lista(item,i);
        incrementa_atual(i);
        incrementa_atual(m);
        consulta_item_atual(item2,m);
        insere_inicio_lista(item2,i);
        incrementa_atual(l);
    }
}