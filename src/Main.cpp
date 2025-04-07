// email: yaacovkrawiec@gmail.com

#include "../include/Graph.h"
#include "../include/Algorithms.h"
#include <iostream>

using namespace graph;

int main() {
    // First example with only positive weighted edges (no negative edeges)
    Graph g(5);
    g.addEdge(0,1,2);
    g.addEdge(0,2,3);
    g.addEdge(1,3,1);
    g.addEdge(2,3,4);
    g.addEdge(3,4,6);

    std::cout << "First example (No negative edges)\n";
    std::cout << "Original Graph:\n";
    g.printGraph();
    std::cout << "\n";

    // BFS from vertex 0
    Graph bfsTree = Algorithms::bfs(g, 0);
    std::cout << "BFS Tree (from 0):\n";
    bfsTree.printGraph();
    std::cout << "\n";

    // DFS from vertex 0
    Graph dfsTree = Algorithms::dfs(g, 0);
    std::cout << "DFS Tree (from 0):\n";
    dfsTree.printGraph();
    std::cout << "\n";

    // Dijkstra from vertex 0
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    std::cout << "Dijkstra Tree (shortest paths from 0):\n";
    dijkstraTree.printGraph();
    std::cout << "\n";

    // Prim MST
    Graph primMST = Algorithms::prim(g);
    std::cout << "Prim MST:\n";
    primMST.printGraph();
    std::cout << "\n";

    // Kruskal MST
    Graph kruskalMST = Algorithms::kruskal(g);
    std::cout << "Kruskal MST:\n";
    kruskalMST.printGraph();
    std::cout << "\n";


    // Another example with this time negative edges so we can check the exception in dijkstra
    Graph g2(4);
    // Here we add a negative edge weight
    g2.addEdge(0,1,-2);
    g2.addEdge(1,2,4);
    g2.addEdge(2,3,1);

    std::cout << "Second example (including negative edge(s) \n";
    std::cout << "Original Graph (with negative edge 0-1):\n";
    g2.printGraph();
    std::cout << "\n";

    // Let's see that BFS or DFS still works, because they don't mind negative edges
    Graph bfs2 = Algorithms::bfs(g2, 0);
    std::cout << "BFS Tree (from 0, ignoring negatives):\n";
    bfs2.printGraph();
    std::cout << "\n";

    // But Dijkstra will throw an exception
    std::cout << "Trying Dijkstra on the graph with negative edges:\n";
    try {
        Graph dijkstra2 = Algorithms::dijkstra(g2, 0);
        // If no exception, we print it
        dijkstra2.printGraph();
    } catch(const char* msg) {
        std::cerr << "Exception caught: " << msg << std::endl;
    }

    return 0;
}
