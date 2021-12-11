#ifndef DFS_H
#define DFS_H


#include "Graph.h"
#include <queue>
#include <random>

//   DFS(G)
//   - Time: O(V + E)

//   DFS-VISIT(G, u)
//   - Time: O(E)

namespace Traversals {
    int time = 0;
    int iterationCounter = 0;

    namespace tools {
        void clear(Graph &G) {
            for (int v : G.visited_track) {
                G.visited[v] = false;
                G.d[v] = 0;
            }
        }

        int random(int min, int max) {
            std::random_device rd;     // only used once to initialise (seed) engine
            std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

            auto random_integer = uni(rng);
            return random_integer;
        }

        int randomVertex(set<int> s) {
            auto it = std::begin(s);
            int n = random(0, s.size() - 1);
            // 'advance' the iterator n times
            std::advance(it,n);
            return (*it);
        }


        bool isLegalNeighbour(const Graph &G, int u) { //TODO inline?
            return !G.visited[u];
        }

        bool generateEdge(Graph &g, int v) {
            int counter = 0;
            g.availVertexes.erase(g.availVertexes.find(v)); //exclude the vertex itself, no loops in the graph
            int u = randomVertex(g.availVertexes);     //randomly choose from the set of available vertexes
            while (!isLegalNeighbour(g, u)) { // TODO if we fail to pick the vertex once, there are no available vertexes
                if (counter == g.n*4){       //Pull out visited in bfs vertexes from available set?
                    return false;
                }
                counter++;
                u = randomVertex(g.availVertexes);
            }
            g.connect(v, u);

            g.availVertexes.erase(g.availVertexes.find(u));
            return true;
        }
    }

    bool bfs(Graph &G, int root) {
        tools::clear(G);
        time = 0;
        int currentDepth = G.g;
        vector<int> currentLayer;
        queue<int> Q;
        Q.push(root);
        G.visited[root] = true;
        G.visited_track.push_back(root);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            time++;
            for (int u : G.Adj[v]) {
                if (!G.visited[u]) {
                    G.d[u] = G.d[v] + 1;
//                    if (G.d[u] == G.g) { //TODO check if g or g+1
//                        return;
//                    }
                    if (G.d[u] > currentDepth) {
                        if (currentLayer.empty()) {
                            currentDepth++;
                        } else {
                            int randomClosestVertex =  currentLayer.at(tools::random(0, currentLayer.size() - 1));
                            G.connect(root, randomClosestVertex);
                            return true;
                        }
                    }
                    if (currentDepth == G.n) return false;
                    if (G.d[u] == currentDepth) {
                        if (G.Adj[u].size() == 2) {
                            currentLayer.push_back(u);
                        }
                    }
                    G.visited[u] = true;
                    G.visited_track.push_back(u);
                    Q.push(u);
                }
            }
        }
        return false;
    }

    bool solve(Graph &G) {
        for (int v = 0; v < G.n; v++) {
            if (v == G.n - 1) return true;
            if (G.Adj[v].size() == 3) continue;
            if (!bfs(G, v)) return false;
//            if (!tools::generateEdge(G, v)) return false;
            G.visited[v] = false;
        }
        return true;
    }

}


#endif