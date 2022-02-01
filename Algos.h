

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

        if ((k < G.g) && (G.isNeighbour(u, v) != -1)) {
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
        //Picks a random vertex v as a candidate for the edge (u,v)
        // valid v should not be adjacent to u and u != v
        vector<int> optional_neighbours_for_u;
        for (int i = 0; i < G.availV.size(); i++) {
            if ((G.isNeighbour(G.availV[i], u) == -1) && u != G.availV[i]){
                optional_neighbours_for_u.push_back(G.availV[i]);
            }
        }

        if (optional_neighbours_for_u.empty()) return -1;

        int v_index = random(0, optional_neighbours_for_u.size() - 1);
        int v = optional_neighbours_for_u[v_index];
        return v;
//
//        int v_index;
//        int v;
//        bool isNeighbours;
//        do {
//            isNeighbours = false;
//            v_index = random(0, G.availV.size() - 1);
//            v = G.availV[v_index];
//            for (int i = 0; i < G.Adj[u].size(); i++) {
//
//                if (G.Adj[u][i] == v) {
//                    isNeighbours = true;
//                    break;
//                }
//            }
//        } while (v == u || isNeighbours);
//        return v;
    }

    void replaceEdgeOnCycle(Graph &G, int u, int v, vector<pair<int, int>> &edgesOnCilcle) {
        //Called when single short cycle is detected in the step of hill climber.
        //removing random edge from the short cycle and adding the edge (u,v)

        pair<int, int> edgeToRemove = edgesOnCilcle[random(0, edgesOnCilcle.size() - 1)];
//        cout << "replacing one of edges:\n";
//        io::print_edges(edgesOnCilcle);
        G.disConnect(edgeToRemove.first, edgeToRemove.second);

        ///DEBUG///
//        tools::clear(G, G.d1);
//        int cycles = tools::count_cycles(G, u, v, G.g-2);
//        if (cycles == 1){
//            if(G.isNeighbour(u,v) != -1){
//                cout << "THEY ARE NEIGHBOURS" <<endl;
//            }
//            ofstream file("After edge removal");
//            cout << "edge " << "(" << edgeToRemove.first<<','<<edgeToRemove.second<<") was removed\n";
//            io::write_graph(G, file);
//            G.findPath(u, v);
//            list<int> route = G.trace_route(u,v);
//            cout  << "\nbut exists route: ";
//            io::print_route(route, u,v);
//            exit(0);
//
//        }
//        cout << "num cycles after disconnect: " << cycles << endl;

        G.connect(u, v);
    }

    bool route_to_edges(list<int> route, vector<pair<int, int>> &edges) {
        //translates list: [1,2,3,4] to vector of pairs [(1,2),(2,3),(3,4)]
        std::list<int>::iterator it;
        for (it = route.begin(); it != route.end();) {
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
            if (v == -1) {
                iter++;
                continue;
            }

            int num_cycles = tools::count_cycles(G, u, v, g - 2); //changed to g-2 misha
            tools::clear(G, G.d1);
            switch (num_cycles) {
                case NO_CYCLES:
                    G.connect(u, v);
                    break;
                case SINGLE_CYCLE: {
                    G.findPath(u, v); //shortest path closing the single cycle with E+(u,v),
                    list<int> route = G.trace_route(u, v);
//                    io::print_route(route,u,v);

                    vector<pair<int, int>> edges;
                    route_to_edges(route, edges);
                    tools::replaceEdgeOnCycle(G, u, v, edges);
                    tools:clear(G, G.d1);
                    break;
                }
                default:
                    break;
            }
            iter++;
        }
        cout << "Finish running after " << iter << " iterations" << endl;
        return iter != max_iter;
    }


}


#endif