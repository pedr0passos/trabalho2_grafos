#include <stdio.h>
#include <stdlib.h>

typedef struct a {
    int u;
    int v;
    int peso;
}aresta;

/*FUNCOES*/
void r_graph(FILE* input,int n, int m, int matriz[n][n], aresta *a);
void inicializa(int n, int matriz[n][n], int matriz_parcial[n][n]);
int arvore_minima(int n, int m, int matriz[n][n], int matriz_parcial[n][n], aresta *a);
void b_insertionsort(aresta *v, int m);
void atualiza_florestas(int n, int *florestas, int matriz[n][n]);
void conta(int n, int matriz[n][n], int vertice, int *florestas, int cont);
void info(int resultado, int n, int matriz[n][n]);

int main () {

    // n=numero de vertices m=numero de arestas
    int n, m;

    // lendo valores n e m
    FILE *input=fopen("input/6.txt", "r");
    fscanf(input, "%d %d\n", &n, &m);

    // criando matriz e vetor com as arestas
    int matriz[n][n], matriz_parcial[n][n], resultado;
    aresta arestas[m];

    inicializa(n,matriz, matriz_parcial);
    r_graph(input,n,m,matriz, arestas);
    b_insertionsort(arestas, m);
    resultado = arvore_minima(n,m,matriz,matriz_parcial,arestas);
    info(resultado, n,matriz_parcial);
    
    return 0;
}

void inicializa(int n, int matriz[n][n], int matriz_parcial[n][n]) {
    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            matriz[i][j]=0;
            matriz_parcial[i][j]=0;
        }
    
}

void b_insertionsort(aresta *v, int m) {
    int  i, j, esquerda, direita, meio;
    aresta auxiliar;
    for (i = 1; i < m; i++) {
        auxiliar = v[i];
        esquerda = 0;
        direita = i;
        while ( esquerda < direita ) {
            meio = ( esquerda + direita )/2;
            if ( v[meio].peso <= auxiliar.peso )    
                esquerda = meio + 1;
            else    
                direita = meio;
        }
        for ( j = i; j > esquerda; j-- ) {
            v[j] = v[j-1];
        }
        v[direita] = auxiliar;        
    }
}

void info(int resultado, int n, int matriz[n][n]) {
    int i, j;
    printf("-------------------------\n");
    for(i=0; i<n; i++)
        for(j=i; j<n; j++)
            if(matriz[i][j]>0)
                printf("(%d,%d):%d\n",i,j,matriz[i][j]);
    printf("-------------------------\n");                
    printf("%d\n", resultado);
}

void r_graph(FILE* input, int n, int m, int matriz[n][n], aresta *a) {
    int i, j, dist, x=0;
    while ( fscanf(input, "%d %d %d\n", &i, &j, &dist) != EOF && x<m ) {
        matriz[i][j]=dist;
        matriz[j][i]=dist;
        a[x].u = i;
        a[x].v = j;
        a[x].peso = dist;
        x++;
    }
    fclose(input);
}

int arvore_minima(int n, int m, int matriz[n][n], int matriz_parcial[n][n], aresta *a) {
    int i,j, floresta[n], soma=0;
    atualiza_florestas(n,floresta,matriz_parcial);
    for (i=0; i<m; i++)
        if ( floresta[a[i].u] != floresta[a[i].v] ) {
            matriz_parcial[a[i].u][a[i].v]=a[i].peso;
            matriz_parcial[a[i].v][a[i].u]=a[i].peso;
            soma += a[i].peso;
            atualiza_florestas(n,floresta,matriz_parcial);
        }
    return soma;
}

void atualiza_florestas(int n, int *florestas, int matriz[n][n]) {
    int cont=0, i;
    for (i=0; i<n; i++)
        florestas[i]=-1;
    for (i=0; i<n; i++)
        if(florestas[i]==-1) {
            cont++;
            conta(n, matriz, i, florestas, cont);
        }
}

void conta(int n, int matriz[n][n], int vertice, int *florestas, int cont) {
    florestas[vertice] = cont;
    for(int j=0; j<n; j++)
        if ( matriz[vertice][j] > 0 && florestas[j] == -1)
                conta(n, matriz, j, florestas, cont);
}