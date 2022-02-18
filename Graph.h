//
// Created by michael on 16/11/2021.
#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include <bits/stdc++.h>


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
    vector<int> legalDeg;


    explicit Graph(int n, int g);
    Graph();

    void connect(int, int);

    void disConnect(int, int);

    int isNeighbour(int u, int v);

    void findPath(int start, int stop);

    list<int> trace_route(int start, int end);


    void findShortCycles(int k, int source, int v, int &count, vector<int>& path);

    int countShortCycles();
    vector<vector<int>> paths;
};

Graph::Graph(int n, int g) {
    Graph::n = n;
    Graph::g = g;
    Graph::PI = vector<int>(n, NONE);
    paths = vector<vector<int>>();

    Adj = vector<vector<int>>(n, vector<int>()); // k = 3

    for (int i = 0; i < n; i++) {
        connect(i, (i + 1) % n);
        legalDeg.push_back(i);
    }

    visited = vector<bool>(n, false);
    d1 = vector<int>(n, 0);
    d2 = vector<int>(n, 0);

    visited_track = vector<int>();

}

void Graph::findPath(int start,
                     int end) { //statement: if there is a single path of length less than g - 2, it's the shortest path
//    tools::clear(G, G.d1);
    queue<int> Queue;
    bool reached_end = false;
    visited[start] = true;
    Queue.push(start);

    //BFS until queue is empty
    while (!Queue.empty() && !reached_end) {
        int current_node = Queue.front();
        Queue.pop();
        for (int node: Adj[current_node]) {
            if (!visited[node]) {
                visited[node] = true;
                PI[node] = current_node;
                Queue.push(node);
                if (node == end) {
                    reached_end = true;
                    break;
                }
            }
        }
    }
}

list<int> Graph::trace_route(int start, int end) {
    list<int> route;
    int w = end;
    //PI[start] always -1
    while (PI[w] != start) {
        route.push_front(w);
        w = PI[w];
    }
    route.push_front(w);
    return route;
}

int Graph::isNeighbour(int u, int v) {
    for (int i = 0; i < Adj[u].size(); i++) {
        if (Adj[u][i] == v) return i;
    }
    return -1;
}

void Graph::findShortCycles(int k, int source, int v, int &count, vector<int>& path) {
    visited[v] = true;
    if (k == 0) {
        visited[v] = false;
        if (isNeighbour(source, v) != -1) {
            //trace rout
            paths.push_back(path);
            count++;
            return;
        } else
            return;
    }


    for (int u: Adj[v]) {
        if (!visited[u]) {
            vector<int> next_path(path);
            next_path.push_back(u);

            findShortCycles(k - 1, source, u, count, next_path);
        }
    }
    // marking vert as unvisited to make it
    // usable again.
    visited[v] = false;
}

int Graph::countShortCycles() {
    // all vertex are marked un-visited initially.
    for (int i = 0; i < visited.size(); visited[i] = false, i++);

    // Searching for cycle by using v-n+1 vertices
    int count = 0;
    for (int i = 0; i < n - (g - 1); i++) {
        vector<int> init_path;
        init_path.push_back(i);
        findShortCycles(g - 1, i, i, count, init_path);

        // ith vertex is marked as visited and
        // will not be visited again.
         visited[i] = true;
    }

    return count / 2;
}


void Graph::disConnect(int u, int v) {
    int idx_v = isNeighbour(u, v);
    int idx_u = isNeighbour(v, u);
    Adj[u].erase(Adj[u].begin() + idx_v);
    Adj[v].erase(Adj[v].begin() + idx_u);
//    cout << "trying to disconnect" << "(" << u << "," << v << ")\n";
//    cout << "elements of " << "Adj[" << v << "]\n";
//    for (int i = 0; i < Adj[v].size(); i++) {
//        cout << Adj[v][i] << " ";
//    }
//    cout << endl;
    if (Adj[u].size() == 2) legalDeg.push_back(u);
    if (Adj[v].size() == 2) legalDeg.push_back(v);
}

void Graph::connect(int a, int b) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
    if (Adj[a].size() == 3) legalDeg.erase(std::remove(legalDeg.begin(), legalDeg.end(), a), legalDeg.end());
    if (Adj[b].size() == 3) legalDeg.erase(std::remove(legalDeg.begin(), legalDeg.end(), b), legalDeg.end());
}

Graph::Graph() {
    Graph::PI = vector<int>(n, NONE);
    paths = vector<vector<int>>();

    Adj = vector<vector<int>>(n, vector<int>());

    visited = vector<bool>(n, false);

}


std::ostream &operator<<(std::ostream &os, const Graph &rhs) {

    for (int v = 0; v < rhs.n; v++) {
        os << std::setw(3) << v;
        for (int u: rhs.Adj[v]) {
            os << std::setw(3) << u << " ";
        }
        os << endl;
    }
    return os;
}

#endif //PROJECT_GRAPH_H
