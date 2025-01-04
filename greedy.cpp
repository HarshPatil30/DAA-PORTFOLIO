#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_NODES 5

struct Node {
    int id;
    int time;
    bool operator>(const Node& other) const {
        return time > other.time;
    }
};

void findShortestPathWithTraffic(int graph[MAX_NODES][MAX_NODES], int trafficMatrix[MAX_NODES][MAX_NODES], int n, int start, int end, const string intersectionNames[]) {
    vector<int> distance(n, INT_MAX);
    vector<int> previous(n, -1);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    distance[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        int u = pq.top().id;
        pq.pop();

        for (int v = 0; v < n; v++) {
            if (graph[u][v] == -1 || trafficMatrix[u][v] == -1 || u == v) continue;

            int newTime = distance[u] + graph[u][v] + trafficMatrix[u][v];

            if (newTime < distance[v]) {
                distance[v] = newTime;
                previous[v] = u;
                pq.push({v, newTime});
            }
        }
    }

    cout << "Shortest path from " << intersectionNames[start] << " to " << intersectionNames[end] << " considering traffic levels:" << endl;
    if (distance[end] == INT_MAX) {
        cout << "No route available." << endl;
    } else {
        cout << "Total distance: " << distance[end] << " kilometer" << endl;
        cout << "Path: ";
        vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++) {
            cout << intersectionNames[path[i]] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }
}

int main() {
    string intersectionNames[MAX_NODES] = {
        "City Center",
        "Restaurant",
        "park",
        "Hospital",
        "Highway"
    };

    int graph[MAX_NODES][MAX_NODES] = {
        {-1, 10, 5, 3, 2},  
        {10, -1, 2, 1, 4},  
        {5, 2, -1, 9, 2},   
        {-1, 1, 9, -1, 4},  
        {2, 4, 2, 4, -1},   
    };

    int trafficMatrix[MAX_NODES][MAX_NODES];
    cout << "Enter the traffic conditions between intersections (0: No traffic, 10: Road blocked, -1: No road):" << endl;

    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            if (graph[i][j] == -1) {
                trafficMatrix[i][j] = -1; 
            } else {
                cout << "Traffic from " << intersectionNames[i] << " to " << intersectionNames[j] << ": ";
                cin >> trafficMatrix[i][j];
            }
        }
    }

    string startName, endName;
    int startNode = -1, endNode = -1;

    cout << "Enter the start intersection name: ";
    cin.ignore();
    getline(cin, startName);

    cout << "Enter the end intersection name: ";
    getline(cin, endName);

    for (int i = 0; i < MAX_NODES; i++) {
        if (intersectionNames[i] == startName) startNode = i;
        if (intersectionNames[i] == endName) endNode = i;
    }

    if (startNode == -1 || endNode == -1) {
        cout << "Invalid intersection names provided." << endl;
        return 1;
    }

    findShortestPathWithTraffic(graph, trafficMatrix, MAX_NODES, startNode, endNode, intersectionNames);

    return 0;
}
