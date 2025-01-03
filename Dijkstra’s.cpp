#include <iostream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

#define MAX_NODES 5

void dijkstra(int graph[MAX_NODES][MAX_NODES], int start, int end, int n, string places[MAX_NODES]) {
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

    cout << "Dijkstra's Algorithm: Shortest route from " << places[start] << " (" << start << ") to " << places[end] << " (" << end << ")\n";
    if (distance[end] == INT_MAX) {
        cout << "No path found.\n";
    } else {
        cout << "Total time: " << distance[end] << " minutes\n";
        cout << "Path: ";
        vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << places[path[i]] << " (" << path[i] << ")";
            if (i > 0) cout << " -> ";
        }
        cout << endl;
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

    string places[MAX_NODES] = {
        "City Center",
        "Restaurant",
        "Intersection 2",
        "Hospital",
        "Highway"
    };

    // Display the available places and their corresponding numbers
    cout << "Available places and their corresponding numbers:\n";
    for (int i = 0; i < MAX_NODES; i++) {
        cout << i << ": " << places[i] << endl;
    }

    int startNode, endNode;

    // Prompt the user for the start and end intersections
    cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> endNode;

    dijkstra(graph, startNode, endNode, MAX_NODES, places);

    return 0;
}
