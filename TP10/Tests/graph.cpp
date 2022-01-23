// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"
#include <set>


// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({src, dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, dest, weight});
}


// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r) {
    MinHeap<int,int> q(n, -1);
    for (Node & i : this->nodes){
        i.distance = INT_MAX;
        i.parent = NULL;
    }
    nodes[r].distance = 0;
    for(int i = 1; i <= n; i++){
        q.insert(i,nodes[i].distance);
    }
    while (q.getSize() != 0){
        int u = q.removeMin();
        for(auto vEdge: nodes[u].adj){
            int v = vEdge.dest;
            if(q.hasKey(v) && vEdge.weight < nodes[v].distance){
                q.decreaseKey(v, vEdge.weight);
                nodes[v].parent = u;
                nodes[v].distance = vEdge.weight;
            }
        }
    }

    int counter = 0;
    for (int i = 1; i<=n; i++)
        counter+=nodes.at(i).distance;

    return counter;
}


// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {
    DisjointSets<int> set;
    for(int i = 1; i <= n; i++){
        set.makeSet(i);
    }

    std::set<Edge> edges;
    for(Node node: nodes){
        edges.insert(node.adj.begin(),node.adj.end());
    }

    int sum = 0;
    for(auto edge: edges){
        if(set.find(edge.parent) != set.find(edge.dest)){
            sum += edge.weight;
            set.unite(edge.parent,edge.dest);
        }
    }

    return sum;
}

