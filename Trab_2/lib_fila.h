struct t_nodo
{
    int dado;
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

int Inicializa_Fila(t_fila *f);
int Fila_vazia(t_fila *f);
int Insere_Fila(int item, t_fila *f);
int Destroi_Fila(t_fila *f);

