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
void quicksort(aresta *v, int esquerda, int direita);
void particao(aresta *v, int esquerda, int direita, int *i, int*j);
int atualiza_arvores(int n, int *arvores, int matriz[n][n]);
void conta(int n, int matriz[n][n], int vertice, int *arvores, int cont);
void info(int resultado, int n, int matriz[n][n]);

int main () {

    // n=numero de vertices m=numero de arestas
    int n, m;

    // lendo valores n e m
    FILE *input=fopen("input/9.txt", "r");
    fscanf(input, "%d %d\n", &n, &m);

    // criando matriz e vetor com as arestas
    int matriz[n][n], matriz_parcial[n][n], resultado;
    aresta arestas[m];

    inicializa(n,matriz, matriz_parcial);
    r_graph(input,n,m,matriz, arestas);
    quicksort(arestas, 0, m-1);
    resultado = arvore_minima(n,m,matriz,matriz_parcial,arestas);
    info(resultado, n, matriz_parcial);
    
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

void quicksort(aresta *v, int esquerda, int direita) {
    int i, j;
    particao(v,esquerda,direita, &i, &j);
    if ( i < direita )
        quicksort(v, i, direita);
    if ( j > esquerda ) 
        quicksort(v, esquerda, j);
}

void particao(aresta *v, int esquerda, int direita, int *i, int*j) {
    aresta aux, pivo;
    pivo = v[direita];
    *i = esquerda;
    *j = direita;
    while ( (*i) <= (*j) ) {
        while (v[*i].peso < pivo.peso && (*i) < direita)
            (*i)++;
        while ( v[*j].peso > pivo.peso && (*j) > esquerda )
            (*j)--;
        if ( (*i) <= (*j) ) {
            aux = v[*i];
            v[*i] = v[*j];
            v[*j] = aux;
            (*i)++;
            (*j)--;
        }
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
    int i, arvores[n], soma=0, qt_arvores;
    qt_arvores=atualiza_arvores(n,arvores,matriz_parcial);
    for (i=0; i<m && qt_arvores>1; i++)
        if ( arvores[a[i].u] != arvores[a[i].v] ) {
            matriz_parcial[a[i].u][a[i].v]=a[i].peso;
            matriz_parcial[a[i].v][a[i].u]=a[i].peso;
            soma += a[i].peso;
            qt_arvores=atualiza_arvores(n,arvores,matriz_parcial);
        }
    return soma;
}

int atualiza_arvores(int n, int *arvores, int matriz[n][n]) {
    int cont=0, i;
    for (i=0; i<n; i++)
        arvores[i]=-1;
    for (i=0; i<n; i++)
        if(arvores[i]==-1) {
            cont++;
            conta(n, matriz, i, arvores, cont);
        }
    return cont;
}

void conta(int n, int matriz[n][n], int vertice, int *arvores, int cont) {
    arvores[vertice] = cont;
    for(int j=0; j<n; j++)
        if ( matriz[vertice][j] > 0 && arvores[j] == -1)
                conta(n, matriz, j, arvores, cont);
}