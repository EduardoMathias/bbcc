#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include "elem.h"
#include <stdlib.h>
#include <time.h>

int disparado;
int direction;
int tick;

//Moldando o Formato da Barreira
#define condformato1 ((k == 0 && b == 0) || (k== 6 && b == 0) ||(k == 2 && b == 2) || (k == 4 && b == 2) || (k == 3 && b == 2))
#define INTERVALO 5000

int insere_navemae(t_lista *l_tela)
{
    insere_fim_lista(0, 3, 1, 0, 1, l_tela); 
	return 1;
}

int insere_aliens( t_lista *l_tela )
{
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

int insere_barreiras(t_lista *l_tela)
{
	int i;
	for (i = 0; i < 4; i++)
        insere_fim_lista(4, 31, (15 + 21*i), 0, 1, l_tela);
	return 1;
}

int insere_nave(t_lista *l_tela)
{
	insere_fim_lista(5, 35, 43, 0, 1, l_tela);
	return 1;
}

int inicializa_lista_tela( t_lista *l_tela )
{
	inicializa_lista(l_tela);
	insere_navemae(l_tela);
	insere_aliens(l_tela);
	insere_barreiras(l_tela);
	insere_nave(l_tela);
	return 1;
}


void Desenha_borda()
{
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


void Desenha_alien(int lin, int col, int tipo, Alien *alien)
{
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

void MudaDirection(Alien *alien, int limiteTela){
    for(int i= 0; i < 55; i++){
        if(alien[i].x == limiteTela)
            direction = -1;
        if(alien[i]. x == 1)
            direction = 1;
    }
}

/*void AtualizaAlien(Alien *alien){
    for(int i=0; i < 55; i++){
        if(alien[i].vivo == 1){
            alien[i].x+= direction;
        }
    }
}*/

void desenhaBarreira(Barreira barreira1[3][7], Barreira barreira2[3][7], Barreira barreira3[3][7], Barreira barreira4[3][7]){
for (int i = 0; i < 3; i++){
 for (int j=0; j < 7; j++){
 	if(barreira1[i][j].atingido == 0)
      mvprintw((barreira1[i][j]).y, (barreira1[i][j]).x, (barreira1[i][j]).bloco);
  	if(barreira2[i][j].atingido == 0)
  		mvprintw((barreira2[i][j]).y, (barreira2[i][j]).x, (barreira2[i][j]).bloco);
  	if(barreira3[i][j].atingido == 0)
  		mvprintw((barreira3[i][j]).y, (barreira3[i][j]).x, (barreira3[i][j]).bloco);
  	if(barreira4[i][j].atingido == 0)
  		mvprintw((barreira4[i][j]).y, (barreira4[i][j]).x, (barreira4[i][j]).bloco);
 }
}}

void disparaMissel(Missel missel, Missel misselalien){
    if(disparado){
    mvprintw(missel.y, missel.x, missel.tiro);
    mvprintw(misselalien.y, misselalien.x, misselalien.tiro);}
    disparado = 0;
}

int main(){
	Alien alien[3];
	Barreira barreira1[3][7], barreira2[3][7], barreira3[3][7], barreira4[3][7];
	int key,ncol,nlin;
	int cont,cont2,cont3,cont4 = 0;

//inicializa tela
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
	alien[1] = inicializaAlien1();
	alien[2] = inicializaAlien2();
    alien[3] = inicializaAlien3();
    //Barreiras
    for(int b = 0; b < 3; b++){
  	 for (int k= 0; k < 7; k++){
  	 	if(condformato1){
  	 	barreira1[b][k].atingido = 1;
  	 	barreira2[b][k].atingido = 1;
  	 	barreira3[b][k].atingido = 1;
  	 	barreira4[b][k].atingido = 1;}
  	 	else{
    	barreira1[b][k]= inicializaBarreira(ncol/15 + k, nlin - 6 + b);
    	barreira2[b][k]= inicializaBarreira(ncol/15 + 20 + k, nlin - 6 + b);
    	barreira3[b][k]= inicializaBarreira(ncol/15 + 40 + k, nlin - 6 + b);
    	barreira4[b][k]= inicializaBarreira(ncol/15 + 60 + k, nlin - 6 + b);}
    }
	}
    Nave nave = inicializaNave(ncol/2, nlin-2);
    Missel missel = inicializaMissel(nave.x, nlin -4);
    Missel misselalien = inicializaMisselAlien(alien[0].x +2 , alien[0].y + 4);
    disparado = 0;
    direction = 1;
    tick = 0;
while((key = getch())){
	if(key == ' '){
        disparado = 1;
    }
	else
		if(key == KEY_LEFT && nave.x > 0) {
    		nave.x--;
  		}
	else if (key == KEY_RIGHT && nave.x <= ncol-6) {
    	nave.x++;
  	}
	else if (key == 'q') {
    	endwin();
    	exit(0);
  	}
  	clear();
	usleep(20000);
	mvprintw(nave.y,nave.x,nave.cima);
	mvprintw(nave.y+1,nave.x,nave.baixo);
    //
    srand(time(NULL));
    int r = rand ()% (54 + 1);
    misselalien.x = alien[r].x + 2;
    misselalien.y = alien[r].y + 4;
    //
    missel.x = nave.x + 1;
    disparaMissel(missel, misselalien);
    missel.y-= 0.001;
    misselalien.y += 0.000001;
	desenhaBarreira(barreira1,barreira2,barreira3,barreira4);
	desenhaAlien(alien);
    //AtualizaAlien(alien);
    MudaDirection(alien, nlin);
    tick++;
	refresh();
}
   endwin();
}
