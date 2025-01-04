#include <iostream>
#include <climits>
#include <vector>
using namespace std;

#define MAX_NODES 5

void greedyShortestPath(int graph[MAX_NODES][MAX_NODES], int start, int end, int n, string places[MAX_NODES]) {
    bool visited[MAX_NODES] = {false};
    vector<int> path;
    int currentNode = start;
    int totalDistance = 0;

    while (currentNode != end) {
        visited[currentNode] = true;
        path.push_back(currentNode);

        int nextNode = -1;
        int minDistance = INT_MAX;

        // Find the closest unvisited neighbor
        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[currentNode][i] != -1 && graph[currentNode][i] < minDistance) {
                nextNode = i;
                minDistance = graph[currentNode][i];
            }
        }

        if (nextNode == -1) {
            cout << "No path found from " << places[start] << " to " << places[end] << ".\n";
            return;
        }

        totalDistance += minDistance;
        currentNode = nextNode;
    }

    // Add the end node to the path
    path.push_back(end);

    // Output the result
    cout << "Greedy Algorithm: Route from " << places[start] << " to " << places[end] << "\n";
    cout << "Total distance: " << totalDistance << " kilometers\n";
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << places[path[i]] << " (" << path[i] << ")";
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 10, 5, -1, 2},
        {10, 0, 2, 1, -1},
        {5, 2, 0, 9, 2},
        {-1, 1, 9, 0, 4},
        {2, -1, 2, 4, 0},
    };

    string places[MAX_NODES] = {
        "City Center",
        "Restaurant",
        "Park",
        "Hospital",
        "Highway"
    };

    cout << "Available places and their corresponding numbers:\n";
    for (int i = 0; i < MAX_NODES; i++) {
        cout << i << ": " << places[i] << endl;
    }

    int startNode, endNode;

    cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> endNode;

    greedyShortestPath(graph, startNode, endNode, MAX_NODES, places);

    return 0;
}
