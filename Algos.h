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
            //TODO clear the visited_track.
        }

        int random(int min, int max) {
            std::random_device rd;     // only used once to initialise (seed) engine
            std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

            auto random_integer = uni(rng);
            return random_integer;
        }

        bool isLegalNeighbour(const Graph &G, int u) {
            return (!G.visited[u] && (G.Adj[u].size() < 3));
        }

        bool generateEdge(Graph &g, int v) {
            vector<int> availVertex;
            for (int vertex = 0; vertex < g.n; vertex++){
                if (isLegalNeighbour(g, vertex)){
                    availVertex.push_back(vertex);
                }
            }
            if (availVertex.empty()) return false;
            int u = random(0, availVertex.size() - 1);
            g.connect(v, availVertex[u]);
            return true;
        }
    }

    void bfs(Graph &G, int root, int g) {
        tools::clear(G);
        queue<int> Q;
        Q.push(root);
        G.visited[root] = true;
        G.visited_track.push_back(root);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int u : G.Adj[v]) {
                if (!G.visited[u]) {
                    G.d[u] = G.d[v] + 1;
                    G.visited[u] = true;
                    G.visited_track.push_back(u);
                    if (G.d[u] == g-1) return;
                    Q.push(u);
                }
            }
        }
    }
    vector<int> getRandOrder(Graph &g) {
        vector<int> order;
        for (int i = 0; i< g.n; i++){
            order.push_back(i);
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine e(seed);
        std::shuffle(order.begin(), order.end(), e);
        return order;
    }

    bool solve(Graph &G, int g) {
        vector<int> random_vertex_order = getRandOrder(G);

        for (int v: random_vertex_order){
            if (G.Adj[v].size() != 3) {
                bfs(G, v, g);
                if (!tools::generateEdge(G, v)) return false;
                G.visited[v] = false;
            }
        }
        return true;
    }

}


#endif
