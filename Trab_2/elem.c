#include "elem.h"
#include <stdlib.h>
#include <stdio.h>


int inicializa_lista(t_lista *l){
    l->tamanho = 0;
	l->ini = NULL;
    l->atual = NULL;
	return 1;
}

int insere_inicio_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l)
{
	t_nodo *novo;

	novo = (t_nodo*) malloc(sizeof(t_nodo));
	if (novo == NULL)
	{
		free(novo);
		return 0;
	}

	novo->tipo = tipo;
	novo->x = lin;
	novo->y = col;
	novo->velocidade = velocidade;
	novo->condicao = condicao;
	novo->prox = l->ini;
    l->ini = novo;
	l->tamanho++;
	return 1;
}

int insere_fim_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l){
    t_nodo *novo,*aux;
	novo = malloc(1*sizeof(t_nodo));
	if (novo == NULL)
        return 0;
    novo->tipo = tipo;
	novo->x = lin;
	novo->y = col;
	novo->velocidade = velocidade;
	novo->condicao = condicao;
	novo->prox = NULL;
	if(l->ini){
		aux = l->ini;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = novo;
	}
	else
		l->ini = novo;
	l->tamanho++;
	return 1;
}

int inicializa_atual_inicio(t_lista *l){
	l->atual = l->ini;
	return 1;
}

int inicializa_atual_fim(t_lista *l){
    t_nodo*aux;
    if(l->ini){
		aux = l->ini;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		l->atual = aux;
	}
    else 
        l->atual = l->ini;
    return 1;
}

void incrementa_atual(t_lista *l){
    if(l->atual != NULL)
        l->atual = l->atual->prox;
}

void decrementa_atual(t_lista *l){
    t_nodo *aux;
    if(l->atual != NULL && l->atual != l->ini){
        aux= l->ini;
    while(aux->prox != l->atual)
        aux = aux->prox;
    l->atual = aux;
    }
}

int consulta_item_atual(int *tipo, int *lin, int *col, int *velocidade, int *condicao, t_lista *l){
    if (l->atual == NULL)
		return 0;
	*tipo = l->atual->tipo;
	*lin = l->atual->x;
	*col = l->atual->y;
	*velocidade = l->atual->velocidade;
	*condicao = l->atual->condicao;
	return 1;
}

int remove_item_atual(t_lista *l){
    t_nodo *elem, *aux;
	elem = l->ini;
	aux = NULL;
	while(elem != NULL && elem != l->atual){
		aux= elem;
		elem= elem->prox;
	}
	if(elem != NULL){
		if(elem == l->ini)
			l->ini = elem->prox;
		if(aux)
			aux->prox = elem->prox;
		free(elem);
	}
	else{
		return 0;
	}
	l->tamanho--;
	return 1;
}


Nave inicializaNave(int x, int y){
	Nave NovaNave = {
		" /^\\ ", "MMMMM", x, y
	};
	return NovaNave;
}
Alien inicializaAlien1(int x,int y){
	Alien Alien1 = {
		" A ","AMA","/X\\", x, y, 1};
	return Alien1;
}
Alien inicializaAlien2(int x,int y){
	Alien Alien2 = {
	     ".v_v.","}WMW{"," / \\ ", x, y, 1};
       return Alien2;
}
Alien inicializaAlien3(int x, int y){
	Alien Alien3 = {
		" nmn ", "dbMdb", "_/-\\_", x, y, 1};
	return Alien3;
}
Barreira inicializaBarreira(int x, int y){
	Barreira NovaBarreira = {
		"M", x, y, 0
	};
	return NovaBarreira;
}

Missel inicializaMissel(int x, int y){
    Missel NovoMissel ={
        "|",x,y,0
    };
    return NovoMissel;
}

Missel inicializaMisselAlien(int x, int y){
    Missel NovoMisselAlien = {
        "$", x,y,0
    };
    return NovoMisselAlien;
}