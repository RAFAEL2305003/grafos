#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data, v, p;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertexs, type;
    Node **adjList;
} Graph;

/**
 * Definindo dados globais
 */
Node *top;
int size;

/**
 * Procedimento para inicializar as váriaveis criadas anteriormente.
 */
void startStack() {
  top = NULL;
  size = 0;
}

Node *newNode(int data) {
    Node *new = (Node*)malloc(sizeof(Node));

    if(new) {
        new->data = data;
        new->v = 0;
        new->p = 0;
        new->next = NULL;
        return new;
    } else {
        printf("Erro ao tentar alocar memoria!\n");
        return NULL;
    }
}

Graph *newGraph(int vertexs, int type) {
    Graph *new = (Graph*)malloc(sizeof(Graph));

    if(new) {
        new->vertexs = vertexs;
        new->adjList = (Node**)calloc(vertexs, sizeof(Node*));
        new->type = type;

        for(int i = 0; i < vertexs; i++) {
            new->adjList[i] = NULL;
        }

        return new;
    } else {
        printf("Erro ao tentar alocar memoria!\n");
        return NULL;
    }
}

/**
 * Função que verifica se a pilha está vazia.
 * @return - Retorna 1 caso esteja vazia e 0 caso não esteja
 */
int isEmpty() {
  return top == NULL;
}

/**
 * Função para pegar o primeiro elemento da pilha.
 * @return - Retorna o primeiro elemento caso a pilha não esteja vazia, caso a mesma esteja, retorna -1
 */
int getTop() {
  if(!isEmpty()) {
    return top->data;
  } else {
    return -1;
  }
}

/**
 * Procedimento para inserir um elemento na pilha.
 * @param data - Elemento a ser inserido
 */
void push(int data) {
  Node *tmp = newNode(data);
  tmp->next = top;
  top = tmp;
  size++;
  tmp = NULL;
}

/**
 * Função que remove um elemento da pilha
 * @return removed - Retorna o elemento removido
 */
int pop() {
  int removed = -1;
  
  if(!isEmpty()) {
    removed = top->data;
    Node *tmp = top;
    top = tmp->next;
    size--;
    tmp = NULL;
    free(tmp);
  } else {
    printf("Erro. Eh impossivel remover um elemento da pilha se a mesma estiver vazia!");
  }

  return removed;
}

void insertEdge(Graph *graph, int src, int dest) {
    Node *tmp = newNode(dest);
    tmp->next = graph->adjList[src];
    graph->adjList[src] = tmp;

    if(graph->type == 1) {
        tmp = newNode(src);
        tmp->next = graph->adjList[dest];
        graph->adjList[dest] = tmp;
    }
}

void showGraph(Graph *graph) {
    printf("\n");
    for(int i = 0; i < graph->vertexs; i++) {
        printf("Lista de adjacencia do vertice %d:\n", i);
        Node *tmp = graph->adjList[i];

        while(tmp) {
            printf(" -> %d", tmp->data);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void DFS(struct Graph* graph, int start_vertex) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = 0;
    }

    // Pilha para DFS
    int* stack = (int*)malloc(graph->vertices * sizeof(int));
    int top = -1;

    printf("Busca em Profundidade a partir do vértice %d:\n", start_vertex);

    // Empilhar o vértice inicial
    stack[++top] = start_vertex;

    while (top != -1) {
        int current_vertex = stack[top--];

        if (!visited[current_vertex]) {
            visited[current_vertex] = 1;
            printf("%d ", current_vertex);
        }

        struct Node* temp = graph->adjacency_list[current_vertex];
        while (temp) {
            int adj_vertex = temp->data;
            if (!visited[adj_vertex]) {
                stack[++top] = adj_vertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(stack);
}

int main() {
    int n, t;
    printf("Digite a quantidade de vertices para seu grafo: ");
    scanf("%d", &n);

    printf("Seu grafo sera direcinado ou nao-direcionado? Digite:\n0- Para direcionado.\n1- Para nao-direcionado.\nSua opcao:");
    scanf("%d", &t);

    Graph *graph = newGraph(n, t);

    insertEdge(graph, 1, 2);
    insertEdge(graph, 0, 2);
    insertEdge(graph, 1, 0);
    insertEdge(graph, 3, 4);
    insertEdge(graph, 4, 2);

    showGraph(graph);

    return  0;
}