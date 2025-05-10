#include"header_t3.h"

int main(int argc, char* argv[])
{
    int T, N, M, K;
    int k;
 
    FILE *in, *out;
    in = fopen(argv[1], "rt");
   
 
    if(in == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }
 
    out = fopen(argv[2], "wt");
    
 
    if(out == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }
 
    fscanf(in, "%d", &T);  

    if(T==3)
    {
    fscanf(in, "%d %d", &N, &M);  
    fscanf(in, "%d", &K);  

    
    char** matricea_initiala = (char**) malloc (N * sizeof(char*));

    int i, j;

    for(i=0;i<N;i++)
    {
        matricea_initiala[i]=(char*) malloc (M * sizeof(char));
        
    }

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            fscanf(in, " %c", &matricea_initiala[i][j]);
        }
    }
    fclose(in);

    
    
        // conversie initiala in lista
        lista* cap_matrice = matrice_devine_lista(NULL, matricea_initiala, N, M);

        // alocare matrici auxiliare
        char** q = (char**)malloc(N * sizeof(char*)); // GOL normal
        char** p = (char**)malloc(N * sizeof(char*)); // GOL modificat
        for(int i = 0; i < N; i++)
        {
            q[i] = (char*)malloc(M * sizeof(char));
            p[i] = (char*)malloc(M * sizeof(char));
        }

        // vectorii de liste pentru capete
        lista** capete_dreapta = (lista**)malloc(K * sizeof(lista*));
        lista** capete_stanga = (lista**)malloc(K * sizeof(lista*));

        for(int k = 0; k < K; k++)
        {
            actualizare_matrice_dreapta(matricea_initiala, q, N, M);
            capete_dreapta[k] = matrice_devine_lista(NULL, q, N, M);

            actualizare_matrice_stanga(matricea_initiala, p, N, M);
            capete_stanga[k] = matrice_devine_lista(NULL, p, N, M);
        }

        // radacina arbore
        node* root = (node*)malloc(sizeof(node));
        root->left = root->right = NULL;
        root->val = cap_matrice;

        creeare_arbore(root, capete_dreapta, capete_stanga, 0, K);

        // matrice temporara pt reconstructie
        char** matrice_output = (char**)malloc(N * sizeof(char*));
        for(int i = 0; i < N; i++)
            matrice_output[i] = (char*)malloc(M * sizeof(char));

        preordine(root, matrice_output, N, M, out);

        fclose(out);

        for(i = 0; i < N; i++)
    {
        free(matricea_initiala[i]);
        free(q[i]);
        free(p[i]);
        free(matrice_output[i]);
    }


    free(matricea_initiala);
    free(q);
    free(p);
    free(matrice_output);
    }
        
    return 0;

    }   