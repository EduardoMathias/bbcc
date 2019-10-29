#include "lib_lista.h"
#include <stdio.h>
#include <stdlib.h>

int inicializa_lista(t_lista *l){
    t_nodo *inicio,*fim;
    inicio = malloc(1*sizeof(t_nodo));
  fim = malloc(1*sizeof(t_nodo));
    inicio->prox= fim;
  inicio->prev = NULL;
  fim->prev = inicio;
  fim->prox = NULL;

  l->ini = inicio;
  l->atual = NULL;
  l->fim = fim;
  l->tamanho = 0;

    return 1;
}

int lista_vazia(t_lista *l){
  if(l->tamanho)
      return 0;
  return 1;
}

void destroi_lista(t_lista *l){
  t_nodo *atual,*aux;
  atual = l->ini;
  while(atual != l->fim){
    aux = atual->prox;
    free(atual);
    atual = aux;
  }
  free(atual);
  l->ini = NULL;
  l->atual = NULL;
  l->fim = NULL;
  l->tamanho = 0;
}

int insere_inicio_lista(int item, t_lista *l){
  t_nodo *novo;
  novo = malloc(1*sizeof(t_nodo));
  if(novo == NULL) return 0;
  l->ini->prox = novo;
  novo->chave = item;
  novo->prox = l->ini->prox;
  novo->prox->prev = novo;
  novo->prev = l->ini;
  l->tamanho++;
  return 1;
}

int tamanho_lista(int *tam, t_lista *l){
  *tam = l->tam;
  return 1;
}

int insere_fim_lista(int item, t_lista *l){
  t_nodo *novo;
  novo = malloc(1*sizeof(t_nodo));
  if(novo == NULL) return 0;
  l->fim->prev->prox = novo;
  l->fim->prev = novo;
  novo->chave = item;
  novo->prox = l->fim;
  novo->prev = l->fim->prev;
  novo->prox->prev = novo;
  l->tamanho++;
  return 1;
}

int insere_ordenado_lista(int item, t_lista *l){
  t_nodo *novo,*aux;
  novo = malloc(1*sizeof(t_nodo));
  if(novo == NULL)return 0;
  novo->chave = item;
  l->fim->chave = item;
  aux = l->ini;
  while(item < aux->prox->chave)
    aux = aux->prox;
  novo->prox = aux->prox;
  novo->prev = aux;
  aux->prox = novo;
  l->tamanho++;
  return 1;
}

int remove_inicio_lista(int *item, t_lista *l)
{
  if(lista_vazia(l))
    return 0;
  t_nodo *aux;
  aux = l->ini->prox;
  *item = aux->chave;
  aux->prev->prox = aux->prox;
  aux->prox->prev = aux->prev;
  free(aux);
  l->tamanho--;
  return 1;
}

int remove_fim_lista(int *item, t_lista *l){
  if(lista_vazia(l))
    return 0;
  t_nodo *aux;
  aux = l->fim->prev;
  *item = aux->chave;
  aux->prev->prox = aux->prox;
  aux->prox->prev = aux->prev;
  free(aux);
  l->tamanho--;
  return 1;
}

int remove_item_lista(int chave, int *item, t_lista *l){
    if(lista_vazia(l))
        return 0;
    l->fim->chave = chave;
    t_nodo *aux;
    aux = l->ini->prox;
    while(aux->chave != chave)
		aux = aux->prox;
	if(aux == l->fim){
		*item= aux->chave;
		aux->prev->prox = aux->prox;
		aux->prox->prev = aux->prev;
		free(aux);
        l->tamanho--;
        return 1;
	}
}
   
int pertence_lista(int chave, t_lista *l){
    if(lista_vazia(l))
        return 0;
    l->fim->chave = chave;
    t_nodo *aux;
    aux = l->ini->prox;
    while(aux->chave != chave)
        aux = aux->prox;
    if(aux == l->fim)
        return 0;
    return 1;
}

int inicializa_atual_inicio(t_lista *l){
    if(lista_vazia(l))
        return 0;
    l->atual = l->ini->prox;
    return 1;

}

int inicializa_atual_fim(t_lista *l){
    if(lista_vazia(l))
        return 0;
    l->atual = l->fim->prev;
    return 1;
}

void incrementa_atual(t_lista *l){
    t_nodo *aux;
    aux = l->atual;
    l->atual = aux->prox;
    free(aux);
}

void decrementa_atual(t_lista *l){
    t_nodo *aux;
    aux = l->atual;
    l->atual = aux->prev;
    free(aux);
}

int consulta_item_atual(int *item, t_lista *l){
    if(lista_vazia(l))
        return 0;
    *item = l->atual->chave;
    return 1;
}

int remove_item_atual(int *item, t_lista *l){
  if(lista_vazia(l))
        return 0;
    t_nodo *aux;
    aux = l->atual;
    *item = l->atual->chave;
    free(l->atual);
    l->atual = aux->prox;
}