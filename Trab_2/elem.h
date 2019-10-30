#pragma once
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

