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
int insere_inicio_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l);
int insere_fim_lista(int tipo, int lin, int col, int velocidade, int condicao, t_lista *l);
int consulta_item_atual(int *tipo, int *lin, int *col, int *velocidade, int *condicao, t_lista *l);

typedef struct {
	char cima[6];
	char meio[6];
	char baixo[6];
	int x,y,vivo;

}Alien;

Alien inicializaAlien1(int x,int y);
Alien inicializaAlien2(int x, int y);
Alien inicializaAlien3(int x, int y);

typedef struct{
	char cima[6];
	char baixo[6];
	int x,y;
}Nave;

Nave inicializaNave(int x, int y);

typedef struct{
	char bloco[1];
	int x,y, atingido;
}Barreira;

Barreira inicializaBarreira(int x,int y);

typedef struct{
    char tiro[1];
    int x,y,atingiu;
}Missel;

Missel inicializaMissel(int x,int y);
Missel inicializaMisselAlien(int x,int y);

