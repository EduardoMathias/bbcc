#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include "elem.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int placar,aliens_mortos = 0;
int disparado, disparado_alien,partida;

#define INTERVALO 38000
#define EXPLOSAO "\\'/- -/,\\"
#define BARREIRA   " AMMMA AMMMMMAMM   MM"
#define BLOCOS     "AM" 

int insere_aliens( t_lista *l_tela ){
	int i, j;
	for (i = 0; i < 11; i++)
		insere_fim_lista(1, 7, (5 + 7*i), 0+partida, 1, l_tela); 	
	for (i = 0; i < 2; i++)
		for (j = 0; j < 11; j++)
			insere_fim_lista(2, (11 + 4*i), (4 + 7*j), 0+partida, 1, l_tela); 
	for (i = 0; i < 2; i++)
		for (j = 0; j < 11; j++)
			insere_fim_lista(3, (19 + 4*i), (4 + 7*j), 0+partida, 1, l_tela);
	return 1;
}

int insere_barreira(int lin, int col, t_lista *l_tela)
{
    int l_atual, c_atual;
    unsigned int i, ncol;

    ncol = strlen(BARREIRA) / 3;
    for (i = 0; i < strlen(BARREIRA); i++)
    {
        l_atual = lin + (i / ncol);
        c_atual = col + (i % ncol);
        
        if (BARREIRA[i] == BLOCOS[0])
        {
            if (!insere_fim_lista(4, l_atual, c_atual, 0, 1, l_tela))
                return 0;
        }
        else if (BARREIRA[i] == BLOCOS[1])
        {
            if (!insere_fim_lista(5, l_atual, c_atual, 0, 1, l_tela))
                return 0;
        }
    }

    return 1;
}

int insere_barreiras(t_lista *l_tela)
{
    int i;
    for (i = 0; i < 4; i++)
        if (!insere_barreira(31, (15 + 21*i), l_tela))
            return 0;

    return 1;
}


int insere_navemae(t_lista *l_tela){
    insere_fim_lista(7, 3, 1, 0, 1, l_tela); 
	return 1;
}

int insere_nave(t_lista *l_tela){
	insere_fim_lista(6, 35, 43, 0, 1, l_tela);
	return 1;
}

int insere_missel(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_fim(l_tela);
    insere_fim_lista(1,37,l_tela->atual->x +1,0,1,l_tiro);
    return 1;
}

int insere_missel_alien(t_lista *l_tela, t_lista *l_tiro){
    /*srand(time(NULL));
    int r = rand ()% (54 + 1);
    inicializa_atual_ultimo_alien(l_tela);
    for(int i = 0; i < r; i++)
        decrementa_atual(l_tela);*/
    inicializa_atual_inicio(l_tela);
    incrementa_atual(l_tela);
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
    wattron(stdscr, COLOR_PAIR(2));
    resize_term(38, 100);
    box(stdscr,0,0);
}

void Desenha_NaveMae(int lin, int col, NaveMae *navemae){
    wattron(stdscr, COLOR_PAIR(1));
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

void Desenha_Bloco1(int lin, int col,Bloco *bloco1){
    int i,largura, l_atual, c_atual;
	char *desenho;
    desenho = bloco1->formato;
    largura = bloco1->largura;
    for (i = 0; i < strlen(desenho); i++)
    {
        l_atual = lin + (i / largura);
        c_atual = col + (i % largura);
        move(l_atual, c_atual);
        addch(desenho[i]);
    }
}

void Desenha_Bloco2(int lin, int col,Bloco *bloco2){
    int i,largura, l_atual, c_atual;
	char *desenho;
    desenho = bloco2->formato;
    largura = bloco2->largura;
    for (i = 0; i < strlen(desenho); i++)
    {
        l_atual = lin + (i / largura);
        c_atual = col + (i % largura);
        move(l_atual, c_atual);
        addch(desenho[i]);
    }
}

void Desenha_Missel_Nave(t_lista *l_tiro,Missel *missel_nave){
    wattron(stdscr, COLOR_PAIR(2));
    if(disparado){
    int tipo, lin, col, vel, estado = 0;
    inicializa_atual_inicio(l_tiro);
    consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tiro);
    mvprintw(lin, col,missel_nave->tiro);}

}

