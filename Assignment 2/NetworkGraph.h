#ifndef NETWORK_GRAPH_H
#define NETWORK_GRAPH_H

#include <bits/stdc++.h>
using namespace std;

class NetworkGraph {
public:
    int cities;
    vector<vector<pair<int, int>>> adj;

    NetworkGraph(int n = 500) {
        cities = n;
        adj.resize(cities);
        srand(42); 
        
        for (int i = 0; i < cities; i++) {
            for (int j = i + 1; j < cities; j++) {
                if (rand() % 200 < 1) { 
                    int distance = rand() % 44 + 6;
                    adj[i].push_back({j, distance});
                    adj[j].push_back({i, distance});
                }
            }
        }
    }
};

#endif