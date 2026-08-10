#include "NetworkGraph.h"

int timer = 0;

// DFS used by Tarjan's algorithm
void dfs(int u, int parent, NetworkGraph& graph,
         vector<int>& disc, vector<int>& low,
         vector<int>& impact) {

    disc[u] = low[u] = timer++;
    int children = 0;

    for (auto edge : graph.adj[u]) {

        int v = edge.first;

        // Don't go back through the same edge we came from
        if (v == parent)
            continue;

        // If this city has not been visited yet
        if (disc[v] == -1) {

            children++;
            dfs(v, u, graph, disc, low, impact);

            // Update the earliest city reachable from u
            low[u] = min(low[u], low[v]);

            /*
            If v's subtree cannot reach above u,
            then removing u separates that subtree
            */
            if (parent != -1 && low[v] >= disc[u])
                impact[u]++;
        }

        // v was already visited, so this is a back edge
        else {
            low[u] = min(low[u], disc[v]);
        }
    }

    /*
    For the DFS root, every child represents
    a separate component if the root is removed
    */
    if (parent == -1)
        impact[u] = children - 1;
}

int main() {

    NetworkGraph graph(500);

    vector<int> disc(graph.cities, -1);
    vector<int> low(graph.cities, -1);
    vector<int> impact(graph.cities, 0);

    // Run DFS for every component of the graph
    for (int i = 0; i < graph.cities; i++) {
        if (disc[i] == -1)
            dfs(i, -1, graph, disc, low, impact);
    }

    int criticalCity = 0;

    // Find the city whose removal causes maximum separation
    for (int i = 1; i < graph.cities; i++) {
        if (impact[i] > impact[criticalCity])
            criticalCity = i;
    }

    cout << "Most Critical City: " << criticalCity << "\n";
    cout << "Disconnected Parts Created: "
         << impact[criticalCity] + 1 << "\n";

    return 0;
}
