#include "lib_fila.h"
#include <stdio.h>
#include <stdlib.h>

int Inicializa_Fila(t_fila *f){
    t_nodo* novo = (t_nodo*)malloc(sizeof(t_nodo));
    novo->dado = 0;
    novo->prev = novo->prox = NULL;
    f->ini = f->fim = NULL;
    f->tamanho = 0;
    return 1;
}

int Fila_vazia(t_fila *f){
    if(f->ini == NULL)
        return 1;
    return 0;
}

int Insere_Fila(int item, t_fila *f){
    t_nodo *novo;
    novo = malloc(1*sizeof(t_nodo));
    if(novo == NULL)
        return 0;
    novo->dado = item;
    if (f->ini == NULL)
        f->fim = f->ini = novo;
    else{
        novo->prev = f->fim;
        f->fim->prox = novo;
        f->fim = novo;
        }
    f->tamanho++;
    return 1;
}
int Destroi_Fila(t_fila *f){
    f->fim = NULL;
    while(f->ini != NULL){
        t_nodo *aux = f->ini;
        f->ini = f->ini->prox;
        free(aux);
    }
    f->tamanho = 0;
    return 1;
}
