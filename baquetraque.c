#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct rainha{
    int lin;
    int col;
    int diagonal1;
    int diagonal2;
};
typedef struct rainha rainha;

int insere_tabuleiro(rainha *rainhas){
    
    return 1;
}

int main(void){
    rainha rainhas[8];
    int tabuleiro[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++)
            tabuleiro[i][j] = 0;
    }
    srand(time(NULL));
    int r = rand() % 7;
    rainhas[0].lin = r;
    rainhas[0].col = r;
    

}