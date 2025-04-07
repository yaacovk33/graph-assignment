// email: yaacovkrawiec@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.hpp"
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"
#include <stdexcept>

using namespace graph;

// A helper function to check the adjacency of an undirected edge
static bool hasEdge(const Graph& g, int u, int v, int weight = -1) {
    // Returns true if g has an edge u->v. If weight != -1, also check the weight.
    if(u < 0 || u >= g.getNumVertices() || v < 0 || v >= g.getNumVertices()) {
        return false;
    }
    int sizeAdj = g.getAdjSize(u);
    Edge* edges = g.getAdjList(u);
    for(int i = 0; i < sizeAdj; i++) {
        if(edges[i].destination == v) {
            if(weight == -1 || edges[i].weight == weight) {
                return true;
            }
        }
    }
    return false;
}

// ================ TEST CASES ================
TEST_CASE("Graph basic functionality") {
    Graph g(4);
    CHECK(g.getNumVertices() == 4);

    // Initially no edges
    for(int i = 0; i < 4; i++) {
        CHECK(g.getAdjSize(i) == 0);
    }

    // addEdge
    g.addEdge(0,1,5);
    CHECK(hasEdge(g, 0, 1, 5));
    CHECK(hasEdge(g, 1, 0, 5));
    CHECK(g.getAdjSize(0) == 1);
    CHECK(g.getAdjSize(1) == 1);

    // add more edges
    g.addEdge(1,2,2);
    g.addEdge(2,3,7);
    CHECK(hasEdge(g, 1, 2, 2));
    CHECK(hasEdge(g, 2, 3, 7));
    CHECK(g.getAdjSize(1) == 2);
    CHECK(g.getAdjSize(2) == 2);

    // removeEdge
    g.removeEdge(1,2);
    CHECK_FALSE(hasEdge(g, 1, 2));
    CHECK_FALSE(hasEdge(g, 2, 1));
    CHECK(g.getAdjSize(1) == 1);
    CHECK(g.getAdjSize(2) == 1);

    // removeEdge - should throw if doesn't exist
    CHECK_THROWS(g.removeEdge(1,2));
}

TEST_CASE("Graph removeEdge on invalid vertices") {
    Graph g(3);
    g.addEdge(0,1,10);
    CHECK(hasEdge(g,0,1,10));

    // out of range
    CHECK_THROWS(g.removeEdge(4,1));
    CHECK_THROWS(g.removeEdge(-1,0));
}

TEST_CASE("BFS on a small connected graph") {
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(1,2,1);
    g.addEdge(2,3,1);

    Graph bfsTree = Algorithms::bfs(g, 0);
    // BFS from 0 => it should explore 1, then 2, then 3
    // BFS tree edges: (0-1), (1-2), (2-3)
    CHECK(hasEdge(bfsTree, 0, 1));
    CHECK(hasEdge(bfsTree, 1, 2));
    CHECK(hasEdge(bfsTree, 2, 3));
    CHECK_FALSE(hasEdge(bfsTree, 0, 2));
    CHECK_FALSE(hasEdge(bfsTree, 1, 3));
}

TEST_CASE("BFS on disconnected graph") {
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(1,2);
    // vertices 3 and 4 are isolated from 0,1,2

    Graph bfsTree = Algorithms::bfs(g, 0);
    // BFS will only visit 0,1,2. So BFS tree edges: (0-1), (1-2)
    CHECK(hasEdge(bfsTree, 0,1));
    CHECK(hasEdge(bfsTree, 1,2));
    CHECK_FALSE(hasEdge(bfsTree, 3,4));
    // BFS tree won't have edges for 3 and 4
    CHECK(bfsTree.getAdjSize(3) == 0);
    CHECK(bfsTree.getAdjSize(4) == 0);
}

