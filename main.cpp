#include <iostream>
#include "Graph.h"
#include "Algos.h"
#include "IO.h"
#include <string>

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

int main(){
//    Graph g(10, 6);
//    g.connect(0,5);
//
//    ofstream  file( "test.txt");
//    io::write_graph(g,file);
//    int num_cycles = g.countShortCycles();
//    for(int numPath = 0; numPath < int(g.paths.size()/2); numPath++){
//        cout << "cycle " + to_string(numPath) + ": ";
//        for(int v : g.paths[numPath]){
//            cout << v << " ";
//        }
//        cout << endl;
//    }
//    cout << num_cycles;
//    Graph G = Graph();
//    io::fromTxt("test.txt", G);



    string dir = " ../data/HillClimberEvenOdd/";
    double success = 0;
    double failure = 0;
    double avgTime = 0;
    vector<int> N = {20};
    int g = 4;
//    int g_max = 6;
    double iteration = 20;

    string statfile_name = "../data/HillClimberEvenOdd/STATS_g="+ to_string(g)+"_n="+ to_string(N[0])+"-"+ to_string(N[N.size() - 1])+"/stats1.txt";
    ofstream statfile(statfile_name);
    for (int n: N) {
        int max_iter_solve = (int) pow(n, 2);
        clock_t start, end;
        success = 0;
        failure = 0;
        avgTime = 0;
        int num_avail = 0;
        for (int i = 0; i < iteration; i++) {
            Graph G(n, g);
            start = clock();
            if (tools::solve(G, g, max_iter_solve)) {
                success++;
                string gstr = to_string(g);
                string nstr = to_string(n);

                string name =
                        "../data/HillClimberEvenOdd/solution_g=" + to_string(g) + "_n=" + to_string(n) +
                        "_" + to_string((int) success) + ".txt";
                ofstream fileGraph(name);
                io::write_graph(G, fileGraph);
//                cout << "+" << endl;

            } else {
                failure++;
//                cout << "-" << endl;
                end = clock();

            }
            avgTime += double(end - start) / double(CLOCKS_PER_SEC);
            num_avail += (int) G.legalDeg.size();
//            cout << "g = " << to_string(g) << " n = " << to_string(n) << "iter no " << i << "/" << iteration - 1 << endl;

        }
        cout << success << endl;
        io::write_stats(statfile, n, g, double(success / iteration), avgTime / iteration,
                        double(num_avail / failure)); //double(success / i) ?

    }

    return 0;
}