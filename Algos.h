#ifndef DFS_H
#define DFS_H


#include "Graph.h"
#include <queue>

//   DFS(G)
//   - Time: O(V + E)

//   DFS-VISIT(G, u)
//   - Time: O(E)

namespace Traversals {

    int time = 0;
    int iterationCounter = 0;

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

    void bfs(const Graph &G, int g) {
        time = 0;
        queue<Vertex *> Q;
        Q.push(G.V[0]);
        while (!Q.empty()) {
            Vertex *v = Q.front();
            Q.pop();
            if (v->color == WHITE) {
                v->color = BLACK;
            }
            time++;
            for (Vertex *u: G.Adj.at(v)) {
                if (u->color == WHITE) {
                    u->color = GRAY;
                    u->PI = v;
                    Q.push(u);
                }
            }
        }
    }


}
namespace tools {
    void vanish(Graph &G) {
        for (Vertex *v: G.V) {
            v->color = WHITE;
            v->PI = nullptr;
            v->f = 0;
            v->cc = 0;
            v->d = 0;
        }
    }
}
#endif