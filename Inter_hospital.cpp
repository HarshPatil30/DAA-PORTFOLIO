#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

const int INF = INT_MAX;

class HospitalNetwork {
private:
    int numHospitals;
    vector<vector<int>> adjMatrix;

public:
    HospitalNetwork(int n) {
        numHospitals = n;
        adjMatrix.resize(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            adjMatrix[i][i] = 0; // No cost to stay within the same hospital
        }
    }

    void addConnection(int u, int v, int travelTime) {
        adjMatrix[u][v] = travelTime;
        adjMatrix[v][u] = travelTime; // Assuming undirected graph (bi-directional travel)
    }

    void dijkstra(int start) {
        vector<int> dist(numHospitals, INF);
        vector<bool> visited(numHospitals, false);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (visited[u]) continue;

            visited[u] = true;

            for (int v = 0; v < numHospitals; v++) {
                if (!visited[v] && adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest travel times from Hospital " << start + 1 << " to other hospitals:" << endl;
        for (int i = 0; i < numHospitals; i++) {
            cout << "Hospital " << i + 1 << ": " << (dist[i] == INF ? "Unreachable" : to_string(dist[i])) << " minutes" << endl;
        }
    }
};

int main() {
    int n, m;
    cout << "Enter number of hospitals: ";
    cin >> n;
    HospitalNetwork network(n);

    cout << "Enter number of connections: ";
    cin >> m;

    cout << "Enter the connections (Hospital1, Hospital2, TravelTime in minutes):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, travelTime;
        cin >> u >> v >> travelTime;
        network.addConnection(u - 1, v - 1, travelTime);
    }

    int source;
    cout << "Enter the source hospital number: ";
    cin >> source;
    network.dijkstra(source - 1);

    return 0;
}
