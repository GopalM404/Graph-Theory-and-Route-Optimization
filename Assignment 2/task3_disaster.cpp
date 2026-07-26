#include "NetworkGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void dijkstra(NetworkGraph& g, int src, int dest, set<int>& badCities, set<pair<int, int>>& badRoads) {
    vector<int> dist(g.cities, INF), parent(g.cities, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == dest) break;

        for (auto& edge : g.adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (badCities.count(v)) continue;

            pair<int, int> road = {min(u, v), max(u, v)};
            if (badRoads.count(road)) continue;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No valid route available after disaster.\n";
    } else {
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
        cout << "Distance = " << dist[dest] << " km | Path: ";
        for (int i = path.size() - 1; i >= 0; i--) cout << path[i] << (i == 0 ? "" : " -> ");
        cout << "\n";
    }
}

int main() {
    NetworkGraph graph(500);
    int src, dest;
    int numBadCities = 0, numBadRoads = 0;
    set<int> badCities;
    set<pair<int, int>> badRoads;

    cout << "Enter Source City: ";
    cin >> src;
    
    cout << "Enter Destination City: ";
    cin >> dest;

    cout << "How many cities to block? (Max 3): ";
    cin >> numBadCities;
    numBadCities = min(3, max(0, numBadCities)); 
    for (int i = 1; i <= numBadCities; i++) {
        int city; 
        cout << "Enter blocked city " << i << " ID: ";
        cin >> city;
        badCities.insert(city);
    }

    cout << "How many roads to block? (Max 3): ";
    cin >> numBadRoads;
    numBadRoads = min(3, max(0, numBadRoads)); 
    for (int i = 1; i <= numBadRoads; i++) {
        int u, v; 
        cout << "Enter blocked road " << i << " (format: city1 city2): ";
        cin >> u >> v;
        badRoads.insert({min(u, v), max(u, v)});
    }

    cout << "\nPath Analysis:\n";
    dijkstra(graph, src, dest, badCities, badRoads);

    return 0;
}