TEST_CASE("DFS check") {
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);

    Graph dfsTree = Algorithms::dfs(g, 0);
    // A DFS from 0 in a chain 0-1-2-3 => edges: (0-1), (1-2), (2-3)
    CHECK(hasEdge(dfsTree,0,1));
    CHECK(hasEdge(dfsTree,1,2));
    CHECK(hasEdge(dfsTree,2,3));
    CHECK(dfsTree.getAdjSize(0) == 1);
    CHECK(dfsTree.getAdjSize(1) == 2);
    CHECK(dfsTree.getAdjSize(2) == 2);
    CHECK(dfsTree.getAdjSize(3) == 1);
}

TEST_CASE("Dijkstra on a small graph with positive edges") {
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(0,2,2);
    g.addEdge(0,3,3);

    Graph dTree = Algorithms::dijkstra(g, 0);
    // In shortest paths from 0: 
    //  0->1 (weight 1)
    //  0->2 (weight 2)
    //  0->3 (weight 3)
    // So the tree should have edges (0-1), (0-2), (0-3)
    CHECK(hasEdge(dTree,0,1,1));
    CHECK(hasEdge(dTree,0,2,2));
    CHECK(hasEdge(dTree,0,3,3));

    // Check that there's no direct edge 1->2, 2->3, etc.
    CHECK_FALSE(hasEdge(dTree,1,2));
    CHECK_FALSE(hasEdge(dTree,2,3));
}

TEST_CASE("Dijkstra negative edges => throw exception") {
    Graph g(3);
    g.addEdge(0,1,5);
    g.addEdge(1,2,-1); // negative

    // We expect an exception
    CHECK_THROWS_AS(Algorithms::dijkstra(g,0), const char*);
}

TEST_CASE("Prim MST basic") {
    Graph g(4);
    // Let's form a square: 0-1, 1-2, 2-3, 3-0
    // and a diagonal 0-2 with bigger weight
    g.addEdge(0,1,1);
    g.addEdge(1,2,2);
    g.addEdge(2,3,3);
    g.addEdge(3,0,4);
    g.addEdge(0,2,10);

    Graph mst = Algorithms::prim(g);
    // MST on this square (with minimal edges) 
    // probably picks: (0-1,w=1), (1-2,w=2), (2-3,w=3)
    // total edges = 3 for MST in a 4-vertex graph
    // check if they exist
    CHECK(hasEdge(mst, 0,1,1));
    CHECK(hasEdge(mst, 1,2,2));
    CHECK(hasEdge(mst, 2,3,3));

    // check that (0,3) or (0,2) are not in MST
    CHECK_FALSE(hasEdge(mst, 0,3));
    CHECK_FALSE(hasEdge(mst, 0,2));
    // MST should have exactly 3 edges in an undirected sense
    int edgesCount = 0;
    for(int v=0; v<4; v++){
        edgesCount += mst.getAdjSize(v);
    }
    // each edge counted twice => total is 3 * 2 = 6
    CHECK(edgesCount == 6);
}

TEST_CASE("Kruskal MST basic") {
    Graph g(4);
    // same shape as in Prim test
    g.addEdge(0,1,1);
    g.addEdge(1,2,2);
    g.addEdge(2,3,3);
    g.addEdge(3,0,4);
    g.addEdge(0,2,10);

    Graph mst = Algorithms::kruskal(g);
    // MST: (0-1,w=1), (1-2,w=2), (2-3,w=3)

    CHECK(hasEdge(mst, 0,1,1));
    CHECK(hasEdge(mst, 1,2,2));
    CHECK(hasEdge(mst, 2,3,3));
    CHECK_FALSE(hasEdge(mst, 0,3));
    CHECK_FALSE(hasEdge(mst, 0,2));

    // check number of edges again
    int edgesCount = 0;
    for(int v=0; v<4; v++){
        edgesCount += mst.getAdjSize(v);
    }
    // each edge is counted twice (undirected)
    CHECK(edgesCount == 6);
}

int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run();
    return res;
}