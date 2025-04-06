// email: yaacovkrawiec@gmail.com
# Graph Assignment

**Author**: [yaacovk33]  
**Email**: [yaacovkrawiec@gmail.com]


## Overview

This project implements an **undirected simple graph** (no multiple edges, no self-loops) using adjacency lists, and **does not use any standard library containers** (`std::vector`, `std::queue`, etc.).  

Five classic graph algorithms are provided:

1. **BFS** (Breadth-First Search)  
2. **DFS** (Depth-First Search)  
3. **Dijkstra** (Shortest paths – throws an exception if a negative edge is found)  
4. **Prim** (Minimum Spanning Tree)  
5. **Kruskal** (Minimum Spanning Tree, using union-find)

---

### Key Points

- **Graph class**  
  - Stores adjacency lists in raw arrays.  
  - Methods: `addEdge(source, dest, weight=1)`, `removeEdge(source, dest)`, `printGraph()`.  
  - No loops, no multiple edges.  
  - Throws an exception if an edge to remove does not exist.

- **Algorithms class**  
  - **bfs**: returns a BFS tree from a starting vertex.  
  - **dfs**: returns a DFS tree from a starting vertex.  
  - **dijkstra**: returns a shortest-path tree; throws if a negative edge is detected anywhere.  
  - **prim**: builds a minimum spanning tree (MST) using a naive array-based priority queue.  
  - **kruskal**: builds an MST using union-find.

- **No STL containers** used.  
- **Data structures** for queue, priority queue, and union-find are implemented manually.

---

## How to Build and Run

1. **Compile the main demo**:
   -> bash terminal
   make Main
   ./Main

   The program will print:

   A first example with no negative edges (BFS, DFS, Dijkstra, Prim, Kruskal).

   A second example with negative edges, which will trigger an exception when calling Dijkstra

2. **Compile and Run the tests**:
   -> bash terminal
   make test
   
   Unit tests use doctest and will indicate any failures.

3. **Memory check through Valgrind**:
   -> bash terminal
   make valgrind

   Runs valgrind --leak-check=full ./Main.

4. **Clean**:
   -> bash terminal
   make clean

   Will remove all the .o files and executabls 


Thanks for reading my README file!
