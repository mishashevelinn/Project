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
    int g = 5;
    int n = 20;
    double success = 0;
    double failure = 0;
//    double iteration = 1;
//    double avgTime = 0;
//    double avgAvailVertex = 0;

//    vector<int> N;
//    N = { 1000,500,400,300, 200, 100, 70, 50, 30, 20, 15, 10};
//    ofstream file("res2.txt");
//    ofstream fileGraph("graph.txt");
//    clock_t start, end;
//    for (int g = 5; g < max_g; g++) {
//        for (int n: N) {
//            for (int i = 0; i < iteration; i++) {
    for (int k=0; k<5; k++){
        Graph G(n, g);
//    start = clock();
        cout << solve(G, g);
    }


    //    if (solve(G, g)) {
//        success++;
//    } else {
//        failure++;
//    }
//                avgAvailVertex += G.availVertexes.size();
//    end = clock();
//    avgTime += double(end - start) / double(CLOCKS_PER_SEC);

//            }
//            avgTime /= iteration;
//            cout << "Success: " << success << ",tries: " << iteration << endl;
//            io::write_stats(file, n, g, double(success / iteration), avgTime);
//            success = 0;
//            failure = 0;
//            avgTime = 0;
//            avgAvailVertex = 0;
//        }
//    }
    return 0;
}

