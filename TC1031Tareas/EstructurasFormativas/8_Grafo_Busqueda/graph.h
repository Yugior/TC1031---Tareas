//A01712206 Horacio Villela Hernández


#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

class Graph {
private:
    int nodes;             // Número de nodos en el grafo
    vector<int> *adjList;  // Lista de adyacencia
    int *adjMatrix;        // Matriz de adyacencia

public:
    Graph();
    Graph(int n);
    ~Graph();
    void addEdgeAdjList(int u, int v);
    void addEdgeAdjMatrix(int u, int v);
    string printAdjList();
    string printAdjMat();
    string DFS(int start, int goal);
    string BFS(int start, int goal);
    void loadGraphList(string edges, int n);
    void loadGraphMat(string edges, int n, int m);
    
private:
    void sortAdjList();
    bool contains(list<int> &visited, int node);
    string depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<int> &paths);
    string breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<int> &paths);
    string printVisited(list<int> &visited);
    string printPath(vector<int> &paths, int start, int goal);
};

// Constructor por defecto
Graph::Graph() : nodes(0), adjList(nullptr), adjMatrix(nullptr) {}

// Constructor que inicializa el grafo con un número dado de nodos
Graph::Graph(int n) : nodes(n) {
    adjList = new vector<int>[nodes];
    adjMatrix = new int[nodes * nodes]();
}

// Destructor para liberar memoria
Graph::~Graph() {
    delete[] adjList;
    delete[] adjMatrix;
}

// Agrega una arista en la lista de adyacencia
// Complejidad: O(1)
void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

// Agrega una arista en la matriz de adyacencia
// Complejidad: O(1)
void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
}

// Carga el grafo como lista de adyacencia desde una cadena de texto
// Complejidad: O(n)
void Graph::loadGraphList(string edges, int n) {
    adjList = new vector<int>[n];
    nodes = n;
    int u, v;
    stringstream ss(edges);
    char discard;
    while (ss >> discard >> u >> discard >> v >> discard) {
        addEdgeAdjList(u, v);
    }
    sortAdjList();
}

// Carga el grafo como matriz de adyacencia desde una cadena de texto
// Complejidad: O(n)
void Graph::loadGraphMat(string edges, int n, int m) {
    adjMatrix = new int[n * m]();
    nodes = n;
    int u, v;
    stringstream ss(edges);
    char discard;
    while (ss >> discard >> u >> discard >> v >> discard) {
        addEdgeAdjMatrix(u, v);
    }
}

// Imprime la lista de adyacencia
// Complejidad: O(n^2)
string Graph::printAdjList() {
    stringstream ss;
    for (int i = 0; i < nodes; ++i) {
        ss << "vertex " << i << " :";
        for (int j : adjList[i]) {
            ss << " " << j;
        }
        ss << " ";
    }
    return ss.str();
}

// Imprime la matriz de adyacencia
// Complejidad: O(n^2)
string Graph::printAdjMat() {
    stringstream ss;
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            ss << adjMatrix[i * nodes + j] << " ";
        }
    }
    return ss.str();
}

// Ordena las listas de adyacencia para mantener un orden consistente
// Complejidad: O(n^2) en el peor caso
void Graph::sortAdjList() {
    for (int i = 0; i < nodes; ++i) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}

// Realiza una búsqueda en profundidad (DFS)
// Complejidad: O(n^2)
string Graph::DFS(int start, int goal) {
    stack<int> st;
    list<int> visited;
    vector<int> paths(nodes, -1);
    st.push(start);
    string result = depthHelper(start, goal, st, visited, paths);
    result += printPath(paths, start, goal);
    return result;
}

// Función auxiliar recursiva para DFS
// Complejidad: O(n^2) en el peor de los casos
string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<int> &paths) {
    if (current == goal) return printVisited(visited);
    if (st.empty()) return " node not found";

    current = st.top();
    st.pop();
    visited.push_back(current);

    for (int neighbor : adjList[current]) {
        if (!contains(visited, neighbor)) {
            st.push(neighbor);
            paths[neighbor] = current;
        }
    }
    return depthHelper(current, goal, st, visited, paths);
}

// Realiza una búsqueda en anchura (BFS)
// Complejidad: O(n^2)
string Graph::BFS(int start, int goal) {
    queue<int> qu;
    list<int> visited;
    vector<int> paths(nodes, -1);
    qu.push(start);
    string result = breadthHelper(start, goal, qu, visited, paths);
    result += printPath(paths, start, goal);
    return result;
}

// Función auxiliar recursiva para BFS
// Complejidad: O(n^2) en el peor de los casos
string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<int> &paths) {
    if (current == goal) return printVisited(visited);
    if (qu.empty()) return " node not found";

    current = qu.front();
    qu.pop();
    visited.push_back(current);

    for (int neighbor : adjList[current]) {
        if (!contains(visited, neighbor) && paths[neighbor] == -1) {
            qu.push(neighbor);
            paths[neighbor] = current;
        }
    }
    return breadthHelper(current, goal, qu, visited, paths);
}

// Verifica si un nodo ha sido visitado
// Complejidad: O(n)
bool Graph::contains(list<int> &visited, int node) {
    return find(visited.begin(), visited.end(), node) != visited.end();
}

// Imprime los nodos visitados
// Complejidad: O(n)
string Graph::printVisited(list<int> &visited) {
    stringstream ss;
    ss << "visited: ";
    for (int node : visited) {
        ss << node << " ";
    }
    return ss.str();
}

// Imprime el camino de un nodo inicial a un nodo objetivo
// Complejidad: O(n) 
string Graph::printPath(vector<int> &paths, int start, int goal) {
    stack<int> pathStack;
    int node = goal;
    while (node != -1 && node != start) {
        pathStack.push(node);
        node = paths[node];
    }
    pathStack.push(start);

    stringstream ss;
    ss << "path:";
    while (!pathStack.empty()) {
        ss << " " << pathStack.top();
        pathStack.pop();
    }
    return ss.str();
}

#endif /* GRAPH_H */
