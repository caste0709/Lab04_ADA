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

void GRAPHremoveArc(Graph G, vertex v, vertex w) {
    link prev = NULL, actu = G->adj[v];
    while (actu != NULL) {
        if (actu->w == w) {
            if (prev == NULL) { 
                G->adj[v] = actu->next;
            } 
            else {
                prev->next = actu->next;
            }
            free(actu);
            G->A--;
            break;
        }
        prev = actu;
        actu = actu->next;
    }
    prev = NULL;
    actu = G->adj[w];
    while (actu != NULL) {
        if (actu->w == v) {
            if (prev == NULL) {
                G->adj[w] = actu->next;
            } 
            else {
                prev->next = actu->next;
            }
            free(actu);
            G->A--;
            break;
        }
        prev = actu;
        actu = actu->next;
    }
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
    printf("Grafo antes de eliminar el arco:\n");
    imprimirGrafo(grafo);
    GRAPHremoveArc(grafo, 0, 1);
    printf("\nGrafo después de eliminar el arco 0-1:\n");
    imprimirGrafo(grafo);

    return 0;
}
