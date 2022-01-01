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
    int max_g = 15;
    double success = 0;
    double failure = 0;
    double iteration = 100;
    double avgTime = 0;
    double avgAvailVertex = 0;
    vector<int> N;
    N = { 1000,500,400,300, 200, 100, 70, 50, 30, 20, 15, 10};
    ofstream file("res2.txt");
    ofstream fileGraph("graph.txt");
    clock_t start, end;
    for (int g = 5; g < max_g; g++) {
        for (int n: N) {
            for (int i = 0; i < iteration; i++) {
                Graph G(n);
                start = clock();
                if (solve(G, g)) {
                    success++;
                } else {
                    failure++;
                }
                avgAvailVertex += G.availVertexes.size();
                end = clock();
                avgTime += double(end - start) / double(CLOCKS_PER_SEC);

            }
            avgTime /= iteration;
            io::write_stats(file, n, g, double(success / iteration), avgTime, avgAvailVertex / failure);
            success = 0;
            failure = 0;
            avgTime = 0;
            avgAvailVertex = 0;
        }
    }
    return 0;
}

