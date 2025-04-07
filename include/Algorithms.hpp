// email: yaacovkrawiec@gmail.com

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.hpp"

namespace graph {

    class Algorithms {
    public:
        // Returns a BFS tree graph from 'startVertex'
        static Graph bfs(const Graph& g, int startVertex);

        // Returns a DFS tree graph from 'startVertex'
        static Graph dfs(const Graph& g, int startVertex);

        // Returns a shortest-path tree using Dijkstra (throws if negative edges)
        static Graph dijkstra(const Graph& g, int startVertex);

        // Returns MST using Prim
        static Graph prim(const Graph& g);

        // Returns MST using Kruskal
        static Graph kruskal(const Graph& g);
    };

} // namespace graph

#endif
