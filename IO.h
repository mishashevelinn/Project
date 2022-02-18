//
// Created by michael on 10/12/2021.
//

#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

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

    void write_graph(const Graph &G, ostream &file) {
        for (int v = 0; v < G.n; v++) {
            file << v << " ";
            std::ostream_iterator<int> output_iterator(file, " ");
            std::copy(G.Adj[v].begin(), G.Adj[v].end(), output_iterator);
            file << endl;

        }
    }

    void write_stats(ostream &file, int n, int g, double succ, double time, double avail) {
        file << std::setprecision(3) << g << " " << n << " " << succ << " " << 1 - succ << " " << time << avail << endl;
    }

    void print_route(std::list<int> route, int u, int v, ostream& os = cout) {
        std::list<int>::iterator it;
        os << "route (" << u << " " << v << ")\n";
        for (it = route.begin(); it != route.end(); it++) {
            os << *it << " ";
        }
        os << "\n";

    }

    void print_edges(vector<pair<int, int>> edges) {
        vector<pair<int, int>>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++) {
            cout << "(" << (*it).first << "," << (*it).second << "), ";
        }
    }
    vector<int> AdjFromString(string line, char delim=' '){
        vector<int> adj{};
        stringstream ss(line); // Turn the string into a stream.
        string tok;
        while(getline(ss, tok, delim)) {
            stringstream char_to_int(tok);
            int x = 0;
            char_to_int >> x;
            adj.push_back(x);
        }
        return adj;


    }
    Graph& fromTxt(string path, Graph &G){
        fstream file;
        file.open(path,ios::in); //open a file to perform read operation using file object
        if (file.is_open()){   //checking whether the file is open
            string tp;
            while(getline(file, tp)){
                vector<int> adj = AdjFromString(tp);
                for(int i = 1; i < adj.size() -1; i++){
//                    G.Adj[adj[0]] = vector<int>();
//                    G.Adj[adj[i]] = vector<int>();
                    G.connect(adj[0], adj[i]);


                }

            }
        }
        file.close(); //close the file object.
    }


    void test1() {
        const char dir_path[] = "c:\\temp\\cplusplus";

        filesystem::path dir(dir_path);
        if( filesystem::create_directory(dir)) {
            std::cout << "Success" << "\n";
        }
    }


}
#endif //PROJECT_IO_H
