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
    int n = 10;
    int g = 3;
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
        if(i == iteration - 1) io::write_map(G.Adj, "output.txt");
    }
    avgTime /= iteration;
    cout << "after " << iteration << " tries: " << success << " successes, and " << failure << " failures\n" << "avg time: " << avgTime;
    return 0;
}
