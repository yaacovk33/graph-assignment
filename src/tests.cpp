// email: yaacovkrawiec@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"  // ou "../external/doctest.h"
#include "../include/Graph.h"
#include "../include/Algorithms.h"

using namespace graph;

TEST_CASE("Basic Graph tests") {
    Graph g(3);
    g.addEdge(0,1,5);
    g.addEdge(1,2,7);

    CHECK(g.getAdjSize(0) == 1);
    CHECK(g.getAdjSize(1) == 2);
    CHECK(g.getAdjSize(2) == 1);

    // removeEdge
    g.removeEdge(1,2);
    CHECK(g.getAdjSize(1) == 1);
    CHECK(g.getAdjSize(2) == 0);
}

TEST_CASE("BFS test") {
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);

    Graph bfsTree = Algorithms::bfs(g, 0);
    // BFS tree from 0 => edges: 0-1, 1-2, 2-3
    CHECK(bfsTree.getAdjSize(0) == 1);
    CHECK(bfsTree.getAdjSize(1) == 2);
    CHECK(bfsTree.getAdjSize(2) == 2);
    CHECK(bfsTree.getAdjSize(3) == 1);
}

int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run();
    return res;
}