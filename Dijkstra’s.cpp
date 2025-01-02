#include <iostream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

#define MAX_NODES 5

void dijkstra(int graph[MAX_NODES][MAX_NODES], int start, int end, int n) {
    int distance[MAX_NODES];
    int previous[MAX_NODES];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }
    distance[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
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
                    previous[i] = currentNode;
                    pq.push({newDist, i});
                }
            }
        }
    }

    cout << "Dijkstra's Algorithm: Shortest route for ambulance from " << start << " to " << end << "\n";
    if (distance[end] == INT_MAX) {
        cout << "No direct path found, trying alternative routes...\n";
    } else {
        cout << "Total time: " << distance[end] << " minutes\n";
        cout << "Path: ";
        vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {
        {-1, 10, 5, -1, -1},
        {-1, -1, 2, 1, -1},
        {-1, -1, -1, 9, 2},
        {-1, -1, -1, -1, 4},
        {-1, -1, -1, -1, -1},
    };

    int startNode = 3;
    int endNode = 0;

    dijkstra(graph, startNode, endNode, MAX_NODES);

    return 0;
}
