#include "elem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAVE_TERRA " /^\\ MMMMM"
#define ALIEN_1_1 " A AMA/X\\"
#define ALIEN_1_2 " A AMA{ } "
#define ALIEN_2_1 ".v_v.}MWM{ / \\ "
#define ALIEN_2_2 ".v_v.}MWM{ } { "
#define ALIEN_3_1 " nmn dbMdb_/-\\_"
#define ALIEN_3_2 " nmn dbMdb |-| "
#define NAVE_MAE " /MMMMM\\ AMoMoMoMA \\/'-'\\/ "
#define BARREIRA " AMMMA AMMMMMAMM   MM"

int inicializa_lista(t_lista *l){
    l->tamanho = 0;
	l->ini = NULL;
    l->atual = NULL;
	return 1;
}

int lista_vazia(t_lista *l)
{
    return l->tamanho == 0 && l->ini == NULL;
}

int insere_inicio_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l)
{
	t_nodo *novo = malloc(sizeof(t_nodo));
	if (novo == NULL)
	{
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
    t_nodo *novo = (t_nodo*)malloc(sizeof(t_nodo));
    t_nodo *aux;
    if (novo == NULL){
        free(novo);
        return 0;}
    novo->tipo = tipo;
    novo->x = lin;
	novo->y = col;
	novo->velocidade = velocidade;
	novo->condicao = condicao;
    novo->prox = NULL;
    if (lista_vazia(l))
    {
        l->ini = novo;
    }
    else
    {
        aux = l->ini;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
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

void imprime_lista(t_lista *l)
{
    if (!lista_vazia(l))
    {
        printf("tam: %d -> ", l->tamanho);
        t_nodo *atual = l->ini;
        while (atual->prox != NULL)
        {
            printf("%d ", atual->tipo);
            atual = atual->prox;
        }
        printf("%d\n", atual->tipo);
    }
}


Nave inicializaNave(){
	Nave NovaNave;
    NovaNave.altura = 2;
    NovaNave.largura = strlen(NAVE_TERRA)/2;
    strcpy(NovaNave.forma, NAVE_TERRA);
	return NovaNave;
}
Alien inicializaAlien1(){
    Alien alien1;
    alien1.forma_inicial = 0;
	alien1.altura = 3; 
	alien1.largura = strlen(ALIEN_1_1) / 3;
	strcpy( alien1.tipo1, ALIEN_1_1 );
	strcpy( alien1.tipo2, ALIEN_1_2 );
    return alien1;
}

Alien inicializaAlien2(){
    Alien alien2;
    alien2.forma_inicial = 0;
	alien2.altura = 3; 
	alien2.largura = strlen(ALIEN_2_1) / 3;
	strcpy( alien2.tipo1, ALIEN_2_1 );
	strcpy( alien2.tipo2, ALIEN_2_2 );
    return alien2;
}
Alien inicializaAlien3(){
    Alien alien3;
    alien3.forma_inicial = 0;
    alien3.altura = 3; 
	alien3.largura = strlen(ALIEN_3_1) / 3;
	strcpy( alien3.tipo1, ALIEN_3_1 );
	strcpy( alien3.tipo2, ALIEN_3_2 );
    return alien3;
}


Barreira inicializaBarreira(){
    Barreira barreira;
	int i_bloco, i_bar, ncol;
	i_bloco = 0;
	ncol = strlen(BARREIRA) / 3;
	for (i_bar = 0; i_bar < strlen(BARREIRA); i_bar++)
		if (BARREIRA[i_bar] != ' ')
		{
			barreira.blocos[i_bloco].forma = BARREIRA[i_bar];
			barreira.blocos[i_bloco].estado = 1;
			barreira.blocos[i_bloco].lin = i_bar / ncol;
			barreira.blocos[i_bloco].col = i_bar % ncol;
			i_bloco++;
		}
	barreira.tam = i_bloco;
    return barreira;
}


Missel inicializaMissel(){
    Missel NovoMissel ={
        "|"
    };
    return NovoMissel;
}

Missel inicializaMisselAlien(){
    Missel NovoMisselAlien = {
        "$"
    };
    return NovoMisselAlien;
}

NaveMae inicializaNaveMae(){
    NaveMae navemae;
    navemae.altura = 3;
	navemae.largura = strlen(NAVE_MAE) / 3;
	strcpy( navemae.formato, NAVE_MAE );   
    return navemae;
}