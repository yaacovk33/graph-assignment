// email: yaacovkrawiec@gmail.com

#include "../include/Algorithms.h"
#include <limits> // For numeric_limits<int>::max()

namespace graph {

    //A simple array-based queue for BFS
    class ArrayQueue {
    private:
        int* data;
        int front;
        int rear;
    
    public:
        // We keep the constructor parameter 'cap' because we use it in new int[cap]
        ArrayQueue(int cap) : front(0), rear(0) {
            data = new int[cap];
        }
        ~ArrayQueue() {
            delete[] data;
        }
        bool isEmpty() const {
            return (front == rear);
        }
        void enqueue(int val) {
            data[rear++] = val;
        }
        int dequeue() {
            return data[front++];
        }
    };

    // BFS
    Graph Algorithms::bfs(const Graph& g, int startVertex) {
        int n = g.getNumVertices();
        Graph bfsTree(n);

        bool* visited = new bool[n];
        for(int i = 0; i < n; i++) {
            visited[i] = false;
        }

        ArrayQueue queue(n*2); // We pass n*2 as capacity
        visited[startVertex] = true;
        queue.enqueue(startVertex);

        while(!queue.isEmpty()) {
            int u = queue.dequeue();
            // Explore adjacency
            int adjSize = g.getAdjSize(u);
            Edge* edges = g.getAdjList(u);

            for(int i = 0; i < adjSize; i++) {
                int v = edges[i].destination;
                if(!visited[v]) {
                    visited[v] = true;
                    // Add edge to BFS tree
                    bfsTree.addEdge(u, v, edges[i].weight);
                    queue.enqueue(v);
                }
            }
        }

        delete[] visited;
        return bfsTree;
    }

    // ----- DFS (recursive)
    static void dfsVisit(const Graph& g, Graph& dfsTree, int u, bool* visited) {
        visited[u] = true;

        int adjSize = g.getAdjSize(u);
        Edge* edges = g.getAdjList(u);
        for(int i = 0; i < adjSize; i++) {
            int v = edges[i].destination;
            if(!visited[v]) {
                // Add edge in DFS tree
                dfsTree.addEdge(u, v, edges[i].weight);
                dfsVisit(g, dfsTree, v, visited);
            }
        }
    }

    Graph Algorithms::dfs(const Graph& g, int startVertex) {
        int n = g.getNumVertices();
        Graph dfsTree(n);

        bool* visited = new bool[n];
        for(int i = 0; i < n; i++) {
            visited[i] = false;
        }

        dfsVisit(g, dfsTree, startVertex, visited);

        delete[] visited;
        return dfsTree;
    }

    //An array-based priority queue for Dijkstra/Prim
    struct PQItem {
        int vertex;
        int dist;
    };

    class ArrayMinPriorityQueue {
    private:
        PQItem* data;
        int size;
    public:
        // Keep constructor param 'cap' to allocate 'data'
        ArrayMinPriorityQueue(int cap) : size(0) {
            data = new PQItem[cap];
        }
        ~ArrayMinPriorityQueue() {
            delete[] data;
        }
        bool isEmpty() const {
            return (size == 0);
        }
        void push(int vertex, int distance) {
            data[size].vertex = vertex;
            data[size].dist = distance;
            size++;
        }
        PQItem pop() {
            if(isEmpty()) {
                return { -1, -1 };
            }
            int minIndex = 0;
            int minVal = data[0].dist;
            for(int i = 1; i < size; i++) {
                if(data[i].dist < minVal) {
                    minVal = data[i].dist;
                    minIndex = i;
                }
            }
            PQItem result = data[minIndex];
            data[minIndex] = data[size - 1];
            size--;
            return result;
        }
        void decreaseKey(int vertex, int newDist) {
            for(int i = 0; i < size; i++) {
                if(data[i].vertex == vertex) {
                    if(newDist < data[i].dist) {
                        data[i].dist = newDist;
                    }
                    break;
                }
            }
        }
        bool contains(int vertex) const {
            for(int i = 0; i < size; i++) {
                if(data[i].vertex == vertex) {
                    return true;
                }
            }
            return false;
        }
    };

