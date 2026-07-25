/*
Algorithm: Dijkstra shortest paths with a binary heap
Purpose: Single-source shortest paths in a directed non-negative weighted graph.
Complexity: O((n + m) log n) time; O(n + m) space.
Indexing: 1-indexed, valid vertices are [1, n].
Requirements: Every edge weight is non-negative; reachable distances fit in long long.
Tested on: Not verified
Common mistakes: Using negative edges; int overflow; forgetting init between test cases.
Status: Unverified
*/

#include <bits/stdc++.h>
using namespace std;

struct Dijkstra {
    using Edge = pair<int, long long>;  // (to, weight)
    static constexpr long long INF = numeric_limits<long long>::max() / 4;

    int n = 0;
    vector<vector<Edge>> graph;

    Dijkstra() = default;
    explicit Dijkstra(int n) { init(n); }

    void init(int n_) {
        n = n_;
        graph.assign(n + 1, {});
    }

    // Parallel edges and self-loops are supported. Add both directions manually
    // for an undirected graph.
    void add_edge(int from, int to, long long weight) {
        graph[from].push_back({to, weight});
    }

    vector<long long> shortest_paths(int source) const {
        vector<long long> distance(n + 1, INF);
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> heap;

        distance[source] = 0;
        heap.push({0, source});

        while (!heap.empty()) {
            auto [current_distance, u] = heap.top();
            heap.pop();
            if (current_distance != distance[u]) continue;

            for (auto [v, weight] : graph[u]) {
                if (weight > INF - current_distance) continue;
                long long candidate = current_distance + weight;
                if (candidate < distance[v]) {
                    distance[v] = candidate;
                    heap.push({candidate, v});
                }
            }
        }
        return distance;
    }
};
