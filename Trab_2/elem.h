#pragma once

struct t_nodo {
    int tipo;
    int x,y;
    int velocidade;
    int condicao;
    struct t_nodo *prox;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    int tamanho;
};
typedef struct t_lista t_lista;

int inicializa_lista(t_lista *l);
int lista_vazia(t_lista *l);
int insere_inicio_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l);
int insere_fim_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l);
int inicializa_atual_inicio(t_lista *l);
int inicializa_atual_fim(t_lista *l);
void incrementa_atual(t_lista *l);
void decrementa_atual(t_lista *l);
int consulta_item_atual(int *tipo, int *lin, int *col, int *velocidade, int *condicao, t_lista *l);
int remove_item_atual(t_lista *l);
void imprime_lista(t_lista *l);

typedef struct {
	char tipo1[28];
	char tipo2[28];
    int forma_inicial;
    int altura,largura;
}Alien;

Alien inicializaAlien1();
Alien inicializaAlien2();
Alien inicializaAlien3();

typedef struct{
	char forma[28];
    int altura,largura;
}Nave;

Nave inicializaNave();


typedef struct Bloco
{
	int lin;
	int col;
	int estado;
	char forma;
} Bloco;

typedef struct Barreira
{
	int tam;
	Bloco blocos[22];
} Barreira;

Barreira inicializaBarreira();

typedef struct{
    char tiro[1];
}Missel;

Missel inicializaMissel();
Missel inicializaMisselAlien();

typedef struct{
    char formato[28];
    int altura,largura;
}NaveMae;

NaveMae inicializaNaveMae();

