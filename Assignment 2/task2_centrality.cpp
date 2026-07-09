#include "NetworkGraph.h"

int main() {
    NetworkGraph graph(500);
    vector<pair<int, int>> centrality; 

    for (int i = 0; i < graph.cities; i++) {
        centrality.push_back({graph.adj[i].size(), i});
    }

    sort(centrality.rbegin(), centrality.rend());

    for (int i = 0; i < 10; i++) {
        cout << "Rank " << i + 1 << " -> City " << centrality[i].second 
             << " -> Degree " << centrality[i].first << "\n";
    }

    cout << "\nTop Development Candidates:\n";
    cout << "* Airport: City " << centrality[0].second << "\n";
    cout << "* Logistics Hub: City " << centrality[1].second << "\n";
    cout << "* Railway Junction: City " << centrality[2].second << "\n";

    return 0;
}