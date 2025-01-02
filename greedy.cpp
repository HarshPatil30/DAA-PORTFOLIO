#include <iostream>
#include <climits>
#include <vector>

using namespace std;

#define MAX_INTERSECTIONS 5

void deploySensorsAndAvoidHighTraffic(int graph[MAX_INTERSECTIONS][MAX_INTERSECTIONS], int trafficDensity[MAX_INTERSECTIONS], int n, int start, int end) {
    int distance[MAX_INTERSECTIONS];
    int previous[MAX_INTERSECTIONS];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }
    distance[start] = 0;

    vector<bool> visited(n, false);

    for (int i = 0; i < n - 1; i++) {
        int minDist = INT_MAX;
        int u = -1;

       
        for (int j = 0; j < n; j++) {
            if (!visited[j] && trafficDensity[j] < 50) {  
                if (distance[j] < minDist) {
                    minDist = distance[j];
                    u = j;
                }
            }
        }

        if (u == -1) break; 

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != -1 && !visited[v] && trafficDensity[v] < 50) {  
                int newDist = distance[u] + graph[u][v];
                if (newDist < distance[v]) {
                    distance[v] = newDist;
                    previous[v] = u;
                }
            }
        }
    }

    cout << "Shortest route from " << start << " to " << end << " avoiding high traffic:\n";
    if (distance[end] == INT_MAX) {
        cout << "No route available.\n";
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
    int graph[MAX_INTERSECTIONS][MAX_INTERSECTIONS] = {
        {-1, 10, 5, -1, -1}, 
        {-1, -1, 2, 1, -1},    
        {-1, -1, -1, 9, 2},   
        {-1, -1, -1, -1, 4},   
        {-1, -1, -1, -1, -1}, 
    };

    int trafficDensity[MAX_INTERSECTIONS] = {25, 60, 35, 80, 45};  // Traffic densities

    int startNode, endNode;
    cout << "Enter the start intersection (0 to " << MAX_INTERSECTIONS - 1 << "): ";
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << MAX_INTERSECTIONS - 1 << "): ";
    cin >> endNode;

    deploySensorsAndAvoidHighTraffic(graph, trafficDensity, MAX_INTERSECTIONS, startNode, endNode);

    return 0;
}
