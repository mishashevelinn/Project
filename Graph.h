//
// Created by michael on 16/11/2021.
//

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

class Vertex { //TODO add static counter
public:
    const int name;
    Color color;
    int d = 0;
    int f = 0;
    Vertex *PI;

    Vertex() : name(0), color(WHITE), d(INT_MAX), PI(nullptr) {
    }

    Vertex(const int name) : name(name) {
    }
};

class Graph {
public:
    vector<Vertex *> V;
    map<Vertex *, vector<Vertex *>> Adj;

    void print() const;

    void add(Vertex* newVertex);

    void connect(Vertex *a, Vertex *b);

    void disConnect(Vertex *a, Vertex *b);

};

void Graph::add(Vertex* newVertex) {
    V.push_back(newVertex);
}

void Graph::disConnect(Vertex *a, Vertex *b) {
    vector<Vertex *> aAdj = Adj.at(a);
    vector<Vertex *> bAdj = Adj.at(b);
    for (int i = 0; i < aAdj.size(); i++) {
        if (aAdj[i]->name == b->name) {
            aAdj.erase(aAdj.begin() + i);
        }
    }
    for (int i = 0; i < bAdj.size(); i++) {
        if (bAdj[i]->name == a->name) {
            bAdj.erase(bAdj.begin() + i);
        }
    }
}

void Graph::connect(Vertex *a, Vertex *b) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
}

void Graph::print() const {
    for (auto v: V) {
        cout << v->name << " : ";
        for (auto &u: Adj.at(v)) {
            cout << u->name << " ";
        }
        cout << "\n";
    }

}

#endif //PROJECT_GRAPH_H
