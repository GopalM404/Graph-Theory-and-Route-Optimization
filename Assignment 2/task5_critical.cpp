#include "NetworkGraph.h"

int countComponents(NetworkGraph& g, int avoidNode) {
    vector<bool> visited(g.cities, false);
    int components = 0;

    for (int i = 0; i < g.cities; i++) {
        if (i == avoidNode || visited[i]) continue;
        components++;
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& edge : g.adj[u]) {
                if (edge.first != avoidNode && !visited[edge.first]) {
                    visited[edge.first] = true;
                    q.push(edge.first);
                }
            }
        }
    }
    return components;
}

int main() {
    NetworkGraph graph(500);
    int maxComponents = 0, criticalCity = -1;

    for (int i = 0; i < graph.cities; i++) {
        int comp = countComponents(graph, i);
        if (comp > maxComponents) {
            maxComponents = comp;
            criticalCity = i;
        }
    }

    cout << "Most Critical City: " << criticalCity << "\n";
    cout << "Disconnected Components Created: " << maxComponents << "\n";

    return 0;
}