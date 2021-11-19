#include <iostream>
#include "Graph.h"

int main() {
    Graph G;
    Vertex* u = new Vertex("u");
    Vertex* v = new Vertex("v");
    Vertex* w = new Vertex("w");
    Vertex* x = new Vertex("x");
    Vertex* y = new Vertex("y");
    Vertex* z = new Vertex("z");
    G.V.push_back(u);
    G.V.push_back(v);
    G.V.push_back(w);
    G.V.push_back(x);
    G.V.push_back(y);
    G.V.push_back(z);

    G.Adj[u].push_back(v);
    G.Adj[u].push_back(x);

    G.Adj[v].push_back(y);

    G.Adj[w].push_back(y);
    G.Adj[w].push_back(z);

    G.Adj[x].push_back(v);

    G.Adj[y].push_back(x);

    G.Adj[z].push_back(z);
    G.print();

    return 0;
}
