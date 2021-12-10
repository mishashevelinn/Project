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
        void vanish(Graph &G) {
            for (int v: G.V) {
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

        void clear_queue(queue<int> q) {
            std::queue<int> empty;
            std::swap(q, empty);
        }

        void vanish_vector(Graph & G, vector<int> vec) {
            for (int v : vec) {
                G.visited[v] = false;
                G.d[v] = 0;
            }
            vec.clear();
        }

        bool isLegalNeighbour(const Graph &G, int v) { //TODO inline?
            return !G.visited[v];
        }

        bool generateEdge(Graph &g, int v) {
            int counter = 0;
            g.availVertexes.erase(g.availVertexes.find(v)); //exclude the vertex itself, no loops in the graph
            int idx = randomVertex(g.availVertexes);     //randomly choose from the set of available vertexes
            while (!isLegalNeighbour(g, g.V[idx])) { // TODO if we fail to pick the vertex once, there are no available vertexes
                if (counter == g.V.size()*4){       //Pull out visited in bfs vertexes from available set?
                    return false;
                }
                counter++;
                idx = randomVertex(g.availVertexes);
            }
            g.connect(v, g.V[idx]);

            g.availVertexes.erase(g.availVertexes.find(g.V[idx]));
            return true;
        }
    }

    void bfs(Graph &G, int root, int g) {
        tools::vanish(G);
        time = 0;
        queue<int> Q;
        Q.push(root);
        G.visited[root] = true;
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            time++;
            for (int u : G.Adj.at(v)) {
                if (!G.visited[u]) {
                    G.d[u] = G.d[v] + 1;
                    if (G.d[u] == g + 1) { //TODO check if g or g+1
                        return;
                    }
                    G.visited[u] = true;
                    Q.push(u);
                }
            }
        }
    }

    bool solve(Graph &G, int g) {
        g--;
        for (int v: G.V) {
            if (v == G.V.size() - 1) return true;
            if (G.Adj.at(v).size() == 3) continue;
            bfs(G, v, g);
            if (!tools::generateEdge(G, v)) return false;
            G.visited[v] = false;
        }
        return true;
    }

}


#endif