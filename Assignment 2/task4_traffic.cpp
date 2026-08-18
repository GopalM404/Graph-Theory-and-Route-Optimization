#include "NetworkGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

const int INF = 1e9;

vector<vector<int>> trafficState(500, vector<int>(500, -1));

int nextTrafficState(int state) {
    int r = rand() % 100;

    if (state == 0) {
        if (r < 70) return 0;
        if (r < 90) return 1;
        return 2;
    }

    if (state == 1) {
        if (r < 20) return 0;
        if (r < 80) return 1;
        return 2;
    }

    if (r < 10) return 0;
    if (r < 40) return 1;
    return 2;
}

void initializeTraffic(NetworkGraph& graph) {
    for (int u = 0; u < graph.cities; u++) {
        for (auto edge : graph.adj[u]) {
            int v = edge.first;

            if (trafficState[u][v] == -1) {
                int state = rand() % 3;

                trafficState[u][v] = state;
                trafficState[v][u] = state;
            }
        }
    }
}

void updateTraffic(NetworkGraph& graph) {
    for (int u = 0; u < graph.cities; u++) {
        for (auto edge : graph.adj[u]) {
            int v = edge.first;

            if (u < v) {
                int newState = nextTrafficState(trafficState[u][v]);

                trafficState[u][v] = newState;
                trafficState[v][u] = newState;
            }
        }
    }
}

double dijkstra(NetworkGraph& graph, int src, int dest, bool traffic) {
    vector<double> dist(graph.cities, INF);

    priority_queue<
        pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>
    > pq;

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

            if (traffic) {
                int state = trafficState[u][v];

                if (state == 1)
                    weight *= 1.5;
                else if (state == 2)
                    weight *= 2.0;
            }

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return INF;
}

int main() {
    srand(time(0));

    NetworkGraph graph(500);

    int src, dest;

    cout << "Enter source city: ";
    cin >> src;

    cout << "Enter destination city: ";
    cin >> dest;

    double originalCost = dijkstra(graph, src, dest, false);

    initializeTraffic(graph);

    updateTraffic(graph);

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
