

#include "Graph.h"
#include <queue>
#include <random>
#include "IO.h"

#ifndef PROJECT_ALGOS_H
#define PROJECT_ALGOS_H



namespace tools {

    typedef enum {
        NO_CYCLES = 0,
        SINGLE_CYCLE = 1,
    } newCirclesOnG;

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
        //DFS variant

        if ((k < G.g) && G.isNeighbour(u, v)) {
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

    void replaceEdgeOnCycle(Graph &G, int u, int v, vector<pair<int, int>> &edgesOnCilcle) {
        pair<int, int> edgeToRemove = edgesOnCilcle[random(0, edgesOnCilcle.size() - 1)];
        G.disConnect(edgeToRemove.first, edgeToRemove.second);
        G.connect(u, v);
    }

    bool route_to_edges(list<int> route, vector<pair<int, int>> &edges) {
        std::list<int>::iterator it;
        for (it = route.begin(); it != route.end();) { //combina muzara aval ovedet? Tal please approve
            if ((++it) != route.end()) {
                --it;
                edges.emplace_back(*it, *(it++));
            }
        }
        return true;
    }


    bool solve(Graph &G, int g, int max_iter) {
        int iter = 0;
        while (!G.availV.empty() && iter < max_iter) {
            int u_index = tools::random(0, G.availV.size() - 1);
            int u = G.availV[u_index];
            int v = tools::getValidV(G, u);

            int num_cycles = tools::count_cycles(G, u, v, g - 2); //changed to g-2 misha
            tools::clear(G, G.d1);
            switch (num_cycles) {
                case NO_CYCLES:
                    G.connect(u, v);
                    break;
                case SINGLE_CYCLE: {
                    G.findPath(u, v);
                    list<int> route = G.trace_route(v);
//                    io::print_route(route, u, v);
                    vector<pair<int, int>> edges;
                    route_to_edges(route, edges);
                    tools::replaceEdgeOnCycle(G, u, v, edges);
                    break;
                }
                default:
                    break;
            }
            iter++;
        }
        return iter != max_iter;
    }


}


#endif