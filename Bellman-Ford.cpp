#include <iostream>
#include <climits>
#include <vector>

using namespace std;

#define MAX_NODES 5

void bellmanFord(int graph[MAX_NODES][MAX_NODES], int start, int end, int n) {
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
                if (graph[u][v] != -1 && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                    previous[v] = u;
                }
            }
        }
    }

    cout << "Shortest travel time from intersection " << start << " to intersection " << end << ":\n";
    if (distance[end] == INT_MAX) {
        cout << "No route available\n";
    } else {
        cout << "Time: " << distance[end] << " minutes\n";
        cout << "Path: ";
        vector<int> path;
        for (int node = end; node != -1; node = previous[node]) {
            path.push_back(node);
        }
        for (int j = path.size() - 1; j >= 0; j--) {
            cout << path[j];
            if (j > 0) cout << " -> ";
        }
        cout << endl;
    }
}

void updateGraph(int graph[MAX_NODES][MAX_NODES], int u, int v, int newWeight) {
    graph[u][v] = newWeight;
    graph[v][u] = newWeight;
}

int main() {
    int n = MAX_NODES;

    int graph[MAX_NODES][MAX_NODES] = {
        {-1, 10, 5, -1, -1},
        {-1, -1, 2, 1, -1},
        {-1, -1, -1, 9, 2},
        {-1, -1, -1, -1, 4},
        {-1, -1, -1, -1, -1}
    };

    int startNode, endNode;
    cout << "Enter the start intersection (0 to " << n - 1 << "): ";
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << n - 1 << "): ";
    cin >> endNode;

    bellmanFord(graph, startNode, endNode, n);

    cout << "\nTraffic condition update: The road to the restaurant is now congested.\n";
    updateGraph(graph, 0, 1, 20);

    cout << "\nRecalculating shortest path with updated traffic...\n";
    bellmanFord(graph, startNode, endNode, n);

    return 0;
}
