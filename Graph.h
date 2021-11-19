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

class Vertex {
public:
    const string name;
    Color color;
    int d = 0;
    int f = 0;
    int cc;
    Vertex* PI;
    Vertex() : color(WHITE), d(INT_MAX), PI(nullptr) {
    }
    Vertex(const string& name) : name(name) {
    }
};

class Graph {
public:
    vector<Vertex*> V;
    map<Vertex*, vector<Vertex*>> Adj;
    void print() const ;

};

void Graph::print() const {
    for(auto v : V){
        cout << v->name << " : ";
        for (auto & u : Adj.at(v)){
            cout << u->name << " ";
        }
        cout << "\n";
    }

}

#endif //PROJECT_GRAPH_H