    //Dijkstra with negative edge weight exception
    Graph Algorithms::dijkstra(const Graph& g, int startVertex) {
        int n = g.getNumVertices();
        Graph tree(n);

        // Check for negative edges first
        for(int u = 0; u < n; u++) {
            int sizeAdj = g.getAdjSize(u);
            Edge* edges = g.getAdjList(u);
            for(int i = 0; i < sizeAdj; i++) {
                if(edges[i].weight < 0) {
                    throw "Dijkstra does not support negative edge weights.";
                }
            }
        }

        int* dist = new int[n];
        bool* visited = new bool[n];
        int* parent = new int[n];

        for(int i = 0; i < n; i++) {
            dist[i] = std::numeric_limits<int>::max();
            visited[i] = false;
            parent[i] = -1;
        }
        dist[startVertex] = 0;

        ArrayMinPriorityQueue pq(n*2);
        pq.push(startVertex, 0);

        while(!pq.isEmpty()) {
            PQItem item = pq.pop();
            int u = item.vertex;
            if(u == -1) break;
            if(visited[u]) continue;

            visited[u] = true;

            int sizeAdj = g.getAdjSize(u);
            Edge* edges = g.getAdjList(u);
            for(int i = 0; i < sizeAdj; i++) {
                int v = edges[i].destination;
                int w = edges[i].weight;

                // Relax
                if(!visited[v] && dist[u] != std::numeric_limits<int>::max()
                   && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    if(!pq.contains(v)) {
                        pq.push(v, dist[v]);
                    } else {
                        pq.decreaseKey(v, dist[v]);
                    }
                }
            }
        }

        // Build the shortest path tree
        for(int i = 0; i < n; i++) {
            if(parent[i] != -1) {
                int w = dist[i] - dist[parent[i]];
                tree.addEdge(parent[i], i, w);
            }
        }

        delete[] dist;
        delete[] visited;
        delete[] parent;
        return tree;
    }

    //Union-Find for Kruskal
    class UnionFind {
    private:
        int* parent;
        int* rank;
        int n;
    public:
        UnionFind(int n_) : n(n_) {
            parent = new int[n];
            rank = new int[n];
            for(int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        ~UnionFind() {
            delete[] parent;
            delete[] rank;
        }
        int find(int x) {
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        void unite(int x, int y) {
            int rx = find(x);
            int ry = find(y);
            if(rx != ry) {
                if(rank[rx] < rank[ry]) {
                    parent[rx] = ry;
                } else if(rank[rx] > rank[ry]) {
                    parent[ry] = rx;
                } else {
                    parent[ry] = rx;
                    rank[rx]++;
                }
            }
        }
    };

    // Prim
    Graph Algorithms::prim(const Graph& g) {
        int n = g.getNumVertices();
        Graph mst(n);

        bool* inMST = new bool[n];
        int* dist = new int[n];
        int* parent = new int[n];

        for(int i = 0; i < n; i++) {
            inMST[i] = false;
            dist[i] = std::numeric_limits<int>::max();
            parent[i] = -1;
        }

        // Start from vertex 0
        dist[0] = 0;
        ArrayMinPriorityQueue pq(n*2);
        pq.push(0, 0);

        while(!pq.isEmpty()) {
            PQItem item = pq.pop();
            int u = item.vertex;
            if(u == -1) break;
            if(inMST[u]) continue;
            inMST[u] = true;

            int sizeAdj = g.getAdjSize(u);
            Edge* edges = g.getAdjList(u);
            for(int i = 0; i < sizeAdj; i++) {
                int v = edges[i].destination;
                int w = edges[i].weight;
                if(!inMST[v] && w < dist[v]) {
                    dist[v] = w;
                    parent[v] = u;
                    if(!pq.contains(v)) {
                        pq.push(v, w);
                    } else {
                        pq.decreaseKey(v, w);
                    }
                }
            }
        }

        // Build MST
        for(int i = 1; i < n; i++) {
            if(parent[i] != -1) {
                mst.addEdge(parent[i], i, dist[i]);
            }
        }

        delete[] inMST;
        delete[] dist;
        delete[] parent;
        return mst;
    }

    // Kruskal
    Graph Algorithms::kruskal(const Graph& g) {
        int n = g.getNumVertices();
        Graph mst(n);
        UnionFind uf(n);

        // Count total edges (each edge appears twice in an undirected graph so we divide by 2)
        int totalEdges = 0;
        for(int i = 0; i < n; i++) {
            totalEdges += g.getAdjSize(i);
        }
        int uniqueEdges = totalEdges / 2;

        struct E {
            int u;
            int v;
            int w;
        };
        E* edgesArr = new E[uniqueEdges];

        int idx = 0;
        for(int u = 0; u < n; u++) {
            int adjSize = g.getAdjSize(u);
            Edge* edges = g.getAdjList(u);
            for(int i = 0; i < adjSize; i++) {
                int v = edges[i].destination;
                int w = edges[i].weight;
                if(v > u) {
                    edgesArr[idx].u = u;
                    edgesArr[idx].v = v;
                    edgesArr[idx].w = w;
                    idx++;
                }
            }
        }

        // bubble sort by w (high runtime but in the assignment requirements we were said that runtime efficiency doesn't matter)
        for(int i = 0; i < uniqueEdges - 1; i++) {
            for(int j = i + 1; j < uniqueEdges; j++) {
                if(edgesArr[j].w < edgesArr[i].w) {
                    E temp = edgesArr[i];
                    edgesArr[i] = edgesArr[j];
                    edgesArr[j] = temp;
                }
            }
        }

        // build MST
        for(int i = 0; i < uniqueEdges; i++) {
            int u = edgesArr[i].u;
            int v = edgesArr[i].v;
            int w = edgesArr[i].w;
            if(uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                mst.addEdge(u, v, w);
            }
        }

        delete[] edgesArr;
        return mst;
    }

} // namespace graph
