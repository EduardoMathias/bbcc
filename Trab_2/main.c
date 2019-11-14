#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include "elem.h"
#include <stdlib.h>
#include <time.h>

int placar = 0;

#define INTERVALO 20000

int insere_aliens( t_lista *l_tela ){
	int i, j;
	for (i = 0; i < 11; i++)
		insere_fim_lista(1, 7, (5 + 7*i), 0, 1, l_tela); 	
	for (i = 0; i < 2; i++)
		for (j = 0; j < 11; j++)
			insere_fim_lista(2, (11 + 4*i), (4 + 7*j), 0, 1, l_tela); 
	for (i = 0; i < 2; i++)
		for (j = 0; j < 11; j++)
			insere_fim_lista(3, (19 + 4*i), (4 + 7*j), 0, 1, l_tela);
	return 1;
}

int insere_barreiras(t_lista *l_tela){
	int i;
	for (i = 0; i < 4; i++)
        insere_fim_lista(4, 31, (15 + 21*i), 0, 1, l_tela);
	return 1;
}

int insere_nave(t_lista *l_tela){
	insere_fim_lista(5, 35, 43, 0, 1, l_tela);
	return 1;
}

int insere_navemae(t_lista *l_tela){
    insere_fim_lista(6, 3, 1, 0, 1, l_tela); 
	return 1;
}


int inicializa_lista_tela( t_lista *l_tela ){
	inicializa_lista(l_tela);
	insere_navemae(l_tela);
	insere_aliens(l_tela);
	insere_barreiras(l_tela);
	insere_nave(l_tela);
	return 1;
}

void DesenhaPlacar(){
    move(1,50);
    printw("%07d",placar);

}

void Desenha_Borda(){
    box(stdscr,0,0);
}

void Desenha_NaveMae(int lin, int col, NaveMae *navemae){
    int i, j;
	for (i = 0; i < navemae->altura; i++){
		for (j = 0; j < navemae->largura; j++)
		{
			move(lin+i, col+j);
			addch(navemae->formato[navemae->largura*i + j]);
		}
    }
}

void Desenha_Nave(int lin, int col, Nave *nave){
    int i, j;
	for (i = 0; i < nave->altura; i++)
		for (j = 0; j < nave->largura; j++)
		{
			move(lin+i, col+j);
			addch(nave->forma[nave->largura*i + j]);
		}
}

void Desenha_Alien(int lin, int col, int tipo, Alien *alien){
	int i, j, nlin, ncol;
	char *forma_atual;
	
	if (!alien[tipo].forma_inicial)
		forma_atual = alien[tipo].tipo1;
	else
		forma_atual = alien[tipo].tipo2;
	
	nlin = alien[tipo].altura;
	ncol = alien[tipo].largura;
	for (i = 0; i < nlin; i++)
		for (j = 0; j < alien[tipo].largura; j++)
			{
				move(lin+i, col+j);
				addch(forma_atual[ncol*i + j]);
			}
}

void Desenha_Barreira(int lin, int col, int num_bar,Barreira *barreiras){
    int i, tam;
	Bloco atual;
	
	tam = barreiras[num_bar].tam;
	for (i = 0; i < tam; i++)
	{
		atual = barreiras[num_bar].blocos[i];
		move(lin + atual.lin, col + atual.col);
		addch(atual.forma);
	}
}


void Desenha_tela(t_lista *l_tela, Alien *alien, Barreira *barreiras, Nave *nave, NaveMae *navemae){
	int tipo, lin, col, vel, estado, cont_bar = 0;

    clear();
	Desenha_Borda();
    DesenhaPlacar();
	inicializa_atual_inicio(l_tela);
	for (int i = 0; i < l_tela->tamanho; i++)
	{
		consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tela);
		if (tipo <= 3)
			Desenha_Alien(lin, col, tipo, alien);
		else if (tipo == 4)
			Desenha_Barreira(lin, col, cont_bar++, barreiras);
        else if(tipo == 6)
            Desenha_NaveMae(lin,col, navemae);
        else if(tipo == 5)
            Desenha_Nave(lin, col, nave);
		incrementa_atual(l_tela);
	}
	refresh();
}



int main(){
    t_lista l_tela;
	Alien alien[4];
	Barreira barreiras[4];
	int key,ncol,nlin;
    int iter = 1;
    inicializa_lista_tela(&l_tela);
	initscr();
    cbreak();
	noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    getmaxyx(stdscr, nlin, ncol);
    if (ncol < 100 || nlin < 38)
	{
		endwin();
        printf("Tamanho errado");
        printf("%d %d", nlin,ncol);
        imprime_lista(&l_tela);
		return 0;
	}
    //Naves
    Nave nave = inicializaNave();
    NaveMae navemae = inicializaNaveMae();
    //Aliens
	alien[1] = inicializaAlien1();
	alien[2] = inicializaAlien2();
    alien[3] = inicializaAlien3();
    //Barreiras
    for(int b = 0; b < 4; b++)
        barreiras[b] = inicializaBarreira();
   
while((key = getch())){
	if(key == ' '){
    }
	else
		if(key == KEY_LEFT){

  		    }
	else if (key == KEY_RIGHT){
  	}
	else if (key == 'q') {
    	endwin();
    	exit(0);
  	}
    Desenha_tela(&l_tela, alien, barreiras, &nave, &navemae);
	usleep(INTERVALO);
	}
	endwin();
}
