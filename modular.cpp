#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>
#include<ctime>
using namespace std;

#define MAX_NODES 5
#define MAX_INTERSECTIONS 5
struct Supply {
    std::string name;
    int quantity;
    double cost, storageSpaceRequired;
    std::string storageLocation;

    bool operator<(const Supply& other) const {
        return quantity < other.quantity;
    }
};

void displayStorage(const std::vector<Supply>& supplies) {
    std::cout << "\nCurrent Storage:\n";
    for (const auto& supply : supplies) {
        std::cout << "Item: " << supply.name << ", Qty: " << supply.quantity
                  << ", Cost: INR " << (supply.cost * 80) << ", Location: " << supply.storageLocation
                  << ", Space: " << supply.storageSpaceRequired << " ft^2\n";
    }
}

void optimizeStorage(std::vector<Supply>& supplies) {
    std::sort(supplies.begin(), supplies.end());
    std::cout << "\nOptimized Storage (sorted by quantity):\n";
    displayStorage(supplies);
}

void checkStorageCapacity(const std::vector<Supply>& supplies, double totalCapacity) {
    double usedCapacity = 0;
    for (const auto& supply : supplies) {
        usedCapacity += supply.storageSpaceRequired;
    }
    std::cout << (usedCapacity > totalCapacity ? "Capacity exceeded!" : "Storage OK.")
              << " Used: " << usedCapacity << " ft^2\n";
}

void addItem(std::vector<Supply>& storage) {
    Supply newItem;
    std::cout << "\nEnter item details:\n";
    std::cout << "Name: ";
    std::cin >> newItem.name;
    std::cout << "Quantity: ";
    std::cin >> newItem.quantity;
    std::cout << "Cost per unit: ";
    std::cin >> newItem.cost;
    std::cout << "Storage space required (in square feet): ";
    std::cin >> newItem.storageSpaceRequired;
    std::cout << "Storage location: ";
    std::cin >> newItem.storageLocation;

    storage.push_back(newItem);
    std::cout << "Item added successfully!\n";
}

