#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_NODES 5

void bellmanFord(int graph[MAX_NODES][MAX_NODES], int start, int end, int n, vector<int> &shortestPath) {
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

void updateTrafficOnPath(int graph[MAX_NODES][MAX_NODES], const vector<int> &shortestPath) {
    cout << "\nTraffic condition update for edges in the shortest path:\n";
    for (size_t i = 0; i < shortestPath.size() - 1; i++) {
        int u = shortestPath[i];
        int v = shortestPath[i + 1];
        int newWeight;
        cout << "Enter new weight for edge (" << u << " -> " << v << ") (-1 to block the road): ";
        cin >> newWeight;
        graph[u][v] = newWeight;
        graph[v][u] = newWeight; 
        cout << "Updated weight for edge (" << u << " -> " << v << ") is now " << newWeight << ".\n";
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

    int startNode, endNode;
    cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> endNode;

    vector<int> shortestPath;
    bellmanFord(graph, startNode, endNode, MAX_NODES, shortestPath);

    char choice;
    do {
        cout << "\nDo you want to update traffic conditions for the shortest path? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            updateTrafficOnPath(graph, shortestPath);
            cout << "\nRecalculating shortest path with updated traffic...\n";
            bellmanFord(graph, startNode, endNode, MAX_NODES, shortestPath);
        }
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
