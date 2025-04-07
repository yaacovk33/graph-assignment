// email: yaacovkrawiec@gmail.com

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>  // for exit, etc.

namespace graph {

    // Represents one edge in the adjacency list
    struct Edge {
        int destination;
        int weight;
    };

    class Graph {
    private:
        int numVertices;         // number of vertices
        Edge** adjacencyList;    // adjacencyList[v] = dynamic array of Edges
        int* adjacencySizes;     // adjacencySizes[v] = current number of edges
        int* adjacencyCapacities;// adjacencyCapacities[v] = allocated capacity for adjacencyList[v]

        // Expand the adjacency array for a given vertex (when it's full)
        void expandEdgeList(int vertex);

    public:
        // Constructor
        Graph(int numberOfVertices);

        // Destructor
        ~Graph();

        // Copy constructor (if needed)
        Graph(const Graph& other);

        // Assignment operator (if needed)
        Graph& operator=(const Graph& other);

        // Add an undirected edge (default weight = 1)
        void addEdge(int source, int dest, int weight = 1);

        // Remove an undirected edge (throw exception if it doesn't exist)
        void removeEdge(int source, int dest);

        // Print adjacency list
        void printGraph() const;

        // Accessors
        int getNumVertices() const { return numVertices; }
        Edge* getAdjList(int vertex) const { return adjacencyList[vertex]; }
        int getAdjSize(int vertex) const { return adjacencySizes[vertex]; }
    };

} // namespace graph

#endif
