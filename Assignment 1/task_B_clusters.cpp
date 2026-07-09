#include "NetworkGraph.h"

int main() {
    NetworkGraph graph(500);
    vector<int> vis(graph.cities, 0);
    int maxGrp = 0, minGrp = INT_MAX, clusters = 0;
    vector<int> clusterSize;

    for (int i = 0; i < graph.cities; i++) {
        if (vis[i] == 0) {
            int currGrp = 0;
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            currGrp++;
            clusters++;

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (auto k : graph.adj[node]) {
                    if (vis[k.first] == 0) {
                        q.push(k.first);
                        vis[k.first] = 1;
                        currGrp++;
                    }
                }
            }
            if (currGrp > maxGrp) maxGrp = currGrp;
            if (currGrp < minGrp) minGrp = currGrp;
            clusterSize.push_back(currGrp);
        }
    }

    cout << "The total no. of connected components is : " << clusters << "\n";
    cout << "The size of each cluster is : {";
    for (size_t i = 0; i < clusterSize.size(); i++) {
        cout << clusterSize[i] << (i != clusterSize.size() - 1 ? "," : "");
    }
    cout << "}\n";
    cout << "Total no. of cities in largest connected component : " << maxGrp << "\n";
    cout << "Total no. of cities in smallest connected component : " << (minGrp == INT_MAX ? 0 : minGrp) << "\n";
    return 0;
}