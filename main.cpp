#include <iostream>
#include "Graph.h"
#include "Algos.h"
#include "IO.h"

using namespace Traversals;
using namespace io;

//void test_bfs(Graph &G, Vertex *x, int g = 2) {
//    bfs(G, x, 2);
//    for (Vertex *v: illegal_vertex) {
//        cout << v->name << ", ";
//    }
//
//}

int main() {
    int n = 1000;
    int g = 5;
    int success = 0;
    int failure = 0;
    int iteration = 50;
    double avgTime = 0;


    clock_t start, end;
//    for (int n = )
    for (int i=0; i< iteration; i++) {
        Graph G(n, g);
        start = clock();
        solve(G)? success++ : failure++;
        end = clock();
        if( success == 1) cout << G;
        if( failure == 1) cout << G;
        avgTime += double(end - start) / double(CLOCKS_PER_SEC);

    }
    avgTime /= iteration;
    cout << "after " << iteration << " tries: " << success << " successes, and " << failure << " failures\n" << "avg time: " << avgTime;
    return 0;
}

