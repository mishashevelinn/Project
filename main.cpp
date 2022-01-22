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
    int max_g = 6;
    double success = 0;
    double failure = 0;
    double iteration = 1;
    double avgTime = 0;
    double avgAvailVertex = 0;
    vector<int> N;
    N = { 20};
    ofstream file("res2.txt");
    ofstream fileGraph("graph.txt");
    clock_t start, end;
    for (int g = 5; g < max_g; g++) {
        for (int n: N) {
            for (int i = 0; i < iteration; i++) {
                Graph G(n, g);
                start = clock();
                if (solve(G, g)) {
                    success++;
//                    cout << G << endl;
                } else {
                    failure++;
                }
                end = clock();
                avgTime += double(end - start) / double(CLOCKS_PER_SEC);

            }
            avgTime /= iteration;
            io::write_stats(cout, n, g, double(success / iteration), avgTime);
            success = 0;
            failure = 0;
            avgTime = 0;
            avgAvailVertex = 0;
        }
    }
    return 0;
}

