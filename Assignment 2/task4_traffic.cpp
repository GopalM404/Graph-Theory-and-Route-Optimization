#include "NetworkGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

const int INF = 1e9;

double dijkstra(NetworkGraph& graph, int src, int dest, bool traffic) {
    vector<double> dist(graph.cities, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        if (u == dest) return dist[u];

        for (auto edge : graph.adj[u]) {
            int v = edge.first;
            double weight = edge.second;

            if (traffic) weight *= (1 + (rand() % 3) * 0.5);

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return INF;
}

int main() {
    NetworkGraph graph(500);

    int src, dest;

    cout << "Enter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;

    double originalCost = dijkstra(graph, src, dest, false);
    double trafficCost = dijkstra(graph, src, dest, true);

    if (originalCost == INF) {
        cout << "No route exists\n";
        return 0;
    }

    cout << "Original Cost: " << originalCost << "\n";
    cout << "Traffic Cost: " << trafficCost << "\n";

    double delay = ((trafficCost - originalCost) / originalCost) * 100;
    cout << "Delay: " << delay << "%\n";

    return 0;
}
