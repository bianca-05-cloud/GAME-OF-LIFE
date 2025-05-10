#include"header_t3.h"

void agaugare_la_inceput(lista** cap_matrice, int i, int j)
{
    lista* nou = (lista*)malloc(sizeof(lista));
    nou->x.l = i;
    nou->x.c = j;
    nou->next = *cap_matrice;
    *cap_matrice = nou;
}

void adaugare_la_final(lista** cap_matrice, int i, int j)
{
    if (*cap_matrice == NULL)
    {
        agaugare_la_inceput(cap_matrice, i, j);
        return;
    }

    lista* aux = *cap_matrice;
    lista* nou = (lista*)malloc(sizeof(lista));
    nou->x.l = i;
    nou->x.c = j;
    nou->next = NULL;

    while (aux->next != NULL)
        aux = aux->next;

    aux->next = nou;
}

lista* matrice_devine_lista(lista* cap_matrice, char** matricea_initiala, int N, int M)
{
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            if(matricea_initiala[i][j] == 'X')
            {
                adaugare_la_final(&cap_matrice, i, j);
            }
        }
    }
    return cap_matrice;
}

int vecinii(char** m, int N, int M, int i, int j)
{
    int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int d, aux = 0;

    for(d = 0; d < 8; d++)
    {
        int ni = i + x[d];
        int nj = j + y[d];

        if(ni >= 0 && ni < N && nj >= 0 && nj < M)
        {
            if(m[ni][nj] == 'X')
                aux++;
        }
    }
    return aux;
}

void actualizare_matrice_dreapta(char** m, char** q, int N, int M)
{
    int i, j, vecinii_vii;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            vecinii_vii = vecinii(m, N, M, i, j);

            if(m[i][j] == 'X' && (vecinii_vii < 2 || vecinii_vii > 3))
                q[i][j] = '+';
            else if(m[i][j] == '+' && vecinii_vii == 3)
                q[i][j] = 'X';
            else
                q[i][j] = m[i][j];
        }
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            m[i][j] = q[i][j];
}

void actualizare_matrice_stanga(char** m, char** p, int N, int M)
{
    int i, j, vecinii_vii;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            vecinii_vii = vecinii(m, N, M, i, j);

            if(m[i][j] == '+' && vecinii_vii == 2)
                p[i][j] = 'X';
            else
                p[i][j] = m[i][j];
        }
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            m[i][j] = p[i][j];
}

void creeare_arbore(node* root, lista** capete_dreapta, lista** capete_stanga, int nivel, int max_k)
{
    if(nivel == max_k)
        return;

    root->left = (node*)malloc(sizeof(node));
    root->left->val = capete_stanga[nivel];
    root->left->left = root->left->right = NULL;

    root->right = (node*)malloc(sizeof(node));
    root->right->val = capete_dreapta[nivel];
    root->right->left = root->right->right = NULL;

    creeare_arbore(root->left, capete_dreapta, capete_stanga, nivel + 1, max_k);
    creeare_arbore(root->right, capete_dreapta, capete_stanga, nivel + 1, max_k);
}

void trecere_din_lista_in_matrice(lista* cap, char** m, int N, int M)
{
    int i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            m[i][j] = '+';

    while(cap != NULL)
    {
        m[cap->x.l][cap->x.c] = 'X';
        cap = cap->next;
    }
}

void preordine(node* root, char** m, int N, int M, FILE* out)
{
    if(root == NULL)
        return;

    trecere_din_lista_in_matrice(root->val, m, N, M);

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            fprintf(out, "%c", m[i][j]);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");

    preordine(root->left, m, N, M, out);
    preordine(root->right, m, N, M, out);
}



