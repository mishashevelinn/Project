#include <iostream>
#include "Graph.h"
#include "Algos.h"
#include "IO.h"

//    Graph G(20, 6);
//    G.connect(0, 6);
//    G.connect(0, 12);
//    int k = 4;
//    cout << G;
//    int cycles = tools::count_cycles(G, 0, 10, k);
//    tools::clear(G, G.d1);
//    G.findPath(0, 10);
//
//    G.trace_route(10);
//    cout << "with keshet (0,10) mispar maagalim ktim mi " << k+1 << " = "<< cycles;
//

using namespace tools;


using namespace io;

int main() {
    int max_g = 11;
    double success = 0;
    double failure = 0;
    double iteration = 10;
    double avgTime = 0;
    double avgAvailVertex = 0;
    vector<int> N;
    int n = 20;
    int g = 5;
    int max_iter = (int)pow(n ,2);
//    ofstream file("tmp.txt");
    ofstream fileGraph("graph.txt");
    clock_t start, end;
    for (int i = 0; i < iteration; i++) {
        Graph G(n, g);
        start = clock();
        if (tools::solve(G, g, max_iter)) {
            success++;
            cout << "Try number " << i+1 << ": Succeed!\n";
            if(success == 1){
                write_graph(G,  fileGraph);
            }
        } else {
            failure++;
            cout << "Try number " << i+1 << ": Failed!\n";
        }

    }
    cout << success;
//        cout << G;
    end = clock();
    avgTime += double(end - start) / double(CLOCKS_PER_SEC);

    avgTime /= iteration;
//    io::write_stats(file, n, g, double(success / iteration), avgTime);
    success = 0;
    failure = 0;
    avgTime = 0;
    avgAvailVertex = 0;
    return 0;
}