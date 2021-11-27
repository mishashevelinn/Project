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

    vector<Vertex *> illegal_vertex;
    namespace tools {
        void vanish(Graph &G) {

            for (Vertex *v: G.V) {
                v->color = WHITE;
                v->PI = nullptr;
                v->f = 0;
                v->d = 0;
            }
        }

        int random(int min, int max) {
            std::random_device rd;     // only used once to initialise (seed) engine
            std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

            auto random_integer = uni(rng);
            return random_integer;
        }

        void clear_queue(queue<Vertex *> q) {
            std::queue<Vertex *> empty;
            std::swap(q, empty);
        }

        void vanish_vector(vector<Vertex *> v) {
            for (Vertex *u: v) {
                u->color = WHITE;
                u->d = 0;
                u->PI = nullptr;
            }
            v.clear();


        }

        bool isLegalNeighbour(const Graph &G, Vertex *v) { //TODO inline?
            return v->color == WHITE && G.Adj.at(v).size() < 3;
        }

        bool generateEdge(Graph &g, Vertex *v) {
            int counter = 0;
            int u = random(0, g.V.size() - 1);
            while (!isLegalNeighbour(g, g.V[u])) {
                if (counter == g.V.size()*4){
                    cout << "coldn't guess the name\n";
                    return false;
                }
                counter++;
                u = random(0, g.V.size() - 1);
            }
            g.connect(v, g.V[u]);
            return true;
        }
    }


    void dfsVisit(const Graph &G, Vertex *u) {
        u->d = ++time;  // white vertex u has just been discovered
        u->color = GRAY;

        for (Vertex *v: G.Adj.at(u)) {  // explore edge (u, v)
            if (v->color == WHITE) {
                v->PI = u;
                dfsVisit(G, v);
            } else {
                G.print();
            }
        }
        u->f = ++time;
        u->color = BLACK;  // blacken u; it is finished
        G.print();
    }

    void dfs(const Graph &G) {
        for (Vertex *u: G.V) {
            u->color = WHITE;
            u->PI = nullptr;
        }
        time = 0;
        for (Vertex *u: G.V)
            if (u->color == WHITE)
                dfsVisit(G, u);
    }

    void bfs(const Graph &G, Vertex *root, int g) {
        tools::vanish_vector(illegal_vertex);
        time = 0;
        queue<Vertex *> Q;
        Q.push(root);
        root->color = BLACK;
        while (!Q.empty()) {
            Vertex *v = Q.front();
            Q.pop();
            time++;
            for (Vertex *u: G.Adj.at(v)) {
                if (u->color == WHITE) {
                    u->d = v->d + 1;
                    if (u->d == g + 1) {
                        return;
                    }
                    u->color = BLACK;
                    illegal_vertex.push_back(u);
                    u->PI = v;
                    Q.push(u);
                }
            }
        }
    }

    bool solve(Graph &G, int g) {
        g--;
        for (Vertex *v: G.V) {
            if (v->name == G.V.size() - 1) break;
            if (G.Adj.at(v).size() == 3) continue;
            bfs(G, v, g);
            if (!tools::generateEdge(G, v)) return false;
            v->color = WHITE;
        }
        return true;
    }

}


#endif