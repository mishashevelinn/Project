#include <iostream>
#include "Graph.h"
#include "Algos.h"
#include "IO.h"

using namespace Traversals;
using namespace io;


int main() {
    int max_g = 11;
    double success = 0;
    double failure = 0;
    double iteration = 1;
    double avgTime = 0;
    double avgAvailVertex = 0;
    vector<int> N;
    int n = 50;
    int g = 5;
    int max_iter = 100S;
    ofstream file("tmp.txt");
    ofstream fileGraph("graph.txt");
    clock_t start, end;
    for (int i = 0; i < iteration; i++) {
        Graph G(n, g);
        start = clock();
        if (solve(G, g, max_iter)) {
            success++;
        } else {
            failure++;
        }
        cout << success;
        cout << G;
        end = clock();
        avgTime += double(end - start) / double(CLOCKS_PER_SEC);

    }
    avgTime /= iteration;
    io::write_stats(file, n, g, double(success / iteration), avgTime);
    success = 0;
    failure = 0;
    avgTime = 0;
    avgAvailVertex = 0;
    return 0;
}