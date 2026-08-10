#include "NetworkGraph.h"

#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

const int INF = 1e9;


// 0 = Low traffic
// 1 = Medium traffic
// 2 = High traffic
int nextTraffic(int current) {

    int r = rand() % 100;

    if (current == 0) {
        if (r < 70) return 0;
        if (r < 95) return 1;
        return 2;
    }

    if (current == 1) {
        if (r < 20) return 0;
        if (r < 80) return 1;
        return 2;
    }

    if (r < 5) return 0;
    if (r < 35) return 1;

    return 2;
}


// Returns road cost according to traffic
double getTrafficCost(int distance, int state) {

    if (state == 0)
        return distance;

    if (state == 1)
        return distance * 1.5;

    return distance * 2.0;
}


// Dijkstra for normal road distances
double normalDijkstra(NetworkGraph& graph, int src, int dest) {

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

        if (d > dist[u])
            continue;

        for (auto edge : graph.adj[u]) {

            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[dest];
}


// Dijkstra using traffic-adjusted road costs
double trafficDijkstra(NetworkGraph& graph, int src, int dest,
                       vector<vector<int>>& traffic) {

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

        if (d > dist[u])
            continue;

        for (auto edge : graph.adj[u]) {

            int v = edge.first;
            int distance = edge.second;

            double weight =
                getTrafficCost(distance, traffic[u][v]);

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

    vector<vector<int>> traffic(
        graph.cities,
        vector<int>(graph.cities, 0)
    );

    // Calculate next traffic state for every road
    for (int u = 0; u < graph.cities; u++) {

        for (auto edge : graph.adj[u]) {

            int v = edge.first;

            if (u < v) {

                int state = nextTraffic(traffic[u][v]);

                traffic[u][v] = state;
                traffic[v][u] = state;
            }
        }
    }

    int src, dest;

    cout << "Enter source city: ";
    cin >> src;

    cout << "Enter destination city: ";
    cin >> dest;

    double originalCost =
        normalDijkstra(graph, src, dest);

    double trafficCost =
        trafficDijkstra(graph, src, dest, traffic);

    if (originalCost == INF) {
        cout << "No route exists\n";
        return 0;
    }

    cout << "Original Cost: "
         << originalCost << "\n";

    cout << "Traffic Cost: "
         << trafficCost << "\n";

    double delay =
        ((trafficCost - originalCost) / originalCost) * 100;

    cout << "Delay: "
         << delay << "%\n";

    return 0;
}
