#pragma once

struct t_nodo {
    int tipo;
    int local;
    int velocidade;
    int estado;
    struct t_nodo *prox;
};
typedef struct t_nodo t_nodo;

struct t_lista_Aliens {
    t_nodo *alien;
    int tamanho;
};
typedef struct t_lista_Aliens t_lista_Aliens;

struct t_lista_Barreiras{
    t_nodo *barreira;
    int tamanho;
};
typedef struct t_lista_Barreiras t_lista_Barreiras;

struct t_lista_Nave{
    t_nodo *nave;
    int tamanho;
};
typedef struct t_lista_Nave t_lista_Nave;

struct t_lista_NaveMae{
    t_nodo *navemae;
    int tamanho;
};
typedef struct t_lista_NaveMae t_lista_NaveMae;

struct t_lista_Missel{
    t_nodo *tiro;
    int tamanho;
};
typedef struct t_lista_Missel t_lista_Missel;

int cria_Aliens(t_lista_Aliens *Alien);
int cria_Barreiras(t_lista_Barreiras *Barreira);
int cria_Nave(t_lista_Nave *Nave);
int cria_Mae(t_lista_NaveMae *NaveMae);

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

