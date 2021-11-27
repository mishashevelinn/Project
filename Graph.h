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

using namespace std;

enum Color {
    WHITE,
    GRAY,
    BLACK,
};

string getString(Color color) {
    switch (color) {
        case WHITE:
            return "WHITE";
        case GRAY:
            return "GRAY";
        case BLACK:
            return "BLACK";
    }
    throw;
}

//class Vertex { //TODO add static counter
//public:
//    const int name;
//    Color color;
//    int d = 0;
//    int f = 0;
//    Vertex *PI;
//
//    Vertex() : name(0), color(WHITE), d(INT_MAX), PI(nullptr) {
//    }
//
//    Vertex(const int name) : name(name), color(WHITE) {
//    }
//};

class Graph {
public:
    vector<int> V;
    map<int, vector<int>> Adj;
    set<int> availVertexes;
    vector<bool> visited;
    vector<int> d;

    explicit Graph(int n);

    void print() const;

    void add(int);

    void connect(int, int);

    void disConnect(int, int);

};

Graph::Graph(int n) {
    add(0);
    for (int i = 1; i < n; i++) {
        add(i);
        connect(V[i - 1], V[i]);
    }
    connect(V[n-1], V[0]);
    availVertexes = set<int>(V.begin(), V.end());
    visited = vector<bool>(n, false);
    d = vector<int>(n, 0); //TODO 32 is enough for bounded DFS, since?

}


void Graph::add(int newVertex) {
    V.push_back(newVertex);
}

void Graph::disConnect(int a, int b) {
    vector<int> aAdj = Adj.at(a);
    vector<int> bAdj = Adj.at(b);
    for (int i = 0; i < aAdj.size(); i++) {
        if (aAdj[i] == b) {
            aAdj.erase(aAdj.begin() + i);

        }
    }
    for (int i = 0; i < bAdj.size(); i++) {
        if (bAdj[i] == a) {
            bAdj.erase(bAdj.begin() + i);
        }
    }
}

void Graph::connect(int a, int b) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
}

void Graph::print() const {
    for (auto v: V) {
        cout << v << " : ";
        for (auto &u: Adj.at(v)) {
            cout << u << " ";
        }
        cout << "\n";
    }

}

#endif //PROJECT_GRAPH_H
