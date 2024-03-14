/* Grafo.h */

#ifndef GRAFO_H
#define GRAFO_H

typedef struct No {
	int elemento;
	struct No *prox;
} No;

typedef struct Grafo {
	int numVertices;
	No **listaAdj;
} Grafo;

typedef struct Pilha {
	int elemento;
	No* topo;
} Pilha;

typedef struct Fila {
	int elemento;
	No* primeiro;
	No* ultimo;
} Fila;

/* Procedimentos relacionados ao grafo */
No* novoNo(int elemento);
Grafo* novoGrafo(int numVertices);
void adicionarAresta(Grafo* grafo, int fonte, int destino);
void adicionarVertice(Grafo* grafo, int numVertices);
void removerAresta(Grafo* grafo, int fonte, int destino);
int contarArestas(Grafo* grafo, int vertice);
void removerVertice(Grafo* grafo, int vertice);
void BFS(Grafo* grafo);
void DFS(Grafo* grafo);
void FTD(Grafo* grafo, int vertice);
void FTI(Grafo* grafo, int vertice);
void mostrar(Grafo* grafo);

/* Procedimento e funções relacionados a pilha ou fila */
void push(Pilha* pilha, int elemento);
int pop(Pilha* pilha);
void enqueue(Fila *fila, int elemento);
int dequeue(Fila* fila);

#endif /* GRAFO_H */
