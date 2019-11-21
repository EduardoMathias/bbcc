#include "elem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Canhao_TERRA " /^\\ MMMMM"
#define ALIEN_1_1 " A AMA/X\\"
#define ALIEN_1_2 " A AMA{ } "
#define ALIEN_2_1 ".v_v.}MWM{ / \\ "
#define ALIEN_2_2 ".v_v.}MWM{ } { "
#define ALIEN_3_1 " nmn dbMdb_/-\\_"
#define ALIEN_3_2 " nmn dbMdb |-| "
#define NAVE_MAE " /MMMMM\\ AMoMoMoMA \\/'-'\\/ "
#define BARREIRA " AMMMA AMMMMMAMM   MM"
#define BLOCOS     "AM"

int inicializa_lista(t_lista *l){
    l->tamanho = 0;
	l->ini = NULL;
    l->atual = NULL;
    l->auxiliar = NULL;
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
	novo->x = col;
	novo->y = lin;
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
    novo->x = col;
	novo->y = lin;
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
	*col = l->atual->x;
	*lin = l->atual->y;
	*velocidade = l->atual->velocidade;
	*condicao = l->atual->condicao;
	return 1;
}

int anda_item_atual_esquerda(t_lista *l){
    if(l->atual == NULL)
        return 0;
    l->atual->x--;
    return 1;
}

int anda_item_atual_direita(t_lista *l){
    if(l->atual == NULL)
        return 0;
    l->atual->x++;
    return 1;
}


int inicializa_atual_ultimo_alien(t_lista *l){
    inicializa_atual_inicio(l);
    while(l->atual->prox->tipo != 4)
        l->atual = l->atual->prox;
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

int inicializa_auxiliar_inicio(t_lista *l){
    l->auxiliar = l->ini;
	return 1;
}

int inicializa_auxiliar_fim(t_lista *l){
    t_nodo*aux;
    if(l->ini){
		aux = l->ini;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		l->auxiliar = aux;
	}
    else 
        l->auxiliar = l->ini;
    return 1;
}

int incrementa_auxiliar(t_lista *l){
     if(l->auxiliar != NULL)
        l->auxiliar = l->auxiliar->prox;
    return 1;
}

int inicializa_auxiliar_primeira_barreira(t_lista *l){
    inicializa_auxiliar_inicio(l);
    while(l->auxiliar->prox->tipo != 4)
        l->auxiliar = l->auxiliar->prox;
    l->auxiliar = l->auxiliar->prox;
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


void destroi_lista(t_lista *l)
{
    t_nodo *aux = l->ini;
    t_nodo *prox;
    while (aux != NULL)
    {
        prox = aux->prox;
        free(aux);
        aux = prox;
    }
    l->ini = NULL;
    l->tamanho = 0;
}


Canhao inicializaCanhao(){
	Canhao NovaCanhao;
    NovaCanhao.altura = 2;
    NovaCanhao.largura = strlen(Canhao_TERRA)/2;
    strcpy(NovaCanhao.forma, Canhao_TERRA);
	return NovaCanhao;
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

Bloco inicializaBloco1(){
    char str_bloco[2];
    Bloco bloco1;
    str_bloco[0] = BLOCOS[0];
    str_bloco[1] = '\0';
    strcpy(bloco1.formato, str_bloco);
    bloco1.altura = 1;
    bloco1.largura = 1;
    return bloco1;
}

Bloco inicializaBloco2(){ 
    char str_bloco[2];
    Bloco bloco2;
    str_bloco[0] = BLOCOS[1];
    str_bloco[1] = '\0';
    strcpy(bloco2.formato, str_bloco);
    bloco2.altura = 1;
    bloco2.largura = 1;
    return bloco2;
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