// email: yaacovkrawiec@gmail.com

#include "../include/Graph.h"
#include "../include/Algorithms.h"
#include <iostream>

using namespace graph;

int main() {
    // Create a simple graph of 5 vertices
    Graph g(5);
    g.addEdge(0,1,2);
    g.addEdge(0,2,3);
    g.addEdge(1,3,1);
    g.addEdge(2,3,4);
    g.addEdge(3,4,6);

    std::cout << "Original Graph:\n";
    g.printGraph();
    std::cout << "\n";

    // BFS
    Graph bfsTree = Algorithms::bfs(g, 0);
    std::cout << "BFS Tree (from 0):\n";
    bfsTree.printGraph();
    std::cout << "\n";

    // DFS
    Graph dfsTree = Algorithms::dfs(g, 0);
    std::cout << "DFS Tree (from 0):\n";
    dfsTree.printGraph();
    std::cout << "\n";

    // Dijkstra
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    std::cout << "Dijkstra Tree (shortest paths from 0):\n";
    dijkstraTree.printGraph();
    std::cout << "\n";

    // Prim
    Graph primMST = Algorithms::prim(g);
    std::cout << "Prim MST:\n";
    primMST.printGraph();
    std::cout << "\n";

    // Kruskal
    Graph kruskalMST = Algorithms::kruskal(g);
    std::cout << "Kruskal MST:\n";
    kruskalMST.printGraph();
    std::cout << "\n";

    return 0;
}
