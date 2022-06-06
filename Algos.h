

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

    void clear(Graph &G) {
//  clear graph before running bfs/ dfs
        for (int v = 0; v < G.n; v++) {
            G.d[v] = 0;
            G.visited[v] = false;
            G.PI[v] = -1;
        }
    }

    vector<int> getRandOrder(vector<int> &vertexes) {
        // copy all even vertexes to new order vector and shuffle them, to random permutation
        vector<int> order(vertexes);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine e(seed);
        std::shuffle(order.begin(), order.end(), e);
        return order;
    }

    int random(int min, int max) {
        // get random int in range (min, max)
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

    int count_cycles(Graph &G, int u, int v, int k, int prev=-1) {
        //DFS variant count all paths p s.t. len(p) < k. if p[-1] == v => there is a cycle c, len(c) < k
        // initially k = g - 2
        if (k <= 0) //DFS exceed the depth bound, early stop
            return 0;
        //last vertex of the short path is adjacent to u => short cycle detected
        if ((k > 0) && (G.isNeighbour(u, v) != -1)) {
            return 1;
        }
        //G.visited is not used to obtain all possible paths(cycles)
        int count = 0;
        for (int neighbour: G.Adj[u]) {
            if (prev != neighbour) {
                count += count_cycles(G, neighbour, v, k - 1, u); //g - 1
                if (count >= 2) return count;
            }
        }
        return count;
    }


    vector<int> getPermOfValidV(Graph &G, int u) {
        //Picks a random vertex v as a candidate for the edge (u,v)
        // valid v should not be adjacent to u and u != v
        //if v is valid Deg(v) = 2
        // return random order of all valid v (optional neighbours for u)
        vector<int> optional_neighbours_for_u;
        for (int i = 0; i < G.legalDeg.size(); i++) {
            if ((G.isNeighbour(G.legalDeg[i], u) == -1) && u != G.legalDeg[i]) {
                assert(G.isEven(G.legalDeg[i]));
                optional_neighbours_for_u.push_back(G.legalDeg[i]);
            }
        }
        return getRandOrder(optional_neighbours_for_u);
    }

    void rout2edgesToRemove(Graph &G, vector<pair<int, int>> &edgesOnCylcle,vector<pair<int, int>> &edgesToRemoveOnCycle) {
        // filter the edges that can be removed from cycle that was found.
        // edge can be removed if both vertices are even.
        for (pair<int, int> edge: edgesOnCylcle) {
            if (G.isInitialEdge(edge)) edgesToRemoveOnCycle.push_back(edge);
        }
    }

    void replaceEdgeOnCycle(Graph &G, int u, int v, vector<pair<int, int>> &edgesOnCycle) {
        // randomly pick 1 edge from the cycle (after filter the edges), delete it and add new edge (u, v)
        // now edge (u, v) is legal because it replaced another edge on cycle with len >= g.
        pair <int, int> edgeToRemove = edgesOnCycle[random(0, (int) edgesOnCycle.size() - 1)];
        G.disConnect(edgeToRemove.first, edgeToRemove.second);
        G.connect(u, v);
    }

    bool isEven(int num) {
        return !(num % 2);
    }

    bool route_to_edges(list<int> route, vector<pair<int, int>> &edges) {
        // return vector of pairs (edges) from given rout (cycle)- vector of vertices
        std::list<int>::iterator it;
        for (it = route.begin(); it != route.end();) {
            if ((++it) != route.end()) {
                --it;
                    edges.emplace_back(*it, *(it++));
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


    bool generateEdge(Graph &g, int v) {
        // for algorithm B usage.
        // after running BFS from vertex v, we are looking for all vertices u, that d[u] >= g-1.
        // that condition will promise that our graph won't have circles lower than g.
        // at the end, we will connect v and randomly vertex u from the optionals vertices.
        vector<int> availVertex;
        for (int i = 0; i < g.legalDeg.size(); i++){
            if (isLegalNeighbour(g, g.legalDeg[i])){
                availVertex.push_back(g.legalDeg[i]);
            }
        }
        if (availVertex.empty()) return false;
        int u = random(0, availVertex.size() - 1);
        g.connect(v, availVertex[u]);
        return true;
    }


    void bfs(Graph &G, int root, int g) {
        // normal BFS implementation
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




    bool solve_B(Graph &G, int g) {
        // algorithm B will run as long as he can find legal neighbour u for vertex v.
        vector<int> random_vertex_order = getRandOrder(G.legalDeg);
        for (int v: random_vertex_order){
            if (G.Adj[v].size() != 3) {
                bfs(G, v, g);
                if (!tools::generateEdge(G, v)) return false;
                G.visited[v] = false;
            }
        }
        return true;

    }


    bool solve(Graph &G, int g, int max_iter) {
        // Hill Climber algorithm will run max_iter iterations, and every iteration will try to add/ replace
        // new legal edge to the graph.
        int iter = 0;
        int replaceCounter = 0;
        while (!G.legalDeg.empty() && iter < max_iter) {

            int u_index = tools::random(0, (int) G.legalDeg.size() - 1);
            int u = G.legalDeg[u_index]; //pick a random u from V s.t. Deg(u) = 2

            vector<int> optional_neighbours_for_u = tools::getPermOfValidV(G, u); //pick a random v from V s.t. v is not adjacent to u, deg(v) = 2, v is Even
            if (optional_neighbours_for_u.empty()) { // no candidates for (u,v) in E
                iter++;
                continue;
            }
            bool connected = false;
            for (int v: optional_neighbours_for_u) {
                int num_cycles = tools::count_cycles(G, u, v, g - 2); //changed from g-1 to g-2 misha
                switch (num_cycles) {
                    case NO_CYCLES:  // E + {(u,v)} is partial solution
                        G.connect(u, v);
                        connected = true;
                        break;
                    case SINGLE_CYCLE: {  // (u,v) is 1-candidate
                        tools::clear(G);
                        G.findPath(u, v);  // shortest path closing the single cycle with E+(u,v),
                        list<int> route = G.trace_route(u, v);

                        vector<pair<int, int>> edgesOnRoute;
                        vector<pair<int, int>> edgesOnRouteToRemove;
                        route_to_edges(route, edgesOnRoute);
                        rout2edgesToRemove(G, edgesOnRoute, edgesOnRouteToRemove);
                        if (edgesOnRouteToRemove.empty()) {
                            break;
                        }
                        replaceCounter++;
                        tools::replaceEdgeOnCycle(G, u, v, edgesOnRouteToRemove);
                        connected = true;
                        break;
                    }
                    default:  // (u,v) is k-candidate , k > 1; adding (u,v) to E yields more than 1 short cycle in G
                        break;
                }
                iter++;
                if (connected) break;
            }
        }
        return G.legalDeg.empty(); //TRUE if (for all v in V deg(v) = 3 & no short cycles in G)
    }


}


#endif