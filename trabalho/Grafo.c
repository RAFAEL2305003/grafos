#include <stdio.h>
#include <stdlib.h>

#include "Grafo.h"

No* novoNo(int elemento) {
	No* novo = (No*)malloc(sizeof(No));

	if(novo) {
		novo->elemento = elemento;
		novo->prox = NULL;
		return novo;
	} else {
		printf("Erro ao tentar alocar memória!\n");
		return NULL;
	}
}

Grafo* novoGrafo(int numVertices) {
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));

	if(grafo) {
		grafo->numVertices = numVertices;
		grafo->listaAdj = (No**)calloc(numVertices, sizeof(No*));

		if(grafo->listaAdj) {
			for(int i = 0; i < numVertices; i++)
				grafo->listaAdj[i] = NULL;
			return grafo;
		} else {
			printf("Erro ao tentar alocar memória!\n");
			return NULL;
		}
	} else {
		printf("Erro ao tentar alocar memória!\n");
		return NULL;
	}
}

void adicionarAresta(Grafo* grafo, int fonte, int destino) {
	No* novo = novoNo(destino);
	novo->prox = grafo->listaAdj[fonte];
	grafo->listaAdj[fonte] = novo;

	novo = novoNo(fonte);
	novo->prox = grafo->listaAdj[destino];
	grafo->listaAdj[destino] = novo;
}

void adicionarVertice(Grafo* grafo, int numVertices) {
	grafo->numVertices = numVertices;
	grafo->listaAdj = (No**)realloc(grafo->listaAdj, numVertices * sizeof(No*));
}

void removerAresta(Grafo* grafo, int fonte, int destino) {
	No* tmp = grafo->listaAdj[fonte];

	while(tmp) {
		if(tmp->elemento == destino) {
            No* aux = tmp->prox;
            grafo->listaAdj[fonte] = aux;
            tmp->prox = NULL;
            tmp = NULL;
        } else if(tmp->prox->elemento == destino) {
            No* aux = tmp->prox;
            tmp->prox = aux->prox;
            tmp = NULL;
        } else {
            tmp = tmp->prox;
        }
    }

    tmp = grafo->listaAdj[destino];

    while(tmp) {
        if(tmp->elemento == fonte) {
            No* aux = tmp->prox;
            grafo->listaAdj[destino] = aux;
            tmp->prox = NULL;
            tmp = NULL;
        } else if(tmp->prox->elemento == fonte) {
            No* aux = tmp->prox;
            tmp->prox = aux->prox;
            tmp = NULL;
        } else {
            tmp = tmp->prox;
        }
    }

    free(tmp);
}

int contarArestas(Grafo* grafo, int vertice) {
	No* tmp = grafo->listaAdj[vertice];
	int contador = 0;

	while(tmp) {
		contador++;
		tmp = tmp->prox;
	}

	return contador;
}

void removerVertice(Grafo* grafo, int vertice) {
	No* tmp = grafo->listaAdj[vertice];
	int n = contarArestas(grafo, vertice);
	int *vertices = (int*)calloc(n, sizeof(int)), i = 0;

	while(tmp) {
		*(vertices + i) = tmp->elemento;
		i++;
		tmp = tmp->prox;
	}

	for(i = 0; i < n; i++) {
		removerAresta(grafo, vertice, *(vertices + i));
	}

	free(vertices);

	grafo->listaAdj[vertice] = NULL;
}

/*void BFS(Grafo* grafo, Fila* fila) {

}

void DFS(Grafo* grafo, Pilha* pilha) {

}

void FTD(Grafo* grafo, int vertice) {

}

void FTI(Grafo* grafo, int vertice) {

}*/

void mostrar(Grafo* grafo) {
	for(int i = 0; i < grafo->numVertices; i++) {
		No* atual = grafo->listaAdj[i];
		printf("Mostrando lista de adjacencia do vertice %d:\n", i);

		while(atual) {
			printf(" %d ->", atual->elemento);9u;
			atual = atual->prox;
		}
		printf("/\n");
	}
}

int main() {
	int n;
	printf("Digite a quantidade de vertices do grafo: ");
	scanf("%d", &n);

	if(n > 0) {
	 	Grafo* grafo = novoGrafo(n);

		adicionarAresta(grafo, 2, 3);
		adicionarAresta(grafo, 4, 1);
		adicionarAresta(grafo, 2, 0);
		adicionarAresta(grafo, 0, 3);
		adicionarAresta(grafo, 1, 2);
		mostrar(grafo);

		adicionarVertice(grafo, 6);

		adicionarAresta(grafo, 5, 1);
		adicionarAresta(grafo, 5, 2);
		adicionarAresta(grafo, 5, 4);

		printf("\nMostrando o grafo apos inserir outro vertice:\n");
		mostrar(grafo);

		removerAresta(grafo, 0, 1);
		removerAresta(grafo, 5, 4);
		removerAresta(grafo, 3, 1);
		removerAresta(grafo, 2, 0);

		printf("\nMostrando o grafo apos remover algumas arestas:\n");
		mostrar(grafo);

		removerVertice(grafo, 1);

		printf("\nMostrando o grafo apos remover um vertice:\n");

		mostrar(grafo);
		free(grafo);
	} else {
		printf("Erro. O numero de vertices nao pode ser negativo!\n");
	}

	return 0;
}