void Desenha_Missel_Alien(t_lista *l_tiro,Missel *missel_alien){
    wattron(stdscr, COLOR_PAIR(2));
    if(disparado_alien){
    int tipo, lin, col, vel, estado = 0;
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tiro);
    mvprintw(lin, col,missel_alien->tiro);}

}

void Desenha_Explosao(int lin,int col,t_lista *l_tela){
    mvprintw(lin, col, EXPLOSAO);
    l_tela->atual->condicao = 3;
}


void Desenha_tela(t_lista *l_tela, Alien *alien, Bloco *bloco1, Bloco *bloco2, Nave *nave, NaveMae *navemae){
	int tipo, lin, col, vel, estado= 0;

	Desenha_Borda();
    DesenhaPlacar();
	inicializa_atual_inicio(l_tela);
	for (int i = 0; i < l_tela->tamanho; i++)
	{
		consulta_item_atual(&tipo, &lin, &col, &vel, &estado, l_tela);
		if (tipo <= 3){
            if(estado == 1){
			Desenha_Alien(lin, col, tipo, alien);}
            if(estado == 2){
            Desenha_Explosao(lin,col, l_tela);
            }}
		else if (tipo == 4){
            if(estado == 1)
			Desenha_Bloco1(lin, col, bloco1);}
        else if(tipo == 5){
            if(estado == 1)
            Desenha_Bloco2(lin,col,bloco2);}
        else if(tipo == 7){
            if(estado == 1)
                Desenha_NaveMae(lin,col, navemae);}
        else if(tipo == 6)
            Desenha_Nave(lin, col, nave);
		incrementa_atual(l_tela);
    }
}


int AtualizaAliens(t_lista *l_tela, Alien *alien, int *direcao){
    int limite = 0;
    int desce = 0;
    inicializa_atual_inicio(l_tela);
    incrementa_atual(l_tela);
    for(int i= 0; i < 55; i++){
    l_tela->atual->x+= *direcao;
    if((l_tela->atual->x >= 95) && (l_tela->atual->condicao != 3)){
           limite = 1;
           desce = 1;
    }
    if((l_tela->atual->x <= 1) && (l_tela->atual->condicao != 3)){
        limite = -1;
        desce = 1;
    }
    alien[1].forma_inicial = alien[1].forma_inicial ? 0: 1;
    alien[2].forma_inicial = alien[2].forma_inicial ? 0: 1;
    alien[3].forma_inicial = alien[3].forma_inicial ? 0: 1;
    incrementa_atual(l_tela);}
    if(limite == 1)
        *direcao*=-1;
    if(limite == -1)
        *direcao*=-1;
    
    inicializa_atual_inicio(l_tela);
    incrementa_atual(l_tela);
    for(int i = 0; i < 55; i++){
        l_tela->atual->y+=desce;
        incrementa_atual(l_tela);
    }
    inicializa_atual_ultimo_alien(l_tela);
    if(l_tela->atual->y >= 35){
        endwin();
        exit(1);}
    return 1;
}

int AtualizaNaveMae(t_lista *l_tela,int *anda){
    inicializa_atual_inicio(l_tela);
    l_tela->atual->x += *anda;
    if(l_tela->atual->x >= 97)
        l_tela->atual->x = 0;
    return 1;
}

void Atualiza_Missel_x(t_lista *l_tela,t_lista *l_tiro){
    if(disparado != 0){
    inicializa_atual_fim(l_tela);
    inicializa_atual_inicio(l_tiro);
    l_tiro->atual->x= l_tela->atual->x + 1;
}}

