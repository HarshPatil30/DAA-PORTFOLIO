#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class BedAvailabilityTracker {
private:
    // HospitalID -> BedType -> Available Beds
    std::unordered_map<int, std::unordered_map<std::string, int>> hospitalBeds;

public:
    // Add or update bed availability for a hospital
    void updateBedCount(int hospitalID, const std::string& bedType, int count) {
        hospitalBeds[hospitalID][bedType] = count;
        std::cout << "Updated: Hospital " << hospitalID << ", Bed Type: "
                  << bedType << ", Available Beds: " << count << "\n";
    }

    // Get the number of available beds for a specific hospital and bed type
    int getAvailableBeds(int hospitalID, const std::string& bedType) {
        if (hospitalBeds.find(hospitalID) != hospitalBeds.end() &&
            hospitalBeds[hospitalID].find(bedType) != hospitalBeds[hospitalID].end()) {
            return hospitalBeds[hospitalID][bedType];
        }
        return 0; // Default to 0 if not found
    }

    // Get hospitals with available beds of a specific type
    std::vector<int> getHospitalsWithAvailableBeds(const std::string& bedType) {
        std::vector<int> result;
        for (const auto& [hospitalID, beds] : hospitalBeds) {
            if (beds.find(bedType) != beds.end() && beds.at(bedType) > 0) {
                result.push_back(hospitalID);
            }
        }
        return result;
    }

    // Display all hospital bed availability
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

int main() {
    BedAvailabilityTracker tracker;
    int choice;

    do {
        std::cout << "\n--- Bed Availability Tracker ---\n";
        std::cout << "1. Update Bed Count\n";
        std::cout << "2. Query Bed Count\n";
        std::cout << "3. Get Hospitals with Available Beds\n";
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
            tracker.updateBedCount(hospitalID, bedType, count);
            break;
        }
        case 2: {
            int hospitalID;
            std::string bedType;
            std::cout << "Enter Hospital ID: ";
            std::cin >> hospitalID;
            std::cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            std::cin >> bedType;
            int availableBeds = tracker.getAvailableBeds(hospitalID, bedType);
            std::cout << "Available Beds in Hospital " << hospitalID
                      << " (" << bedType << "): " << availableBeds << "\n";
            break;
        }
        case 3: {
            std::string bedType;
            std::cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            std::cin >> bedType;
            std::vector<int> hospitals = tracker.getHospitalsWithAvailableBeds(bedType);
            if (!hospitals.empty()) {
                std::cout << "Hospitals with available " << bedType << " beds:\n";
                for (int hospitalID : hospitals) {
                    std::cout << "  Hospital " << hospitalID << "\n";
                }
            } else {
                std::cout << "No hospitals with available " << bedType << " beds.\n";
            }
            break;
        }
        case 4:
            tracker.displayAllBeds();
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
