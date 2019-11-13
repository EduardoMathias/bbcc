#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include "elem.h"
#include <stdlib.h>
#include <time.h>

int disparado;
int direction;
int tick;


#define INTERVALO 5000

int insere_navemae(t_lista *l_tela){
    insere_fim_lista(0, 3, 1, 0, 1, l_tela); 
	return 1;
}

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

int inicializa_lista_tela( t_lista *l_tela ){
	inicializa_lista(l_tela);
	insere_navemae(l_tela);
	insere_aliens(l_tela);
	insere_barreiras(l_tela);
	insere_nave(l_tela);
	return 1;
}


void Desenha_Borda(){
	int i, j;
	
	for (i = 0; i < 38; i += 37)
		for (j = 0; j < 100; j++)
			{
				move(i, j);
				addch('*');
			}

	for (i = 1; i < 37; i++)
		for (j = 0; j < 100; j += 99)
		{
			move(i, j);
			addch('*');
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


void Desenha_tela(t_lista *l_tela, Alien *alien, Barreira *barreiras, Nave *nave){
	int tipo, lin, col, vel, estado, cont_bar = 0;

	clear();
	Desenha_Borda();

	inicializa_atual_inicio(l_tela);
	for (int i = 0; i < l_tela->tamanho; i++)
	{
		consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tela);

		if (tipo <= 3)
			Desenha_Alien(lin, col, tipo, alien);
		else if (tipo == 4)
			Desenha_Barreira(lin, col, cont_bar++, barreiras);
		incrementa_atual(l_tela);
	}
	refresh();
}

void move_aliens(t_lista *l_tela)
{
	inicializa_atual_inicio(l_tela);
	while(l_tela->atual->tipo < 1)
		incrementa_atual(l_tela);
	while(l_tela->atual->tipo <= 3)	
	{
		incrementa_atual(l_tela);
	}
}

int main(){
    t_lista l_tela;
	Alien alien[3];
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
    if (nlin < 38 || ncol < 100)
	{
		endwin();
		return 0;
	}
    //Aliens
	alien[0] = inicializaAlien1();
	alien[1] = inicializaAlien2();
    alien[2] = inicializaAlien3();
    //Barreiras
    for(int b = 0; b < 4; b++)
        barreiras[b] = inicializaBarreira();
  	 
    Nave nave = inicializaNave();
    Missel missel = inicializaMissel();
    Missel misselalien = inicializaMisselAlien();
   
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
    //Desenha_tela(&l_tela, alien, barreiras, &nave);
		
		if (iter % 100 == 0)
			//move_aliens(&l_tela);
		
		iter++;
		usleep(INTERVALO);
	}
	endwin();
}
