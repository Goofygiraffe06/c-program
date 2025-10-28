#include <stdio.h>
#define MAX 30

typedef struct edge {
    int u, v, w;
} edge;

typedef struct edgelist {
    edge data[MAX];
    int n;
} edgelist;

edgelist elist, spanlist;
int G[MAX][MAX], n;

void kruskal();
int find(int belongs[], int vertexno);
void union1(int belongs[], int c1, int c2);
void sort();
void print();

void main() {
    int i, j;
    printf("\nEnter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &G[i][j]);

    kruskal();
    print();
}

void kruskal() {
    int belongs[MAX], i, j, cno1, cno2;
    elist.n = 0;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (G[i][j] != 0) {
                elist.data[elist.n].u = i;
                elist.data[elist.n].v = j;
                elist.data[elist.n].w = G[i][j];
                elist.n++;

