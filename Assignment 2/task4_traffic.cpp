#include "NetworkGraph.h"

const int INF = 1e9;

int getRouteCost(NetworkGraph& g, int src, int dest, bool applyTraffic) {
    vector<int> dist(g.cities, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : g.adj[u]) {
            int v = edge.first, weight = edge.second;
            if (applyTraffic) weight *= (1.0 + ((u + v) % 3)); 

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[dest];
}

int main() {
    NetworkGraph graph(500);
    int src = 10, dest = 450;

    int normal = getRouteCost(graph, src, dest, false);
    int traffic = getRouteCost(graph, src, dest, true);

    cout << "Normal Route Distance = " << normal << " km\n";
    cout << "Traffic Route Distance = " << traffic << " km\n";
    cout << "Delay = " << ((float)(traffic - normal) / normal) * 100.0 << "%\n";

    return 0;
}