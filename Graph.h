//
// Created by michael on 16/11/2021.
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
    vector<int> PI;
    int n;
    int g;
    vector<vector<int>> Adj;
    vector<int> visited_track;
    vector<int> availV;



    explicit Graph(int n, int g);

    void connect(int, int);

    void disConnect(int, int);

    bool isNeighbour(int u, int v);

    void findPath(int start, int stop);

    list<int> trace_route(int end);
};

Graph::Graph( int n, int g) {
    Graph::n = n;
    Graph::g = g;
    Graph:: PI = vector<int>(n, NONE);

    Adj = vector<vector<int>>(n, vector<int>()); // k = 3

    for (int i = 0; i < n ; i++) {
        connect(i, (i+1) % n);
        availV.push_back(i);
    }

    visited = vector<bool>(n, false);
    d1 = vector<int>(n, 0);
    d2= vector<int>(n, 0);

    visited_track = vector<int>();

}
void Graph::findPath(int start, int end){ //statement: if there is a single path of length less than g - 2, it's the shortest path
    queue<int> Queue;
    bool reached_end = false;
    visited[start] = true;
    Queue.push(start);

    //BFS until queue is empty
    while(!Queue.empty() && !reached_end){
        int current_node=Queue.front();
        Queue.pop();
        for(int node: Adj[current_node]){
            if(!visited[node]){
                visited[node] = true;
                PI[node] = current_node;
                Queue.push(node);
                if(node == end){
                    reached_end = true;
                    break;
                }
            }
        }
    }
}

list<int> Graph::trace_route(int end){
    list<int> route;
    int w = end;
    //PI[start] always -1
    while(PI[w]!= NONE){
        route.push_front(w);
        w = PI[w];
    }
    route.push_front(w);
    return route;
}
bool Graph::isNeighbour(int u,int v){
    for(int i : Adj[u]){
        if (i == v) return true;
    }
    return false;
}

void Graph::disConnect(int a, int b) {
    Adj[a].erase(std::remove(Adj[a].begin(), Adj[a].end(), b), Adj[a].end());
    Adj[b].erase(std::remove(Adj[b].begin(), Adj[b].end(), a), Adj[b].end());
    if (Adj[a].size() == 2 ) availV.push_back(a);
    if (Adj[b].size() == 2 ) availV.push_back(b);
}

void Graph::connect(int a, int b) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
    if (Adj[a].size() == 3) availV.erase(std::remove(availV.begin(), availV.end(), a), availV.end());
    if (Adj[b].size() == 3) availV.erase(std::remove(availV.begin(), availV.end(), b), availV.end());
}



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
