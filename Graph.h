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
#include <boost/dynamic_bitset.hpp>


#include <iostream>
#define NONE -1
using namespace std;



class Graph {
public:
    vector<bool> visited;
    vector<int> d1;
    vector<int> d2;
    int n;
    int g;
    vector<vector<int>> Adj;
    vector<int> visited_track;
    vector<int> availV;



    explicit Graph(int n, int g);

    void connect(int, int);

    void disConnect(int, int);
};

Graph::Graph( int n, int g) {
    Graph::n = n;
    Graph::g = g;

    Adj = vector<vector<int>>(n, vector<int>()); // k = 3

    for (int i = 0; i < n ; i++) {
        connect(i, (i+1) % n);
        availV.push_back(i);
    }

    visited = vector<bool>(n, false);
    d1 = vector<int>(n, 0);
    d2= vector<int>(n, 0);

    visited_track = vector<int>(); //keep track of visited in BFS vertexes 2**5

}

/**********NEVER__USED******************/
void Graph::disConnect(int a, int b) {
    vector<int> aNeighbours = Adj[a];
    vector<int> bNeighbours = Adj[b];
    aNeighbours.erase(aNeighbours.erase(std::remove(aNeighbours.begin(), aNeighbours.end(), b), aNeighbours.end()));
    bNeighbours.erase(bNeighbours.erase(std::remove(bNeighbours.begin(), bNeighbours.end(), a), bNeighbours.end()));
    if (aNeighbours.size() == 2 ) availV.push_back(a);
    if (bNeighbours.size() == 2 ) availV.push_back(b);
}

void Graph::connect(int a, int b) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
    if (Adj[a].size() == 3) availV.erase(std::remove(Adj[a].begin(), Adj[a].end(), a), Adj[a].end());
    if (Adj[b].size() == 3) availV.erase(std::remove(Adj[b].begin(), Adj[b].end(), b), Adj[b].end());
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
        os << std::setw(3) << v << " ---> ";
        for (int u: rhs.Adj[v]) {
            os << std::setw(3) << u << " ";
        }
        os << endl;
    }
    return os;
}

#endif //PROJECT_GRAPH_H
