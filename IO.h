//
// Created by michael on 10/12/2021.
//

#include <vector>
#include <fstream>
#include <iterator>


#ifndef PROJECT_IO_H
#define PROJECT_IO_H
namespace io {


    void write_map(const std::map<int, std::vector<int>> Adj, std::string path) {
        ofstream stream(path);
        for (auto &kv: Adj) {
            stream << kv.first << "---->";
            std::ostream_iterator<int> output_iterator(stream, " ");
            std::copy(Adj.at(kv.first).begin(), Adj.at(kv.first).end(), output_iterator);
            stream << "\n";
        }
    }

    void write_graph(const Graph &G, string path) {
        ofstream stream(path, ios::app);
        for (int v = 0; v < G.n; v++) {
            stream << v << " ----> ";
            std::ostream_iterator<int> output_iterator(stream, " ");
            std::copy(G.Adj[v].begin(), G.Adj[v].end(), output_iterator);
            stream << endl;

        }
    }

    void write_stats(ostream &file, int n, int g, double succ, double time) {
        file << std::setprecision(3) << g << " " << n << " " << succ << " " << 1 - succ << " " << time << endl;
//        file << std::setprecision(3) << "\t\tAvg availVertex size=" ;
    }

    void print_route(std::list<int> route, int u, int v) {
        std::list<int>::iterator it;
        cout << "route (" << u << " " << v << ")\n";
        for (it = route.begin(); it != route.end(); it++) {
            cout << *it << " ";
        }
        cout << "\n";

    }

    void print_edges(vector<pair<int, int>> edges) {
        vector<pair<int, int>>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++) {
            cout << "(" << (*it).first << "," << (*it).second << "), ";
        }
    }
}
#endif //PROJECT_IO_H
