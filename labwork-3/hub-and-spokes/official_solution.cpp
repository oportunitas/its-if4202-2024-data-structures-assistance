/**
* ╭╴official_solution.c
* | GNU C11
* ╰--> official solution for ITS IF4202 2024's labwork 3 problem: 
*      'Hub-and-Spokes'
* ╭╴created    : 25 May 2024
* ╰--> @oportunitas
**/

#include <bits/stdc++.h>
using namespace std;

#define lli int64_t
const lli max_nodes = 100005;

struct network {
    lli head[max_nodes], size[max_nodes];

    // Initialize network
    network() {
        memset(head, -1, sizeof(head));
        fill(size, size + max_nodes, 1);
    }

    // Find the head of a set
    lli find_head(lli nd) {
        while (head[nd] != -1) {
            nd = head[nd];
        }
        return nd;
    }

    // Merge 2 disjoint sets
    bool merge(lli node_1, lli node_2) {
        // Find the head of both sets
        lli set_x = find_head(node_1);
        lli set_y = find_head(node_2);

        // Join the 2 sets by setting the head of the bigger set to be the 
        // head of the smaller set
        if (set_x != set_y) {
            if (size[set_x] < size[set_y]) {
                swap(set_x, set_y);
            }
            size[set_x] += size[set_y];
            head[set_y] = set_x;
        }

        // Return false if the 2 sets turns out to be the same
        // (no need to join/join fail)
        return set_x != set_y;
    }

    // Get the node count of a set
    lli get_size(lli nd) {
        lli root = find_head(nd);
        return size[root];
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    lli n, m; cin >> n >> m;
    vector<pair<lli, pair<lli, lli>>> edges;

    // Insert nodes and edges and sort the edges by distance ascendingly
    for (lli i = 1; i <= m; i++) {
        lli u, v, w; 
        cin >> u >> v >> w;
        edges.push_back({ w, {u , v} });
    }
    sort(edges.begin(), edges.end());
    
    network original_route;
    vector<pair<lli, pair<lli, lli>>> best_route;

    // Perform Minimum Spanning Tree creation using Kruskal's algorithm
    for (auto edge : edges) {
        lli weight = edge.first;
        lli u = edge.second.first;
        lli v = edge.second.second;

        // If the 2 nodes are from different sets, add their connection
        // to the best routes list
        if (original_route.merge(u, v)) {
            best_route.push_back({ weight,{u , v} });
        }

        if (best_route.size() == n - 1) {
            break;
        }
    }

    // Iterate through and print the total weight of the best route
    lli ans = 0;
    for (auto edge : best_route) {
        lli weight = edge.first;
        ans += weight;
    } cout << ans << endl;

    return 0;
}