void removeItem(std::vector<Supply>& storage) {
    std::string itemName;
    std::cout << "\nEnter the name of the item to remove: ";
    std::cin >> itemName;

    auto it = std::remove_if(storage.begin(), storage.end(), [&itemName](const Supply& supply) {
        return supply.name == itemName;
    });

    if (it != storage.end()) {
        storage.erase(it, storage.end());
        std::cout << "Item removed successfully!\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void storageMenu() {
    std::vector<Supply> storage = {
        {"Bandages", 50, 1.5, 5.0, "Shelf A1"},
        {"Gloves", 200, 0.5, 4.0, "Shelf B2"},
        {"Masks", 100, 2.0, 6.0, "Shelf C3"},
        {"Sanitizers", 80, 3.0, 5.5, "Shelf D4"}
    };

    int choice;
    double totalCapacity = 30.0;

    do {
        std::cout << "\n\nStorage Management System Menu:\n";
        std::cout << "1. Display Storage\n";
        std::cout << "2. Optimize Storage\n";
        std::cout << "3. Check Storage Capacity\n";
        std::cout << "4. Add Item\n";
        std::cout << "5. Remove Item\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayStorage(storage);
                break;
            case 2:
                optimizeStorage(storage);
                break;
            case 3:
                checkStorageCapacity(storage, totalCapacity);
                break;
            case 4:
                addItem(storage);
                break;
            case 5:
                removeItem(storage);
                break;
            case 6:
                std::cout << "Exiting Storage Management System...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

class Supplier {
public:
    string name;
    int cost;  // Cost in thousands of rupees
    int quality;  // Rating on a scale of 1 to 10 (1 = lowest quality, 10 = highest quality)
    int deliveryTime;  // Rating on a scale of 1 to 10 (1 = longest time, 10 = quickest time)

    Supplier(string name, int cost, int quality, int deliveryTime) {
        this->name = name;
        this->cost = cost;
        this->quality = quality;
        this->deliveryTime = deliveryTime;
    }

    double calculateScore() const {
        return quality * 0.6 + deliveryTime * 0.4;  // Weighted score
    }
};

void supplierSelection() {
    vector<Supplier> suppliers = {
        Supplier("HealthEquip", 30, 9, 8),
        Supplier("MediTech", 40, 8, 7),
        Supplier("MedSupplyCo", 40, 7, 9),
        Supplier("PharmaSource", 10, 10, 6),
        Supplier("CareLogix", 30, 6, 10)
    };

    int budget;
    cout << "Enter the total budget (in thousands of rupees): ";
    cin >> budget;

    int n = suppliers.size();
    vector<vector<double>> dp(n + 1, vector<double>(budget + 1, 0));
    vector<vector<bool>> selected(n + 1, vector<bool>(budget + 1, false));

    // Knapsack DP algorithm
    for (int i = 1; i <= n; ++i) {
        for (int b = 1; b <= budget; ++b) {
            if (suppliers[i - 1].cost <= b) {
                double includeScore = dp[i - 1][b - suppliers[i - 1].cost] + suppliers[i - 1].calculateScore();
                double excludeScore = dp[i - 1][b];

                if (includeScore > excludeScore) {
                    dp[i][b] = includeScore;
                    selected[i][b] = true;
                } else {
                    dp[i][b] = excludeScore;
                }
            } else {
                dp[i][b] = dp[i - 1][b];
            }
        }
    }

    // Backtracking to find the selected suppliers
    vector<Supplier> selectedSuppliers;
    int remainingBudget = budget;
    double maxScore = dp[n][budget];

    for (int i = n; i > 0 && remainingBudget > 0; --i) {
        if (selected[i][remainingBudget]) {
            selectedSuppliers.push_back(suppliers[i - 1]);
            remainingBudget -= suppliers[i - 1].cost;
        }
    }

    // Output results
    cout << "\nMaximum Score Achieved: " << maxScore << "\n";
    cout << "Selected Suppliers:\n";
    for (const auto& supplier : selectedSuppliers) {
        cout << "Name: " << supplier.name
             << ", Cost: " << supplier.cost << "k"
             << ", Quality: " << supplier.quality
             << ", Delivery Time Rating: " << supplier.deliveryTime << "\n";
    }
}

struct Edge {
    int destination;
    double distance; // Distance in kilometers
};

struct Hospital {
    std::string name;
    int id;
};

class Graph {
public:
    Graph(int n) : adjList(n) {}

    void addEdge(int u, int v, double dist) {
        adjList[u].push_back({v, dist});
        adjList[v].push_back({u, dist}); // Bidirectional road
    }

    // Dijkstra's Algorithm
    std::vector<double> dijkstra(int start) {
        std::vector<double> distances(adjList.size(), INT_MAX);
        distances[start] = 0;
        std::vector<bool> visited(adjList.size(), false);

        for (size_t i = 0; i < adjList.size(); ++i) {
            int u = -1;
            double minDist = INT_MAX;
            for (size_t j = 0; j < adjList.size(); ++j) {
                if (!visited[j] && distances[j] < minDist) {
                    minDist = distances[j];
                    u = j;
                }
            }

            if (u == -1) break; // No more nodes to visit

            visited[u] = true;

            for (const auto& edge : adjList[u]) {
                int v = edge.destination;
                double dist_v = edge.distance;
                if (distances[u] + dist_v < distances[v]) {
                    distances[v] = distances[u] + dist_v;
                }
            }
        }

        return distances;
    }

private:
    std::vector<std::vector<Edge>> adjList;
};

void displayHospitals(const std::vector<Hospital>& hospitals) {
    std::cout << "Hospitals List (ID - Name):\n";
    for (const auto& hospital : hospitals) {
        std::cout << hospital.id + 1 << " - " << hospital.name << "\n"; // Display 1-based index
    }
}

void findShortestPaths(Graph& graph, const std::vector<Hospital>& hospitals, int warehouse) {
    std::vector<double> shortestPaths = graph.dijkstra(warehouse);

    std::cout << "\nShortest paths from warehouse (" << hospitals[warehouse].name << "):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Distance to " << hospitals[i].name << ": " << shortestPaths[i] << " km\n";
    }
}

void findOptimalRoute(Graph& graph, const std::vector<Hospital>& hospitals, int warehouse) {
    // Get user input for supply requests
    int requestCount;
    std::cout << "\nEnter number of hospitals with supply requests: ";
    std::cin >> requestCount;

    std::vector<int> requestedHospitals;
    std::cout << "Enter the hospital numbers (1-based index) with supply requests:\n";
    for (int i = 0; i < requestCount; ++i) {
        int hospitalNumber;
        std::cin >> hospitalNumber;
        requestedHospitals.push_back(hospitalNumber - 1); // Adjust for 0-based index
    }

    // Find the shortest paths to the requested hospitals
    std::vector<double> shortestPaths = graph.dijkstra(warehouse);

    std::vector<std::pair<std::string, double>> optimalRoute;
    for (int hospitalId : requestedHospitals) {
        optimalRoute.push_back({hospitals[hospitalId].name, shortestPaths[hospitalId]});
    }

    // Sort hospitals by distance to warehouse
    std::sort(optimalRoute.begin(), optimalRoute.end(), [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
        return a.second < b.second;
    });

    std::cout << "\nOptimal route covering requested hospitals:\n";
    double totalDistance = 0;
    for (const auto& entry : optimalRoute) {
        std::cout << "Hospital: " << entry.first << " | Distance: " << entry.second << " km\n";
        totalDistance += entry.second;
    }

    std::cout << "\nTotal distance for optimal route: " << totalDistance << " km\n";
}

// Main menu function
void Distribution_menu() {
    std::vector<Hospital> hospitals = {
        {"Warehouse", 0},
        {"Hospital A", 1},
        {"Hospital B", 2},
        {"Hospital C", 3},
        {"Hospital D", 4}
    };

    Graph graph(5);
    graph.addEdge(0, 1, 10); // Warehouse to Hospital A
    graph.addEdge(0, 2, 15); // Warehouse to Hospital B
    graph.addEdge(1, 2, 5);  // Hospital A to Hospital B
    graph.addEdge(1, 3, 20); // Hospital A to Hospital C
    graph.addEdge(2, 3, 10); // Hospital B to Hospital C
    graph.addEdge(2, 4, 25); // Hospital B to Hospital D
    graph.addEdge(3, 4, 30); // Hospital C to Hospital D

    int warehouse = 0;

    while (true) {
        std::cout << "\n===== Main Menu =====\n";
        std::cout << "1. Display Hospitals\n";
        std::cout << "2. Find Shortest Paths\n";
        std::cout << "3. Find Optimal Route\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayHospitals(hospitals);
                break;
            case 2:
                findShortestPaths(graph, hospitals, warehouse);
                break;
            case 3:
                findOptimalRoute(graph, hospitals, warehouse);
                break;
            case 4:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }
}

struct Item {
    string name;
    int quantity;
    int criticalLevel;
    int expiryDays; // Days until expiration

    bool operator<(const Item& other) const {
        return expiryDays > other.expiryDays; // Min-heap for expiration
    }
};

class InventoryManagement {
private:
    vector<Item> inventory;
    priority_queue<Item> expirationQueue; // Min-heap for managing expirations

    // Binary search for item lookup
    int findItemIndex(const string& name) const {
        int low = 0, high = inventory.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (inventory[mid].name == name) return mid;
            else if (inventory[mid].name < name) low = mid + 1;
            else high = mid - 1;
        }
        return -1; // Not found
    }

public:
    void addItem(const string& name, int quantity, int criticalLevel, int expiryDays) {
        Item newItem = {name, quantity, criticalLevel, expiryDays};
        inventory.push_back(newItem);
        expirationQueue.push(newItem);
        sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
            return a.name < b.name; // Maintain alphabetical order for binary search
        });
    }

    void checkItemStatus(const string& name) const {
        int index = findItemIndex(name);
        if (index == -1) {
            cout << "Item not found in inventory.\n";
            return;
        }

        const Item& item = inventory[index];
        cout << "Name: " << item.name
             << ", Quantity: " << item.quantity
             << ", Critical Level: " << item.criticalLevel
             << ", Expiry Days: " << item.expiryDays << "\n";
    }

    void displayDepletedStock() {
        vector<Item> depleted;
        for (const auto& item : inventory) {
            if (item.quantity < item.criticalLevel) {
                depleted.push_back(item);
            }
        }

        // Sort by most critical first (greedy approach)
        sort(depleted.begin(), depleted.end(), [](const Item& a, const Item& b) {
            return (a.criticalLevel - a.quantity) > (b.criticalLevel - b.quantity);
        });

        cout << "\nDepleted Stock Items (prioritized):\n";
        for (const auto& item : depleted) {
            cout << "Name: " << item.name
                 << ", Quantity: " << item.quantity
                 << ", Critical Level: " << item.criticalLevel
                 << ", Shortage: " << (item.criticalLevel - item.quantity) << "\n";
        }
    }

    void handleExpirations() {
        cout << "\nItems near expiration:\n";
        while (!expirationQueue.empty() && expirationQueue.top().expiryDays <= 7) {
            const Item& item = expirationQueue.top();
            cout << "Name: " << item.name
                 << ", Quantity: " << item.quantity
                 << ", Expiry Days: " << item.expiryDays << "\n";
            expirationQueue.pop();
        }
    }

    void manageInventory() {
        int choice;
        do {
            cout << "\nInventory Management Menu:\n";
            cout << "1. Add Item\n";
            cout << "2. Check Item Status\n";
            cout << "3. Display Depleted Stock\n";
            cout << "4. Handle Expirations\n";
            cout << "5. Exit Inventory Management\n";
            cout << "Enter your choice: ";
            cin >> choice;

            string name;
            int quantity, criticalLevel, expiryDays;
            switch (choice) {
                case 1:
                    cout << "Enter item name: ";
                    cin >> name;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    cout << "Enter critical level: ";
                    cin >> criticalLevel;
                    cout << "Enter expiry days: ";
                    cin >> expiryDays;
                    addItem(name, quantity, criticalLevel, expiryDays);
                    cout << "Item added successfully.\n";
                    break;
                case 2:
                    cout << "Enter item name to check status: ";
                    cin >> name;
                    checkItemStatus(name);
                    break;
                case 3:
                    displayDepletedStock();
                    break;
                case 4:
                    handleExpirations();
                    break;
                case 5:
                    cout << "Exiting Inventory Management...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};

// Function to call Inventory Management within a larger menu
void InventoryMenu() {
    InventoryManagement inventory;
    inventory.addItem("Paracetamol", 100, 50, 10);
    inventory.addItem("Aspirin", 30, 40, 5);
    inventory.addItem("Ibuprofen", 10, 20, 2);
    inventory.addItem("Amoxicillin", 5, 10, 15);




inventory.manageInventory();

}

struct Node {
    int id;
    int time;
    bool operator>(const Node& other) const {
        return time > other.time;
    }
};

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

    path.push_back(end);

    cout << "Greedy Algorithm: Route from " << places[start] << " to " << places[end] << "\n";
    cout << "Total distance: " << totalDistance << " kilometers\n";
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << places[path[i]] << " (" << path[i] << ")";
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void bellmanFord(int graph[MAX_NODES][MAX_NODES], int traffic[MAX_NODES][MAX_NODES], int start, int end, int n, vector<int> &shortestPath, bool includeTraffic,string places[MAX_NODES]) {
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
                // Skip blocked roads (traffic value = -1)
                if (traffic[u][v] == -1 || graph[u][v] == -1) continue;

                int effectiveWeight = graph[u][v];
                if (includeTraffic && traffic[u][v] != -1) {
                    effectiveWeight += traffic[u][v];  // Add traffic to the weight
                }

                if (distance[u] != INT_MAX && distance[u] + effectiveWeight < distance[v]) {
                    distance[v] = distance[u] + effectiveWeight;
                    previous[v] = u;
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
            //cout << shortestPath[i];
             cout << places[shortestPath[i]] << " (" << shortestPath[i] << ")";
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

void handleBellmanFordWithTraffic(int graph[MAX_NODES][MAX_NODES], int traffic[MAX_NODES][MAX_NODES], int start, int end, int n,string places[MAX_NODES]) {
    vector<int> shortestPath;
    cout << "\nCalculating shortest path without traffic (Bellman-Ford)...\n";
    bellmanFord(graph, traffic, start, end, n, shortestPath, false,places);

    if (!shortestPath.empty()) {
        updateTrafficOnPath(traffic, shortestPath);
        cout << "\nRecalculating shortest path with updated traffic...\n";
        bellmanFord(graph, traffic, start, end, n, shortestPath, true,places);
    }
}

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
        cout << "Total distance: " << distance[end] << " kilometers\n";
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

void handleShortestPathWithTraffic(int graph[MAX_NODES][MAX_NODES], int trafficMatrix[MAX_NODES][MAX_NODES], const string places[MAX_NODES]) {
    cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
    int startNode, endNode;
    cin >> startNode;
    cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
    cin >> endNode;

    // Set traffic to 0 if the start and end are the same (e.g., "Park" to "Park")
    if (startNode == endNode) {
        trafficMatrix[startNode][endNode] = 0;
    }

    cout << "Enter the traffic conditions between intersections (0: No traffic, 10: Road blocked, -1: No road):\n";
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            if (graph[i][j] == -1) {
                trafficMatrix[i][j] = -1;
            } else {
                if (i == j) {
                    trafficMatrix[i][j] = 0; // Ensure traffic between same intersection is 0
                } else {
                    cout << "Traffic from " << places[i] << " to " << places[j] << ": ";
                    cin >> trafficMatrix[i][j];
                }
            }
        }
    }

    findShortestPathWithTraffic(graph, trafficMatrix, MAX_NODES, startNode, endNode, places);
}


// New Function for Optimizing Signal Timings
void optimizeSignalTimings(int trafficDensity[MAX_INTERSECTIONS], int totalTime) {
    int totalDensity = 0;
    int signalTimings[MAX_INTERSECTIONS] = {0};

    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        totalDensity += trafficDensity[i];
    }

    int remainingTime = totalTime;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        signalTimings[i] = (trafficDensity[i] * totalTime) / totalDensity;
        remainingTime -= signalTimings[i];
    }

    for (int i = 0; remainingTime > 0 && i < MAX_INTERSECTIONS; i++) {
        signalTimings[i]++;
        remainingTime--;
    }

    cout << "Optimized signal timings for each intersection:" << endl;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        cout << "Intersection " << i + 1 << ": " << signalTimings[i] << " seconds" << endl;
    }
}
string intersectionNames[MAX_INTERSECTIONS] = {
    "City Center", "Restaurant", "Park", "Hospital", "Highway"
};

