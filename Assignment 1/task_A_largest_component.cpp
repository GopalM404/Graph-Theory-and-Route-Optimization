#include "NetworkGraph.h"

int main() {
    NetworkGraph graph(500);
    vector<int> vis(graph.cities, 0);
    int maxGrp = 0;
    vector<int> maxCities;

    for (int i = 0; i < graph.cities; i++) {
        if (vis[i] == 0) {
            int currMax = 0;
            vector<int> currCities;
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            currCities.push_back(i);
            currMax++;

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (auto k : graph.adj[node]) {
                    if (vis[k.first] == 0) {
                        q.push(k.first);
                        vis[k.first] = 1;
                        currMax++;
                        currCities.push_back(k.first);
                    }
                }
            }
            if (currMax > maxGrp) {
                maxGrp = currMax;
                maxCities = currCities;
            }
        }
    }
   
    cout << "Total no. of cities in the largest connected component : " << maxGrp << "\n";
    cout << "The cities in the group are : {";
    for (size_t z = 0; z < maxCities.size(); z++) {
        cout << maxCities[z] << (z != maxCities.size() - 1 ? "," : "");
    }
    cout << "}\n";
    return 0;
}