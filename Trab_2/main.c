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

void desenhaAlien(Alien *alien){
 for (int i = 0; i < 55; i++){
	if(alien[i].vivo == 1){
	mvprintw(alien[i].y, alien[i].x, alien[i].cima);
	mvprintw(alien[i].y+1, alien[i].x, alien[i].meio);
	mvprintw(alien[i].y+2, alien[i].x, alien[i].baixo);}
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

void AtualizaAlien(Alien *alien){
    for(int i=0; i < 55; i++){
        if(alien[i].vivo == 1){
            alien[i].x+= direction;
        }
    }
}

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
	Alien alien[55];
	Barreira barreira1[3][7], barreira2[3][7], barreira3[3][7], barreira4[3][7];
	int key,ncol,nlin;
	int cont,cont2,cont3,cont4 = 0;
	initscr();
    cbreak();
	noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    getmaxyx(stdscr, nlin, ncol);
    //Aliens
    for (int i = 0; i < 11; i++){
		alien[i] = inicializaAlien1(ncol/18 + (6*i +2), nlin/12);}
    for(int i= 11; i < 22; i++){
		alien[i] = inicializaAlien2(ncol/18 + (6*cont + 1) , nlin/12 + 3.2);
		++cont;}
    for(int i = 22; i < 33; i++){
		alien[i] = inicializaAlien3(ncol/18 + (6*cont2 + 1) , nlin/12 + 6.4);
    	cont2++;}
    for(int i = 33; i < 44; i++){
		alien[i] = inicializaAlien2(ncol/18 + (6*cont3 + 1), nlin/12 + 9.6);
    	cont3++;}
    for (int i = 44; i < 55; i++){
		alien[i] = inicializaAlien3(ncol/18 + (6*cont4 + 1), nlin/12 + 12.8);
    	cont4++;}
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
    AtualizaAlien(alien);
    MudaDirection(alien, nlin);
    tick++;
	refresh();
}
   endwin();
}
