#include <iostream>
#include <vector>

class No {
public:
    int elemento;
    No* prox;
    
    No(int elemento) : elemento(elemento), prox(nullptr) {}
};

class Grafo {
public:
    int numVertices;
    std::vector<No*> listaAdj;

    Grafo(int numVertices) : numVertices(numVertices), listaAdj(numVertices, nullptr) {}

    void adicionarAresta(int origem, int destino) {
        No* novo = new No(destino);
        novo->prox = listaAdj[origem];
        listaAdj[origem] = novo;
        adicionarAresta(destino, origem);
        //novo = new No(origem);
        //novo->prox = listaAdj[destino];
        //listaAdj[destino] = novo;
    }

    void mostrar() {
        for (int i = 0; i < numVertices; i++) {
            No* atual = listaAdj[i];
            std::cout << "Mostrando lista de adjacencia do vertice " << i << ":\n";

            while (atual) {
                std::cout << " " << atual->elemento << " ->";
                atual = atual->prox;
            }
            std::cout << "/\n";
        }
    }
};

int main() {
    int numVertices = 5; 
    Grafo grafo(numVertices);
    
    grafo.adicionarAresta(0, 1);
    grafo.adicionarAresta(0, 4);
    grafo.adicionarAresta(1, 2);
    grafo.adicionarAresta(1, 3);
    grafo.adicionarAresta(1, 4);
    grafo.adicionarAresta(2, 3);
    grafo.adicionarAresta(3, 4);

    grafo.mostrar();

    return 0;
}