void Atualiza_Missel_y(t_lista *l_tiro){
    if(disparado != 0){
    inicializa_atual_inicio(l_tiro);
    if(l_tiro->atual->y <= 0){
        l_tiro->atual->y = 37;
        disparado = 0;

    }
    l_tiro->atual->y -= 0.01;
}}

void Atualiza_MisselAlien(t_lista *l_tela,t_lista *l_tiro){
    if(disparado_alien == 0){
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

}

void Anda_MisselAlien_y(t_lista *l_tiro){
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    if(l_tiro->atual->y >= 38){
        l_tiro->atual->y = 1;
        disparado_alien = 0;
    }
    l_tiro->atual->y += 1;

}


void AtingiuAlien(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_ultimo_alien(l_tela);
    inicializa_atual_inicio(l_tiro);
    for(int i= 0; i < 55; i++){
    if(l_tiro->atual->tipo == 1){
        int meio = l_tela->atual->x;
        if((meio - 2  <= l_tiro->atual->x) &&(meio + 2 >= l_tiro->atual->x) && (l_tela->atual->y == l_tiro->atual->y)){
            if(l_tela->atual->condicao == 1){
            l_tela->atual->condicao = 2;
            placar += 1;
            l_tiro->atual->y = 37;
            disparado = 0;
            aliens_mortos++;}
        }}
        decrementa_atual(l_tela);
    }
    }

void Atingiu_Tiro_Nave(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_fim(l_tela);
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    int meio = l_tela->atual->x;
    if((meio - 2  <= l_tiro->atual->x) && (meio + 2 >= l_tiro->atual->x) && (l_tela->atual->y == l_tiro->atual->y)){
            endwin();
            exit(1);
    }
}


void AtingiuNaveMae(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_inicio(l_tela);
    inicializa_atual_inicio(l_tiro);
    if((l_tela->atual->x+1 == l_tiro->atual->x) && (l_tela->atual->y == l_tiro->atual->y)){
            if(l_tela->atual->condicao == 1){
                l_tela->atual->condicao = 3;
                placar += 300;
            }
}
}

void Atingiu_Alien_Fileira_Nave(t_lista *l_tela){
    inicializa_auxiliar_fim(l_tela);
    inicializa_atual_ultimo_alien(l_tela);
    for(int i= 0; i < 55; i++){
         if(l_tela->atual->y +2 == l_tela->auxiliar->y){
            endwin();
            exit(1);}
        decrementa_atual(l_tela);}
    }

void Atingiu__TiroNave_Barreira(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_ultimo_alien(l_tela);
    incrementa_atual(l_tela);
    inicializa_atual_inicio(l_tiro);
    while (l_tela->atual->tipo <= 5)
    {
     if(l_tela->atual->condicao != 2){
        if((l_tela->atual->x == l_tiro->atual->x) && (l_tela->atual->y == l_tiro->atual->y)){
            l_tela->atual->condicao = 2;
            disparado = 0;
            }}
            incrementa_atual(l_tela);
    }
}


void Atingiu__TiroALien_Barreira(t_lista *l_tela, t_lista *l_tiro){
    inicializa_atual_ultimo_alien(l_tela);
    incrementa_atual(l_tela);
    inicializa_atual_inicio(l_tiro);
    incrementa_atual(l_tiro);
    while (l_tela->atual->tipo <= 5)
    {
     if(l_tela->atual->condicao != 2){
        if(((l_tela->atual->x == l_tiro->atual->x) && (l_tela->atual->y == l_tiro->atual->y)) || ((l_tela->atual->x+1 == l_tiro->atual->x) && (l_tela->atual->y == l_tiro->atual->y))){
            l_tela->atual->condicao = 2;
            disparado_alien = 0;
            }}
            incrementa_atual(l_tela);}
}

void Raspou_Alien_Barreira(t_lista *l_tela){
    inicializa_auxiliar_primeira_barreira(l_tela);
    for(int i = 0; i < 64; i++){
        inicializa_atual_ultimo_alien(l_tela);
        for(int j= 0; j < 55; j++){
            if((l_tela->atual->x == l_tela->auxiliar->x) && (l_tela->atual->y+2 == l_tela->auxiliar->y)){
                if(l_tela->atual->condicao != 2)
                    l_tela->auxiliar->condicao = 2;}
            decrementa_atual(l_tela);
        }}
        incrementa_auxiliar(l_tela);
    }

void Recomecar(t_lista*l_tela,t_lista*l_tiro){
    destroi_lista(l_tela);
    destroi_lista(l_tiro);
    inicializa_lista_tela(l_tela);
    inicializa_lista_tiro(l_tela, l_tiro);
    aliens_mortos = 0;
    partida++;
}

int main(){
    t_lista l_tela,l_tiro;
	Alien alien[4];
	Bloco bloco1;
    Bloco bloco2;
	int key,ncol,nlin;
    int iter,iter_alien = 1;
    disparado = 0;
    disparado_alien = 0;
    int anda = 1;
    int direcao = 1;
    partida = 0;
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
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_WHITE, -1);
    //Naves
    Nave nave = inicializaNave();
    NaveMae navemae = inicializaNaveMae();
    //Aliens
	alien[1] = inicializaAlien1();
	alien[2] = inicializaAlien2();
    alien[3] = inicializaAlien3();
    //Barreiras
    bloco1 = inicializaBloco1();
    bloco2 = inicializaBloco2();
    //Misseis
    Missel missel_nave = inicializaMissel();
    Missel missel_alien = inicializaMisselAlien();
while(1){
    clear();
    key = getch();
	if(key == ' '){
        disparado = 1;
    }
	else
		if(key == KEY_LEFT){
            inicializa_atual_fim(&l_tela);
            if(l_tela.atual->x > (2))
             anda_item_atual_esquerda(&l_tela);
  		    }
	else if (key == KEY_RIGHT){
            inicializa_atual_fim(&l_tela);
            if(l_tela.atual->x < (94))
             anda_item_atual_direita(&l_tela);
  	}
	else if (key == 'q') {
    	endwin();
    	exit(0);
  	}

    Desenha_tela(&l_tela,alien,&bloco1, &bloco2, &nave, &navemae);
    Atualiza_Missel_x(&l_tela,&l_tiro);
    Atualiza_MisselAlien(&l_tela, &l_tiro);
    Desenha_Missel_Nave(&l_tiro,&missel_nave);
    Desenha_Missel_Alien(&l_tiro, &missel_alien);
    Atualiza_Missel_y(&l_tiro);
    Anda_MisselAlien_y(&l_tiro);
    AtingiuAlien(&l_tela, &l_tiro);
    AtingiuNaveMae(&l_tela, &l_tiro);
    Atingiu_Tiro_Nave(&l_tela,&l_tiro);
    Atingiu_Alien_Fileira_Nave(&l_tela);
    Atingiu__TiroNave_Barreira(&l_tela, &l_tiro);
    Atingiu__TiroALien_Barreira(&l_tela, &l_tiro);
    Raspou_Alien_Barreira(&l_tela);
    if(iter > (30 - aliens_mortos - l_tela.ini->prox->velocidade)){
        AtualizaAliens(&l_tela, alien, &direcao);
        if(disparado_alien ==  0)
            disparado_alien = 1;
        iter = 1;
        }
    if(iter_alien > 100){
        disparado_alien = 1;
        iter_alien = 0;}
    if(iter % 5000){
        AtualizaNaveMae(&l_tela, &anda);
    }
     if(aliens_mortos == 55){
         Recomecar(&l_tela,&l_tiro);
     }
    refresh();   
	usleep(INTERVALO);
    iter++;
	}
	endwin();
}