// Existing function to calculate and display green light times (using backtracking)
void mergeoptimizeSignalTimings(int trafficDensity[MAX_INTERSECTIONS], int totalTime) {
    int totalDensity = 0;
    int signalTimings[MAX_INTERSECTIONS] = {0};

    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        totalDensity += trafficDensity[i];
    }

    int remainingTime = totalTime;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        signalTimings[i] = (trafficDensity[i] * totalTime) / totalDensity;
        remainingTime -= signalTimings[i];
    }

    for (int i = 0; remainingTime > 0 && i < MAX_INTERSECTIONS; i++) {
        signalTimings[i]++;
        remainingTime--;
    }

    cout << "Optimized signal timings for each intersection:" << endl;
    for (int i = 0; i < MAX_INTERSECTIONS; i++) {
        cout << "Intersection " << i + 1 << ": " << signalTimings[i] << " seconds" << endl;
    }
}

// New function using Merge Sort to calculate and display green light times
void merge1(int arr[], int left, int mid, int right, int intersections[]) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];
    int leftIntersections[n1], rightIntersections[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
        leftIntersections[i] = intersections[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
        rightIntersections[i] = intersections[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            intersections[k] = leftIntersections[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            intersections[k] = rightIntersections[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        intersections[k] = leftIntersections[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        intersections[k] = rightIntersections[j];
        j++;
        k++;
    }
}

void mergeSort1(int arr[], int left, int right, int intersections[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort1(arr, left, mid, intersections);
        mergeSort1(arr, mid + 1, right, intersections);

        merge1(arr, left, mid, right, intersections);
    }
}

void displayGreenLightTimes(int congestionLevels[], int intersections[], int size, int totalGreenTime) {
    cout << "Green light timings for each intersection based on congestion levels:" << endl;

    int totalCongestion = 0;
    for (int i = 0; i < size; i++) {
        totalCongestion += congestionLevels[i];
    }

    for (int i = 0; i < size; i++) {
        int greenTime = (congestionLevels[i] * totalGreenTime) / totalCongestion;
        cout << intersectionNames[intersections[i]] << ": " << greenTime << " seconds" << endl;
    }
}
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return -1;
}

void locateCongestionLevel(int arr[], int idx[], int size, int target) {
    if (target >= 1 && target <= size) {
        int intersectionIndex = target - 1;
        cout << "Congestion level at Intersection " << target << " is " << arr[intersectionIndex] << " congestion units." << endl;
    } else {
        cout << "Invalid intersection number!" << endl;
    }
}

void merge(int arr[], int left, int mid, int right, int idx[]) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2], leftIdx[n1], rightIdx[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
        leftIdx[i] = idx[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
        rightIdx[i] = idx[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] >= rightArr[j]) {
            arr[k] = leftArr[i];
            idx[k] = leftIdx[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            idx[k] = rightIdx[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        idx[k] = leftIdx[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        idx[k] = rightIdx[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right, int idx[]) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, idx);
        mergeSort(arr, mid + 1, right, idx);

        merge(arr, left, mid, right, idx);
    }
}
void displayCongestionLevels(int arr[], int idx[], int size) {
    cout << "Congestion levels sorted from highest to lowest:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Intersection " << idx[i] + 1 << ": " << arr[i] << " congestion units" << endl;
    }
}


void menuDrivenProgram(int graph[MAX_NODES][MAX_NODES], int traffic[MAX_NODES][MAX_NODES], string places[MAX_NODES]) {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Ambulance Route Optimization\n";
        cout << "2. Inventory management\n";
        cout<<"3.Supply Distribution optimization\n";
        cout << "4.Supplier selection\n";
        cout<<"5.Storage optimizing\n";
        cout<<"6.Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    cout << "\nAmbulance Route Optimization Sub-Menu:\n";
                    cout << "1. Calculate shortest path using Greedy Algorithm\n";
                    cout << "2. Calculate and update shortest path using Bellman-Ford\n";
                    cout << "3. Calculate shortest path considering traffic (Dijkstra's Algorithm)\n";
                    cout << "4. Optimize Signal Timings (Backtracking)\n";
                    cout << "5. Optimize Signal Timings (Merge Sort)\n";
                    cout << "6. Display Congestion Level (Binary Search)\n";
                    cout << "7. Exit to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    static int startNode, endNode;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
                            cin >> startNode;
                            cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
                            cin >> endNode;
                            greedyShortestPath(graph, startNode, endNode, MAX_NODES, places);
                            break;

                        case 2:
                            cout << "Enter the start intersection (0 to " << MAX_NODES - 1 << "): ";
                            cin >> startNode;
                            cout << "Enter the end intersection (0 to " << MAX_NODES - 1 << "): ";
                            cin >> endNode;
                            handleBellmanFordWithTraffic(graph, traffic, startNode, endNode, MAX_NODES, places);
                            break;

                        case 3:
                            handleShortestPathWithTraffic(graph, traffic, places);
                            break;

                        case 4: {
                            int trafficDensity[MAX_INTERSECTIONS];
                            cout << "Enter the traffic density at each intersection:" << endl;
                            for (int i = 0; i < MAX_INTERSECTIONS; i++) {
                                cout << "Intersection " << i + 1 << ": ";
                                cin >> trafficDensity[i];
                            }
                            int totalTime;
                            cout << "Enter the total time available for signal optimization (in seconds): ";
                            cin >> totalTime;
                            optimizeSignalTimings(trafficDensity, totalTime);
                        } break;

                        case 5: {
                            int congestionLevels[MAX_INTERSECTIONS];
                            int intersections[MAX_INTERSECTIONS] = {0, 1, 2, 3, 4};  // Intersection indices

                            cout << "Enter the traffic congestion levels for " << MAX_INTERSECTIONS << " intersections:" << endl;
                            for (int i = 0; i < MAX_INTERSECTIONS; i++) {
                                cout << intersectionNames[i] << ": ";
                                cin >> congestionLevels[i];
                            }

                            mergeSort1(congestionLevels, 0, MAX_INTERSECTIONS - 1, intersections);

                            int totalGreenTime;
                            cout << "\nEnter the total green light time available (in seconds): ";
                            cin >> totalGreenTime;

                            displayGreenLightTimes(congestionLevels, intersections, MAX_INTERSECTIONS, totalGreenTime);
                        } break;

                        case 6: {
                            int size;
                            cout << "Enter the number of intersections (max " << MAX_INTERSECTIONS << "): ";
                            cin >> size;

                            if (size > MAX_INTERSECTIONS) {
                                cout << "Exceeds the maximum number of intersections." << endl;
                                return;
                            }

                            int congestionLevels[size];
                            int intersectionIds[size];

                            srand(time(0));

                            cout << "Generating random congestion levels for " << size << " intersections:" << endl;
                            for (int i = 0; i < size; i++) {
                                congestionLevels[i] = rand() % 101;
                                intersectionIds[i] = i;
                                cout << "Intersection " << i + 1 << ": " << congestionLevels[i] << " congestion units" << endl;
                            }

                            mergeSort(congestionLevels, 0, size - 1, intersectionIds);

                            displayCongestionLevels(congestionLevels, intersectionIds, size);

                            int targetIntersection;
                            cout << "\nEnter the intersection number to get the congestion level: ";
                            cin >> targetIntersection;

                            locateCongestionLevel(congestionLevels, intersectionIds, size, targetIntersection);
                        } break;

                        case 7:
                            cout << "Exiting to Main Menu.\n";
                            break;

                        default:
                            cout << "Invalid sub-choice. Please try again.\n";
                            break;
                    }
                } while (subChoice != 7);
            } break;

            case 2:
                InventoryMenu();
                break;
            case 3: Distribution_menu();
            break;
           case 4:supplierSelection();
            break;
            case 5:storageMenu();  // Call the storage management menu
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);
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

    string places[MAX_NODES] = {
        "City Center",
        "Park",
        "School",
        "Hospital",
        "Mall",
    };

    menuDrivenProgram(graph, traffic, places);

    return 0;
}
