#ifndef DFS_H
#define DFS_H


#include "Graph.h"


//   DFS(G)
//   - Time: O(V + E)

//   DFS-VISIT(G, u)
//   - Time: O(E)

namespace CLRS {
namespace CH22 {
int time;
int iterationCounter = 0;

void dfsVisit(const Graph& G, Vertex* u) {
  u->d = ++time;  // white vertex u has just been discovered
  u->color = GRAY;

  for (Vertex* v : G.Adj.at(u)) {  // explore edge (u, v)
    if (v->color == WHITE) {
      v->PI = u;
      dfsVisit(G, v);
    } else {
      printGraph(G);
    }
  }
  u->f = ++time;
  u->color = BLACK;  // blacken u; it is finished
  printGraph(G);
}

void dfs(const Graph& G) {
  for (Vertex* u : G.V) {
    u->color = WHITE;
    u->PI = nullptr;
  }
  time = 0;
  for (Vertex* u : G.V)
    if (u->color == WHITE)
      dfsVisit(G, u);
}


#endif