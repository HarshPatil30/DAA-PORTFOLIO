#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_NODES 5

void bellmanFord(int graph[MAX_NODES][MAX_NODES], int traffic[MAX_NODES][MAX_NODES], int start, int end, int n, vector<int> &shortestPath, bool includeTraffic) {
    int distance[MAX_NODES];
    int previous[MAX_NODES];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }
    distance[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (graph[u][v] != -1) {
                    int effectiveWeight = graph[u][v];
                    if (includeTraffic && traffic[u][v] != -1) {
                        effectiveWeight += traffic[u][v];
                    }
                    // Skip blocked roads (traffic value = -1)
                    if (traffic[u][v] == -1) continue;
                    if (distance[u] != INT_MAX && distance[u] + effectiveWeight < distance[v]) {
                        distance[v] = distance[u] + effectiveWeight;
                        previous[v] = u;
                    }
                }
            }
        }
    }

    cout << "Shortest travel time from intersection " << start << " to intersection " << end << ":\n";
    if (distance[end] == INT_MAX) {
        cout << "No route available\n";
    } else {
        cout << "Distance: " << distance[end] << " kilometers\n";
        cout << "Path: ";
        shortestPath.clear();
        for (int node = end; node != -1; node = previous[node]) {
            shortestPath.push_back(node);
        }
        reverse(shortestPath.begin(), shortestPath.end());
        for (size_t i = 0; i < shortestPath.size(); i++) {
            cout << shortestPath[i];
            if (i < shortestPath.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

void updateTrafficOnPath(int traffic[MAX_NODES][MAX_NODES], const vector<int> &shortestPath) {
    cout << "\nProvide traffic values for the edges in the shortest path:\n";
    for (size_t i = 0; i < shortestPath.size() - 1; i++) {
        int u = shortestPath[i];
        int v = shortestPath[i + 1];
        int newTraffic;
        cout << "Enter traffic weight for edge (" << u << " -> " << v << ") (-1 to block the road): ";
        cin >> newTraffic;
        traffic[u][v] = newTraffic;
        traffic[v][u] = newTraffic;
        cout << "Updated traffic for edge (" << u << " -> " << v << ") is now " << newTraffic << ".\n";
    }
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 10, 5, -1, 2},
        {10, 0, 2, 1, -1},
        {5, 2, 0, 9, 2},
        {-1, 1, 9, 0, 4},
        {2, -1, 2, 4, 0},
    };

    int traffic[MAX_NODES][MAX_NODES] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    };

    int startNode, endNode;
    cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> endNode;

    vector<int> shortestPath;

    cout << "\nCalculating shortest path without traffic...\n";
    bellmanFord(graph, traffic, startNode, endNode, MAX_NODES, shortestPath, false);

    char choice;
    cout << "\nDo you want to update traffic conditions for the shortest path? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        updateTrafficOnPath(traffic, shortestPath);

        cout << "\nRecalculating shortest path with updated traffic...\n";
        bellmanFord(graph, traffic, startNode, endNode, MAX_NODES, shortestPath, true);
    }

    return 0;
}
