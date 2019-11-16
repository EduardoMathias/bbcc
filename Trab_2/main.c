#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include "elem.h"
#include <stdlib.h>
#include <time.h>

int placar = 0;
int disparado, disparado_alien;

#define INTERVALO 30000

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

int insere_navemae(t_lista *l_tela){
    insere_fim_lista(6, 3, 1, 0, 1, l_tela); 
	return 1;
}

int insere_nave(t_lista *l_tela){
	insere_fim_lista(5, 35, 43, 0, 1, l_tela);
	return 1;
}

int insere_missel(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_fim(l_tela);
    insere_fim_lista(1,33,l_tela->atual->x +1,0,1,l_tiro);
    return 1;
}

int insere_missel_alien(t_lista *l_tela, t_lista *l_tiro){
    srand(time(NULL));
    int r = rand ()% (54 + 1);
    inicializa_atual_ultimo_alien(l_tela);
    for(int i = 0; i < r; i++)
        decrementa_atual(l_tela);
    insere_fim_lista(1,l_tela->atual->y + 4,l_tela->atual->x +2,0,1,l_tiro);
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

int inicializa_lista_tiro(t_lista *l_tela ,t_lista *l_tiro){
    inicializa_lista(l_tiro);
    insere_missel(l_tela, l_tiro);
    insere_missel_alien(l_tela, l_tiro);
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
	
	if (alien[tipo].forma_inicial == 0)
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

void Desenha_Missel_Nave(t_lista *l_tiro,Missel *missel_nave){
    if(disparado){
    int tipo, lin, col, vel, estado = 0;
    inicializa_atual_inicio(l_tiro);
    consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tiro);
    mvprintw(lin, col,missel_nave->tiro);
    disparado = 0;}

}

void Desenha_Missel_Alien(t_lista *l_tiro,Missel *missel_alien){
    if(disparado_alien){
    int tipo, lin, col, vel, estado = 0;
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tiro);
    mvprintw(lin, col,missel_alien->tiro);
    disparado_alien = 0;}

}



void Desenha_tela(t_lista *l_tela, Alien *alien, Barreira *barreiras, Nave *nave, NaveMae *navemae){
	int tipo, lin, col, vel, estado, cont_bar = 0;

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
}

int AtualizaAliens(t_lista *l_tela, Alien *alien, int *direcao){
    int limite = 0;
    inicializa_atual_inicio(l_tela);
    incrementa_atual(l_tela);
    for(int i= 0; i < 55; i++){
    l_tela->atual->x+= *direcao;
    if(l_tela->atual->x >= 98){
           limite = 1;
    }
    if(l_tela->atual->x <= 1){
        limite = -1;
    }
    alien[1].forma_inicial = alien[1].forma_inicial ? 0: 1;
    alien[2].forma_inicial = alien[2].forma_inicial ? 0: 1;
    alien[3].forma_inicial = alien[3].forma_inicial ? 0: 1;
    incrementa_atual(l_tela);}
    if(limite == 1)
        *direcao*=-1;
    if(limite == -1)
        *direcao*=-1;
    return 1;
}
void Atualiza_Missel_x(t_lista *l_tela,t_lista *l_tiro){
    inicializa_atual_fim(l_tela);
    inicializa_atual_inicio(l_tiro);
    l_tiro->atual->x= l_tela->atual->x + 1;
}

void Atualiza_Missel_y(t_lista *l_tiro){
    inicializa_atual_inicio(l_tiro);
    if(l_tiro->atual->y <= 1){
        l_tiro->atual->y = 33;
    }
    l_tiro->atual->y -= 0.01;
}

void Atualiza_MisselAlien(t_lista *l_tela,t_lista *l_tiro){
    srand(time(NULL));
    int r = rand ()% (54 + 1);
    inicializa_atual_ultimo_alien(l_tela);
    for(int i = 0; i < r; i++)
        decrementa_atual(l_tela);
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    l_tiro->atual->x= l_tela->atual->x + 2;
    l_tiro->atual->y = l_tela->atual->y + 4;

}



void Anda_MisselAlien_y(t_lista *l_tiro){
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    if(l_tiro->atual->y >= 37){
        l_tiro->atual->y = 1;
    }
    l_tiro->atual->y += 0.01;
}

int main(){
    t_lista l_tela,l_tiro;
	Alien alien[4];
	Barreira barreiras[4];
	int key,ncol,nlin;
    int iter = 1;
    disparado = 0;
    disparado_alien = 0;
    int direcao = 1;
    inicializa_lista_tela(&l_tela);
    inicializa_lista_tiro(&l_tela, &l_tiro);
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
    //Misseis
    Missel missel_nave = inicializaMissel();
    Missel missel_alien = inicializaMisselAlien();
while(1){
    clear();
    key = getch();
	if(key == ' '){
        disparado = 1;
        disparado_alien = 1;
    }
	else
		if(key == KEY_LEFT){
            inicializa_atual_fim(&l_tela);
            if(l_tela.atual->x > (2))
             anda_item_atual_esquerda(&l_tela);
  		    }
	else if (key == KEY_RIGHT){
            inicializa_atual_fim(&l_tela);
            if(l_tela.atual->x < (ncol - 6))
             anda_item_atual_direita(&l_tela);
  	}
	else if (key == 'q') {
    	endwin();
    	exit(0);
  	}

    Desenha_tela(&l_tela,alien, barreiras, &nave, &navemae);
    Atualiza_Missel_x(&l_tela,&l_tiro);
    Atualiza_MisselAlien(&l_tela, &l_tiro);
    Desenha_Missel_Nave(&l_tiro,&missel_nave);
    Desenha_Missel_Alien(&l_tiro, &missel_alien);
    Atualiza_Missel_y(&l_tiro);
    Anda_MisselAlien_y(&l_tiro);
    if(iter % 100)
        AtualizaAliens(&l_tela, alien, &direcao);
     
    refresh();   
	usleep(INTERVALO);
    iter++;
	}
	endwin();
}

