#include <iostream>
#include "Graph.h"
#include "Algos.h"

using namespace Traversals;

void test_bfs(Graph &G, Vertex *x, int g = 2) {
    bfs(G, x, 2);
    for (Vertex *v: illegal_vertex) {
        cout << v->name << ", ";
    }

}

int main() {
    Graph G;
    int n = 6;
    G.add(new Vertex(0));
    for (int i = 1; i < n; i++) {
        G.add(new Vertex(i));
        G.connect(G.V[i - 1], G.V[i]);
    }
    G.connect(G.V[0], G.V[n - 1]);
    G.print();
    solve(G, 3);
    G.print();
    return 0;
}
