#include "NetworkGraph.h"

struct GraphEdge {
    int u, v, weight;
    bool operator<(GraphEdge const& other) { return weight < other.weight; }
};

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n); rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) parent[root_i] = root_j;
            else if (rank[root_i] > rank[root_j]) parent[root_j] = root_i;
            else { parent[root_j] = root_i; rank[root_i]++; }
        }
    }
};

int main() {
    NetworkGraph graph(500);
    vector<GraphEdge> edges, result;
    int originalCost = 0, mstCost = 0;

    for (int i = 0; i < graph.cities; i++) {
        for (auto& edge : graph.adj[i]) {
            if (i < edge.first) {
                edges.push_back({i, edge.first, edge.second});
                originalCost += edge.second;
            }
        }
    }

    sort(edges.begin(), edges.end());
    DSU dsu(graph.cities);

    for (GraphEdge e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            result.push_back(e);
            mstCost += e.weight;
        }
    }

    cout << "Original Cost = " << originalCost << "\nMST Cost = " << mstCost << "\n";
    cout << "Cost Saved = " << ((float)(originalCost - mstCost) / originalCost) * 100.0 << " %\n\n";
    cout << "Selected Roads:\n";
    for (int i = 0; i < min(5, (int)result.size()); i++) cout << "(" << result[i].u << "," << result[i].v << ")\n";
    cout << "...\n[All " << result.size() << " structural spans successfully written]\n";
    return 0;
}