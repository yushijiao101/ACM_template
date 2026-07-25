#include <bits/stdc++.h>
using namespace std;

#include "../template/graph/dijkstra.cpp"

int main() {
    Dijkstra graph(6);
    graph.add_edge(1, 2, 10);
    graph.add_edge(1, 2, 3);   // parallel edge
    graph.add_edge(2, 2, 0);   // self-loop
    graph.add_edge(2, 3, 4);
    graph.add_edge(1, 3, 20);
    graph.add_edge(3, 4, 5);
    graph.add_edge(1, 5, 3000000000LL);

    vector<long long> distance = graph.shortest_paths(1);
    assert(distance[1] == 0);
    assert(distance[2] == 3);
    assert(distance[3] == 7);
    assert(distance[4] == 12);
    assert(distance[5] == 3000000000LL);
    assert(distance[6] == Dijkstra::INF);
    return 0;
}
