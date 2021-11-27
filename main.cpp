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
    int n = 100;
    int g = 5;
    int success = 0;
    int failure = 0;
    int avgTime = 0;
    int iteration = 50;

    for (int i=0; i< iteration; i++) {
        Graph G(n);
        cout << " availSet size: " << G.availVertexes.size() << endl;
        auto start = std::chrono::system_clock::now();
        solve(G, g)? success++ : failure++ ;
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        avgTime += elapsed_seconds.count();
        G.print();
    }
    avgTime /= iteration;
    cout << "after " << iteration << " tries: " << success << " successes, and " << failure << " failures\n" << "avg time: " << avgTime;

    return 0;
}
