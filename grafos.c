#include <stdio.h>
#include <stdlib.h>

#define vertex int

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

int GRAPHindeg(Graph G, vertex v) {
    int indeg = 0;
    for (vertex u = 0; u < G->V; u++) {
        for (link a = G->adj[u]; a != NULL; a = a->next) {
            if (a->w == v)
                indeg++;
        }
    }
    return indeg;
}

void GRAPHshow(Graph G, vertex v) {
    printf("Vértices adyacentes a %d: ", v);
    for (link a = G->adj[v]; a != NULL; a = a->next)
        printf("%d ", a->w);
    printf("\n");
}

void GRAPHdestroy(Graph G) {
    for (int v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL) {
            link temp = a;
            a = a->next;
            free(temp);
        }
    }
    free(G->adj);
    free(G);
    printf("Grafo destruido\n");
}

int main() {
    Graph G = GRAPHinit(4);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 1, 3);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 3, 1);

    for (int i = 0; i < G->V; i++) {
        printf("%d: ", i);
        for (link a = G->adj[i]; a != NULL; a = a->next)
            printf("%d ", a->w);
        printf("\n");
    }

    for (int i = 0; i < G->V; i++) {
        printf("Grado de entrada de %d: %d\n", i, GRAPHindeg(G, i));
    }

    GRAPHshow(G, 1);
    GRAPHshow(G, 2);

    GRAPHdestroy(G);

    return 0;
}
