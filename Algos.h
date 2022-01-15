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

        bool isLegalNeighbour(const Graph &G, int u) {
            return (!G.visited[u] && (G.Adj[u].size() < 3));
        }

        int generateEdge(Graph &g, int v) {
            vector<int> availVertex;
            for (int vertex = 0; vertex < g.n; vertex++){
                if (isLegalNeighbour(g, vertex)){
                    availVertex.push_back(vertex);
                }
            }
            if (availVertex.empty()) return -1;
            int u = random(0, availVertex.size() - 1);
            g.connect(v, availVertex[u]);
            return availVertex[u];
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

    void updateQueue(queue<int> &q, Graph &G, int v, int u) {
        int v_neighbour1 = G.Adj[v][0];
        int v_neighbour2 = G.Adj[v][1];
        int u_neighbour1 = G.Adj[u][0];
        int u_neighbour2 = G.Adj[u][1];
        if (G.Adj[v_neighbour1].size() != 3) q.push(v_neighbour1);
        if (G.Adj[v_neighbour2].size() != 3) q.push(v_neighbour2);
        if (G.Adj[u_neighbour1].size() != 3) q.push(u_neighbour1);
        if (G.Adj[u_neighbour2].size() != 3) q.push(u_neighbour2);
    }


    bool solve(Graph &G, int g) {
        vector<int> random_vertex_order = getRandOrder(G);
        for (int vertex: random_vertex_order) {
            queue<int> new_vertex_order;
            new_vertex_order.push(vertex);
            while (!new_vertex_order.empty()) {
                int v = new_vertex_order.front();
                new_vertex_order.pop();
                if (G.Adj[v].size() != 3) {
                    bfs(G, v, g);
                    int u = tools::generateEdge(G, v);
                    if (u == -1) return false;
                    G.visited[v] = false;
                    updateQueue(new_vertex_order, G, v, u);
                }
            }
        }
        return true;
    }

}


#endif