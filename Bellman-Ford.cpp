#include <iostream>
#include <climits>

using namespace std;

#define MAX_NODES 5

void bellmanFord(int graph[MAX_NODES][MAX_NODES], int start, int n) {
    int distance[MAX_NODES];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
    }
    distance[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (graph[u][v] != -1 && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                }
            }
        }
    }

    cout << "Shortest travel times from intersection " << start << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To intersection " << i << " : ";
        if (distance[i] == INT_MAX) {
            cout << "No route available\n";
        } else {
            cout << distance[i] << " minutes\n";
        }
    }
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

    int startNode = 0;

    bellmanFord(graph, startNode, n);

    return 0;
}
