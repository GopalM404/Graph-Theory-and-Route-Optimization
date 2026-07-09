#include "NetworkGraph.h"

int main() {
    NetworkGraph graph(500);
    srand(time(0)); 
    int sourceNode = rand() % graph.cities;
    
    vector<int> minDist(graph.cities, INT_MAX);
    minDist[sourceNode] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, sourceNode});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist > minDist[node]) continue;

        for (auto it : graph.adj[node]) {
            if (it.second + dist < minDist[it.first]) {
                minDist[it.first] = it.second + dist;
                pq.push({minDist[it.first], it.first});
            }
        }
    }

    cout << "Shortest distance from source city -> " << sourceNode << " to reachable cities :\n";
    for (int i = 0; i < graph.cities; i++) {
        if (i != sourceNode && minDist[i] != INT_MAX) {
            cout << "{" << i << "," << minDist[i] << "} ";
        }
    }
    
    cout << "\n\nThe unreachable cities are : {";
    for (int i = 0; i < graph.cities; i++) {
        if (minDist[i] == INT_MAX) cout << i << ",";
    }
    cout << "}\n\n";
    
    int maxPath = 0, maxPathCity = sourceNode;
    for (int i = 0; i < graph.cities; i++) {
        if (minDist[i] != INT_MAX && minDist[i] > maxPath) {
            maxPath = minDist[i];
            maxPathCity = i;
        }
    }
    cout << "City with maximum shortest path from source city is : " << maxPathCity << "\n";

    return 0;
}