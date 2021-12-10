#include <iostream>
#include "Graph.h"
#include "Algos.h"

using namespace Traversals;

//void test_bfs(Graph &G, Vertex *x, int g = 2) {
//    bfs(G, x, 2);
//    for (Vertex *v: illegal_vertex) {
//        cout << v->name << ", ";
//    }
//
//}

int main() {
    int n = 100;
    int g = 10;
    int success = 0;
    int failure = 0;
    int iteration = 100;
    double avgTime = 0;


    clock_t start, end;
    for (int i=0; i< iteration; i++) {
        Graph G(n);
        start = clock();
        solve(G, g)? success++ : failure++ ;
        end = clock();
        avgTime += double(end - start) / double(CLOCKS_PER_SEC);
//        G.print();
    }
    avgTime /= iteration;
    cout << "after " << iteration << " tries: " << success << " successes, and " << failure << " failures\n" << "avg time: " << avgTime;
    return 0;
}
