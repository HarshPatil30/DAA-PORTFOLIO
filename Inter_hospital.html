#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <functional> // For priority_queue comparison

#define INF std::numeric_limits<int>::max()

// Enum for Patient Priority (High, Medium, Low)
enum class PatientPriority {
    High,   // Emergency, ICU
    Medium, // General
    Low     // Non-urgent cases
};

// Structure for Edge in Graph
struct Edge {
    int destination;
    int weight;
};

// Class for Graph (for Dijkstra's algorithm)
class Graph {
private:
    std::unordered_map<int, std::vector<Edge>> adjList;

public:
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Assuming undirected graph
    }

    std::vector<int> dijkstra(int source, int numHospitals) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        std::vector<int> distances(numHospitals + 1, INF);
        distances[source] = 0;
        pq.push({0, source}); // {distance, node}

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDistance > distances[currentNode]) continue;

            for (const Edge& edge : adjList[currentNode]) {
                int neighbor = edge.destination;
                int weight = edge.weight;

                if (distances[currentNode] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[currentNode] + weight;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }

        return distances;
    }

    void displayShortestPaths(int source, const std::vector<int>& distances) {
        std::cout << "Shortest paths from Hospital " << source << ":\n";
        for (int i = 1; i < distances.size(); i++) {
            std::cout << "Hospital " << i << ": " << (distances[i] == INF ? "No path" : std::to_string(distances[i])) << "\n";
        }
    }
};

// Bed Availability Tracker
class BedAvailabilityTracker {
private:
    std::unordered_map<int, std::unordered_map<std::string, int>> hospitalBeds;

public:
    void updateBedCount(int hospitalID, const std::string& bedType, int count) {
        hospitalBeds[hospitalID][bedType] = count;
        std::cout << "Updated: Hospital " << hospitalID << ", Bed Type: "
                  << bedType << ", Available Beds: " << count << "\n";
    }

    int getAvailableBeds(int hospitalID, const std::string& bedType) {
        if (hospitalBeds.find(hospitalID) != hospitalBeds.end() &&
            hospitalBeds[hospitalID].find(bedType) != hospitalBeds[hospitalID].end()) {
            return hospitalBeds[hospitalID][bedType];
        }
        return 0;
    }

    void displayAllBeds() {
        std::cout << "\nHospital Bed Availability:\n";
        for (const auto& [hospitalID, beds] : hospitalBeds) {
            std::cout << "Hospital " << hospitalID << ":\n";
            for (const auto& [bedType, count] : beds) {
                std::cout << "  " << bedType << ": " << count << " beds available\n";
            }
        }
    }
};

// Patient class for managing patient priority
class Patient {
public:
    int patientID;
    std::string name;
    PatientPriority priority;

    Patient(int id, const std::string& name, PatientPriority priority)
        : patientID(id), name(name), priority(priority) {}

    bool operator<(const Patient& other) const {
        return priority < other.priority; // Higher priority patients come first
    }
};

// Patient Priority Queue
class PatientPriorityQueue {
private:
    std::priority_queue<Patient> pq;

public:
    void addPatient(int id, const std::string& name, PatientPriority priority) {
        Patient p(id, name, priority);
        pq.push(p);
    }

    Patient getNextPatient() {
        if (!pq.empty()) {
            Patient p = pq.top();
            pq.pop();
            return p;
        }
        return Patient(-1, "No Patient", PatientPriority::Low);
    }

    bool hasPatients() {
        return !pq.empty();
    }
};

// Bed Allocation System
class BedAllocationSystem {
private:
    BedAvailabilityTracker& bedTracker;
    PatientPriorityQueue& patientQueue;

public:
    BedAllocationSystem(BedAvailabilityTracker& bedTracker, PatientPriorityQueue& patientQueue)
        : bedTracker(bedTracker), patientQueue(patientQueue) {}

    void allocateBed(int hospitalID, const std::string& bedType) {
        if (!patientQueue.hasPatients()) {
            std::cout << "No patients in the queue.\n";
            return;
        }

        Patient p = patientQueue.getNextPatient();
        int availableBeds = bedTracker.getAvailableBeds(hospitalID, bedType);

        if (availableBeds > 0) {
            bedTracker.updateBedCount(hospitalID, bedType, availableBeds - 1);
            std::cout << "Allocated Bed to Patient " << p.name << " (ID: " << p.patientID << ") in Hospital "
                      << hospitalID << " (" << bedType << ").\n";
        } else {
            std::cout << "No available " << bedType << " beds in Hospital " << hospitalID << " for Patient "
                      << p.name << " (ID: " << p.patientID << ").\n";
        }
    }
};

// Main Program
int main() {
    BedAvailabilityTracker bedTracker;
    PatientPriorityQueue patientQueue;
    BedAllocationSystem allocationSystem(bedTracker, patientQueue);
    Graph graph;
    int numHospitals = 5; // Example number of hospitals

    // Sample hospital connections (edges)
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 4);
    graph.addEdge(4, 5, 1);

    int choice;
    do {
        std::cout << "\n--- Hospital Bed Management System ---\n";
        std::cout << "1. Update Bed Count\n";
        std::cout << "2. Add Patient to Priority Queue\n";
        std::cout << "3. Allocate Bed to Patient\n";
        std::cout << "4. Display All Bed Availability\n";
        std::cout << "5. Display Shortest Paths Between Hospitals\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int hospitalID, count;
            std::string bedType;
            std::cout << "Enter Hospital ID: ";
            std::cin >> hospitalID;
            std::cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            std::cin >> bedType;
            std::cout << "Enter Number of Beds: ";
            std::cin >> count;
            bedTracker.updateBedCount(hospitalID, bedType, count);
            break;
        }
        case 2: {
            int patientID;
            std::string name, priorityStr;
            PatientPriority priority;

            std::cout << "Enter Patient ID: ";
            std::cin >> patientID;
            std::cout << "Enter Patient Name: ";
            std::cin >> name;
            std::cout << "Enter Patient Priority (High/Medium/Low): ";
            std::cin >> priorityStr;

            if (priorityStr == "High") priority = PatientPriority::High;
            else if (priorityStr == "Medium") priority = PatientPriority::Medium;
            else priority = PatientPriority::Low;

            patientQueue.addPatient(patientID, name, priority);
            break;
        }
        case 3: {
            int hospitalID;
            std::string bedType;
            std::cout << "Enter Hospital ID: ";
            std::cin >> hospitalID;
            std::cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            std::cin >> bedType;

            allocationSystem.allocateBed(hospitalID, bedType);
            break;
        }
        case 4:
            bedTracker.displayAllBeds();
            break;
        case 5: {
            int source;
            std::cout << "Enter Source Hospital: ";
            std::cin >> source;
            std::vector<int> distances = graph.dijkstra(source, numHospitals);
            graph.displayShortestPaths(source, distances);
            break;
        }
        case 6:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
