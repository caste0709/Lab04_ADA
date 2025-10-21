#include <stdio.h>
#include <stdlib.h>

typedef int vertex;

typedef struct node *link;
struct node {
    vertex w;
    link next;
};

typedef struct graph *Graph;
struct graph {
    int V;
    int A;
    link *adj;
};

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof(struct node));
    if (a == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    if (G->adj == NULL) {
        fprintf(stderr, "Error de memoria\n");
        exit(1);
    }
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void UGRAPHinsertEdge(Graph G, vertex v, vertex w){
    GRAPHinsertArc(G, w, v);
    GRAPHinsertArc(G, v, w);
}
void imprimirGrafo(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        printf("Nodo %d: ", v);
        link a = G->adj[v];
        while (a != NULL) {
            printf("%d", a->w);
            a = a->next;
            if (a != NULL) printf("->");
        }
        printf("\n");
    }
}

int main() {
    Graph grafo = GRAPHinit(4); 
    GRAPHinsertArc(grafo, 0, 1); 
    GRAPHinsertArc(grafo, 1, 0); 
    GRAPHinsertArc(grafo, 0, 2); 
    GRAPHinsertArc(grafo, 2, 0); 
    GRAPHinsertArc(grafo, 1, 3); 
    GRAPHinsertArc(grafo, 3, 1);
    printf("Grafo original:\n");
    imprimirGrafo(grafo);
    UGRAPHinsertEdge(grafo, 3, 0);
    UGRAPHinsertEdge(grafo, 2, 3);
    printf("Grafo después de insertar algunas aristas:\n");
    imprimirGrafo(grafo);
    return 0;
}