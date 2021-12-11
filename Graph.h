//
// Created by michael on 16/11/2021.
//
/* TODO:
 
 algos:
 1 long runs (g=5~19, n=10~100000) see what the prob and time
 2 check if we should choose the vertex by order or random
 3 check if we should pick close vertex to connect or far one.
 4 get access to darwin ( Itay Sharon)
 optimization:
 1 cut where we can the Vertex and Graph (data structure)
 2 add data structure for "legal vertex's" (less then 3 degree)
 */
#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include <bits/stdc++.h>

#include <iostream>

using namespace std;


class Graph {
public:
    set<int> availVertexes;
    vector<bool> visited;
    vector<int> d;
    int n;
    vector<vector<int>> Adj;


    explicit Graph(int n);

    void print() const;

    void add(int);

    void connect(int, int);

    void disConnect(int, int);
};

Graph::Graph( int n) {
    Graph::n = n;
    Adj = vector<vector<int>>(n, vector<int>()); // k = 3

    for (int i = 0; i < n ; i++) {
        connect(i, (i+1) % n);
        availVertexes.insert(i);
    }
    visited = vector<bool>(n, false);
    d = vector<int>(n, 0); //TODO 32 is enough for bounded DFS, since?

//    visited_track = vector<int>()
}

/**********NEVER__USED******************/
//void Graph::disConnect(int a, int b) {
//    vector<int> aAdj = Adj.at(a);
//    vector<int> bAdj = Adj.at(b);
//    for (int i = 0; i < aAdj.size(); i++) {
//        if (aAdj[i] == b) {
//            aAdj.erase(aAdj.begin() + i);
//
//        }
//    }
//    for (int i = 0; i < bAdj.size(); i++) {
//        if (bAdj[i] == a) {
//            bAdj.erase(bAdj.begin() + i);
//        }
//    }
//}

void Graph::connect(int a, int b) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
}

/********Deprecated**********/
//void Graph::print() const {
//    for (auto v: V) {
//        cout << v << " : ";
//        for (auto &u: Adj.at(v)) {
//            cout << u << " ";
//        }
//    }
//}

std::ostream &operator<<(std::ostream &os, const Graph &rhs) {

    for (int v = 0; v < rhs.n; v++) {
        os << v << " ---> ";
        for (int u: rhs.Adj[v]) {
            os << u << " ";
        }
        os << endl;
    }
    return os;
}

#endif //PROJECT_GRAPH_H
