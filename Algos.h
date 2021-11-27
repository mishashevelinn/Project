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

    vector<int> illegal_vertex;
    namespace tools {
        void vanish(Graph &G) {

            for (int v: G.V) {
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

        int randomVertex(set<Vertex*> s) {
            auto it = std::begin(s);
            int n = random(0, s.size() - 1);
            // 'advance' the iterator n times
            std::advance(it,n);
            return (*it)->name;
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
            return v->color == WHITE;
        }

        bool generateEdge(Graph &g, Vertex *v) {
            int counter = 0;
            g.availVertexes.erase(g.availVertexes.find(v));
            int idx = randomVertex(g.availVertexes);
            while (!isLegalNeighbour(g, g.V[idx])) {
                if (counter == g.V.size()*4){
                    cout << "couldn't guess the name\n";
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

    void bfs(Graph &G, Vertex *root, int g) {
        tools::vanish_vector(illegal_vertex);
        G.V[0]->color = WHITE;
        for(Vertex *v: G.V){
            if(v->color != WHITE){
                cerr << v->name <<"'s color is "<< v->color <<endl;
            }
        }

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
            if (v->name == G.V.size() - 1) return true;
            if (G.Adj.at(v).size() == 3) continue;
            bfs(G, v, g);
            if (!tools::generateEdge(G, v)) return false;
            //v->color = WHITE;
        }
        return true;
    }

}


#endif