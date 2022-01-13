// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

void Graph::dfs(int v, int& counter) {
    nodes[v].visited = true;
    counter++;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w,counter);
    }
}

void Graph::dfs(int v, list<int>& order) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w, order);
    }
    order.push_front(v);
}

void Graph::dfs(int v, vector<string>& colors, bool& result){
    colors[v] = "Gray";
    for(auto e: nodes[v].adj){
        int w = e.dest;
        if(colors[w] == "Gray")
            result = true;
        else if(colors[w] == "White")
            dfs(w, colors, result);
    }
    colors[v] = "Black";
}

// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].distance = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].distance = 0;
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
// TODO
int Graph::outDegree(int v) {
    if(v == 0 || nodes.size() <= v)
        return -1;
    return nodes[v].adj.size();
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    int counter = 0;
    for(int v = 1; v <= n; v++){
        nodes[v].visited = false;
    }

    for(int v = 1; v<=n; v++){
        if(!nodes[v].visited){
            counter++;
            dfs(v);
        }
    }
    return counter;
}

// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {
    int max = 0;
    int counter;
    for(int v = 1; v <= n; v++){
        nodes[v].visited = false;
    }

    for(int v = 1; v<=n; v++){
        counter = 0;
        if(!nodes[v].visited){
            dfs(v, counter);
            if(max < counter)
                max = counter;
        }
    }
    return max;
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;

    for(auto node: nodes)
        node.visited = false;

    for(int v = 1; v<=n; v++){
        if(!nodes[v].visited){
            dfs(v,order);
        }
    }
    return order;
}

// ----------------------------------------------------------
// Exercicio 4: Distancias em grafos nao pesados
// ----------------------------------------------------------

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(int a, int b) {
    if(a == 0 || b == 0 || a > n || b > n){
        return -1;
    }
    bfs(a);
    return nodes[b].distance;
}

// ..............................
// b) Diametro
// TODO
int Graph::diameter() {
    int max = 0;
    for(int i = 1 ; i <= n; i++){
        bfs(i);
        for(int j = 1; j <=n; j++){
            if(nodes[j].distance == -1)
                return -1;
            else if(nodes[j].distance > max)
                max = nodes[j].distance;
        }
    }
    return max;
}

// ----------------------------------------------------------
// Exercicio 5: To or not be… a DAG!
// ----------------------------------------------------------
// TODO
bool Graph::hasCycle() {
    vector<string> colors(n+1, "White");
    bool result = false;
    for(int v = 1; v <= n; v++){
        if(colors[v] == "White")
            dfs(v, colors, result);
    }
    return result;
}
