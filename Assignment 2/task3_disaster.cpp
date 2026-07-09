#include "NetworkGraph.h"

const int INF = 1e9;

void dijkstra(NetworkGraph& g, int src, int dest, int avoidNode) {
    vector<int> dist(g.cities, INF), parent(g.cities, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == dest) break;

        for (auto& edge : g.adj[u]) {
            int v = edge.first, weight = edge.second;
            if (v == avoidNode) continue;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INF) cout << "No valid route available.\n";
    else {
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
        cout << "Distance = " << dist[dest] << " km | Path: ";
        for (int i = path.size() - 1; i >= 0; i--) cout << path[i] << (i == 0 ? "" : " -> ");
        cout << "\n";
    }
}

int main() {
    NetworkGraph graph(500);
    int srcA = 12, srcB = 44, destD = 203, disasterNode = 55; 

    cout << "Source A Path: ";
    dijkstra(graph, srcA, destD, disasterNode);
    cout << "Source B Path: ";
    dijkstra(graph, srcB, destD, disasterNode);

    return 0;
}