struct t_nodo
{
    int dado,dado2;
    struct t_nodo *prev;
    struct t_nodo *prox;
};
typedef struct t_nodo t_nodo;

struct t_fila
{
    t_nodo *ini;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_fila t_fila;

int inicializa_fila(t_fila *f);
int fila_vazia(t_fila *f);
int tamanho(t_fila *f);
int enfileira(int id,int t, t_fila *f);
int desenfileira(int *id, int *t, t_fila *f);
int removefila(int *id, int *t, t_fila *f);
void imprimefila(t_fila *f);
int Destroi_Fila(t_fila *f);
