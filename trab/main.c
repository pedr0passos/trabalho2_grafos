#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0
#define infinito INT_MAX
int confere=0;

/*FUNCOES*/
void r_graph(FILE* input,int n, int m, int matriz[n][n]);
void print_m(int n, int matriz[n][n]);
void inicializa(int n, int matriz[n][n]);
void conf();

int main () {

    int n, m;
    FILE *input=fopen("input/input.txt", "r");
    fscanf(input, "%d %d\n", &n, &m);
    int matriz[n][n], dist[n], p[n];

    inicializa(n,matriz);
    r_graph(input,n,m,matriz);
    fclose(input);
    print_m(n, matriz);
    return 0;
}

void conf() {
    printf("%d\n", confere++);
}

void inicializa(int n, int matriz[n][n]) {
    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            matriz[i][j]=0;
}

void print_m(int n, int matriz[n][n]) {
    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

void r_graph(FILE* input, int n, int m, int matriz[n][n]) {
    int pos1, pos2, dist;
    while ( fscanf(input, "%d %d %d\n", &pos1, &pos2, &dist) != EOF ) {
        matriz[pos1][pos2]=dist;
    }
    fclose(input);
}

void dijkstra(int *dist, int *p, int n, int matriz[n][n] ) {
    
}