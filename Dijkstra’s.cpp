#include <iostream>
#include <climits>
#include <queue>

using namespace std;

#define MAX_NODES 5

void dijkstra(int graph[MAX_NODES][MAX_NODES], int start, int n) {
    int distance[MAX_NODES];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
    }
    distance[start] = 0;

    priority_queue<pair<int, int>, pair<int, int>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentNode = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distance[currentNode]) {
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] != -1) {
                int newDist = currentDistance + graph[currentNode][i];

                if (newDist < distance[i]) {
                    distance[i] = newDist;
                    pq.push({newDist, i});
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

    dijkstra(graph, startNode, n);

    return 0;
}
