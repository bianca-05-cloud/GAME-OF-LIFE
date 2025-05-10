#include<stdio.h>
#include<stdlib.h>

struct coordonate //structura prin intermediul careia vreau sa salvez coordonatele pe care le modifica jocul
                  //acestea sunt coordonatele pe care le salvez in lista/liste care se salveaza in nodurile arborelui
{
    char l;
    char c;
};

typedef struct coordonate coordonate;

struct lista //structura definita ptr a fi salvata in nodurile arborelui pe care dorim sa-l creeam
{
    coordonate x;
    struct lista* next;
};

typedef struct lista lista;

struct tree
{
    lista* val;
    struct tree* left;
    struct tree* right;
};

typedef struct tree node;


void adaugare_la_inceput(lista** cap_matrice, int i, int j);
void adaugare_la_final(lista** cap_matrice, int i, int j);
lista* matrice_devine_lista(lista* cap_matrice, char** matricea_initiala, int N, int M);
int vecinii(char** m, int N, int M, int i, int j);
void actualizare_matrice_dreapta(char** m, char** q, int N, int M);
void actualizare_matrice_stanga(char** m, char** p, int N, int M);
void creeare_arbore(node* root, lista** capete_dreapta, lista** capete_stanga, int nivel, int max_k);
void trecere_din_lista_in_matrice(lista* cap, char** m, int N, int M);
void preordine(node* root, char** m, int N, int M, FILE* out);


