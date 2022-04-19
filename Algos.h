

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
        //not visited by bfs and has 2 neighbours DEPRECATED IN CURRENT VER
        return (!G.visited[u] && (G.Adj[u].size() < 3));
    }

    int count_cycles(Graph &G, int u, int v, int k) {
        //DFS variant count all paths p s.t. len(p) < k. if p[-1] == v => there is a cycle c, len(c) < k
        // initially k = g - 2

//        if ( u == v) {
//            cout << "u == v state can occur"; //it shouldn't
//            return 1;
//        }
        if (k <= 0) //DFS exceed the depth bound, early stop
            return 0;

        //last vertex of the short path is adjacent to u => short cycle detected
        if ((k > 0) && (G.isNeighbour(u, v) != -1)) {
            return 1;
        }


        //G.visited is not used to obtain all possible paths(cycles)
        int count = 0;
        for (int neighbour: G.Adj[u]) {
            count += count_cycles(G, neighbour, v, k - 1); //g - 1
            if (count >= 2) return count;
        }

        return count;
    }


    int getValidV(Graph &G, int u) {
        //Picks a random vertex v as a candidate for the edge (u,v)
        // valid v should not be adjacent to u and u != v
        //if v is valid Deg(v) = 2 (if initial graph is Hamiltonian cycle - current version)
        vector<int> optional_neighbours_for_u;
        for (int i = 0; i < G.legalDeg.size(); i++) {
            ///*isEven added for DiGraph///*
            if ((G.isNeighbour(G.legalDeg[i], u) == -1) && u != G.legalDeg[i]) {
                assert(G.isEven(G.legalDeg[i]));
                optional_neighbours_for_u.push_back(G.legalDeg[i]);
            }
        }

        if (optional_neighbours_for_u.empty()) return -1;

        int v_index = random(0, (int) optional_neighbours_for_u.size() - 1);
        int v = optional_neighbours_for_u[v_index];
        return v;
    }

    void rout2edgesToRemove(Graph &G, vector<pair<int, int>> &edgesOnCylcle,vector<pair<int, int>> &edgesToRemoveOnCycle) {
        for (pair<int, int> edge: edgesOnCylcle) {
            if (G.isInitialEdge(edge)) edgesToRemoveOnCycle.push_back(edge);
        }
    }

    void replaceEdgeOnCycle(Graph &G, int u, int v, vector<pair<int, int>> &edgesOnCycle) {
        //Invoked when single short cycle is detected in the step of hill climber.
        //removing random edge from the short cycle and adding the edge (u,v)
        ///*Changed for Even-Odd version: edges from original cycle can't be removed///*

        pair <int, int> edgeToRemove = edgesOnCycle[random(0, (int) edgesOnCycle.size() - 1)];
        cout << "removing " << edgeToRemove.first << " " << edgeToRemove.second << endl;
        G.disConnect(edgeToRemove.first, edgeToRemove.second);
//        assert(G.isNeighbour(edgeToRemove.first, edgeToRemove.second) == -1);

        ///DEBUG: after removal of random edge on the cycle the condition should be always FALSE///
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

    bool isEven(int num) {
        return !(num % 2);
    }

    bool route_to_edges(list<int> route, vector<pair<int, int>> &edges) {
        //translates list: [1,2,3,4] to vector of pairs [(1,2),(2,3),(3,4)]
        std::list<int>::iterator it;
        for (it = route.begin(); it != route.end();) {
            if ((++it) != route.end()) {
                --it;
//                if (isEven(*it) && isEven(*(it++))) {
//                    --it;
                    edges.emplace_back(*it, *(it++));
//                }
            }
        }
        return true;
    }

    void printRoute(vector<pair<int, int>> &route) {
        for (pair<int, int> edge: route) {
            cout << "(" << edge.first << ", " << edge.second << ") --> ";
        }
        cout << endl;
    }

    bool solve(Graph &G, int g, int max_iter) {
        int iter = 0;
        int TALSHA_replaceCounter = 0;
        while (!G.legalDeg.empty() && iter < max_iter) {
            int u_index = tools::random(0, (int) G.legalDeg.size() - 1);
            int u = G.legalDeg[u_index]; //pick a random u from V s.t. Deg(u) = 2

            int v = tools::getValidV(G, u); //pick a random v from V s.t. v is not adjacent to u, deg(v) = 2, v is Even
            if (v == -1) { // no candidates for (u,v) in E
                iter++;
                continue;
            }

            int num_cycles = tools::count_cycles(G, u, v, g - 2); //changed from g-1 to g-2 misha
            switch (num_cycles) {
                case NO_CYCLES:  // E + {(u,v)} is partial solution
                    G.connect(u, v);
                    break;
                case SINGLE_CYCLE: {  // (u,v) is 1-candidate
                    tools::clear(G, G.d1);
                    G.findPath(u, v);  // shortest path closing the single cycle with E+(u,v),
                    list<int> route = G.trace_route(u, v);
//                    io::print_route(route,u,v);

                    vector<pair<int, int>> edgesOnRoute;
                    vector<pair<int, int>> edgesOnRouteToRemove;
                    route_to_edges(route, edgesOnRoute);
                    rout2edgesToRemove(G, edgesOnRoute, edgesOnRouteToRemove);
                    if (edgesOnRouteToRemove.empty()) {
                        cout << "No edges to remove on route:" << endl;
                        printRoute(edgesOnRoute);
                        break;
                    }
                    TALSHA_replaceCounter++;
                    tools::replaceEdgeOnCycle(G, u, v, edgesOnRouteToRemove);
                    break;
                }
                default:  // (u,v) is k-candidate , k > 1; adding (u,v) to E yields more than 1 short cycle in G
                    break;
            }
            iter++;
        }
        cout << "TALSHA: check how many replacement (SINGLE_CYCLE case worked): " << TALSHA_replaceCounter << endl;
        return iter != max_iter; //TRUE if (for all v in V deg(v) = 3 & no short cycles in G)
    }


}


#endif