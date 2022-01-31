

#include "Graph.h"
#include <queue>
#include <random>

#ifndef PROJECT_ALGOS_H
#define PROJECT_ALGOS_H


//   DFS(G)
//   - Time: O(V + E)

//   DFS-VISIT(G, u)
//   - Time: O(E)

namespace Traversals {
    int time = 0;
    int iterationCounter = 0;

    namespace tools {
        void clear(Graph &G, vector<int> d, char which = 'v') {
            if (which == 'd') {
                for (int v = 0; v < G.n; v++) {
                    d[v] = 0;
                }
            } else if (which == 'v') {
                for (int v = 0; v < G.n; v++) {
                    G.visited[v] = false;
                    G.PI[v] = -1;
                }

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
            //not visited by bfs and has 2 neighbours
            return (!G.visited[u] && (G.Adj[u].size() < 3));
        }

        int count_cycles(Graph &G, int u, int v, int k) {

            if (k == 0 && u == v) {
                cout << "hii";
                return 1;
            }
            if ((k == 1 || k == 2 || k == 3 || k == 4) && G.isNeighbour(u, v)) {
                return 1;
            }
            if (k <= 0)
                return 0;

            int count = 0;
            G.visited[u] = true;
            for (int neighbour: G.Adj[u]) {
                if (!G.visited[neighbour]) {
                    G.visited[neighbour] = true;
                    count += count_cycles(G, neighbour, v, k - 1);
                }
            }

            return count;
        }

        int generateEdge(Graph &g, int v) {
            vector<int> availVertex;
            for (int vertex = 0; vertex < g.n; vertex++) {
                if (isLegalNeighbour(g, vertex)) {
                    availVertex.push_back(vertex);
                }
            }
            if (availVertex.empty()) return -1;
            int u = random(0, availVertex.size() - 1);
            g.connect(v, availVertex[u]);
            return availVertex[u];
        }

        int getValidV(Graph &G, int u) {
            int v_index;
            int v;
            bool isNeighbours;
            do {
                isNeighbours = false;
                v_index = random(0, G.availV.size() - 1);
                v = G.availV[v_index];
                for (int i = 0; i < G.Adj[u].size(); i++) {

                    if (G.Adj[u][i] == v) {
                        isNeighbours = true;
                        break;
                    }
                }
            } while (v == u || isNeighbours);
            return v;
        }

        void replaceEdgeOnCircle(Graph &G, int u, int v, vector<pair<int, int>> edgesOnCilcle) {
            pair<int, int> edgeToRemove = edgesOnCilcle[random(0, edgesOnCilcle.size() - 1)];
            G.disConnect(edgeToRemove.first, edgeToRemove.second);
            G.connect(u, v);
        }


        bool getEdgesOnCircle(Graph &G, int u, int v, vector<pair<int, int>> &edgesOnCilcle) {
            int source = u;
            int dest;
            while (source != v) {
                vector<int> source_niegours = G.Adj[source];
                int numCircles = 0;
                for (int i = 0; i < source_niegours.size(); i++) {
                    if (G.d1[source_niegours[i]] + G.d2[source_niegours[i]] < G.g - 1) {
                        if (++numCircles == 2) return false;
                        dest = source_niegours[i];
                    }
                }
                pair<int, int> edge(source, dest);
                edgesOnCilcle.push_back(edge);
                source = dest;
            }
            return true;
        }
    }


    void bfs(Graph &G, int root, int g, vector<int> &d) {
        tools::clear(G, d);
        queue<int> Q;
        Q.push(root);
        G.visited[root] = true;
        G.visited_track.push_back(root);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int u: G.Adj[v]) {
                if (!G.visited[u]) {
                    d[u] = d[v] + 1;
                    G.visited[u] = true;
                    G.visited_track.push_back(u);
                    Q.push(u);
                }
            }
        }


    }


    vector<int> getRandOrder(Graph &g) {
        vector<int> order;
        for (int i = 0; i < g.n; i++) {
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

    typedef enum {
        NO_CIRCLES = 0,
        SINGLE_CIRCLE = 1,
    } newCirclesOnG;

    bool solve(Graph &G, int g, int max_iter) {
        int iter = 0;
        while (!G.availV.empty() && iter < max_iter) {
            int u_index = tools::random(0, G.availV.size() - 1);
            int u = G.availV[u_index];
            int v = tools::getValidV(G, u);

            int num_cyces = tools::count_cycles(G, u, v, g - 1);
            tools::clear(G, G.d1);
            switch (num_cyces) {
                case NO_CIRCLES:
                    G.connect(u, v);
                    break;
                case SINGLE_CIRCLE:
                    cout << "found single circle!\n";
                    G.findPath(u, v);
                    G.trace_route(v);
                    tools::clear(G, G.d1);

                    break;
                default:
                    break;
            }
            iter++;
        }
        return iter != max_iter;
    }
}


#endif