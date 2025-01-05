#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>
#include <functional> // For priority_queue comparison

// Enum for Patient Priority (High, Medium, Low)
enum class PatientPriority {
    High,   // Emergency, ICU
    Medium, // General
    Low     // Non-urgent cases
};

// Bed Availability Tracker
class BedAvailabilityTracker {
private:
    std::unordered_map<int, std::unordered_map<std::string, int>> hospitalBeds; // HospitalID -> BedType -> Available Beds

public:
    // Update bed availability for a specific hospital and bed type
    void updateBedCount(int hospitalID, const std::string& bedType, int count) {
        hospitalBeds[hospitalID][bedType] = count;
        std::cout << "Updated: Hospital " << hospitalID << ", Bed Type: "
                  << bedType << ", Available Beds: " << count << "\n";
    }

    // Get available beds in a specific hospital and bed type
    int getAvailableBeds(int hospitalID, const std::string& bedType) {
        if (hospitalBeds.find(hospitalID) != hospitalBeds.end() &&
            hospitalBeds[hospitalID].find(bedType) != hospitalBeds[hospitalID].end()) {
            return hospitalBeds[hospitalID][bedType];
        }
        return 0;
    }

    // Display all available beds
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

    // Define comparison for priority queue
    bool operator<(const Patient& other) const {
        return priority < other.priority; // Higher priority (emergency) patients come first
    }
};

// Patient Priority Queue
class PatientPriorityQueue {
private:
    std::priority_queue<Patient> pq;

public:
    // Add patient to the priority queue
    void addPatient(int id, const std::string& name, PatientPriority priority) {
        Patient p(id, name, priority);
        pq.push(p);
    }

    // Get the highest priority patient (i.e., the patient at the front)
    Patient getNextPatient() {
        if (!pq.empty()) {
            Patient p = pq.top();
            pq.pop();
            return p;
        }
        return Patient(-1, "No Patient", PatientPriority::Low);  // Return a default patient if queue is empty
    }

    // Check if there are any patients in the queue
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

    // Allocate a bed to the next highest priority patient
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

    int choice;
    do {
        std::cout << "\n--- Hospital Bed Management System ---\n";
        std::cout << "1. Update Bed Count\n";
        std::cout << "2. Add Patient to Priority Queue\n";
        std::cout << "3. Allocate Bed to Patient\n";
        std::cout << "4. Display All Bed Availability\n";
        std::cout << "5. Exit\n";
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
        case 5:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
