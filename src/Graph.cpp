// email: yaacovkrawiec@gmail.com

#include "../include/Graph.h"

namespace graph {

    Graph::Graph(int numberOfVertices)
        : numVertices(numberOfVertices)
    {
        if(numberOfVertices <= 0) {
            std::cerr << "Number of vertices must be positive.\n";
            std::exit(1);
        }

        // Allocate arrays
        adjacencyList = new Edge*[numVertices];
        adjacencySizes = new int[numVertices];
        adjacencyCapacities = new int[numVertices];

        // Initialize
        for(int i = 0; i < numVertices; i++) {
            adjacencyList[i] = nullptr;
            adjacencySizes[i] = 0;
            adjacencyCapacities[i] = 0;
        }
    }

    Graph::~Graph() {
        // Free each adjacency sub-array
        for(int i = 0; i < numVertices; i++) {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;

        // Free arrays
        delete[] adjacencySizes;
        delete[] adjacencyCapacities;
    }

    // (Optional) Copy constructor
    Graph::Graph(const Graph& other)
        : numVertices(other.numVertices)
    {
        adjacencyList = new Edge*[numVertices];
        adjacencySizes = new int[numVertices];
        adjacencyCapacities = new int[numVertices];

        for(int i = 0; i < numVertices; i++) {
            adjacencySizes[i] = other.adjacencySizes[i];
            adjacencyCapacities[i] = other.adjacencyCapacities[i];

            adjacencyList[i] = new Edge[ adjacencyCapacities[i] ];
            for(int j = 0; j < adjacencySizes[i]; j++) {
                adjacencyList[i][j] = other.adjacencyList[i][j];
            }
        }
    }

    // (Optional) operator=
    Graph& Graph::operator=(const Graph& other) {
        if(this == &other) {
            return *this;
        }

        // Free old data
        for(int i = 0; i < numVertices; i++) {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
        delete[] adjacencySizes;
        delete[] adjacencyCapacities;

        // Copy new data
        numVertices = other.numVertices;
        adjacencyList = new Edge*[numVertices];
        adjacencySizes = new int[numVertices];
        adjacencyCapacities = new int[numVertices];

        for(int i = 0; i < numVertices; i++) {
            adjacencySizes[i] = other.adjacencySizes[i];
            adjacencyCapacities[i] = other.adjacencyCapacities[i];
            adjacencyList[i] = new Edge[ adjacencyCapacities[i] ];
            for(int j = 0; j < adjacencySizes[i]; j++) {
                adjacencyList[i][j] = other.adjacencyList[i][j];
            }
        }
        return *this;
    }

    void Graph::expandEdgeList(int vertex) {
        int oldCap = adjacencyCapacities[vertex];
        int newCap = (oldCap == 0) ? 2 : oldCap * 2;
        Edge* newArray = new Edge[newCap];

        for(int i = 0; i < adjacencySizes[vertex]; i++) {
            newArray[i] = adjacencyList[vertex][i];
        }

        delete[] adjacencyList[vertex];
        adjacencyList[vertex] = newArray;
        adjacencyCapacities[vertex] = newCap;
    }

    void Graph::addEdge(int source, int dest, int weight) {
        if(source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
            std::cerr << "Invalid vertex.\n";
            return;
        }
        if(source == dest) {
            std::cerr << "Simple graph: no loops allowed.\n";
            return;
        }
        // For Dijkstra (or BFS/DFS), if negative is not allowed, we might just warn or throw
        if(weight < 0) {
            std::cerr << "Warning: negative edge weight. Dijkstra may fail if used.\n";
        }

        // Add (dest, weight) to adjacencyList[source]
        if(adjacencySizes[source] == adjacencyCapacities[source]) {
            expandEdgeList(source);
        }
        adjacencyList[source][ adjacencySizes[source] ].destination = dest;
        adjacencyList[source][ adjacencySizes[source] ].weight = weight;
        adjacencySizes[source]++;

        // Add (source, weight) to adjacencyList[dest]
        if(adjacencySizes[dest] == adjacencyCapacities[dest]) {
            expandEdgeList(dest);
        }
        adjacencyList[dest][ adjacencySizes[dest] ].destination = source;
        adjacencyList[dest][ adjacencySizes[dest] ].weight = weight;
        adjacencySizes[dest]++;
    }

    void Graph::removeEdge(int source, int dest) {
        if(source < 0 || source >= numVertices || dest < 0 || dest >= numVertices) {
            throw "Invalid vertices for removeEdge.";
        }
        bool foundSrc = false;
        for(int i = 0; i < adjacencySizes[source]; i++) {
            if(adjacencyList[source][i].destination == dest) {
                foundSrc = true;
                for(int j = i; j < adjacencySizes[source] - 1; j++) {
                    adjacencyList[source][j] = adjacencyList[source][j+1];
                }
                adjacencySizes[source]--;
                break;
            }
        }

        bool foundDest = false;
        for(int i = 0; i < adjacencySizes[dest]; i++) {
            if(adjacencyList[dest][i].destination == source) {
                foundDest = true;
                for(int j = i; j < adjacencySizes[dest] - 1; j++) {
                    adjacencyList[dest][j] = adjacencyList[dest][j+1];
                }
                adjacencySizes[dest]--;
                break;
            }
        }

        if(!foundSrc || !foundDest) {
            throw "Edge does not exist.";
        }
    }

    void Graph::printGraph() const {
        std::cout << "Graph adjacency list:\n";
        for(int v = 0; v < numVertices; v++) {
            std::cout << "Vertex " << v << ": ";
            for(int i = 0; i < adjacencySizes[v]; i++) {
                std::cout << "(" << adjacencyList[v][i].destination 
                          << ", w=" << adjacencyList[v][i].weight << ") ";
            }
            std::cout << "\n";
        }
    }

} // namespace graph
