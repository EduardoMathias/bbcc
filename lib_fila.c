#include "lib_fila.h"
#include <stdio.h>
#include <stdlib.h>

int inicializa_fila(t_fila *f){
    f->ini = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return 1;
}

int fila_vazia(t_fila *f){
    if(f->ini == NULL)
        return 1;
    return 0;
}

int tamanho(t_fila *f){
    if(f->ini == NULL)
        return -1;
    return f->tamanho;
}

int enfileira(int id,int t, t_fila *f){
    t_nodo *novo;
    novo = malloc(1*sizeof(t_nodo));
    if(novo == NULL)
        return 0;
    novo->dado = id;
    novo->dado2 = t;
    novo->prox = NULL;
    if (f->ini == NULL){
        f->ini= novo;
        f->fim = f->ini;}
    else{
        novo->prev = f->fim;
        f->fim->prox = novo;
        f->fim = novo;
        }
    f->tamanho++;
    return 1;
}

int desenfileira(int *id, int *t, t_fila *f){
    if(fila_vazia(f))
        return 0;
    t_nodo *aux = f->ini->prox;
    aux->prev = NULL; 
    free(f->ini);
    *id = f->ini->dado;
    *t = f->ini->dado2;
    f->ini = aux;
    f->tamanho--;
    return 1;
}

int removefila(int *id, int *t, t_fila *f){
    t_nodo *aux = f->ini;
    if(fila_vazia(f))
        return 0;
    while(aux != NULL && aux->dado != *id)
        aux = aux->prox;
    if(aux->dado != *id)
        return 0;
    if(aux == NULL)
        return 0;
    *t = aux->dado2;
    if(aux->prev)
        aux->prev = aux->prox;
    if(aux->prox)
        aux->prox = aux->prev;
    free(aux);
    return 1;
}

void imprimefila(t_fila *f){
    t_nodo *aux = f->ini;
    while(aux != NULL){
        printf("%d(%d)", aux->dado, aux->dado2);
        if(aux->prox != NULL)
            printf(", ");
        aux = aux->prox;
    }
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